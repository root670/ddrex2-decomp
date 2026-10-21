#!/usr/bin/env python3
"""line_map.py -- retail's statement map for one translation unit.

Print this **before writing code for a unit**.  It is the shape the source has to reproduce,
not a byte gate: which source lines carry code, which carry several statements, and which
numbers inside a function's span carry none at all.  A line with two rows is two statements
on one source line (a `switch` dispatch, a chained assignment); a gap is a blank line, a
comment, a declaration with no code, or a statement that was written but produced nothing.

The rows are retail's own ``.line`` records, read from the split's function chunks in the
retail image -- one chunk per function, so no compile is needed::

    python3 tools/units/line_map.py --tu src/CS/edit/ed_edit.c
    python3 tools/units/line_map.py --tu src/CS/dancemaster/dmm_chara.c --target ddrex2p --raw
    python3 tools/units/line_map.py --tu src/CS/shop/shop_list.c --json

Each record is ``(line, position, address delta)``; the last record of every table is the
line-0 end marker.  ``--raw`` prints every record in order, ``--json`` the same map for
tooling.  Brace hints compare the numbers with the unit's current source, and are omitted
when that source is absent or still carries ``#line`` directives (the numbers would then be
retail's, not the file's).
"""

from __future__ import annotations

import argparse
import collections
import dataclasses
import json
import pathlib
import re
import sys
from typing import NamedTuple

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from toolchain import compile as cc, debug_adopt, line_reflow  # noqa: E402

#: Width the signal lists wrap at, so one pathological function does not run off the page.
WIDTH = 96
#: A JSON array of integers on one line, so ``--json`` rows stay readable.
_NUMERIC_LIST = re.compile(r"\[\s+(-?\d+(?:,\s+-?\d+)*)\s+\]")
#: How many gaps a line may list before the tail is summarised.  A span can have dozens of
#: blank/comment lines; the count is what matters once the shape is clear.
GAP_LIMIT = 24


class Row(NamedTuple):
    """One ``.line`` record: the source line, the position word, the address delta."""

    line: int
    position: int
    delta: int

    @property
    def is_end(self) -> bool:
        """Whether this is the table's line-0 end marker."""
        return self.line == 0


@dataclasses.dataclass(frozen=True)
class FunctionMap:
    """One function's retail statement table and where the function sits."""

    name: str
    address: int
    size: int
    tables: int
    base: int
    rows: tuple

    @property
    def end(self) -> int:
        return self.address + self.size

    @property
    def words(self) -> int:
        """Retail instruction words; MIPS32, so the function's size in words."""
        return self.size // 4

    @property
    def statements(self) -> tuple:
        """The rows that name a source line (the end marker excluded)."""
        return tuple(row for row in self.rows if not row.is_end)

    @property
    def lines(self) -> tuple:
        """The source lines carrying at least one row, sorted."""
        return tuple(sorted({row.line for row in self.statements}))

    @property
    def span(self):
        """``(min, max)`` of the statement lines, or None for a function with no rows."""
        lines = self.lines
        return (lines[0], lines[-1]) if lines else None


@dataclasses.dataclass(frozen=True)
class UnitMap:
    """A unit's functions, in address order, plus the source the brace hint reads."""

    unit: str
    target: str
    elf: str
    functions: tuple
    source: tuple | None
    source_note: str | None


# ---------------------------------------------------------------------------
# measurement
# ---------------------------------------------------------------------------


def _source(tu) -> tuple:
    """``(lines, note)``: the unit's current source for brace hints, or why it is unusable.

    Line numbers in retail's table are the source's own, so a file that still carries
    ``#line`` directives cannot be read by physical line; the hint is omitted rather than
    guessed.  A file that does not exist yet is the normal state of a unit not started.
    """
    path = REPO_ROOT / tu.file
    try:
        text = path.read_text(encoding="latin-1")
    except OSError:
        return None, f"no source at {tu.file}; brace hints omitted"
    if line_reflow.has_directives(text):
        return None, f"{tu.file} carries #line; brace hints omitted"
    return tuple(text.splitlines()), None


