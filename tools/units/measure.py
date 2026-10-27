#!/usr/bin/env python3
"""measure.py -- one line per body: how far our C is from retail's instructions.

Every unit worker used to write this private: a script that compiled the unit with its
recorded pair, put the relocations in, and printed which words of which body differed.
This is that measurement, once, with the answer stated the way the gate states it:

* the compile is the unit's **recorded pair** (:meth:`config.targets.Target.build_pair`),
  never ``fetch.REQUIRED`` -- the same choice ``ninja``'s ``cc`` edge makes;
* the relocations are applied by :func:`toolchain.compile.relocate` over the sections
  :class:`toolchain.compile.MWObject` reads, which is exactly what
  :func:`toolchain.compile.placed_text` does before it compares;
* retail is the pinned ELF's own bytes at each function's ``low_pc``, not a regenerated
  tree, so a stale split cannot move the answer.

**The masking rule.**  A relocation overwrites a field of an instruction, so a difference
confined to one of those fields is not evidence about the C.  Only the bits a relocation
actually writes are ignored, on both sides of the comparison:

===============  ==========================================================
``R_MIPS_26``    the jump target, bits 25..0 of the word
``R_MIPS_32``    the whole word
``R_MIPS_HI16``  the ``lui`` immediate, the low 16 bits
``R_MIPS_LO16``  the ``%lo`` immediate, the low 16 bits
``R_MIPS_GPREL16``  the small-data addend, the low 16 bits
===============  ==========================================================

A body that differs from retail **only** in those fields is therefore ``EXACT`` (0
differing), and the header prints this rule on every run so the number cannot be read as
"byte-identical, relocations included".  Every other differing word is counted.

A body whose **length** differs is not reported as a word count: it prints ``short by N
bytes`` or ``N bytes too large`` in the differing column, because the gate refuses such a
body (:func:`toolchain.compile.placed_text`) and a word count would suggest the size is
already right.

Usage::

    python3 tools/units/measure.py src/sys/sys_demo.c
    python3 tools/units/measure.py title_demo --fn title_movie_init --side
    python3 tools/units/measure.py sys_demo --json

``--fn`` narrows the table to one body; with ``--side`` it prints retail's and our
instructions line by line, marking the register and immediate fields that moved.  ``--json``
is the same measurement for tooling.

Exit codes: 0 the measurement was printed, 2 the unit has no ``tu_builds`` row, its splits
are missing (``./ddr build``), or it does not resolve, 1 the compile itself failed.
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import pathlib
import struct
import sys
import tempfile
from typing import NamedTuple

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from config import targets  # noqa: E402
from toolchain import compile as cc, fetch, probe  # noqa: E402

#: What the generated split tree is, for the refusal that names the command.
BUILD = "./ddr build"

#: The bits each relocation overwrites, by type.  Anything not here is either a no-op
#: (``R_MIPS_NONE``) or a relocation :func:`toolchain.compile.relocate` refuses.
FIELD_MASK = {
    cc.R_MIPS_26: 0x03FFFFFF,          # the jump target, low 26 bits
    cc.R_MIPS_32: 0xFFFFFFFF,          # the whole word
    cc.R_MIPS_HI16: 0x0000FFFF,        # the lui immediate
    cc.R_MIPS_LO16: 0x0000FFFF,        # the %lo immediate
    cc.R_MIPS_GPREL16: 0x0000FFFF,     # the small-data addend
}

#: The rule the header carries, one clause per relocation kind, so the count is unambiguous.
MASKING_NOTE = (
    "masking: a body is EXACT when it differs from retail only in the bits a relocation "
    "writes\n"
    "         (R_MIPS_26 jump target; R_MIPS_32 whole word; R_MIPS_HI16, R_MIPS_LO16 and\n"
    "         R_MIPS_GPREL16 low half); every other differing word is counted.")


def _display(path) -> str:
    """A path as a reader types it: repo-relative when it is inside the repository."""
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


class NotPromoted(Exception):
    """The unit has no measured pair in the target's ``tu_builds``."""


class Missing(Exception):
    """Input the measurement needs is absent; the message names how to make it."""


