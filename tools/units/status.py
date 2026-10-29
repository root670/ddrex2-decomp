#!/usr/bin/env python3
"""status.py -- generated progress table and heatmap for the translation units.

The unit list is the target's own manifest (``config/<target>/cus.json``): every record whose
``kind`` is ``tu`` is one row.  A unit is in exactly one state:

* **promoted** -- a source exists at its path, a ``tu_builds`` row records the compiler pair,
  and ``ddr verify --tu`` is green.  The gate is the definition, not a corroboration: a
  ``src/`` file and a row without a green per-TU verdict are a claim, not a promotion.
* **partial** -- a draft named like the unit exists on *any* branch (or in the working tree),
  or a source exists on some branch without a ``tu_builds`` row.  A row whose source or gate
  is missing is partial too: the attempt is visible, the proof is not.
* **untouched** -- none of the above.

Completion is reported in three columns, each a ``promoted/total (percent)`` cell, because a
unit is a coarse denominator (one unit ranges from 8 bytes to 2.4 KB):

* **translation units** -- the 249 rows of the manifest;
* **functions** -- the code splits' ``nonmatching <fn>, 0xNN`` declarations (one function per
  line);
* **reconstructed bytes** -- the sum of those declarations' sizes.  This is code the
  decompilation has to reproduce as C: debug information and data are not in it.

**Accounting.**  A promoted unit counts every function the split ledger attributes to it (by
the DWARF function start) and that function's declared size, which is the unit's whole size in
the manifest; nothing else counts.  The old numerator was the object's ``.text`` span rounded up
to MWCC's 16-byte function alignment -- padding, not code -- which could exceed the unit's own
manifest size and made ``sys`` read 96 of 80 bytes (120%).  Each numerator is now a subset of
its denominator by construction, so no percentage can pass 100.

**The gate is the promotion, and a refusal is a failure.**  A unit whose source and
``tu_builds`` row exist is promoted only when ``ddr verify --tu`` is green.  When that gate
exits 2 -- a stale ``out/``, a missing object, a graph that predates the row -- the status run
exits 2 naming the unit and what is stale.  It never prints a smaller number than the gate
would confirm; the remedy is ``./ddr build``, which regenerates both artifacts itself.

The split bytes are attributed to a module only where the retail debug manifest names the
function's start address (its ``low_pc``); a named function with no compile unit is
``(library)`` (the SDK symbols), and an unnamed ``func_*`` with no compile unit is
``(unattributed)``.  Nothing is assigned by guessing.

The states are rendered twice from the same data: a Markdown table in ``README.md`` between
``<!-- status:start -->`` and ``<!-- status:end -->`` (the markers are inserted on the first
run; later runs replace only their contents), and ``docs/status.svg``, one cell per unit,
grouped and labelled by module with a per-cell ``<title>``.  Both are deterministic, and
``--check`` compares them without writing.  The README block is one summary line carrying the
legend, the denominator clause and the pointer to this file, then a table row for **every**
module -- alphabetical by module key, including the split-only buckets that have no
units -- so the rows reconcile with the summary to the byte and to the function.  The SVG
groups the same modules in the same order, one band each, with one cell per unit.

``./ddr build`` and a plain ``./ddr verify`` call this generator themselves, at the point the
build's ``g1`` edge has just passed, so a promotion cannot leave either file stale.

A draft is matched by file name (``drafts/lang.c`` is a draft of ``src/CS/lang.c``); draft
experiment trees with other names are not matched, because a name is the only link the tree
records.  "Any branch" means every ref under ``refs/heads`` and ``refs/remotes`` plus the
working tree, read with ``git ls-tree`` -- never by checking out.

Usage::

    python3 tools/units/status.py                 # rewrite README.md and docs/status.svg
    python3 tools/units/status.py --check         # exit 1 if either is stale
    python3 tools/units/status.py --no-verify     # structural states, skip the per-TU gate
    python3 tools/units/status.py --target NAME   # another target's manifest

Exit codes: 0 written (or current), 1 ``--check`` found stale files, 2 unusable invocation or
input -- and, since the promotion set is the gate's, a ``ddr verify --tu`` that refuses stale
evidence (exit 2) is reported as exit 2 naming the unit rather than silently counting it out.
"""

