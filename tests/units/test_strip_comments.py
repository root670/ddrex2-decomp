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

    expected = (" " * len("/* head */") + "\n"
                "int f(void) {\n"
                "             \n"
                "                        \n"
                "    return 1;\n"
                "}\n")
    assert stripped == expected
    assert stripped.count("\n") == source.count("\n")


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
# every comment goes: no header, no marker, no exception
# ---------------------------------------------------------------------------


def test_the_leading_block_header_is_blanked_like_any_comment():
    source = "/* src/x.c -- what this is.\n *\n * More provenance. */\nint a; /* gone */\n"

    stripped = sc.strip(source)

    assert sc.scan(stripped) == ()
    assert "src/x.c" not in stripped
    assert "More provenance" not in stripped
    assert "/* gone */" not in stripped
    assert stripped.count("\n") == source.count("\n")
    assert stripped.splitlines()[-1].rstrip() == "int a;"


def test_a_leading_line_header_run_is_blanked():
    source = ("// header one\n"
              "// header two\n"
              "\n"
              "int a; // gone\n")

    stripped = sc.strip(source)

    assert sc.scan(stripped) == ()
    assert stripped == (" " * len("// header one") + "\n"
                        + " " * len("// header two") + "\n"
                        + "\n"
                        + "int a; " + " " * len("// gone") + "\n")


def test_a_marked_block_comment_is_blanked_too():
    source = "/*! keep this: magic constant 1 */\nint a = 1; /* drop this */\n"

    stripped = sc.strip(source)

    assert sc.scan(stripped) == ()
    assert "keep this" not in stripped
    assert "drop this" not in stripped


def test_a_marked_line_comment_is_blanked_too():
    source = "int a = 1; //! delay slot packing\nint b; // note\n"

    stripped = sc.strip(source)

    assert sc.scan(stripped) == ()
    assert "delay slot packing" not in stripped
    assert "// note" not in stripped


def test_the_header_and_a_marker_are_blanked_alike():
    source = ("/* header */\n"
              "/* second note */\n"
              "/*! third note */\n")

    stripped = sc.strip(source)

    assert sc.scan(stripped) == ()
    assert stripped.strip() == ""


def test_require_no_comments_accepts_a_clean_source():
    sc.require_no_comments("int a;\n")


def test_require_no_comments_refuses_a_marked_note():
    with pytest.raises(sc.Refused) as excinfo:
        sc.require_no_comments("int a;\n/*! notes a magic constant */\n")

    assert "still carries 1 comment(s)" in str(excinfo.value)
    assert "carries none" in str(excinfo.value)
    assert "line 2" in str(excinfo.value)


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


def test_the_cli_check_fails_a_file_that_still_carries_a_comment(tmp_path):
    source = tmp_path / "plain.c"
    body = "int a; /*! a load-bearing note */\n"
    source.write_text(body)

    result = run("--no-verify", "--check", str(source))

    assert result.returncode == 1
    assert "still carries 1 comment(s)" in result.stderr
    assert "carries none" in result.stderr
    assert source.read_text() == body, "--check writes nothing"


def test_the_cli_check_passes_a_clean_file(tmp_path):
    source = tmp_path / "plain.c"
    body = "int a;\n"
    source.write_text(body)

    result = run("--no-verify", "--check", str(source))

    assert result.returncode == 0, result.stderr
    assert "no comments remain" in result.stdout
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
    committed = tu.source.read_bytes()
    # The promoted file is comment-free; put a comment back so this still exercises the
    # blanking (inline, so no line moves) rather than passing on an identity transform.
    original = committed.replace(b"\n", b" /* probe note */\n", 1)
    stripped = sc.strip(original.decode("latin-1")).encode("latin-1")
    assert stripped != original and sc.scan(stripped.decode("latin-1")) == ()
    target = targets.get(targets.DEFAULT)

    before = cc._place_source(tu, manifests, compiler_dir, wibo, flags, original,
                              tmp_path / "before.mw.o", normalise, adopt)
    after = cc._place_source(tu, manifests, compiler_dir, wibo, flags, stripped,
                             tmp_path / "after.mw.o", normalise, adopt)

    assert (before.text, before.debug, before.line) == (after.text, after.debug, after.line)

    checked = sc.verify(tu, original, stripped, target)
    assert (checked[0].text, checked[0].debug, checked[0].line) == (
        checked[1].text, checked[1].debug, checked[1].line)


