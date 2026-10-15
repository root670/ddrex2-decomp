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