from __future__ import annotations

import argparse
import json
import os
import pathlib
import re
import subprocess
import sys
from collections import defaultdict
from dataclasses import dataclass, field
from typing import Iterable, NamedTuple
from xml.sax.saxutils import escape

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

README = REPO_ROOT / "README.md"
SVG = REPO_ROOT / "docs" / "status.svg"
#: The gate this report counts: one ``verify --tu`` per unit with a source and a row.
DDR = REPO_ROOT / "ddr"
#: Set on the gate calls this tool makes so a ``ddr verify --tu`` cannot refresh in turn.
GATE_GUARD = "DDR_NO_STATUS"
START = "<!-- status:start -->"
END = "<!-- status:end -->"

PROMOTED = "promoted"
PARTIAL = "partial"
UNTOUCHED = "untouched"

#: The two buckets for split code no compile unit claims.
LIBRARY = "(library)"
UNATTRIBUTED = "(unattributed)"

#: Plain hex, no gradients or CSS variables: GitHub's SVG sanitizer keeps them as written.
COLOURS = {
    PROMOTED: "#2da44e",
    PARTIAL: "#bf8700",
    UNTOUCHED: "#d0d7de",
}
INK = "#24292f"
MUTED = "#57606a"
PANEL = "#ffffff"

#: ``nonmatching <fn>, 0xNN`` -- splat's declaration of one function's code size.
NONMATCHING = re.compile(r"^[ \t]*nonmatching[ \t]+([^,\s]+),[ \t]*(0x[0-9A-Fa-f]+)[ \t]*$",
                         re.MULTILINE)
#: The first instruction comment, ``/* fileoffset address bytes */``.
SPLIT_ADDRESS = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]+\s*\*/")


class Unit(NamedTuple):
    """One ``kind: tu`` record, as the manifest spells it."""

    file: str
    size: int        # the CU record's size; not the completion denominator (that is code)


class Split(NamedTuple):
    """One sized split function: its retail address, code size and symbol name."""

    address: int
    size: int
    name: str


@dataclass(frozen=True)
class CodeFact:
    """Function count and code bytes."""

    functions: int = 0
    code_bytes: int = 0

    def __add__(self, other: "CodeFact") -> "CodeFact":
        return CodeFact(self.functions + other.functions,
                        self.code_bytes + other.code_bytes)


@dataclass(frozen=True)
class Code:
    """The completion denominator and the per-unit numerator facts."""

    splits: CodeFact
    by_module: dict = field(default_factory=dict)
    functions_by_file: dict = field(default_factory=dict)
    bytes_by_file: dict = field(default_factory=dict)

    def fact_of(self, module: str) -> CodeFact:
        return self.by_module.get(module, CodeFact())


@dataclass(frozen=True)
class Stats:
    """One row of the report: the promoted part and the total of each denominator.

    Both sides come from the same split ledger, so ``promoted_*`` is a subset of its
    denominator; :meth:`__post_init__` refuses a row that is not, which keeps every percentage
    at or below 100 instead of printing a ratio the tree cannot support.
    """

    units: int
    promoted_units: int
    functions: int
    promoted_functions: int
    code_bytes: int
    promoted_code_bytes: int

    def __post_init__(self) -> None:
        for label, part, total in (("units", self.promoted_units, self.units),
                                   ("functions", self.promoted_functions, self.functions),
                                   ("code bytes", self.promoted_code_bytes, self.code_bytes)):
            if part > total:
                raise ValueError(f"status: {label}: {part} reconstructed of {total}: the "
                                 f"numerator of a row cannot exceed its denominator")

    def cells(self) -> tuple[str, str, str]:
        """The three table cells, all in the one ``promoted/total (percent)`` shape."""
        return (cell(self.promoted_units, self.units),
                cell(self.promoted_functions, self.functions),
                cell(self.promoted_code_bytes, self.code_bytes))

    @property
    def unit_percent(self) -> float:
        return percent(self.promoted_units, self.units)

    @property
    def function_percent(self) -> float:
        return percent(self.promoted_functions, self.functions)

    @property
    def code_percent(self) -> float:
        return percent(self.promoted_code_bytes, self.code_bytes)


