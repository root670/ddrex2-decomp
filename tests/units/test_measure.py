"""`measure.py`: per-body word differences, the masking rule, and the length phrases.

The comparison is exercised through the real relocation path (:func:`measure.bodies` with a
stand-in object), so the masking rule is tested where it is applied rather than on a copy of
it.  The one measured test compiles a promoted unit with its recorded pair and skips when
this checkout has no retail ELF, no fetched compiler, or no generated split tree.
"""

import pathlib
import struct
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import compile as cc, fetch, probe  # noqa: E402
from units import measure  # noqa: E402


def words(*values) -> bytes:
    """The little-endian bytes of ``values``, as an object section holds them."""
    return b"".join(struct.pack("<I", value) for value in values)


class Symbol:
    """What a relocation's last field is read for: its name."""

    def __init__(self, name):
        self.name = name


# `addiu sp,sp,-0x30`; `jal`; `lw v0,4(v0)` / `lw v1,4(v0)`.
PROLOGUE = 0x27BDFFD0
JAL = 0x0C000000
LOAD_V0 = 0x8C420004
LOAD_V1 = 0x8C430004


# ---------------------------------------------------------------------------
# the masking rule
# ---------------------------------------------------------------------------


def test_a_jump_target_is_ignored_and_the_bare_words_are_not():
    """The same two words are exact through an R_MIPS_26 and one word apart without it."""
    relocs = [(0, cc.R_MIPS_26, Symbol("callee"))]
    body = measure.compare("Fn", words(JAL | 0x20), words(JAL | 0x10), relocs)

    assert (body.differing, body.first_diff, body.exact) == (0, None, True)

    bare = measure.compare("Fn", words(JAL | 0x20), words(JAL | 0x10))
    assert (bare.differing, bare.first_diff, bare.exact) == (1, 0, False)


def test_r_mips_32_ignores_the_whole_word():
    body = measure.compare("Fn", words(0x11223344), words(0xAABBCCDD),
                           [(0, cc.R_MIPS_32, Symbol("datum"))])

    assert body.exact


@pytest.mark.parametrize("rtype", [cc.R_MIPS_HI16, cc.R_MIPS_LO16, cc.R_MIPS_GPREL16])
def test_the_address_halves_ignore_only_the_immediate(rtype):
    """`lw v0,-0x4670($gp)` against another offset is the relocation's field, not ours."""
    relocs = [(0, rtype, Symbol("datum"))]
    body = measure.compare("Fn", words(0x8F82B990), words(0x8F82B944), relocs)
    assert body.exact

    # The register *around* the immediate is not masked, so a different one still counts.
    outside = measure.compare("Fn", words(0x8F83B990), words(0x8F82B944), relocs)
    assert (outside.differing, outside.first_diff) == (1, 0)


def test_a_relocation_that_writes_nothing_masks_nothing():
    assert measure.ignored_fields([(0, cc.R_MIPS_NONE, Symbol("x"))]) == ()


def test_masking_zeroes_the_field_on_both_sides():
    masked = measure.masked(words(0x0C000020, 0x8C420004), ((0, 0x03FFFFFF),))

    assert masked == words(0x0C000000, 0x8C420004)


# ---------------------------------------------------------------------------
# the report: one line per body
# ---------------------------------------------------------------------------


class Function:
    def __init__(self, name, address, size):
        self.name, self.address, self.size = name, address, size


class Unit:
    """The three bodies of the synthetic object, laid out at consecutive addresses."""

    file = "src/example.c"
    name = "Z:\\example.c"
    address = 0x00100000
    end = 0x00100018
    functions = [Function("Exact", 0x00100000, 8),       # exact modulo a jump relocation
                 Function("Register", 0x00100008, 8),    # one register differs
                 Function("Short", 0x00100010, 8)]       # one byte short


