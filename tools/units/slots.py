#!/usr/bin/env python3
"""slots.py -- the callee-saved and stack-slot map of one body, ours against retail's.

A residue that survives every statement rewrite is usually an *allocation*: the compiler
chose a different callee-saved register for the address of a local, or put two spill
slots the other way round, and the scheduler and frame follow from that choice.  This
tool states the two allocations side by side, in the words a reader uses for a prologue:

* **the saved-register order**, from the prologue's stores and the epilogue's loads,
  GPR and floating-point separately, with each register's stack offset;
* **every stack slot**, with the local (and, for an aggregate, the member) whose home it
  is, the size the DWARF gives that local, and the register that holds its *address*
  (``addiu $s4,$sp,0x1C0``) or the registers that read and write its *value*;
* **the frame size**, from the ``addiu $sp,$sp,-N`` the prologue makes;
* **the diff**, naming each exchange exactly: ``retail &sp.flg -> s4, ours -> s6``.

The two sides come from different places on purpose:

* retail's instructions are the split at ``asm/nonmatchings/<segment>/<fn>.s`` -- the
  generated tree, so a stale compile cannot move retail's answer;
* ours are the same compile :mod:`units.measure` makes: the unit's recorded
  ``tu_builds`` pair (or ``--draft``), staged and compiled the way ``place`` stages it,
  with relocations masked by :mod:`units.measure`'s rule so a field a relocation owns is
  never evidence.

Names and sizes come from the DWARF both binaries carry: retail's from the pinned ELF,
ours from the object the compile just wrote.  Attribution is a *fact* about one side's
own records, never a guess about the other's: a slot with no local in that side's DWARF
prints as ``0xOFF (unattributed)``.

The one equality that is not DWARF's is a *slot move*: two slots are the same slot put
elsewhere when the multiset of accesses to them -- mnemonic and register, which the
schedule does not change -- is equal and unique on both sides.  The tool then reports
``retail 0xA0 -> ours 0xB0``, that being the compiler's own allocation read off the code;
a local our DWARF names at ``0xB0`` (``def_y``) is printed with it, and retail's offset
stays unattributed unless retail's DWARF homes it.  A signature two slots share is
ambiguous and is not paired at all.

The register tally at the end covers the case this map cannot: a body whose *caller*-saved
colouring moved.  It is printed only when the two bodies are the same code with a
different colouring (few unmasked differences); a structural difference is reported by
the word count instead.

``--search N`` exists for the one experiment that is cheap and occasionally decisive:
permuting the *declarations of the address-taken locals only* (the order is fixed and
enumerated -- rotations first, then transpositions -- never random) and printing the best
``N`` candidates by frame size, then saved-register set, then differing words.  A
candidate is never reported as an improvement unless its **unmasked** differing-word
count is lower than the baseline's: a permutation that changes the code is an artefact,
not a fix, and the gate would refuse the unit anyway.

Usage::

    python3 tools/units/slots.py com_keyboard ComKeyBoardDisp
    python3 tools/units/slots.py dcamera camera_ero --source drafts/dcamera.c
    python3 tools/units/slots.py com_keyboard ComKeyBoardDisp --search 5

``<unit>`` is any spelling :meth:`toolchain.compile.Manifests.tu_named` accepts, and must
be promoted (have a ``tu_builds`` row).  ``--draft PATH`` measures a source that is not
promoted yet with ``--compiler``/``--flags`` (default: the target's recorded pair if the
unit has one); that is how a draft whose residue is this class is compared before anyone
adds a row.  ``--segment`` overrides the split directory for a function outside ``main``.

Exit codes: 0 the map was printed, 2 the inputs are missing (no split, no DWARF, no
``tu_builds`` row and no ``--draft``), 1 the compile failed, 3 the search ran and no
permutation improved the body.
"""

from __future__ import annotations

import argparse
import dataclasses
import pathlib
import re
import struct
import sys
import tempfile
from typing import NamedTuple

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from config import targets  # noqa: E402
from oracle import dwarf1  # noqa: E402
from toolchain import compile as cc, debug_set, fetch, probe  # noqa: E402
from units import measure  # noqa: E402

#: What the generated split tree is, for the refusal that names the command.
BUILD = "./ddr build"

#: The default split directory: the main image's segment name.
SEGMENT = "main"

#: Instruction mnemonics, by what they do to memory.  A store saves a register; a load
#: restores it.
STORES = frozenset(("sb", "sh", "sw", "swl", "swr", "sd", "sq", "sdl", "sdr", "sc", "scd",
                    "swc1", "sdc1"))
LOADS = frozenset(("lb", "lh", "lw", "lwl", "lwr", "lbu", "lhu", "lwu", "ldl", "ldr", "lq",
                   "ll", "lld", "ld", "lwc1", "ldc1"))

#: GPR numbers the ABI makes callee-saved: ``$s0``..``$s7``, ``$fp`` ($s8) and ``$ra``.
GPR_SAVED = frozenset(range(16, 24)) | {30, 31}

#: Floating-point numbers ``$f20``..``$f31``: the ABI's callee-saved bank.  Not only the
#: even ones -- this target's retail saves ``$f21`` (``camera_ero``), so the range is what
#: the compiler uses, not the pairing rule.
FP_SAVED = frozenset(range(20, 32))

#: The mnemonics that move a floating-point register to or from memory: their register
#: field is ``ft``, and the number is an ``$fN`` even where it collides with a GPR's.
FP_MNEMONICS = frozenset(("swc1", "sdc1", "lwc1", "ldc1"))

#: The stack pointer, as an instruction field names it.
SP = 29

#: A prologue may open with constant setup for a wide store; these are the shapes MWCC
#: emits there and nothing else.
PROLOGUE_SETUP = frozenset(("ori", "lui", "mtc1", "mfc1", "addu", "daddu", "move",
                            "dsll", "dsll32", "dsrl", "dsrl32", "movz", "movn"))

#: Spellings a generated split uses for one encoding: the assembler's pseudo-instructions
#: around the real opcode.  Only what the splits in this tree actually write.
ALIASES = {"bnez": "bne", "beqz": "beq", "b": "beq", "nop": "sll", "negu": "subu",
           "negu": "subu", "move": "daddu", "li": "addiu", "not": "nor"}

