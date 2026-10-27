#!/usr/bin/env python3
"""m2c_draft.py -- a mechanical first draft of one function, seeded by its split.

``m2c`` (matt-kempster/m2c, fetched and digest-pinned by ``tools/toolchain/fetch.py``)
turns assembly into plausible C.  It is a *drafting* aid, never a promotion proof: it
emits ``unk24`` fields, unrolled loops and ``var_N`` temporaries, and this tree's
promotion gate is byte equality (``./ddr verify --tu <tu>``).  What it is good for is
the part that takes longest to get wrong -- the control flow and the call/argument
shape of a hard function -- so a draft is something to edit, not something to trust.

The draft is written to **stdout**, or to ``drafts/`` with ``--out``; no path under
``src/``, ``include/`` or ``asm/`` is accepted, because ``asm/`` is generated (rule 2)
and ``src/`` is the hand-written tree.

Example::

    python3 tools/units/m2c_draft.py AM/s573/doll/ps1lib.c GsInitCoordinate2
    python3 tools/units/m2c_draft.py src/AM/s573/doll/ps1lib.c ps1rsin --out drafts/ps1rsin.c

What is fed to m2c:

* **the function's own split** -- the ``glabel <fn>`` .. ``endlabel <fn>`` block, with
  the preamble (``.include``/``.set``) the split needs, out of
  ``asm/nonmatchings/<segment>/<fn>.s`` (a generated tree; ``./ddr build`` writes it);
* **the types this tree already knows** -- ``include/src/<unit>.h`` and the
  ``include/types/*.h`` headers it includes, flattened for m2c's C parser (it wants a
  preprocessed context).  That is the same evidence a person gathers by hand, so the
  draft's argument and member types are retail's, not invented.

A function whose split is ``dlabel`` (DWARF says subroutine, the bytes are data) is
refused: m2c cannot decompile it, and the refusal is the finding.

**A jump-table dispatch is fed its table.**  A body that ends in ``jr $reg`` (not ``jr $31``)
reads a case address out of a table, and m2c refuses the whole function with *"the
corresponding jump table is not provided"* unless that table is in the assembly it parses: it
looks back from the ``jr`` for a ``%lo(...)``/``%l(...)`` macro naming a symbol that starts
with ``jtbl``/``jpt_``/``jumptable_``/``lbl_``, then wants that symbol *defined* as data, one
word per case label.  A split carries the dispatch but not the table -- the table sits outside
the function -- so this tool reads the words out of the retail ELF at the address the symbol
names (``jtbl_002D7110`` -> ``0x002D7110``), writes them to a second ``.s`` file, and adds the
case labels the split lacks (splat labels branch targets, not table entries).  A body with no
table is handed to m2c byte-for-byte as before.

Dependencies: none to install.  m2c is pure Python and vendors its own pycparser fork
(BSD-3-Clause) inside the pinned tree; its only declared dependency, ``graphviz``, is used
by ``--visualize`` alone, which this tool never passes.  ``python3 tools/toolchain/fetch.py
m2c`` is the whole setup, and the tree it installs is digest-verified before it runs.
"""

from __future__ import annotations

import argparse
import bisect
import dataclasses
import os
import pathlib
import re
import subprocess
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from toolchain import fetch  # noqa: E402

#: m2c's PS2 triple: little-endian MIPS (EE), Metrowerks compiler, C.
M2C_TARGET = "mipsee-mwcc-c"

#: Where a draft may be written -- nowhere the build reads.
OUTPUT_DIR = "drafts"
REFUSED_DIRS = ("src", "include", "asm", "config", "build", "out")

#: One ``#include "..."`` line and one preprocessor directive, for the context flattener.
_INCLUDE = re.compile(r'\s*#\s*include\s+"([^"]+)"\s*')
_DIRECTIVE = re.compile(r"\s*#")
_GLABEL = re.compile(r"\s*glabel\s+(\S+)\s*")
_DLABEL = re.compile(r"\s*dlabel\s+(\S+)\s*")

#: m2c finds a jump table through the *name* a ``%lo(...)``/``%l(...)`` macro references: it
#: walks back from the ``jr $reg`` through the current and parent blocks for a name with one
#: of these prefixes, then requires that name to be defined as data in the assembly it parses.
JTBL_PREFIXES = ("jtbl", "jpt_", "jumptable_", "lbl_")

