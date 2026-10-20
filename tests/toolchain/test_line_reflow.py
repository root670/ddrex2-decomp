"""The ``#line`` reflow: physical layout, refusals, and the compile it must preserve.

The step's contract has three halves.  The rewrite is *byte-preserving*: every line that is
not a directive comes out unchanged and the line a directive numbered lands on that number
physically.  It *refuses* what it cannot express -- a target already behind the rewritten
file, and a file name that is not the unit's own -- and refuses without producing a byte.
And because those two properties are a claim about the compiler, the last test compiles a
promoted unit before and after the rewrite through the promotion path and requires
``.text``, ``.debug`` and ``.line`` to be identical.

The pure tests need no compiler; the compile test skips (with a reason) when the retail
ELF or the recorded compiler is not present in this checkout.
"""

import pathlib
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from toolchain import line_reflow as lr  # noqa: E402

TOOL = ROOT / "tools/toolchain/line_reflow.py"


def run(*args):
    return subprocess.run([sys.executable, str(TOOL), *args],
                          capture_output=True, text=True)


# ---------------------------------------------------------------------------
# the rewrite
# ---------------------------------------------------------------------------


def test_a_forward_directive_round_trips_onto_physical_lines():
    """Every other byte is copied, and the statement after ``#line 20`` sits on line 20."""
    source = ("/* header */\n"
              "int f(void) {\n"
              "    int a = 1;\n"
              "#line 20\n"
              "    return a;\n"
              "}\n")

    rewritten, directives = lr.rewrite(source)

    assert directives == (lr.Directive(physical=4, target=20, filename=None),)
    assert "#line" not in rewritten
    lines = rewritten.split("\n")
    assert lines[19] == "    return a;"           # 1-based line 20
    kept = [line for line in rewritten.split("\n")
            if line in ("/* header */", "int f(void) {", "    int a = 1;",
                        "    return a;", "}")]
    assert kept == ["/* header */", "int f(void) {", "    int a = 1;",
                    "    return a;", "}"]
    # Nothing else moved: the rewrite has no directives left, so it is its own fixpoint.
    assert lr.rewrite(rewritten) == (rewritten, ())


def test_a_directive_inside_a_comment_is_not_a_directive():
    source = "/*\n#line 3\n*/\nint a;\n"
    assert lr.rewrite(source) == (source, ())


def test_a_backward_directive_is_refused_and_names_its_line(tmp_path):
    source = tmp_path / "back.c"
    source.write_text("".join(f"int v{line};\n" for line in range(1, 10))
                      + "#line 5\nint last;\n")
    original = source.read_bytes()

    result = run(str(source))

    assert result.returncode == 1
    assert "line 10" in result.stderr
    assert "#line 5 moves backwards" in result.stderr
    assert source.read_bytes() == original, "a refusal writes nothing"

    with pytest.raises(lr.Refused) as excinfo:
        lr.rewrite(original.decode("latin-1"))
    assert excinfo.value.line == 10


def test_a_filename_that_is_not_the_units_own_is_refused():
    source = "#line 9 \"other.c\"\nint a;\n"

    with pytest.raises(lr.Refused) as excinfo:
        lr.rewrite(source, accept_paths=("src/sys/sys_scf.c",))

    assert excinfo.value.line == 1
    assert "not this unit" in str(excinfo.value)
    # The unit's own spelling -- DWARF name or repo path -- is accepted.
    accepted, directives = lr.rewrite(
        source.replace("other.c", "src/sys/sys_scf.c"),
        accept_paths=(r"C:\work2\usaex2\src\sys\sys_scf.c", "src/sys/sys_scf.c"))
    assert directives[0].filename == "src/sys/sys_scf.c"
    assert "#line" not in accepted


def test_the_cli_refuses_a_foreign_filename_and_leaves_the_file(tmp_path):
    source = tmp_path / "foreign.c"
    source.write_text("#line 4 \"somewhere/else.c\"\nint a;\n")
    original = source.read_bytes()

    result = run("--unit-path", "src/sys/sys_scf.c", str(source))

    assert result.returncode == 1
    assert "line 1" in result.stderr and "not this unit" in result.stderr
    assert source.read_bytes() == original


# ---------------------------------------------------------------------------
# the compile the rewrite must preserve
# ---------------------------------------------------------------------------


