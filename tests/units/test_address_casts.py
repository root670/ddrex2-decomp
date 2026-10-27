"""The cast-literal gate: a datum is reached by a name, or by one ``D_<ADDR>`` #define.

``tools/units/address_casts.py`` is the check.  Rule 3 of ``AGENTS.md`` says a promoted
source never reaches an object by a hard-coded address, and the *spelling* the tree settled
on is one of two: a real extern (the symbol table and objdiff then carry the reference) or
one file-scope ``#define`` named for the address.  Wrapping an access in that macro is
byte-identical by construction -- the tokens the compiler sees do not change -- and that is
what makes it the safe answer where retail materialises the address per use, as the
``net_game_logout`` measurement showed: a real symbol there CSEs the ``%hi`` and cost four
words.

The refusal is per *site*, not per file: there is no allowlist, and a macro with another
name (``LAST_DATA``) does not hide the address.  The pure tests feed the scanner text; the
last three drive the CLI and both wiring points (``configure.py``, ``compile.py``).
"""

import pathlib
import subprocess
import sys
from types import SimpleNamespace

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from units import address_casts  # noqa: E402

TOOL = ROOT / "tools/units/address_casts.py"


def run(*args):
    return subprocess.run([sys.executable, str(TOOL), *args],
                          capture_output=True, text=True)


def test_a_cast_inside_its_own_named_define_is_the_justification():
    """``#define D_0102FE88 (*(char *)0x0102FE88)`` is the form the tree keeps."""
    text = ("#define D_0102FE88 (*(char *)0x0102FE88)\n"
            "void f(void) { D_0102FE88 = 1; }\n")

    assert address_casts.cast_literals(text) == ()
    assert address_casts.require_named(text, "unit.c") is None


def test_a_define_spelt_with_another_name_does_not_hide_the_address():
    """The name has to *be* the address: ``LAST_DATA`` is a synonym, not the evidence."""
    text = "#define LAST_DATA (unsigned char *)0xFC29D0\nvoid f(void) { x = LAST_DATA; }\n"

    found = address_casts.cast_literals(text)

    assert len(found) == 1
    assert found[0].line == 1
    assert found[0].address == 0xFC29D0
    with pytest.raises(address_casts.CastAddress) as caught:
        address_casts.require_named(text, "unit.c")
    message = str(caught.value)
    assert "unit.c" in message
    assert "line 1" in message
    assert "0xFC29D0" in message
    assert "D_00FC29D0" in message
    assert "unit_symbols.txt" in message
    assert "four words" in message, "the measured counter-example is the remedy's reason"


def test_a_mismatched_name_is_a_finding_for_the_address_it_does_not_name():
    """A macro may justify only the address its name spells; a second literal stays a hit."""
    text = ("#define D_0102FFCC (*(int *)0x0102FFCC)\n"
            "#define D_0102FFC8 ((int *)0x0102FFD0)\n"
            "void f(void) { D_0102FFCC = D_0102FFC8[0]; }\n")

    found = address_casts.cast_literals(text)

    assert [(hit.line, hit.address) for hit in found] == [(2, 0x0102FFD0)]


def test_an_inline_pointer_cast_is_a_finding():
    text = ("struct _tag_cCmes *pCmes = (struct _tag_cCmes *)0x006D2E30;\n"
            "ps2dancerPdataLoadInit((void *)0x01874000);\n")

    found = address_casts.cast_literals(text)

    assert [(hit.line, hit.address) for hit in found] == [
        (1, 0x006D2E30), (2, 0x01874000)]
    assert found[0].text == "(struct _tag_cCmes *)0x006D2E30"


def test_a_cast_to_a_pointer_typedef_is_a_finding():
    """``(CwsWin)0x...`` is a pointer cast too, and the typedef is right there in the file."""
    text = ("typedef struct _CWS_WIN_W *CwsWin;\n"
            "CwsWin win = (CwsWin)0x0102FBCC;\n"
            "CwsWin2 = (OtherWin)0x0102FBD0;\n")

    found = address_casts.cast_literals(text)

    assert [(hit.line, hit.address) for hit in found] == [(2, 0x0102FBCC)]


def test_the_pointer_typedef_is_found_through_a_quoted_include(tmp_path):
    """A unit's typedef usually lives in its header, which is a repository path."""
    header = tmp_path / "types" / "win.h"
    header.parent.mkdir()
    header.write_text("typedef struct _CWS_WIN_W *CwsWin;\n")
    source = tmp_path / "unit.c"
    text = '#include "types/win.h"\nCwsWin win = (CwsWin)0x0102FBCC;\n'
    source.write_text(text)

    assert [hit.address for hit in address_casts.cast_literals(text, source)] == [0x0102FBCC]


def test_an_integer_cast_and_a_clean_file_are_left_alone():
    text = ("void f(void) {\n"
            "    int x = (int)0x2D;\n"
            "    win->obj[0]->tu = num % 8 * 42;\n"
            "}\n")

    assert address_casts.cast_literals(text) == ()
    assert address_casts.report(text, "unit.c") == []