#: A top-level function definition: column 0, a parenthesised name, and no prototype ``;``.
_IDENTIFIER = re.compile(r"([A-Za-z_][A-Za-z0-9_]*)\s*$")
#: A word that is never a function's name, so a declaration cannot be mistaken for one.
_NOT_A_NAME = frozenset((
    "int", "void", "char", "short", "long", "float", "double", "unsigned", "signed",
    "struct", "union", "enum", "const", "static", "extern", "if", "for", "while", "switch",
    "return", "sizeof", "typedef"))


def _definitions(source) -> list:
    """``[(line, name)]`` for the top-level function definitions a source spells.

    A line is a definition when it starts in column 0, names a function before a ``(``, and
    opens a body with ``{`` on the same line (or the next non-blank one).  A prototype's
    ``;``, an initialiser's ``=`` and a non-name keyword are rejected; a multi-line signature
    that fails the test only makes the alignment check more cautious.
    """
    found = []
    for number, text in enumerate(source, start=1):
        stripped = text.strip()
        if not text or text[0].isspace() or stripped.startswith("#") or "(" not in text:
            continue
        opens = "{" in text
        if opens:
            if ";" in text[:text.index("{")] or "=" in text[:text.index("{")]:
                continue
        else:
            if stripped.endswith(";") or "=" in text:
                continue
            following = next((line for line in source[number:] if line.strip()), "")
            if "{" not in following:
                continue
        match = _IDENTIFIER.search(text.split("(", 1)[0])
        if match is None or match.group(1) in _NOT_A_NAME:
            continue
        found.append((number, match.group(1)))
    return found


def _aligned(functions, source) -> bool:
    """Whether every function's retail span falls inside the source body of the same name.

    A reconstructed source that orders its functions differently (or inserts lines the
    retail build did not have) still compiles, but its physical lines no longer answer to
    retail's numbers.  Reading a brace off the wrong line would be worse than not hinting.
    """
    definitions = _definitions(source)
    starts = {name: number for number, name in definitions}
    bounds = [number for number, _name in definitions] + [len(source) + 1]
    for function in functions:
        if function.span is None:
            continue
        number = starts.get(function.name)
        if number is None:
            return False
        following = next(bound for bound in bounds if bound > number)
        if not (number <= function.span[0] and function.span[1] < following):
            return False
    return True


def _display(path) -> str:
    path = pathlib.Path(path)
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _function_map(function, chunk: bytes) -> FunctionMap:
    """One function's map from its own ``.line`` chunk (one table, in retail's format)."""
    tables = debug_adopt.line_rows(chunk)
    rows = tuple(Row(*row) for _offset, _base, table in tables for row in table)
    base = tables[0][1] if tables else function.address
    return FunctionMap(function.name, function.address, function.size, len(tables), base, rows)


def _unit_name(name: str) -> str:
    """The repo-relative spelling of ``name``, so an absolute path still matches the manifest."""
    path = pathlib.Path(name)
    if path.is_absolute():
        try:
            return str(path.resolve().relative_to(REPO_ROOT))
        except ValueError:
            return str(path)
    return path.as_posix()


def collect(unit: str, target) -> UnitMap:
    """Read ``unit``'s function splits and their ``.line`` chunks from ``target``'s retail image.

    ``unit`` is what the build's ``--tu`` accepts: a repo path, a path tail or a file name.
    No compiler and no generated tree is touched -- the manifest's function records and the
    retail ELF are the whole input.
    """
    manifests = cc.Manifests(target)
    tu = manifests.tu_named(_unit_name(unit))
    retail = cc.retail_bytes(tu, target.elf)["line"]
    functions = []
    for function in sorted(tu.functions, key=lambda f: f.address):
        start = function.line_offset - tu.line_offset
        if start < 0 or start + function.line_size > len(retail):
            raise cc.Unusable(f"{tu.file}: {function.name}'s .line chunk is outside the "
                              f"unit's run of chunks")
        functions.append(_function_map(function, retail[start:start + function.line_size]))
    source, note = _source(tu)
    if source is not None and not _aligned(functions, source):
        source = None
        note = (f"{tu.file}'s layout does not answer to retail's line numbers "
                f"(functions reordered or lines moved); brace hints omitted")
    return UnitMap(tu.file, getattr(target, "name", "?"), _display(target.elf), tuple(functions),
                   source, note)


