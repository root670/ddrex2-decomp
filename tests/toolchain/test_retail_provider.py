"""The retail provider: which file a unit's bytes come from, and what it refuses.

``Elf.read`` answers zeros at every zero-fill ``PT_LOAD`` -- the bss tail and all ten overlay
reservations -- so a comparison built on it reports agreement with an empty buffer.  The
provider is the one place that decides the file instead: the ELF's file-backed image for a
main unit, the disc image's blob for an overlay unit, and the ELF's chunked sections for
``.debug``/``.line`` either way.

The ELF here is synthetic (``tests/target_support.write_elf``), so these tests pin the reads
and the refusals without a retail binary.
"""

import pathlib
import sys
import types

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

from config import targets  # noqa: E402
from tests import target_support  # noqa: E402
from toolchain.retail import Retail  # noqa: E402

#: Where the synthetic blob lives in the synthetic image, and how the row describes it.
IMAGE_OFFSET = 0x1000
OVERLAY = targets.Overlay("probe_rel4cd", 0x00200000, 0x200, 0x100, 0xC0, 0x100, IMAGE_OFFSET)
CODE = bytes((index * 7) & 0xFF for index in range(0x100))
BLOB = b"\x00" * targets.OVERLAY_HEADER + CODE + b"\xAA" * 0xC0
TEXT = bytes(range(0x40))          # the synthetic ELF's file-backed image at 0x00100000


def geometry():
    return targets.Geometry(
        elf_size=0x2000, loadable_rom=0x80, loadable_end=0x1000, loadable_vram=0x00100000,
        bss_end=0x00110000,
        trailing=(("shstrtab", 0x1000, 0x10), ("debug", 0x1010, 0x400),
                  ("line", 0x1410, 0x100), ("section_headers", 0x1510, 0x2000 - 0x1510)),
        debug_size=0x400, line_size=0x100, image_elf_offset=0x92000,
        overlays=(OVERLAY,))


def unit(address, end, overlay="main"):
    """What ``Retail`` reads off a unit: its span and the module it loads in."""
    return types.SimpleNamespace(address=address, end=end, overlay=overlay)


@pytest.fixture
def world(tmp_path):
    elf = tmp_path / "retail.elf"
    target_support.write_elf(elf, segments=[(0x00100000, 0x80, TEXT)],
                             sections=[(".debug", b"D" * 0x400), (".line", b"L" * 0x100)])
    image = tmp_path / "disc.iso"
    image.write_bytes(b"\x00" * IMAGE_OFFSET + BLOB)
    target = types.SimpleNamespace(elf=elf, image=image, name="probe",
                                   geometry_required=geometry)
    return Retail(target)


def test_a_main_units_text_is_the_elfs_file_backed_bytes(world):
    text = world.text(unit(0x00100010, 0x00100020))
    assert text == TEXT[0x10:0x20]
    assert text != bytes(0x10), "the ELF answers with bytes, not the bss zeros"


def test_a_main_read_past_the_file_backed_image_is_refused(world):
    """``0x00100040..0x00100080`` is inside ``p_memsz`` and outside ``p_filesz``: zeros, if
    the reader were allowed to answer -- which is the evidence that made a mismatch read as a
    match."""
    with pytest.raises(targets.OutsideLoadableImage) as refusal:
        world.text(unit(0x00100040, 0x00100048))
    assert "0x00100040" in str(refusal.value) and "0x00100F80" in str(refusal.value)


def test_an_overlay_units_text_is_the_image_at_image_offset_plus_the_delta(world):
    text = world.text(unit(0x00200050, 0x00200058, "probe_rel4cd"))
    assert text == BLOB[0x50:0x58]
    assert text == CODE[0x10:0x18]
    # The formula, spelled out: image_offset + (VA - vaddr) is where the byte is.
    assert world.code(0x00200041, 1, OVERLAY) == BLOB[0x41:0x42]


def test_an_overlay_name_the_geometry_does_not_record_is_refused(world):
    with pytest.raises(KeyError) as refusal:
        world.text(unit(0x00200050, 0x00200058, "not_a_module"))
    assert "not_a_module" in str(refusal.value)


def test_an_overlay_address_on_a_main_unit_is_still_refused(world):
    """A unit whose own record says ``main`` cannot be rescued by the address being in a
    window: the window is evidence about a *module*, and the unit says it is not in one."""
    with pytest.raises(targets.OutsideLoadableImage):
        world.text(unit(0x00200050, 0x00200058))


def test_an_overlay_read_past_the_blob_is_refused(world):
    with pytest.raises(targets.OutsideLoadableImage) as refusal:
        world.code(0x002001F0, 0x20, OVERLAY)
    assert "probe_rel4cd" in str(refusal.value)


def test_the_chunked_sections_stay_on_the_elf(world):
    chunk = world.section(types.SimpleNamespace(debug_offset=0x10, debug_size=4,
                                                line_offset=0x20, line_size=8), ".debug")
    assert chunk == b"D" * 4
    line = world.section(types.SimpleNamespace(debug_offset=0x10, debug_size=4,
                                               line_offset=0x20, line_size=8), ".line")
    assert line == b"L" * 8


def test_a_missing_image_is_named_only_when_an_overlay_needs_it(world):
    world.image_path.unlink()
    assert world.text(unit(0x00100010, 0x00100020)) == TEXT[0x10:0x20]
    with pytest.raises(FileNotFoundError) as refusal:
        world.text(unit(0x00200050, 0x00200058, "probe_rel4cd"))
    assert "disc.iso" in str(refusal.value) and "overlay" in str(refusal.value)