# ---------------------------------------------------------------------------
# the comparison
# ---------------------------------------------------------------------------


def ignored_fields(relocs) -> tuple:
    """``((offset, mask), ...)``: the fields ``relocs`` makes free, for one body.

    Offsets are the object's own, i.e. relative to the body's first word, and the mask is
    the part of the word the relocation rewrites.  A relocation type with no field in
    :data:`FIELD_MASK` contributes nothing: it either writes nothing or is refused later.
    """
    return tuple((offset, FIELD_MASK[rtype]) for offset, rtype, _symbol in relocs
                 if rtype in FIELD_MASK)


def masked(body: bytes, ignored) -> bytes:
    """``body`` with every field a relocation writes zeroed, on a copy.

    Zeroing *both* sides is what makes the rule symmetric: a field the relocation owns can
    never be evidence, whichever side it came from.
    """
    out = bytearray(body)
    for offset, mask in ignored:
        if offset + 4 > len(out):
            continue      # a relocation outside the body is the object's problem, not ours
        word = struct.unpack_from("<I", out, offset)[0]
        struct.pack_into("<I", out, offset, word & ~mask & 0xFFFFFFFF)
    return bytes(out)


def _common(ours: bytes, retail: bytes) -> int:
    """The whole words both bodies have: a partial trailing word is a length fact, not a count."""
    span = min(len(ours), len(retail))
    return span - span % 4


@dataclasses.dataclass(frozen=True)
class Body:
    """One function's body against retail's bytes at its ``low_pc``.

    ``ours`` is the relocated body the object produced, whatever its length; ``retail`` is
    the pinned image's bytes over the function's DWARF extent, so its length is what the
    gate requires ours to be.  ``differing`` and
    ``first_diff`` are measured over the common span and are always populated (``--json``
    reports them for a wrong-length body too); the text report prints the length phrase
    instead, because the gate refuses such a body before any word count matters.
    """

    name: str
    ours: bytes
    retail: bytes
    ignored: tuple = ()

    @property
    def ours_words(self) -> int:
        return (len(self.ours) + 3) // 4

    @property
    def retail_words(self) -> int:
        return (len(self.retail) + 3) // 4

    @property
    def size_gap(self) -> int:
        """Bytes our body has *more* than retail's (negative: short)."""
        return len(self.ours) - len(self.retail)

    @property
    def length_note(self) -> str | None:
        """``None`` for retail's length, else the phrase the gate uses."""
        gap = self.size_gap
        if gap == 0:
            return None
        return f"short by 0x{-gap:X} bytes" if gap < 0 else f"0x{gap:X} bytes too large"

    def _compared(self) -> tuple:
        return masked(self.ours, self.ignored), masked(self.retail, self.ignored)

    @property
    def differing(self) -> int:
        ours, retail = self._compared()
        return sum(1 for at in range(0, _common(ours, retail), 4)
                   if ours[at:at + 4] != retail[at:at + 4])

    @property
    def first_diff(self) -> int | None:
        ours, retail = self._compared()
        for at in range(0, _common(ours, retail), 4):
            if ours[at:at + 4] != retail[at:at + 4]:
                return at
        return None

    @property
    def exact(self) -> bool:
        """Retail's length and no differing word outside the relocation's own fields."""
        return self.size_gap == 0 and self.differing == 0

    def as_json(self) -> dict:
        return {
            "name": self.name,
            "ours_words": self.ours_words,
            "retail_words": self.retail_words,
            "size_gap": self.size_gap,
            "differing": self.differing,
            "first_diff": self.first_diff,
            "exact": self.exact,
        }


def compare(name: str, ours: bytes, retail: bytes, relocs=()) -> Body:
    """One body's report: ``ours`` relocated, ``retail`` from the image, ``relocs`` its own."""
    return Body(name, ours, retail, ignored_fields(relocs))