# ---------------------------------------------------------------------------
# the signals
# ---------------------------------------------------------------------------


def multi_rows(function: FunctionMap) -> list:
    """``[(first, last, count)]``: runs of consecutive lines that carry ``count`` rows.

    A run is merged when the count is equal, so ``460x2 461x2`` prints as ``460-461x2``.
    Every line carrying more than one row is represented.
    """
    counts = collections.Counter(row.line for row in function.statements)
    runs = []
    for line in sorted(counts):
        count = counts[line]
        if count < 2:
            continue
        if runs and runs[-1][1] == line - 1 and runs[-1][2] == count:
            runs[-1][1] = line
        else:
            runs.append([line, line, count])
    return [tuple(run) for run in runs]


def gaps(function: FunctionMap) -> list:
    """``[(first, last)]``: span lines with no statement row, inclusive."""
    lines = function.lines
    return [(before + 1, after - 1)
            for before, after in zip(lines, lines[1:]) if after > before + 1]


def braces(function: FunctionMap, source) -> list | None:
    """Source lines with a row whose text contains ``{`` or ``}``, or None without a source.

    The prologue sits on the function's opening line and a ``switch`` dispatch on its
    ``switch (...) {`` line, so these rows are the structural anchors of the map.
    """
    if source is None:
        return None
    found = []
    for line in function.lines:
        if line <= len(source) and ("{" in source[line - 1] or "}" in source[line - 1]):
            found.append(line)
    return found


def signals(function: FunctionMap, source) -> dict:
    """Every hint for one function, as JSON-ready lists."""
    return {
        "multi": [[first, last, count] for first, last, count in multi_rows(function)],
        "gaps": [[first, last] for first, last in gaps(function)],
        "braces": braces(function, source),
    }


# ---------------------------------------------------------------------------
# rendering
# ---------------------------------------------------------------------------


def _token(first: int, last: int, count=None) -> str:
    span = str(first) if first == last else f"{first}-{last}"
    return span if count is None else f"{span}x{count}"


def _wrapped(label: str, tokens, width: int = WIDTH) -> list:
    """``label`` plus ``tokens``, wrapped with a hanging indent; nothing for no tokens."""
    head = f"    {label:<6}"
    lines, current = [], head
    for token in tokens:
        addition = token if current == head else " " + token
        if current != head and len(current) + len(addition) > width:
            lines.append(current)
            current = " " * len(head) + token
        else:
            current += addition
    if current != head:
        lines.append(current)
    return lines


def _span_text(function: FunctionMap) -> str:
    span = function.span
    return "-" if span is None else f"{span[0]}..{span[1]}"


