"""Overlay units in the compiler's manifests: their names, their splits, their references.

Three couplings this pins, all of them measured facts about *this* target's layout:

* an overlay unit's functions are not in ``by_address`` -- the oracle withholds them with the
  reason "outside every declared segment", because seven modules are alternatives at one base
  -- so the name comes from ``unplaced_symbols.txt``'s ``(module, address)`` records and the
  unit's own DWARF overlay name from ``cus.json``;
* the unit's splits are the module's own splat run (``asm/nonmatchings/<overlay>/``) and the
  last one stops at the window's code end, not at the next module's address at the same base;
* a reference *to* an overlay symbol from main-image code resolves to its absolute address,
  because the window loads at a fixed VA and no linker placement is needed for it.

The manifests here are synthetic (a temp config dir and a stub target), so no test reads or
writes the repository's generated ``asm/``.
"""

import json
import pathlib
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

import emit_symbols  # noqa: E402
from config import targets  # noqa: E402
from toolchain import compile as cc  # noqa: E402

#: The module under test: code at 0x200040..0x200140 (0x40 header, 0x100 code), data after.
OVERLAY = targets.Overlay("probe_rel4cd", 0x00200000, 0x200, 0x100, 0xC0, 0x100, 0x1000)
CODE_VRAM = 0x00200040
CODE_END = 0x00200140


def geometry(overlays=(OVERLAY,)):
    return targets.Geometry(
        elf_size=0x2000, loadable_rom=0x80, loadable_end=0x1000, loadable_vram=0x00100000,
        bss_end=0x00110000,
        trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400),
                  ("line", 0x1410, 0x100), ("section_headers", 0x1510, 0x2000 - 0x1510)),
        debug_size=0x400, line_size=0x100, image_elf_offset=0x92000, overlays=overlays)


def cus_records(overlay="probe_rel4cd", functions=((0x00200080, 0x00200090),
                                                   (0x00200090, 0x002000C0))):
    records = [dict(index=0, kind="tu", offset=0, size=0x20, name="probe.c",
                    file="src/probe/ov.c", overlay=overlay, low_pc=None, high_pc=None,
                    stmt_list=None)]
    for number, (low, high) in enumerate(functions, start=1):
        records.append(dict(index=number, kind="function", offset=0x20 * number, size=0x20,
                            name="probe.c", file="src/probe/ov.c", overlay=overlay,
                            low_pc=low, high_pc=high, stmt_list=0))
    return records


def chunks(records=None):
    records = records or cus_records()
    debug = dict(section=".debug", offset=0, size=0x400,
                 tunits=[record["index"] for record in records])
    lines = [dict(section=".line", offset=0x10 * record["index"], size=0x10,
                  tunits=[record["index"]])
             for record in records if record["kind"] == "function"]
    return [debug] + lines


def config(tmp_path, records=None, unplaced=(), splits=(), placed=()):
    records = records or cus_records()
    directory = tmp_path / "config"
    directory.mkdir(parents=True, exist_ok=True)
    (directory / "cus.json").write_text(json.dumps(records))
    (directory / "debug_chunks.json").write_text(json.dumps(chunks(records)))
    (directory / "symbol_addrs.txt").write_text("".join(placed))
    (directory / "unplaced_symbols.txt").write_text("".join(unplaced))
    (directory / "data_placements.txt").write_text("")
    (directory / "unit_symbols.txt").write_text("")
    for name, text in splits:
        path = tmp_path / "asm" / "nonmatchings" / OVERLAY.name / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    target = types.SimpleNamespace(config_dir=directory,
                                   symbols=directory / "symbol_addrs.txt",
                                   geometry=geometry(),
                                   geometry_required=geometry)
    return cc.Manifests(target, root=tmp_path)


def unplaced(name, address, overlay=OVERLAY.name):
    module = f" overlay:{overlay}" if overlay else ""
    return (f"{name} = 0x{address:08X}; // type:func provenance:dwarf "
            f"reason:{emit_symbols.OUTSIDE_REASON}{module}\n")