def bodies(tu, mw, retail: bytes, gp: int) -> list:
    """Every body of ``tu``, relocated the way ``placed_text`` relocates it.

    The length refusal :func:`toolchain.compile.placed_text` makes is deliberately absent:
    a wrong-length body is what this tool is for, so it is measured and reported rather
    than refused.  Data placement (:func:`toolchain.compile.verify_data`) is not run
    either: the question here is ``.text``, and a datum's refusal would hide every body.
    Everything else -- the section lookup, the resolve callback, ``$gp`` -- is the gate's.
    """
    groups = mw.groups(tu)
    out = []
    for function in tu.functions:
        section = groups[function.name][0]
        relocs = mw.relocs.get(section, ())
        ours = cc.relocate(mw.data(section), relocs,
                           lambda symbol: mw.resolve(tu, symbol),
                           f"{function.name}.text", gp)
        at = function.address - tu.address
        out.append(compare(function.name, ours, retail[at:at + function.size], relocs))
    return out


# ---------------------------------------------------------------------------
# the measurement: the unit's recorded pair, one compile
# ---------------------------------------------------------------------------


@dataclasses.dataclass(frozen=True)
class Measured:
    """What the report prints: the unit, its pair, and one :class:`Body` per function."""

    source: str
    target: str
    compiler: str
    flags: str
    bodies: list

    def as_json(self) -> dict:
        return {
            "unit": self.source,
            "target": self.target,
            "compiler": self.compiler,
            "flags": self.flags,
            "masked_relocations": [cc.RELOC_NAMES[rtype] for rtype in FIELD_MASK],
            "bodies": [body.as_json() for body in self.bodies],
        }


def require_splits(tu, target) -> None:
    """Refuse a unit whose splits are absent: the comparison has no generated tree to read.

    The image is what the numbers come from, but a missing ``asm/nonmatchings`` means the
    build has not run, and every other tool in this directory refuses that state by naming
    the command rather than reporting a body of zero words.
    """
    segment = target.geometry_required().code_segment
    directory = REPO_ROOT / "asm" / "nonmatchings" / segment
    if not directory.is_dir():
        raise Missing(f"{_display(directory)} does not exist: the split tree is generated, "
                      f"not committed; run {BUILD}")
    missing = [f.name for f in tu.functions if not (directory / f"{f.name}.s").is_file()]
    if missing:
        names = ", ".join(missing[:3]) + (", ..." if len(missing) > 3 else "")
        raise Missing(f"{tu.file}: {len(missing)} function split(s) missing under "
                      f"{_display(directory)} ({names}); run {BUILD}")


def compile_bodies(tu, pair, target, manifests, scratch=None) -> list:
    """Compile ``tu`` with ``pair`` and compare each body with the pinned image."""
    compiler_version, flags_text = pair
    flags = flags_text.split()
    compiler_dir = fetch.compiler(compiler_version)
    wibo = fetch.wibo()
    staged = cc.staged_path(tu)
    staged.parent.mkdir(parents=True, exist_ok=True)
    staged.write_bytes(tu.source.read_bytes())
    recorded = cc.recorded_name(staged)
    if len(recorded) != len(tu.name):
        raise cc.Unusable(f"staging {staged} spells {len(recorded)} bytes, retail "
                          f"{len(tu.name)}")
    directory = pathlib.Path(scratch or tempfile.mkdtemp(prefix="ddr-measure-"))
    directory.mkdir(parents=True, exist_ok=True)
    obj = directory / "unit.mw.o"
    probe.compile(staged, obj, compiler_dir, wibo,
                  [*flags, *cc.include_flags(target)])
    mw = cc.MWObject(obj, manifests)
    gp = cc.gp_value(target.elf)
    manifests.prefer_source(tu.file)
    retail = cc.retail_bytes(tu, target.elf)["text"]
    return bodies(tu, mw, retail, gp)