def percent(part: int, total: int) -> float:
    """``part`` as a percentage of ``total``; an empty denominator is 0, never a crash."""
    return 0.0 if not total else 100.0 * part / total


# ---------------------------------------------------------------------------
# manifests
# ---------------------------------------------------------------------------


def read_records(cus_path: pathlib.Path) -> list[dict]:
    """Every record of the target's ``cus.json``, in manifest order."""
    try:
        records = json.loads(pathlib.Path(cus_path).read_text())
    except OSError as exc:
        raise SystemExit(f"status: {cus_path}: {exc.strerror or exc}") from exc
    except json.JSONDecodeError as exc:
        raise SystemExit(f"status: {cus_path}: not JSON: {exc}") from exc
    if not isinstance(records, list):
        raise SystemExit(f"status: {cus_path}: expected a JSON array of records")
    return records


def units_of(records: Iterable[dict]) -> list[Unit]:
    """Every translation unit record, in manifest order."""
    units = [Unit(record["file"], int(record["size"])) for record in records
             if record.get("kind") == "tu"]
    if not units:
        raise SystemExit("status: the manifest has no kind 'tu' records")
    return units


def load_units(cus_path: pathlib.Path) -> list[Unit]:
    return units_of(read_records(cus_path))


def load_splits(asm_root: pathlib.Path) -> list[Split]:
    """Every sized ``nonmatching <fn>, 0xNN`` declaration under ``asm_root``.

    A line without a size is a data symbol declaration, not a function, and is skipped.
    """
    splits: list[Split] = []
    files = sorted(pathlib.Path(asm_root).rglob("nonmatchings/**/*.s"))
    for path in files:
        text = path.read_text()
        match = NONMATCHING.search(text)
        if match is None:
            continue
        address = SPLIT_ADDRESS.search(text)
        if address is None:
            raise SystemExit(f"status: {path}: sized split has no address comment")
        splits.append(Split(int(address.group(1), 16), int(match.group(2), 16),
                            match.group(1)))
    if not splits:
        raise SystemExit(f"status: {asm_root}: no sized nonmatching splits (run ./ddr build)")
    return splits


def code_of(records: Iterable[dict], splits: list[Split]) -> Code:
    """The split ledger, attributed to modules and files through the DWARF function starts.

    ``functions_by_file`` and ``bytes_by_file`` are the *same* splits the module and overall
    denominators sum: one promoted unit's share is a subset of its module's total by
    construction, so its percentage cannot pass 100.  A split no compile unit claims stays in
    the denominators with no file, so it is counted nowhere as reconstructed.
    """
    owner = {record["low_pc"]: record["file"] for record in records
             if record.get("kind") == "function" and record.get("low_pc") is not None}

    by_module: dict[str, CodeFact] = defaultdict(CodeFact)
    functions_by_file: dict[str, int] = defaultdict(int)
    bytes_by_file: dict[str, int] = defaultdict(int)
    total = CodeFact()
    for split in splits:
        file = owner.get(split.address)
        if file is not None:
            module = module_of(file)
            functions_by_file[file] += 1
            bytes_by_file[file] += split.size
        elif split.name.startswith("func_"):
            module = UNATTRIBUTED
        else:
            module = LIBRARY
        fact = CodeFact(1, split.size)
        by_module[module] = by_module[module] + fact
        total = total + fact
    return Code(splits=total, by_module=dict(by_module),
                functions_by_file=dict(functions_by_file),
                bytes_by_file=dict(bytes_by_file))


