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


def test_the_tail_rule_states_an_alignment_the_members_do_not():
    """The aggregate's own size states a 16-byte alignment its members do not.

    Measured on `fp_style.c`: DIE 0x1254e3's members end at 0x1c, DWARF says 0x20, and retail
    strides the type by 0x20.  Members that give the type 8-byte alignment already explain a
    0x20 size, so there is nothing to state -- the rule is about a size that implies *more*
    than the members do.
    """
    assert emit_headers._tail_alignment(0x1C, 0x20, 4) == 16
    assert emit_headers._tail_alignment(0x1C, 0x20, 8) is None
    assert emit_headers._tail_alignment(0x1C, 0x20, 16) is None
    assert emit_headers._tail_alignment(0x1C, 0x30, 4) is None, "the size is a wider tail"
    assert emit_headers._tail_alignment(0x20, 0x20, 4) is None, "there is no tail"
    assert emit_headers._tail_alignment(0x1C, 0x2C, 4) is None, "not a multiple of 16"


def test_a_definition_states_the_tail_alignment_right_after_the_brace():
    """The spelling is the one 3.0b38 honours, and it is the aggregate's closing line.

    The other spelling -- the attribute after the typedef's name -- is silently ignored by the
    pinned compiler (`sizeof` stayed 0x1c), so a header that used it would look right and stride
    wrong.  This searches the binary's own DWARF for an aggregate that trips the rule rather
    than naming a unit or a member.
    """
    dw = emit_headers.dwarf(TARGET.elf)
    for die in dw.dies.values():
        if die.tag not in emit_headers.AGGREGATES:
            continue
        lines = emit_headers.definition(dw, die, "probe", lambda d: "ANON", typedef=True)
        if "__attribute__((aligned(16)))" in lines[-1]:
            assert lines[-1] == "} __attribute__((aligned(16))) probe;"
            return
    pytest.skip("this binary's DWARF has no aggregate whose size states a 16-byte tail")


def test_no_generated_header_states_alignment_after_the_typedef_name():
    """The ignored spelling appears in no header: after the brace, before the name, or not at all."""
    import re
    for path in sorted((ROOT / "include").rglob("*.h")):
        assert not re.search(r"}\s+\w+\s+__attribute__", path.read_text()), path
