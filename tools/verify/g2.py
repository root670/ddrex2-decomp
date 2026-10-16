#!/usr/bin/env python3
"""G2 -- name the translation unit that owns a G1 failure, from the oracle's own manifests.

G1 compares the two images as *files* and hands the first differing offset to the manifests;
this module turns that answer into the one a reader can act on.  Two halves, and neither
re-derives the other's geometry (R32):

* ``.debug``/``.line`` offsets go through :class:`g1.Localiser`'s chunk manifest -- a
  ``.debug`` chunk names the translation unit whose records it holds, a ``.line`` chunk is
  one function compile unit's statement list.
* a byte in the loadable image has no chunk manifest at all, so it becomes a virtual address
  through the geometry ``configure.py`` pins (file ``0x80`` is VA ``0x100000``) and the
  address picks the DWARF *function* compile unit that covers it -- whose ``low_pc`` names
  the function and whose ``file`` names the translation unit.  That is the mapping the
  skeleton needs most: the code it builds is code, not debug data.

The manifests are read, never guessed: a missing or malformed file yields an empty
localisation rather than an exception, because the gate must not depend on the diagnostic.

``verify --tu NAME`` is the same manifests read the other way round -- the translation unit
becomes the subject and its ``.text`` span and its ``.debug``/``.line`` chunks are compared
with retail one by one (:func:`verdicts`).

Usage::

    python3 tools/verify/g2.py [out/<elf>] [--target NAME] [--retail orig/<elf>]
    python3 tools/verify/g2.py --tu sys_scf.c

Every input belongs to the target named by ``--target`` (the default target when it is not
named): its manifests, its retail binary and its built image, so a verdict is about one target
and never about two at once.

Exit codes: 0 nothing to localise (or the TU verdict is green), 1 a difference (or a red
verdict), 2 a file is missing or a name matches no translation unit.
"""

from __future__ import annotations

import argparse
import json
import pathlib
import sys
from typing import NamedTuple

HERE = pathlib.Path(__file__).resolve().parent
REPO_ROOT = HERE.parents[1]
for extra in (str(HERE), str(REPO_ROOT)):  # `python3 tools/verify/g2.py`, and configure
    if extra not in sys.path:
        sys.path.insert(0, extra)

try:
    from . import g1
except ImportError:  # imported flat, as `python3 tools/verify/g2.py` does
    import g1

from config import targets  # noqa: E402  the target's geometry: LOADABLE_ROM/VRAM, not a copy

#: The default target's names, so a bare call means "the target this tree is built for".  The
#: geometry a verdict is computed with is a parameter (`geometry=`), because the .text span of a
#: unit is a target's own measurement -- and it is resolved lazily, below: an unmeasured target
#: must not make this module unimportable.
TARGET = targets.get(targets.DEFAULT)
RETAIL = TARGET.elf
BUILT = TARGET.built


def geometry_of(target=None):
    """``target``'s measured geometry, or the default target's -- resolved when asked for."""
    return (target or TARGET).geometry_required()


class UnknownUnit(LookupError):
    """A ``--tu`` name matches no translation unit, or matches more than one."""


class Verdict(NamedTuple):
    """One line of ``verify --tu``'s report: what was compared, and what came out."""

    what: str          # "text", "debug chunk" or "line chunk"
    ok: bool
    detail: str        # the span compared, or the first byte that differs


def _chunks_of(chunks, section) -> list:
    return [chunk for chunk in chunks if chunk.get("section") == section]


def _first_difference_in(built, retail, start, end):
    """The absolute offset of the first byte that differs in ``[start, end)``, or None.

    The window is one translation unit (or one chunk), so it is read whole: a few kilobytes
    to a few hundred, against a 2.5 MB image.
    """
    with open(built, "rb") as lhs, open(retail, "rb") as rhs:
        lhs.seek(start)
        rhs.seek(start)
        left, right = lhs.read(end - start), rhs.read(end - start)
    for index, (one, other) in enumerate(zip(left, right)):
        if one != other:
            return start + index
    return start + min(len(left), len(right)) if len(left) != len(right) else None