def module_of(file: str) -> str:
    """The directory after ``src/``; a unit directly under ``src`` is ``(root)``.

    A manifest path that does not live under ``src/`` (a library object) is ``(external)``:
    it has no module directory, and inventing one would split the table by guesswork.
    """
    parts = pathlib.PurePosixPath(file).parts
    if parts and parts[0] == "src":
        rest = parts[1:]
        return rest[0] if len(rest) > 1 else "(root)"
    return "(external)"


_SYNTHETIC_ORDER = {"(root)": 0, "(external)": 1, LIBRARY: 2, UNATTRIBUTED: 3}


def module_key(name: str) -> tuple:
    """Real modules first, alphabetically; then the four non-directory groups in order."""
    if name in _SYNTHETIC_ORDER:
        return (1, _SYNTHETIC_ORDER[name], "")
    return (0, 0, name.lower())


def classify(units: Iterable[Unit], sources: set[str], drafts: set[str],
             rows: set[str], verified: set[str]) -> dict[str, str]:
    """State per unit path from the four facts already gathered.

    ``sources`` holds every unit path that exists on some ref (or in the working tree),
    ``drafts`` holds draft *file names*, ``rows`` the ``tu_builds`` source paths and
    ``verified`` the paths whose ``ddr verify --tu`` was green.  Promotion needs all three
    of source, row and verdict; anything else that shows work is partial.
    """
    states: dict[str, str] = {}
    for unit in units:
        has_source = unit.file in sources
        has_row = unit.file in rows
        if has_source and has_row and unit.file in verified:
            states[unit.file] = PROMOTED
        elif has_source or has_row or pathlib.PurePosixPath(unit.file).name in drafts:
            states[unit.file] = PARTIAL
        else:
            states[unit.file] = UNTOUCHED
    return states


def stats_of(group: Iterable[Unit], states: dict[str, str], code: Code,
             module: str | None = None) -> Stats:
    """One report row: the units in ``group`` against the splits of ``module`` (or all splits).

    The promoted part is the units' own share of the split ledger; the total is the module's
    (or the whole) split ledger.  Nothing is inferred from the manifest record's size, and
    nothing is rounded up to the object's alignment, so the numerator is a subset of the
    denominator and every percentage stays at or below 100.
    """
    fact = code.splits if module is None else code.fact_of(module)
    members = list(group)
    promoted = [unit for unit in members if states.get(unit.file) == PROMOTED]
    return Stats(
        units=len(members),
        promoted_units=len(promoted),
        functions=fact.functions,
        promoted_functions=sum(code.functions_by_file.get(unit.file, 0)
                               for unit in promoted),
        code_bytes=fact.code_bytes,
        promoted_code_bytes=sum(code.bytes_by_file.get(unit.file, 0)
                                for unit in promoted),
    )


# ---------------------------------------------------------------------------
# rendering
# ---------------------------------------------------------------------------


def _fmt(number: int) -> str:
    return f"{number:,}"


def _pct(part: int, total: int, digits: int = 1) -> str:
    return f"{percent(part, total):.{digits}f}%"


def cell(part: int, total: int) -> str:
    """One report cell: ``x/y (zz.z%)``, one decimal everywhere, totals grouped in threes."""
    return f"{_fmt(part)}/{_fmt(total)} ({_pct(part, total)})"


def _module_groups(units: Iterable[Unit], states: dict[str, str]) -> dict[str, list[Unit]]:
    """``{module: [units...]}``, each list in manifest order."""
    groups: dict[str, list[Unit]] = {}
    for unit in units:
        groups.setdefault(module_of(unit.file), []).append(unit)
    return groups


