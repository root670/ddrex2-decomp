#!/usr/bin/env python3
"""status.py -- generated progress table and heatmap for the translation units.

The unit list is the target's own manifest (``config/<target>/cus.json``): every record whose
``kind`` is ``tu`` is one row, and its ``file``/``size`` are the path a source must occupy and
the retail code bytes the unit owns.  A unit is in exactly one state:

* **promoted** -- a source exists at its path, a ``tu_builds`` row records the compiler pair,
  and ``ddr verify --tu`` is green.  The gate is the definition, not a corroboration: a
  ``src/`` file and a row without a green per-TU verdict are a claim, not a promotion.
* **partial** -- a draft named like the unit exists on *any* branch (or in the working tree),
  or a source exists on some branch without a ``tu_builds`` row.  A row whose source or gate
  is missing is partial too: the attempt is visible, the proof is not.
* **untouched** -- none of the above.

The states are rendered twice from the same data: a Markdown table in ``README.md`` between
``<!-- status:start -->`` and ``<!-- status:end -->`` (the markers are inserted on the first
run; later runs replace only their contents), and ``docs/status.svg``, one cell per unit,
grouped and labelled by module with a per-cell ``<title>``.  Both are deterministic, so
``--check`` compares them without writing and fails when either is stale.

A draft is matched by file name (``drafts/lang.c`` is a draft of ``src/CS/lang.c``); draft
experiment trees with other names are not matched, because a name is the only link the tree
records.  "Any branch" means every ref under ``refs/heads`` and ``refs/remotes`` plus the
working tree, read with ``git ls-tree`` -- never by checking out.

Usage::

    python3 tools/units/status.py                 # rewrite README.md and docs/status.svg
    python3 tools/units/status.py --check         # exit 1 if either is stale
    python3 tools/units/status.py --no-verify     # structural states, skip the per-TU gate
    python3 tools/units/status.py --target NAME   # another target's manifest

Exit codes: 0 written (or current), 1 ``--check`` found stale files, 2 unusable invocation
or input.
"""

from __future__ import annotations

import argparse
import json
import pathlib
import subprocess
import sys
from dataclasses import dataclass
from typing import Iterable, NamedTuple
from xml.sax.saxutils import escape

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

README = REPO_ROOT / "README.md"
SVG = REPO_ROOT / "docs" / "status.svg"
START = "<!-- status:start -->"
END = "<!-- status:end -->"

PROMOTED = "promoted"
PARTIAL = "partial"
UNTOUCHED = "untouched"

#: Plain hex, no gradients or CSS variables: GitHub's SVG sanitizer keeps them as written.
COLOURS = {
    PROMOTED: "#2da44e",
    PARTIAL: "#bf8700",
    UNTOUCHED: "#d0d7de",
}
INK = "#24292f"
MUTED = "#57606a"
PANEL = "#ffffff"


class Unit(NamedTuple):
    """One ``kind: tu`` record, as the manifest spells it."""

    file: str
    size: int


@dataclass(frozen=True)
class Totals:
    """Completion over units and over the retail code bytes they own."""

    units: int
    bytes: int
    promoted_units: int
    promoted_bytes: int

    @property
    def unit_percent(self) -> float:
        return percent(self.promoted_units, self.units)

    @property
    def byte_percent(self) -> float:
        return percent(self.promoted_bytes, self.bytes)


def percent(part: int, total: int) -> float:
    """``part`` as a percentage of ``total``; an empty denominator is 0, never a crash."""
    return 0.0 if not total else 100.0 * part / total


def load_units(cus_path: pathlib.Path) -> list[Unit]:
    """Every translation unit record, in manifest order."""
    try:
        records = json.loads(pathlib.Path(cus_path).read_text())
    except OSError as exc:
        raise SystemExit(f"status: {cus_path}: {exc.strerror or exc}") from exc
    except json.JSONDecodeError as exc:
        raise SystemExit(f"status: {cus_path}: not JSON: {exc}") from exc
    units = [Unit(record["file"], int(record["size"])) for record in records
             if record.get("kind") == "tu"]
    if not units:
        raise SystemExit(f"status: {cus_path}: no kind 'tu' records")
    return units


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


def module_key(name: str) -> tuple:
    """Real modules first, alphabetically, then the two synthetic groups."""
    return (name.startswith("("), name.lower())


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


def totals_of(units: Iterable[Unit], states: dict[str, str]) -> Totals:
    units = list(units)
    promoted = [unit for unit in units if states.get(unit.file) == PROMOTED]
    return Totals(units=len(units),
                  bytes=sum(unit.size for unit in units),
                  promoted_units=len(promoted),
                  promoted_bytes=sum(unit.size for unit in promoted))


def _fmt(number: int) -> str:
    return f"{number:,}"


def _pct(part: int, total: int) -> str:
    return f"{percent(part, total):.1f}%"