class Manifests:
    """``cus.json`` + ``debug_chunks.json`` + ``symbol_addrs.txt``, read once and joined.

    This is the same data :class:`g1.Localiser` reads, with the two lookups a translation
    unit needs added: by name (``--tu`` takes ``sys_scf``, ``sys_scf.c`` or the full
    ``src/sys/sys_scf.c``), and by address (the function CU covering a virtual address).
    """

    def __init__(self, cus_path=g1.CUS, chunks_path=g1.CHUNKS, symbols_path=g1.SYMBOLS,
                 geometry=None):
        try:
            self.records = json.loads(pathlib.Path(cus_path).read_text())
            self.chunks = json.loads(pathlib.Path(chunks_path).read_text())
        except (OSError, json.JSONDecodeError, TypeError):
            self.records, self.chunks = [], []
        self.symbols = g1._symbol_table(symbols_path)
        self.geometry = geometry if geometry is not None else geometry_of()

    # -- names ---------------------------------------------------------------

    @property
    def debug_chunks(self) -> list:
        return _chunks_of(self.chunks, ".debug")

    @property
    def line_chunks(self) -> list:
        return _chunks_of(self.chunks, ".line")

    def tu_named(self, name: str) -> str:
        """The canonical ``file`` of the translation unit ``name`` spells, or raise."""
        candidates = {record["file"] for record in self.records}
        matched = sorted(
            file for file in candidates
            if file == name
            or file.endswith("/" + name)
            or pathlib.PurePosixPath(file).name in (name, f"{name}.c"))
        if not matched:
            raise UnknownUnit(f"no translation unit matches {name!r}")
        if len(matched) > 1:
            raise UnknownUnit(f"{name!r} matches {len(matched)} translation units: "
                              + ", ".join(matched))
        return matched[0]

    def records_of(self, tu: str) -> list:
        """Every compile-unit record the translation unit owns, in `.debug` order."""
        return [record for record in self.records if record.get("file") == tu]

    def functions_of(self, tu: str) -> list:
        return [record for record in self.records_of(tu)
                if record.get("kind") == "function" and record.get("low_pc") is not None]

    def symbol_at(self, address: int) -> str:
        """The DWARF (or Ghidra) name at ``address``, or the ``func_`` fallback splat uses."""
        return self.symbols.get(address) or f"func_{address:08X}"

    # -- addresses -----------------------------------------------------------

    def record_at_pc(self, pc: int):
        """The function compile unit whose ``[low_pc, high_pc)`` covers ``pc``, or None."""
        for record in self.records:
            if record.get("kind") != "function":
                continue
            low = record.get("low_pc")
            high = record.get("high_pc")
            if low is not None and high is not None and low <= pc < high:
                return record
        return None

    def debug_chunks_of(self, tu: str) -> list:
        """The `.debug` chunk(s) holding the translation unit's records (normally one)."""
        indices = {record["index"] for record in self.records_of(tu)}
        return [chunk for chunk in self.debug_chunks if indices & set(chunk.get("tunits") or ())]

    def line_chunks_of(self, tu: str) -> list:
        """One `.line` chunk per function of the translation unit, in `.line` order."""
        indices = {record["index"] for record in self.functions_of(tu)}
        chunks = [chunk for chunk in self.line_chunks
                  if indices & set(chunk.get("tunits") or ())]
        return sorted(chunks, key=lambda chunk: chunk["offset"])

    # -- the localisation itself --------------------------------------------

    def describe(self, offset: int):
        """``{section, offset, cu, tu, function}`` for a file offset, or None.

        ``cu`` is the compile-unit record's own `.debug` offset -- the address a reader can
        hand back to ``dwarf1.py`` -- and ``tu``/``function`` are None when the byte lies in
        the image but in no function's code (padding, rodata, data).
        """
        for section, base, size in self.geometry.sections:
            if base <= offset < base + size:
                return self._in_chunked_section(section, base, offset - base)
        if self.geometry.loadable_rom <= offset < self.geometry.loadable_end:
            return self._in_loadable_image(offset)
        return None

    def _in_chunked_section(self, section: str, base: int, relative: int):
        chunk = g1._chunk_at(self.chunks, section, relative)
        if chunk is None:
            return None
        if section == ".debug":
            unit = g1._record_at(self.records, relative) or self.records[chunk["tunits"][0]]
        else:
            unit = self.records[chunk["tunits"][0]]
        function = None
        if unit.get("kind") == "function" and unit.get("low_pc") is not None:
            function = self.symbol_at(unit["low_pc"])
        return {"section": section, "offset": base + relative, "cu": unit["offset"],
                "tu": unit.get("file"), "function": function}

    def _in_loadable_image(self, offset: int):
        address = self.geometry.address_of(offset)
        record = self.record_at_pc(address)
        if record is None:
            return {"section": ".text", "offset": offset, "cu": None, "tu": None,
                    "function": None}
        return {"section": ".text", "offset": offset, "cu": record["offset"],
                "tu": record.get("file"), "function": self.symbol_at(record["low_pc"])}


def localise(built, retail=RETAIL, cus=g1.CUS, chunks=g1.CHUNKS, symbols=g1.SYMBOLS,
             geometry=None):
    """The first difference between the two images as a location, or None when equal.

    ``built`` and ``retail`` are compared as files exactly as G1 compares them, so the
    offset reported here is the offset G1 reported: this is a *diagnostic* on top of the
    gate, never a second opinion about whether the gate passed.
    """
    offset, _note = g1._first_difference(built, retail)
    if offset is None:
        return None
    return Manifests(cus, chunks, symbols, geometry).describe(offset)


def describe(located) -> str:
    """The located difference as the one line ``verify`` prints for a G1 failure."""
    if located is None:
        return ""
    where = located["tu"] or "no compile unit names that byte"
    if located["function"]:
        where += f" / {located['function']}"
    if located["cu"] is not None:
        where += f" (CU 0x{located['cu']:X})"
    return (f"first difference at 0x{located['offset']:X} in {located['section']} "
            f"\u2192 {where}")


