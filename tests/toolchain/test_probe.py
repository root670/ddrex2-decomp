import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch, probe

PROBE_C = ROOT / "tests/toolchain/probe.c"


def test_compiler_produces_metrowerks_object(tmp_path):
    d = fetch.compiler("2.4-001213")
    obj = tmp_path / "probe.o"
    probe.compile(PROBE_C, obj, d, fetch.wibo(),
                  ["-c", "-lang", "c", "-O2", "-g"])
    info = probe.inspect(obj)
    # MWCC writes its own ident into .comment; the "PlayStation2" half of the retail
    # .comment is contributed by MWLD at link time (test below).
    assert info["comment"] == b"MW MIPS C Compiler (2.4.1.01)\x00"
    assert ".debug" in info["sections"] and ".line" in info["sections"]
    assert info["sections"][".debug"][0] == 0x70000005      # SHT_MIPS_DEBUG
    assert "sysInitScf" in info["text_symbols"]


def test_linker_contributes_playstation2_to_comment(tmp_path):
    """The 43-byte retail .comment is MWCC's ident plus MWLD's; only a link shows both."""
    d = fetch.compiler("2.4-001213")
    obj = tmp_path / "probe.o"
    elf_path = tmp_path / "probe.elf"
    probe.compile(PROBE_C, obj, d, fetch.wibo(), ["-c", "-lang", "c", "-O2", "-g"])
    probe.link([obj], elf_path, d, fetch.wibo(), entry="sysInitScf")
    assert probe.inspect(elf_path)["comment"] == \
        b"MW MIPS C Compiler (2.4.1.01)\x00PlayStation2\x00"


def test_compile_reports_the_rejected_flag(tmp_path):
    """A rejected flag is reported by name, never dropped from the command line."""
    d = fetch.compiler("2.4-001213")
    with pytest.raises(probe.CompilerFailed) as excinfo:
        probe.compile(PROBE_C, tmp_path / "probe.o", d, fetch.wibo(),
                      ["-c", "-lang", "c", "-O2", "-g", "-notaflag"])
    assert "-notaflag" in str(excinfo.value)


def test_inspect_keeps_every_repeated_section_visible(tmp_path):
    """MWCC emits one .text/.debug/.line group per function; none may be hidden."""
    d = fetch.compiler("2.4-001213")
    obj = tmp_path / "probe.o"
    probe.compile(PROBE_C, obj, d, fetch.wibo(), ["-c", "-lang", "c", "-O2", "-g"])
    info = probe.inspect(obj)
    assert info["sections"][".debug"][0] == 0x70000005
    assert info["debug_kind"] == "MIPS_DEBUG"
    assert info["section_names"].count(".debug") >= 2
    assert set(info["text"]) == {"sysGetDateNotation", "sysInitScf"}


# ---------------------------------------------------------------------------
# The invocation itself: with a runner (macOS/Linux) and without one (native Windows)
#
# Both cases are exercised here on one host by handing `_invoke` a small script that echoes
# its argv: what reaches the tool *is* the command line, and the two rules differ only in
# whether the runner's path comes first.
# ---------------------------------------------------------------------------

ECHO_ARGV = '#!/bin/sh\nfor arg in "$@"; do echo "$arg"; done\n'
#: The same, but it also creates the ``-o`` file: a tool that *succeeds* on the native path,
#: so ``link``'s own `_checked` gate is what accepts the run.
ECHO_ARGV_WRITING_OUTPUT = (
    '#!/bin/sh\n'
    'while [ $# -gt 0 ]; do\n'
    '  echo "$1"\n'
    '  if [ "$1" = "-o" ]; then : > "$2"; fi\n'
    '  shift\n'
    'done\n'
)


def _echo_tool(directory: pathlib.Path, name: str,
               body: str = ECHO_ARGV) -> pathlib.Path:
    path = directory / name
    path.write_text(body)
    path.chmod(0o755)
    return path


@pytest.mark.skipif(sys.platform.startswith("win"),
                    reason="a .exe cannot be a /bin/sh script; Windows runs the real tool")
def test_a_native_run_execs_the_tool_with_no_runner_in_argv(tmp_path):
    """``wibo is None`` means the tool is the program: argv[0] is the tool, not ``wibo``."""
    compiler_dir = tmp_path / "compiler"
    compiler_dir.mkdir()
    tool = _echo_tool(compiler_dir, probe.COMPILER_NAME)
    result = probe._invoke(None, compiler_dir, probe.COMPILER_NAME, ["-c", "-lang", "c"])
    assert result.returncode == 0
    assert result.stdout.split() == ["-c", "-lang", "c"]
    assert str(tool.resolve()) not in result.stdout     # the tool itself is not an argument


@pytest.mark.skipif(sys.platform.startswith("win"),
                    reason="a .exe cannot be a /bin/sh script; Windows runs the real tool")
def test_a_runner_still_comes_first_in_argv(tmp_path):
    """The macOS/Linux command is byte-identical: ``wibo <tool> <argv>``."""
    compiler_dir = tmp_path / "compiler"
    compiler_dir.mkdir()
    tool = _echo_tool(compiler_dir, probe.COMPILER_NAME)
    runner = _echo_tool(tmp_path, "wibo")
    result = probe._invoke(runner, compiler_dir, probe.COMPILER_NAME, ["-c"])
    assert result.stdout.split() == [str(tool), "-c"]
    assert probe._runner_prefix(runner) == [str(runner.resolve())]
    assert probe._runner_prefix(None) == []


@pytest.mark.skipif(sys.platform.startswith("win"),
                    reason="a .exe cannot be a /bin/sh script; Windows runs the real tool")
def test_link_takes_the_same_no_runner_path(tmp_path):
    """``link`` is ``_invoke`` plus MWLD's argv, so ``None`` reaches it the same way."""
    compiler_dir = tmp_path / "compiler"
    compiler_dir.mkdir()
    _echo_tool(compiler_dir, probe.LINKER_NAME, ECHO_ARGV_WRITING_OUTPUT)
    obj = tmp_path / "probe.o"
    obj.write_bytes(b"")
    out = tmp_path / "probe.elf"
    probe.link([obj], out, compiler_dir, None, entry="sysInitScf")
    assert out.is_file() and out.stat().st_size == 0   # the tool ran and `_checked` accepted it