# ---------------------------------------------------------------------------
# the tidy (--collapse): blank runs, trailing whitespace, the header, adoption
# ---------------------------------------------------------------------------


def test_collapse_reduces_a_blank_run_to_one_line():
    source = "int a;\n\n\n\nint b;\n\n\nint c;\n"

    assert sc.collapse(source) == "int a;\n\nint b;\n\nint c;\n"


def test_collapse_drops_leading_and_trailing_blank_lines():
    source = "\n\nint a;\n\n\nint b;\n\n\n\n"

    assert sc.collapse(source) == "int a;\n\nint b;\n"


def test_collapse_trims_trailing_whitespace_without_moving_a_line():
    source = "int a;   \nint b;\t \n\n   \nint c;\n"

    tidied = sc.collapse(source)

    assert tidied == "int a;\nint b;\n\nint c;\n"
    assert sc._moves_lines(source, tidied) is True, "the whitespace-only run collapsed"


def test_collapse_drops_the_header_block_and_the_notes_entirely():
    source = ("/* src/x.c -- what this file is, over\n"
              " * several lines and two paragraphs.\n"
              " *\n"
              " * More measurements live here. */\n"
              "\n"
              "int a; /*! a load-bearing note */\n"
              "//! another load-bearing note\n"
              "int b;\n")

    tidied = sc.collapse(source)

    assert tidied.startswith("int a;"), "a promoted file starts with its first declaration"
    assert sc.scan(tidied) == ()
    assert "src/x.c" not in tidied
    assert "reconstructed from DWARF 1" not in tidied
    assert "measurements live here" not in tidied
    assert "load-bearing" not in tidied
    assert tidied == "int a;\n\nint b;\n"


def test_collapse_is_idempotent():
    source = "/* head\n * two lines */\n\n\nint a;\n\nint b;   \n"

    once = sc.collapse(source)

    assert sc.collapse(once) == once


def test_collapse_drops_a_blank_line_inside_a_open_and_close_brace():
    source = ("void f(void) {\n"
              "\n"
              "    int a;\n"
              "\n"
              "    int b;\n"
              "\n"
              "}\n"
              "\n"
              "void g(void) {\n"
              "\n"
              "    if (a) {\n"
              "\n"
              "        b();\n"
              "\n"
              "    }\n"
              "}\n")

    tidied = sc.collapse(source)

    assert tidied == ("void f(void) {\n"
                      "    int a;\n"
                      "\n"
                      "    int b;\n"
                      "}\n"
                      "\n"
                      "void g(void) {\n"
                      "    if (a) {\n"
                      "        b();\n"
                      "    }\n"
                      "}\n")
    assert sc._brace_edge_blanks(tidied.splitlines()) == ()


def test_collapse_drops_a_blank_line_at_a_brace_with_else():
    source = ("void f(void) {\n"
              "    if (a) {\n"
              "        b();\n"
              "\n"
              "    } else {\n"
              "\n"
              "        c();\n"
              "    }\n"
              "}\n")

    tidied = sc.collapse(source)

    assert tidied == ("void f(void) {\n"
                      "    if (a) {\n"
                      "        b();\n"
                      "    } else {\n"
                      "        c();\n"
                      "    }\n"
                      "}\n")


def test_require_no_brace_padding_refuses_a_blank_after_an_opening_brace():
    with pytest.raises(sc.Refused) as excinfo:
        sc.require_no_brace_padding("void f(void) {\n\n    int a;\n}\n")

    assert "blank line directly inside a brace" in str(excinfo.value)
    assert "line 2" in str(excinfo.value)


def test_require_no_brace_padding_refuses_a_blank_before_a_closing_brace():
    with pytest.raises(sc.Refused) as excinfo:
        sc.require_no_brace_padding("void f(void) {\n    int a;\n\n}\n")

    assert "line 3" in str(excinfo.value)


def test_require_no_brace_padding_accepts_blanks_between_statements():
    sc.require_no_brace_padding("void f(void) {\n    int a;\n\n    int b;\n}\n")