def report_modules(units: Iterable[Unit], states: dict[str, str],
                   code: Code) -> list[tuple[str, list[Unit]]]:
    """Every module in the report, in :func:`module_key` order -- alphabetical.

    A module is anything with a translation unit *or* split code, so the rows always
    partition the summary's denominators: units by the unit's own module, functions and
    bytes by the split ledger's attribution (``module_of`` of the owning unit's path, or the
    ``(library)``/``(unattributed)`` bucket).  Overlay-resident splits are attributed the
    same way -- through the owning unit's path -- so an overlay's code is in its unit's row,
    not a second row that would double-count it.  Ordering is :func:`module_key`: the real
    modules alphabetically, then the non-directory buckets, so a table row's position never
    moves when a unit is promoted.
    """
    groups = _module_groups(units, states)
    names = set(groups) | set(code.by_module)
    ordered = sorted(names, key=module_key)
    return [(name, groups.get(name, [])) for name in ordered]


def render_markdown(units: list[Unit], states: dict[str, str], target: str,
                    code: Code) -> str:
    """The block placed between the README markers: one summary line, then the table.

    The table lists every module -- overlays included through the unit that owns their
    splits, and the ``(library)``/``(unattributed)`` buckets, which have no units -- so its
    rows partition the summary's three totals exactly.  Ordering is by code bytes, biggest
    first: the reader sees where the code is before where it is not (see
    :func:`report_modules`).
    """
    overall = stats_of(units, states, code)
    units_cell, functions_cell, bytes_cell = overall.cells()
    lines = [
        f"**{units_cell} units · {functions_cell} functions · {bytes_cell} code bytes "
        f"reconstructed** — green = promoted, amber = partial, grey = untouched; "
        f"denominators are the split ledger's functions and declared code bytes, and "
        f"`tools/units/status.py` counts only what `./ddr verify --tu` confirms.",
        "",
        "| module | units | functions | reconstructed bytes |",
        "|---|---:|---:|---:|",
    ]
    for module, group in report_modules(units, states, code):
        row_units, row_functions, row_bytes = stats_of(group, states, code, module).cells()
        lines.append(f"| `{module}` | {row_units} | {row_functions} | {row_bytes} |")
    return "\n".join(lines) + "\n"


# ---------------------------------------------------------------------------
# SVG heatmap
# ---------------------------------------------------------------------------

WIDTH = 800
MARGIN = 24
CELL = 12
GAP = 3
PITCH = CELL + GAP
LABEL = 18
BAND_GAP = 8
HEADER = 88
LEGEND = 46


def _svg_layout(groups: list[tuple]) -> list[dict]:
    """Per-module geometry: where its label goes and where each cell sits."""
    max_columns = (WIDTH - 2 * MARGIN + GAP) // PITCH
    layout, y = [], HEADER
    for module, group in groups:
        rows = (len(group) + max_columns - 1) // max_columns
        cells = []
        for index, unit in enumerate(group):
            column, row = index % max_columns, index // max_columns
            cells.append((MARGIN + column * PITCH, y + LABEL + row * PITCH, unit))
        height = LABEL + rows * PITCH - GAP + BAND_GAP
        layout.append({"module": module, "group": group, "label_y": y + 13,
                       "cells": cells, "height": height})
        y += height
    return layout


def _legend() -> str:
    entries = [(PROMOTED, "promoted"), (PARTIAL, "partial"), (UNTOUCHED, "untouched")]
    parts, x = [], MARGIN
    for state, label in entries:
        parts.append(f'<rect x="{x}" y="0" width="12" height="12" rx="2" '
                     f'fill="{COLOURS[state]}" stroke="#8c959f" stroke-width="0.5"/>')
        parts.append(f'<text x="{x + 18}" y="10" font-size="12" fill="{INK}">{label}</text>')
        x += 124
    return "".join(parts)