class Object:
    """The stand-in for `compile.MWObject`: sections, their relocations, and a resolution."""

    def __init__(self):
        self.sections = {
            0: words(PROLOGUE, JAL),                 # the relocation supplies the target
            1: words(PROLOGUE, LOAD_V1),             # retail has LOAD_V0
            2: b"\xD0\xFF\xBD\x27\xD0\xFF\xBD",      # 7 bytes: one byte short
        }
        self.relocs = {0: [(4, cc.R_MIPS_26, Symbol("callee"))]}

    def groups(self, tu):
        return {function.name: (index, 0, 0)
                for index, function in enumerate(tu.functions)}

    def data(self, index):
        return self.sections[index]

    def resolve(self, tu, symbol):
        return 0x00100100


RETAIL = words(PROLOGUE, JAL | 0x10,
               PROLOGUE, LOAD_V0,
               PROLOGUE, PROLOGUE)


def measured():
    bodies = measure.bodies(Unit(), Object(), RETAIL, gp=0x002E0000)
    return measure.Measured("src/example.c", "ddrex2p", "3.0b38-030307",
                            "-c -lang c -O3 -opt full -g", bodies)


def test_every_body_gets_a_line_with_its_word_counts():
    body = measured().bodies[0]
    assert (body.name, body.ours_words, body.retail_words) == ("Exact", 2, 2)
    assert (body.differing, body.first_diff, body.exact) == (0, None, True)


def test_a_register_body_reports_its_count_and_first_difference():
    body = measured().bodies[1]
    assert (body.differing, body.first_diff, body.exact) == (1, 4, False)


def test_a_short_body_reports_the_length_phrase_not_a_word_count():
    body = measured().bodies[2]
    assert body.length_note == "short by 0x1 bytes"
    assert body.size_gap == -1
    # The word count is still measured over the common span for --json.
    assert body.differing == 0
    assert not body.exact


def test_too_large_is_the_other_phrase():
    body = measure.compare("Fn", words(PROLOGUE, PROLOGUE, PROLOGUE), words(PROLOGUE))
    assert body.length_note == "0x8 bytes too large"
    assert body.size_gap == 8


def test_the_rendered_report_carries_the_counts_the_length_line_and_the_rule():
    text = measure.render(measured())
    lines = text.splitlines()

    assert lines[0] == "measure: src/example.c (ddrex2p)"
    assert "3.0b38-030307 -c -lang c -O3 -opt full -g" in text
    assert "masking:" in text and "R_MIPS_26" in text and "EXACT" in text

    row = next(line for line in lines if line.strip().startswith("Exact "))
    assert row.split() == ["Exact", "2/2", "0", "-"]
    row = next(line for line in lines if line.strip().startswith("Register "))
    assert row.split() == ["Register", "2/2", "1", "+0x4"]
    row = next(line for line in lines if line.strip().startswith("Short "))
    assert "short by 0x1 bytes" in row
    assert row.split()[-1] == "-"
    assert "1 of 3 bodies EXACT" in text


def test_the_header_states_the_masking_rule_so_the_number_is_unambiguous():
    header = measure.MASKING_NOTE

    for name in ("R_MIPS_26", "R_MIPS_32", "R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_GPREL16"):
        assert name in header
    assert "EXACT" in header


def test_side_output_marks_the_register_that_moved():
    text = measure.render_side(measured().bodies[1])
    lines = text.splitlines()

    moved = next(line for line in lines if "rt $v0 -> $v1" in line)
    assert "0x8C420004" in moved and "0x8C430004" in moved
    # The identical prologue carries no mark.
    prologue = next(line for line in lines if line.startswith("  +0x0000"))
    assert "rt" not in prologue and "offset" not in prologue


def test_side_output_marks_a_word_that_only_the_relocation_moved():
    text = measure.render_side(measured().bodies[0])

    assert "(relocation field)" in text
    assert "jal 0x40" in text and "jal 0x100100" in text


def test_side_output_prints_the_length_line_for_a_short_body():
    text = measure.render_side(measured().bodies[2])

    assert "short by 0x1 bytes" in text
    assert "(retail only)" in text


