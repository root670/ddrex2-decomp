"""`compile.py --syntax-only`: the original compiler as a C-syntax gate.

A generated header that does not compile as C is the loop's first blocker (plan M3 Task 1
Review Focus 1), so the check has to be made by `mwccps2 -lang c -O3 -g` -- the compiler
the units are measured against -- and not by a host `cc` that would accept the C++
spellings these headers used to carry.
"""
import pathlib, subprocess, sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
COMPILE = ROOT / "tools/toolchain/compile.py"

#: The pinned pair's flags, spelled once; `--syntax-only` is the wrapper's own.
MWCC = ["-c", "-lang", "c", "-O3", "-g"]


def run(*args):
    return subprocess.run([sys.executable, str(COMPILE), *args],
                          capture_output=True, text=True)


def test_it_accepts_c(tmp_path):
    include = tmp_path / "include"
    include.mkdir()
    (include / "work.h").write_text("struct _tag_WORK { int a; unsigned int b; };\n")
    source = tmp_path / "probe.c"
    source.write_text('#include "work.h"\n'
                      "struct _tag_WORK *f(struct _tag_WORK *p) { return p; }\n")
    result = run("--syntax-only", "--include", str(include), str(source), *MWCC)
    assert result.returncode == 0, result.stdout + result.stderr
    assert not list(tmp_path.rglob("*.o")), "a syntax check produces no object"


def test_it_reports_cpp_spellings_with_the_compilers_own_message(tmp_path):
    """A bare tag is what every generated header used to emit, and it is not C."""
    source = tmp_path / "probe.c"
    source.write_text("struct _tag_WORK { int a; };\n"
                      "_tag_WORK *pscf;\n")
    result = run("--syntax-only", str(source), *MWCC)
    assert result.returncode == 1
    assert "syntax error" in result.stdout + result.stderr
    assert not list(tmp_path.rglob("*.o"))


def test_it_requires_a_source(tmp_path):
    result = run("--syntax-only", "--include", str(tmp_path))
    assert result.returncode == 2
    assert "source" in result.stderr


def test_an_include_directory_that_is_not_there_is_a_configuration_error(tmp_path):
    source = tmp_path / "probe.c"
    source.write_text("int main(void) { return 0; }\n")
    result = run("--syntax-only", "--include", str(tmp_path / "absent"), str(source))
    assert result.returncode == 2
    assert "absent" in result.stderr
