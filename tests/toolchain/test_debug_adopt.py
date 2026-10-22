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
from toolchain import debug_set as ds  # noqa: E402
from tests.toolchain.test_debug_normalize import Die, Lazy, build  # noqa: E402
from tests.toolchain.test_debug_set import _attribute, _encoded_length  # noqa: E402

AT_ARRAY_TYPE = 0x0001
AT_SIBLING = 0x0012
AT_BYTE_SIZE = 0x00B6
AT_FUND_TYPE = 0x0055
AT_LOCATION = 0x0023
AT_NAME = 0x0038
AT_USER_DEF_TYPE = 0x0072
AT_2303 = 0x2303

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


def block_tree(extra_local):
    """A CU whose function holds a block that is empty in retail and has a local in ours.

    Dropping that local empties the block's child chain, so the chain's four-byte
    terminator is not part of the layout either -- the shape that leaves the block's,
    the function's and the CU's ``AT_sibling`` stale if the drop only removes records.
    """
    block = Die(0x000B, [(AT_NAME, "b")])
    if extra_local:
        block.children.append(
            Die(0x000C, [(AT_NAME, "t"), (AT_FUND_TYPE, 8), (AT_LOCATION, register(2))]))
    body = Die(0x0006, [(AT_NAME, "f")], [block])
    return Die(0x0011, [(AT_NAME, "p_anime.c")], [body])


def encode_tree(root, without_sibling=None):
    """Encode ``root``, omitting ``without_sibling``'s own ``AT_sibling`` word.

    The fixture encoder always writes the word; this variant exists to build the corrupt
    record the normaliser must refuse -- a DIE with children and no positional target.
    """
    cursor = [0]

    def record_size(die):
        own = 6 + sum(_encoded_length(code, value) for code, value in die.attrs)
        return own + (0 if die is without_sibling else 6)

    def subtree_length(die):
        total = record_size(die)
        if die.children:
            total += sum(subtree_length(child) for child in die.children) + 4
        return total

    def assign(die):
        die.offset = cursor[0]
        cursor[0] += record_size(die)
        for child in die.children:
            assign(child)
        if die.children:
            cursor[0] += 4

    assign(root)

    def value(one):
        if isinstance(one, Die):
            return one.offset
        if isinstance(one, Lazy):
            return one.render()
        return one

    def encode(die):
        body = struct.pack("<H", die.tag)
        for code, one in die.attrs:
            body += _attribute(code, value(one))
        if die is not without_sibling:
            body += _attribute(AT_SIBLING, die.offset + subtree_length(die))
        record = struct.pack("<I", len(body) + 4) + body
        children = b"".join(encode(child) for child in die.children)
        return record + (children + b"\x00\x00\x00\x00" if die.children else b"")

    return encode(root)


def test_dropping_a_chain_recomputes_every_surviving_sibling(capsys):
    """The block loses its only record: its terminator and every enclosing word move."""
    retail = build(block_tree(extra_local=False))
    emitted = build(block_tree(extra_local=True))
    assert len(emitted) > len(retail), "the local and its chain terminator are extra"

    adopted = da.adopt(emitted, retail, 0, OURS_LINE, RETAIL_LINE)

    assert adopted.chunk == retail
    assert [die.tag for die, _span in adopted.dropped] == [0x000C]

    block = next(die for die in ds.parse(retail, 0) if die.tag == 0x000B)
    rewrites = [change for change in adopted.sibling_changes
                if "lexical_block" in change[2]]
    assert rewrites, "the emptied block's AT_sibling is recomputed"
    assert rewrites[0][1] == block.attrs[AT_SIBLING], "it names the laid-out chain end"
    assert rewrites[0][0] != rewrites[0][1], "the emitted word pointed past the layout"
    assert any("global_subroutine" in change[2] for change in adopted.sibling_changes)
    assert any("compile_unit" in change[2] for change in adopted.sibling_changes)

    placed = cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=emitted,
                                retail_text=b"code", retail_line=RETAIL_LINE,
                                retail_debug=retail, adopt=True)

    assert placed == retail
    error = capsys.readouterr().err
    assert "dropped extra DIE +0x" in error
    assert "recomputed AT_sibling 0x" in error
    assert "lexical_block" in error
    assert "byte for byte after adoption" in error


