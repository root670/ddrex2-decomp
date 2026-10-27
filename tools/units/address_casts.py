#!/usr/bin/env python3
"""address_casts.py -- fail a source that reaches a datum by a cast literal.

``AGENTS.md`` rule 3 says a promoted source never reaches an object by a hard-coded
address: a datum with no DWARF name is ``D_<ADDR>``, and the *spelling* of the address is
one of two things, never a bare number at the use site.

* It is a **real extern** when the bytes allow one: ``extern int D_006B47F0[];``, used as
  ``D_006B47F0[0]``.  The address is then the linker's, the symbol table carries it, and
  ``objdiff`` can name the reference.
* It is **one file-scope ``#define`` named for the address** when they do not:
  ``#define D_0102FE88 (*(char *)0x0102FE88)``.  Wrapping the access in that macro is
  byte-identical *by construction* -- the tokens the compiler sees are the old ones --
  which is exactly what a body needs when retail materialises the address per use.

The second form is not the default and not a convenience: the extern is preferred wherever
the bytes permit it, and the macro is the measured answer to one compiler shape.  Measured
on ``ddrex2p`` (``net_game_logout``, ``D_0102FE88``): a plain extern, a ``volatile`` extern
and ``extern char D_0102FE88[]`` all leave the *same* residue -- four differing words,
``beq ...$zero,+3`` against ``+2`` and ``lui $at,0x103`` against ``nop`` -- because retail
re-emits the ``lui`` in two branch delay slots and a symbol lets the compiler CSE the
``%hi``.  The named ``#define`` over the constant is 8/8 exact.

So the rule this tool enforces, in order of preference:

1. an inline cast literal outside a ``#define`` is refused: reach it through a symbol;
2. a ``#define D_<ADDR>`` whose address *also* has a ``unit_symbols.txt`` record for this
   source is refused -- the extern is available and preferred, and the macro is only the
   answer when the extern changes a word;
3. a ``#define D_<ADDR>`` with no such record is allowed, and the recipe is on the message:
   try the extern with ``measure.py`` and keep the macro only for the delay-slot shape.

That is the only justification a site may carry -- there is no allowlist of files, and a
differently-named macro (``LAST_DATA``) does not hide the address.

Two casts are findings:

* a pointer cast, ``(struct _T *)0x006D2E30`` or ``(unsigned char *)0xFC29D0``;
* a cast to a *pointer typedef*, ``(CwsWin)0x0102FBCC``, when this file (or a header it
  includes from the repository) spells ``typedef ... *CwsWin;``.  An integer cast,
  ``(int)0x10``, is a value and is left alone.

``require_named`` is what ``configure.py`` and ``compile.py`` call, so an unnameable
address can neither be configured nor compiled; the CLI is the same check over a path.

Usage::

    python3 tools/units/address_casts.py src/CS/freeplay/fp_qmenu.c
    python3 tools/units/address_casts.py --check src/**/*.c

Exit codes: 0 every file is clean, 1 a cast literal was found, 2 unusable invocation or an
unreadable file.
"""

from __future__ import annotations

import argparse
import functools
import pathlib
import re
import sys
from typing import NamedTuple

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]

#: ``(<type words> *)<address>`` -- a pointer cast whose operand is a hex literal, so the
#: cast is the access.  ``volatile``/``struct``/a typedef all spell as words and one or more
#: ``*`` are required: ``(unsigned int)0x10000003`` is a value, not an address.
_POINTER_CAST = re.compile(
    r"\(\s*[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\*+\s*\)\s*\(?\s*"
    r"0[xX]([0-9A-Fa-f]+)[uUlL]*\b")

#: ``(<name>)<address>`` -- a cast to one identifier, which is a finding only when that
#: identifier is a pointer typedef (:func:`pointer_typedefs`).
_NAME_CAST = re.compile(r"\(\s*([A-Za-z_]\w*)\s*\)\s*\(?\s*0[xX]([0-9A-Fa-f]+)[uUlL]*\b")

