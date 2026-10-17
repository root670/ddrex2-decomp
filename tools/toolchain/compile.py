#!/usr/bin/env python3
"""compile.py -- build one promoted translation unit with the retail compiler.

This is the program behind the ninja ``cc`` rule::

    build <out.o>: cc <src>     # flags = --compiler 3.0-011126 -c -lang c -O3 -g
      command = python3 tools/toolchain/compile.py $in $out $flags

``$in`` is the source alone: ``configure.py`` also declares this file -- and itself -- as the
edge's *implicit* inputs (``| ...``, R35a), so editing the driver invalidates the object it
produced without changing the command line.

It runs ``mwccps2`` (under wibo, through :mod:`toolchain.probe`) over a C source and turns
the Metrowerks object it writes into the one object the pinned build needs:

* ``.text`` -- the unit's functions, laid out and relocated at the virtual addresses the
  retail image has them at and labelled with their DWARF names, so the pinned ``ld`` script
  places the unit exactly where its splits used to be, and
* ``.debug`` / ``.line`` -- the unit's DWARF 1 payload, with the object's own ``.rel.debug``
  / ``.rel.line`` applied, so the ninja ``objsec`` edges can dump them and the file's tail
  can be assembled from the compiler's bytes instead of from the retail databins.

Why a translation rather than a link of the Metrowerks object (R23): mainline binutils
cannot read a ``mwccps2`` object at all, and ``mwldps2`` -- which can -- does not keep
``.debug``/``.line`` for a link without debug flags.  Every address a relocation needs is
already pinned by the oracle's manifests -- the unit's own chunk in ``.debug``, each
function's record and statement list, the unit's address, and ``$gp`` from the retail
ELF's ``.reginfo`` -- so the object's bytes can be placed directly under the pinned layout.
G1 and the unit's per-chunk verdicts are what prove the result; this program only has to be
honest about what it wrote.

Usage::

    python3 tools/toolchain/compile.py src/sys/sys_scf.c build/src/sys/sys_scf.c.o \\
        --compiler 3.0-011126 -c -lang c -O3 -g

``--syntax-only`` is the second thing this program is: the *compiler's* verdict on whether a
file is C, for the generated headers (`include/types/*.h`, `include/src/**`) that nothing
compiles yet:

    python3 tools/toolchain/compile.py --syntax-only --include include probe.c

MWCC has no parse-only mode -- ``-nocodegen`` skips the front end's own error reporting, so
it exits 0 on a file it cannot parse -- so the check runs the ordinary compile and throws
the object away.  What is left is the exit status and the compiler's own diagnostics.

Exit codes: 0 the object was written (or ``--syntax-only`` accepted the file), 1 the compiler
or the assembler failed, 2 the source, a manifest, a host tool or a name the object needs is
not something this build can place.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import pathlib
import re
import shutil
import struct
import subprocess
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

import elf  # noqa: E402  the vendored 32-bit little-endian MIPS reader
from config import targets  # noqa: E402  the one place a target's facts are written down
from toolchain import check_deps, fetch, probe  # noqa: E402

#: The target a direct invocation works on when ``--target`` names none: the one the tree is
#: configured for.  The ninja graph always names the target it was generated for, so a build
#: never depends on this default; it is what `compile.py` and `select_build.py` do by hand.
DEFAULT_TARGET = targets.get(targets.DEFAULT)
RETAIL = DEFAULT_TARGET.elf
BUILD = REPO_ROOT / "build"

#: The ``mwccps2`` flags a direct invocation uses.  ``-O3`` is where the retail instruction
#: scheduling appears, ``-g`` is where its DWARF 1 comes from;
#: ``tools/toolchain/select_build.py`` measures the pair per unit and prints what the build
#: should pass.
DEFAULT_FLAGS = ("-c", "-lang", "c", "-O3", "-g")

#: The host assembler invocation, matching the splits' rule in ``configure.py``: no padding
#: (the pinned script places whole objects back to back with SUBALIGN(1)), EABI register
#: numbering, the R5900 ISA.
AS = ("mips-linux-gnu-as", "-Iasm/include", "--no-pad-sections", "-EL", "-march=5900",
      "-mabi=eabi")

#: The staging root.  The compiler records the *absolute* path of the file it is given,
#: canonicalised -- wibo resolves the host path, so a staged copy under macOS's ``/tmp``
#: is recorded under ``/private/tmp`` -- and spells the host root as the ``Z:`` drive.
#: Retail's CU name records the original build host's path, and a staged copy is put at a
#: path whose guest spelling is exactly as long as retail's, so that replacing the
#: recorded name cannot resize a DIE.  ``/tmp`` is the shortest root every host has (the
#: repo's own path is longer than the retail build's recorded one); it is resolved here because
#: the *real* path is the one that has to fit.
STAGING_ROOT = pathlib.Path("/tmp").resolve()

#: The oracle's own word for the one reason that still has an address to place: an object
#: whose DWARF `AT_location` carries none, which is 0 in retail's bytes (`emit_symbols.py`
#: writes the reason; `tests/toolchain/test_compile_relocations.py` pins this spelling to
#: it).  The other reason, "outside every declared segment", is *not* address 0 -- those
#: objects live in the overlay reservations this layout does not model.
UNPLACED_NO_ADDRESS = "no AT_location address"

R_MIPS_NONE, R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16 = 0, 2, 4, 5, 6, 7
RELOC_NAMES = {R_MIPS_32: "R_MIPS_32", R_MIPS_26: "R_MIPS_26",
               R_MIPS_HI16: "R_MIPS_HI16", R_MIPS_LO16: "R_MIPS_LO16",
               R_MIPS_GPREL16: "R_MIPS_GPREL16"}

SHT_REL = 9
STT_SECTION, STT_FUNC = 3, 2
SYMBOL_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<address>0x[0-9A-Fa-f]+);\s*//\s*(?P<attrs>.*)$")
SPLIT_ADDRESS = re.compile(
    r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]{8}\s+\*/")


class Unusable(Exception):
    """The unit cannot be placed: a manifest, a name or the source itself is unusable."""


# ---------------------------------------------------------------------------
# the oracle's manifests, as the compiler needs them
# ---------------------------------------------------------------------------


class Function:
    """One function of a unit: where retail put it, and where its DWARF goes."""

    __slots__ = ("name", "address", "size", "debug_offset", "debug_size",
                 "line_offset", "line_size", "record")

    def __init__(self, name, address, size, debug_offset, debug_size, line_offset,
                 line_size, record):
        self.name = name
        self.address = address
        self.size = size
        self.debug_offset = debug_offset      # offset in the .debug section
        self.debug_size = debug_size
        self.line_offset = line_offset        # offset in the .line section
        self.line_size = line_size
        self.record = record                  # index into cus.json


class Tu:
    """One translation unit of the retail build, with its pinned placement."""

    __slots__ = ("file", "name", "records", "debug_offset", "debug_size",
                 "line_offset", "line_size", "functions")

    def __init__(self, file, name, records, debug_offset, debug_size, line_offset,
                 line_size, functions):
        self.file = file                  # repo-relative, e.g. "src/sys/sys_scf.c"
        self.name = name                  # the retail spelling, with its drive
        self.records = records            # cus.json indices, in .debug order
        self.debug_offset = debug_offset  # the unit's .debug chunk
        self.debug_size = debug_size
        self.line_offset = line_offset    # the unit's run of .line chunks
        self.line_size = line_size
        self.functions = functions        # in address order

    @property
    def source(self) -> pathlib.Path:
        return REPO_ROOT / self.file

    @property
    def address(self) -> int:
        return min(function.address for function in self.functions)

    @property
    def end(self) -> int:
        return max(function.address + function.size for function in self.functions)

    def function_named(self, name):
        return next((f for f in self.functions if f.name == name), None)


class Manifests:
    """A target's ``cus.json``, ``debug_chunks.json`` and ``symbol_addrs.txt``, read once.

    The target is a parameter, never a module-level convention: the ninja ``cc`` edge passes
    ``--target``, so a unit is placed against the manifests of the binary its object is
    linked into rather than against whichever config a default happens to name.
    """

    def __init__(self, target=None):
        self.target = target if target is not None else DEFAULT_TARGET
        self.dir = self.target.config_dir
        self.cus = self._json(self.dir / "cus.json")
        self.chunks = self._json(self.dir / "debug_chunks.json")
        self.symbols = {}
        self.by_address = {}
        # An object the oracle could not place *because retail's own DWARF gives it no
        # address* still has a value a placement has to reproduce: 0, which is what retail's
        # `AT_location` holds for it.  Those records are in `unplaced_symbols.txt` with that
        # reason, and nothing else in that file may be read this way -- an object outside
        # every declared segment (this target's overlay reservations) has a real address that
        # this layout does not model, so substituting 0 for it would be a guess.  The name is
        # the oracle's own word for the reason (`emit_symbols.UNPLACED_REASON`), and
        # `tests/toolchain/test_compile_relocations.py` pins the two together.
        for name, address, _attrs in self._unplaced_without_address():
            self.symbols.setdefault(name, (address, {"provenance": "unplaced"}))
        for line in (self.dir / "symbol_addrs.txt").read_text().splitlines():
            match = SYMBOL_LINE.match(line.strip())
            if match is None:
                continue
            address = int(match["address"], 16)
            attrs = dict(attr.split(":", 1) for attr in match["attrs"].split() if ":" in attr)
            self.symbols[match["name"]] = (address, attrs)
            # An address-derived stand-in (`func_0021C410`) and the DWARF name share an
            # address; the DWARF name is the evidence, so it wins.
            known = self.by_address.get(address)
            if known is None or (attrs.get("provenance") == "dwarf"
                                 and self.symbols[known][1].get("provenance") != "dwarf"):
                self.by_address[address] = match["name"]

    def _unplaced_without_address(self):
        """``[(name, address, attrs)]`` for the unplaced records retail gives no address.

        The placed ledger wins over every one of them (they are read first), so this can
        only ever *add* a name: one whose object exists in the unit's DWARF and nowhere in
        the image.
        """
        path = self.dir / "unplaced_symbols.txt"
        if not path.is_file():
            return []
        out = []
        for line in path.read_text().splitlines():
            match = SYMBOL_LINE.match(line.strip())
            if match is None:
                continue
            # The reason is prose and carries spaces ("no AT_location address"), so it is the
            # one field that cannot come out of the keyword split; `dwarf_name:` follows it
            # when the oracle had to rename a duplicate.
            tail = match["attrs"]
            if "reason:" not in tail:
                continue
            reason = tail.split("reason:", 1)[1].split(" dwarf_name:", 1)[0].strip()
            if reason == UNPLACED_NO_ADDRESS:
                out.append((match["name"], int(match["address"], 16), {"reason": reason}))
        return out

    @staticmethod
    def _json(path) -> object:
        if not path.is_file():
            raise Unusable(f"{path.relative_to(REPO_ROOT)} is missing; run ./ddr oracle")
        return json.loads(path.read_text())

    def address_of(self, name) -> int:
        if name not in self.symbols:
            raise Unusable(
                f"the object references {name!r}, which "
                f"{self.target.symbols.relative_to(REPO_ROOT)} "
                f"gives no address for; the unit cannot be placed")
        return self.symbols[name][0]

    def tu_named(self, name: str) -> Tu:
        """The unit ``name`` spells -- a repo path, a path tail, or a file name.

        The rules are ``tools/verify/g2.py``'s, so the name ``ddr verify --tu`` accepts is
        the name this build accepts, and an ambiguous name is an error in both.
        """
        matched = sorted(
            (index, record["file"]) for index, record in enumerate(self.cus)
            if record.get("kind") == "tu"
            and (record["file"] == name
                 or record["file"].endswith("/" + name)
                 or pathlib.PurePosixPath(record["file"]).name in (name, f"{name}.c")))
        if not matched:
            raise Unusable(f"no translation unit matches {name!r}")
        if len(matched) > 1:
            raise Unusable(f"{name!r} matches {len(matched)} translation units: "
                           + ", ".join(file for _, file in matched))
        return self._tu(matched[0][0])

    def tu_files(self) -> set:
        """Every ``file`` a ``kind:tu`` record names -- no placement asked, no validation.

        Most units have records this build cannot place (a unit with no function at all, a
        unit whose records are not subprograms); they are still units the promotion check
        has to see, so the listing is what this returns rather than a placed :class:`Tu`.
        """
        return {record["file"] for record in self.cus if record.get("kind") == "tu"}

    def _tu(self, index: int) -> Tu:
        record = self.cus[index]
        chunk = next((c for c in self.chunks if c.get("section") == ".debug"
                      and c.get("tunits", [None])[0] == index), None)
        if chunk is None:
            raise Unusable(f"no .debug chunk starts at cus.json record {index}")
        records = list(chunk["tunits"])
        line_chunks = []
        functions = []
        for number in records[1:]:
            entry = self.cus[number]
            if entry.get("kind") != "function" or entry.get("low_pc") is None:
                raise Unusable(
                    f"{record['file']}: cus.json record {number} is "
                    f"{entry.get('kind')!r}, not a function this build can place")
            name = self.by_address.get(entry["low_pc"])
            if name is None:
                raise Unusable(f"{record['file']}: no symbol at 0x{entry['low_pc']:08X}")
            line = next((c for c in self.chunks if c.get("section") == ".line"
                         and c.get("tunits", [None])[0] == number), None)
            if line is None:
                raise Unusable(f"{record['file']}: no .line chunk for {name}")
            line_chunks.append((line["offset"], line["size"]))
            functions.append(Function(
                name, entry["low_pc"], entry["high_pc"] - entry["low_pc"],
                entry["offset"], entry["size"], line["offset"], line["size"], number))
        if not functions:
            raise Unusable(f"{record['file']} declares no functions")
        functions.sort(key=lambda f: f.address)
        if not _contiguous(line_chunks):
            raise Unusable(
                f"{record['file']}: the unit's .line chunks are not contiguous "
                f"({', '.join(f'0x{o:X}+0x{s:X}' for o, s in line_chunks)}); the file's tail "
                f"cannot be assembled from one payload")
        return Tu(record["file"], record["name"], records, chunk["offset"], chunk["size"],
                  min(offset for offset, _ in line_chunks),
                  sum(size for _, size in line_chunks), functions)

    def section_chunks(self, section: str):
        """A section's chunks in file order -- the order ``configure.py`` cuts databins."""
        return sorted((c for c in self.chunks if c.get("section") == section),
                      key=lambda c: c["offset"])

    def line_chunk_indices(self, tu: Tu):
        """The unit's ``.line`` chunks, by their position among the ``.line`` chunks.

        The position, not the manifest index: ``configure.py`` names a databin
        ``.line_<position>`` from the section's own file order, which is what the tail
        substitution has to match.
        """
        offsets = {f.line_offset for f in tu.functions}
        return [index for index, chunk in enumerate(self.section_chunks(".line"))
                if chunk["offset"] in offsets]

    def debug_chunk_index(self, tu: Tu) -> int:
        """The unit's ``.debug`` chunk, by its position among the ``.debug`` chunks."""
        return [c["offset"] for c in self.section_chunks(".debug")].index(tu.debug_offset)


