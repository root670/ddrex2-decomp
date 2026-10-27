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
import re
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


def test_unit_split_shares_come_from_the_same_splits_as_the_denominator():
    _, code = fixture()

    assert code.functions_by_file["src/sys/sys_a.c"] == 1
    assert code.bytes_by_file["src/sys/sys_a.c"] == 100
    assert code.bytes_by_file["libstr3.c"] == 75
    # Every per-file byte is one of the module denominators' bytes: a promoted unit's
    # share can never exceed its module's total.
    assert sum(code.bytes_by_file.values()) <= code.splits.code_bytes


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


def test_code_bytes_are_split_sizes_and_a_promoted_unit_counts_its_share():
    units, code = fixture()
    promoted = {"src/sys/sys_a.c"}

    totals = st.stats_of(units, st.classify(
        units, sources=promoted, drafts=set(), rows=promoted, verified=promoted), code)

    assert totals.units == 8
    assert totals.functions == 10              # 8 unit splits + library + unattributed
    assert totals.code_bytes == 1700           # 1,650 unit bytes + 20 + 30
    assert totals.promoted_units == 1
    assert totals.promoted_functions == 1
    assert totals.promoted_code_bytes == 100   # the split's declaration, not a padded span
    assert totals.unit_percent == pytest.approx(12.5)
    assert totals.function_percent == pytest.approx(10.0)
    assert totals.code_percent == pytest.approx(100 * 100 / 1700)


def test_a_promoted_unit_whose_padded_span_exceeds_its_size_still_reads_100_percent():
    # sys's real shape: 12 + 40 + 28 = 80 bytes of code, but MWCC's 16-byte function
    # alignment makes the object's .text 16 + 48 + 32 = 96.  Counting the padded span read
    # "96 of 80" (120%); the split declaration is the unit's whole manifest size, so the
    # row is 80/80 and the ceiling holds.
    records = [
        {"kind": "tu", "file": "src/sys/sys_a.c", "size": 80},
        {"kind": "function", "file": "src/sys/sys_a.c", "low_pc": 0x1000, "high_pc": 0x100C},
        {"kind": "function", "file": "src/sys/sys_a.c", "low_pc": 0x1010, "high_pc": 0x1038},
        {"kind": "function", "file": "src/sys/sys_a.c", "low_pc": 0x1040, "high_pc": 0x105C},
    ]
    splits = [st.Split(0x1000, 12, "a"), st.Split(0x1010, 40, "b"),
              st.Split(0x1040, 28, "c")]
    units = st.units_of(records)
    code = st.code_of(records, splits)
    promoted = {"src/sys/sys_a.c"}

    assert code.bytes_by_file == {"src/sys/sys_a.c": 80}     # not 16 + 48 + 32
    totals = st.stats_of(units, st.classify(
        units, sources=promoted, drafts=set(), rows=promoted, verified=promoted), code)
    assert totals.promoted_code_bytes == 80
    assert totals.code_percent == 100.0
    assert totals.cells()[-1] == "80/80 (100.0%)"


def test_a_numerator_above_its_denominator_is_refused_not_printed():
    # The old 96-of-80 sys row cannot be constructed at all: the row itself refuses it.
    with pytest.raises(ValueError):
        st.Stats(units=1, promoted_units=1, functions=4, promoted_functions=4,
                 code_bytes=80, promoted_code_bytes=96)
    assert st.Stats(1, 1, 4, 4, 80, 80).code_percent == 100.0


def test_every_cell_is_promoted_over_total_with_one_decimal():
    assert st.cell(8, 18) == "8/18 (44.4%)"
    assert st.cell(44, 182) == "44/182 (24.2%)"
    assert st.cell(45168, 1631596) == "45,168/1,631,596 (2.8%)"
    assert st.cell(3, 4) == "3/4 (75.0%)"
    assert st.cell(0, 0) == "0/0 (0.0%)"


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
    empty = st.Stats(0, 0, 0, 0, 0, 0)
    assert empty.unit_percent == empty.function_percent == empty.code_percent == 0.0
    assert empty.cells() == ("0/0 (0.0%)", "0/0 (0.0%)", "0/0 (0.0%)")


def test_module_is_the_directory_after_src():
    assert st.module_of("src/CS/dance/dm_b.c") == "CS"
    assert st.module_of("src/CS/dm_c.c") == "CS"
    assert st.module_of("src/root_unit.c") == "(root)"
    assert st.module_of("libstr3.c") == "(external)"


def test_markdown_is_a_summary_line_and_the_three_column_table():
    units, code = fixture()
    states = st.classify(units, sources={"src/sys/sys_a.c"}, drafts={"dm_d.c"},
                         rows={"src/sys/sys_a.c"}, verified={"src/sys/sys_a.c"})

    markdown = st.render_markdown(units, states, "synthetic", code)
    lines = markdown.splitlines()

    assert lines[0] == (
        "**1/8 (12.5%) units · 1/10 (10.0%) functions · 100/1,700 (5.9%) code bytes "
        "reconstructed** — green = promoted, amber = partial, grey = untouched; "
        "`tools/units/status.py` counts only what `./ddr verify --tu` confirms.")
    assert lines[1] == ""
    assert lines[2] == "| module | units | functions | reconstructed bytes |"
    assert lines[3] == "|---|---:|---:|---:|"
    assert any(line.startswith("| `sys` |") for line in lines)
    # A module with nothing promoted is not a repeated row: the overall line counts it and
    # the heatmap keeps its band.
    assert not any(line.startswith("| `(library)` |") for line in lines)
    assert not any(line.startswith("| `(unattributed)` |") for line in lines)
    assert len(lines) <= 12


