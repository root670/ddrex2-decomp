#!/usr/bin/env python3
"""line_inventory.py -- the persisted ``.line`` record for every promoted unit.

``.line`` equality is an **iteration gate, not a promotion gate**.  While the source is being
recovered, its statements have to sit on retail's line numbers -- that is what tells an
unwritten inline from a missing declaration.  At promotion the source may be reformatted
freely and the chunk the image carries is reconstructed from retail's own inventory (the
``"adopt"`` path, or the ``.line`` half of it); the promotion proof is ``.text`` byte equality,
and the checksum that matters is the linked ELF's (``G1``).  This file is the evidence that
survives that freedom: for each promoted unit it records

* the retail ``.line`` chunk's size (the unit's contiguous run of split linetables), its table
  count and record count, and a digest of the bytes;
* what our own layout emitted -- the record count, and how many rows differ from retail's --
  measured by compiling the committed source through the unit's recorded pair with its recorded
  debug step (:func:`toolchain.compile.place`), so the measurement is the compile path itself;
* the unit's state (``tu_builds``' fourth element) and whether its emitted table still
  reproduces retail's layout or no longer corresponds to it.

The retail bytes are read from the split's ``.line`` chunk in the retail image (the same bytes
``configure.py`` cuts into ``build/assets/.line_NNN.databin.bin``), at the offset and size
``config/<target>/debug_chunks.json`` pins for the unit.

Usage::

    python3 tools/units/line_inventory.py            # rewrite docs/line-inventory.md
    python3 tools/units/line_inventory.py --check    # exit 1 if the file is stale
    python3 tools/units/line_inventory.py --target NAME
    python3 tools/units/line_inventory.py --output PATH

Exit codes: 0 written (or current), 1 ``--check`` found a stale file, 2 unusable invocation or
input (including a checkout without the retail ELF or the recorded compiler).
"""

from __future__ import annotations

import argparse
import contextlib
import dataclasses
import hashlib
import io
import pathlib
import shlex
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

OUTPUT = REPO_ROOT / "docs" / "line-inventory.md"


@dataclasses.dataclass(frozen=True)
class Record:
    """One promoted unit's line inventory, as measured."""

    unit: str
    state: str
    chunks: str
    size: int
    tables: int
    records: int
    digest: str
    emitted: int
    differ: int | None
    note: str


def _chunk_label(indices: list) -> str:
    """``"005"`` or ``"005-006"``: the split linetables' positions in the section."""
    if not indices:
        return "-"
    parts, start, previous = [], indices[0], indices[0]
    for index in indices[1:]:
        if index == previous + 1:
            previous = index
            continue
        parts.append(f"{start:03d}-{previous:03d}" if previous != start else f"{start:03d}")
        start = previous = index
    parts.append(f"{start:03d}-{previous:03d}" if previous != start else f"{start:03d}")
    return ",".join(parts)


def _digest(chunk: bytes) -> str:
    return hashlib.sha256(chunk).hexdigest()[:16]


def _differ(emitted: bytes, retail: bytes) -> tuple:
    """``(differing rows, explanation)``: the rows that are not retail's, or ``None``.

    The comparison is :func:`toolchain.debug_adopt.line_changes`, the adoption report's own
    measure: it refuses when the two chunks are not the same run of tables with the same row
    counts, because "how many rows differ" then has no aligned answer.  The refusal is
    returned as the explanation, not raised: a different shape is a fact the inventory records.
    """
    from toolchain import debug_adopt

    try:
        changes, _tables, _rows = debug_adopt.line_changes(emitted, retail)
    except debug_adopt.Refused as exc:
        return None, str(exc)
    return len(changes), None