#: ``typedef ... *Name;`` -- the pointer typedefs a cast may hide behind.
_POINTER_TYPEDEF = re.compile(
    r"\btypedef\b[^;{}]*?\*\s*(?:const\s+)?([A-Za-z_]\w*)\s*;")

#: ``#define D_<hex> ...`` at the start of a logical line.
_DEFINE = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)")

#: A macro name that *is* an address: ``D_006D2E30``, ``D_824450``.
_ADDRESS_NAME = re.compile(r"^D_([0-9A-Fa-f]+)$")

#: ``#include "<path>"`` -- a quoted include is a repository path; a system header is not
#: followed (its typedefs are not the unit's evidence).
_INCLUDE = re.compile(r'(?m)^[ \t]*#[ \t]*include[ \t]+"([^"]+)"')


class CastLiteral(NamedTuple):
    """One cast literal: where it is, the address, the text, and why it is refused."""

    line: int
    address: int
    text: str
    named: bool           # a ledger already gives the address a D_ name
    recorded: bool        # unit_symbols.txt has a record for this address *and this source*
    in_define: bool       # the site sits inside a #define named for its address


class CastAddress(Exception):
    """A cast literal the rule refuses; the message is the remedy."""

    def __init__(self, finding: CastLiteral, count: int, what: str = "source"):
        self.finding = finding
        self.count = count
        super().__init__(
            f"{what}: line {finding.line}: {finding.text} reaches an object by a cast "
            f"literal, not by name -- {remedy(finding)} ({count} cast literal(s) in this "
            f"file)")


#: The measurement a macro has to survive: the extern is the default, and only this shape
#: makes the macro the right answer.
DELAY_SLOT = ("Measured: a real symbol CSEs the %hi and retail re-emits the lui in two "
              "branch delay slots, so D_0102FE88 as an extern cost four words "
              "(beq ...$zero,+3 against +2) while the macro was 8/8 exact")


def remedy(finding: CastLiteral) -> str:
    """The spelling a site may take, and the measurement that decides between them."""
    name = f"D_{finding.address:08X}"
    if finding.in_define:
        return (f"`#define {name}` also has a unit_symbols.txt record for this source, so "
                f"the extern is available and preferred: declare `extern <type> {name};` (an "
                f"array for a datum, the pointer type for a slot), use it as a value, and "
                f"delete the macro -- keep the macro only if measure.py says the extern "
                f"changes a word ({DELAY_SLOT})")
    existing = (f"the ledgers already name it: use {name}" if finding.named else
                f"add `{name} = 0x{finding.address:08X}; // source:<file>` to that target's "
                f"unit_symbols.txt and declare it")
    return (f"(1) use the symbol -- {existing}; a real extern is the default because the "
            f"symbol table and objdiff then carry the reference; or (2) with no record, one "
            f"file-scope `#define {name} ...` whose body holds this address. The macro is "
            f"the exception, not the convenience: {DELAY_SLOT} -- run "
            f"python3 tools/units/measure.py on the unit before choosing it")


def _line_of(text: str, offset: int) -> int:
    return text.count("\n", 0, offset) + 1


