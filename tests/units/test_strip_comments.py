"""The comment strip: lexical correctness, line preservation, keeps, and the compile gate.

The contract has four parts.  The strip is *lexical*: ``//`` and ``/* */`` are recognised
with strings, character literals and escapes respected.  It is *line-preserving*: every
removed character becomes a space, every newline survives, so a comment-only line becomes
a blank line and no statement changes its number.  It *refuses* malformed input and a
backslash continuation rather than guessing.  And because "the token stream is unchanged"
is still a claim about the compiler, the last test compiles a promoted unit before and
after the strip through the promotion path and requires ``.text``, ``.debug`` and ``.line``
to be identical.

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

from units import strip_comments as sc  # noqa: E402

TOOL = ROOT / "tools/units/strip_comments.py"


def run(*args):
    return subprocess.run([sys.executable, str(TOOL), *args],
                          capture_output=True, text=True)


# ---------------------------------------------------------------------------
# the lexical strip
# ---------------------------------------------------------------------------


def test_a_line_comment_is_blanked_and_the_line_survives():
    source = "int a; // note\nint b;\n"

    stripped = sc.strip(source)

    assert stripped == "int a;        \nint b;\n"
    assert stripped.count("\n") == source.count("\n")
    assert sc.scan(stripped) == ()


def test_a_block_comment_keeps_its_newlines():
    source = ("/* head */\n"
              "int f(void) {\n"
              "    /* a note\n"
              "       over two lines */\n"
              "    return 1;\n"
              "}\n")

    stripped = sc.strip(source)

    expected = ("/* head */\n"
                "int f(void) {\n"
                "             \n"
                "                        \n"
                "    return 1;\n"
                "}\n")
    assert stripped == expected
    assert stripped.count("\n") == source.count("\n")
    assert stripped.splitlines()[1:] == expected.splitlines()[1:]


def test_a_comment_only_line_becomes_a_blank_line_not_a_deleted_line():
    source = "int a;\n    /* only a comment */\nint b;\n"

    stripped = sc.strip(source)

    lines = stripped.split("\n")
    assert len(lines) == len(source.split("\n"))
    assert lines[1].strip() == ""
    assert stripped == "int a;\n" + " " * 24 + "\nint b;\n"


def test_strings_and_character_literals_are_not_comments():
    source = ('char *s = "a // b /* c */";\n'
              'char q = \'/\';\n'
              'char r = \'\\\'\';\n'
              'char *t = "escaped \\" // still string"; /* gone */\n')

    stripped = sc.strip(source)

    assert 'char *s = "a // b /* c */";' in stripped
    assert "char q = '/';" in stripped
    assert "char r = '\\'';" in stripped
    assert 'char *t = "escaped \\" // still string";' in stripped
    assert "/* gone */" not in stripped
    assert stripped.count("\n") == source.count("\n")


def test_a_divisor_is_not_a_comment():
    source = "int a = 7 / 2;\nint b = 8 / 2; // half\n"
    assert sc.strip(source) == "int a = 7 / 2;\nint b = 8 / 2;        \n"


# ---------------------------------------------------------------------------
# what is kept
# ---------------------------------------------------------------------------


def test_the_leading_block_header_is_kept_whole():
    source = "/* src/x.c -- what this is.\n *\n * More provenance. */\nint a; /* gone */\n"

    stripped = sc.strip(source)

    assert stripped.startswith("/* src/x.c -- what this is.\n *\n * More provenance. */\n")
    assert "/* gone */" not in stripped
    assert stripped.count("\n") == source.count("\n")


def test_a_leading_line_header_run_is_kept():
    source = ("// header one\n"
              "// header two\n"
              "\n"
              "int a; // gone\n")

    stripped = sc.strip(source)

    assert stripped == "// header one\n// header two\n\nint a;        \n"


def test_a_marked_block_comment_is_kept_and_an_unmarked_one_is_not():
    source = "/*! keep this: magic constant 1 */\nint a = 1; /* drop this */\n"

    stripped = sc.strip(source)

    assert "/*! keep this: magic constant 1 */" in stripped
    assert "drop this" not in stripped


def test_a_marked_line_comment_is_kept():
    source = "int a = 1; //! delay slot packing\nint b; // note\n"

    stripped = sc.strip(source)

    assert "//! delay slot packing" in stripped
    assert "// note" not in stripped


def test_the_header_is_kept_but_a_marker_is_needed_below_it():
    source = ("/* header */\n"
              "/* second note */\n"
              "/*! third note */\n")

    stripped = sc.strip(source)

    assert "/* header */" in stripped
    assert "second note" not in stripped
    assert "/*! third note */" in stripped


# ---------------------------------------------------------------------------
# refusals
# ---------------------------------------------------------------------------


def test_an_unterminated_block_comment_is_refused():
    with pytest.raises(sc.Refused) as excinfo:
        sc.strip("int a;\n/* never closed\n")

    assert excinfo.value.line == 2
    assert "unterminated" in str(excinfo.value)


def test_a_stray_closer_is_refused():
    with pytest.raises(sc.Refused) as excinfo:
        sc.strip("int a;\n*/\n")

    assert excinfo.value.line == 2
    assert "outside a comment" in str(excinfo.value)


def test_an_unterminated_string_is_refused():
    with pytest.raises(sc.Refused) as excinfo:
        sc.strip('char *s = "open;\n')

    assert excinfo.value.line == 1
    assert "unterminated string" in str(excinfo.value)


def test_a_trailing_backslash_continuation_is_refused():
    with pytest.raises(sc.Refused) as excinfo:
        sc.strip("int a; \\\n// swallowed\nint b;\n")

    assert excinfo.value.line == 1
    assert "backslash" in str(excinfo.value)


def test_a_backslash_at_end_of_file_is_not_a_continuation():
    assert sc.strip("int a; \\") == "int a; \\"


# ---------------------------------------------------------------------------
# the object gate
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("part", ["text", "debug", "line"])
def test_a_changed_object_part_is_refused(part):
    from types import SimpleNamespace

    before = SimpleNamespace(text=b"\x01\x02", debug=b"a", line=b"b")
    after = SimpleNamespace(**{**vars(before), part: bytes([getattr(before, part)[0] ^ 1])})

    with pytest.raises(sc.Refused) as excinfo:
        sc.compare(before, after)

    assert f"same {part}" in str(excinfo.value)
    assert "refusing to write it" in str(excinfo.value)


def test_the_cli_refuses_a_non_unit_without_an_explicit_layout_edit(tmp_path):
    source = tmp_path / "plain.c"
    body = "int a; /* note */\n"
    source.write_text(body)

    result = run(str(source))

    assert result.returncode == 2
    assert "nothing can be compiled" in result.stderr
    assert source.read_text() == body, "a refusal writes nothing"


def test_the_cli_layout_only_edit_with_no_verify(tmp_path):
    source = tmp_path / "plain.c"
    source.write_text("int a; /* note */\n")

    result = run("--no-verify", str(source))

    assert result.returncode == 0, result.stderr
    assert source.read_text() == "int a;           \n"
    assert "nothing was compiled" in result.stdout


def test_the_cli_check_writes_nothing(tmp_path):
    source = tmp_path / "plain.c"
    body = "int a; /* note */\n"
    source.write_text(body)

    result = run("--no-verify", "--check", str(source))

    assert result.returncode == 0, result.stderr
    assert source.read_text() == body


# ---------------------------------------------------------------------------
# the compile the strip must preserve
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
    try:
        compiler_dir = fetch.compiler(compiler)
        wibo = fetch.wibo()
    except Exception as exc:                     # a checkout without the pinned toolchain
        pytest.skip(f"recorded compiler unavailable: {exc}")
    import shlex
    return tu, manifests, compiler_dir, wibo, shlex.split(flags), state is True, state == "adopt"


def test_a_stripped_unit_compiles_byte_identically(tmp_path):
    """The acceptance step itself: compile before and after through ``verify``."""
    from config import targets
    from toolchain import compile as cc

    tu, manifests, compiler_dir, wibo, flags, normalise, adopt = _unit_and_compiler()
    original = tu.source.read_bytes()
    stripped = sc.strip(original.decode("latin-1")).encode("latin-1")
    target = targets.get(targets.DEFAULT)

    before = cc._place_source(tu, manifests, compiler_dir, wibo, flags, original,
                              tmp_path / "before.mw.o", normalise, adopt)
    after = cc._place_source(tu, manifests, compiler_dir, wibo, flags, stripped,
                             tmp_path / "after.mw.o", normalise, adopt)

    assert (before.text, before.debug, before.line) == (after.text, after.debug, after.line)

    checked = sc.verify(tu, original, stripped, target)
    assert (checked[0].text, checked[0].debug, checked[0].line) == (
        checked[1].text, checked[1].debug, checked[1].line)