def _contiguous(runs) -> bool:
    ordered = sorted(runs)
    return all(ordered[i][0] + ordered[i][1] == ordered[i + 1][0]
               for i in range(len(ordered) - 1))


def _split_extent(tu: Tu, manifests: Manifests, root=REPO_ROOT) -> tuple[int, int]:
    """Return the address range occupied by the splits a promotion removes.

    Splat's function split includes the trailing bytes up to the next split, which can be
    padding outside the function's DWARF ``high_pc``.  The linker removes that whole run,
    so a promoted object has to fill it too.
    """
    segment = manifests.target.geometry_required().code_segment
    directory = pathlib.Path(root) / "asm" / "nonmatchings" / segment
    if not directory.is_dir():
        raise Unusable(f"{tu.file}: {directory} is missing; run the oracle and "
                       "configure step first")
    rows = []
    for path in directory.glob("*.s"):
        match = SPLIT_ADDRESS.search(path.read_text())
        if match is None:
            raise Unusable(f"{path} carries no split address")
        rows.append((int(match.group(1), 16), path))
    rows.sort()
    addresses = [function.address for function in tu.functions]
    positions = []
    for address in addresses:
        position = next((i for i, (candidate, _) in enumerate(rows)
                         if candidate == address), None)
        if position is None:
            raise Unusable(f"{tu.file}: no code split at 0x{address:08X}")
        positions.append(position)
    first, last = min(positions), max(positions)
    if sorted(positions) != list(range(first, last + 1)):
        raise Unusable(f"{tu.file}: its function splits are not one contiguous run")
    end = rows[last + 1][0] if last + 1 < len(rows) else tu.end
    if end < tu.end:
        raise Unusable(f"{tu.file}: split extent ends at 0x{end:08X}, before its "
                       f"last function ends at 0x{tu.end:08X}")
    return tu.address, end


