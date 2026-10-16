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
    """The lookup every `.text` localisation depends on: VA -> the function DIE that covers it.

    The function's code must lie in the loadable image (the segment the split places code in):
    a VA outside it would mean the reader and the descriptor disagree about the binary.
    """
    geometry = TARGET.geometry_required()
    found = None
    for tu in dw.tus:
        for cu in tu.cus:
            low = cu.attrs.get(dwarf1.AT_low_pc)
            if cu is tu.decl or low is None:
                continue
            assert geometry.loadable_vram <= low < geometry.loadable_end, \
                f"0x{low:08X} ({tu.name}) is outside the loadable image"
            found = (dw.func_at(low), low, tu)
            break
        if found:
            break
    assert found is not None, "the binary declares no function compile unit"
    dies, low, tu = found
    assert dies, f"0x{low:08X} ({tu.name}) has no function DIE"
    assert dies[0].off >= 0, "the DIE has no offset into the section it was parsed from"
    assert dw.cus_at(low) is not None, "the function's own address must resolve to a CU"


def test_names_and_elf_symbols_are_available(dw):
    names = dw.names()
    assert names, "no type names were indexed"
    assert all(isinstance(name, str) and name for name in list(names)[:16])

    # The reader offers the ELF's own symbol table when there is one; this deployment binary's
    # names come from its DWARF (`.symtab` is stripped), so what is asserted is the shape of what
    # it does return, and that a name is only ever at an address.
    symbols = dw.elf_symbols()
    assert isinstance(symbols, dict)
    for address, name in list(symbols.items())[:16]:
        assert isinstance(address, int) and address >= 0
        assert isinstance(name, str) and name


# ---------------------------------------------------------------------------
# the main image's boundary: measured from the file, never a literal
# ---------------------------------------------------------------------------


def test_the_main_image_is_the_files_own_file_backed_program_headers(dw):
    """The reader's main/overlay boundary is the ELF's own measurement.

    It was the literal ``0x400800`` -- the boundary of the binary this reader was vendored
    against -- so a second target inherited that game's address space: every global this
    binary keeps above ``0x400800`` was homed in whichever overlay declared it, and one
    global declared by several overlays became several records at one address.
    """
    mapped = tuple((segment.vaddr, segment.vaddr + segment.memsz)
                   for segment in dw.elf.segments
                   if segment.type == 1 and segment.filesz > 0)
    assert mapped, "this ELF maps a main image from the file"
    assert dw.main_spans == mapped
    # A zero-fill reservation maps no bytes, so it is *not* main: this target has eleven of
    # them (the deferred overlays), and calling them main would place nothing anywhere.
    for segment in dw.elf.segments:
        if segment.type == 1 and not segment.filesz:
            assert not any(lo <= segment.vaddr < hi for lo, hi in dw.main_spans)


def test_no_address_the_dwarf_never_gave_is_in_main(dw):
    """``None`` and 0 mean "no location", which is not an address in main.

    Those are this binary's 136 objects whose ``DW_AT_location`` is ``DW_OP_addr 0``: homing
    them in main would put a record at address 0 into the ledger's placed set.
    """
    assert not dw.in_main_image(None)
    assert not dw.in_main_image(0)


def test_a_main_image_global_is_one_record_however_many_overlays_declare_it(dw):
    """Several overlays declare the same main-image global, and it is one variable.

    With the literal boundary, four such globals in this binary's bss (``tex_bind``,
    ``g_game_w``, ``g_sys_w``, ``workout_work``) came out as 16 records at 4 addresses --
    12 more than the split can hold, because splat refuses two symbols at one address.
    """
    globals_ = dw.globals(None)
    inside = [g["addr"] for g in globals_.values() if dw.in_main_image(g["addr"])]
    assert inside, "this binary has globals in its main image"
    assert len(inside) == len(set(inside)), "one record per address in the main image"
    homes = {key[2] for key, g in globals_.items() if dw.in_main_image(g["addr"])}
    assert homes == {"main"}, f"an address in main was homed elsewhere: {homes}"