def split(name, address):
    return (f'.include "macro.inc"\nnonmatching {name}, 0x4\n\nglabel {name}\n'
            f"    /* 0 {address:08X} 00000000 */  nop\n")


# -- names -------------------------------------------------------------------------------


def test_an_overlay_units_functions_resolve_from_its_own_modules_records(tmp_path):
    manifests = config(tmp_path, unplaced=[
        unplaced("probe_first", 0x00200080),
        unplaced("probe_second", 0x00200090),
        # The same address in another module: seven modules share one base, so this is the
        # case an address-keyed lookup gets wrong.
        unplaced("other_first", 0x00200080, overlay="other_rel4cd"),
    ])
    tu = manifests.tu_named("src/probe/ov.c")
    assert tu.overlay == "probe_rel4cd" and tu.is_overlay
    assert [function.name for function in tu.functions] == ["probe_first", "probe_second"]
    assert tu.split_directory == "probe_rel4cd"


def test_a_function_with_no_record_in_its_module_names_the_module(tmp_path):
    manifests = config(tmp_path, unplaced=[unplaced("probe_first", 0x00200080)])
    with pytest.raises(cc.Unusable) as refusal:
        manifests.tu_named("src/probe/ov.c")
    message = str(refusal.value)
    assert "0x00200090" in message and "overlay probe_rel4cd" in message


def test_a_reference_to_an_overlay_symbol_is_its_absolute_address(tmp_path):
    """A main-image unit that calls into an overlay has no section to relocate against: the
    window loads at a fixed VA, so the name resolves to the address itself."""
    manifests = config(tmp_path, unplaced=[
        unplaced("probe_first", 0x00200080),
        unplaced("probe_second", 0x00200090),
    ])
    assert manifests.address_of("probe_first") == 0x00200080
    assert manifests.address_of("probe_second") == 0x00200090
    # Resolving it does not pretend the link places it.
    assert "probe_first" not in manifests.placed


def test_a_withheld_address_no_window_claims_is_still_refused(tmp_path):
    manifests = config(tmp_path, unplaced=[unplaced("probe_gap", 0x00300000)])
    with pytest.raises(cc.Unusable) as refusal:
        manifests.address_of("probe_gap")
    message = str(refusal.value)
    assert "0x00300000" in message and "no overlay window" in message


def test_a_target_with_no_overlay_rows_still_refuses_the_reference(tmp_path):
    """Nothing is resolved by address alone: a geometry that records no windows has no
    evidence where the bytes would be."""
    manifests = config(tmp_path, unplaced=[unplaced("probe_first", 0x00200080)])
    manifests.target.geometry = geometry(overlays=())
    with pytest.raises(cc.Unusable):
        manifests.address_of("probe_first")


# -- splits ------------------------------------------------------------------------------


def test_an_overlay_units_last_split_ends_at_the_windows_code_end(tmp_path):
    manifests = config(tmp_path, unplaced=[
        unplaced("probe_first", 0x00200080), unplaced("probe_second", 0x00200090)],
        splits=[("probe_first.s", split("probe_first", 0x00200080)),
                ("probe_second.s", split("probe_second", 0x00200090))])
    tu = manifests.tu_named("src/probe/ov.c")
    assert cc.split_extent(tu, manifests) == (0x00200080, CODE_END)


def test_the_next_split_bounds_the_extent_and_the_window_clamps_it(tmp_path):
    records = cus_records()
    followed = config(tmp_path, records=records, unplaced=[
        unplaced("probe_first", 0x00200080), unplaced("probe_second", 0x00200090)],
        splits=[("probe_first.s", split("probe_first", 0x00200080)),
                ("probe_second.s", split("probe_second", 0x00200090)),
                ("probe_after.s", split("probe_after", 0x00200100))])
    tu = followed.tu_named("src/probe/ov.c")
    assert cc.split_extent(tu, followed) == (0x00200080, 0x00200100)

    # A split past the code end is another module's address at the same base: the window's
    # measurement wins, so the extent stops at the code end instead of claiming those bytes.
    beyond = config(tmp_path / "beyond", records=records, unplaced=[
        unplaced("probe_first", 0x00200080), unplaced("probe_second", 0x00200090)],
        splits=[("probe_first.s", split("probe_first", 0x00200080)),
                ("probe_second.s", split("probe_second", 0x00200090)),
                ("probe_other_module.s", split("probe_other_module", 0x00200200))])
    tu = beyond.tu_named("src/probe/ov.c")
    assert cc.split_extent(tu, beyond) == (0x00200080, CODE_END)