#: A split's instruction comment: ``/* 16A594 0026A394 2D00033C */`` -- the ROM offset, the
#: virtual address, and the encoded word.  The address is what ties a table entry to a line.
_INSTRUCTION = re.compile(r"/\* +([0-9A-Fa-f]+) +([0-9A-Fa-f]+) +([0-9A-Fa-f]+) +\*/")

#: The table's own symbol, as the ``lui``/``addiu`` pair before the dispatch spells it.
_LO_SYMBOL = re.compile(r"%l(?:o)?\(\s*(\S+?)\s*\)")

#: ``jr $2``: a dispatch; ``jr $31`` is the function's return and dispatches through nothing.
_JR = re.compile(r"\bjr\s+\$(\w+)")

#: ``sltiu $1, $2, 0xD``: the compiler's bounds check, whose immediate is the table's length.
_SLTIU = re.compile(r"\bsltiu\s+\$\w+\s*,\s*\$(\w+)\s*,\s*(0x[0-9A-Fa-f]+|\d+)")

#: ``  .L0026A408:`` -- a standalone label line, which is where a case block begins.
_LABEL = re.compile(r"\s*([A-Za-z_.$][\w.$]*):\s*")

#: A table's name carries its address: ``jtbl_002D7110`` -> ``0x002D7110``.
_SYMBOL_ADDRESS = re.compile(r"_([0-9A-Fa-f]{6,8})$")

#: The most entries one table is allowed to grow to when the split shows no bound.
TABLE_LIMIT = 1024


class DraftError(Exception):
    """The draft cannot be produced, and the message says what to do instead."""


def _case_label(address: int) -> str:
    """The label a case address gets when the split does not already name it."""
    return f".L{address:08X}"


def _display(path: pathlib.Path) -> str:
    """``path`` relative to the repository when it is inside it."""
    path = path.resolve()
    return str(path.relative_to(REPO_ROOT)) if path.is_relative_to(REPO_ROOT) else str(path)


def unit_key(unit: str, target) -> str:
    """``src/AM/s573/doll/ps1lib.c`` -> ``AM/s573/doll/ps1lib`` (the header's own key)."""
    candidate = pathlib.Path(unit)
    if candidate.is_absolute():
        candidate = candidate.relative_to(REPO_ROOT) if candidate.is_relative_to(REPO_ROOT) else candidate
    parts = list(candidate.parts)
    if parts and parts[0] == "src":
        parts = parts[1:]
    if not parts:
        raise DraftError(f"{unit!r} names no unit: pass the path as `src/<dir>/<unit>.c` or `<dir>/<unit>.c`")
    if parts[-1].endswith(".c"):
        parts[-1] = parts[-1][: -len(".c")]
    key = "/".join(parts)
    header = unit_header(key, target)
    if header is None:
        raise DraftError(
            f"{unit!r} has no generated header under "
            f"{' or '.join(_display(p / 'src') for p in target.include_paths)}: the unit is "
            f"unknown to the oracle, or its headers are stale -- run `./ddr oracle` (or "
            f"`./ddr build`, which runs it) and check the path"
        )
    return key


def unit_header(key: str, target) -> pathlib.Path | None:
    """``include/src/<key>.h`` searched along the target's include path."""
    for root in target.include_paths:
        candidate = root / "src" / f"{key}.h"
        if candidate.is_file():
            return candidate
    return None


def split_path(function: str, target) -> pathlib.Path:
    """The function's split file, naming ``./ddr build`` when the tree is not generated."""
    geometry = target.geometry_required()
    candidate = REPO_ROOT / "asm" / "nonmatchings" / geometry.code_segment / f"{function}.s"
    if candidate.is_file():
        return candidate
    matches = sorted((REPO_ROOT / "asm" / "nonmatchings").glob(f"*/{function}.s"))
    if len(matches) == 1:
        return matches[0]
    if matches:
        raise DraftError(
            f"{function!r} appears in {len(matches)} splits: "
            + ", ".join(_display(path) for path in matches)
            + "; the function name alone is ambiguous, so nothing is drafted"
        )
    raise DraftError(
        f"no split for {function!r} under asm/nonmatchings/{geometry.code_segment}/: "
        f"`asm/` is generated, so run `./ddr build` first (or check the symbol's spelling "
        f"against {_display(target.symbols)})"
    )