def measure(unit: str, function: str | None = None, target=None, scratch=None) -> Measured:
    """Compile ``unit`` with its recorded pair and measure every body (or ``function``).

    ``unit`` is any spelling :meth:`toolchain.compile.Manifests.tu_named` accepts --
    ``sys_scf``, ``sys_scf.c`` or ``src/sys/sys_scf.c`` -- which is also the spelling
    ``ddr verify --tu`` accepts.
    """
    target = targets.get(target)
    manifests = cc.Manifests(target)
    tu = manifests.tu_named(unit)
    pair = target.build_pair(tu.file)
    if pair is None:
        raise NotPromoted(
            f"{tu.file} has no row in {target.name}'s tu_builds: there is no measured "
            f"compile to compare with. Measure the pair that reproduces it "
            f"(python3 tools/toolchain/select_build.py --tu {tu.file}) and add the row to "
            f"config/targets.py once its .text is retail's")
    require_splits(tu, target)
    if function is not None and tu.function_named(function) is None:
        names = ", ".join(f.name for f in tu.functions)
        raise Missing(f"{tu.file} declares no function {function!r}; it has {names}")
    found = compile_bodies(tu, pair, target, manifests, scratch)
    if function is not None:
        found = [body for body in found if body.name == function]
    return Measured(tu.file, target.name, pair[0], pair[1], found)


# ---------------------------------------------------------------------------
# a readable instruction, for --side
# ---------------------------------------------------------------------------

REGISTERS = (
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra",
)

class Field(NamedTuple):
    """One instruction field, as ``--side`` names it when it moves."""

    name: str        # "rs", "rt", "rd", "imm", "offset", "target", "sa"
    value: int
    text: str        # how the field reads in the instruction


class Instruction(NamedTuple):
    """One decoded word: its text, and the fields a difference can be attributed to."""

    mnemonic: str
    text: str
    fields: tuple


def _reg(number: int, name: str = "rs") -> Field:
    register = REGISTERS[number] if 0 <= number < 32 else f"r{number}"
    return Field(name, number, register)


def _signed(value: int) -> str:
    value &= 0xFFFF
    return f"-0x{0x10000 - value:X}" if value & 0x8000 else f"0x{value:X}"


def _hex(value: int) -> str:
    return f"0x{value & 0xFFFF:X}"


def _instruction(mnemonic: str, operands=(), fields=()) -> Instruction:
    text = mnemonic + (" " + ",".join(operands) if operands else "")
    return Instruction(mnemonic, text, tuple(fields))