def _mask(text: str) -> str:
    """``text`` with comments and the contents of literals blanked, newlines kept.

    A hex literal in a string or a comment is not code.  The mask has the same length as
    ``text``, so an offset into it is an offset into the source and the line number is the
    source's own.
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


def _logical_lines(masked: str):
    """``(start, end, text)`` for every logical line, backslash continuations joined."""
    start, index, length = 0, 0, len(masked)
    while index <= length:
        at_end = index == length
        if at_end or masked[index] == "\n":
            end = index
            text = masked[start:end]
            while text.rstrip().endswith("\\") and end + 1 <= length:
                end += 1
                next_break = masked.find("\n", end)
                if next_break < 0:
                    next_break = length
                text = masked[start:next_break]
                index = next_break
                if next_break == length:
                    break
            yield start, min(index + 1, length), text
            start = index + 1
        index += 1


def named_defines(masked: str) -> tuple:
    """``(start, end, address)`` for each ``#define D_<ADDR>``, address from the name.

    The *name* decides which address the macro may hold, so a define that wraps two
    literals justifies only the one its name spells and the other stays a finding.
    """
    found = []
    for start, end, text in _logical_lines(masked):
        match = _DEFINE.match(text)
        if match is None:
            continue
        named = _ADDRESS_NAME.match(match.group(1))
        if named is None:
            continue
        found.append((start, end, int(named.group(1), 16)))
    return tuple(found)


def _included_text(path: pathlib.Path, text: str, seen: set, depth: int = 0) -> dict:
    """``{name: words}`` spellings of the pointer typedefs this file can see.

    Only quoted includes are followed, and only where they resolve inside the repository:
    a unit's typedef comes from a header under ``src/`` or ``include/``, whose path is the
    same absolute-ish spelling the source uses.  A system header's ``typedef`` is not
    evidence about this target.  The include is read from the raw text (the mask blanks the
    contents of a string literal, which is where the path is spelt) and the typedefs from
    its masked text, so a commented-out ``typedef`` declares nothing.
    """
    names = {}
    for match in _POINTER_TYPEDEF.finditer(_mask(text)):
        names[match.group(1)] = names.get(match.group(1), 0) + 1
    if depth >= 2:
        return names
    for relative in _INCLUDE.findall(text):
        candidate = None
        for base in (path.parent / relative, REPO_ROOT / relative,
                     REPO_ROOT / "include" / relative):
            if base.is_file():
                candidate = base
                break
        if candidate is None or not candidate.is_file():
            continue
        resolved = candidate.resolve()
        if resolved in seen:
            continue
        seen.add(resolved)
        try:
            inner = resolved.read_bytes().decode("latin-1")
        except OSError:
            continue
        for name, count in _included_text(resolved, inner, seen, depth + 1).items():
            names[name] = names.get(name, 0) + count
    return names


def pointer_typedefs(text: str, path=None) -> set:
    """Every name this source casts to that a typedef declares as a pointer."""
    seen = set()
    return set(_included_text(pathlib.Path(path) if path else pathlib.Path("."), text,
                              seen))


def cast_literals(text: str, path=None) -> tuple:
    """Every unjustified cast literal in ``text``, in source order."""
    masked = _mask(text)
    defines = named_defines(masked)
    pointers = pointer_typedefs(text, path)
    sites = []
    for match in _POINTER_CAST.finditer(masked):
        sites.append((match.start(), match.end(), int(match.group(1), 16)))
    for match in _NAME_CAST.finditer(masked):
        if match.group(1) in pointers:
            sites.append((match.start(), match.end(), int(match.group(2), 16)))
    recorded = _unit_symbol_records(_repo_relative(path))
    found = []
    for start, end, address in sorted(sites):
        in_define = any(lo <= start < hi and address == named
                        for lo, hi, named in defines)
        if in_define and address not in recorded:
            continue        # the named macro is the justification, and no extern exists
        found.append(CastLiteral(_line_of(text, start), address,
                                 " ".join(masked[start:end].split()),
                                 _named_in(path, address),
                                 address in recorded, in_define))
    return tuple(found)


def _repo_relative(path) -> str | None:
    """The source path as the ledgers spell it (``src/...``), or ``None`` without one."""
    if path is None:
        return None
    resolved = pathlib.Path(path)
    try:
        resolved = resolved.resolve()
    except OSError:
        return None
    try:
        return resolved.relative_to(REPO_ROOT).as_posix()
    except ValueError:
        return None


@functools.lru_cache(maxsize=8)
def _unit_symbol_records(source: str | None) -> frozenset:
    """The addresses ``unit_symbols.txt`` records *for ``source``* -- the extern rows.

    Only the source's own rows count: a record names the unit that defines the datum, and
    :func:`toolchain.compile.Manifests.unit_symbols` resolves the reference through it.  So
    a row for this source is the proof that the extern exists and works for this file.
    """
    if source is None:
        return frozenset()
    addresses = set()
    for ledger in sorted((REPO_ROOT / "config").glob("*/unit_symbols.txt")):
        try:
            text = ledger.read_bytes().decode("latin-1")
        except OSError:
            continue
        for match in re.finditer(
                r"(?m)^\s*(\w+)\s*=\s*0[xX]([0-9A-Fa-f]+)\s*;\s*//\s*source:(\S+)", text):
            if match.group(3) == source:
                addresses.add(int(match.group(2), 16))
    return frozenset(addresses)


@functools.lru_cache(maxsize=64)
def _ledger_text() -> str:
    """Every target ledger's text, once: the ``D_`` names the repository already carries."""
    chunks = []
    for pattern in ("*/symbol_addrs.txt", "*/unit_symbols.txt", "*/splat_symbol_addrs.txt",
                    "*/undefined_syms_auto.txt"):
        for ledger in sorted((REPO_ROOT / "config").glob(pattern)):
            try:
                chunks.append(ledger.read_bytes().decode("latin-1"))
            except OSError:
                continue
    return "\n".join(chunks)