def extract_function(text: str, function: str, split: pathlib.Path) -> str:
    """The split's preamble plus the ``glabel <function>`` .. ``endlabel`` block.

    A split holds one function, but the preamble (``.include "macro.inc"``, ``.set
    noat``, ``.align``) is what m2c needs to read the body, and a file that also holds
    a neighbour's bytes must not have them drafted.
    """
    if any(_DLABEL.fullmatch(line) for line in text.splitlines() if line.strip()):
        raise DraftError(
            f"{_display(split)} is a `dlabel` split: retail's DWARF calls {function!r} a "
            f"subroutine but its bytes are data (.word), so m2c has no instructions to "
            f"decompile -- there is nothing to draft for this symbol"
        )
    lines = text.splitlines(keepends=True)
    stripped = [line.rstrip("\n") for line in lines]
    start = end = None
    first_label = len(lines)
    labels: list[str] = []
    for index, line in enumerate(stripped):
        match = _GLABEL.fullmatch(line)
        if match is None:
            continue
        labels.append(match.group(1))
        first_label = min(first_label, index)
        if match.group(1) == function:
            start = index
        elif start is not None:
            break
    if start is None:
        raise DraftError(
            f"{_display(split)} has no `glabel {function}`: the split defines "
            + (", ".join(labels) if labels else "no glabel at all")
        )
    for index in range(start + 1, len(lines)):
        if re.fullmatch(rf"\s*endlabel\s+{re.escape(function)}\s*", stripped[index]):
            end = index
            break
    if end is None:
        raise DraftError(f"{_display(split)} has `glabel {function}` but no `endlabel {function}`")
    preamble = [line for line in lines[:first_label] if not line.lstrip().startswith("nonmatching")]
    return "".join(preamble + lines[start : end + 1])


@dataclasses.dataclass(frozen=True)
class JumpTable:
    """A ``jr $reg`` dispatch's table, before its words have been read."""

    symbol: str
    address: int | None
    bound: int | None


@dataclasses.dataclass(frozen=True)
class TablePlan:
    """One table resolved to the case labels m2c is handed, plus what could not be used."""

    symbol: str
    address: int
    entries: tuple
    labels: tuple
    dropped: tuple
    bound: int | None

    def note(self) -> str:
        """One line naming the table, its address and its cases -- the hand-written fallback."""
        cases = ", ".join(f"{index}:0x{address:08X}" for index, address in enumerate(self.entries))
        return f"{self.symbol} at 0x{self.address:08X} has {len(self.entries)} case(s): {cases}"


def instruction_rows(lines) -> list:
    """``(line index, virtual address)`` for every instruction the split's comments carry."""
    rows = []
    for index, line in enumerate(lines):
        match = _INSTRUCTION.search(line)
        if match is not None:
            rows.append((index, int(match.group(2), 16)))
    return rows


def function_span(rows) -> tuple:
    """``(low, high)``: the half-open address range the split's own instructions cover."""
    if not rows:
        return (0, 0)
    addresses = [address for _, address in rows]
    return (min(addresses), max(addresses) + 4)


def jump_tables(text: str) -> tuple:
    """The tables a ``jr $reg`` in ``text`` dispatches through, in body order.

    An indirect jump whose ``%lo(...)`` names no table symbol is reported as nothing to do:
    m2c refuses such a body with its own message, and that message is the finding.
    """
    lines = text.splitlines()
    indexes = []
    for index, line in enumerate(lines):
        match = _JR.search(line)
        if match is not None and match.group(1) != "31":
            indexes.append(index)
    if not indexes:
        return ()
    every: list = []
    for line in lines:
        for match in _LO_SYMBOL.finditer(line):
            if match.group(1).startswith(JTBL_PREFIXES) and match.group(1) not in every:
                every.append(match.group(1))
    tables: list = []
    seen: set = set()
    for index in indexes:
        symbol = _table_symbol(lines, index)
        if symbol is None and len(every) == 1:
            # The pair may sit a block away from the `jr` (the base in a saved register);
            # one table name in the whole body is unambiguous.
            symbol = every[0]
        if symbol is None or symbol in seen:
            continue
        seen.add(symbol)
        address = _symbol_address(symbol)
        tables.append(JumpTable(symbol, address, _switch_bound(lines, index)))
    return tuple(tables)