#: The ``nonmatching NAME, 0xSIZE`` line: the function's own extent, past which the split
#: carries link padding.
EXTENT = re.compile(r"^\s*nonmatching\s+(?P<name>\S+),\s+0x(?P<size>[0-9A-Fa-f]+)\s*$")

#: One ``/* VA VADDR WORD */ mnemonic operands`` line of a generated split.
SPLIT_LINE = re.compile(
    r"/\*\s*(?P<va>[0-9A-Fa-f]+)\s+(?P<vaddr>[0-9A-Fa-f]+)\s+(?P<word>[0-9A-Fa-f]{8})\s*\*/"
    r"\s*(?P<mnemonic>\S+)\s*(?P<operands>.*)")

#: The two DWARF tags this tool reads: a variable that lives in the frame, and a member
#: of a structure (its byte offset is where the member starts).
LOCAL_VARIABLE = 0x000C
MEMBER = 0x000D

#: A DWARF home location: ``sp+0x1A0`` is the frame; ``$s4`` is a register.
_FRAME_HOME = re.compile(r"^(?:sp|\$sp|\$29)\+(0x[0-9A-Fa-f]+|[0-9]+)$")
_REGISTER_HOME = re.compile(r"^\$(?:fp|ra|[satvafk][0-9]|f[0-9]+)$")

#: One declaration statement: the only lines ``--search`` permutes.
_DECLARATION = re.compile(r"^(?P<indent>\s+)(?P<type>[A-Za-z_][\w\s*]*?)\s+"
                          r"(?P<name>[A-Za-z_]\w*)\s*(?P<array>(?:\[[^\]]*\])*)\s*;\s*$")

#: How many candidates ``--search`` will compile, and how many locals it will permute.
#: Rotations plus transpositions is ``m + m(m-1)/2``, so ten locals already means 56
#: compiles: the bound is what keeps a stray call from measuring for an hour.
MAX_LOCALS = 10
MAX_CANDIDATES = 96


def _display(path) -> str:
    """A path as a reader types it: repo-relative when it is inside the repository."""
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


class Missing(Exception):
    """Input the map needs is absent; the message names how to make it."""


class Refused(Exception):
    """The request cannot be answered as asked; the message says what would work."""


# ---------------------------------------------------------------------------
# reading one body's instructions
# ---------------------------------------------------------------------------


