import subprocess, sys, pathlib

ROOT = pathlib.Path(__file__).resolve().parents[2]
CLI = ROOT / "tools/oracle/dwarf1.py"
ELF = ROOT / "orig/SLUS_207.11"


def run(cmd, *args):
    # the upstream CLI is `dwarf1.py <cmd> <elf> …`; keep that order verbatim
    return subprocess.run([sys.executable, str(CLI), cmd, str(ELF), *args],
                          capture_output=True, text=True, check=True).stdout


def test_dwarf_counts_match_retail():
    out = run("stats")
    assert "compile units 480 (423 with code)" in out
    assert "translation units 57" in out
    assert "functions 423 (with code 423)" in out
    assert "818 (123 distinct names)" in out
    assert "unique globals/statics 639" in out


def test_tree_is_self_consistent():
    assert "0 sibling/length problems" in run("check")


def test_known_function_bounds_and_lines():
    assert "sysInitScf" in run("fn", "sysInitScf")
    assert "0x0021c420" in run("lines", "0x21c420")
