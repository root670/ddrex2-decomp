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