def _special(word: int) -> Instruction:
    funct, rd, rt, rs = word & 0x3F, (word >> 11) & 31, (word >> 16) & 31, (word >> 21) & 31
    sa = (word >> 6) & 31
    if funct in (0x00, 0x02, 0x03, 0x38, 0x3A, 0x3B, 0x3C, 0x3E, 0x3F):
        names = {0x00: "sll", 0x02: "srl", 0x03: "sra", 0x38: "dsll",
                 0x3A: "dsrl", 0x3B: "dsra", 0x3C: "dsll32", 0x3E: "dsrl32",
                 0x3F: "dsra32"}
        return _instruction(names[funct],
                            (REGISTERS[rd], REGISTERS[rt], str(sa)),
                            (_reg(rd, "rd"), _reg(rt, "rt"), Field("sa", sa, str(sa))))
    if funct in (0x04, 0x06, 0x07, 0x14, 0x16, 0x17):
        names = {0x04: "sllv", 0x06: "srlv", 0x07: "srav",
                 0x14: "dsllv", 0x16: "dsrlv", 0x17: "dsrav"}
        return _instruction(names[funct], (REGISTERS[rd], REGISTERS[rt], REGISTERS[rs]),
                            (_reg(rd, "rd"), _reg(rt, "rt"), _reg(rs, "rs")))
    if funct == 0x08:
        return _instruction("jr", (REGISTERS[rs],), (_reg(rs, "rs"),))
    if funct == 0x09:
        return _instruction("jalr", (REGISTERS[rd], REGISTERS[rs]),
                            (_reg(rd, "rd"), _reg(rs, "rs")))
    if funct in (0x0A, 0x0B):
        return _instruction("movz" if funct == 0x0A else "movn",
                            (REGISTERS[rd], REGISTERS[rs], REGISTERS[rt]),
                            (_reg(rd, "rd"), _reg(rs, "rs"), _reg(rt, "rt")))
    if funct in (0x0C, 0x0D):
        code = (word >> 6) & 0xFFFFF
        return _instruction("syscall" if funct == 0x0C else "break",
                            (f"0x{code:X}",), (Field("code", code, f"0x{code:X}"),))
    if funct == 0x0F:
        return _instruction("sync", (str(sa),), (Field("stype", sa, str(sa)),))
    if funct in (0x10, 0x12, 0x28):
        names = {0x10: "mfhi", 0x12: "mflo", 0x28: "mfsa"}
        return _instruction(names[funct], (REGISTERS[rd],), (_reg(rd, "rd"),))
    if funct in (0x11, 0x13, 0x29):
        names = {0x11: "mthi", 0x13: "mtlo", 0x29: "mtsa"}
        return _instruction(names[funct], (REGISTERS[rs],), (_reg(rs, "rs"),))
    if funct in (0x18, 0x19, 0x1C, 0x1D):
        names = {0x18: "mult", 0x19: "multu", 0x1C: "dmult", 0x1D: "dmultu"}
        if rd:      # EE's three-operand form, which the split spells out
            return _instruction(names[funct], (REGISTERS[rd], REGISTERS[rs], REGISTERS[rt]),
                                (_reg(rd, "rd"), _reg(rs, "rs"), _reg(rt, "rt")))
        return _instruction(names[funct], (REGISTERS[rs], REGISTERS[rt]),
                            (_reg(rs, "rs"), _reg(rt, "rt")))
    if funct in (0x1A, 0x1B, 0x1E, 0x1F):
        names = {0x1A: "div", 0x1B: "divu", 0x1E: "ddiv", 0x1F: "ddivu"}
        return _instruction(names[funct], (REGISTERS[rs], REGISTERS[rt]),
                            (_reg(rs, "rs"), _reg(rt, "rt")))
    names = {0x20: "add", 0x21: "addu", 0x22: "sub", 0x23: "subu", 0x24: "and",
             0x25: "or", 0x26: "xor", 0x27: "nor", 0x2A: "slt", 0x2B: "sltu",
             0x2C: "dadd", 0x2D: "daddu", 0x2E: "dsub", 0x2F: "dsubu",
             0x30: "tge", 0x31: "tgeu", 0x32: "tlt", 0x33: "tltu", 0x34: "teq",
             0x36: "tne"}
    if funct in names:
        if funct >= 0x30:      # the trap forms take no destination
            return _instruction(names[funct], (REGISTERS[rs], REGISTERS[rt]),
                                (_reg(rs, "rs"), _reg(rt, "rt")))
        return _instruction(names[funct], (REGISTERS[rd], REGISTERS[rs], REGISTERS[rt]),
                            (_reg(rd, "rd"), _reg(rs, "rs"), _reg(rt, "rt")))
    return _unknown(word)


def _regimm(word: int) -> Instruction:
    rt, rs, offset = (word >> 16) & 31, (word >> 21) & 31, word & 0xFFFF
    branches = {0x00: "bltz", 0x01: "bgez", 0x02: "bltzl", 0x03: "bgezl",
                0x10: "bltzal", 0x11: "bgezal", 0x12: "bltzall", 0x13: "bgezall"}
    traps = {0x08: "tgei", 0x09: "tgeiu", 0x0A: "tlti", 0x0B: "tltiu",
             0x0C: "teqi", 0x0E: "tnei", 0x18: "mtsab", 0x19: "mtsah"}
    if rt in branches:
        return _instruction(branches[rt], (REGISTERS[rs], _signed(offset)),
                            (_reg(rs, "rs"), Field("offset", offset, _signed(offset))))
    if rt in traps:
        return _instruction(traps[rt], (REGISTERS[rs], _signed(offset)),
                            (_reg(rs, "rs"), Field("imm", offset, _signed(offset))))
    return _unknown(word)


def _rt_rs_imm(word: int, mnemonic: str, signed: bool = True) -> Instruction:
    rs, rt, imm = (word >> 21) & 31, (word >> 16) & 31, word & 0xFFFF
    text = _signed(imm) if signed else _hex(imm)
    return _instruction(mnemonic, (REGISTERS[rt], REGISTERS[rs], text),
                        (_reg(rt, "rt"), _reg(rs, "rs"), Field("imm", imm, text)))


