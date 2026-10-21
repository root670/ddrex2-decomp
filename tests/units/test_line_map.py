"""The per-unit line map: the retail statement shape, its hints, and the CLI.

The pure tests build a synthetic function out of a real ``.line`` table, so the shape rules
(multi-row lines, gaps, brace anchors, alignment) are checked without the retail image or a
compiler.  The measured tests read three units of different shapes: ``net_win_item`` (clean,
aligned), ``dmm_chara`` (a collapsed reconstruction, so its numbers are a hint but its source
cannot answer them) and ``shop_list`` (functions in a different order from retail, with a
jump-table dispatch).  They skip when the retail ELF is absent.
"""

import json
import pathlib
import struct
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))

from units import line_map as lm  # noqa: E402

RETAIL = ROOT / "orig" / "SLUS_211.74"
ALIGNED = "src/network/net_window/net_win_item.c"
COLLAPSED = "src/CS/dancemaster/dmm_chara.c"
REORDERED = "src/CS/shop/shop_list.c"


def table(base: int, rows: list) -> bytes:
    """One DWARF 1 statement table: ``(length, base)`` then ``(line, position, delta)``."""
    body = b"".join(struct.pack("<IHI", *row) for row in rows)
    return struct.pack("<II", 8 + len(body), base) + body


def function(name: str, address: int, size: int):
    return types.SimpleNamespace(name=name, address=address, size=size,
                                 line_offset=0, line_size=0)


SYNTHETIC = table(0x1000, [(5, 0, 0), (5, 0, 4), (6, 0, 8), (8, 0, 12), (0, 0, 16)])


def synthetic_map() -> lm.FunctionMap:
    return lm._function_map(function("f", 0x1000, 16), SYNTHETIC)


def test_a_function_map_counts_the_rows_and_keeps_the_end_marker():
    mapped = synthetic_map()

    assert mapped.tables == 1
    assert len(mapped.rows) == 5
    assert len(mapped.statements) == 4
    assert mapped.span == (5, 8)
    assert mapped.words == 4
    assert mapped.rows[-1].is_end


def test_multi_rows_names_every_line_with_more_than_one_row():
    assert lm.multi_rows(synthetic_map()) == [(5, 5, 2)]


def test_gaps_are_the_interior_lines_with_no_row():
    assert lm.gaps(synthetic_map()) == [(7, 7)]


def test_a_consecutive_run_of_equal_counts_is_one_token():
    mapped = lm._function_map(function("f", 0x1000, 16),
                              table(0x1000, [(3, 0, 0), (3, 0, 4), (4, 0, 8), (4, 0, 12),
                                             (0, 0, 16)]))
    runs = lm.multi_rows(mapped)

    assert runs == [(3, 4, 2)]
    assert lm._token(*runs[0]) == "3-4x2"


def test_braces_are_the_rows_on_a_source_line_containing_a_brace():
    source = ("void f(void) {", "", "", "", "    }", "    }", "", "    foo();")

    assert lm.braces(synthetic_map(), source) == [5, 6]
    assert lm.braces(synthetic_map(), None) is None


def test_alignment_requires_each_span_inside_its_own_source_body():
    source = ("void a(void) {", "    one();", "}", "void b(void) {", "    two();", "}")
    inside = lm._function_map(function("b", 0x2000, 12),
                              table(0x2000, [(5, 0, 0), (0, 0, 4)]))

    assert lm._aligned([inside], source)
    assert not lm._aligned([inside], ("void a(void) {", "    one();", "}"))


def test_a_reordered_source_is_not_aligned_even_when_the_names_exist():
    source = ("void a(void) {", "    one();", "}", "void b(void) {", "    two();", "}")
    # b's retail body is line 1, but line 1 is inside a's current body.
    wrong = lm._function_map(function("b", 0x2000, 12),
                             table(0x2000, [(2, 0, 0), (0, 0, 4)]))

    assert not lm._aligned([wrong], source)


def test_prototypes_and_initialisers_are_not_definitions():
    source = ("void a(void);", "int (*table[1])(void) = { a };", "void b(void) {", "}")

    assert lm._definitions(source) == [(3, "b")]