def _all_nops(data: bytes) -> bool:
    """Whether ``data`` is whole-word MIPS ``nop`` padding."""
    return len(data) % 4 == 0 and all(data[offset:offset + 4] == b"\0\0\0\0"
                                       for offset in range(0, len(data), 4))


def _uncovered(size: int, spans) -> list[tuple[int, int]]:
    """The ``[start, end)`` runs of ``size`` that no ``(offset, length)`` span covers."""
    runs = []
    cursor = 0
    for start, length in sorted(spans):
        if start > cursor:
            runs.append((cursor, start))
        cursor = max(cursor, start + length)
    if cursor < size:
        runs.append((cursor, size))
    return runs


def _require_nops(data: bytes, unit: str, chunk: str) -> None:
    """Refuse unless ``data`` is whole-word ``nop``: padding may be filled, content not."""
    if not _all_nops(data):
        raise Unusable(
            f"{unit}: {chunk} is short by 0x{len(data):X} bytes; C is incomplete "
            f"(retail's bytes there are content, not nop padding)")


def _fill_nop_tail(known: bytes, padding: bytes, unit: str, chunk: str) -> bytes:
    """``known`` extended with retail's ``padding`` -- only when that padding is ``nop``."""
    _require_nops(padding, unit, chunk)
    if padding:
        print(f"compile: {unit}: filled {chunk} trailing nop padding from retail "
              f"(0x{len(padding):X} bytes)", file=sys.stderr)
    return known + padding


