"""The opt-in retail-metadata adoption: .line, AT_location, and the identity proof.

The contract has two halves: a ``.text``-exact unit whose only residue is retail's statement
table and a local's register adopts both and comes out retail's ``.debug`` bytes, and a unit
that differs in anything adoption does not cover refuses -- including the count difference
(an extra local DIE) that no metadata step can repair.  The report is checked as part of the
acceptance: the number of ``.line`` rows changed and every adopted location's before/after
values are printed.

Chunks are synthetic (the DWARF 1 encoder ``tests.toolchain.test_debug_normalize`` uses), so
no compiler is needed: what is under test is the adoption and the proof, not the compiler's
output.  The real p_anime proof lives in the unit's ``tu_builds`` comment.
"""

import pathlib
import struct
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import compile as cc  # noqa: E402
from toolchain import debug_adopt as da  # noqa: E402
from tests.toolchain.test_debug_normalize import Die, build  # noqa: E402

AT_BYTE_SIZE = 0x00B6
AT_FUND_TYPE = 0x0055
AT_LOCATION = 0x0023
AT_NAME = 0x0038

UNIT = "src/AM/s573/play/p_anime.c"


def register(n):
    """A DWARF 1 location expression: ``DW_OP_REGn``.

    Register 2 is MW's ``scratch`` placeholder, so this is the measured ``n`` case:
    ``scratch -> $a2``.
    """
    return b"\x01" + struct.pack("<I", n)


def tree(location=2, anon="@anon0"):
    """A CU with one function and one local, plus one anonymous aggregate."""
    local = Die(0x000C, [(AT_NAME, "n"), (AT_FUND_TYPE, 8),
                         (AT_LOCATION, register(location))])
    body = Die(0x0006, [(AT_NAME, "f")], [local])
    aggregate = Die(0x0013, [(AT_NAME, anon), (AT_BYTE_SIZE, 4)])
    return Die(0x0011, [(AT_NAME, "p_anime.c")], [body, aggregate])


def line_chunk(rows, base=0x1C5B40):
    """One DWARF 1 statement-list table: a header, then 10-byte ``(line, pos, delta)`` rows."""
    out = struct.pack("<II", 8 + 10 * len(rows), base)
    for row in rows:
        out += struct.pack("<IHI", *row)
    return out


OURS_LINE = line_chunk([(10, 0, 0), (12, 0, 4), (0, 0, 8)])
RETAIL_LINE = line_chunk([(10, 0, 0), (11, 0, 4), (0, 0, 8)])


def test_metadata_is_adopted_and_every_value_is_reported(capsys):
    retail = build(tree(location=6, anon="@anon1"))
    emitted = build(tree(location=2, anon="@anon0"))
    assert emitted != retail

    placed = cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=emitted,
                                retail_text=b"code", retail_line=RETAIL_LINE,
                                retail_debug=retail, adopt=True)

    assert placed == retail
    error = capsys.readouterr().err
    assert "adopted retail's .line (emitted 3 record(s), adopted 3;" in error
    assert "1 row(s) changed by statement line" in error
    assert "first at .line+0x12: 12 -> 11" in error
    assert "1 of 3 rows byte-different" in error
    assert "adopted AT_location n (in f): scratch -> $a2" in error
    assert "adopted anonymous name @anon0 -> @anon1" in error
    assert "byte for byte after adoption" in error
    assert "tu_builds comment" in error
    assert "--adopt-retail-meta" in error


def test_the_adoption_returns_retails_line_chunk_whole():
    retail_debug = build(tree(location=6, anon="@anon1"))
    emitted_debug = build(tree(location=2, anon="@anon0"))

    adopted = da.adopt(emitted_debug, retail_debug, 0, OURS_LINE, RETAIL_LINE)

    assert adopted.chunk == retail_debug
    assert adopted.line == RETAIL_LINE
    assert adopted.line_emitted == 3 and adopted.line_total == 3
    assert adopted.line_changed == 1
    assert adopted.first_line_row == (0, 1, 0x12, 12, 11)
    assert len(adopted.line_rows) == 1
    table, row, before, after = adopted.line_rows[0]
    assert (table, row) == (0, 1)
    assert before[1][0] == 12 and after[1][0] == 11
    assert [str(change) for change in adopted.locations] == ["n (in f): scratch -> $a2"]
    assert [str(change) for change in adopted.anon_names] == ["@anon0 -> @anon1"]