def test_the_decoder_agrees_with_the_adoption_path():
    from toolchain import debug_adopt

    assert debug_adopt.line_shape(SYNTHETIC) == (1, 5)
    assert len(debug_adopt.line_rows(SYNTHETIC)[0][2]) == 5


# ---------------------------------------------------------------------------
# the measured units
# ---------------------------------------------------------------------------

requires_retail = pytest.mark.skipif(not RETAIL.is_file(),
                                     reason="retail ELF is not in this checkout")


def target():
    from config import targets

    return targets.get("ddrex2p")


@pytest.fixture(scope="module")
def aligned():
    return lm.collect(ALIGNED, target())


@requires_retail
def test_the_aligned_unit_maps_each_function_from_its_own_chunk(aligned):
    names = [function.name for function in aligned.functions]

    assert names[0] == "NetWin_ItemSetSelect"
    first = aligned.functions[0]
    assert first.address == 0x22E740
    assert first.rows[-1].is_end and first.rows[-1].delta == first.size
    assert len(first.rows) == 94
    assert first.span == (452, 528)
    assert (460, 461, 2) in lm.multi_rows(first)
    assert aligned.source_note is None
    assert 452 in lm.braces(first, aligned.source)


@requires_retail
def test_the_aligned_units_output_stays_compact_and_deterministic(aligned):
    text = lm.render(aligned)

    assert text == lm.render(aligned)
    assert len(text.splitlines()) <= 40
    assert "multi 460-461x2" in text
    assert "brace 452" in text


@requires_retail
def test_json_is_the_same_map_with_every_row(aligned):
    document = json.loads(lm.as_json(aligned))

    assert document["unit"] == ALIGNED
    assert document["source"] == ALIGNED
    first = document["functions"][0]
    assert [first["rows"][0], first["rows"][-1]] == [[452, 65535, 0],
                                                     [0, 65535, first["size"]]]
    assert first["statements"] == 93
    assert first["multi"][0] == [460, 461, 2]
    assert first["braces"] is not None


@requires_retail
def test_raw_prints_every_row_in_order(aligned):
    lines = lm.render_raw(aligned).splitlines()
    total = sum(len(function.rows) for function in aligned.functions)

    assert len(lines) == total + len(aligned.functions)
    assert "  line 452 +0x0000  pos 0xFFFF" in lines
    assert "  end      +0x03F0  pos 0xFFFF" in lines


@requires_retail
def test_a_collapsed_source_gets_no_brace_hints():
    unit = lm.collect(COLLAPSED, target())

    assert unit.functions[0].span == (33, 101)
    assert unit.source is None
    assert "brace hints omitted" in unit.source_note
    assert "    brace " not in lm.render(unit)


@requires_retail
def test_a_reordered_unit_keeps_the_statement_map_but_loses_the_brace_hint():
    unit = lm.collect(REORDERED, target())
    names = [function.name for function in unit.functions]

    assert names[0] == "shop_make_contents_list_other"
    assert len(unit.functions) == 7
    assert unit.functions[0].span == (389, 442)
    assert unit.source is None and "brace hints omitted" in unit.source_note
    assert len(lm.render(unit).splitlines()) <= 40


# ---------------------------------------------------------------------------
# the CLI
# ---------------------------------------------------------------------------


@requires_retail
def test_the_cli_prints_the_map_and_the_json_document(capsys):
    assert lm.main(["--tu", ALIGNED]) == 0
    text = capsys.readouterr().out
    assert text.startswith(f"{ALIGNED} — retail statement map")

    assert lm.main(["--tu", ALIGNED, "--json"]) == 0
    document = json.loads(capsys.readouterr().out)
    assert len(document["functions"]) == 6


@requires_retail
def test_an_unknown_unit_is_a_usage_error(capsys):
    assert lm.main(["--tu", "src/nowhere/nothing.c"]) == 2
    assert "no translation unit matches" in capsys.readouterr().err


def test_raw_and_json_are_mutually_exclusive():
    with pytest.raises(SystemExit):
        lm.parse_args(["--tu", ALIGNED, "--raw", "--json"])