def _text_extent(text: bytes, retail: bytes, spans, trailing: int, unit: str) -> bytes:
    """``text`` with every byte no function body covers taken from retail's own padding.

    ``spans`` are the ``(offset, length)`` runs the unit's function bodies occupy and
    ``trailing`` is where its last function ends: the run from there on is the *shortfall*
    the promotion has to fill, because the splits it displaces run to the next split's
    address, past that function.  A byte in an inter-function gap that retail does not
    leave ``nop`` is content this unit has not written, and is refused -- as is a shortfall
    whose remainder is anything but ``nop``.
    """
    for start, end in _uncovered(len(text), spans):
        gap = retail[start:end]
        if start == trailing:
            return _fill_nop_tail(text[:start], gap, unit, ".text")
        _require_nops(gap, unit, ".text")
    return text


# ---------------------------------------------------------------------------
# the Metrowerks object
# ---------------------------------------------------------------------------


class MWObject:
    """A compiled ``mwccps2`` object, read by section index.

    Metrowerks emits one group of sections per function (``.text``, ``.debug``, ``.line``,
    ``.mwcats``), so a section *name* is not unique: every lookup here goes through the
    symbol table, which is also how the linker told the groups apart.
    """

    def __init__(self, path, manifests=None):
        self.path = pathlib.Path(path)
        self.elf = elf.Elf(str(self.path))
        self.manifests = manifests
        self.relocs = {}      # target section index -> [(offset, type, symbol)]
        for section in self.elf.sections:
            if section.type != SHT_REL:
                continue
            for offset in range(section.offset, section.offset + section.size, 8):
                at, info = struct.unpack_from("<II", self.elf.data, offset)
                self.relocs.setdefault(section.info, []).append(
                    (at, info & 0xFF, self.elf.symbols[info >> 8]))

    def data(self, index) -> bytes:
        section = self.elf.sections[index]
        return self.elf.data[section.offset:section.offset + section.size]

    def section_named(self, name) -> int:
        """The first section called ``name`` -- the unit's own ``.debug``, for instance."""
        found = [i for i, s in enumerate(self.elf.sections) if s.name == name]
        if not found:
            raise Unusable(f"{self.path}: the object has no {name} section")
        return found[0]

    def _symbol(self, predicate, what: str):
        for symbol in self.elf.symbols:
            if predicate(symbol):
                return symbol
        raise Unusable(f"{self.path}: the object has no {what}")

    def section_of_symbol(self, name) -> int:
        return self._symbol(lambda s: s.name == name and s.type == STT_SECTION,
                            f"section symbol {name!r}").shndx

    def function_section(self, name) -> int:
        return self._symbol(lambda s: s.name == name and s.type == STT_FUNC,
                            f"definition of the function {name!r}").shndx

    def groups(self, tu: Tu):
        """``{function name: (text, debug, line)}`` -- one section group per function."""
        return {function.name: (self.function_section(function.name),
                               self.section_of_symbol(f".debug_{function.name}"),
                               self.section_of_symbol(f".line_{function.name}"))
                for function in tu.functions}

    def resolve(self, tu: Tu, symbol):
        """The pinned value of ``symbol`` in the layout this unit goes into.

        Three cases, all pinned: one of the unit's own section symbols (the offset of the
        block it carries: the unit's records, a function's DWARF record, or a statement
        list), a function of the unit (its retail address), and anything else -- which has
        to be a name the oracle's symbol file gives an address for.
        """
        pinned = self._section_offset(tu, symbol)
        if pinned is not None:
            return pinned
        function = tu.function_named(symbol.name)
        if function is not None:
            return function.address
        if self.manifests is None:
            raise Unusable("no manifests to resolve symbols with")
        return self.manifests.address_of(symbol.name)

    def _section_offset(self, tu: Tu, symbol):
        if symbol.type != STT_SECTION:
            return None
        name = symbol.name
        if name == ".debug":                       # the unit's own records start here
            return tu.debug_offset
        for function in tu.functions:
            if name == f".debug_{function.name}":
                return function.debug_offset
            if name == f".line_{function.name}":
                return function.line_offset
            if name == ".text" and symbol.shndx == self.function_section(function.name):
                return function.address
        return None