def verdicts(built, retail=RETAIL, name="", cus=g1.CUS, chunks=g1.CHUNKS, symbols=g1.SYMBOLS,
             geometry=None):
    """The per-TU report ``verify --tu NAME`` prints: text, then `.debug`, then `.line`.

    A translation unit is promoted only when its code *and* its debug chunk match retail
    (the spec's promotion rule), so all three are compared here and neither is implied by
    the other: G1 could be green while a chunk is not, and vice versa.
    """
    manifests = Manifests(cus, chunks, symbols, geometry)
    tu = manifests.tu_named(name)
    report = [_text_verdict(manifests, built, retail, tu)]
    sections = manifests.geometry.sections
    report.append(_section_verdict("debug chunk", manifests.debug_chunks_of(tu),
                                   sections[0][1], built, retail))
    report.append(_section_verdict("line chunk", manifests.line_chunks_of(tu),
                                   sections[1][1], built, retail))
    return tu, report


def _text_verdict(manifests, built, retail, tu) -> Verdict:
    geo = manifests.geometry
    functions = manifests.functions_of(tu)
    if not functions:
        return Verdict("text", True, "the translation unit declares no code")
    low = min(record["low_pc"] for record in functions)
    high = max(record["high_pc"] for record in functions)
    start = geo.offset_of(low)
    end = geo.offset_of(high)
    span = f"VA 0x{low:08X}-0x{high:08X}, {end - start} bytes"
    offset = _first_difference_in(built, retail, start, end)
    if offset is None:
        return Verdict("text", True, span)
    record = manifests.record_at_pc(geo.address_of(offset))
    name = manifests.symbol_at(record["low_pc"]) if record else "?"
    # The offset is the *file* offset, because that is what G1 reports and what a reader
    # compares; the VA and the function name are what makes it fixable.
    address = geo.address_of(offset)
    return Verdict("text", False,
                   f"{span}: first differing byte at 0x{offset:X} (VA 0x{address:08X}, {name})")


def _section_verdict(what, chunks, base, built, retail) -> Verdict:
    """``ok`` when every chunk of the section matches, else the first byte that differs."""
    if not chunks:
        return Verdict(what, True, f"nothing to compare in {what.split()[0]}")
    total = sum(chunk["size"] for chunk in chunks)
    for chunk in chunks:
        start, end = base + chunk["offset"], base + chunk["offset"] + chunk["size"]
        offset = _first_difference_in(built, retail, start, end)
        if offset is not None:
            relative = offset - base
            return Verdict(what, False,
                           f"first differing byte at 0x{offset:X} "
                           f"({'.' + what.split()[0]}+0x{relative:X})")
    return Verdict(what, True, f"{len(chunks)} chunk(s), {total} bytes")


def parse_args(argv):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("built", nargs="?", default=None,
                        help="the image to inspect (the target's built one by default)")
    parser.add_argument("--target", default=targets.DEFAULT,
                        help="the target whose manifests and retail binary this reads "
                             f"(default: {targets.DEFAULT}; known: "
                             f"{', '.join(targets.names())})")
    parser.add_argument("--retail", default=None,
                        help="the reference image the built one is compared against "
                             "(default: the target's retail binary)")
    parser.add_argument("--tu", default=None,
                        help="report one translation unit instead of the first difference")
    parser.add_argument("--cus", default=None, type=pathlib.Path)
    parser.add_argument("--chunks", default=None, type=pathlib.Path)
    parser.add_argument("--symbols", default=None, type=pathlib.Path)
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(sys.argv[1:] if argv is None else argv)
    try:
        target = targets.get(args.target)
    except targets.UnknownTarget as exc:
        print(f"g2: {exc}", file=sys.stderr)
        return 2
    built = pathlib.Path(args.built) if args.built else target.built
    retail = pathlib.Path(args.retail) if args.retail else target.elf
    cus = args.cus or target.cus
    chunks = args.chunks or target.chunks
    symbols = args.symbols or target.symbols
    for path in (built, retail):
        if not path.is_file():
            print(f"g2: {path}: no such file", file=sys.stderr)
            return 2
    # A verdict is a statement about a span of *this* target's image, so it needs the target's
    # geometry: an unmeasured target stops here, loudly, instead of borrowing a span.
    try:
        geometry = target.geometry_required()
    except targets.NotMeasured as exc:
        print(f"g2: {exc}", file=sys.stderr)
        return 2
    if args.tu is not None:
        try:
            tu, report = verdicts(built, retail, args.tu, cus, chunks, symbols, geometry)
        except UnknownUnit as exc:
            print(f"g2: {exc}", file=sys.stderr)
            return 2
        for verdict in report:
            print(f"{tu}: {verdict.what} {'ok' if verdict.ok else 'FAIL'} ({verdict.detail})")
        return 0 if all(verdict.ok for verdict in report) else 1
    located = localise(built, retail, cus, chunks, symbols, geometry)
    if located is None:
        print(f"ok: {built} and {retail} have no first difference")
        return 0
    print(describe(located))
    return 1


if __name__ == "__main__":
    sys.exit(main())