def _table_symbol(lines, index: int) -> str | None:
    """The table name the ``%lo(...)`` before line ``index``'s ``jr`` references, if any."""
    for back in range(index - 1, max(index - 13, -1), -1):
        for match in _LO_SYMBOL.finditer(lines[back]):
            if match.group(1).startswith(JTBL_PREFIXES):
                return match.group(1)
    return None


def _symbol_address(symbol: str) -> int | None:
    """``jtbl_002D7110`` -> ``0x002D7110``; ``None`` when the name carries no address."""
    match = _SYMBOL_ADDRESS.search(symbol)
    return int(match.group(1), 16) if match is not None else None


def _switch_bound(lines, index: int) -> int | None:
    """The case count the dispatch is guarded by, when the split shows the check.

    ``sltiu $1, $2, 0xD`` above the table setup is the compiler's bounds check, and its
    immediate is the table's length.  It is a *cap*, never the only evidence: the scan below
    stops on its own at the first word that is not a code address in this function.
    """
    for back in range(index - 1, max(index - 25, -1), -1):
        match = _SLTIU.search(lines[back])
        if match is None:
            continue
        register = match.group(1)
        if not any(re.search(rf"\${register}\b", line) for line in lines[back + 1 : index]):
            continue
        value = int(match.group(2), 0)
        if 0 < value <= TABLE_LIMIT:
            return value
    return None