def render_svg(units: list[Unit], states: dict[str, str], target: str,
               code: Code) -> str:
    """One cell per unit, grouped and labelled by module; no scripts, no external refs.

    Every number is the Markdown table's own ``x/y (zz.z%)`` cell, rendered from the same
    :class:`Stats`, so the two artifacts cannot disagree about what was counted.
    """
    overall = stats_of(units, states, code)
    layout = _svg_layout(report_modules(units, states, code))
    height = (layout[-1]["label_y"] + layout[-1]["height"] + LEGEND
              if layout else HEADER + LEGEND)
    units_cell, functions_cell, bytes_cell = overall.cells()
    out = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" height="{height}" '
        f'viewBox="0 0 {WIDTH} {height}" role="img" '
        f'aria-label="{escape(target)} translation unit heatmap">',
        f'<title>{escape(target)} translation units: {units_cell} promoted</title>',
        f'<desc>One square per translation unit, grouped by module. '
        f'{units_cell} units, {functions_cell} functions and {bytes_cell} code bytes are '
        f'reconstructed.</desc>',
        f'<rect width="{WIDTH}" height="{height}" fill="{PANEL}"/>',
        f'<text x="{MARGIN}" y="32" font-size="18" font-weight="600" fill="{INK}">'
        f'{escape(target)}: {units_cell} units</text>',
        f'<text x="{MARGIN}" y="52" font-size="12" fill="{MUTED}">'
        f'{functions_cell} functions &#183; {bytes_cell} code bytes '
        f'&#183; one cell per translation unit</text>',
        f'<text x="{MARGIN}" y="76" font-size="12" fill="{MUTED}">'
        f'green = promoted (G2 green) &#183; amber = partial &#183; grey = untouched '
        f'&#183; hover for path, code bytes and state</text>',
    ]
    for band in layout:
        module = band["module"]
        group = band["group"]
        row_units, row_functions, row_bytes = stats_of(
            group, states, code, module).cells()
        label = (f"{module} - {row_units} units"
                 f" \u00b7 {row_functions} functions"
                 f" \u00b7 {row_bytes} bytes")
        out.append(f'<g class="module" data-module="{escape(module, {chr(34): "&quot;"})}">')
        out.append(f'<text x="{MARGIN}" y="{band["label_y"]}" font-size="12" '
                   f'font-weight="600" fill="{INK}">{escape(label)}</text>')
        for x, y, unit in band["cells"]:
            state = states.get(unit.file, UNTOUCHED)
            code_bytes = code.bytes_by_file.get(unit.file, 0)
            title = f"{unit.file} - {_fmt(code_bytes)} code bytes - {state}"
            out.append(
                f'<rect class="cell" data-state="{state}" x="{x}" y="{y}" '
                f'width="{CELL}" height="{CELL}" rx="2" fill="{COLOURS[state]}">'
                f'<title>{escape(title)}</title></rect>')
        out.append("</g>")
    legend_y = height - 30
    out.append(f'<g transform="translate(0 {legend_y})" class="legend">'
               f'{_legend()}</g>')
    out.append("</svg>")
    return "\n".join(out) + "\n"


# ---------------------------------------------------------------------------
# repository facts
# ---------------------------------------------------------------------------


def _git(*args: str) -> subprocess.CompletedProcess:
    return subprocess.run(["git", *args], cwd=REPO_ROOT, capture_output=True, text=True)


def branches() -> list[str]:
    """Every local and remote branch; an empty list outside a git tree."""
    proc = _git("for-each-ref", "--format=%(refname:short)",
                "refs/heads", "refs/remotes")
    if proc.returncode != 0:
        return []
    return [line.strip() for line in proc.stdout.splitlines() if line.strip()]


def _tree_files(ref: str, paths: tuple[str, ...]) -> list[str]:
    proc = _git("ls-tree", "-r", "--name-only", ref, "--", *paths)
    return proc.stdout.splitlines() if proc.returncode == 0 else []


def _worktree_files(paths: tuple[str, ...]) -> list[str]:
    found = []
    for path in paths:
        root = REPO_ROOT / path
        if root.is_file():
            found.append(path)
        elif root.is_dir():
            found += [p.relative_to(REPO_ROOT).as_posix() for p in root.rglob("*")
                      if p.is_file()]
    return found