def _signed16(value: int) -> int:
    """A 16-bit immediate as the instruction means it: sign-extended."""
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def _lo_addend(data, offset: int) -> int:
    """The addend an instruction carries: what the compiler wrote in its low half."""
    return _signed16(struct.unpack_from("<I", data, offset)[0])


def _pairs(data, relocs, what: str):
    """``{hi offset: (lo offset, addend)}`` for the ``lui``/``addiu`` address pairs.

    A MIPS address over the small-data threshold is materialised by two instructions whose
    *addend* is split the same way: the compiler writes the high half in the ``lui`` and the
    low half in the ``%lo`` instruction, so the value to place is ``symbol + addend`` and the
    two immediates are its halves.  Only one split can be read off the object without
    guessing, and this is it: a ``lui`` whose own high half is zero (an address with no
    constant offset, which is every reference that names an object rather than a field of
    one) paired with the next ``%lo`` for the same symbol.  Anything else raises, because a
    half-split address would be a *guess* at the layout rather than a read of it.
    """
    lo = [(offset, _lo_addend(data, offset), symbol.name)
          for offset, rtype, symbol in relocs if rtype == R_MIPS_LO16]
    pairs = {}
    for offset, rtype, symbol in relocs:
        if rtype != R_MIPS_HI16:
            continue
        hi = struct.unpack_from("<I", data, offset)[0] & 0xFFFF
        if hi:
            raise Unusable(
                f"{what}: the address at 0x{offset:X} has 0x{hi:X} in its high half, so its "
                f"constant offset is split across a `lui`/`%lo` pair this build cannot read; "
                f"the two immediates cannot be recomputed from {symbol.name}")
        partner = next((entry for entry in lo
                        if entry[2] == symbol.name and entry[0] > offset), None)
        if partner is None:
            raise Unusable(
                f"{what}: the address of {symbol.name} at 0x{offset:X} is loaded with a "
                f"`lui` whose `%lo` half is not in this section; a lone high half is not an "
                f"address")
        pairs[offset] = (partner[1], partner[2])
    return pairs


def relocate(data: bytes, relocs, resolve, what: str, gp: int) -> bytes:
    """Apply a section's ``.rel`` entries to its bytes.

    The objects are ``SHT_REL``, so each entry's addend is the value already in the field:
    a whole word for ``R_MIPS_32`` (the compiler writes the record's own offset there and
    relocates against its section symbol), the target word for ``R_MIPS_26``, the
    sign-extended immediate for ``R_MIPS_GPREL16`` and for the ``%lo`` half of an address,
    and the *paired* ``%lo``'s immediate for that address's ``%hi`` half -- because the
    address is ``symbol + addend`` and the compiler writes one constant's two halves into
    the two instructions.  A pair whose constant offset is split any other way is refused
    rather than approximated (see :func:`_pairs`).
    """
    out = bytearray(data)
    pairs = _pairs(data, relocs, what)
    for offset, rtype, symbol in relocs:
        if rtype == R_MIPS_NONE:
            continue
        value = resolve(symbol)
        word = struct.unpack_from("<I", out, offset)[0]
        if rtype == R_MIPS_32:
            struct.pack_into("<I", out, offset, (value + word) & 0xFFFFFFFF)
        elif rtype == R_MIPS_26:
            target = value + ((word & 0x03FFFFFF) << 2)
            struct.pack_into("<I", out, offset,
                             (word & 0xFC000000) | ((target >> 2) & 0x03FFFFFF))
        elif rtype in (R_MIPS_HI16, R_MIPS_LO16):
            address = value + (pairs[offset][0] if rtype == R_MIPS_HI16
                               else _lo_addend(data, offset))
            half = (address + 0x8000) >> 16 if rtype == R_MIPS_HI16 else address
            struct.pack_into("<I", out, offset, (word & 0xFFFF0000) | (half & 0xFFFF))
        elif rtype == R_MIPS_GPREL16:
            addend = word & 0xFFFF
            if addend & 0x8000:
                addend -= 0x10000
            delta = value + addend - gp
            if not -0x8000 <= delta <= 0x7FFF:
                raise Unusable(
                    f"{what}: {symbol.name} is 0x{delta:X} from $gp (0x{gp:08X}), which the "
                    f"instruction cannot hold; retail's $gp does not fit this layout")
            struct.pack_into("<I", out, offset, (word & 0xFFFF0000) | (delta & 0xFFFF))
        else:
            raise Unusable(f"{what}: relocation {RELOC_NAMES.get(rtype, rtype)!r} at "
                           f"0x{offset:X} is not one this build applies")
    return bytes(out)