def _unit_and_compiler():
    """The promoted unit, its manifests, and the toolchain, or a skip reason."""
    from config import targets
    from toolchain import compile as cc, fetch

    if not (ROOT / "orig" / "SLUS_211.74").is_file():
        pytest.skip("no retail ELF in this checkout: nothing to place the unit against")
    target = targets.get(targets.DEFAULT)
    manifests = cc.Manifests(target)
    tu = manifests.tu_named("src/sys/sys_scf.c")
    pair = target.build_pair(tu.file)
    assert pair is not None, "sys_scf.c must stay a recorded promotion"
    compiler, flags, state = pair
    # The row's fourth element is `False`, `True` (normalise) or `"adopt"`; the two
    # stronger steps are separate arguments to the promotion path.
    normalise, adopt = state is True, state == "adopt"
    try:
        compiler_dir = fetch.compiler(compiler)
        wibo = fetch.wibo()
    except Exception as exc:                     # a checkout without the pinned toolchain
        pytest.skip(f"recorded compiler unavailable: {exc}")
    import shlex
    return tu, manifests, compiler_dir, wibo, shlex.split(flags), normalise, adopt


def test_a_recompiled_unit_is_byte_identical_after_the_rewrite(tmp_path):
    """The acceptance step itself: compile before and after through ``place``'s path."""
    from toolchain import compile as cc

    tu, manifests, compiler_dir, wibo, flags, normalise, adopt = _unit_and_compiler()
    original = tu.source.read_bytes()
    text = original.decode("latin-1")
    lines = text.split("\n")
    # A blank line becomes a no-op directive ("the next line keeps its number"), so the
    # only difference between the two spellings is the directive itself -- until the
    # rewrite takes it away again.
    blank = next(number for number, line in enumerate(lines, 1)
                 if line == "" and number < len(lines) and lines[number] != "")
    variant = "\n".join(lines[:blank - 1] + [f"#line {blank + 1}"] + lines[blank:])

    rewritten, directives = lr.rewrite(variant, accept_paths=(tu.name, tu.file))

    assert [directive.physical for directive in directives] == [blank]
    assert rewritten == text, "the directive occupied a blank line; the rewrite restores it"
    assert lr.has_directives(variant) and not lr.has_directives(rewritten)

    before = cc._place_source(tu, manifests, compiler_dir, wibo, flags,
                              variant.encode("latin-1"), tmp_path / "before.mw.o", normalise,
                              adopt)
    after = cc._place_source(tu, manifests, compiler_dir, wibo, flags,
                             rewritten.encode("latin-1"), tmp_path / "after.mw.o", normalise,
                             adopt)

    assert before.text == after.text, "the rewrite moved .text"
    assert before.debug == after.debug, "the rewrite moved .debug"
    assert before.line == after.line, "the rewrite moved .line"

    # And the promotion path itself runs the same comparison and accepts this spelling.
    placed = cc.place(tu, manifests, compiler_dir, wibo, flags, keep=tmp_path / "placed.mw.o",
                      normalise=normalise, adopt=adopt,
                      source_text=variant.encode("latin-1"))
    assert (placed.text, placed.debug, placed.line) == (before.text, before.debug,
                                                        before.line)


def test_a_backward_unit_is_compiled_unrewritten_rather_than_refused(tmp_path, capsys):
    """A layout the rewrite cannot express is skipped, not made a promotion failure."""
    from toolchain import compile as cc

    tu, manifests, compiler_dir, wibo, flags, normalise, adopt = _unit_and_compiler()
    original = tu.source.read_bytes()
    text = original.decode("latin-1")
    # A directive after the last statement cannot move a record, but it does move the
    # rewritten file's numbering backwards -- `#line 1` where dozens of lines are already
    # out -- so the rewrite refuses it and the build compiles it as written.
    variant = text + "#line 1\n"
    with pytest.raises(lr.Refused):
        lr.rewrite(variant, accept_paths=(tu.name, tu.file))

    placed = cc.place(tu, manifests, compiler_dir, wibo, flags, keep=tmp_path / "skipped.mw.o",
                      normalise=normalise, adopt=adopt,
                      source_text=variant.encode("latin-1"))

    assert "reflow skipped" in capsys.readouterr().err
    plain = cc._place_source(tu, manifests, compiler_dir, wibo, flags,
                             variant.encode("latin-1"), tmp_path / "plain.mw.o", normalise,
                             adopt)
    assert placed.text == plain.text
