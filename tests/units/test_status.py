"""Synthetic tests for ``tools/units/status.py``.

The status generator has three output contracts and each is tested without the repository's
real trees: classification from a manifest plus four sets of facts, percentage arithmetic with
a zero denominator, and the two artefacts -- a README block that is stable between its markers
and an SVG whose cell count *is* the translation-unit count.  Nothing here runs ``ddr``, a
compiler, or ``git``; the real regeneration is the command's own job.
"""

from __future__ import annotations

import json
import pathlib
import sys
import xml.etree.ElementTree as ET

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))

from units import status as st  # noqa: E402


def U(file, size):
    return st.Unit(file, size)


UNITS = [
    U("src/sys/sys_a.c", 100),
    U("src/CS/dance/dm_b.c", 200),
    U("src/CS/dm_c.c", 300),
    U("src/AM/s573/dm_d.c", 400),
    U("src/root_unit.c", 50),
    U("src/gs/dm_e.c", 500),
    U("src/sys/dm_f.c", 25),
    U("libstr3.c", 75),
]


# ---------------------------------------------------------------------------
# manifest and classification
# ---------------------------------------------------------------------------


def test_manifest_reads_only_tu_records_in_order(tmp_path):
    manifest = tmp_path / "cus.json"
    manifest.write_text(json.dumps([
        {"kind": "tu", "file": "src/a.c", "size": 10},
        {"kind": "function", "file": "src/a.c", "size": 999},
        {"kind": "tu", "file": "src/b.c", "size": 20},
    ]))

    units = st.load_units(manifest)

    assert units == [U("src/a.c", 10), U("src/b.c", 20)]


def test_manifest_with_no_tu_records_is_refused(tmp_path):
    manifest = tmp_path / "cus.json"
    manifest.write_text(json.dumps([{"kind": "function", "file": "src/a.c", "size": 10}]))

    with pytest.raises(SystemExit):
        st.load_units(manifest)


def test_classification_covers_all_three_states():
    sources = {"src/sys/sys_a.c", "src/CS/dance/dm_b.c", "src/CS/dm_c.c",
               "src/root_unit.c", "src/gs/dm_e.c", "src/sys/dm_f.c"}
    drafts = {"dm_d.c"}                     # a draft on some branch, no source
    rows = {"src/sys/sys_a.c", "src/sys/dm_f.c"}   # f has a row but no green verdict
    verified = {"src/sys/sys_a.c"}

    states = st.classify(UNITS, sources, drafts, rows, verified)

    assert states["src/sys/sys_a.c"] == st.PROMOTED       # source + row + gate
    assert states["src/CS/dance/dm_b.c"] == st.PARTIAL    # source without a row
    assert states["src/CS/dm_c.c"] == st.PARTIAL
    assert states["src/AM/s573/dm_d.c"] == st.PARTIAL     # draft, no source
    assert states["src/root_unit.c"] == st.PARTIAL
    assert states["src/gs/dm_e.c"] == st.PARTIAL
    assert states["src/sys/dm_f.c"] == st.PARTIAL         # row, source, red verdict
    assert states["libstr3.c"] == st.UNTOUCHED            # no work anywhere


def test_a_loaded_synthetic_manifest_classifies_end_to_end(tmp_path):
    manifest = tmp_path / "cus.json"
    manifest.write_text(json.dumps([
        {"kind": "tu", "file": "src/sys/promoted.c", "size": 10},
        {"kind": "tu", "file": "src/sys/partial.c", "size": 20},
        {"kind": "tu", "file": "src/sys/untouched.c", "size": 30},
    ]))

    units = st.load_units(manifest)
    states = st.classify(units,
                         sources={"src/sys/promoted.c", "src/sys/partial.c"},
                         drafts=set(),
                         rows={"src/sys/promoted.c"},
                         verified={"src/sys/promoted.c"})

    assert [states[unit.file] for unit in units] == [
        st.PROMOTED, st.PARTIAL, st.UNTOUCHED]


def test_a_row_without_a_source_is_partial_not_promoted():
    states = st.classify([U("src/sys/gone.c", 10)], sources=set(), drafts=set(),
                         rows={"src/sys/gone.c"}, verified={"src/sys/gone.c"})

    assert states["src/sys/gone.c"] == st.PARTIAL


def test_verified_without_a_row_or_source_is_never_promoted():
    states = st.classify([U("src/sys/a.c", 10)], sources={"src/sys/a.c"},
                         drafts=set(), rows=set(), verified={"src/sys/a.c"})

    assert states["src/sys/a.c"] == st.PARTIAL


# ---------------------------------------------------------------------------
# arithmetic
# ---------------------------------------------------------------------------


def test_percentages_are_by_units_and_by_bytes():
    totals = st.totals_of(UNITS, st.classify(
        UNITS,
        sources={"src/sys/sys_a.c"},
        drafts=set(),
        rows={"src/sys/sys_a.c"},
        verified={"src/sys/sys_a.c"}))

    assert totals.units == 8
    assert totals.bytes == 100 + 200 + 300 + 400 + 50 + 500 + 25 + 75
    assert totals.promoted_units == 1
    assert totals.promoted_bytes == 100
    assert totals.unit_percent == pytest.approx(12.5)
    assert totals.byte_percent == pytest.approx(100 * 100 / 1650)


