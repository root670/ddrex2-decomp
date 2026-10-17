"""A promotion fills the extent it replaces, and refuses when it cannot.

Two couplings here are the kind only a synthetic test can pin, because the real ones need a
build: a promotion's ``.text`` has to cover the *splits* it displaces (which run past the
DIE's ``high_pc`` to the next split's address), and that overhang may be filled from retail
only when retail leaves ``nop`` there.  ``.debug`` and ``.line`` are never padded at all --
a short chunk there is a missing DIE or an unwritten statement, and padding it would
fabricate agreement.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import compile as cc  # noqa: E402

#: Two four-byte bodies, then eight bytes of split padding: the shape of a unit whose last
#: split runs to the next symbol's address.
BODIES = [(0, 4), (4, 4)]
TRAILING = 8
EXTENT = 16
REGISTERS = b"\x11\x22\x33\x44" + b"\x55\x66\x77\x88"


def payload(bodies=REGISTERS):
    """What ``place`` hands the helper: the whole extent, bodies written into zeros."""
    return bodies.ljust(EXTENT, b"\x00")


def test_a_nop_tail_is_filled_from_retail_and_reported(capsys):
    bodies = payload()

    filled = cc._text_extent(bodies, bodies, BODIES, TRAILING, "src/example.c")

    assert filled == bodies
    message = capsys.readouterr().err
    assert "src/example.c: filled .text trailing nop padding from retail (0x8 bytes)" in message


def test_a_code_tail_is_refused_as_incomplete_c():
    extent = REGISTERS + b"\x99\x99\x99\x99" + b"\x00" * 4

    with pytest.raises(cc.Unusable) as excinfo:
        cc._text_extent(payload(), extent, BODIES, TRAILING, "src/example.c")

    assert str(excinfo.value) == (
        "src/example.c: .text is short by 0x8 bytes; C is incomplete "
        "(retail's bytes there are content, not nop padding)")


def test_a_non_nop_inter_function_gap_is_refused_too():
    """Inside the extent the padding is already zero; retail's gap has to be ``nop``."""
    extent = REGISTERS[:4] + b"\x99\x99\x99\x99" + REGISTERS[4:] + b"\x00" * 8

    with pytest.raises(cc.Unusable, match=r"\.text is short by 0x4 bytes"):
        cc._text_extent(payload(), extent, [(0, 4), (8, 4)], 12, "src/example.c")


def test_a_whole_extent_payload_is_returned_untouched(capsys):
    bodies = payload(REGISTERS * 2)

    assert cc._text_extent(bodies, bodies, [(0, 16)], EXTENT, "src/example.c") == bodies
    assert capsys.readouterr().err == ""


# -- the split extent itself --------------------------------------------------------------


class _Geometry:
    code_segment = "main"


class _Target:
    def geometry_required(self):
        return _Geometry()


class _Manifests:
    target = _Target()


class _Function:
    def __init__(self, address):
        self.address = address


class _Tu:
    file = "src/example.c"

    def __init__(self, functions, end):
        self.functions = [_Function(address) for address in functions]
        self.address = min(functions)
        self.end = end


def split(directory, name, address):
    """A splat split: its own first instruction's comment carries the address."""
    path = directory / f"{name}.s"
    path.write_text(f"glabel {name}\n"
                    f"    /* {address - 0x100000 + 0x200:X} {address:08X} 00000000 */  nop\n"
                    "endlabel\n")


def test_the_extent_runs_to_the_next_split_past_the_last_function(tmp_path):
    directory = tmp_path / "asm" / "nonmatchings" / "main"
    directory.mkdir(parents=True)
    for name, address in (("before", 0x100FC0), ("a", 0x100000), ("b", 0x100004),
                          ("after", 0x100010)):
        split(directory, name, address)

    start, end = cc._split_extent(_Tu([0x100000, 0x100004], 0x100008), _Manifests(),
                                  root=tmp_path)

    assert (start, end) == (0x100000, 0x100010)


def test_the_extent_is_the_last_function_when_nothing_follows(tmp_path):
    directory = tmp_path / "asm" / "nonmatchings" / "main"
    directory.mkdir(parents=True)
    split(directory, "a", 0x100000)

    assert cc._split_extent(_Tu([0x100000], 0x100008), _Manifests(), root=tmp_path) == \
        (0x100000, 0x100008)


def test_a_function_with_no_split_is_refused(tmp_path):
    directory = tmp_path / "asm" / "nonmatchings" / "main"
    directory.mkdir(parents=True)
    split(directory, "a", 0x100000)

    with pytest.raises(cc.Unusable, match="no code split at 0x00100008"):
        cc._split_extent(_Tu([0x100000, 0x100008], 0x100010), _Manifests(), root=tmp_path)


# -- .debug and .line are never padded ----------------------------------------------------


class _MW:
    relocs = {}

    @staticmethod
    def data(_index):
        return b"\xAA\xBB"

    @staticmethod
    def resolve(_tu, _symbol):
        return 0


class _SmallTu:
    file = "src/example.c"


@pytest.mark.parametrize("section", [".debug", ".line"])
def test_a_short_debug_or_line_chunk_is_refused(section):
    with pytest.raises(cc.Unusable) as excinfo:
        cc._fill(_MW(), _SmallTu(), 0, 4, [(0, 4, 0, "the unit's types")], 0, section,
                 unit_file="src/example.c")

    assert str(excinfo.value) == (
        f"src/example.c: the unit's types {section} is short by 0x2 bytes; "
        f"C is incomplete (cannot pad {section})")