def _state_groups(units: Iterable[Unit], states: dict[str, str]) -> list[tuple]:
    """``[(module, [units...])]`` in display order, each list in manifest order."""
    groups: dict[str, list[Unit]] = {}
    for unit in units:
        groups.setdefault(module_of(unit.file), []).append(unit)
    return [(module, groups[module]) for module in sorted(groups, key=module_key)]


def render_markdown(units: list[Unit], states: dict[str, str], target: str) -> str:
    """The block placed between the README markers."""
    overall = totals_of(units, states)
    groups = _state_groups(units, states)
    lines = [
        f"**Overall: {overall.promoted_units} / {overall.units} translation units promoted "
        f"({_pct(overall.promoted_units, overall.units)}); "
        f"{_fmt(overall.promoted_bytes)} / {_fmt(overall.bytes)} retail code bytes "
        f"({_pct(overall.promoted_bytes, overall.bytes)}).**",
        "",
        "Green means a unit is **promoted** — this is not a draft count.  It has a source "
        "at its manifest path, a `tu_builds` row recording the compiler and flags it was "
        "measured with, and a green `./ddr verify --tu` verdict: its `.text` span, its "
        "`.debug` chunk and its `.line` chunks are retail's bytes.  Amber is **partial** — "
        "a draft named like the unit exists on some branch, or a source exists without a "
        "`tu_builds` row (or its verdict is not green).  Grey is **untouched**.",
        "",
        "Regenerate both this table and [`docs/status.svg`](docs/status.svg) with "
        f"`python3 tools/units/status.py --target {target}`; "
        "`python3 tools/units/status.py --check` fails when either is stale.  The heatmap "
        "has one cell per translation unit, grouped by module; hover a cell for its path, "
        "bytes and state.",
        "",
        "| module | units | promoted | bytes | promoted bytes | units % | bytes % |",
        "|---|---:|---:|---:|---:|---:|---:|",
    ]
    for module, group in groups:
        part = totals_of(group, states)
        lines.append(
            f"| `{module}` | {part.units} | {part.promoted_units} | {_fmt(part.bytes)} | "
            f"{_fmt(part.promoted_bytes)} | {_pct(part.promoted_units, part.units)} | "
            f"{_pct(part.promoted_bytes, part.bytes)} |")
    lines.append(
        f"| **total** | **{overall.units}** | **{overall.promoted_units}** | "
        f"**{_fmt(overall.bytes)}** | **{_fmt(overall.promoted_bytes)}** | "
        f"**{_pct(overall.promoted_units, overall.units)}** | "
        f"**{_pct(overall.promoted_bytes, overall.bytes)}** |")
    lines += [
        "",
        "Legend: green = promoted (G2 green); amber = partial (draft or source, unproven); "
        "grey = untouched.",
    ]
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


def render_svg(units: list[Unit], states: dict[str, str], target: str) -> str:
    """One cell per unit, grouped and labelled by module; no scripts, no external refs."""
    overall = totals_of(units, states)
    groups = _state_groups(units, states)
    layout = _svg_layout(groups)
    height = (layout[-1]["label_y"] + layout[-1]["height"] + LEGEND
              if layout else HEADER + LEGEND)
    out = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" height="{height}" '
        f'viewBox="0 0 {WIDTH} {height}" role="img" '
        f'aria-label="{escape(target)} translation unit heatmap">',
        f'<title>{escape(target)} translation units: '
        f'{overall.promoted_units} / {overall.units} promoted</title>',
        f'<desc>One square per translation unit, grouped by module. '
        f'{_pct(overall.promoted_units, overall.units)} of units and '
        f'{_pct(overall.promoted_bytes, overall.bytes)} of retail code bytes are '
        f'promoted.</desc>',
        f'<rect width="{WIDTH}" height="{height}" fill="{PANEL}"/>',
        f'<text x="{MARGIN}" y="32" font-size="18" font-weight="600" fill="{INK}">'
        f'{escape(target)}: {overall.promoted_units} / {overall.units} units promoted '
        f'({_pct(overall.promoted_units, overall.units)})</text>',
        f'<text x="{MARGIN}" y="52" font-size="12" fill="{MUTED}">'
        f'{_fmt(overall.promoted_bytes)} / {_fmt(overall.bytes)} retail code bytes '
        f'({_pct(overall.promoted_bytes, overall.bytes)}) &#183; one cell per translation '
        f'unit &#183; hover for path, bytes and state</text>',
        f'<text x="{MARGIN}" y="76" font-size="12" fill="{MUTED}">'
        f'green = promoted (G2 green) &#183; amber = partial &#183; grey = untouched</text>',
    ]
    for band in layout:
        module = band["module"]
        group, states_here = band["group"], [states.get(unit.file, UNTOUCHED)
                                             for unit in band["group"]]
        promoted = sum(1 for state in states_here if state == PROMOTED)
        label = (f"{module} - {promoted}/{len(group)} promoted, "
                 f"{_pct(promoted, len(group))}")
        out.append(f'<g class="module" data-module="{escape(module, {chr(34): "&quot;"})}">')
        out.append(f'<text x="{MARGIN}" y="{band["label_y"]}" font-size="12" '
                   f'font-weight="600" fill="{INK}">{escape(label)}</text>')
        for x, y, unit in band["cells"]:
            state = states.get(unit.file, UNTOUCHED)
            title = f"{unit.file} - {_fmt(unit.size)} bytes - {state}"
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
    """Every local and remote branch, plus ``HEAD``; an empty list outside a git tree."""
    proc = _git("for-each-ref", "--format=%(refname:short)",
                "refs/heads", "refs/remotes")
    if proc.returncode != 0:
        return []
    refs = [line.strip() for line in proc.stdout.splitlines() if line.strip()]
    return refs


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