def test_a_zero_denominator_is_zero_percent_not_a_division_error():
    assert st.percent(0, 0) == 0.0
    assert st.percent(3, 0) == 0.0
    assert st.totals_of([], {}).unit_percent == 0.0


def test_module_is_the_directory_after_src():
    assert st.module_of("src/CS/dance/dm_b.c") == "CS"
    assert st.module_of("src/CS/dm_c.c") == "CS"
    assert st.module_of("src/root_unit.c") == "(root)"
    assert st.module_of("libstr3.c") == "(external)"


def test_markdown_reports_both_denominators_and_one_legend_line():
    states = st.classify(UNITS, sources={"src/sys/sys_a.c"}, drafts={"dm_d.c"},
                         rows={"src/sys/sys_a.c"}, verified={"src/sys/sys_a.c"})

    markdown = st.render_markdown(UNITS, states, "synthetic")
    lines = markdown.splitlines()

    assert "**Overall: 1 / 8 translation units promoted (12.5%); " \
           "100 / 1,650 retail code bytes (6.1%).**" in lines
    assert any(line.startswith("| `CS` |") for line in lines)
    assert any(line.startswith("| `(root)` |") for line in lines)
    assert any(line.startswith("| `(external)` |") for line in lines)
    legends = [line for line in lines if line.startswith("Legend:")]
    assert len(legends) == 1


# ---------------------------------------------------------------------------
# README marker idempotence
# ---------------------------------------------------------------------------


BASE = ("# Project\n\nIntro paragraph.\n\n## The gates\n\n"
        "A gate is a digest.\n\n## Licence\n\nText.\n")


def test_markers_are_inserted_above_the_gates_and_rerun_is_byte_identical():
    block = st.marked_block(st.render_markdown(UNITS, {
        unit.file: st.UNTOUCHED for unit in UNITS}, "synthetic"))

    once = st.replace_marked(BASE, block)
    twice = st.replace_marked(once, block)

    assert twice == once
    assert once.count(st.START) == 1 and once.count(st.END) == 1
    assert once.index("## Progress") < once.index("## The gates")
    assert "Intro paragraph." in once and "A gate is a digest." in once


def test_a_rerun_rewrites_only_the_marked_block():
    block = st.marked_block("old body\n")
    once = st.replace_marked(BASE, block)
    changed = st.replace_marked(once, st.marked_block("new body\n"))

    assert changed.count(st.START) == 1 and changed.count(st.END) == 1
    assert "old body" not in changed
    assert "new body" in changed
    assert changed[:changed.index(st.START)] == once[:once.index(st.START)]
    assert changed[changed.index(st.END):] == once[once.index(st.END):]


def test_one_marker_alone_is_refused():
    with pytest.raises(ValueError):
        st.replace_marked("# Project\n\n" + st.START + "\n", st.marked_block("x\n"))


# ---------------------------------------------------------------------------
# SVG heatmap
# ---------------------------------------------------------------------------


def _local(tag):
    return tag.rsplit("}", 1)[-1]


def _title_of(element):
    for child in element:
        if _local(child.tag) == "title":
            return child.text
    return None


def test_svg_is_well_formed_and_has_one_cell_per_unit():
    states = st.classify(UNITS, sources={"src/sys/sys_a.c", "src/CS/dance/dm_b.c"},
                         drafts={"dm_d.c"}, rows={"src/sys/sys_a.c"},
                         verified={"src/sys/sys_a.c"})

    svg = st.render_svg(UNITS, states, "synthetic")
    root = ET.fromstring(svg)

    cells = [element for element in root.iter()
             if _local(element.tag) == "rect" and element.get("class") == "cell"]
    assert len(cells) == len(UNITS)
    assert {cell.get("data-state") for cell in cells} == {
        st.PROMOTED, st.PARTIAL, st.UNTOUCHED}
    assert all(cell.get("fill") in st.COLOURS.values() for cell in cells)


def test_every_svg_cell_names_its_path_bytes_and_state():
    states = st.classify(UNITS, sources={"src/sys/sys_a.c"}, drafts=set(),
                         rows={"src/sys/sys_a.c"}, verified={"src/sys/sys_a.c"})

    root = ET.fromstring(st.render_svg(UNITS, states, "synthetic"))
    titles = {_title_of(cell): cell.get("data-state") for cell in root.iter()
              if _local(cell.tag) == "rect" and cell.get("class") == "cell"}

    for unit in UNITS:
        state = states[unit.file]
        title = f"{unit.file} - {unit.size} bytes - {state}"
        assert title in titles
        assert titles[title] == state


def test_svg_is_grouped_by_module_and_is_github_sized():
    states = {unit.file: st.UNTOUCHED for unit in UNITS}
    svg = st.render_svg(UNITS, states, "synthetic")
    root = ET.fromstring(svg)

    groups = [element for element in root.iter()
              if _local(element.tag) == "g" and element.get("class") == "module"]
    assert {group.get("data-module") for group in groups} == {
        "sys", "CS", "AM", "(root)", "gs", "(external)"}
    assert int(root.get("width")) <= 900
    assert int(root.get("height")) > 0
    assert "<script" not in svg
    assert "href=" not in svg
    assert "http://" not in svg.replace("http://www.w3.org/2000/svg", "")