def split_words(text: str) -> list:
    """The words of a generated split, in order, checked against the comments.

    The word column is the evidence; the mnemonic next to it is what a reader sees.  A line
    whose two spellings disagree is refused, because then neither side of this report can be
    trusted.
    """
    words = []
    extent = None
    for number, line in enumerate(text.splitlines(), 1):
        header = EXTENT.search(line)
        if header is not None:
            extent = int(header.group("size"), 16)
            continue
        match = SPLIT_LINE.search(line)
        if match is None:
            continue
        # The split prints the instruction's four bytes in memory order, so the hex column
        # is little-endian even though address and value read big-endian above it.
        word = int.from_bytes(bytes.fromhex(match.group("word")), "little")
        decoded = measure.decode(word)
        written = match.group("mnemonic")
        if not decoded.mnemonic.startswith(".word") and decoded.mnemonic not in (
                written, ALIASES.get(written)):
            raise Missing(f"{number}: the comment says {written} but the word "
                          f"0x{word:08X} decodes as {decoded.text}; the split is stale "
                          f"(run {BUILD})")
        words.append(word)
    if extent is not None:
        # The split carries the padding after the function's own extent; it is not the
        # function, and a word count has to be retail's.
        words = words[:extent // 4]
    return words


def split_path(function: str, segment: str = SEGMENT) -> pathlib.Path:
    """Where the generated tree keeps ``function``'s split."""
    return REPO_ROOT / "asm" / "nonmatchings" / segment / f"{function}.s"


def words_of(data: bytes) -> list:
    """The whole words of a body's bytes (a partial trailing word is not an instruction)."""
    return [struct.unpack_from("<I", data, at)[0]
            for at in range(0, len(data) - len(data) % 4, 4)]


# ---------------------------------------------------------------------------
# the anatomy of one body
# ---------------------------------------------------------------------------


class Saved(NamedTuple):
    """One saved register: where the prologue stores it, or where the epilogue loads it."""

    offset: int
    register: str          # "$s4", "$f20"
    floating: bool
    mnemonic: str


class Slot(NamedTuple):
    """One stack slot and how the body uses it.

    ``kind`` is ``"saved"`` (a callee-saved register's home), ``"address"`` (a local's
    address, materialised with ``addiu``) or ``"value"`` (a local read or written in
    place).  ``registers`` are the registers the body uses with it: the one holding the
    address for an ``"address"`` slot, the readers and writers for a ``"value"`` slot.
    """

    offset: int
    kind: str
    registers: tuple


@dataclasses.dataclass(frozen=True)
class Anatomy:
    """One body's frame, saved registers, and stack slots -- the shape of its prologue."""

    name: str
    words: tuple
    frame: int
    saved: tuple            # (Saved, ...) in prologue store order
    restored: tuple         # (Saved, ...) in epilogue load order
    slots: tuple            # (Slot, ...) ascending by offset
    accesses: tuple = ()    # ((offset, mnemonic, register), ...) for every value access

    def signature(self, offset: int) -> tuple:
        """The multiset of accesses to ``offset``: what identifies a slot without its
        number.  Sorting is what makes the signature independent of the schedule, which
        this target's bodies differ in."""
        return tuple(sorted((mnemonic, register)
                            for at, mnemonic, register in self.accesses if at == offset))

    @property
    def saved_gpr(self) -> tuple:
        return tuple(s for s in self.saved if not s.floating)

    @property
    def saved_fp(self) -> tuple:
        return tuple(s for s in self.saved if s.floating)

    @property
    def registers(self) -> tuple:
        """Every callee-saved register the prologue stores, GPR and FP, in store order."""
        return tuple(s.register for s in self.saved)

    def slot(self, offset: int):
        return next((s for s in self.slots if s.offset == offset), None)


def _field(instruction, name: str):
    """One decoded field's value, or ``None`` when the instruction has no such field."""
    return next((field.value for field in instruction.fields if field.name == name), None)


def _signed(value):
    """A 16-bit immediate as MIPS means it: the decoder keeps the unsigned half-word."""
    if value is None:
        return None
    return value - 0x10000 if value & 0x8000 else value


def _signed_field(instruction, name: str):
    """One immediate field, sign-extended."""
    return _signed(_field(instruction, name))


def _register(number):
    """``number`` as a register name, or ``None`` for a field that is not one."""
    return measure.REGISTERS[number] if number is not None and 0 <= number < 32 else None


def _is_sp_relative(instruction) -> bool:
    return _field(instruction, "base") == SP


def anatomy(name: str, words) -> Anatomy:
    """Read one body's prologue, epilogue and slot table off its instructions."""
    decoded = [measure.decode(word) for word in words]
    frame = 0
    if decoded:
        first = decoded[0]
        imm = _signed_field(first, "imm")
        if (first.mnemonic == "addiu" and _field(first, "rt") == SP
                and _field(first, "rs") == SP and imm is not None and imm < 0):
            frame = -imm

    saved = _saves(decoded[:32])
    restored = _saves(list(reversed(decoded[-24:])))
    restored.reverse()

    saved_offsets = {entry.offset: entry for entry in saved}
    addresses, values, accesses = {}, {}, []
    for instruction in decoded:
        if instruction.mnemonic == "addiu" and _field(instruction, "rs") == SP:
            target, offset = _field(instruction, "rt"), _signed_field(instruction, "imm")
            if target is not None and target != SP and offset is not None and offset >= 0:
                addresses.setdefault(offset, []).append(_register(target))
        elif instruction.mnemonic == "daddu" and _field(instruction, "rs") == SP \
                and _field(instruction, "rt") == 0:
            target = _field(instruction, "rd")
            if target is not None:
                addresses.setdefault(0, []).append(_register(target))
        elif _is_sp_relative(instruction) and (instruction.mnemonic in STORES
                                               or instruction.mnemonic in LOADS):
            offset = _signed_field(instruction, "offset")
            register = _field(instruction, "rt")
            if register is None:
                register = _field(instruction, "ft")
            if offset is None or offset < 0 or offset in saved_offsets:
                continue
            values.setdefault(offset, []).append(_register(register))
            accesses.append((offset, instruction.mnemonic, _register(register)))

    slots = [Slot(offset, "saved", (entry.register,))
             for offset, entry in sorted(saved_offsets.items())]
    for offset in sorted(set(addresses) | set(values)):
        if offset in saved_offsets:
            continue
        if offset in addresses:
            slots.append(Slot(offset, "address", _unique(addresses[offset])))
        else:
            slots.append(Slot(offset, "value", _unique(values[offset])))
    slots.sort(key=lambda slot: (slot.offset, slot.kind))
    return Anatomy(name, tuple(words), frame, tuple(saved), tuple(restored), tuple(slots),
                   tuple(accesses))


def _saves(instructions) -> list:
    """The saved registers a run of instructions stores (or, reversed, restores).

    ``sq $30,0x80($sp)`` saves the GPR ``$fp``; ``sdc1 $f30`` saves the FP register
    ``$f30``.  The encoding puts both numbers in the same field, so the *mnemonic* decides
    which class was saved.  The run ends at the first instruction that is not part of a
    prologue or an epilogue, which is what keeps a body's own ``sq`` onto a saved
    register's contents out of the map.
    """
    out = []
    for instruction in instructions:
        floating = instruction.mnemonic in FP_MNEMONICS
        if (instruction.mnemonic in STORES or instruction.mnemonic in LOADS) \
                and _is_sp_relative(instruction):
            register = _field(instruction, "ft" if floating else "rt")
            allowed = FP_SAVED if floating else GPR_SAVED
            if register is None or register not in allowed:
                break
            name = f"$f{register}" if floating else measure.REGISTERS[register]
            out.append(Saved(_signed_field(instruction, "offset"), name, floating,
                             instruction.mnemonic))
        elif (instruction.mnemonic in PROLOGUE_SETUP or _is_nop(instruction)
              or instruction.mnemonic in ("jr", "jalr")
              or (instruction.mnemonic == "addiu"
                  and _field(instruction, "rs") in (SP, 0)
                  and _field(instruction, "rt") != 0)):
            # A prologue materialises constants (``addiu $3,$zero,1``) between its stores;
            # skipping one is not skipping work, because the run still ends at the first
            # instruction that reads a body pointer or branch.
            continue
        else:
            break
    return out


def _is_nop(instruction) -> bool:
    """``nop`` is an all-zero ``sll``; the split spells it ``nop`` and so does a reader."""
    return instruction.mnemonic == "nop" or (
        instruction.mnemonic == "sll"
        and _field(instruction, "sa") == 0
        and not _field(instruction, "rd") and not _field(instruction, "rt"))


def _unique(registers) -> tuple:
    """The registers in first-use order, without repeats or ``None``."""
    return tuple(dict.fromkeys(r for r in registers if r is not None))


# ---------------------------------------------------------------------------
# the names and sizes: the DWARF each side carries
# ---------------------------------------------------------------------------


class Local(NamedTuple):
    """One local variable that lives in the frame, and the members of its type."""

    name: str
    offset: int
    size: int | None
    members: tuple          # ((name, offset, size|None), ...)


class Symbols:
    """One body's frame locals, and the name a stack offset carries in that body.

    The mapping is this side's own DWARF record: a local whose home is ``sp+0xOFF``.  A
    register-homed local is *not* here -- MWCC writes one location per variable, and for a
    variable the allocator kept in a register that location is a hint, not a slot.
    """

    def __init__(self, locals_=()):
        self.locals = tuple(sorted(locals_, key=lambda local: (local.offset, local.name)))

    def exact(self, offset: int):
        return next((local for local in self.locals if local.offset == offset), None)

    def name(self, offset: int, address: bool = False) -> tuple:
        """``(name, size)`` for ``offset``, or ``(None, None)`` when nothing homes there."""
        prefix = "&" if address else ""
        local = self.exact(offset)
        if local is not None:
            return prefix + local.name, local.size
        best = None
        for local in self.locals:
            delta = offset - local.offset
            if local.size is None or not 0 < delta < local.size:
                continue
            for member_name, member_offset, member_size in local.members:
                if member_offset == delta:
                    return prefix + local.name + "." + member_name, member_size
            if best is None or local.offset > best.offset:
                best = Local(local.name, local.offset, local.size, local.members)
                best_delta = delta
        if best is not None:
            return prefix + best.name + f"+0x{best_delta:X}", best.size
        return None, None

    def label(self, offset: int, address: bool = False, size: bool = True) -> str:
        """How a reader sees one slot: ``&sp.flg``, ``def_y``, or ``0xOFF (unattributed)``."""
        name, width = self.name(offset, address)
        if name is None:
            return f"0x{offset:X} (unattributed)"
        if size and width:
            return f"{name} (0x{width:X})"
        return name

def _location_offset(home) -> int | None:
    """The stack offset a DWARF location text homes a variable at, or ``None``."""
    if not isinstance(home, str):
        return None
    match = _FRAME_HOME.match(home.strip())
    if match is None:
        return None
    return int(match.group(1), 0)


def _size_of(die, by_offset) -> int | None:
    """The size the DWARF gives a type DIE, best effort (``None`` when it gives none)."""
    if die is None:
        return None
    size = die.attrs.get(dwarf1.AT_byte_size)
    if isinstance(size, int):
        return size
    fund = die.attrs.get(dwarf1.AT_fund_type)
    if isinstance(fund, int):
        entry = dwarf1.FT.get(fund)
        return entry[1] if entry else None
    for code in (dwarf1.AT_user_def_type, getattr(dwarf1, "AT_mod_u_d_type", 0x0008)):
        reference = die.attrs.get(code)
        if isinstance(reference, int) and reference in by_offset:
            return _size_of(by_offset[reference], by_offset)
    return None


def _members(die, by_offset) -> tuple:
    """The direct members of a structure type DIE, as ``(name, offset, size)``."""
    out = []
    if die is None:
        return ()
    for child in die.children:
        if child.tag != MEMBER:
            continue
        offset = dwarf1.member_offset(child)
        if offset is None:
            continue
        reference = child.attrs.get(dwarf1.AT_user_def_type)
        target = by_offset.get(reference) if isinstance(reference, int) else None
        fund = child.attrs.get(dwarf1.AT_fund_type)
        if target is None and isinstance(fund, int):
            target = dwarf1.Die(-1, dwarf1.AT_fund_type, {dwarf1.AT_fund_type: fund})
        out.append((child.name, offset, _size_of(target, by_offset)))
    return tuple(out)


def symbols_from_dies(dies, by_offset) -> Symbols:
    """``Symbols`` from one function's DIE sequence (as :func:`debug_set.parse` returns it)."""
    locals_ = []
    for die in dies:
        if die.tag != LOCAL_VARIABLE:
            continue
        offset = _location_offset(dwarf1.loc_str(die.attrs.get(dwarf1.AT_location, b"")))
        if offset is None:
            continue
        reference = die.attrs.get(dwarf1.AT_user_def_type)
        target = by_offset.get(reference) if isinstance(reference, int) else None
        size = _size_of_die(die, target, by_offset)
        locals_.append(Local(die.name, offset, size, _members(target, by_offset)))
    return Symbols(locals_)


def _size_of_die(die, target, by_offset) -> int | None:
    """A variable's own type first, then its fundamental type."""
    if target is not None:
        size = _size_of(target, by_offset)
        if size is not None:
            return size
    return _size_of(die, by_offset)


def retail_function(target, function: str):
    """``(die, image)``: retail's DWARF record for one function, and the image it is in.

    The pinned ELF's ``.debug`` is retail's own, so this answers for a unit that has never
    been compiled in this tree -- including the name its DWARF spells the translation unit
    with, which is what a draft has to stage under.
    """
    image = dwarf1.Dwarf(target.elf)
    found = [die for die in image.dies.values()
             if die.tag in dwarf1.FUNCTIONS and die.name == function]
    if not found:
        raise Missing(f"{_display(target.elf)} records no function {function!r} in its "
                      f"DWARF; the name has to be the one the retail binary was compiled "
                      f"with")
    if len(found) > 1:
        raise Refused(f"{_display(target.elf)} records {len(found)} functions named "
                      f"{function!r}; a function name is unique in this image")
    return found[0], image


def retail_dies(target, function: str):
    """``(dies, by_offset)``: retail's DWARF records for one function."""
    die, image = retail_function(target, function)
    dies = [die, *die.children]

    def walk(node):
        for child in node.children:
            dies.append(child)
            walk(child)

    walk(die)
    return dies, image.dies


def object_dies(mw, function: str):
    """``(dies, by_offset)``: our object's DWARF records for one function.

    Metrowerks emits one ``.debug`` group per function plus the unit's own; a type
    reference in the function's chunk is the offset of the type in the unit's chunk, so
    both are parsed and the unit's records answer the references.
    """
    unit = debug_set.parse(mw.data(mw.section_named(".debug")))
    by_offset = {die.offset: die for die in unit}
    chunk = mw.data(mw.section_of_symbol(f".debug_{function}"))
    return debug_set.parse(chunk), by_offset


# ---------------------------------------------------------------------------
# the compile: the same path measure.py takes
# ---------------------------------------------------------------------------


@dataclasses.dataclass(frozen=True)
class Compiled:
    """Our object and one body of it, as the split and the DWARF need them."""

    object: object            # toolchain.compile.MWObject
    section: int
    body: bytes


def require_promoted(tu, target):
    """The unit's recorded pair, or the refusal that names the tool that records one."""
    pair = target.build_pair(tu.file)
    if pair is None:
        raise Missing(
            f"{tu.file} has no row in {target.name}'s tu_builds: there is no recorded "
            f"pair to compile with. Measure one (python3 tools/toolchain/select_build.py "
            f"--tu {tu.file}) or pass --draft with --compiler/--flags for a source that is "
            f"not promoted yet")
    return pair


def compile_unit(tu, pair, target, manifests, source: bytes, scratch=None) -> Compiled:
    """Compile ``source`` as ``tu``'s unit and hand back the object, unmasked.

    The steps are :func:`units.measure.compile_bodies`'s, so a slot report and a word count
    are about the same object: the staging path (retail's DWARF path length), the recorded
    flags plus the target's includes, and the same compiler build.
    """
    compiler_version, flags_text = pair
    wibo = fetch.wibo()
    staged = cc.staged_path(tu, wibo)
    staged.parent.mkdir(parents=True, exist_ok=True)
    staged.write_bytes(source)
    directory = pathlib.Path(scratch or tempfile.mkdtemp(prefix="ddr-slots-"))
    directory.mkdir(parents=True, exist_ok=True)
    obj = directory / "unit.mw.o"
    probe.compile(staged, obj, fetch.compiler(compiler_version), wibo,
                  [*flags_text.split(), *cc.include_flags(target)])
    return obj


def body_of(mw, function: str) -> Compiled:
    """``function``'s own ``.text`` section from the object, with its relocations."""
    section = mw.function_section(function)
    return Compiled(mw, section, mw.data(section))


def _retail_body(target, function: str, segment: str) -> bytes:
    """Retail's instructions for ``function``, from the generated split."""
    path = split_path(function, segment)
    if not path.is_file():
        raise Missing(f"{_display(path)} does not exist: the split tree is generated, not "
                      f"committed; run {BUILD}")
    words = split_words(path.read_text())
    if not words:
        raise Missing(f"{_display(path)} has no instruction lines; run {BUILD}")
    return b"".join(struct.pack("<I", word) for word in words)


# ---------------------------------------------------------------------------
# the report
# ---------------------------------------------------------------------------


def _saved_line(entries) -> str:
    return ", ".join(f"{entry.register} 0x{entry.offset:X}" for entry in entries) or "-"


def _slot_line(slot, symbols: Symbols) -> str:
    if slot.kind == "saved":
        return f"    0x{slot.offset:<4X} saved     {slot.registers[0]}"
    address = slot.kind == "address"
    label = symbols.label(slot.offset, address)
    registers = ", ".join(slot.registers) if slot.registers else "-"
    role = "address" if address else "value"
    return f"    0x{slot.offset:<4X} {role:<9} {label:<28} {registers}"


def render_anatomy(anatomy_: Anatomy, symbols: Symbols, heading: str) -> list:
    """One side's frame, saved registers and slots, the way a prologue reads."""
    lines = [f"{heading}: {len(anatomy_.words)} words, frame 0x{anatomy_.frame:X}"]
    lines.append(f"  saved GPR (prologue):  {_saved_line(anatomy_.saved_gpr)}")
    lines.append(f"  saved FP  (prologue):  {_saved_line(anatomy_.saved_fp)}")
    lines.append(f"  restored  (epilogue):  {_saved_line(anatomy_.restored)}")
    if not anatomy_.slots:
        lines.append("  stack slots: none")
        return lines
    lines.append("  stack slots:")
    for slot in anatomy_.slots:
        lines.append(_slot_line(slot, symbols))
    return lines


def _registers_of(anatomy_: Anatomy, name: str, symbols: Symbols, address: bool) -> tuple:
    """The registers that hold ``name``'s address (or value) in this body."""
    out = []
    for slot in anatomy_.slots:
        if slot.kind == "saved":
            continue
        if (slot.kind == "address") != address:
            continue
        resolved, _ = symbols.name(slot.offset, address)
        if resolved == name:
            out.extend(slot.registers)
    return _unique(out)


def _short(register: str) -> str:
    return register.lstrip("$")


def _exchange_lines(retail: Anatomy, ours: Anatomy, retail_symbols: Symbols,
                   ours_symbols: Symbols) -> list:
    """Each symbol whose holding register differs, named the way a reader says it."""
    lines = []
    names = {name for name in
             (retail_symbols.name(slot.offset, slot.kind == "address")[0]
              for slot in retail.slots if slot.kind != "saved") if name}
    names |= {name for name in
              (ours_symbols.name(slot.offset, slot.kind == "address")[0]
               for slot in ours.slots if slot.kind != "saved") if name}
    for name in sorted(names):
        address = name.startswith("&")
        mine = _registers_of(retail, name, retail_symbols, address)
        theirs = _registers_of(ours, name, ours_symbols, address)
        if not mine or not theirs:
            continue
        if tuple(_short(r) for r in mine) == tuple(_short(r) for r in theirs):
            continue
        lines.append(f"  retail {name} -> {', '.join(_short(r) for r in mine)}"
                     f", ours -> {', '.join(_short(r) for r in theirs)}")
    return lines


def _slot_moves(retail: Anatomy, ours: Anatomy) -> list:
    """``[(retail offset, ours offset, accesses)]``: slots the compiler put elsewhere.

    A slot is identified by the multiset of instructions that touch it -- the mnemonic and
    the register for every access -- which the schedule does not change.  Two slots are the
    same slot moved when those multisets are equal and *unique* on both sides; a signature
    that two slots share is ambiguous and is left unreported rather than guessed at.
    """
    def signatures(anatomy_: Anatomy) -> dict:
        out = {}
        for slot in anatomy_.slots:
            if slot.kind == "saved":
                continue
            out.setdefault(anatomy_.signature(slot.offset), []).append(slot.offset)
        return out

    mine, theirs = signatures(retail), signatures(ours)
    moves = []
    for signature, offsets in mine.items():
        candidates = theirs.get(signature)
        if not signature or not candidates or len(offsets) != 1 or len(candidates) != 1:
            continue
        if offsets[0] != candidates[0]:
            moves.append((offsets[0], candidates[0], len(signature)))
    return sorted(moves)


def _move_lines(retail: Anatomy, ours: Anatomy, retail_symbols: Symbols,
                ours_symbols: Symbols) -> list:
    """The slot moves, with our DWARF's name for a slot only where it has one."""
    lines = []
    pairs = _slot_moves(retail, ours)
    for one, two, count in pairs:
        retail_name, _ = retail_symbols.name(one, False)
        ours_name, ours_size = ours_symbols.name(two, False)
        retail_text = f"retail 0x{one:X} ({retail_name})" if retail_name else \
            f"retail 0x{one:X} (unattributed)"
        ours_text = f"ours 0x{two:X} ({ours_name}"
        if ours_name is None:
            ours_text = f"ours 0x{two:X} (unattributed)"
        else:
            ours_text += f", 0x{ours_size:X} bytes)" if ours_size else ")"
        lines.append(f"  {retail_text} -> {ours_text}  "
                     f"[{count} matching access{'es' if count != 1 else ''}]")
    exchanged = {(one, two) for one, two, _ in pairs}
    for one, two, _ in pairs:
        if (two, one) in exchanged and one < two:
            lines.append(f"  the two slots are exchanged: retail 0x{one:X} <-> ours "
                         f"0x{two:X}")
    return lines


#: Above this many unmasked differences the two bodies are not the same code with a
#: different colouring, and a register tally at aligned sites would be noise, not evidence.
COLOURING_LIMIT = 64

#: How many register pairs the tally prints before it stops: enough to name an exchange,
#: not enough to bury the named slots above it.
COLOUR_SHOWN = 8


def colour_pairs(retail: Anatomy, ours: Anatomy) -> list:
    """``[((retail register, ours register), field, sites)]`` at aligned instruction sites.

    Two instructions that agree in mnemonic but name a different register in one field are
    the colouring question in its smallest form.  The tally is evidence only when the bodies
    are the same code, which is the caller's :data:`COLOURING_LIMIT` check.
    """
    tally = {}
    for left, right in zip(retail.words, ours.words):
        one, two = measure.decode(left), measure.decode(right)
        if one.mnemonic != two.mnemonic or one.mnemonic.startswith(".word"):
            continue
        for name in ("rs", "rt", "rd", "ft"):
            mine, theirs = _field(one, name), _field(two, name)
            if mine is None or theirs is None or mine == theirs:
                continue
            if mine == SP or theirs == SP:
                continue
            key = (measure.REGISTERS[mine], measure.REGISTERS[theirs], name)
            tally[key] = tally.get(key, 0) + 1
    return sorted(((pair, field, count) for (one, two, field), count in
                   ((key, count) for key, count in tally.items())
                   for pair in [(one, two)]),
                  key=lambda entry: (-entry[2], entry[0], entry[1]))


def _colour_lines(retail: Anatomy, ours: Anatomy, named: set) -> list:
    """The register tally, for a body that is the same code with a different colouring."""
    lines = []
    shown = 0
    for (one, two), field, count in colour_pairs(retail, ours):
        if {_short(one), _short(two)} & named:
            continue
        lines.append(f"  retail {one} -> ours {two} ({field}, "
                     f"{count} aligned site{'s' if count != 1 else ''})")
        shown += 1
        if shown == COLOUR_SHOWN:
            break
    return lines


def _frame_line(retail: Anatomy, ours: Anatomy) -> list:
    if retail.frame == ours.frame:
        return []
    return [f"  frame: retail 0x{retail.frame:X}, ours 0x{ours.frame:X}"
            f" ({'+' if ours.frame > retail.frame else '-'}0x"
            f"{abs(ours.frame - retail.frame):X})"]


def _saved_set_line(retail: Anatomy, ours: Anatomy) -> list:
    mine = set(retail.registers)
    theirs = set(ours.registers)
    if mine == theirs:
        return []
    extra = ", ".join(sorted(theirs - mine)) or "-"
    missing = ", ".join(sorted(mine - theirs)) or "-"
    return [f"  saved set: ours only {extra}; retail only {missing}"]


def diff_lines(retail: Anatomy, ours: Anatomy, retail_symbols: Symbols,
               ours_symbols: Symbols, raw: int | None = None) -> list:
    """The diff section: frame, saved set, slot moves, named exchanges, colouring.

    The last group needs the two bodies to be the same code: ``raw`` is their unmasked
    differing-word count, and past :data:`COLOURING_LIMIT` the tally is not printed at all
    -- a structural difference is reported by the word count, not guessed at here.
    """
    lines = _frame_line(retail, ours)
    lines += _saved_set_line(retail, ours)
    lines += _move_lines(retail, ours, retail_symbols, ours_symbols)
    exchanges = _exchange_lines(retail, ours, retail_symbols, ours_symbols)
    lines += exchanges
    if raw is not None and raw <= COLOURING_LIMIT:
        named = {_short(token)
                 for line in exchanges
                 for token in re.findall(r"-> (\$?[a-z0-9]+)", line)}
        lines += _colour_lines(retail, ours, named)
    return lines


def render(unit: str, function: str, retail: Anatomy, ours: Anatomy,
           retail_symbols: Symbols, ours_symbols: Symbols, body=None) -> str:
    """The whole report: retail's side, ours, and the diff between them."""
    lines = [f"{unit} {function}"]
    lines += render_anatomy(retail, retail_symbols, "retail")
    lines += [""]
    lines += render_anatomy(ours, ours_symbols, "ours")
    lines.append("")
    if body is not None:
        lines.append(f"words: retail {body.retail_words}, ours {body.ours_words}; "
                     f"differing {body.differing} (masked), "
                     f"{raw_differing(body)} (unmasked)"
                     + (f"; {body.length_note}" if body.length_note else ""))
    diff = diff_lines(retail, ours, retail_symbols, ours_symbols,
                      None if body is None else raw_differing(body))
    lines.append("diff")
    lines += diff if diff else ["  (none: frame, saved set and every named slot agree)"]
    return "\n".join(lines) + "\n"


def raw_differing(body) -> int:
    """Differing words with *no* relocation masking: what a candidate may not trade away."""
    span = min(len(body.ours), len(body.retail))
    return sum(1 for at in range(0, span - span % 4, 4)
               if body.ours[at:at + 4] != body.retail[at:at + 4])


# ---------------------------------------------------------------------------
# --search: permutations of the address-taken locals' declarations
# ---------------------------------------------------------------------------


def declaration_lines(text: str, names) -> list:
    """``[(line index, name)]`` for the declaration statements of ``names``.

    Only a whole-line declaration of one of ``names`` is a candidate: a statement that
    shares its line with code, or a declaration with an initialiser, is left alone.
    """
    wanted = set(names)
    found = []
    for number, line in enumerate(text.splitlines()):
        match = _DECLARATION.match(line)
        if match is None or match.group("name") not in wanted:
            continue
        found.append((number, match.group("name")))
    return found


def permuted(text: str, order) -> str:
    """``text`` with its declaration statements spelled in ``order``.

    The statements keep their lines; only the texts swap, so the frame's line numbers move
    no more than C's declaration order does.
    """
    lines = text.splitlines()
    slots = declaration_lines(text, order)
    if sorted(name for _, name in slots) != sorted(order):
        raise Refused("the permutation does not name exactly the declaration lines found")
    texts = {name: lines[number] for number, name in slots}
    return "\n".join(_with_lines(lines, [number for number, _ in slots],
                                 [texts[name] for name in order])) + (
        "\n" if text.endswith("\n") else "")


def _with_lines(lines, numbers, replacement) -> list:
    out = list(lines)
    for number, text in zip(numbers, replacement):
        out[number] = text
    return out


def improves(raw: int, base_raw: int) -> bool:
    """Whether a candidate may be called an improvement.

    The masked count is the gate's number, but a permutation that *changes the code* can
    lower it as an artefact.  A lower unmasked count is the evidence that the same code
    now differs in fewer words; without it the candidate is rejected and reported as such.
    """
    return raw < base_raw


def orders(names) -> list:
    """Every candidate order: the source's, then rotations, then transpositions.

    Fixed and enumerated on purpose: a search whose answer changes when it is re-run is not
    evidence.  Rotations first because a rotation is what a different declaration walk
    usually produces; transpositions second because they isolate one exchange.
    """
    names = list(names)
    seen = [tuple(names)]
    for step in range(1, len(names)):
        seen.append(tuple(names[step:] + names[:step]))
    for left in range(len(names)):
        for right in range(left + 1, len(names)):
            swapped = list(names)
            swapped[left], swapped[right] = swapped[right], swapped[left]
            seen.append(tuple(swapped))
    unique = []
    for order in seen:
        if order not in unique:
            unique.append(order)
    return unique[:MAX_CANDIDATES]


@dataclasses.dataclass(frozen=True)
class Candidate:
    """One permutation, measured the way the gate measures."""

    order: tuple
    frame: int
    saved: tuple
    masked: int
    raw: int
    note: str | None = None

    def line(self, index: int, retail: Anatomy) -> str:
        frame = f"0x{self.frame:X}" + ("" if self.frame == retail.frame else " (differs)")
        registers = ""
        mine, theirs = set(self.saved), set(retail.registers)
        if mine == theirs:
            registers = "saved set = retail's"
        elif mine:
            registers = "saved " + ",".join(sorted(mine))
        text = (f"  {index:>2}. {', '.join(self.order):<44} frame {frame:<11} "
                f"{registers:<22} masked {self.masked:>3}  unmasked {self.raw:>3}")
        if self.note:
            text += f"  rejected: {self.note}"
        return text


def _rank(candidate: Candidate, retail: Anatomy) -> tuple:
    """Frame size, then saved-register set, then differing words -- retail's order."""
    return (abs(candidate.frame - retail.frame),
            len(set(candidate.saved) ^ set(retail.registers)),
            candidate.masked,
            candidate.order)


def address_taken(anatomy_: Anatomy, symbols: Symbols) -> tuple:
    """The frame locals whose address the body materialises, in declaration order.

    A local is address-taken when an ``address`` slot falls inside its own bytes: the body
    takes its address, so the allocator's choice for it is a colouring decision rather
    than a spill.
    """
    taken = []
    for local in symbols.locals:
        span = local.size or 4
        for slot in anatomy_.slots:
            if slot.kind != "address":
                continue
            if local.offset <= slot.offset < local.offset + span:
                taken.append(local.name)
                break
    return tuple(taken)


def search(unit: str, function: str, count: int, *, tu, pair, target, manifests,
           source: pathlib.Path, retail: Anatomy, retail_symbols: Symbols,
           base_body, baseline: Anatomy, baseline_symbols: Symbols) -> tuple:
    """Measure every declaration-order candidate and rank the ones that are real."""
    text = source.read_text()
    names = address_taken(baseline, baseline_symbols)
    if not names:
        raise Refused(f"{unit}: no local of {function} has its address materialised, so "
                      f"there is no declaration order to permute")
    if len(names) > MAX_LOCALS:
        raise Refused(f"{unit}: {len(names)} address-taken locals is more than the "
                      f"{MAX_LOCALS} this search will permute; narrow the question")
    slots = declaration_lines(text, names)
    fixed = sorted(set(names) - {name for _, name in slots})
    if len(slots) < 2:
        raise Refused(
            f"{_display(source)}: only {len(slots)} address-taken local of {function} is a "
            f"whole-line declaration, so there is no declaration order to permute"
            + (f" ({', '.join(fixed)} carry an initialiser or share a line)" if fixed else ""))
    if len(slots) > MAX_LOCALS:
        raise Refused(f"{unit}: {len(slots)} permutable address-taken locals is more than "
                      f"the {MAX_LOCALS} this search will permute; narrow the question")
    baseline_order = tuple(name for _, name in slots)
    tried = orders(baseline_order)
    print(f"search: {len(tried)} declaration orders of {len(baseline_order)} address-taken "
          f"locals ({', '.join(baseline_order)}); baseline masked {base_body.differing}, "
          f"unmasked {raw_differing(base_body)}")
    if fixed:
        print(f"  not permutable (declared with an initialiser or not one to a line): "
              f"{', '.join(fixed)}")

    base_raw = raw_differing(base_body)
    candidates = []
    for index, order in enumerate(tried):
        candidate_text = permuted(text, order).encode()
        try:
            obj = compile_unit(tu, pair, target, manifests, candidate_text)
            mw = cc.MWObject(obj, manifests)
            compiled = body_of(mw, function)
            body = measure.Body(function, compiled.body, base_body.retail,
                                base_body.ignored)
        except Exception as error:                              # noqa: BLE001
            candidates.append(Candidate(order, -1, (), 0, 0, f"does not compile ({error})"))
            continue
        words = words_of(compiled.body)
        candidate = anatomy(function, words)
        raw = raw_differing(body)
        note = None
        if order != baseline_order and not improves(raw, base_raw):
            note = (f"unmasked {raw} is not lower than {base_raw}: it alters the code")
        candidates.append(Candidate(order, candidate.frame, candidate.registers,
                                    body.differing, raw, note))

    ranked = sorted(candidates, key=lambda c: _rank(c, retail))
    for index, candidate in enumerate(ranked[:count], 1):
        print(candidate.line(index, retail))
    winners = [c for c in ranked if c.note is None and c.order != baseline_order
               and c.masked < base_body.differing and c.raw < base_raw]
    if not winners:
        print("winner: none -- every permutation is either the baseline or does not lower "
              "the unmasked count")
        return None
    winner = winners[0]
    print(f"winner: {', '.join(winner.order)}  (frame 0x{winner.frame:X}, saved "
          f"{','.join(winner.saved) or '-'}, masked {base_body.differing} -> "
          f"{winner.masked}, unmasked {base_raw} -> {winner.raw})")
    return winner


# ---------------------------------------------------------------------------
# entry point
# ---------------------------------------------------------------------------


def parse_args(argv=None):
    parser = argparse.ArgumentParser(
        description="the callee-saved and stack-slot map of one body, ours against "
                    "retail's")
    parser.add_argument("unit", help="the unit, any spelling `ddr verify --tu` accepts")
    parser.add_argument("fn", help="the function whose prologue to map")
    parser.add_argument("--target", default=None,
                        help="the target name (default: the configured one)")
    parser.add_argument("--segment", default=None,
                        help=f"the split directory (default: the target's own, {SEGMENT!r})")
    parser.add_argument("--draft", default=None, metavar="PATH",
                        help="compile this source instead of a promoted unit's")
    parser.add_argument("--compiler", default=None,
                        help="the compiler build for --draft (default: the recorded pair)")
    parser.add_argument("--flags", default=None,
                        help="the flags for --draft (default: the recorded pair's)")
    parser.add_argument("--search", type=int, default=0, metavar="N",
                        help="try declaration permutations of the address-taken locals and "
                             "print the best N (bounded, deterministic)")
    parser.add_argument("--scratch", default=None,
                        help="where to compile (default: a fresh temporary directory)")
    return parser.parse_args(argv)


def resolve_target(name=None):
    """The target ``--target`` names (a seam the tests use in place of the registry)."""
    return targets.get(name)


def _source_and_pair(args, target, manifests):
    """``(tu, pair, source)``: the recorded pair, or the draft's explicit one."""
    if not args.draft:
        try:
            tu = manifests.tu_named(args.unit)
        except cc.Unusable as error:
            raise Missing(f"{error}; if the source is a draft, pass --draft PATH with "
                          f"--compiler and --flags") from error
        return tu, require_promoted(tu, target), tu.source
    source = pathlib.Path(args.draft)
    if not source.is_file():
        raise Missing(f"{source}: no such source to compile")
    try:
        tu = manifests.tu_named(args.unit)
    except cc.Unusable:
        die, _image = retail_function(target, args.fn)
        tu = _draft_tu(args.unit, source, die.cu.name)
    recorded = target.build_pair(tu.file)
    compiler = args.compiler or (recorded[0] if recorded else None)
    flags = args.flags or (recorded[1] if recorded else None)
    if compiler is None or flags is None:
        raise Missing(f"--draft needs --compiler and --flags when {args.unit} has no "
                      f"recorded pair (its source is not in {target.name}'s tu_builds)")
    return tu, (compiler, flags), source


def _draft_tu(unit_text: str, source: pathlib.Path, retail_name: str):
    """A stand-in ``Tu`` for a source no manifest describes: what staging reads.

    ``retail_name`` is the translation unit's spelling in retail's own DWARF: staging has to
    record a path of that length, and the draft has no manifest row to read it from.
    """

    class DraftTu:
        file = str(source)
        name = retail_name
        functions = ()

        @staticmethod
        def function_named(_name):
            return None

    DraftTu.source = source
    DraftTu.unit = pathlib.PurePosixPath(unit_text).stem
    return DraftTu()


def main(argv=None) -> int:
    args = parse_args(argv)
    try:
        target = resolve_target(args.target)
        manifests = cc.Manifests(target)
        tu, pair, source = _source_and_pair(args, target, manifests)
        segment = args.segment or SEGMENT
        retail_bytes = _retail_body(target, args.fn, segment)
        retail = anatomy(args.fn, words_of(retail_bytes))
        dies, by_offset = retail_dies(target, args.fn)
        retail_symbols = symbols_from_dies(dies, by_offset)

        text = pathlib.Path(source).read_bytes()
        obj = compile_unit(tu, pair, target, manifests, text, args.scratch)
        mw = cc.MWObject(obj, manifests)
        compiled = body_of(mw, args.fn)
        ours = anatomy(args.fn, words_of(compiled.body))
        ours_dies, ours_by_offset = object_dies(mw, args.fn)
        ours_symbols = symbols_from_dies(ours_dies, ours_by_offset)
        body = measure.compare(args.fn, compiled.body, retail_bytes,
                               mw.relocs.get(compiled.section, ()))
        print(render(args.unit, args.fn, retail, ours, retail_symbols, ours_symbols, body),
              end="")
        if args.search > 0:
            winner = search(args.unit, args.fn, args.search, tu=tu, pair=pair,
                            target=target, manifests=manifests,
                            source=pathlib.Path(source), retail=retail,
                            retail_symbols=retail_symbols, base_body=body, baseline=ours,
                            baseline_symbols=ours_symbols)
            if winner is None:
                return 3
        return 0
    except (Missing, Refused, cc.Unusable, probe.ProbeError) as error:
        print(f"slots: {error}", file=sys.stderr)
        return 2 if isinstance(error, (Missing, Refused)) else 1


if __name__ == "__main__":
    sys.exit(main())