def test_a_comment_sharing_its_line_with_code_leaves_the_code():
    tidied = sc.collapse("/* head */ int a;\n")

    assert tidied == " " * len("/* head */") + " int a;\n"
    assert sc.scan(tidied) == ()


def test_a_tidy_that_moves_a_line_requires_an_adoption_state():
    source = "/* head */\n\n\nint a;\n"
    tidied = sc.collapse(source)

    assert sc._moves_lines(source, tidied) is True
    for state in (False, True):
        with pytest.raises(sc.Refused) as excinfo:
            sc._require_adoption("src/x.c", state, True)
        assert "records" in str(excinfo.value)
        assert "adopt" in str(excinfo.value)
        assert "refusing to write it" in str(excinfo.value)
    sc._require_adoption("src/x.c", "adopt", True)
    sc._require_adoption("src/x.c", False, False)


def test_verify_refuses_a_moved_tidy_without_an_adoption_row():
    """The rule is enforced by the compile gate, not only by convention."""
    from types import SimpleNamespace

    target = SimpleNamespace(build_pair=lambda _file: ("3.0b38-030307", "-c -lang c", False))
    tu = SimpleNamespace(file="src/x.c")

    with pytest.raises(sc.Refused) as excinfo:
        sc.verify(tu, b"/* head */\n\n\nint a;\n", b"\nint a;\n", target,
                  tidy=True)

    assert "src/x.c records False" in str(excinfo.value)
    assert "adopt" in str(excinfo.value)
    assert "refusing to write it" in str(excinfo.value)


def test_a_tidy_that_moves_nothing_needs_no_adoption_state():
    source = "int a;   \nint b;\t\n"

    tidied = sc.collapse(source)

    assert sc._moves_lines(source, tidied) is False
    sc._require_adoption("src/x.c", False, sc._moves_lines(source, tidied))


def test_a_tidied_source_whose_text_moves_is_refused():
    from types import SimpleNamespace

    before = SimpleNamespace(text=b"\x01\x02", debug=b"d", line=b"l")
    after = SimpleNamespace(text=b"\x01\x03", debug=b"d", line=b"l")

    with pytest.raises(sc.Refused) as excinfo:
        sc.compare(before, after, "tidied")

    assert "same text" in str(excinfo.value)
    assert "refusing to write it" in str(excinfo.value)


def test_a_tidy_that_changes_the_record_grouping_is_refused():
    from types import SimpleNamespace

    def placed(*counts):
        return SimpleNamespace(sizes=[(name, ".line", count * 10, pinned * 10)
                                      for name, count, pinned in counts])

    before = placed(("f", 7, 7), ("g", 3, 3))
    after = placed(("f", 8, 7), ("g", 2, 3))

    with pytest.raises(sc.Refused) as excinfo:
        sc.compare_grouping(before, after)

    assert "f 7 -> 8" in str(excinfo.value)
    assert "grouping did not survive" in str(excinfo.value)
    sc.compare_grouping(placed(("f", 7, 7)), placed(("f", 7, 7)))


def test_the_cli_collapse_layout_edit_with_no_verify(tmp_path):
    source = tmp_path / "plain.c"
    source.write_text("/* head\n * two lines */\n\n\nint a;   \n")

    result = run("--collapse", "--no-verify", str(source))

    assert result.returncode == 0, result.stderr
    assert source.read_bytes() == sc.collapse(
        "/* head\n * two lines */\n\n\nint a;   \n").encode("latin-1")
    assert "nothing was compiled" in result.stdout


def test_the_cli_check_fails_a_blank_line_inside_a_brace(tmp_path):
    source = tmp_path / "plain.c"
    body = "void f(void) {\n\n    int a;\n}\n"
    source.write_text(body)

    result = run("--no-verify", "--check", str(source))

    assert result.returncode == 1
    assert "blank line directly inside a brace" in result.stderr
    assert source.read_text() == body, "--check writes nothing"


def test_the_cli_collapse_check_fails_a_file_that_still_carries_a_header(tmp_path):
    source = tmp_path / "plain.c"
    body = "/* head\n * two lines */\n\n\nint a;\n"
    source.write_text(body)

    result = run("--collapse", "--no-verify", "--check", str(source))

    assert result.returncode == 1
    assert "still carries 1 comment(s)" in result.stderr
    assert source.read_text() == body, "--check writes nothing"


