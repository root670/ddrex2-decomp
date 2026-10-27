"""``tools/units/m2c_draft.py``: the split slice, the context flattening, the write guard.

The pure tests use synthetic splits and headers, so the shape rules are checked without the
retail image, a compiler or the m2c install.  The one measured test drafts a promoted
function and asserts its control flow against the C this tree already carries; it skips
when m2c has not been fetched or ``asm/`` has not been generated.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))

from toolchain import fetch  # noqa: E402
from units import m2c_draft  # noqa: E402

SPLIT = """\
.include "macro.inc"
.set noat
.set noreorder
.align 3
nonmatching demo, 0x20

glabel demo
    /* 0000 00100000 0800E003 */  jr         $31
    /* 0004 00100004 00000000 */  nop
endlabel demo
"""


def write(path: pathlib.Path, text: str) -> pathlib.Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)
    return path


def write_image(path: pathlib.Path, data: bytes) -> pathlib.Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return path


def test_extract_function_keeps_the_preamble_and_drops_the_neighbour(tmp_path):
    split = write(tmp_path / "demo.s", SPLIT + "\nglabel other\n    nop\nendlabel other\n")
    text = m2c_draft.extract_function(split.read_text(), "demo", split)
    assert ".set noat" in text and ".include" in text
    assert ".align 3" in text
    assert "glabel demo" in text and "endlabel demo" in text
    assert "other" not in text
    assert "nonmatching" not in text


def test_extract_function_refuses_a_data_split(tmp_path):
    split = write(
        tmp_path / "d.s",
        '.include "macro.inc"\nnonmatching d\n\ndlabel d\n    /* 0 */ .word 0x24020018\n',
    )
    with pytest.raises(m2c_draft.DraftError, match="dlabel"):
        m2c_draft.extract_function(split.read_text(), "d", split)


def test_extract_function_names_the_labels_it_found(tmp_path):
    split = write(tmp_path / "s.s", SPLIT)
    with pytest.raises(m2c_draft.DraftError, match="split defines demo"):
        m2c_draft.extract_function(split.read_text(), "missing", split)


def test_flatten_context_resolves_includes_once_and_drops_directives(tmp_path):
    write(
        tmp_path / "include/types/anon_1.h",
        "#ifndef GUARD\n#define GUARD\ntypedef struct { int a; } anon_1;\n#endif\n",
    )
    write(
        tmp_path / "include/types/t.h",
        '#ifndef T\n#define T\n#include "types/anon_1.h"\nstruct t { anon_1 a; };\n#endif\n',
    )
    header = write(
        tmp_path / "include/src/a/b.h",
        '#ifndef U\n#define U\n#include "types/t.h"\n#include "types/anon_1.h"\n'
        "void f(anon_1 *v);\n#endif\n",
    )
    text = m2c_draft.flatten_context(header, (tmp_path / "include",))
    assert text.count("} anon_1;") == 1  # visited once, despite the second include
    assert "struct t { anon_1 a; };" in text
    assert "void f(anon_1 *v);" in text
    assert "#" not in text


def test_output_path_refuses_the_hand_written_tree():
    with pytest.raises(m2c_draft.DraftError, match="build reads"):
        m2c_draft.output_path("src/AM/s573/doll/matrix.c", "f")
    with pytest.raises(m2c_draft.DraftError, match="outside drafts/"):
        m2c_draft.output_path("/tmp/f.c", "f")
    assert m2c_draft.output_path("drafts/f.c", "f") == ROOT / "drafts/f.c"
    assert m2c_draft.output_path("drafts", "f") == ROOT / "drafts/f.c"
    assert m2c_draft.output_path(None, "f") is None


def test_missing_m2c_names_the_remedy(tmp_path):
    with pytest.raises(fetch.MissingTool) as caught:
        fetch.installed_m2c(tmp_path)
    assert fetch.M2C_REMEDY in str(caught.value)


INSTALLED = ROOT / "toolchain" / "m2c" / fetch.M2C_COMMIT
SPLITS = ROOT / "asm" / "nonmatchings"

JUMP = """\
.include "macro.inc"
.set noat
.set noreorder
.align 3
nonmatching demo, 0x40

