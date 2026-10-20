"""Synthetic tests for ``tools/units/status.py``.

The status generator has three output contracts and each is tested without the repository's
real trees: classification from a manifest plus four sets of facts, completion arithmetic over
three denominators (units, split functions and split code bytes), and the two artefacts -- a
README block that is stable between its markers and an SVG whose cell count *is* the
translation-unit count.  The split fixture is splat's own shape, so the parser and the
module attribution are exercised too.  Nothing here runs ``ddr``, a compiler, or ``git``.
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

#: One function per unit, each span exactly the unit's size; two splits no CU claims.
FUNCTIONS = [
    (0x1000, 100, "sys_a"),
    (0x1100, 200, "dm_b"),
    (0x1200, 300, "dm_c"),
    (0x1400, 400, "dm_d"),
    (0x1600, 50, "root_unit"),
    (0x1700, 500, "dm_e"),
    (0x1900, 25, "dm_f"),
    (0x1A00, 75, "libstr3"),
]

RECORDS = [{"kind": "tu", "file": unit.file, "size": unit.size} for unit in UNITS]
RECORDS += [{"kind": "function", "file": unit.file, "low_pc": address,
             "high_pc": address + size, "name": name}
            for unit, (address, size, name) in zip(UNITS, FUNCTIONS)]

SPLITS = [st.Split(address, size, name) for address, size, name in FUNCTIONS]
SPLITS += [st.Split(0x9000, 20, "write"),          # named, no CU -> (library)
           st.Split(0x9100, 30, "func_009100")]   # unnamed, no CU -> (unattributed)


def fixture():
    units = st.units_of(RECORDS)
    return units, st.code_of(RECORDS, SPLITS)


# ---------------------------------------------------------------------------
# manifests and splits
# ---------------------------------------------------------------------------


def test_manifest_reads_only_tu_records_in_order(tmp_path):
    manifest = tmp_path / "cus.json"
    manifest.write_text(json.dumps([
        {"kind": "tu", "file": "src/a.c", "size": 10},
        {"kind": "function", "file": "src/a.c", "size": 999, "low_pc": 1, "high_pc": 2},
        {"kind": "tu", "file": "src/b.c", "size": 20},
    ]))

    units = st.load_units(manifest)

    assert units == [U("src/a.c", 10), U("src/b.c", 20)]


def test_manifest_with_no_tu_records_is_refused(tmp_path):
    manifest = tmp_path / "cus.json"
    manifest.write_text(json.dumps([{"kind": "function", "file": "src/a.c", "size": 10}]))

    with pytest.raises(SystemExit):
        st.load_units(manifest)


def test_splits_parse_sizes_addresses_and_skip_data_declarations(tmp_path):
    asm = tmp_path / "asm/nonmatchings/main"
    asm.mkdir(parents=True)
    (asm / "a.s").write_text(
        '.include "macro.inc"\nnonmatching sys_a, 0x64\n\nglabel sys_a\n'
        "    /* 1000 00101000 00000000 */  nop\n")
    (asm / "b.s").write_text(
        'nonmatching data_obj\n\ndlabel data_obj\n    /* 2000 */ .space 0x10\n')

    splits = st.load_splits(tmp_path / "asm")

    assert splits == [st.Split(0x101000, 0x64, "sys_a")]


def test_no_sized_splits_is_a_loud_stop(tmp_path):
    (tmp_path / "asm/nonmatchings/main").mkdir(parents=True)
    with pytest.raises(SystemExit):
        st.load_splits(tmp_path / "asm")


def test_unit_code_counts_functions_and_uses_the_pinned_text_span():
    counts, spans = st.unit_code(RECORDS)

    assert counts["src/sys/sys_a.c"] == 1
    assert spans["src/sys/sys_a.c"] == 112   # 100 rounded to the 16-byte function alignment
    assert spans["libstr3.c"] == 80         # 75 rounded up


def test_promoted_text_is_the_sum_of_aligned_function_spans():
    # The five promoted units' measured .text sizes: 64, 192, 2384, 464 and 80 bytes.
    records = [
        {"kind": "function", "file": "a.c", "low_pc": 0x1000, "high_pc": 0x100C},  # 12
        {"kind": "function", "file": "a.c", "low_pc": 0x1010, "high_pc": 0x1040},  # 48
        {"kind": "function", "file": "b.c", "low_pc": 0x2000, "high_pc": 0x2068},  # 104
        {"kind": "function", "file": "b.c", "low_pc": 0x2070, "high_pc": 0x20B8},  # 72
        {"kind": "function", "file": "c.c", "low_pc": 0x3000, "high_pc": 0x3044},  # 68
    ]

    _, spans = st.unit_code(records)

    assert spans == {"a.c": 64, "b.c": 192, "c.c": 80}
    assert sum(spans.values()) == 336
    # 0x40 + 0xC0 + 0x50 for these three; the full five-unit total is 3,184.
    assert st.percent(3184, 1631596) < 0.2


# ---------------------------------------------------------------------------
# classification
# ---------------------------------------------------------------------------


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
# completion arithmetic
# ---------------------------------------------------------------------------


def test_code_bytes_are_split_sizes_and_promoted_bytes_are_the_text_span():
    units, code = fixture()
    promoted = {"src/sys/sys_a.c"}

    totals = st.totals_of(units, st.classify(
        units, sources=promoted, drafts=set(), rows=promoted, verified=promoted), code)

    assert totals.units == 8
    assert totals.functions == 10              # 8 unit splits + library + unattributed
    assert totals.code_bytes == 1700           # 1,650 unit bytes + 20 + 30
    assert totals.promoted_units == 1
    assert totals.promoted_functions == 1
    assert totals.promoted_code_bytes == 112   # 100 rounded to the pinned .text size
    assert totals.unit_percent == pytest.approx(12.5)
    assert totals.function_percent == pytest.approx(10.0)
    assert totals.code_percent == pytest.approx(100 * 112 / 1700)


def test_split_code_is_attributed_by_the_dwarf_function_start():
    _, code = fixture()

    assert code.fact_of("sys") == st.CodeFact(2, 125)
    assert code.fact_of("CS") == st.CodeFact(2, 500)
    assert code.fact_of(st.LIBRARY) == st.CodeFact(1, 20)
    assert code.fact_of(st.UNATTRIBUTED) == st.CodeFact(1, 30)
    assert sum(fact.functions for fact in code.by_module.values()) == 10
    assert sum(fact.code_bytes for fact in code.by_module.values()) == 1700


def test_percentages_pin_the_measured_repository_arithmetic():
    # 5 promoted units, 11 reconstructed functions, 3,184 pinned .text bytes;
    # 249 units, 4,463 split functions, 1,631,596 split code bytes.
    assert f"{st.percent(5, 249):.1f}%" == "2.0%"
    assert f"{st.percent(11, 4463):.2f}%" == "0.25%"
    assert f"{st.percent(3184, 1631596):.2f}%" == "0.20%"
    assert st.percent(3184, 1631596) == pytest.approx(0.1951463475, rel=1e-9)


def test_a_zero_denominator_is_zero_percent_not_a_division_error():
    assert st.percent(0, 0) == 0.0
    assert st.percent(3, 0) == 0.0
    empty = st.Totals(0, 0, 0, 0, 0, 0)
    assert empty.unit_percent == empty.function_percent == empty.code_percent == 0.0


def test_module_is_the_directory_after_src():
    assert st.module_of("src/CS/dance/dm_b.c") == "CS"
    assert st.module_of("src/CS/dm_c.c") == "CS"
    assert st.module_of("src/root_unit.c") == "(root)"
    assert st.module_of("libstr3.c") == "(external)"


def test_markdown_labels_all_three_denominators_and_one_legend_line():
    units, code = fixture()
    states = st.classify(units, sources={"src/sys/sys_a.c"}, drafts={"dm_d.c"},
                         rows={"src/sys/sys_a.c"}, verified={"src/sys/sys_a.c"})

    markdown = st.render_markdown(units, states, "synthetic", code)
    lines = markdown.splitlines()

    assert ("**Overall: 1 / 8 translation units promoted (12.5%); "
            "1 / 10 functions reconstructed (10.00%); "
            "112 / 1,700 code bytes reconstructed (6.59%).**") in lines
    assert "| module | units | promoted units | functions |" in markdown
    assert any(line.startswith("| `CS` |") for line in lines)
    assert any(line.startswith("| `(root)` |") for line in lines)
    assert any(line.startswith("| `(external)` |") for line in lines)
    assert any(line.startswith("| `(library)` |") for line in lines)
    assert any(line.startswith("| `(unattributed)` |") for line in lines)
    legends = [line for line in lines if line.startswith("Legend:")]
    assert len(legends) == 1


# ---------------------------------------------------------------------------
# README marker idempotence
# ---------------------------------------------------------------------------

BASE = ("# Project\n\nIntro paragraph.\n\n## The gates\n\n"
        "A gate is a digest.\n\n## Licence\n\nText.\n")


def test_markers_are_inserted_above_the_gates_and_rerun_is_byte_identical():
    units, code = fixture()
    states = {unit.file: st.UNTOUCHED for unit in units}
    block = st.marked_block(st.render_markdown(units, states, "synthetic", code))

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
    units, code = fixture()
    states = st.classify(units, sources={"src/sys/sys_a.c", "src/CS/dance/dm_b.c"},
                         drafts={"dm_d.c"}, rows={"src/sys/sys_a.c"},
                         verified={"src/sys/sys_a.c"})

    svg = st.render_svg(units, states, "synthetic", code)
    root = ET.fromstring(svg)

    cells = [element for element in root.iter()
             if _local(element.tag) == "rect" and element.get("class") == "cell"]
    assert len(cells) == len(units)
    assert {cell.get("data-state") for cell in cells} == {
        st.PROMOTED, st.PARTIAL, st.UNTOUCHED}
    assert all(cell.get("fill") in st.COLOURS.values() for cell in cells)


def test_every_svg_cell_names_its_path_code_bytes_and_state():
    units, code = fixture()
    states = st.classify(units, sources={"src/sys/sys_a.c"}, drafts=set(),
                         rows={"src/sys/sys_a.c"}, verified={"src/sys/sys_a.c"})

    root = ET.fromstring(st.render_svg(units, states, "synthetic", code))
    titles = {_title_of(cell): cell.get("data-state") for cell in root.iter()
              if _local(cell.tag) == "rect" and cell.get("class") == "cell"}

    for unit in units:
        state = states[unit.file]
        title = f"{unit.file} - {code.bytes_by_file[unit.file]:,} code bytes - {state}"
        assert title in titles
        assert titles[title] == state


def test_svg_is_grouped_by_module_and_is_github_sized():
    units, code = fixture()
    states = {unit.file: st.UNTOUCHED for unit in units}
    svg = st.render_svg(units, states, "synthetic", code)
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