def _memory(word: int, mnemonic: str, first: str = "rt") -> Instruction:
    rs, rt, offset = (word >> 21) & 31, (word >> 16) & 31, word & 0xFFFF
    field = _reg(rt, first)
    return _instruction(mnemonic,
                        (field.text, f"{_signed(offset)}({REGISTERS[rs]})"),
                        (field, Field("offset", offset, _signed(offset)), _reg(rs, "base")))


_LOADS = {0x20: "lb", 0x21: "lh", 0x22: "lwl", 0x23: "lw", 0x24: "lbu", 0x25: "lhu",
          0x26: "lwr", 0x27: "lwu", 0x1A: "ldl", 0x1B: "ldr", 0x1E: "lq", 0x30: "ll",
          0x34: "lld", 0x37: "ld"}
_STORES = {0x28: "sb", 0x29: "sh", 0x2A: "swl", 0x2B: "sw", 0x2C: "sdl", 0x2D: "sdr",
           0x2E: "swr", 0x1F: "sq", 0x38: "sc", 0x3C: "scd", 0x3F: "sd"}


def _unknown(word: int) -> Instruction:
    return _instruction(f".word 0x{word:08X}")


def decode(word: int) -> Instruction:
    """One MIPS III/EE word as text plus the fields a difference is attributed to.

    The table covers what this target's units emit: the integer core, the branch and jump
    forms, loads/stores (including ``lq``/``sq``), ``SPECIAL2``'s multiply-add family and
    ``COP0``'s ``eret``/TLB forms.  An opcode it does not know prints its word verbatim and
    the word comparison still says it differs -- a decoder gap must never hide a residue.
    """
    opcode = word >> 26
    if opcode == 0x00:
        return _special(word)
    if opcode == 0x01:
        return _regimm(word)
    if opcode in (0x02, 0x03):
        target = word & 0x03FFFFFF
        return _instruction("j" if opcode == 0x02 else "jal", (f"0x{target << 2:X}",),
                            (Field("target", target, f"0x{target << 2:X}"),))
    if opcode in (0x04, 0x05, 0x14, 0x15):
        names = {0x04: "beq", 0x05: "bne", 0x14: "beql", 0x15: "bnel"}
        rs, rt, offset = (word >> 21) & 31, (word >> 16) & 31, word & 0xFFFF
        return _instruction(names[opcode],
                            (REGISTERS[rs], REGISTERS[rt], _signed(offset)),
                            (_reg(rs, "rs"), _reg(rt, "rt"),
                             Field("offset", offset, _signed(offset))))
    if opcode in (0x06, 0x07, 0x16, 0x17):
        names = {0x06: "blez", 0x07: "bgtz", 0x16: "blezl", 0x17: "bgtzl"}
        rs, offset = (word >> 21) & 31, word & 0xFFFF
        return _instruction(names[opcode], (REGISTERS[rs], _signed(offset)),
                            (_reg(rs, "rs"), Field("offset", offset, _signed(offset))))
    if opcode in (0x08, 0x09, 0x0A, 0x0B, 0x18, 0x19):
        names = {0x08: "addi", 0x09: "addiu", 0x0A: "slti", 0x0B: "sltiu",
                 0x18: "daddi", 0x19: "daddiu"}
        return _rt_rs_imm(word, names[opcode])
    if opcode in (0x0C, 0x0D, 0x0E):
        names = {0x0C: "andi", 0x0D: "ori", 0x0E: "xori"}
        return _rt_rs_imm(word, names[opcode], signed=False)
    if opcode == 0x0F:
        rt, imm = (word >> 16) & 31, word & 0xFFFF
        return _instruction("lui", (REGISTERS[rt], _hex(imm)),
                            (_reg(rt, "rt"), Field("imm", imm, _hex(imm))))
    if opcode in _LOADS:
        return _memory(word, _LOADS[opcode])
    if opcode in _STORES:
        return _memory(word, _STORES[opcode])
    if opcode in (0x31, 0x35):
        return _memory(word, "lwc1" if opcode == 0x31 else "ldc1", first="ft")
    if opcode in (0x39, 0x3D):
        return _memory(word, "swc1" if opcode == 0x39 else "sdc1", first="ft")
    if opcode == 0x10:
        return _cop0(word)
    if opcode == 0x1C:
        return _special2(word)
    return _unknown(word)