def render(unit: UnitMap) -> str:
    """The default map: one summary and its hints per function, under ~40 lines per unit."""
    lines = [
        f"{unit.unit} — retail statement map ({unit.target})",
        "rows: retail .line records, one per statement site (each table ends with a line-0 "
        "marker);",
        "multi: a source line with more than one row (several statements, or a dispatch);",
        "gap: a line inside the span with no row (blank, comment, or no code);",
        "brace: a row on a source line containing { or }; words: retail size in words.",
    ]
    if unit.source_note:
        lines.append(f"note: {unit.source_note}.")
    lines.append("")
    name_width = max([len("function")] + [len(f.name) for f in unit.functions])
    lines.append(f"  {'function':<{name_width}}  {'VA range':<21}  {'words':>6}  "
                 f"{'lines':<11}  {'rows':>5}  {'tables':>6}")
    for function in unit.functions:
        lines.append(
            f"  {function.name:<{name_width}}  "
            f"0x{function.address:08X}..0x{function.end:08X}  "
            f"{function.words:>6}  {_span_text(function):<11}  "
            f"{len(function.rows):>5}  {function.tables:>6}")
        hint = signals(function, unit.source)
        multi = [_token(first, last, count) for first, last, count in hint["multi"]]
        lines.extend(_wrapped("multi", multi))
        gap_tokens = [_token(first, last) for first, last in hint["gaps"]]
        if len(gap_tokens) > GAP_LIMIT:
            extra = len(gap_tokens) - GAP_LIMIT
            gap_tokens = gap_tokens[:GAP_LIMIT] + [f"(+{extra} more)"]
        lines.extend(_wrapped("gaps", gap_tokens))
        if hint["braces"]:
            lines.extend(_wrapped("brace", [str(line) for line in hint["braces"]]))
    return "\n".join(lines) + "\n"


def render_raw(unit: UnitMap) -> str:
    """Every row in order, including each table's line-0 end marker."""
    lines = []
    for function in unit.functions:
        lines.append(f"{function.name} 0x{function.address:08X}..0x{function.end:08X}  "
                     f"{function.words} words, {function.tables} table(s), "
                     f"{len(function.rows)} rows")
        for row in function.rows:
            label = "end" if row.is_end else f"line {row.line}"
            lines.append(f"  {label:<8} +0x{row.delta:04X}  pos 0x{row.position:04X}")
    return "\n".join(lines) + "\n"


def as_json(unit: UnitMap) -> str:
    """The same map for tooling: every row, every signal, no text formatting."""
    document = {
        "unit": unit.unit,
        "target": unit.target,
        "elf": unit.elf,
        "source": None if unit.source_note else unit.unit,
        "source_note": unit.source_note,
        "functions": [
            {
                "name": function.name,
                "address": function.address,
                "end": function.end,
                "size": function.size,
                "words": function.words,
                "tables": function.tables,
                "base": function.base,
                "rows": [list(row) for row in function.rows],
                "statements": len(function.statements),
                "line_min": function.span[0] if function.span else None,
                "line_max": function.span[1] if function.span else None,
                **signals(function, unit.source),
            }
            for function in unit.functions
        ],
    }
    # Keep the leaf arrays on one line: a row or a gap is a tuple, and one number per line
    # makes a tool's input needlessly long.
    text = json.dumps(document, indent=2)
    return _NUMERIC_LIST.sub(lambda match: "[" + re.sub(r"\s+", " ", match.group(1)) + "]", text) + "\n"


# ---------------------------------------------------------------------------
# entry point
# ---------------------------------------------------------------------------


def parse_args(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--tu", required=True, metavar="PATH",
                        help="the translation unit (repo path, path tail or file name)")
    parser.add_argument("--target", default=None,
                        help="the registered target (default: this tree's)")
    output = parser.add_mutually_exclusive_group()
    output.add_argument("--raw", action="store_true", help="print every .line row in order")
    output.add_argument("--json", action="store_true", help="print the map as JSON")
    return parser.parse_args(argv)


def resolve_target(name=None):
    """The target ``--target`` names (a seam the tests use in place of the registry)."""
    from config import targets

    return targets.get(name)


def main(argv=None) -> int:
    args = parse_args(argv)
    from config import targets

    try:
        target = resolve_target(args.target)
        unit = collect(args.tu, target)
    except targets.UnknownTarget as exc:
        print(f"line_map: {exc}", file=sys.stderr)
        return 2
    except (cc.Unusable, debug_adopt.Refused, OSError) as exc:
        print(f"line_map: {exc}", file=sys.stderr)
        return 2

    text = as_json(unit) if args.json else (render_raw(unit) if args.raw else render(unit))
    sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