def test_a_missing_sibling_target_refuses():
    """Retail's record carries a positional word ours has not: it cannot be recomputed."""
    retail = build(block_tree(extra_local=False))
    our_tree = block_tree(extra_local=True)
    block = our_tree.children[0].children[0]
    emitted = encode_tree(our_tree, without_sibling=block)

    with pytest.raises(da.Refused) as excinfo:
        da.adopt(emitted, retail, 0, OURS_LINE, RETAIL_LINE)

    message = str(excinfo.value)
    assert "lexical_block 'b'" in message
    assert "attribute 0x0012" in message
    assert "no counterpart in the emitted record" in message


def struct_array_twin(duplicate):
    """A struct whose two ``float[4]`` members share one array type in retail.

    The fp_qmenu shape: the twin type records are CU children and the two references come
    from *member* DIEs, not from locals.  Dropping the extra type still has to retarget the
    member that named it at the survivor.
    """
    first = Die(AT_ARRAY_TYPE, [(AT_BYTE_SIZE, 16)])
    second = Die(AT_ARRAY_TYPE, [(AT_BYTE_SIZE, 16)]) if duplicate else first
    types = [first] + ([second] if duplicate else [])
    members = [Die(0x000D, [(AT_NAME, "cam_p"), (AT_USER_DEF_TYPE, first),
                            (AT_LOCATION, register(2))]),
               Die(0x000D, [(AT_NAME, "eye_p"), (AT_USER_DEF_TYPE, second),
                            (AT_LOCATION, register(3))])]
    aggregate = Die(0x0013, [(AT_NAME, "@anon1"), (AT_BYTE_SIZE, 32)], members)
    return Die(0x0011, [(AT_NAME, "p_anime.c")], types + [aggregate]), second


def test_a_duplicate_type_record_is_absorbed_by_a_struct_member(capsys):
    """A type record referenced from a member is droppable like any identical twin."""
    retail_tree, retail_array = struct_array_twin(duplicate=False)
    retail = build(retail_tree)
    our_tree, extra_array = struct_array_twin(duplicate=True)
    emitted = build(our_tree)

    adopted = da.adopt(emitted, retail, 0, OURS_LINE, RETAIL_LINE)

    assert adopted.chunk == retail
    assert [die.tag for die, _span in adopted.dropped] == [AT_ARRAY_TYPE]
    redirects = [change for change in adopted.reference_changes
                 if change[0] == extra_array.offset]
    assert redirects, "eye_p's AT_type is retargeted at the surviving array"
    assert redirects[0][1] == retail_array.offset
    assert all("member 'eye_p'" in change[2] for change in redirects)

    placed = cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=emitted,
                                retail_text=b"code", retail_line=RETAIL_LINE,
                                retail_debug=retail, adopt=True)

    assert placed == retail
    error = capsys.readouterr().err
    assert "dropped extra DIE +0x" in error
    assert "array_type" in error
    assert "rewrote reference" in error
    assert "byte for byte after adoption" in error


def twin_tree(duplicate):
    """Retail shares one array type between two locals; our compiler emitted two.

    The two array DIEs are structurally identical (same tag, same size), so either may
    stand for retail's one -- but each local names a different one on our side.  Dropping
    the extra therefore has to retarget one surviving local's reference at the survivor:
    the interchangeable-duplicate rule the pairing already uses.
    """
    first = Die(AT_ARRAY_TYPE, [(AT_BYTE_SIZE, 16)])
    second = Die(AT_ARRAY_TYPE, [(AT_BYTE_SIZE, 16)]) if duplicate else first
    types = [first] + ([second] if duplicate else [])
    locals_ = [Die(0x000C, [(AT_NAME, "n"), (AT_USER_DEF_TYPE, first),
                            (AT_LOCATION, register(6))]),
               Die(0x000C, [(AT_NAME, "m"), (AT_USER_DEF_TYPE, second),
                            (AT_LOCATION, register(7))])]
    body = Die(0x0006, [(AT_NAME, "f")], locals_)
    aggregate = Die(0x0013, [(AT_NAME, "@anon1"), (AT_BYTE_SIZE, 4)])
    return Die(0x0011, [(AT_NAME, "p_anime.c")], types + [body, aggregate]), second