def gp_value(retail=RETAIL) -> int:
    """``$gp`` as the retail ELF's ``.reginfo`` records it -- the ABI's own number."""
    image = elf.Elf(str(retail))
    section = next((s for s in image.sections if s.name == ".reginfo"), None)
    if section is None or section.size < 24:
        raise Unusable(f"{retail}: no .reginfo section to read $gp from")
    return struct.unpack_from("<I", image.data, section.offset + 20)[0]


# ---------------------------------------------------------------------------
# staging: the source path the DWARF records
# ---------------------------------------------------------------------------


def staged_path(tu: Tu) -> pathlib.Path:
    """Where to compile ``tu``'s source so that the DWARF path has retail's length."""
    basename = tu.source.name
    pad = len(tu.name) - len("Z:") - 1 - len(basename) - len(str(STAGING_ROOT)) - 1
    if pad < 1:
        raise Unusable(
            f"{tu.file}: retail's path spelling is {len(tu.name)} bytes, too short to stage "
            f"{basename!r} under {STAGING_ROOT}; this unit's DWARF name cannot be "
            f"reproduced")
    stem = re.sub(r"\W", "_", basename)
    # The directory must stay exactly `pad` long, so a per-unit digest is mixed in: two
    # units that share a basename and a retail-name length (`src/sys/foo.c` and
    # `src/mov/foo.c`) would otherwise stage over each other, and ninja runs `cc` edges in
    # parallel -- one unit would compile the other's copy.
    tag = hashlib.sha1(tu.file.encode()).hexdigest()
    directory = tag[:pad] if pad <= len(tag) else (stem + "_" * pad)[:pad - len(tag)] + tag
    return STAGING_ROOT / directory / basename


def recorded_name(staged: pathlib.Path) -> bytes:
    """The source path as mwcc records it: wibo spells a host path as the ``Z:`` drive."""
    return ("Z:" + str(staged)).replace("/", "\\").encode()


def retail_name_in(payload: bytes, recorded: bytes, retail: bytes) -> bytes:
    """Replace the recorded source path with retail's spelling, or fail loudly."""
    if len(recorded) != len(retail):
        raise Unusable(
            f"the staged path spells {len(recorded)} bytes where retail's spells "
            f"{len(retail)}; a different-length name would resize the DWARF records")
    if recorded == retail:
        return payload
    if recorded not in payload:
        raise Unusable(f"the compiler did not record {recorded!r} in its DWARF")
    return payload.replace(recorded, retail)


# ---------------------------------------------------------------------------
# emitting the GNU object
# ---------------------------------------------------------------------------


def _words(data: bytes) -> list[str]:
    """``.word`` lines for the bytes, with a trailing partial word as ``.byte``."""
    lines = []
    for start in range(0, len(data), 16):
        chunk = data[start:start + 16]
        whole = len(chunk) - len(chunk) % 4
        line = ""
        if whole:
            line = "\t.word\t" + ", ".join(
                f"0x{struct.unpack_from('<I', chunk, at)[0]:08X}"
                for at in range(0, whole, 4))
        if whole != len(chunk):
            rest = "\t.byte\t" + ", ".join(f"0x{byte:02X}" for byte in chunk[whole:])
            line = f"{line}\n{rest}" if line else rest
        lines.append(line)
    return lines


def assembly(size: int, labels, debug: bytes, line: bytes) -> str:
    """The GNU assembler source for the placed split extent and the payloads.

    Each function's bytes follow its label, and the layout's own inter-function padding --
    the retail image aligns them, and the gap is zeros there -- is a ``.space`` between
    them.  The final ``.space`` fills any trailing split padding accepted by ``place``.
    """
    out = ["\t.text"]
    cursor = 0
    for address, name, body in sorted(labels):
        if address > cursor:
            out.append(f"\t.space\t{address - cursor}")
        out += [f"\t.globl\t{name}", f"{name}:"]
        out += _words(body)
        cursor = address + len(body)
    if cursor < size:
        out.append(f"\t.space\t{size - cursor}")
    for name, payload in ((".debug", debug), (".line", line)):
        if payload:
            out.append(f'\t.section {name},"",@progbits')
            out += _words(payload)
    return "\n".join(out) + "\n"


def assemble(source: str, out: pathlib.Path) -> None:
    """Assemble the placed unit with the host assembler the splits use."""
    out.parent.mkdir(parents=True, exist_ok=True)
    assembler = shutil.which(AS[0])
    if assembler is None:
        raise check_deps.MissingDependency(
            f"{AS[0]} is not on PATH; run python3 tools/toolchain/check_deps.py")
    result = subprocess.run([assembler, *AS[1:], "-o", str(out), "-"],
                            input=source, capture_output=True, text=True)
    if result.returncode != 0:
        raise Unusable(f"{AS[0]} failed:\n{result.stderr.strip()}")


# ---------------------------------------------------------------------------
# the whole step
# ---------------------------------------------------------------------------


class Placed:
    """What a promoted unit contributes to the pinned build."""

    __slots__ = ("text", "debug", "line", "labels", "sizes")

    def __init__(self, text, debug, line, labels, sizes):
        self.text = text        # the promoted run of code splits, including its tail padding
        self.debug = debug      # the unit's .debug chunk
        self.line = line        # the unit's run of .line chunks
        self.labels = labels    # [(offset within .text, function name, bytes)]
        self.sizes = sizes      # [(function name, (block, emitted, pinned))]


