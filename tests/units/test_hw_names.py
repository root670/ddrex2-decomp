"""The hardware-name gate: a register or the VU1 window is named, never cast.

``tools/units/hw_names.py`` is the check: a cast to an absolute address in the EE register
block (0x10000000-0x101FFFFF) or the VU1 memory window (0x70000000-0x70003FFF) fails, and
the remedy names the ``hwinclude`` header that defines the block.  The pure tests need no
compiler -- they feed the scanner source text -- and the last three exercise the two CLI
entry points and every promoted source in the tree.
"""

import pathlib
import re
import subprocess
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from units import hw_names  # noqa: E402

TOOL = ROOT / "tools/units/hw_names.py"
STRIP = ROOT / "tools/units/strip_comments.py"
DMA_HEADER = "hwinclude/hw/ee_dma.h"
VU_HEADER = "hwinclude/hw/vu1_mem.h"


def run(tool, *args):
    return subprocess.run([sys.executable, str(tool), *args], capture_output=True, text=True)


def _cast(address, text="x"):
    return f"unsigned int *p = (volatile unsigned int *)0x{address:08X};\n"


@pytest.mark.parametrize("address, header", [
    (0x10008000, DMA_HEADER),
    (0x1000A020, DMA_HEADER),
    (0x1000B080, DMA_HEADER),
    (0x1000E000, DMA_HEADER),
    (0x1000E060, DMA_HEADER),
    (0x70000000, VU_HEADER),
    (0x70000010, VU_HEADER),
    (0x70003FFF, VU_HEADER),
])
def test_a_pointer_cast_to_a_hardware_address_names_its_header(address, header):
    found = hw_names.raw_casts(_cast(address))

    assert len(found) == 1
    assert found[0].address == address
    assert found[0].line == 1
    assert found[0].header == header
    with pytest.raises(hw_names.RawAddressCast) as caught:
        hw_names.require_named(_cast(address), "unit.c")
    message = str(caught.value)
    assert f"0x{address:08X}" in message
    assert header in message
    assert "unit.c" in message


def test_the_boundaries_are_the_two_stated_ranges():
    for address, flagged in ((0x10000000, True), (0x101FFFFF, True),
                             (0x0FFFFFFF, False), (0x10200000, False),
                             (0x70000000, True), (0x70003FFF, True),
                             (0x6FFFFFFF, False), (0x70004000, False)):
        assert bool(hw_names.raw_casts(_cast(address))) is flagged, hex(address)


def test_an_ee_register_no_header_names_yet_asks_for_one():
    found = hw_names.raw_casts(_cast(0x10000010))

    assert found[0].header is None
    with pytest.raises(hw_names.RawAddressCast) as caught:
        hw_names.require_named(_cast(0x10000010))
    message = str(caught.value)
    assert "no header under hwinclude/hw/" in message
    assert "lvalue macro" in message


def test_an_integer_cast_is_a_value_not_an_address():
    """A GIF tag's ``0x10000003`` is a bit pattern; it never names a register."""
    for body in ("unsigned int tag = (unsigned int)0x10000003;\n",
                 "unsigned int a = 0x70000000;\n",
                 "int size = 0x100000;\n",
                 "unsigned int v = *(volatile unsigned int *)0x1000A020;\n"):
        expected = 1 if "0x1000A020" in body else 0
        assert len(hw_names.raw_casts(body)) == expected, body


def test_a_literal_inside_a_string_or_a_comment_is_not_a_cast():
    body = ('char *s = "(unsigned int *)0x1000A020";\n'
            '/* unsigned int *p = (unsigned int *)0x70000010; */\n'
            '// unsigned int *q = (unsigned int *)0x1000E000;\n')
    assert hw_names.raw_casts(body) == ()


def test_a_pointer_cast_outside_both_ranges_is_left_alone():
    """The three raw game-state addresses the tree keeps: no hardware fact, no macro."""
    body = ("struct _tag_cCmes *pCmes = (struct _tag_cCmes *)0x006D2E30;\n"
            "struct _tag_cOpening *pOpening = (struct _tag_cOpening *)0x006D33A0;\n"
            "ps2dancerPdataLoadInit((void *)0x01874000);\n")
    assert hw_names.raw_casts(body) == ()


def test_every_promoted_source_passes_the_gate():
    """The tree's own rule: no ``src/`` file reaches hardware by a cast."""
    offenders = {}
    for source in sorted((ROOT / "src").rglob("*.c")):
        found = hw_names.raw_casts(source.read_bytes().decode("latin-1"))
        if found:
            offenders[source.relative_to(ROOT).as_posix()] = [
                (violation.line, f"0x{violation.address:08X}") for violation in found]
    assert offenders == {}


def test_the_headers_are_where_the_cast_is_spelt():
    """Every DMAC register the header defines maps back to it, in the lvalue shape.

    The header is exempt from the gate because it is never scanned; this pins the other half
    of that bargain -- the cast it does spell is the DMAC map, and each address resolves to
    the header itself.
    """
    text = (ROOT / DMA_HEADER).read_text()
    addresses = [int(value, 16) for value in
                 re.findall(r"\(\*\(volatile unsigned int \*\)0x([0-9A-Fa-f]+)u\)", text)]
    assert len(addresses) == 35
    for address in addresses:
        assert hw_names.header_for(address) == DMA_HEADER, hex(address)
    assert len(set(addresses)) == len(addresses)
    assert {address & 0xFF for address in addresses} <= {0x00, 0x10, 0x20, 0x30,
                                                          0x40, 0x50, 0x60, 0x80}
    vu = (ROOT / VU_HEADER).read_text()
    assert "VU1_MEM_BASE 0x70000000u" in vu
    assert "VU1_MEM_U128" in vu and "unsigned __int128" in vu
    assert "VU1_MEM_PTR(type, offset) ((type *)(VU1_MEM_BASE + (offset)))" in vu


def test_the_cli_reports_the_remedy_and_exits_one(tmp_path):
    bad = tmp_path / "bad.c"
    bad.write_text(_cast(0x1000A020))
    good = tmp_path / "good.c"
    good.write_text("D2_TADR = 0;\n")

    failed = run(TOOL, str(bad))
    assert failed.returncode == 1
    assert DMA_HEADER in failed.stderr
    assert "line 1" in failed.stderr

    passed = run(TOOL, str(good))
    assert passed.returncode == 0, passed.stderr
    assert "no raw hardware cast" in passed.stdout


def test_the_cli_refuses_a_missing_file(tmp_path):
    result = run(TOOL, str(tmp_path / "absent.c"))

    assert result.returncode == 2
    assert "does not exist" in result.stderr


def test_strip_comments_check_runs_the_hardware_gate(tmp_path):
    """``--check`` is one invocation for both source-form rules: comments and hardware names."""
    source = tmp_path / "unit.c"
    body = _cast(0x70000010)
    source.write_text(body)

    result = run(STRIP, "--no-verify", "--check", str(source))

    assert result.returncode == 1
    assert VU_HEADER in result.stderr
    assert "by memory, not by name" in result.stderr
    assert source.read_text() == body, "--check writes nothing"

    source.write_text("gs3d->vp = VU1_MEM_PTR(FVEC4, 0x10);\n")
    fixed = run(STRIP, "--no-verify", "--check", str(source))
    assert fixed.returncode == 0, fixed.stderr
