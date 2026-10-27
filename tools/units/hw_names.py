#!/usr/bin/env python3
"""hw_names.py -- fail a source that spells a hardware address as a cast.

A hardware register and the VU1 memory window have a name in ``hwinclude/hw/**``, and a
unit reaches them through that header.  A cast to the absolute address at the use site is
the same access with the evidence removed: it hides which peripheral the unit touches and
puts a bare number where a documented hardware fact belongs.  ``AGENTS.md`` rule 3 forbids
a game datum reached by an address; this is the same rule for hardware, and the two ranges
it covers are

* the EE register block, ``0x10000000-0x101FFFFF`` -- the EE DMAC map is
  ``hwinclude/hw/ee_dma.h`` (channels D0-D3 and the controller's own registers);
* the VU1 memory window, ``0x70000000-0x70003FFF`` -- ``hwinclude/hw/vu1_mem.h``.

The check is about the *cast*: the address has to become an lvalue through a named macro
(``D2_TADR = x``, ``VU1_MEM_F32(0x10) = y``), which is why ``hw_names`` answers with the
header that already names the block, or -- for a block no header names yet -- with the
header to add.  An integer that merely happens to sit in one of the ranges (a GIF tag's
``0x10000003``, an MPEG buffer size) is not a cast and is left alone, and so is an address
outside both ranges (game state under ``g_sys_w``, an overlay scratch base): those are not
hardware facts, and :func:`header_for` is the single place that decides.

``require_named`` is what ``tools/units/strip_comments.py --check`` runs, so the comment
gate and the hardware-name gate are one invocation.  A file that is not a promoted source
(a draft, a header) is checked the same way; a macro *definition* lives in ``hwinclude/``
and is never scanned, which is what makes the header the one place the cast may appear.

Usage::

    python3 tools/units/hw_names.py src/gs/gs_3d.c
    python3 tools/units/hw_names.py src/**/*.c

Exit codes: 0 every file is clean, 1 a raw hardware cast was found, 2 unusable invocation.
"""

from __future__ import annotations

import argparse
import pathlib
import re
import sys
from typing import NamedTuple

#: The EE's register block, as the rule states it: every peripheral register the EE core
#: reaches by an absolute address lives inside this span.
EE_REGISTERS = (0x10000000, 0x101FFFFF)

#: VU1 data memory as the EE addresses it: 16 KiB, uncached, 128-bit aligned.
VU1_MEMORY = (0x70000000, 0x70003FFF)

#: The DMAC's two chunks inside ``EE_REGISTERS``: the channel register blocks (D0-D3, one
#: per 0x1000, registers +0x00..+0x80) and the controller's own registers at 0x1000E000.
EE_DMAC = ((0x10008000, 0x1000BFFF), (0x1000E000, 0x1000E0FF))

#: ``(<type words> *)<address>`` -- a pointer cast whose operand is a hex literal, so the
#: cast is the access.  ``volatile``/``struct``/a typedef all spell as words, and one or
#: more ``*`` are required: ``(unsigned int)0x10000003`` is a value, not an address.
_POINTER_CAST = re.compile(
    r"\(\s*[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\*+\s*\)\s*\(?\s*"
    r"0[xX]([0-9A-Fa-f]+)[uUlL]*\b")


class RawAddress(NamedTuple):
    """One raw cast: the source line, the address, and the header that should have named it."""

    line: int
    address: int
    header: str | None


def _within(address: int, span: tuple) -> bool:
    low, high = span
    return low <= address <= high


def _block(address: int) -> str:
    """The words for the peripheral block ``address`` belongs to, for a message."""
    if _within(address, VU1_MEMORY):
        return "the VU1 memory window"
    return "the EE register block"


def header_for(address: int) -> str | None:
    """The ``hwinclude`` header that names ``address``, or ``None`` when none does yet.

    This is the single decision the remedy reads: a DMAC register is ``hw/ee_dma.h``, the
    VU1 window is ``hw/vu1_mem.h``, and any other EE register has no home yet, so the
    remedy is to add one instead of guessing a name for it.
    """
    if _within(address, VU1_MEMORY):
        return "hwinclude/hw/vu1_mem.h"
    for span in EE_DMAC:
        if _within(address, span):
            return "hwinclude/hw/ee_dma.h"
    return None