def collect_sources_and_drafts(unit_paths: Iterable[str] = ()) -> tuple[set[str], set[str]]:
    """Unit-path sources and draft file names over every branch and the working tree.

    ``unit_paths`` is the manifest's own list, which is what lets a source *outside* ``src/``
    count: `libstr3.c` is a translation unit at the repository root, and walking only ``src/``
    and ``drafts/`` made it permanently "partial" however green its gate was (the report read
    104 units while the gate confirmed 105).
    """
    wanted = set(unit_paths)
    sources: set[str] = set()
    drafts: set[str] = set()

    def absorb(paths: Iterable[str]) -> None:
        for path in paths:
            posix = path.replace("\\", "/")
            if posix.startswith("src/") or posix in wanted:
                sources.add(posix)
            elif posix.startswith("drafts/"):
                drafts.add(pathlib.PurePosixPath(posix).name)

    outside = tuple(sorted({p for p in wanted if not p.startswith("src/")}))
    absorb(_worktree_files(("src", "drafts", *outside)))
    for ref in ["HEAD", *branches()]:
        absorb(_tree_files(ref, ("src", "drafts", *outside)))
    return sources, drafts


class StaleEvidence(RuntimeError):
    """The gate refused to judge a unit because the build is not that unit's build.

    ``ddr verify --tu`` exits 2 for a stale ``out/``, a missing object or a graph that
    predates the row.  Treating that as "not promoted" is exactly the silent undercount this
    report had -- it printed 38 units while the gate confirmed 76 -- so the run stops and
    names the unit instead of shrinking the numerator.
    """


def verify_units(candidates: Iterable[Unit], target,
                 ddr: pathlib.Path | None = None) -> tuple[set[str], dict[str, str]]:
    """Run ``ddr --target T verify --tu FILE`` for each candidate; return green and failures.

    Exit 0 is green.  Exit 1 is a real verdict failure: the attempt exists, the proof does
    not, and it is counted as not promoted.  Exit 2 is the gate declining to judge stale
    evidence, which raises :class:`StaleEvidence` -- a configuration problem in the tree,
    never a unit that quietly leaves the numerator.

    ``ddr`` is a parameter so a test can point the rule at a synthetic gate.  Each call
    carries ``DDR_NO_STATUS``: the generator is the gate's client, and the gate must not
    call back into the generator that called it.
    """
    executable = pathlib.Path(ddr) if ddr is not None else DDR
    environment = dict(os.environ, **{GATE_GUARD: "1"})
    verified: set[str] = set()
    failures: dict[str, str] = {}
    for unit in candidates:
        proc = subprocess.run([str(executable), "--target", target.name, "verify",
                               "--tu", unit.file],
                              cwd=REPO_ROOT, capture_output=True, text=True,
                              env=environment)
        if proc.returncode == 0:
            verified.add(unit.file)
            continue
        detail = (proc.stderr or proc.stdout).strip().splitlines()
        message = detail[-1] if detail else f"exit {proc.returncode}"
        if proc.returncode == 2:
            raise StaleEvidence(f"{unit.file}: {message}")
        failures[unit.file] = message
    return verified, failures


# ---------------------------------------------------------------------------
# README markers
# ---------------------------------------------------------------------------


def replace_marked(text: str, block: str, heading: str = "## Progress") -> str:
    """Replace the marker contents, or insert them (with ``heading``) before the gates."""
    if START in text and END in text:
        before, rest = text.split(START, 1)
        _, after = rest.split(END, 1)
        return before + START + block + END + after
    if START in text or END in text:
        raise ValueError("README has only one status marker; restore or remove it")
    insertion = f"{heading}\n\n{START}{block}{END}\n\n"
    anchor = "## The gates"
    index = text.find(anchor)
    if index == -1:
        return text.rstrip() + "\n\n" + insertion
    return text[:index] + insertion + text[index:]