def _named_in(the_path, address: int) -> bool:
    """Whether a ledger already gives ``address`` a ``D_`` name.

    The answer only shapes the remedy's words ("use the name it has" vs "add the row"), so
    it reads the target ledgers the repository carries: ``config/*/symbol_addrs.txt``,
    ``unit_symbols.txt``, ``splat_symbol_addrs.txt`` and ``undefined_syms_auto.txt``.
    """
    if the_path is None:
        return False
    return re.search(rf"\bD_0*{address:X}\b", _ledger_text(), re.IGNORECASE) is not None


def require_named(text: str, what: str = "source", path=None) -> None:
    """Raise :class:`CastAddress` on the first unjustified cast literal in ``text``.

    ``what`` names the file in the message; the count is the whole file's, so one run names
    every site that has to go rather than the first alone.  ``path`` is the file the text
    came from, used only to say whether the ledgers already name the address.
    """
    findings = cast_literals(text, path)
    if findings:
        raise CastAddress(findings[0], len(findings), what)


def report(text: str, what: str, path=None) -> list:
    """One line per finding, each carrying the file, the line, the text and the remedy."""
    return [f"{what}:{finding.line}: {finding.text} -- {remedy(finding)}"
            for finding in cast_literals(text, path)]


def check_file(path) -> tuple:
    """``(findings, error)``: the finding lines and, for an unreadable file, the error."""
    path = pathlib.Path(path)
    try:
        text = path.read_bytes().decode("latin-1")
    except OSError as exc:
        return (), f"{path}: cannot be read ({exc})"
    return tuple(report(text, path.as_posix(), path)), None


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(prog="address_casts.py", description=__doc__.splitlines()[0])
    parser.add_argument("--check", action="store_true",
                        help="gate mode: silent per clean file, one line per finding")
    parser.add_argument("sources", nargs="+", help="the C sources to check")
    args = parser.parse_args(argv)
    failed = 0
    for name in args.sources:
        path = pathlib.Path(name)
        findings, error = check_file(path)
        if error is not None:
            print(f"address_casts.py: error: {error}", file=sys.stderr)
            return 2
        if findings:
            for line in findings:
                print(f"address_casts.py: {line}", file=sys.stderr)
            failed = 1
        elif not args.check:
            print(f"address_casts.py: {path.as_posix()}: no cast literal")
    return failed


if __name__ == "__main__":
    sys.exit(main())