def test_the_cli_collapse_check_passes_a_clean_file(tmp_path):
    source = tmp_path / "plain.c"
    body = "int a;\n\nint b;\n"
    source.write_text(body)

    result = run("--collapse", "--no-verify", "--check", str(source))

    assert result.returncode == 0, result.stderr
    assert "no comments remain" in result.stdout
    assert source.read_text() == body


def test_the_cli_collapse_refuses_a_non_unit_without_layout_edit(tmp_path):
    source = tmp_path / "plain.c"
    body = "/* head */\n\n\nint a;\n"
    source.write_text(body)

    result = run("--collapse", str(source))

    assert result.returncode == 2
    assert "nothing can be compiled" in result.stderr
    assert source.read_text() == body


def test_a_tidied_unit_compiles_with_the_same_record_grouping(tmp_path):
    """The tidy's compile gate: .text identical, retail's .debug/.line, equal counts."""
    from config import targets
    from toolchain import compile as cc

    tu, manifests, compiler_dir, wibo, flags, normalise, adopt = _unit_and_compiler()
    committed = tu.source.read_bytes()
    # Re-dirty the comment-free file (a header and a note line) so the tidy really strips,
    # deletes those lines and shifts statements, instead of collapsing an identity.
    original = b"/* probe header */\n\n" + committed.replace(
        b"\n", b"\n    /*! probe note */\n", 1)
    tidied = sc.collapse(original.decode("latin-1")).encode("latin-1")
    assert sc.scan(tidied.decode("latin-1")) == ()
    assert sc._moves_lines(original.decode("latin-1"), tidied.decode("latin-1"))
    target = targets.get(targets.DEFAULT)

    before = cc._place_source(tu, manifests, compiler_dir, wibo, flags, original,
                              tmp_path / "before.mw.o", normalise, adopt, allow_line=True)
    after = cc._place_source(tu, manifests, compiler_dir, wibo, flags, tidied,
                             tmp_path / "after.mw.o", normalise, adopt, allow_line=True)

    assert before.text == after.text
    assert sc.record_counts(before) == sc.record_counts(after)
    checked = sc.verify(tu, original, tidied, target, tidy=True)
    retail = cc.retail_bytes(tu, text_size=len(checked[1].text))
    assert (checked[1].text, checked[1].debug, checked[1].line) == (
        retail["text"], retail["debug"], retail["line"])


# ---------------------------------------------------------------------------
# the brace-attach pass: every block-opening brace joins its statement
# ---------------------------------------------------------------------------


def test_attach_joins_a_brace_alone_on_the_next_line():
    source = ("void f(void)\n"
              "{\n"
              "    if (a)\n"
              "    {\n"
              "        b();\n"
              "    }\n"
              "}\n")

    attached = sc.attach_braces(source)

    assert attached.text == ("void f(void) {\n"
                             "    if (a) {\n"
                             "        b();\n"
                             "    }\n"
                             "}\n")
    assert attached.joined == 2
    assert attached.skipped == ()


def test_attach_joins_a_nested_inline_block_and_keeps_its_statement():
    source = ("void f(void)\n"
              "{\n"
              "    do\n"
              "    { x = 1;\n"
              "        for (i = 0; i < 2; i++)\n"
              "        { for (j = 0; j < 2; j++)\n"
              "            { a[i][j] = 0;\n"
              "            } }\n"
              "    } while (x);\n"
              "}\n")

    attached = sc.attach_braces(source)

    assert attached.text == ("void f(void) {\n"
                             "    do { x = 1;\n"
                             "        for (i = 0; i < 2; i++) { for (j = 0; j < 2; j++) "
                             "{ a[i][j] = 0;\n"
                             "            } }\n"
                             "    } while (x);\n"
                             "}\n")
    assert attached.joined == 4


def test_attach_leaves_an_else_brace_that_already_reads_that_way():
    source = ("void f(void) {\n"
              "    if (a) {\n"
              "        b();\n"
              "    } else {\n"
              "        c();\n"
              "    }\n"
              "}\n")

    attached = sc.attach_braces(source)

    assert attached.text == source
    assert attached.joined == 0


