"""A promoted source carries no ``#line``: the promotion path refuses one, naming the remedy.

``compile.place`` is both the ninja ``cc`` rule's program and the promotion path every tool
goes through, so the refusal lives there rather than in a lint beside it: a directive-laden
source cannot reach an object, whoever the caller is (``ninja``, ``select_build.py``,
``--compare`` or ``configure.py``'s own recompiles).  Removing the directive is a promotion
step -- ``python3 tools/toolchain/line_reflow.py <file> --normalise`` -- and the build used to
do that silently to a staged copy, so a committed file could differ from the compiled one.
The message has to carry both facts a caller needs: how many directives are there, and the
one command that removes them.

No compiler is needed: the refusal comes before the manifests and the toolchain are touched,
which is also why these tests pass ``None`` for every argument after the unit.
"""

import pathlib
import sys
from types import SimpleNamespace

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import compile as cc  # noqa: E402
from toolchain import line_reflow as lr  # noqa: E402

REMEDY = "python3 tools/toolchain/line_reflow.py"


def test_the_promotion_path_refuses_a_source_with_directives(tmp_path):
    """Two directives: refused, with the count, the file and the command that strips them."""
    source = tmp_path / "unit.c"
    source.write_text("int f(void) {\n#line 20\n    return 0;\n#line 30\n}\n")
    unit = SimpleNamespace(file="src/x/unit.c", source=source)

    with pytest.raises(cc.Unusable) as excinfo:
        cc.place(unit, None, None, None, None)

    message = str(excinfo.value)
    assert "src/x/unit.c" in message
    assert "2 #line directive(s)" in message
    assert f"{REMEDY} src/x/unit.c --normalise" in message


def test_an_overridden_spelling_is_checked_too(tmp_path):
    """``source_text`` is the bytes about to be compiled, so it is what the gate reads.

    ``line_reflow.py`` and the before/after checks pass an in-memory spelling; a caller that
    hands the build a directive-bearing one is refused exactly as the file would be.
    """
    source = tmp_path / "unit.c"
    source.write_text("int f(void) { return 0; }\n")
    unit = SimpleNamespace(file="src/x/unit.c", source=source)

    with pytest.raises(cc.Unusable, match=r"1 #line directive") as excinfo:
        cc.place(unit, None, None, None, None,
                 source_text=b"int f(void) {\n#line 20\n    return 0;\n}\n")

    assert "src/x/unit.c" in str(excinfo.value)


def test_a_source_without_directives_passes_the_gate(tmp_path):
    """The same unit, directive-free, is not refused: the rule is about the directive only."""
    source = tmp_path / "unit.c"
    source.write_text("int f(void) {\n    return 0;\n}\n")
    unit = SimpleNamespace(file="src/x/unit.c", source=source)

    assert cc.refuse_line_directives(unit.file, source.read_text()) is None
    # And the conservative counter agrees with the gate line_reflow itself uses.
    assert lr.directive_count(source.read_text()) == 0
    assert not lr.has_directives(source.read_text())


def test_the_remedy_is_the_spelling_the_tool_documents(tmp_path):
    """The message's command is the tool's own invocation, not a paraphrase of it."""
    source = tmp_path / "unit.c"
    source.write_text("#line 1\nint f(void) { return 0; }\n")

    with pytest.raises(cc.Unusable) as excinfo:
        cc.refuse_line_directives("src/x/unit.c", source.read_text())

    assert excinfo.value.args[0].startswith("src/x/unit.c: 1 #line directive(s)")
    assert str(excinfo.value).endswith(f"{REMEDY} src/x/unit.c --normalise")