def test_a_unit_whose_text_differs_refuses_loudly():
    retail = build(tree(location=6, anon="@anon1"))
    emitted = build(tree(location=2, anon="@anon0"))

    with pytest.raises(cc.Unusable) as excinfo:
        cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=emitted,
                           retail_text=b"codf", retail_line=RETAIL_LINE,
                           retail_debug=retail, adopt=True)

    message = str(excinfo.value)
    assert "refusing to adopt retail's metadata" in message
    assert ".text" in message
    assert "first differing byte at 0x3" in message


def test_an_extra_die_is_dropped_and_reported(capsys):
    """Our extra local has no retail counterpart: it is dropped, and the bytes are the proof."""
    retail = build(tree(location=6, anon="@anon1"))
    extra = tree(location=2, anon="@anon0")
    extra.children[0].children.append(
        Die(0x000C, [(AT_NAME, "t"), (AT_FUND_TYPE, 8), (AT_LOCATION, register(2))]))
    emitted = build(extra)
    assert len(emitted) > len(retail)

    placed = cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=emitted,
                                retail_text=b"code", retail_line=RETAIL_LINE,
                                retail_debug=retail, adopt=True)

    assert placed == retail
    error = capsys.readouterr().err
    assert "dropped extra DIE +0x" in error
    assert "local_variable 't'" in error
    assert "no counterpart in retail" in error
    assert "byte for byte after adoption" in error


def test_a_missing_die_refuses(capsys):
    """Retail has a record we do not: fabricating it would be invention, not adoption."""
    retail_extra = tree(location=6, anon="@anon1")
    retail_extra.children[0].children.append(
        Die(0x000C, [(AT_NAME, "t"), (AT_FUND_TYPE, 8), (AT_LOCATION, register(6))]))
    retail = build(retail_extra)
    emitted = build(tree(location=6, anon="@anon1"))
    assert len(emitted) < len(retail)

    with pytest.raises(cc.Unusable) as excinfo:
        cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=emitted,
                           retail_text=b"code", retail_line=RETAIL_LINE,
                           retail_debug=retail, adopt=True)

    message = str(excinfo.value)
    assert "condition 6 (retail metadata adoption) failed" in message
    assert "missing record is not fabricated" in message
    assert not capsys.readouterr().err.count("dropped extra DIE")


def test_adoption_refuses_a_chunk_that_does_not_come_out_identical():
    """Same DIEs and same length, but a tail byte retail's chunk does not have."""
    retail = build(tree(location=6, anon="@anon1")) + b"\x00\x00\x00\x00"
    emitted = build(tree(location=6, anon="@anon1")) + b"\x01\x00\x00\x00"

    with pytest.raises(da.Refused) as excinfo:
        da.adopt(emitted, retail, 0, OURS_LINE, RETAIL_LINE)

    assert "the adopted chunk is not retail's" in str(excinfo.value)
    assert "first difference" in str(excinfo.value)


def test_a_line_table_of_a_different_shape_is_reported_and_retail_is_adopted():
    """A normalised layout can emit a different number of rows; retail's chunk is adopted."""
    other = line_chunk([(10, 0, 0), (11, 0, 4)])

    result = da.adopt(build(tree()), build(tree()), 0, other, RETAIL_LINE)

    assert "holds 2 rows against retail's 3" in (result.line_note or "")
    assert result.line_rows == []
    assert result.line_emitted == 2 and result.line_total == 3
    assert result.line == RETAIL_LINE, "the emitted table is replaced whole"
    assert result.chunk == build(tree())


def test_a_short_line_chunk_is_accepted_under_adopt_and_reported(capsys):
    """Adoption is independent of the emitted `.line` length: `.text` is the precondition.

    The emitted table carries 2 records against retail's 3 (the measured decodeVAG shape:
    MWCC sinks a record into the next statement's line).  The unit is accepted because its
    `.text` is retail's, retail's chunk is placed, and the report says how short it was.
    """
    debug = build(tree(location=6, anon="@anon1"))
    short = line_chunk([(10, 0, 0), (11, 0, 4)])

    placed = cc.debug_promotion(UNIT, text=b"code", line=short, debug=debug,
                                retail_text=b"code", retail_line=RETAIL_LINE,
                                retail_debug=debug, adopt=True)

    assert placed == debug
    error = capsys.readouterr().err
    assert "emitted 2 record(s), adopted 3" in error
    assert "not row-for-row comparable" in error
    assert "retail's chunk is adopted whole" in error
    assert "byte for byte after adoption" in error