def record(unit: str, state, chunks: str, retail: bytes, emitted: bytes) -> Record:
    """One inventory row from the retail chunk and the layout the source emitted.

    The state is kept honest here: ``False`` and ``True`` claim our own layout reproduced
    retail's ``.line``, so a measurement that contradicts that raises instead of being
    recorded.  ``"adopt"`` claims retail's chunk was substituted, and the note says whether
    the emitted table nevertheless reproduced it (adoption supplied ``.debug`` metadata only)
    or no longer corresponds to it (the source was reformatted / re-laid-out).
    """
    from toolchain import debug_adopt

    tables, records = debug_adopt.line_shape(retail)
    emitted_records = debug_adopt.line_shape(emitted)[1]
    differ, because = _differ(emitted, retail)
    reproduced = emitted == retail
    if state in (False, True):
        if not reproduced:
            detail = because or f"{differ} row(s) differ"
            raise ValueError(
                f"{unit}: tu_builds records {state!r} -- our own layout reproduced retail's "
                f".line -- but the emitted table has {emitted_records} record(s) against "
                f"retail's {records}: {detail}")
        note = "our layout reproduces retail's table"
    elif state == "adopt":
        if reproduced:
            note = "layout reproduces retail's table; adoption supplied .debug metadata only"
        elif differ is None:
            note = (f"layout no longer corresponds to retail's table: emitted "
                    f"{emitted_records} record(s), retail {records} ({because}); retail's "
                    f"chunk is adopted")
        else:
            note = (f"layout no longer corresponds to retail's table: {differ} of "
                    f"{records} row(s) differ; retail's chunk is adopted")
    else:
        raise ValueError(f"{unit}: unknown tu_builds state {state!r}")
    return Record(unit, str(state), chunks, len(retail), tables, records, _digest(retail),
                  emitted_records, differ, note)


def collect(target, verbose: bool = False) -> list:
    """Measure every promoted unit of ``target``, in address order.

    The compile is the unit's own path: its recorded compiler build, its recorded flags, and
    the debug step its state names.  Under ``"adopt"`` the emitted table is the report's
    pre-adoption measurement (:attr:`toolchain.compile.Placed.emitted_line`), which is exactly
    what "what our own layout would produce" means.
    """
    from toolchain import check_deps, compile as cc, fetch

    manifests = cc.Manifests(target)
    builds = target.build_table()
    if not builds:
        return []
    compiler_dirs = {}
    wibo = None
    rows = []
    with tempfile.TemporaryDirectory(prefix="line-inventory-") as scratch:
        scratch = pathlib.Path(scratch)
        for number, file in enumerate(sorted(builds, key=lambda name: manifests.tu_named(name).address)):
            version, flags, state = builds[file]
            if not (REPO_ROOT / file).is_file():
                raise cc.Unusable(f"{file}: tu_builds names a source that does not exist")
            tu = manifests.tu_named(file)
            if wibo is None:
                wibo = fetch.wibo()
            if version not in compiler_dirs:
                compiler_dirs[version] = fetch.compiler(version)
            retail = cc.retail_bytes(tu, target.elf)["line"]
            captured = io.StringIO()
            try:
                with contextlib.redirect_stderr(captured):
                    placed = cc.place(
                        tu, manifests, compiler_dirs[version], wibo, shlex.split(flags),
                        keep=scratch / f"{number:03d}.mw.o",
                        normalise=(state is True), adopt=(state == "adopt"))
            except Exception:
                if captured.getvalue():
                    print(captured.getvalue().rstrip(), file=sys.stderr)
                raise
            if verbose and captured.getvalue():
                print(captured.getvalue().rstrip(), file=sys.stderr)
            rows.append(record(tu.file, state,
                               _chunk_label(manifests.line_chunk_indices(tu)),
                               retail, placed.emitted_line))
    return rows


