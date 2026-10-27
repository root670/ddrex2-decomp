"""The generated headers: one C header per translation unit, from the target's own DWARF.

Re-pointed at the registered target.  Rendering the whole tree is what `ddr oracle` does; what is
tested here is the emitter's contract on one unit of *this* binary -- a header is produced, a name
that matches nothing is refused, and the committed tree and a fresh render agree for that unit --
so nothing depends on how many units the binary happens to have.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
sys.path.insert(0, str(ROOT))

import emit_headers  # noqa: E402
from tests import target_support  # noqa: E402

TARGET = target_support.registered()
pytestmark = pytest.mark.skipif(
    not TARGET.elf.is_file() or not TARGET.cus.is_file(),
    reason=f"{TARGET.name}: its ELF and config are generated in Task 4")


def a_unit():
    """One translation unit of this binary, as its *repo path*, from the committed CU map."""
    import json
    cus = json.loads(TARGET.cus.read_text())
    return next(record["file"] for record in cus
               if record.get("kind") == "tu" and record.get("file"))


def a_unit_name():
    """The name the *retail build recorded* for that unit: what `render` is asked for.

    The recorded path is the build host's (`C:\\work2\\...\\src\\sys\\sys_scf.c`), and the emitter
    matches on its tail; the repo path (`src/sys/sys_scf.c`) is what identifies the unit in this
    tree and what its header's location mirrors -- the two are not interchangeable.
    """
    return a_unit().split("/")[-1]


def test_a_units_header_is_generated_from_its_own_evidence():
    unit = a_unit_name()
    text = emit_headers.render(TARGET.elf, unit)
    assert text.count("#ifndef") == 1 and "DDR_UNIT_" in text
    assert "#endif /* DDR_UNIT_" in text, "the header is guarded and closes its guard"
    assert unit in text, "the header names the unit it was generated from"
    assert unit in text, "the header names the unit it was generated from"


def test_an_unknown_unit_is_refused():
    with pytest.raises(emit_headers.NoSuchUnit):
        emit_headers.render(TARGET.elf, "no_such_unit_at_all.c")


def test_the_committed_header_matches_a_fresh_render():
    """The committed tree is the generator's output: the same unit renders the same bytes.

    The path is the generator's own rule -- a unit's header mirrors its repo path under
    `include/` -- so this proves the committed header, not a path this test imagined.
    """
    unit = a_unit()
    path = emit_headers.header_for(unit)                 # mirrors the repo path under include/
    committed = ROOT / "include" / path
    assert committed.is_file(), f"include/{path} is not committed"
    assert emit_headers.render(TARGET.elf, a_unit_name()) == committed.read_text()


def test_the_tail_rule_states_the_smallest_alignment_the_size_needs():
    """The aggregate's own size states an alignment its members do not -- the smallest one.

    Measured on `fp_style.c`: DIE 0x1254e3's members end at 0x1c, DWARF says 0x20, and retail
    strides the type by 0x20.  Eight already reproduces that size, so eight is what is stated:
    a smaller claim is the one DWARF supports, and a use that needs more says so on the member
    its offset demands.  Members that give the type 8-byte alignment themselves explain a 0x20
    size, so there is nothing to state -- the rule is about a size that implies *more* than the
    members do.  `_NETWORK_W` is the other end: 0x76dc of members and a 0x7700 size need 64.
    """
    assert emit_headers._tail_alignment(0x1C, 0x20, 4) == 8
    assert emit_headers._tail_alignment(0x74, 0x80, 4) == 16, "8 reaches 0x78, not 0x80"
    assert emit_headers._tail_alignment(0x66, 0x80, 4) == 32
    assert emit_headers._tail_alignment(0x76DC, 0x7700, 4) == 64, "_NETWORK_W"
    assert emit_headers._tail_alignment(0x45A, 0x480, 4) == 64, "_mio_message"
    assert emit_headers._tail_alignment(0x1C, 0x20, 8) is None, "the members explain it"
    assert emit_headers._tail_alignment(0x9C, 0xA0, 8) is None, "music_info: 8 explains 0xa0"
    assert emit_headers._tail_alignment(0x1C, 0x20, 16) is None
    assert emit_headers._tail_alignment(0x1C, 0x30, 4) is None, "the size is a wider tail"
    assert emit_headers._tail_alignment(0x20, 0x20, 4) is None, "there is no tail"
    assert emit_headers._tail_alignment(0x1C, 0x2C, 4) is None, "not a multiple of 16"
    assert emit_headers._tail_alignment(0x15, 0x16, 1) is None, "no alignment fits: a pad"
    assert emit_headers._tail_alignment(0x8A, 0x8C, 4) is None, "no power of two is invented"


def test_a_definition_states_the_tail_alignment_right_after_the_brace():
    """The spelling is the one 3.0b38 honours, and it is the aggregate's closing line.

    The other spelling -- the attribute after the typedef's name -- is silently ignored by the
    pinned compiler (`sizeof` stayed 0x1c), so a header that used it would look right and stride
    wrong.  This searches the binary's own DWARF for an aggregate that trips the rule rather
    than naming a unit or a member, and accepts any alignment the rule can state: 8 and 64 are
    both measured through this placement (`fp_style.c`'s `anon_5_73` and `_NETWORK_W`).
    """
    dw = emit_headers.dwarf(TARGET.elf)
    import re
    for die in dw.dies.values():
        if die.tag not in emit_headers.AGGREGATES:
            continue
        lines = emit_headers.definition(dw, die, "probe", lambda d: "ANON", typedef=True)
        match = re.fullmatch(r"\} __attribute__\(\(aligned\((8|16|32|64)\)\)\) probe;",
                             lines[-1])
        if match:
            return
    pytest.skip("this binary's DWARF has no aggregate whose size states a tail alignment")


def test_the_member_rule_searches_wider_alignments():
    """A member's offset states its alignment, and 16 is not the widest retail uses.

    Measured on the pinned image: `_mio_message`'s `body` sits at 0x40 after `head` ends at
    0x24 (32 reaches it, 16 stops at 0x30), `_ddrnet`'s `msg` at 0x3700 after `msys` ends at
    0x36D8 (only 64 reaches it).  16 is still tried first, because the tree already spells it
    and retail's DWARF cannot distinguish it from a narrower claim; a candidate is returned
    only when it reproduces the offset *and* divides the aggregate's recorded size.
    """
    assert emit_headers._stated_alignment(0x54, 0x60, 4, 0x90) == 16
    assert emit_headers._stated_alignment(0x24, 0x40, 1, 0x480) == 32, "_mio_message.body"
    assert emit_headers._stated_alignment(0x36D8, 0x3700, 4, 0x2B5C0) == 64, "_ddrnet.msg"
    assert emit_headers._stated_alignment(0x54, 0x60, 16, 0x90) is None, "the member's own"
    assert emit_headers._stated_alignment(0x54, 0x60, 4, 0x91) is None, "the size would move"
    assert emit_headers._stated_alignment(0x10, 0x30, 4, 0x40) is None, "nothing reaches 0x30"


def test_a_gap_alignment_explains_stays_a_comment():
    """The next member's own alignment is enough: no statement and no member.

    Measured shape: `_ddrnet`'s `use_pindex` ends at 0x8FD5 and `use_pid`, an `int`, starts
    at 0x8FD8; `_mio_message`'s 0x24..0x40 jump is not that kind of gap.
    """
    assert emit_headers._padded_by_alignment(0x8FD5, 0x8FD8, 4)
    assert not emit_headers._padded_by_alignment(0x24, 0x40, 4)
    assert emit_headers._padded_by_alignment(0x30, 0x30, 4), "no gap, nothing to place"


def test_a_gap_no_alignment_explains_is_spelled_as_a_member():
    """The fallback: bytes the DIE's offsets or `byte_size` demand but nothing explains.

    Nothing in this image needs it (the sweep below finds no such aggregate), so the spelling
    is pinned here -- exactly the missing length, a name no retail member can have, and an
    element type that cannot round the following member up.
    """
    line = emit_headers._omitted_member("    ", 0x76DC, 0x7700)
    assert "unsigned char pad_76dc[0x24];" in line, line
    assert "0x24 bytes no alignment or member explains" in line, line
    assert emit_headers._omitted_member("", 0x15, 0x16).startswith("/* 0x015 */")


def test_no_aggregate_in_this_image_leaves_a_gap_unexplained():
    """Every gap in the binary's own named aggregates is padding or a stated alignment.

    Measured: the member rule states 16, 32 and 64 here (64 on the 0x40-multiple aggregates
    -- `_NETWORK_W`, `_mio_message`, `_ddrnet`, `_tag_cNetCnf`), and not one gap is written
    as an omission any more.
    """
    import re
    dw = emit_headers.dwarf(TARGET.elf)
    alignments, gaps = set(), 0
    for name, dies in emit_headers.named_types(dw).items():
        for line in emit_headers.definition(dw, dies[0], name, lambda d: "ANON"):
            if "// 0x" not in line:
                continue
            assert "not in DWARF" not in line, line
            assert "no alignment or member explains" not in line, line
            alignments.update(int(value) for value in re.findall(r"aligned\((\d+)\)", line))
            gaps += "bytes padding" in line
    assert {16, 32, 64} <= alignments, sorted(alignments)
    assert gaps, "the image has padding gaps, and they are comments only"


def test_no_generated_header_states_alignment_after_the_typedef_name():
    """The ignored spelling appears in no header: after the brace, before the name, or not at all."""
    import re
    for path in sorted((ROOT / "include").rglob("*.h")):
        assert not re.search(r"}\s+\w+\s+__attribute__", path.read_text()), path