def _cop0(word: int) -> Instruction:
    rs, rt, rd = (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    if rs in (0x00, 0x04):
        names = {0x00: "mfc0", 0x04: "mtc0"}
        return _instruction(names[rs], (REGISTERS[rt], REGISTERS[rd]),
                            (_reg(rt, "rt"), _reg(rd, "rd")))
    if rs == 0x10:
        names = {0x01: "tlbr", 0x02: "tlbwi", 0x06: "tlbwr", 0x08: "tlbp",
                 0x10: "rfe", 0x18: "eret"}
        if (word & 0x3F) in names:
            return _instruction(names[word & 0x3F])
    return _unknown(word)


def _special2(word: int) -> Instruction:
    funct, rd, rt, rs = word & 0x3F, (word >> 11) & 31, (word >> 16) & 31, (word >> 21) & 31
    three = {0x00: "madd", 0x01: "maddu", 0x04: "msub", 0x05: "msubu"}
    if funct in three:
        return _instruction(three[funct], (REGISTERS[rs], REGISTERS[rt]),
                            (_reg(rs, "rs"), _reg(rt, "rt")))
    if funct == 0x02:
        return _instruction("mul", (REGISTERS[rd], REGISTERS[rs], REGISTERS[rt]),
                            (_reg(rd, "rd"), _reg(rs, "rs"), _reg(rt, "rt")))
    if funct in (0x20, 0x21):
        return _instruction("clz" if funct == 0x20 else "clo", (REGISTERS[rd], REGISTERS[rs]),
                            (_reg(rd, "rd"), _reg(rs, "rs")))
    return _unknown(word)


def _moved(retail: Instruction, ours: Instruction) -> list:
    """The fields that moved between the two spellings, as ``name retail -> ours``."""
    if retail.mnemonic != ours.mnemonic:
        return [f"{retail.mnemonic} -> {ours.mnemonic}"]
    there = {field.name: field for field in ours.fields}
    out = []
    for field in retail.fields:
        other = there.get(field.name)
        if other is not None and other.value != field.value:
            out.append(f"{field.name} {field.text} -> {other.text}")
    return out


# ---------------------------------------------------------------------------
# rendering
# ---------------------------------------------------------------------------


def _first_diff_text(body: Body) -> str:
    at = body.first_diff
    return "-" if at is None else f"+0x{at:X}"


def render(measured: Measured) -> str:
    """The default report: the pair, the masking rule, and one line per body."""
    lines = [f"measure: {measured.source} ({measured.target})",
             f"pair: {measured.compiler} {measured.flags}",
             MASKING_NOTE]
    widths = [max(len("body"), *(len(body.name) for body in measured.bodies))]
    counts = [f"{body.ours_words}/{body.retail_words}" for body in measured.bodies]
    width_span = max(len("ours/retail words"), *(len(count) for count in counts))
    width_diff = max(len("differing"),
                     *(len(body.length_note or str(body.differing)) for body in measured.bodies))
    header = (f"  {'body':<{widths[0]}}  {'ours/retail words':>{width_span}}  "
              f"{'differing':>{width_diff}}  first diff")
    lines += [header, "  " + "-" * (len(header) - 2)]
    for body, count in zip(measured.bodies, counts):
        differing = body.length_note or str(body.differing)
        lines.append(f"  {body.name:<{widths[0]}}  {count:>{width_span}}  "
                     f"{differing:>{width_diff}}  {_first_diff_text(body)}")
    exact = sum(1 for body in measured.bodies if body.exact)
    lines.append("")
    lines.append(f"{exact} of {len(measured.bodies)} bodies EXACT"
                 + (" (retail's length, no differing word outside a relocated field)"
                    if measured.bodies else ""))
    return "\n".join(lines) + "\n"


def _word(data: bytes, at: int):
    """The little-endian word at ``at``, or ``None`` past the body's end."""
    return struct.unpack_from("<I", data, at)[0] if at + 4 <= len(data) else None


def render_side(body: Body) -> str:
    """Retail's and our instructions, one pair per line, with the fields that moved.

    A word that differs only inside a field the relocation writes is marked
    ``(relocation field)``: it is not a residue, and the table above has already called it
    exact.
    """
    ours, retail = masked(body.ours, body.ignored), masked(body.retail, body.ignored)
    span = _common(ours, retail)
    rows = []
    for at in range(0, span, 4):
        mine, want = _word(body.ours, at), _word(body.retail, at)
        left = "-" if want is None else f"0x{want:08X}  {decode(want).text}"
        right = "-" if mine is None else f"0x{mine:08X}  {decode(mine).text}"
        if want is None or mine is None:
            note = "(length)"
        elif want == mine:
            note = ""
        elif ours[at:at + 4] == retail[at:at + 4]:
            note = "(relocation field)"
        else:
            note = ", ".join(_moved(decode(want), decode(mine))) or "(word)"
        rows.append((f"+0x{at:04X}", left, right, note))
    for at in range(span, len(body.ours), 4):
        word = _word(body.ours, at)
        if word is not None:
            rows.append((f"+0x{at:04X}", "-", f"0x{word:08X}  {decode(word).text}",
                         "(ours only)"))
    for at in range(span, len(body.retail), 4):
        word = _word(body.retail, at)
        if word is not None:
            rows.append((f"+0x{at:04X}", f"0x{word:08X}  {decode(word).text}", "-",
                         "(retail only)"))
    width_retail = max((len(row[1]) for row in rows), default=1)
    width_ours = max((len(row[2]) for row in rows), default=1)
    lines = [f"{body.name}: retail (left) and ours (right)",
             f"  {'offset':<7}  {'retail':<{width_retail}}  {'ours':<{width_ours}}  field"]
    for offset, left, right, note in rows:
        lines.append(f"  {offset:<7}  {left:<{width_retail}}  {right:<{width_ours}}  {note}")
    if body.length_note:
        lines.append(f"  {body.length_note}: retail 0x{len(body.retail):X} bytes, "
                     f"ours 0x{len(body.ours):X}")
    return "\n".join(lines) + "\n"


# ---------------------------------------------------------------------------
# entry point
# ---------------------------------------------------------------------------


def parse_args(argv=None):
    parser = argparse.ArgumentParser(
        prog="measure.py",
        description="Compile a unit with its recorded pair and compare each body with "
                    "retail's words.")
    parser.add_argument("unit", help="the unit: src/... .c, its file name, or its stem")
    parser.add_argument("--fn", default=None, metavar="NAME",
                        help="measure only this function (default: every body)")
    parser.add_argument("--side", action="store_true",
                        help="with --fn: print retail and ours line by line")
    parser.add_argument("--json", action="store_true", help="report the measurement as JSON")
    parser.add_argument("--target", default=None,
                        help=f"the target whose pair and image are used (default: "
                             f"{targets.DEFAULT})")
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(argv)
    if args.side and not args.fn:
        print("measure.py: --side prints one body: name it with --fn", file=sys.stderr)
        return 2
    if args.side and args.json:
        print("measure.py: --json and --side report the same body differently: pick one",
              file=sys.stderr)
        return 2
    try:
        measured = measure(args.unit, args.fn, args.target)
    except (NotPromoted, Missing) as exc:
        print(f"measure.py: {exc}", file=sys.stderr)
        return 2
    except (cc.Unusable, targets.UnknownTarget, targets.NotMeasured) as exc:
        print(f"measure.py: {exc}", file=sys.stderr)
        return 2
    except (probe.ProbeError, FileNotFoundError, OSError) as exc:
        print(f"measure.py: {exc}", file=sys.stderr)
        print("measure.py: that is the toolchain, not the unit: fetch it with "
              "python3 tools/toolchain/fetch.py --all", file=sys.stderr)
        return 1
    if args.json:
        print(json.dumps(measured.as_json(), indent=2))
        return 0
    sys.stdout.write(render(measured))
    if args.side:
        # ``--fn`` narrowed the measurement, so the one body is the one to lay out.
        sys.stdout.write("\n" + render_side(measured.bodies[0]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
