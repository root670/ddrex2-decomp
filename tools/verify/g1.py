#!/usr/bin/env python3
"""G1 -- the whole-file gate: a target's built image must equal its retail binary.

G1 is milestone M1's acceptance criterion, so it compares the two images as *files*: both
sha256 digests, and on a mismatch the first differing offset.  A bare offset is close to
useless in a multi-megabyte image that is mostly debug data, so the offset is mapped back
through the oracle's manifests (``cus.json``, ``debug_chunks.json``) to the compile unit and
the translation unit that own it -- the localisation G2 will reuse when a promoted translation
unit's bytes drift.  The manifests are the only place where byte offsets and source files
meet, which is why a ``.line`` byte names the compile unit whose statement list it belongs
to rather than a byte range.

Usage::

    python3 tools/verify/g1.py out/<elf> [--target NAME] [--retail orig/<elf>]
                                        [--expected SHA256] [--checksums PATH]

Every input is the *target's*: its retail binary, its ``checksums.txt`` (whose first record is
the pinned digest of the built image) and its manifests.  The target is named with ``--target``
and defaults to the one the tree is configured for; nothing here spells a target name or a
retail path of its own.  When the pinned digest is known the *retail* file's digest is checked
against it first, so a missing, truncated or different retail binary is reported as such
instead of being compared with.  A second record pins the retail disc image; the ISO gate
resolves it by file name through :func:`pinned_hash_for`, and this module's own gate never
needs it.
Exit codes: 0 identical, 1 they differ (or the retail binary is wrong), 2 a file is missing
or unusable.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import pathlib
import re
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
# The geometry (which sections exist, where they start and how the loadable image maps a
# file offset to a virtual address) belongs to the *target*, and is measured there once
# (`config/targets.py`); `configure.py` reads the same descriptor, so the split and this
# gate cannot disagree about it.  The names below are the default target's, because that is
# what a bare `python3 tools/verify/g1.py out/<elf>` means; every function that can be asked
# to work on another target takes it as an argument.
if str(REPO_ROOT) not in sys.path:  # run as `python3 tools/verify/g1.py` from ninja
    sys.path.insert(0, str(REPO_ROOT))
from config import targets  # noqa: E402

TARGET = targets.get(targets.DEFAULT)
RETAIL = TARGET.elf
CHECKSUMS = TARGET.checksums
SYMBOLS = TARGET.symbols
CUS = TARGET.cus
CHUNKS = TARGET.chunks


def geometry_of(target=None):
    """The geometry the gate localises with: ``target``'s own measurement, or the default's.

    Resolved when it is asked for, never at import: a target nobody has measured yet must be
    able to *import* this gate (and run the pin check, which needs no geometry at all), and
    stop only where a number nobody measured would be used.
    """
    return (target or TARGET).geometry_required()


SYMBOL_LINE = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+);")


def sha256(path) -> str:
    """Digest of a file, read in blocks: a 2.5 MB image should never be slurped whole."""
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for block in iter(lambda: handle.read(1 << 20), b""):
            digest.update(block)
    return digest.hexdigest()


def _pins(path=CHECKSUMS) -> list:
    """``(digest, target)`` per record of ``checksums.txt``, in file order.

    A record is a ``sha256sum``-style line: a 64-character digest, then the target it pins.
    Everything else in the file is ignored, so a comment costs nothing.
    """
    try:
        text = pathlib.Path(path).read_text()
    except OSError:
        return []
    pins = []
    for line in text.splitlines():
        fields = line.split(None, 1)
        if fields and len(fields[0]) == 64:
            pins.append((fields[0], fields[1].strip() if len(fields) > 1 else ""))
    return pins


def pinned_hash(path=CHECKSUMS):
    """The digest recorded in ``checksums.txt`` (``<sha256>  <target>``), or None.

    The first record wins: the manifest's first line pins the built image, which is what
    every caller of *this* function means by "the pinned hash".
    """
    pins = _pins(path)
    return pins[0][0] if pins else None


def pinned_hash_for(target, path=CHECKSUMS):
    """The digest pinned for ``target``'s file name, or None when no record names it.

    Matched by file name rather than by path: the retail disc image is mounted wherever the
    developer keeps it (``disc/`` by this repo's own convention), so a path in the manifest
    would be true on one machine only, while a name identifies the image everywhere.
    """
    name = pathlib.PurePath(str(target)).name
    if not name:
        return None
    for digest, pinned_target in _pins(path):
        if pathlib.PurePath(pinned_target).name == name:
            return digest
    return None


def _symbol_table(path=SYMBOLS):
    """``address -> name`` from the oracle's symbol file; the first record wins."""
    table = {}
    try:
        text = pathlib.Path(path).read_text()
    except OSError:
        return table
    for line in text.splitlines():
        match = SYMBOL_LINE.match(line)
        if match is not None:
            table.setdefault(int(match.group(2), 16), match.group(1))
    return table


def _first_difference(built, retail):
    """``(offset, note)`` of the first byte that differs, or ``(None, "")`` if equal.

    ``note`` is empty unless the two files simply run out at different lengths, which is
    the case a truncated or over-long build produces.
    """
    built_size, retail_size = os.path.getsize(built), os.path.getsize(retail)
    with open(built, "rb") as lhs, open(retail, "rb") as rhs:
        offset = 0
        while True:
            left, right = lhs.read(1 << 20), rhs.read(1 << 20)
            if left != right:
                for index, (one, other) in enumerate(zip(left, right)):
                    if one != other:
                        return offset + index, ""
                if built_size < retail_size:
                    note = (f" (the built file ends there: {built_size} bytes against "
                            f"{retail_size})")
                else:
                    note = (f" (the built file runs past the retail image: {built_size} "
                            f"bytes against {retail_size})")
                return offset + min(len(left), len(right)), note
            if not left:
                return None, ""
            offset += len(left)


def _chunk_at(chunks, section, relative):
    for chunk in chunks:
        if chunk.get("section") == section \
                and chunk["offset"] <= relative < chunk["offset"] + chunk["size"]:
            return chunk
    return None


def _record_at(records, relative):
    for record in records:
        if record["offset"] <= relative < record["offset"] + record["size"]:
            return record
    return None


def _describe_cu(record, symbols) -> str:
    """A compile unit as a reader can act on it: file, or the function and its address."""
    low_pc = record.get("low_pc")
    if record.get("kind") == "function" and low_pc is not None:
        name = symbols.get(low_pc) or f"func_{low_pc:08X}"
        return f"function {name} at 0x{low_pc:08X}"
    return f"{record.get('kind')} {record.get('file')}"


class Localiser:
    """Maps a file offset inside ``.debug``/``.line`` to its CU and TU.

    Built from the two committed manifests, so the mapping is the oracle's own: a CU
    record tiles a byte range of ``.debug``, a ``.debug`` chunk names the translation
    unit that range belongs to, and a ``.line`` chunk *is* one compile unit's statement
    list.  If a manifest is missing or malformed the localisation is simply empty --
    the gate itself must never depend on the diagnostic.
    """

    def __init__(self, cus_path=CUS, chunks_path=CHUNKS, symbols_path=SYMBOLS,
                 geometry=None):
        try:
            self.records = json.loads(pathlib.Path(cus_path).read_text())
            self.chunks = json.loads(pathlib.Path(chunks_path).read_text())
        except (OSError, json.JSONDecodeError, TypeError):
            self.records, self.chunks = [], []
        self.symbols = _symbol_table(symbols_path)
        self.geometry = geometry if geometry is not None else geometry_of()

    def tu_of(self, index):
        """The translation unit record that owns compile-unit record ``index``."""
        for chunk in self.chunks:
            if chunk.get("section") == ".debug" and index in (chunk.get("tunits") or []):
                return self.records[chunk["tunits"][0]]
        return None

    def describe(self, offset) -> str:
        """``""`` outside the chunked sections, else the offset's CU and TU."""
        for name, base, size in self.geometry.sections:
            if base <= offset < base + size:
                return self._in_section(name, offset - base)
        return ""

    def _in_section(self, section, relative) -> str:
        chunk = _chunk_at(self.chunks, section, relative)
        if chunk is None:
            return f" -- {section}+0x{relative:X} (no chunk declares that byte)"
        if section == ".debug":
            translation_unit = self.records[chunk["tunits"][0]]
            unit = _record_at(self.records, relative) or translation_unit
            return (f" -- .debug+0x{relative:X}: translation unit "
                    f"{translation_unit['file']}, compile unit {unit['index']} "
                    f"({_describe_cu(unit, self.symbols)})")
        unit = self.records[chunk["tunits"][0]]
        owner = self.tu_of(unit["index"])
        return (f" -- .line+0x{relative:X}: the statement list of compile unit "
                f"{unit['index']} ({_describe_cu(unit, self.symbols)}), translation unit "
                f"{owner['file'] if owner else '?'}")


def compare(built, retail, cus=CUS, chunks=CHUNKS, geometry=None) -> str:
    """``"ok"``, or the mismatch message the brief's interface promises.

    The verdict itself needs nothing but the two files: two images that differ are reported as
    differing whether or not anybody has measured the target's geometry.  The *localisation*
    does need it, so a target whose segment list has not been measured yet says exactly that
    instead of naming a translation unit from numbers nobody measured.
    """
    built, retail = pathlib.Path(built), pathlib.Path(retail)
    expected, got = sha256(retail), sha256(built)
    if expected == got:
        return "ok"
    offset, note = _first_difference(built, retail)
    where = ""
    if offset is not None:
        try:
            where = Localiser(cus, chunks, geometry=geometry).describe(offset)
        except targets.NotMeasured:
            where = (" -- the byte is not localised: this target has no measured geometry "
                     "yet (its segment list is read from its own ELF when it is placed)")
    return (f"sha256 mismatch: expected {expected} got {got} at first difference "
            f"0x{offset:X}{note}{where}")


def parse_args(argv):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("built", help="the image to verify (the target's out/<elf>)")
    parser.add_argument("--target", default=targets.DEFAULT,
                        help="the target whose retail binary and manifests this gate reads "
                             f"(default: {targets.DEFAULT}; known: "
                             f"{', '.join(targets.names())})")
    parser.add_argument("--retail", default=None,
                        help="the retail binary to compare against (default: the target's "
                             "own retail ELF)")
    parser.add_argument("--expected", default=None,
                        help="pinned sha256 the retail binary must have")
    parser.add_argument("--checksums", default=None,
                        help="file --expected is read from when it is not given "
                             "(default: the target's own)")
    parser.add_argument("--cus", default=None, type=pathlib.Path,
                        help="the target's compile-unit map")
    parser.add_argument("--chunks", default=None, type=pathlib.Path,
                        help="the target's debug chunk manifest")
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(sys.argv[1:] if argv is None else argv)
    try:
        target = targets.get(args.target)
    except targets.UnknownTarget as exc:
        print(f"g1: {exc}", file=sys.stderr)
        return 2
    built = pathlib.Path(args.built)
    retail = pathlib.Path(args.retail) if args.retail else target.elf
    if not built.is_file():
        print(f"g1: {built}: no such file", file=sys.stderr)
        return 2
    if not retail.is_file():
        print(f"g1: {retail}: the retail binary is required to verify the build",
              file=sys.stderr)
        return 2
    expected = args.expected or pinned_hash(args.checksums or target.checksums)
    got = sha256(retail)
    if expected and got != expected:
        print(f"g1: {retail} has sha256 {got} ({retail.stat().st_size} bytes), but the "
              f"pinned hash is {expected}: the retail binary is missing, truncated or a "
              f"different version", file=sys.stderr)
        return 1
    # `target.geometry` may be None: the verdict does not need it, and `compare` says so in
    # the one place the localisation would have used it.
    message = compare(built, retail,
                      args.cus or target.cus, args.chunks or target.chunks, target.geometry)
    print(message if message != "ok" else f"ok: {built} is {sha256(built)}")
    return 0 if message == "ok" else 1


if __name__ == "__main__":
    sys.exit(main())