def _fill(mw: MWObject, tu: Tu, base: int, size: int, blocks, gp: int, section: str,
          rename=None, unit_file=None) -> tuple[bytes, list]:
    """A pinned span of ``.debug`` or ``.line``, filled from the object's own blocks.

    ``blocks`` is ``[(offset, pinned size, section index, label)]``, all of them offsets
    retail pinned, and ``rename`` is the ``(recorded, retail)`` source-path pair for the
    sections that carry one.  A block that does not fit its slot is raised: the file's tail
    would otherwise reflow silently and every later chunk would be a red herring.
    """
    out = bytearray(size)
    sizes = []
    for offset, pinned, index, label in blocks:
        body = relocate(mw.data(index), mw.relocs.get(index, ()),
                        lambda symbol: mw.resolve(tu, symbol), f"{label}.{section}", gp)
        if rename is not None:
            body = retail_name_in(body, *rename)
        sizes.append((label, section, len(body), pinned))
        at = offset - base
        owner = unit_file or tu.file
        if len(body) < pinned:
            shortfall = pinned - len(body)
            raise Unusable(
                f"{owner}: {label} {section} is short by 0x{shortfall:X} bytes; "
                f"C is incomplete (cannot pad {section})")
        if at < 0 or at + len(body) > size:
            raise Unusable(
                f"{owner}: {label} {section} is 0x{len(body):X} bytes where retail's is "
                f"0x{pinned:X}; it does not fit the pinned chunk at 0x{offset:X}")
        out[at:at + len(body)] = body
    return bytes(out), sizes


def place(tu: Tu, manifests: Manifests, compiler_dir, wibo, flags, keep=None) -> Placed:
    """Compile ``tu`` and place it: the unit's bytes, as the pinned layout has them."""
    if not tu.source.is_file():
        raise Unusable(f"{tu.source.relative_to(REPO_ROOT)} does not exist")
    staged = staged_path(tu)
    staged.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(tu.source, staged)
    recorded = recorded_name(staged)
    if len(recorded) != len(tu.name):
        raise Unusable(f"staging {staged} spells {len(recorded)} bytes, retail "
                       f"{len(tu.name)}")

    obj = pathlib.Path(keep) if keep else BUILD / "cc" / (tu.file + ".mw.o")
    probe.compile(staged, obj, compiler_dir, wibo, flags)

    mw = MWObject(obj, manifests)
    gp = gp_value(manifests.target.elf)
    groups = mw.groups(tu)

    text_start, text_end = _split_extent(tu, manifests)
    text_size = text_end - text_start
    text = bytearray(text_size)
    labels, sizes, body_spans = [], [], []
    for function in tu.functions:
        body = relocate(mw.data(groups[function.name][0]),
                        mw.relocs.get(groups[function.name][0], ()),
                        lambda symbol: mw.resolve(tu, symbol), f"{function.name}.text", gp)
        if len(body) != function.size:
            shortfall = function.size - len(body)
            detail = (f"short by 0x{shortfall:X} bytes" if shortfall > 0
                      else f"0x{-shortfall:X} bytes too large")
            raise Unusable(
                f"{tu.file}: .text {function.name} is {detail}; C is incomplete")
        at = function.address - text_start
        text[at:at + len(body)] = body
        body_spans.append((at, len(body)))
        labels.append((at, function.name, body))
        sizes.append((function.name, ".text", len(body), function.size))

    retail = elf.Elf(str(manifests.target.elf))
    expected_text = retail.read(text_start, text_size)
    text = bytearray(_text_extent(bytes(text), expected_text, body_spans,
                                  tu.end - text_start, tu.file))

    types = manifests.cus[tu.records[0]]
    debug, debug_sizes = _fill(
        mw, tu, tu.debug_offset, tu.debug_size,
        [(types["offset"], types["size"], mw.section_named(".debug"), "the unit's types")]
        + [(f.debug_offset, f.debug_size, groups[f.name][1], f.name) for f in tu.functions],
        gp, ".debug", (recorded, tu.name.encode()), tu.file)
    line, line_sizes = _fill(
        mw, tu, tu.line_offset, tu.line_size,
        [(f.line_offset, f.line_size, groups[f.name][2], f.name) for f in tu.functions],
        gp, ".line", unit_file=tu.file)
    return Placed(bytes(text), debug, line, labels, sizes + debug_sizes + line_sizes)


def retail_bytes(tu: Tu, retail=RETAIL, text_size=None) -> dict:
    """The unit's bytes in the retail image: its replaced text extent and payloads."""
    image = elf.Elf(str(retail))
    text = image.read(tu.address, tu.end - tu.address if text_size is None else text_size)
    spans = {}
    for section, (base, size) in ((".debug", (tu.debug_offset, tu.debug_size)),
                                  (".line", (tu.line_offset, tu.line_size))):
        entry = next((s for s in image.sections if s.name == section), None)
        if entry is None:
            raise Unusable(f"{retail}: no {section} section")
        spans[section] = image.data[entry.offset + base:entry.offset + base + size]
    return {"text": text, "debug": spans[".debug"], "line": spans[".line"]}


def compare(tu: Tu, placed: Placed, retail=RETAIL) -> dict:
    """Per part: ``(ok, detail)`` -- what the gates would say, for the selection loop."""
    want = retail_bytes(tu, retail, text_size=len(placed.text))
    mine = {"text": placed.text, "debug": placed.debug, "line": placed.line}
    out = {}
    for part, expected in want.items():
        got = mine[part]
        if got == expected:
            out[part] = (True, f"{len(expected)} bytes")
        elif len(got) != len(expected):
            out[part] = (False, f"{len(got)} bytes, retail has {len(expected)}")
        else:
            at = next(i for i, (a, b) in enumerate(zip(got, expected)) if a != b)
            out[part] = (False, f"{len(got)} bytes, first difference at 0x{at:X}")
    return out