def render(rows: list, target) -> str:
    """The generated Markdown document, byte-for-byte, for ``rows``."""
    lines = [
        "<!-- generated by tools/units/line_inventory.py; do not edit by hand -->",
        "# Line inventory",
        "",
        "The retail `.line` record for every promoted unit, and how close our own layout came",
        "to it.  The retail bytes are the unit's run of split linetables (the same bytes",
        "`configure.py` cuts into `build/assets/.line_NNN.databin.bin`).",
        "",
        "**`.line` equality is an iteration gate, not a promotion gate.**  While a unit is",
        "being recovered its statements must sit on retail's line numbers -- that is the",
        "evidence that tells a missing declaration or inline from a guess.  At promotion the",
        "source may be reformatted freely and the chunk the image carries is reconstructed",
        "from retail's inventory.  The promotion proof is `.text` byte equality (and `.debug`",
        "under its own rules); the checksum that matters is the linked ELF's, `G1`",
        f"`{target.elf_sha256[:8]}...{target.elf_sha256[-5:]}`.",
        "",
        "`state` is `tu_builds`' fourth element: `False` means no debug step, `True` the DIE",
        "order normaliser, `adopt` retail metadata adoption.  `False` and `True` are a claim",
        "that our own emitted table reproduced retail's, so this generator fails when a",
        "measurement contradicts them; an `adopt` unit whose layout no longer corresponds to",
        "retail's says so in the note.  `emitted` and `differ` are measured by compiling the",
        "committed source through the unit's recorded pair and debug step.  `differ` is `-`",
        "when the two chunks are not the same run of tables with the same row counts, so no",
        "row-for-row answer exists; the note explains the shape mismatch.",
        "",
        f"`python3 tools/units/line_inventory.py --check` fails when this file is stale.",
        "",
        "| unit | state | split line chunks | bytes | tables | records | sha256 | emitted | differ | note |",
        "|---|---|---|---|---|---|---|---|---|---|",
    ]
    for row in rows:
        differ = "-" if row.differ is None else str(row.differ)
        lines.append(
            f"| `{row.unit}` | {row.state} | {row.chunks} | 0x{row.size:X} | {row.tables} | "
            f"{row.records} | `{row.digest}` | {row.emitted} | {differ} | {row.note} |")
    lines.append("")
    return "\n".join(lines)


def parse_args(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--target", default=None,
                        help="the target whose tu_builds and retail ELF are read "
                             "(default: the registered target)")
    parser.add_argument("--check", action="store_true",
                        help="compare the generated file, write nothing; exit 1 if stale")
    parser.add_argument("--output", type=pathlib.Path, default=OUTPUT,
                        help=f"the generated file (default: {OUTPUT.relative_to(REPO_ROOT)})")
    parser.add_argument("-v", "--verbose", action="store_true",
                        help="print the compiler/adoption report for every unit")
    return parser.parse_args(argv)


def resolve_target(name=None):
    """The target ``--target`` names (a seam the tests use in place of the registry)."""
    from config import targets

    return targets.get(name)


def main(argv=None) -> int:
    args = parse_args(argv)
    from config import targets
    from toolchain import check_deps, compile as cc, fetch

    try:
        target = resolve_target(args.target)
        rows = collect(target, verbose=args.verbose)
        text = render(rows, target)
    except targets.UnknownTarget as exc:
        print(f"line_inventory: {exc}", file=sys.stderr)
        return 2
    except (cc.Unusable, fetch.FetchError, check_deps.MissingDependency, ValueError) as exc:
        print(f"line_inventory: {exc}", file=sys.stderr)
        return 2

    path = pathlib.Path(args.output)
    current = path.read_text() if path.is_file() else None
    stale = current != text
    if args.check:
        if stale:
            try:
                shown = path.relative_to(REPO_ROOT)
            except ValueError:
                shown = path
            print(f"line_inventory: stale: {shown}", file=sys.stderr)
            return 1
        print(f"line_inventory: current ({len(rows)} promoted unit(s))")
        return 0

    if stale:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    try:
        shown = path.relative_to(REPO_ROOT)
    except ValueError:
        shown = path
    print(f"line_inventory: {shown} {'updated' if stale else 'current'} "
          f"({len(rows)} promoted unit(s))")
    return 0


if __name__ == "__main__":
    sys.exit(main())