def marked_block(markdown: str) -> str:
    return "\n\n" + markdown.rstrip() + "\n\n"


# ---------------------------------------------------------------------------
# command
# ---------------------------------------------------------------------------


def parse_args(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--target", default=None,
                        help="the target whose cus.json and tu_builds are read "
                             "(default: the registered target)")
    parser.add_argument("--check", action="store_true",
                        help="compare the generated files, write nothing; exit 1 if stale")
    parser.add_argument("--no-verify", action="store_true",
                        help="do not run the per-TU gate; a source plus a tu_builds row "
                             "counts as promoted (for checkouts without the retail ELF)")
    return parser.parse_args(argv)


def apply_artifacts(readme_path, svg_path, markdown: str, svg: str,
                    check: bool = False) -> list[pathlib.Path]:
    """Write the two generated files, or with ``check`` only list the ones that differ.

    Returns the paths whose content differs from what was generated.  A file is written only
    when it differs, so a no-op run -- and every ordinary edit outside the markers -- leaves
    both artifacts untouched.  This is the whole write path: ``main`` and ``--check`` share
    it, so "written" and "stale" can never mean different things.
    """
    readme_path, svg_path = pathlib.Path(readme_path), pathlib.Path(svg_path)
    readme_text = readme_path.read_text()
    new_readme = replace_marked(readme_text, marked_block(markdown))
    changed = []
    if new_readme != readme_text:
        changed.append(readme_path)
    if not svg_path.is_file() or svg_path.read_text() != svg:
        changed.append(svg_path)
    if check:
        return changed
    if readme_path in changed:
        readme_path.write_text(new_readme)
    if svg_path in changed:
        svg_path.parent.mkdir(parents=True, exist_ok=True)
        svg_path.write_text(svg)
    return changed


def _display(path) -> str:
    """A path as the reader types it: repo-relative when it lives in the repo."""
    try:
        return str(pathlib.Path(path).relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def main(argv=None) -> int:
    args = parse_args(argv)
    from config import targets  # local: the module is importable without a configured tree

    try:
        target = targets.get(args.target)
    except targets.UnknownTarget as exc:
        print(f"status: {exc}", file=sys.stderr)
        return 2
    records = read_records(target.config_dir / "cus.json")
    units = units_of(records)
    rows = {entry[0] for entry in target.tu_builds}
    code = code_of(records, load_splits(REPO_ROOT / "asm"))

    sources, drafts = collect_sources_and_drafts(unit.file for unit in units)
    candidates = [unit for unit in units
                  if unit.file in sources and (args.no_verify or unit.file in rows)]
    if args.no_verify:
        verified, failures = {unit.file for unit in candidates}, {}
    else:
        try:
            verified, failures = verify_units(candidates, target)
        except StaleEvidence as exc:
            print(f"status: stale evidence: {exc}", file=sys.stderr)
            return 2
        for file, detail in failures.items():
            print(f"status: {file}: not promoted: {detail}", file=sys.stderr)

    states = classify(units, sources, drafts, rows, verified)
    overall = stats_of(units, states, code)
    markdown = render_markdown(units, states, target.name, code)
    svg = render_svg(units, states, target.name, code)

    stale = apply_artifacts(README, SVG, markdown, svg, check=args.check)
    units_cell, functions_cell, bytes_cell = overall.cells()
    summary = (f"{units_cell} units, {functions_cell} functions, "
               f"{bytes_cell} code bytes")

    if args.check:
        if stale:
            for path in stale:
                print(f"status: stale: {_display(path)}", file=sys.stderr)
            return 1
        print(f"status: current: {summary}")
        return 0

    print(f"status: {summary}")
    print(f"status: README.md {'updated' if README in stale else 'current'}; "
          f"docs/status.svg {'updated' if SVG in stale else 'current'}")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except ValueError as exc:
        print(f"status: {exc}", file=sys.stderr)
        sys.exit(2)