def test_a_missing_overlay_split_directory_names_it(tmp_path):
    manifests = config(tmp_path, unplaced=[
        unplaced("probe_first", 0x00200080), unplaced("probe_second", 0x00200090)])
    tu = manifests.tu_named("src/probe/ov.c")
    tu.functions = tu.functions[:1]
    with pytest.raises(cc.Unusable) as refusal:
        cc.split_extent(tu, manifests)
    assert "asm/nonmatchings/probe_rel4cd" in str(refusal.value)


def test_a_unit_outside_its_modules_code_is_refused(tmp_path):
    records = cus_records(functions=((0x00200010, 0x00200020),))
    manifests = config(tmp_path, records=records, unplaced=[
        unplaced("probe_first", 0x00200010)],
        splits=[("probe_first.s", split("probe_first", 0x00200010))])
    tu = manifests.tu_named("src/probe/ov.c")
    with pytest.raises(cc.Unusable) as refusal:
        cc.split_extent(tu, manifests)
    assert "not the module its DWARF says" in str(refusal.value)


# -- data: the file that holds a datum's bytes ------------------------------------------


def test_a_datum_is_read_from_the_file_its_address_is_in():
    """A promoted overlay unit's initialised data is a `.datum.*` section of its object, and
    `verify_data` proves it against retail before the link places it.  Which file answers is
    the *address's* answer: inside the unit's module window the bytes are the disc blob's,
    anywhere else (a main-image datum an overlay unit defines -- `infodoll.c`'s `crect` is the
    measured case) they are the ELF's, and the ELF's overlay reservation is zero-fill, so a
    datum must never be compared with the ELF at an overlay address."""
    calls = []

    class Retail:
        def code(self, address, size, overlay=None):
            calls.append((address, size, overlay))
            return bytes(size)

    data_end = OVERLAY.vaddr + OVERLAY.filesize
    cc.retail_datum(Retail(), OVERLAY, CODE_END + 0x10, 0x24)
    cc.retail_datum(Retail(), OVERLAY, 0x00108000, 0x8)
    cc.retail_datum(Retail(), None, 0x00108000, 0x8)
    assert calls == [(CODE_END + 0x10, 0x24, OVERLAY),
                     (0x00108000, 0x8, None),
                     (0x00108000, 0x8, None)]
    # The blob's own end is its last byte, not the window's zero-filled tail.
    assert OVERLAY.filesize < OVERLAY.memsz
    cc.retail_datum(Retail(), OVERLAY, data_end - 0x4, 0x4)
    assert calls[-1] == (data_end - 0x4, 0x4, OVERLAY)
    cc.retail_datum(Retail(), OVERLAY, data_end, 0x4)
    assert calls[-1] == (data_end, 0x4, None), "past the blob it is not the blob's byte"


def test_an_overlay_unit_is_named_by_its_dwarf_records_not_the_ledger():
    """The ledger's spelling is positional (`set_warning_msg_3`, `D_008062B0`); the unit's C,
    its header and its DIEs use the DWARF name, so that is what resolution must return."""
    manifests = cc.Manifests(targets.get())
    try:
        tu = manifests.tu_named("src/network/net_router/net_router_main.c")
    except cc.Unusable as exc:          # manifests absent: nothing to pin here
        pytest.skip(str(exc))
    names = [function.name for function in tu.functions]
    assert "set_warning_msg" in names and "set_warning_msg_3" not in names
    assert "NetRouterMain" in names and "D_008062B0" not in names