def collect_sources_and_drafts() -> tuple[set[str], set[str]]:
    """Unit-path sources and draft file names over every branch and the working tree."""
    sources: set[str] = set()
    drafts: set[str] = set()

    def absorb(paths: Iterable[str]) -> None:
        for path in paths:
            posix = path.replace("\\", "/")
            if posix.startswith("src/"):
                sources.add(posix)
            elif posix.startswith("drafts/"):
                drafts.add(pathlib.PurePosixPath(posix).name)

    absorb(_worktree_files(("src", "drafts")))
    for ref in ["HEAD", *branches()]:
        absorb(_tree_files(ref, ("src", "drafts")))
    return sources, drafts


def verify_units(candidates: Iterable[Unit], target) -> tuple[set[str], dict[str, str]]:
    """Run ``ddr --target T verify --tu FILE`` for each candidate; return green and failures."""
    verified: set[str] = set()
    failures: dict[str, str] = {}
    ddr = REPO_ROOT / "ddr"
    for unit in candidates:
        proc = subprocess.run([str(ddr), "--target", target.name, "verify",
                               "--tu", unit.file],
                              cwd=REPO_ROOT, capture_output=True, text=True)
        if proc.returncode == 0:
            verified.add(unit.file)
        else:
            detail = (proc.stderr or proc.stdout).strip().splitlines()
            failures[unit.file] = detail[-1] if detail else f"exit {proc.returncode}"
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


def main(argv=None) -> int:
    args = parse_args(argv)
    from config import targets  # local: the module is importable without a configured tree

    try:
        target = targets.get(args.target)
    except targets.UnknownTarget as exc:
        print(f"status: {exc}", file=sys.stderr)
        return 2
    units = load_units(target.config_dir / "cus.json")
    rows = {entry[0] for entry in target.tu_builds}

    sources, drafts = collect_sources_and_drafts()
    candidates = [unit for unit in units
                  if unit.file in sources and (args.no_verify or unit.file in rows)]
    if args.no_verify:
        verified, failures = {unit.file for unit in candidates}, {}
    else:
        verified, failures = verify_units(candidates, target)
        for file, detail in failures.items():
            print(f"status: {file}: not promoted: {detail}", file=sys.stderr)

    states = classify(units, sources, drafts, rows, verified)
    overall = totals_of(units, states)
    markdown = render_markdown(units, states, target.name)
    svg = render_svg(units, states, target.name)

    readme_text = README.read_text()
    new_readme = replace_marked(readme_text, marked_block(markdown))
    readme_changed = new_readme != readme_text
    svg_changed = not SVG.is_file() or SVG.read_text() != svg
    stale = []
    if readme_changed:
        stale.append(README)
    if svg_changed:
        stale.append(SVG)

    if args.check:
        if stale:
            for path in stale:
                print(f"status: stale: {path.relative_to(REPO_ROOT)}", file=sys.stderr)
            return 1
        print(f"status: current: {overall.promoted_units}/{overall.units} units "
              f"({_pct(overall.promoted_units, overall.units)}), "
              f"{_fmt(overall.promoted_bytes)}/{_fmt(overall.bytes)} bytes "
              f"({_pct(overall.promoted_bytes, overall.bytes)})")
        return 0

    if readme_changed:
        README.write_text(new_readme)
    if svg_changed:
        SVG.parent.mkdir(parents=True, exist_ok=True)
        SVG.write_text(svg)

    print(f"status: {overall.promoted_units}/{overall.units} units promoted "
          f"({_pct(overall.promoted_units, overall.units)}), "
          f"{_fmt(overall.promoted_bytes)}/{_fmt(overall.bytes)} retail code bytes "
          f"({_pct(overall.promoted_bytes, overall.bytes)})")
    print(f"status: README.md {'updated' if readme_changed else 'current'}; "
          f"docs/status.svg {'updated' if svg_changed else 'current'}")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except ValueError as exc:
        print(f"status: {exc}", file=sys.stderr)
        sys.exit(2)