def test_json_reports_the_measurement_and_keeps_the_common_span_count():
    report = measured().as_json()

    assert report["unit"] == "src/example.c"
    assert report["target"] == "ddrex2p"
    assert report["masked_relocations"] == ["R_MIPS_26", "R_MIPS_32", "R_MIPS_HI16",
                                            "R_MIPS_LO16", "R_MIPS_GPREL16"]
    short = next(body for body in report["bodies"] if body["name"] == "Short")
    assert (short["size_gap"], short["differing"], short["exact"]) == (-1, 0, False)


# ---------------------------------------------------------------------------
# refusals
# ---------------------------------------------------------------------------


def test_a_missing_split_tree_names_the_build():
    """A generated tree that is absent is a build shortfall, not a body of zero words."""
    target = types.SimpleNamespace(geometry_required=lambda: types.SimpleNamespace(
        code_segment="no-such-segment-for-measure-test"))
    unit = types.SimpleNamespace(file="src/example.c", functions=[])

    with pytest.raises(measure.Missing) as caught:
        measure.require_splits(unit, target)

    assert "./ddr build" in str(caught.value)


def test_a_missing_function_split_names_the_build():
    """A split tree without this body is the same shortfall, and names the same command."""
    if not (ROOT / "asm" / "nonmatchings" / "main").is_dir():
        pytest.skip("generated split tree absent")
    from config import targets

    unit = types.SimpleNamespace(
        file="src/example.c",
        functions=[types.SimpleNamespace(name="NoBodyNamedThis_measure_test")])

    with pytest.raises(measure.Missing) as caught:
        measure.require_splits(unit, targets.get())

    assert "NoBodyNamedThis_measure_test" in str(caught.value)
    assert "./ddr build" in str(caught.value)


# ---------------------------------------------------------------------------
# one real unit: a promoted source is word-exact, body by body
# ---------------------------------------------------------------------------

#: Promoted, small, and compiled by every checkout that has the pinned toolchain.
TITLE_DEMO = "src/AM/s573/demo/title_demo.c"
#: A unit the tree has not promoted: it has a CU and no `tu_builds` row.
UNPROMOTED = "src/AM/s573/doll/vu0.c"


def _needs_checkout():
    if not (ROOT / "orig" / "SLUS_211.74").is_file():
        pytest.skip("no retail ELF in this checkout: nothing to compare against")


def _measured_or_skip(unit):
    _needs_checkout()
    try:
        return measure.measure(unit)
    except measure.Missing as exc:
        pytest.skip(f"generated split tree absent: {exc}")
    except (fetch.FetchError, probe.ProbeError, FileNotFoundError, OSError) as exc:
        pytest.skip(f"recorded compiler unavailable: {exc}")


def test_every_body_of_a_promoted_unit_is_exact():
    result = _measured_or_skip(TITLE_DEMO)

    assert result.source == TITLE_DEMO
    assert result.bodies, "the unit must declare at least one body"
    for body in result.bodies:
        assert (body.name, body.differing, body.size_gap) == (body.name, 0, 0)
        assert body.exact
    assert "8 of 8 bodies EXACT" in measure.render(result)


def test_a_unit_with_no_tu_builds_row_is_refused_with_the_remedy():
    _needs_checkout()

    with pytest.raises(measure.NotPromoted) as caught:
        measure.measure(UNPROMOTED)

    message = str(caught.value)
    assert "tu_builds" in message
    assert "select_build.py" in message and "config/targets.py" in message


def test_main_exits_two_on_a_unit_with_no_measured_pair(monkeypatch, capsys):
    def refuse(*args, **kwargs):
        raise measure.NotPromoted(f"{UNPROMOTED} has no row in ddrex2p's tu_builds")

    monkeypatch.setattr(measure, "measure", refuse)

    assert measure.main([UNPROMOTED]) == 2
    assert "tu_builds" in capsys.readouterr().err