def _remedy(violation: RawAddress) -> str:
    if violation.header is not None:
        return (f"include {violation.header} and reach the register through its macro "
                f"(add it there in the same lvalue shape if it is missing)")
    return (f"no header under hwinclude/hw/ names {_block(violation.address)} yet: add it "
            f"to a header there as an lvalue macro and include that")


class RawAddressCast(Exception):
    """A cast to an absolute hardware address; the message is the remedy."""

    def __init__(self, violation: RawAddress, count: int, what: str = "source"):
        self.violation = violation
        self.count = count
        super().__init__(
            f"{what}: line {violation.line}: the cast to 0x{violation.address:08X} reaches "
            f"{_block(violation.address)} by memory, not by name -- {_remedy(violation)} "
            f"({count} raw hardware cast(s) in this file)")


def _line_of(text: str, offset: int) -> int:
    return text.count("\n", 0, offset) + 1


def _mask(text: str) -> str:
    """``text`` with comments and the contents of literals blanked, newlines kept.

    A hex literal in a string or a comment is not code, and the check must not read it as
    one.  The mask has the same length as ``text``, so an offset into it is an offset into
    the source and the line number is the source's own.
    """
    out = list(text)
    index, length = 0, len(text)
    while index < length:
        char = text[index]
        if char in ('"', "'"):
            quote = char
            out[index] = " "
            index += 1
            while index < length and text[index] != quote and text[index] != "\n":
                if text[index] == "\\" and index + 1 < length and text[index + 1] != "\n":
                    out[index] = out[index + 1] = " "
                    index += 2
                    continue
                out[index] = " "
                index += 1
            if index < length and text[index] == quote:
                out[index] = " "
                index += 1
            continue
        if char == "/" and index + 1 < length and text[index + 1] == "/":
            while index < length and text[index] != "\n":
                out[index] = " "
                index += 1
            continue
        if char == "/" and index + 1 < length and text[index + 1] == "*":
            out[index] = out[index + 1] = " "
            index += 2
            while index < length and not (text[index] == "*" and index + 1 < length
                                          and text[index + 1] == "/"):
                if text[index] != "\n":
                    out[index] = " "
                index += 1
            if index < length:
                out[index] = out[index + 1] = " "
                index += 2
            continue
        index += 1
    return "".join(out)


def raw_casts(text: str) -> tuple:
    """Every cast in ``text`` whose operand is an address in one of the two ranges."""
    masked = _mask(text)
    found = []
    for match in _POINTER_CAST.finditer(masked):
        address = int(match.group(1), 16)
        if not (_within(address, EE_REGISTERS) or _within(address, VU1_MEMORY)):
            continue
        found.append(RawAddress(_line_of(text, match.start()), address, header_for(address)))
    return tuple(found)


def require_named(text: str, what: str = "source") -> None:
    """Raise :class:`RawAddressCast` on the first raw hardware cast in ``text``.

    ``what`` names the file in the message (``src/gs/gs_3d.c``); the count in the message is
    the whole file's, so one run names every cast that has to go rather than the first alone.
    """
    violations = raw_casts(text)
    if violations:
        raise RawAddressCast(violations[0], len(violations), what)


def check_file(path) -> str | None:
    """``None`` when ``path`` is clean, else the message for its first raw cast."""
    path = pathlib.Path(path)
    try:
        text = path.read_bytes().decode("latin-1")
    except OSError as exc:
        return f"{path}: cannot be read ({exc})"
    try:
        require_named(text, path.as_posix())
    except RawAddressCast as exc:
        return str(exc)
    return None


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(prog="hw_names.py", description=__doc__.splitlines()[0])
    parser.add_argument("sources", nargs="+", help="the C sources to check")
    args = parser.parse_args(argv)
    failed = 0
    for name in args.sources:
        path = pathlib.Path(name)
        if not path.is_file():
            print(f"hw_names.py: error: {name} does not exist", file=sys.stderr)
            return 2
        message = check_file(path)
        if message is not None:
            print(f"hw_names.py: {message}", file=sys.stderr)
            failed = 1
            continue
        print(f"hw_names.py: {path.as_posix()}: no raw hardware cast")
    return failed


if __name__ == "__main__":
    sys.exit(main())