def retail_words(target, address: int, count: int) -> list:
    """Up to ``count`` little-endian words of the retail image at virtual ``address``."""
    geometry = target.geometry_required()
    low = geometry.loadable_vram
    high = low + geometry.loadable_end - geometry.loadable_rom
    if not low <= address < high:
        # Before the mapping, because `offset_of` now refuses an address the file-backed image
        # does not map (an overlay window has no ELF bytes at all): the reader should be told
        # what this function wanted, not what the mapping refused.
        raise DraftError(
            f"0x{address:08X} lies outside the retail binary's loadable image "
            f"(0x{low:08X}..0x{high:08X}), so it names no table"
        )
    offset = geometry.offset_of(address)
    try:
        data = target.elf.read_bytes()
    except OSError as exc:
        raise DraftError(f"cannot read {_display(target.elf)}: {exc}") from exc
    available = min(count, (high - address) // 4)
    return [
        int.from_bytes(data[offset + 4 * step : offset + 4 * step + 4], "little")
        for step in range(available)
    ]


def _table_words(target, table: JumpTable, notes: list) -> tuple:
    """The table's words, read out of the retail image at the address its name carries."""
    if table.address is None:
        notes.append(
            f"{table.symbol} names no address, so its words cannot be found in the retail "
            f"image; the switch has to be written by hand"
        )
        return ()
    count = TABLE_LIMIT if table.bound is None else min(table.bound, TABLE_LIMIT)
    try:
        return tuple(retail_words(target, table.address, count))
    except DraftError as exc:
        notes.append(f"{table.symbol}: {exc}")
        return ()


def _inside(words, span: tuple) -> tuple:
    """The leading run of ``words`` that names an address in ``span``."""
    low, high = span
    inside = []
    for word in words:
        if not low <= word < high:
            break
        inside.append(word)
    return tuple(inside)


def _label_map(lines, rows) -> tuple:
    """``({address: label}, {address: first instruction line})`` for one split body."""
    labels: dict = {}
    first: dict = {}
    positions = [index for index, _ in rows]
    for index, address in rows:
        first.setdefault(address, index)
    for index, line in enumerate(lines):
        match = _LABEL.fullmatch(line) or _GLABEL.fullmatch(line)
        if match is None:
            continue
        position = bisect.bisect_right(positions, index)
        if position == len(rows):
            continue
        labels.setdefault(rows[position][1], match.group(1))
    return labels, first


def prepare_assembly(text: str, target, function: str) -> tuple:
    """``(assembly for m2c, resolved tables, notes)`` -- the split plus its case labels.

    A body with no table comes back as the very string it was: there is nothing to add, and
    the draft stays exactly what it was before this tool learned to read tables.
    """
    tables = jump_tables(text)
    if not tables:
        return text, (), ()
    lines = text.splitlines(keepends=True)
    plain = text.splitlines()
    rows = instruction_rows(plain)
    labels, first = _label_map(plain, rows)
    span = function_span(rows)
    defined = set(labels.values())
    notes: list = []
    plans: list = []
    insertions: dict = {}
    for table in tables:
        if table.symbol in defined:
            notes.append(f"{table.symbol} is already defined inside the split; left as it is")
            continue
        words = _table_words(target, table, notes)
        if not words:
            continue
        inside = _inside(words, span)
        resolved: list = []
        for address in inside:
            name = labels.get(address)
            if name is None:
                position = first.get(address)
                if position is None:
                    break
                name = _case_label(address)
                labels[address] = name
                insertions.setdefault(position, []).append(name)
            resolved.append((address, name))
        if not resolved:
            listed = ", ".join(f"0x{word:08X}" for word in words[:8])
            more = ", ..." if len(words) > 8 else ""
            notes.append(
                f"{table.symbol} at 0x{table.address:08X}: no entry names an instruction in "
                f"{function}'s split (0x{span[0]:08X}..0x{span[1]:08X}) -- it starts with "
                f"{listed}{more}, and the case blocks live in another split; m2c is handed no "
                f"table for it, so the switch has to be written by hand"
            )
            continue
        # A case the split cannot hold is one the bounds check promises and the scan could not
        # place: without a bound, a word that is not a code address ends the table, and there
        # is no shortfall to report.
        shortfall = 0 if table.bound is None else max(0, table.bound - len(resolved))
        dropped = tuple(words[len(resolved) : len(resolved) + shortfall])
        plan = TablePlan(
            table.symbol,
            table.address,
            tuple(address for address, _ in resolved),
            tuple(name for _, name in resolved),
            dropped,
            table.bound,
        )
        plans.append(plan)
        if dropped:
            notes.append(
                f"{plan.symbol} at 0x{table.address:08X}: the bounds check says {table.bound} "
                f"case(s), but case 0x{dropped[0]:08X} (and any after it) is not an instruction "
                f"in {function}'s split (which stops at 0x{span[1] - 4:08X}); the draft's switch "
                f"stops before that case"
            )
    if not plans:
        return text, (), tuple(notes)
    assembled: list = []
    for index, line in enumerate(lines):
        for name in insertions.get(index, ()):
            assembled.append(name + ":\n")
        assembled.append(line)
    return "".join(assembled), tuple(plans), tuple(notes)


def table_assembly(plans) -> str:
    """The ``.s`` file m2c is handed alongside the split: one data label per table."""
    lines = [".section .rodata"]
    for plan in plans:
        lines.append(".align 2")
        lines.append(f"{plan.symbol}:")
        lines.append("    .word " + ", ".join(plan.labels))
    return "\n".join(lines) + "\n"


def flatten_context(header: pathlib.Path, roots: tuple) -> str:
    """``header`` with its ``#include`` lines replaced by the included files' text.

    m2c reads an already-preprocessed context, so include guards and the other
    directives are dropped; every ``#include "..."`` is resolved against the target's
    include path (then the including file's directory) and visited once.
    """
    lines: list[str] = []
    seen: set = set()

    def visit(path: pathlib.Path) -> None:
        resolved = path.resolve()
        if resolved in seen or not resolved.is_file():
            return
        seen.add(resolved)
        for line in resolved.read_text().splitlines(keepends=True):
            include = _INCLUDE.fullmatch(line)
            if include:
                name = include.group(1)
                for root in (*roots, resolved.parent):
                    candidate = root / name
                    if candidate.is_file():
                        visit(candidate)
                        break
                else:
                    raise DraftError(
                        f"#include \"{name}\" in {_display(resolved)} resolves under none of "
                        f"{', '.join(_display(pathlib.Path(root)) for root in roots)}: the "
                        f"generated headers are incomplete or stale -- run `./ddr oracle`"
                    )
                continue
            if _DIRECTIVE.match(line):
                continue
            lines.append(line)

    visit(header)
    return "".join(lines)


def extract_draft(
    function: str, unit: str, target
) -> tuple[str, pathlib.Path, pathlib.Path, int]:
    """``(draft C, split used, context header, m2c's exit code)`` -- m2c runs only here."""
    install = fetch.installed_m2c()
    key = unit_key(unit, target)
    header = unit_header(key, target)
    assert header is not None  # unit_key proved it
    split = split_path(function, target)
    asm = extract_function(split.read_text(), function, split)
    asm, plans, notes = prepare_assembly(asm, target, function)
    for note in notes:
        print(f"m2c_draft: {note}", file=sys.stderr)
    context = flatten_context(header, target.include_paths)
    if function not in context:
        print(
            f"m2c_draft: {function!r} is not declared by {_display(header)}; running anyway "
            f"(the draft's signature then comes from the call sites)",
            file=sys.stderr,
        )
    with tempfile.TemporaryDirectory(prefix="m2c_draft-") as scratch:
        asm_path = pathlib.Path(scratch) / f"{function}.s"
        context_path = pathlib.Path(scratch) / f"{key.replace('/', '_')}.c"
        asm_path.write_text(asm)
        context_path.write_text(context)
        extra: list = []
        if plans:
            table_path = pathlib.Path(scratch) / f"{function}_tables.s"
            table_path.write_text(table_assembly(plans))
            extra.append(str(table_path))
        command = [
            sys.executable,
            "-B",
            str(install / fetch.M2C_ENTRY),
            "-t",
            M2C_TARGET,
            "-f",
            function,
            "--no-cache",
            "--context",
            str(context_path),
            str(asm_path),
            *extra,
        ]
        environment = dict(os.environ, PYTHONDONTWRITEBYTECODE="1")
        try:
            result = subprocess.run(
                command, capture_output=True, text=True, env=environment, timeout=300
            )
        except (OSError, subprocess.SubprocessError) as exc:
            raise DraftError(f"m2c at {_display(install)} could not run: {exc}") from exc
    if result.returncode != 0:
        sys.stderr.write(result.stderr)
        print(
            f"m2c_draft: m2c exited {result.returncode}; its output below is what it managed",
            file=sys.stderr,
        )
        for plan in plans:
            print(
                f"m2c_draft: {plan.note()} -- m2c was handed this table and still refused, so "
                f"write the switch from these entries by hand",
                file=sys.stderr,
            )
    else:
        for plan in plans:
            print(f"m2c_draft: switch recovered from {plan.note()}", file=sys.stderr)
    return result.stdout, split, header, result.returncode


def output_path(destination: str | None, function: str) -> pathlib.Path | None:
    """Resolve ``--out`` and refuse any path the build reads (``src/`` above all)."""
    if destination is None:
        return None
    path = pathlib.Path(destination)
    if path.parts and path.parts[0] in REFUSED_DIRS:
        raise DraftError(
            f"--out {destination!r} names a tree the build reads ({path.parts[0]}/); a draft "
            f"is never written there -- write it under {OUTPUT_DIR}/ or leave --out off"
        )
    if not path.is_absolute():
        path = REPO_ROOT / path
    if not path.is_relative_to(REPO_ROOT / OUTPUT_DIR):
        raise DraftError(
            f"--out {destination!r} is outside {OUTPUT_DIR}/; a draft belongs there (or on "
            f"stdout), so nothing lands in the hand-written tree"
        )
    if path.name != f"{function}.c" and not path.suffix:
        path = path / f"{function}.c"
    return path


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Draft one function's C with m2c, from its split and this tree's types.",
        usage="%(prog)s [-t NAME] <unit> <function> [--out drafts/<function>.c]",
    )
    parser.add_argument("unit", help="translation unit: src/<dir>/<unit>.c, or <dir>/<unit>")
    parser.add_argument("function", help="the symbol to draft (its split's `glabel` name)")
    parser.add_argument(
        "--target", default=None, help="the registered target (default: this tree's)"
    )
    parser.add_argument(
        "--out",
        default=None,
        metavar="PATH",
        help=f"write the draft here instead of stdout (must be inside {OUTPUT_DIR}/)",
    )
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    from config import targets

    try:
        target = targets.get(args.target)
        draft, split, header, status = extract_draft(args.function, args.unit, target)
        destination = output_path(args.out, args.function)
    except targets.UnknownTarget as exc:
        print(f"m2c_draft: {exc}", file=sys.stderr)
        return 2
    except fetch.FetchError as exc:
        print(f"m2c_draft: {exc}", file=sys.stderr)
        return 2
    except (DraftError, OSError, targets.NotMeasured) as exc:
        print(f"m2c_draft: {exc}", file=sys.stderr)
        return 2
    if destination is None:
        sys.stdout.write(draft)
    else:
        try:
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(draft)
        except OSError as exc:
            print(f"m2c_draft: cannot write {_display(destination)}: {exc}", file=sys.stderr)
            return 2
        print(
            f"m2c_draft: {args.function} -> {_display(destination)} "
            f"(split {_display(split)}, context {_display(header)})",
            file=sys.stderr,
        )
    return 0 if status == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