def test_a_duplicate_record_is_dropped_and_its_reference_redirected(capsys):
    """Two identical type records where retail has one: one is dropped, refs follow it."""
    retail_tree, retail_array = twin_tree(duplicate=False)
    retail = build(retail_tree)
    our_tree, extra_array = twin_tree(duplicate=True)
    emitted = build(our_tree)

    adopted = da.adopt(emitted, retail, 0, OURS_LINE, RETAIL_LINE)

    assert adopted.chunk == retail
    assert [die.tag for die, _span in adopted.dropped] == [AT_ARRAY_TYPE]
    assert adopted.dropped[0][0].name is None, "the array type is unnamed"
    redirects = [change for change in adopted.reference_changes
                 if change[0] == extra_array.offset]
    assert redirects, "m's reference to the dropped twin is rewritten"
    assert redirects[0][1] == retail_array.offset, "it lands on the surviving twin"

    placed = cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=emitted,
                                retail_text=b"code", retail_line=RETAIL_LINE,
                                retail_debug=retail, adopt=True)

    assert placed == retail
    error = capsys.readouterr().err
    assert "dropped extra DIE +0x" in error
    assert "array_type" in error
    assert "rewrote reference" in error
    assert "byte for byte after adoption" in error


def test_a_reference_to_a_dropped_record_without_a_twin_refuses():
    """No identical survivor means the reference's meaning would change: adoption refuses."""
    shared_retail = Die(AT_ARRAY_TYPE, [(AT_BYTE_SIZE, 16)])
    local_retail = Die(0x000C, [
        (AT_NAME, "n"), (AT_FUND_TYPE, 8),
        (AT_2303, Lazy(4, lambda: struct.pack("<I", shared_retail.offset)))])
    body_retail = Die(0x0006, [(AT_NAME, "f")], [local_retail])
    retail = build(Die(0x0011, [(AT_NAME, "p_anime.c")],
                       [shared_retail, body_retail]))

    shared = Die(AT_ARRAY_TYPE, [(AT_BYTE_SIZE, 16)])
    extra = Die(AT_ARRAY_TYPE, [(AT_BYTE_SIZE, 32)])
    local = Die(0x000C, [
        (AT_NAME, "n"), (AT_FUND_TYPE, 8),
        (AT_2303, Lazy(4, lambda: struct.pack("<I", extra.offset)))])
    body = Die(0x0006, [(AT_NAME, "f")], [local])
    emitted = build(Die(0x0011, [(AT_NAME, "p_anime.c")],
                        [shared, extra, body]))

    with pytest.raises(da.Refused) as excinfo:
        da.adopt(emitted, retail, 0, OURS_LINE, RETAIL_LINE)

    message = str(excinfo.value)
    assert "points at a DIE dropped as an extra record" in message
    assert "retail carries no such target" in message


def test_a_drop_that_still_leaves_a_difference_refuses():
    """Dropping is not a licence to accept: the remaining chunk must be retail's bytes."""
    retail = build(tree(location=6, anon="@anon1")) + b"\x00\x00\x00\x00"
    extra = tree(location=2, anon="@anon0")
    extra.children[0].children.append(
        Die(0x000C, [(AT_NAME, "t"), (AT_FUND_TYPE, 8), (AT_LOCATION, register(2))]))
    emitted = build(extra) + b"\x01\x00\x00\x00"
    assert len(emitted) > len(retail)

    with pytest.raises(da.Refused) as excinfo:
        da.adopt(emitted, retail, 0, OURS_LINE, RETAIL_LINE)

    assert "the adopted chunk is not retail's" in str(excinfo.value)


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


def test_equal_debug_does_not_excuse_a_different_line_chunk():
    """Every part the state advertises is checked; one part's equality cannot skip another.

    A state-``True`` row claims ``.text``, ``.line`` and the normalised ``.debug`` are all
    retail's.  When ``.debug`` is already equal, that claim about ``.line`` still has to be
    proven: returning early on the ``.debug`` equality let a mistaken ``True`` row compile
    while ``--compare`` reported ``line DIFFERS``.  Adoption is the state that substitutes
    ``.line`` by design, so the same unit is accepted there.
    """
    debug = build(tree())

    with pytest.raises(cc.Unusable) as excinfo:
        cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=debug,
                           retail_text=b"code", retail_line=RETAIL_LINE,
                           retail_debug=debug, normalise=True)

    assert "condition 1 (.text and .line byte-equal) failed: .line is" in str(excinfo.value)

    placed = cc.debug_promotion(UNIT, text=b"code", line=OURS_LINE, debug=debug,
                                retail_text=b"code", retail_line=RETAIL_LINE,
                                retail_debug=debug, adopt=True)

    assert placed == debug


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