glabel demo
    /* 0000 00100000 0300412C */  sltiu      $1, $2, 0x2
    /* 0004 00100004 07002010 */  beqz       $1, .L00100038
    /* 0008 00100008 2D800000 */   daddu     $16, $0, $0
    /* 000C 0010000C 2D00033C */  lui        $3, %hi(jtbl_002A0000)
    /* 0010 00100010 80100200 */  sll        $2, $2, 2
    /* 0014 00100014 00006324 */  addiu      $3, $3, %lo(jtbl_002A0000)
    /* 0018 00100018 21104300 */  addu       $2, $2, $3
    /* 001C 0010001C 0000428C */  lw         $2, 0x0($2)
    /* 0020 00100020 08004000 */  jr         $2
    /* 0024 00100024 00000000 */   nop
    /* 0028 00100028 0800E003 */  jr         $31
    /* 002C 0010002C 00000000 */   nop
.align 2
  .L00100030:
    /* 0030 00100030 0800E003 */  jr         $31
    /* 0034 00100034 00000000 */   nop
.align 2
  .L00100038:
    /* 0038 00100038 0800E003 */  jr         $31
    /* 003C 0010003C 00000000 */   nop
endlabel demo
"""


class _StubGeometry:
    """Just the two fields ``retail_words`` reads, over a file that *is* the loadable image."""

    def __init__(self, size: int, vram: int):
        self.loadable_rom = 0
        self.loadable_end = size
        self.loadable_vram = vram

    def offset_of(self, address: int) -> int:
        return address - self.loadable_vram


class _StubTarget:
    """A target whose retail image is a temp file, so the table read needs no retail binary."""

    def __init__(self, elf: pathlib.Path, size: int, vram: int):
        self.elf = elf
        self._geometry = _StubGeometry(size, vram)

    def geometry_required(self):
        return self._geometry


def test_jump_tables_names_the_table_the_dispatch_reads():
    tables = m2c_draft.jump_tables(JUMP)
    assert tables == (m2c_draft.JumpTable("jtbl_002A0000", 0x002A0000, 2),)
    # A return is not a dispatch, and a dispatch whose `%lo` names no table is not one either.
    assert m2c_draft.jump_tables(SPLIT) == ()
    without = JUMP.replace("%l(jtbl_002A0000)", "%l(D_002A0000)").replace(
        "%lo(jtbl_002A0000)", "%lo(D_002A0000)"
    )
    assert m2c_draft.jump_tables(without) == ()


def test_prepare_assembly_leaves_a_table_free_body_alone():
    asm, plans, notes = m2c_draft.prepare_assembly(SPLIT, None, "demo")
    # The same string, not merely an equal one: a body with no table is handed to m2c untouched.
    assert asm is SPLIT
    assert plans == () and notes == ()


def stub_target(tmp_path, words) -> _StubTarget:
    """A retail image whose words sit at ``0x002A0000`` (the address this split's name says)."""
    image = bytearray(0x1A0008)
    image[0x1A0000:0x1A0008] = b"".join(word.to_bytes(4, "little") for word in words)
    return _StubTarget(write_image(tmp_path / "retail.elf", bytes(image)), len(image), 0x100000)


def test_prepare_assembly_adds_the_case_label_the_split_lacks(tmp_path):
    # 0x00100028 is a case the split never labels; 0x00100030 already carries `.L00100030`.
    target = stub_target(tmp_path, (0x00100028, 0x00100030))
    asm, plans, notes = m2c_draft.prepare_assembly(JUMP, target, "demo")
    assert [plan.symbol for plan in plans] == ["jtbl_002A0000"]
    assert plans[0].entries == (0x00100028, 0x00100030)
    assert plans[0].labels == (".L00100028", ".L00100030")
    assert plans[0].dropped == ()
    # The missing label is inserted before the instruction it names, and only once.
    assert asm != JUMP
    lines = asm.splitlines()
    assert lines[lines.index(".L00100028:") + 1].lstrip().startswith("/* 0028 00100028")
    assert sum(1 for line in lines if line.strip() == ".L00100030:") == 1
    # The extra file m2c parses is one data label per table, one word per case.
    assert m2c_draft.table_assembly(plans) == (
        ".section .rodata\n.align 2\njtbl_002A0000:\n    .word .L00100028, .L00100030\n"
    )
    assert notes == ()


def test_prepare_assembly_stops_at_the_first_case_outside_the_split(tmp_path):
    # The first word is a case in this split; the second is somewhere else entirely.
    target = stub_target(tmp_path, (0x00100028, 0x00400000))
    asm, plans, notes = m2c_draft.prepare_assembly(JUMP, target, "demo")
    assert plans[0].entries == (0x00100028,)
    assert plans[0].dropped == (0x00400000,)
    assert any("stops before that case" in note for note in notes)


def test_prepare_assembly_notes_a_table_whose_cases_are_in_another_split(tmp_path):
    # `func_001A8770`'s shape: every entry points past the function, so no switch exists here.
    target = stub_target(tmp_path, (0x00400000, 0x00400004))
    asm, plans, notes = m2c_draft.prepare_assembly(JUMP, target, "demo")
    assert asm is JUMP and plans == ()
    assert len(notes) == 1
    assert "0x002A0000" in notes[0] and "0x00400000" in notes[0]
    assert "written by hand" in notes[0]


@pytest.mark.skipif(
    not (INSTALLED / "m2c.py").is_file() or not SPLITS.is_dir(),
    reason="m2c is not fetched (python3 tools/toolchain/fetch.py m2c) or asm/ is not generated",
)
def test_draft_of_a_jump_table_body_recovers_the_switch(capsys):
    status = m2c_draft.main(["CS/advanced/adv_main.c", "extras_main"])
    assert status == 0
    capture = capsys.readouterr()
    draft = capture.out
    # `extras_main` dispatches through jtbl_002D7110, whose 13 words are case addresses; the
    # split carries the `jr $2` but neither the table nor a label for the case blocks.
    assert "switch (" in draft
    assert "case 0:" in draft and "case 12:" in draft and "default:" in draft
    assert "jump table is not provided" not in draft
    assert "jtbl_002D7110 at 0x002D7110 has 13 case(s)" in capture.err


@pytest.mark.skipif(
    not (INSTALLED / "m2c.py").is_file() or not SPLITS.is_dir(),
    reason="m2c is not fetched (python3 tools/toolchain/fetch.py m2c) or asm/ is not generated",
)
def test_a_table_free_body_is_drafted_exactly_as_before(capsys):
    from config import targets

    target = targets.get()
    split = SPLITS / "main" / "PsGsGetLs.s"
    if not split.is_file():
        pytest.skip("asm/nonmatchings/main/PsGsGetLs.s is not generated")
    body = m2c_draft.extract_function(split.read_text(), "PsGsGetLs", split)
    asm, plans, notes = m2c_draft.prepare_assembly(body, target, "PsGsGetLs")
    assert asm is body and plans == () and notes == ()
    status = m2c_draft.main(["AM/s573/doll/model2.c", "PsGsGetLs"])
    assert status == 0
    capture = capsys.readouterr()
    assert "PsGsGetLs" in capture.out
    assert "jtbl" not in capture.err



@pytest.mark.skipif(
    not (INSTALLED / "m2c.py").is_file() or not SPLITS.is_dir(),
    reason="m2c is not fetched (python3 tools/toolchain/fetch.py m2c) or asm/ is not generated",
)
def test_draft_of_a_promoted_function_has_retails_control_flow(capsys):
    status = m2c_draft.main(["AM/s573/doll/ps1lib.c", "GsInitCoordinate2"])
    assert status == 0
    draft = capsys.readouterr().out
    # The promoted C nests two loops over `m->m[i][j]`; the compiler flattened them into one
    # do-while over the three vectors, which is the control flow the draft has to show.
    assert "GsInitCoordinate2(struct _GsCOORDINATE2 *super, struct _GsCOORDINATE2 *base)" in draft
    assert "do {" in draft and "} while (" in draft
    assert "m[0][0] = 0" in draft
    # ... and the tail is the promoted source's assignment sequence, not invented code.
    assert "base->flg = 0;" in draft
    assert "base->super = super;" in draft