# ---------------------------------------------------------------------------
# entry point
# ---------------------------------------------------------------------------


def _display(path) -> str:
    """A path as a reader types it: repo-relative when it is inside the repo."""
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def build(tu: Tu, out: pathlib.Path, flags, compiler: str, manifests=None,
          keep=None, target=None) -> Placed:
    """Everything the ``cc`` rule does: compile, place, and write ``out``."""
    target = target if target is not None else DEFAULT_TARGET
    manifests = manifests if manifests is not None else Manifests(target)
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    placed = place(tu, manifests, compiler_dir, wibo, flags, keep=keep)
    assemble(assembly(len(placed.text), placed.labels, placed.debug, placed.line), out)
    return placed


def syntax_only(source, flags, compiler: str, includes=()) -> int:
    """Compile ``source`` with the retail compiler and throw the object away.

    Returns the compiler's exit status -- 0 it accepted the file, 1 it did not, with its own
    diagnostics on stderr -- which is the whole point: a generated header is checked by
    ``mwccps2 -lang c``, the compiler the units are measured against, not by a host ``cc``.
    ``includes`` are added with ``-I`` (MWCC wants the directory joined to the flag), and
    nothing survives the call, so the check cannot be mistaken for a build.
    """
    source = pathlib.Path(source).expanduser()
    if not source.is_file():
        raise Unusable(f"{source} does not exist")
    command = list(flags or DEFAULT_FLAGS)
    for directory in includes:
        directory = pathlib.Path(directory).expanduser().resolve()
        if not directory.is_dir():
            raise Unusable(f"{directory} is not a directory: --include wants one")
        command.append(f"-I{directory}")
    compiler_dir = fetch.compiler(compiler)
    wibo = fetch.wibo()
    with tempfile.TemporaryDirectory(prefix="cc-syntax-") as scratch:
        obj = pathlib.Path(scratch) / (source.stem + ".mw.o")
        try:
            probe.compile(source, obj, compiler_dir, wibo, command)
        except probe.CompilerFailed as exc:
            print(f"compile.py: {exc}", file=sys.stderr)
            return 1
    print(f"cc --syntax-only {_display(source)}: accepted as C")
    return 0


def _parser(with_out: bool) -> argparse.ArgumentParser:
    """The CLI.  Two shapes, because mwcc's flags carry bare values.

    ``--syntax-only`` checks one file and writes nothing, so its parser has one positional
    and not two: with an optional ``out``, ``-lang c``'s value would be taken for the object
    path and the flag would reach the compiler stripped of its argument.
    """
    parser = argparse.ArgumentParser(prog="compile.py", description=__doc__.splitlines()[0])
    parser.add_argument("source",
                        help="the C source: as configure.py names it (src/...), or any file "
                             "with --syntax-only")
    if with_out:
        parser.add_argument("out", type=pathlib.Path, help="the object to write")
    parser.add_argument("--syntax-only", action="store_true",
                        help="ask the compiler whether the source is C and write nothing")
    parser.add_argument("--include", action="append", default=[], metavar="DIR",
                        help="add DIR to the compiler's include search path (repeatable; "
                             "with --syntax-only)")
    parser.add_argument("--compiler", default=fetch.REQUIRED,
                        help=f"the mwccps2 build to use (default: {fetch.REQUIRED})")
    parser.add_argument("--target", default=targets.DEFAULT,
                        help="the target whose manifests place the unit and whose retail "
                             f"binary it is compared with (default: {targets.DEFAULT}; "
                             f"known: {', '.join(targets.names())})")
    parser.add_argument("--keep", type=pathlib.Path, default=None,
                        help="where to keep the Metrowerks object the compiler writes")
    parser.add_argument("--compare", action="store_true",
                        help="also report each part against the retail image")
    return parser


def main(argv=None) -> int:
    argv = list(sys.argv[1:] if argv is None else argv)
    # Everything else is a flag for mwccps2 (`-c`, `-lang c`, `-O3`, `-g`, ...), which is
    # why the rule can pass `$flags` after the two paths without a separator.
    parser = _parser(with_out="--syntax-only" not in argv)
    args, flags = parser.parse_known_args(argv)
    try:
        target = targets.get(args.target)
        if args.syntax_only:
            return syntax_only(args.source, flags, args.compiler, args.include)
        manifests = Manifests(target)
        tu = manifests.tu_named(args.source)
        placed = build(tu, args.out, flags or DEFAULT_FLAGS, args.compiler, manifests,
                       keep=args.keep, target=target)
        shown = _display(args.out)
        print(f"cc {tu.file} [{target.name}]: {len(placed.text):#x} bytes of .text, "
              f"{len(placed.debug):#x} of .debug, {len(placed.line):#x} of .line -> {shown}")
        if args.compare:
            for part, (ok, detail) in compare(tu, placed, target.elf).items():
                print(f"cc {tu.file}: {part} {'ok' if ok else 'DIFFERS'} ({detail})")
        return 0
    except targets.UnknownTarget as exc:
        print(f"compile.py: error: {exc}", file=sys.stderr)
        return 2
    except probe.ProbeError as exc:  # the compiler failed: the source, or the flags
        print(f"compile.py: error: {exc}", file=sys.stderr)
        return 1
    except (Unusable, fetch.FetchError, check_deps.MissingDependency) as exc:
        print(f"compile.py: error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
