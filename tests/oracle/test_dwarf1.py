"""The vendored DWARF 1 reader, against the registered target's binary.

The reader is the one piece of `tools/oracle` that is vendored third-party code, and every other
emitter's answer is only as good as its parse: this suite pins the properties the project relies on
-- translation units with compile units, compile units that tile the section, a function lookup by
address, names and ELF symbols -- on the binary actually being decompiled.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/oracle"))
sys.path.insert(0, str(ROOT))

import dwarf1  # noqa: E402
from tests import target_support  # noqa: E402

TARGET = target_support.registered()
pytestmark = pytest.mark.skipif(
    not TARGET.elf.is_file(), reason=f"{TARGET.name}: orig/{TARGET.elf.name} is not placed")


@pytest.fixture(scope="module")
def dw():
    return dwarf1.Dwarf(str(TARGET.elf))


def test_the_parse_finds_translation_units_and_their_compile_units(dw):
    assert dw.tus, "no translation unit was parsed"
    for tu in dw.tus:
        assert tu.cus, tu.name
        assert tu.decl is not None
        assert tu.cus[0].off >= 0


def test_the_compile_units_tile_the_debug_section(dw):
    offsets = sorted(cu.off for tu in dw.tus for cu in tu.cus)
    assert offsets[0] == 0
    assert len(offsets) == len(set(offsets))
    assert max(offsets) < len(dw.buf)


def test_a_functions_die_can_be_found_by_its_address(dw):
    """The lookup every `.text` localisation depends on: VA -> the function that covers it."""
    geometry = TARGET.geometry_required()
    for tu in dw.tus:
        for cu in tu.cus:
            low = cu.attrs.get(dwarf1.AT_low_pc)
            if cu is tu.decl or low is None:
                continue
            found = dw.func_at(low)
            assert found is not None, f"0x{low:08X} ({tu.name}) has no function DIE"
            assert geometry.loadable_vram <= low < geometry.bss_vram or low >= geometry.bss_vram
            return
    pytest.fail("the binary declares no function compile unit")


def test_names_and_elf_symbols_are_available(dw):
    assert dw.names(), "no type names were indexed"
    assert isinstance(dw.elf_symbols(), dict)