CELL = re.compile(r"^\d[\d,]*/\d[\d,]* \(\d+\.\d%\)$")


def _table_rows(markdown):
    return [line for line in markdown.splitlines() if line.startswith("|")]


def test_every_table_row_has_the_module_and_three_promoted_over_total_cells():
    units, code = fixture()
    states = st.classify(units, sources={"src/sys/sys_a.c"}, drafts=set(),
                         rows={"src/sys/sys_a.c"}, verified={"src/sys/sys_a.c"})
    rows = _table_rows(st.render_markdown(units, states, "synthetic", code))

    assert rows[0] == "| module | units | functions | reconstructed bytes |"
    assert rows[1] == "|---|---:|---:|---:|"
    for row in rows[2:]:
        cells = [cell.strip().strip("*") for cell in row.strip("|").split("|")]
        assert len(cells) == 4, row
        assert cells[0], row
        for cell in cells[1:]:
            assert CELL.match(cell), f"{row}: {cell!r}"
            assert float(cell.rsplit("(", 1)[1].rstrip("%)")) <= 100.0, row

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


def test_svg_prints_the_tables_own_cells_for_every_row_and_the_overall_line():
    units, code = fixture()
    states = st.classify(units, sources={"src/sys/sys_a.c", "src/CS/dance/dm_b.c"},
                         drafts=set(), rows={"src/sys/sys_a.c", "src/CS/dance/dm_b.c"},
                         verified={"src/sys/sys_a.c"})
    markdown = st.render_markdown(units, states, "synthetic", code)
    svg = st.render_svg(units, states, "synthetic", code)
    rows = _table_rows(markdown)

    for row in rows[2:]:
        name = row.split("|")[1].strip().strip("`")
        if f'data-module="{name}"' not in svg:
            continue                      # a split-only group has no module band
        cells = [cell.strip() for cell in row.strip("|").split("|")][1:]
        label = (f"{name} - {cells[0]} units \u00b7 {cells[1]} functions"
                 f" \u00b7 {cells[2]} bytes")
        assert label in svg, label

    summary = markdown.splitlines()[0]
    assert re.findall(r"\d[\d,]*/\d[\d,]* \(\d+\.\d%\)", summary)
    for cell in re.findall(r"\d[\d,]*/\d[\d,]* \(\d+\.\d%\)", summary):
        assert cell in svg, cell


# ---------------------------------------------------------------------------
# writing, checking and stale evidence
# ---------------------------------------------------------------------------


def test_the_write_path_updates_only_what_changed_and_check_never_writes(tmp_path):
    readme, svg = tmp_path / "README.md", tmp_path / "docs/status.svg"
    readme.write_text(BASE)
    block, picture = "**Over: 1/2 (50.0%).**\n", "<svg/>\n"

    changed = st.apply_artifacts(readme, svg, block, picture)

    assert changed == [readme, svg]
    assert st.START in readme.read_text() and st.END in readme.read_text()
    assert svg.read_text() == picture
    # A second identical run is a no-op, and --check agrees without touching either file.
    assert st.apply_artifacts(readme, svg, block, picture) == []
    assert st.apply_artifacts(readme, svg, block, picture, check=True) == []
    before = readme.read_text()
    assert st.apply_artifacts(readme, svg, "new body\n", picture, check=True) == [readme]
    assert readme.read_text() == before


def _fake_gate(tmp_path, body: str) -> pathlib.Path:
    script = tmp_path / "ddr"
    script.write_text("#!/bin/sh\n" + body)
    script.chmod(0o755)
    return script


class _Target:
    name = "synthetic"


def test_a_gate_refusal_is_a_loud_stale_evidence_stop_not_a_smaller_count(tmp_path):
    gate = _fake_gate(tmp_path, "echo 'src/sys/a.c: its object build/src/sys/a.c.o is "
                                "missing: run ./ddr build, then verify again' >&2\nexit 2\n")

    with pytest.raises(st.StaleEvidence) as caught:
        st.verify_units([U("src/sys/a.c", 100)], _Target(), ddr=gate)

    assert "src/sys/a.c" in str(caught.value)
    assert "missing" in str(caught.value)


def test_a_real_verdict_failure_is_partial_and_a_missing_file_is_fatal(tmp_path):
    gate = _fake_gate(tmp_path, "echo 'src/sys/a.c: text FAIL'\nexit 1\n")

    verified, failures = st.verify_units([U("src/sys/a.c", 100)], _Target(), ddr=gate)

    assert verified == set()
    assert failures == {"src/sys/a.c": "src/sys/a.c: text FAIL"}


def test_main_exits_two_naming_the_stale_unit(monkeypatch, capsys, tmp_path):
    from config import targets as target_module
    unit = U("src/sys/a.c", 100)
    monkeypatch.setattr(target_module, "get", lambda name=None: type(
        "T", (), {"name": "synthetic", "config_dir": tmp_path,
                  "tu_builds": [("src/sys/a.c", "cc", "flags")]})())
    monkeypatch.setattr(st, "read_records", lambda path: [])
    monkeypatch.setattr(st, "units_of", lambda records: [unit])
    monkeypatch.setattr(st, "load_splits", lambda root: [st.Split(0x1000, 100, "a")])
    monkeypatch.setattr(st, "collect_sources_and_drafts", lambda: ({"src/sys/a.c"}, set()))
    monkeypatch.setattr(st, "verify_units", lambda candidates, target: (_ for _ in ()).throw(
        st.StaleEvidence("src/sys/a.c: its object is missing: run ./ddr build")))

    assert st.main(["--target", "synthetic"]) == 2
    err = capsys.readouterr().err
    assert "stale evidence" in err and "src/sys/a.c" in err
