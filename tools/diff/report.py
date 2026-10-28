#!/usr/bin/env python3
"""What objdiff's report is allowed to say: never a data percentage with no data measured.

``objdiff-cli report generate`` reports a unit as code *and* data, and it divides the two
matches by their totals.  An empty denominator is printed as 100%: a unit whose target
object carries no data symbols gets ``matched_data_percent: 100.0`` with no ``total_data``
at all.  Every unit of this project's objdiff project is that unit -- its target objects
hold the unit's ``.text`` and nothing else, because data stays pinned retail bytes by
design (``AGENTS.md`` rule 9) and G1, not this report, is what proves those bytes -- so the
raw report advertises "100% data" for a tree in which no datum is reconstructed from C.

``prune`` therefore drops a data measure that was never measured instead of printing 100%
for it:

* when ``total_data`` is absent or zero, ``matched_data_percent``/``complete_data_percent``
  and the byte counts (``matched_data``/``complete_data``/``total_data``, zero or absent)
  are removed from that measures object -- the report makes no claim about data;
* a zero denominator with a non-zero numerator is a refusal, never arithmetic: it means
  objdiff (or a hand-edited report) is claiming matched data it did not count, and papering
  over that is exactly the fabrication this module exists to remove;
* a measure with a real denominator is left exactly as objdiff computed it, so running this
  over a project that does reconstruct data changes nothing.

The percentages decmp.dev shows are whatever the report says, so the artifact the workflow
uploads must be the pruned one; ``progress.yml`` runs this after ``report generate``.

Usage::

    objdiff-cli report generate -o build/report.json
    python3 tools/diff/report.py build/report.json

Exit codes: 0 the report was checked (and pruned), 2 a report whose data arithmetic is
inconsistent, 1 the file could not be read or parsed.
"""

from __future__ import annotations

import argparse
import json
import pathlib
import sys

#: The percentage fields objdiff derives from the data denominator.
DATA_PERCENT_KEYS = ("matched_data_percent", "complete_data_percent")
#: The byte counts those percentages are derived from.
DATA_BYTE_KEYS = ("total_data", "matched_data", "complete_data")


def _count(measures: dict, key: str) -> int:
    """A byte count as an int.  objdiff writes ``u64`` as a JSON string; absent means zero."""
    value = measures.get(key)
    if value is None or value == "":
        return 0
    try:
        return int(value)
    except (TypeError, ValueError):
        raise ValueError(f"{key} is {value!r}, not a byte count") from None


def pruned(measures: dict) -> dict:
    """``measures`` without the data fields of an empty denominator.

    Returns a new dict; the input is not mutated.  A non-zero ``total_data`` is returned
    unchanged, so this is only ever a removal of the fabricated 100%.
    """
    if _count(measures, "total_data"):
        return dict(measures)
    claimed = _count(measures, "matched_data") + _count(measures, "complete_data")
    if claimed:
        raise ValueError(
            f"a measures object claims {claimed} matched data bytes with no data denominator; "
            f"the ratio is undefined and must not be printed as a percentage: {measures!r}")
    return {key: value for key, value in measures.items()
            if key not in DATA_PERCENT_KEYS + DATA_BYTE_KEYS}


def _prune_measures(holder: dict) -> bool:
    """Prune ``holder["measures"]`` in place; whether it had data fields to remove."""
    measures = holder.get("measures")
    if not isinstance(measures, dict):
        return False
    pruned_measures = pruned(measures)
    if pruned_measures == measures:
        return False
    holder["measures"] = pruned_measures
    return True


def prune(report: dict) -> tuple[dict, int]:
    """``report`` with fabricated data measures removed; ``(report, objects_pruned)``.

    Every measures object objdiff's schema has is visited: the report's own, each unit's,
    and each progress category's.  The report is copied, not mutated.
    """
    report = json.loads(json.dumps(report))          # deep copy: the input is the caller's
    pruned_objects = int(_prune_measures(report))
    for key in ("units", "categories"):
        for holder in report.get(key) or []:
            if isinstance(holder, dict) and _prune_measures(holder):
                pruned_objects += 1
    return report, pruned_objects


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("report", type=pathlib.Path,
                        help="the report objdiff-cli wrote (rewritten in place)")
    parser.add_argument("-o", "--output", type=pathlib.Path, default=None,
                        help="write the pruned report here instead of in place")
    args = parser.parse_args(sys.argv[1:] if argv is None else argv)
    try:
        report = json.loads(args.report.read_text())
    except OSError as exc:
        print(f"report.py: error: {exc}", file=sys.stderr)
        return 1
    except json.JSONDecodeError as exc:
        print(f"report.py: error: {args.report} is not JSON: {exc}", file=sys.stderr)
        return 1
    try:
        pruned_report, removed = prune(report)
    except ValueError as exc:
        print(f"report.py: error: {exc}", file=sys.stderr)
        return 2
    out = args.output or args.report
    out.write_text(json.dumps(pruned_report, indent=2) + "\n")
    if removed:
        print(f"report: removed fabricated data measures from {removed} measures object"
              f"{'s' if removed != 1 else ''} (no data bytes were measured)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