def test_a_literal_in_a_string_or_a_comment_is_not_a_cast():
    text = ('char *s = "*(int *)0x01029FE4";\n'
            "/* CwsWin w = (CwsWin)0x0102FBCC; */\n"
            "// x = (int *)0x0102FBD0;\n")

    assert address_casts.cast_literals(text) == ()


def test_a_define_with_no_symbol_record_is_allowed():
    """The macro is the exception with a reason: no extern exists for this source."""
    path = ROOT / "src/common/cws/multi_window.c"
    text = "#define D_00824450 (*(struct _MULTI_WIN_W *)0x824450)\n"

    found = address_casts.cast_literals(text, path)

    assert found == ()
    assert address_casts._unit_symbol_records("src/common/cws/multi_window.c") == frozenset()


def test_a_define_whose_address_has_an_extern_record_is_refused():
    """The extern is preferred: a row for this source means the symbol is measurable now.

    ``net_win_peruser.c`` carries a ``unit_symbols.txt`` row for ``D_01029FE4`` -- its slot is
    a real extern, 4/4 bodies exact -- so a macro over that address in that file would be the
    convenience the policy forbids rather than the measured exception.
    """
    path = ROOT / "src/network/net_window/net_win_peruser.c"
    text = "#define D_01029FE4 (*(struct _NSV_USER_FILE_WORK **)0x01029FE4)\n"

    found = address_casts.cast_literals(text, path)

    assert [(hit.line, hit.address, hit.in_define, hit.recorded) for hit in found] == [
        (1, 0x01029FE4, True, True)]
    with pytest.raises(address_casts.CastAddress) as caught:
        address_casts.require_named(text, "src/network/net_window/net_win_peruser.c",
                                    path=path)
    message = str(caught.value)
    assert "unit_symbols.txt record for this source" in message
    assert "extern is available and preferred" in message


def test_every_source_under_src_is_clean():
    """The tree's own rule, over every file -- including the units that are not built yet."""
    offenders = {}
    for source in sorted((ROOT / "src").rglob("*.c")):
        found = address_casts.cast_literals(
            source.read_bytes().decode("latin-1"), source)
        if found:
            offenders[source.relative_to(ROOT).as_posix()] = [
                (hit.line, f"0x{hit.address:08X}") for hit in found]
    assert offenders == {}


def test_the_cli_exits_one_on_a_finding_and_zero_on_a_clean_file(tmp_path):
    bad = tmp_path / "bad.c"
    bad.write_text("void f(void) { x = (int *)0x0102FBD0; }\n")
    good = tmp_path / "good.c"
    good.write_text("#define D_0102FBD0 ((int *)0x0102FBD0)\nvoid f(void) { x = D_0102FBD0; }\n")

    failed = run("--check", str(bad))
    assert failed.returncode == 1
    assert "bad.c:1:" in failed.stderr
    assert "D_0102FBD0" in failed.stderr
    assert "unit_symbols.txt" in failed.stderr

    assert run("--check", str(good)).returncode == 0
    report = run(str(good))
    assert report.returncode == 0
    assert "no cast literal" in report.stdout


def test_the_cli_refuses_an_unusable_invocation(tmp_path):
    assert run(str(tmp_path / "absent.c")).returncode == 2
    assert run().returncode == 2


def test_configure_refuses_a_promoted_source_with_a_cast_literal(tmp_path):
    """``configure.py`` refuses the source before it writes the graph, naming the remedy."""
    from tests.test_configure import probe  # noqa: E402  the synthetic target builder
    import configure  # noqa: E402

    source = tmp_path / "src" / "promoted.c"
    source.parent.mkdir()
    source.write_text("struct _T *p = (struct _T *)0x006D2E30;\n")
    target = probe(tu_builds=(("src/promoted.c", "3.0-011126", "-c -g"),))

    with pytest.raises(configure.ConfigError) as caught:
        configure.check_promoted_sources(target, root=tmp_path)

    message = str(caught.value)
    assert "src/promoted.c" in message
    assert "1 cast literal(s) in this file" in message
    assert "D_006D2E30" in message

    source.write_text("#define D_006D2E30 ((struct _T *)0x006D2E30)\n"
                      "struct _T *p = D_006D2E30;\n")
    assert configure.check_promoted_sources(target, root=tmp_path) is None


def test_the_promotion_path_refuses_a_cast_literal(tmp_path):
    """``compile.place`` is the ``cc`` edge: the refusal comes before the compiler runs."""
    from toolchain import compile as cc  # noqa: E402

    source = tmp_path / "unit.c"
    source.write_text("void f(void) { x = (unsigned char *)0xE4D380; }\n")
    unit = SimpleNamespace(file="src/x/unit.c", source=source)

    with pytest.raises(cc.Unusable) as caught:
        cc.place(unit, None, None, None, None)

    message = str(caught.value)
    assert "src/x/unit.c" in message
    assert "0xE4D380" in message
    assert "D_00E4D380" in message

    source.write_text("#define D_00E4D380 ((unsigned char *)0xE4D380)\n"
                      "void f(void) { x = D_00E4D380; }\n")
    assert cc.refuse_cast_literals(unit.file, source.read_text()) is None