def test_attach_joins_a_brace_after_a_bare_else_and_do():
    source = ("void f(void)\n"
              "{\n"
              "    if (a)\n"
              "        b();\n"
              "    else\n"
              "    {\n"
              "        c();\n"
              "    }\n"
              "    do\n"
              "    {\n"
              "        d();\n"
              "    } while (a);\n"
              "}\n")

    attached = sc.attach_braces(source)

    assert "    else {" in attached.text
    assert "    do {" in attached.text
    assert attached.joined == 3


def test_attach_skips_a_brace_after_a_declaration():
    source = ("int a;\n"
              "{\n"
              "    a = 1;\n"
              "}\n")

    attached = sc.attach_braces(source)

    assert attached.text == source, "the declaration keeps its line and the brace stays"
    assert attached.joined == 0
    assert len(attached.skipped) == 1
    line, reason = attached.skipped[0]
    assert line == 2
    assert "declaration that must keep its line" in reason


def test_attach_skips_a_block_whose_first_statement_is_a_declaration():
    source = ("void f(void)\n"
              "{\n"
              "    if (a)\n"
              "    { int b; b = 1; }\n"
              "}\n")

    attached = sc.attach_braces(source)

    assert attached.text == ("void f(void) {\n"
                             "    if (a)\n"
                             "    { int b; b = 1; }\n"
                             "}\n")
    assert attached.joined == 1
    assert attached.skipped and "first statement is a declaration" in attached.skipped[0][1]


def test_attach_skips_an_aggregate_initializer_row():
    source = ("static int t[] = {\n"
              "    { 1, 2 },\n"
              "    { 3, 4 },\n"
              "};\n")

    attached = sc.attach_braces(source)

    assert attached.text == source
    assert attached.joined == 0
    assert len(attached.skipped) == 2
    assert all("aggregate initializer" in reason for _line, reason in attached.skipped)


def test_attach_is_idempotent():
    source = ("void f(void)\n"
              "{\n"
              "    for (i = 0; i < 2; i++)\n"
              "    { for (j = 0; j < 2; j++)\n"
              "        { a[i][j] = 0;\n"
              "        } }\n"
              "}\n")

    once = sc.attach_braces(source)

    assert sc.attach_braces(once.text) == sc.Attached(once.text, 0, ())


def test_the_tidy_attaches_braces_and_reports_the_joins():
    source = "void f(void)\n{\n    return;\n}\n"

    tidied = sc.tidy(source)

    assert tidied.text == "void f(void) {\n    return;\n}\n"
    assert tidied.joined == 1
    assert sc.collapse(source) == tidied.text


@pytest.mark.parametrize("part", ["text", "debug", "line"])
def test_a_brace_attached_source_whose_part_moves_is_refused(part):
    from types import SimpleNamespace

    before = SimpleNamespace(text=b"\x01\x02", debug=b"d", line=b"l")
    after = SimpleNamespace(**{**vars(before),
                               part: bytes([getattr(before, part)[0] ^ 1])})

    with pytest.raises(sc.Refused) as excinfo:
        sc.compare(before, after, "brace-attached")

    assert f"same {part}" in str(excinfo.value)
    assert "refusing to write it" in str(excinfo.value)


def test_the_cli_reports_the_braces_it_attached(tmp_path):
    source = tmp_path / "plain.c"
    source.write_text("void f(void)\n{\n    return;\n}\n")

    result = run("--collapse", "--no-verify", str(source))

    assert result.returncode == 0, result.stderr
    assert "1 block-opening brace(s) attached" in result.stdout
    assert source.read_text() == "void f(void) {\n    return;\n}\n"


def test_the_cli_reports_a_skipped_brace(tmp_path):
    source = tmp_path / "plain.c"
    body = "int a;\n{\n    a = 1;\n}\n"
    source.write_text(body)

    result = run("--collapse", "--no-verify", str(source))

    assert result.returncode == 0, result.stderr
    assert "0 block-opening brace(s) attached" in result.stdout
    assert "line 2: brace not attached" in result.stdout
    assert "declaration that must keep its line" in result.stdout
    assert source.read_text() == body
