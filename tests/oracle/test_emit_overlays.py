"""The overlay ledgers's derivation: two files, one identity, and a named stop on disagreement.

`overlays.txt` is not a table somebody typed: it is the join of the ELF's zero-fill ``PT_LOAD``
reservations (where each window loads and how big it is) with the ``DATA*.BIN`` blobs in the
pinned image (where their bytes are, and -- in each blob's own ``MWo3`` header -- which module
it is and how its bytes divide).  The join is ``(vaddr, filesize + bss) == (p_vaddr, p_memsz)``
and it has to be a bijection, so these tests pin the two ways it can fail *and* the committed
artifact against a fresh derivation from the two real files (skipped where they are absent).
"""

import io
import pathlib
import struct
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
sys.path.insert(0, str(ROOT))

import emit_overlays  # noqa: E402
from config import targets  # noqa: E402
from tests import target_support  # noqa: E402

TARGET = target_support.registered()


def blob(name="probe_rel4cd.prg", vaddr=0x00200000, code=0x100, data=0xC0, bss=0x100,
         end=None, magic=b"MWo3", size=None):
    """A synthetic ``MWo3`` blob: the header plus zero-filled code and data."""
    body = targets.OVERLAY_HEADER + code + data
    header = bytearray(targets.OVERLAY_HEADER)
    header[0:4] = magic
    struct.pack_into("<I", header, 4, 1)
    struct.pack_into("<IIIII", header, 8, vaddr, code, data, bss,
                     vaddr + body if end is None else end)
    header[0x20:0x20 + len(name)] = name.encode()
    return bytes(header) + b"\x00" * (body - targets.OVERLAY_HEADER), (body if size is None
                                                                     else size)


def read(data, name="DATA00.BIN", size=None, offset=0x2000):
    """``data`` as a blob at ``offset`` in a padded stand-in image (an image never starts a
    blob at 0: sector 0 is the filesystem's)."""
    stream = io.BytesIO(b"\x00" * offset + data)
    return emit_overlays.read_blob(stream, name, offset,
                                   len(data) if size is None else size)


def test_a_blob_whose_header_adds_up_is_one_row():
    data, size = blob()
    row = read(data, size=size)
    assert row["name"] == "probe_rel4cd" and row["header_name"] == "probe_rel4cd.prg"
    assert (row["vaddr"], row["filesize"], row["code_end"], row["data_size"], row["bss"]) \
        == (0x00200000, size, 0x100, 0xC0, 0x100)


@pytest.mark.parametrize("broken, delta, message", [
    (dict(magic=b"XXXX"), 0, "not an overlay blob"),
    (dict(name="probe_rel4cd"), 0, "ending in"),
    (dict(name="probe/rel4cd.prg"), 0, "not a module identifier"),
    (dict(), 4, "header + "),
    (dict(end=0x00200000), 0, "header says the blob ends"),
])
def test_a_blob_that_disagrees_with_itself_is_a_named_stop(broken, delta, message):
    data, size = blob(**broken)
    with pytest.raises(emit_overlays.OverlayMismatch) as refusal:
        read(data, size=size + delta)
    assert message in str(refusal.value)


def test_a_blob_is_paired_with_its_window_by_address_and_size():
    data, size = blob()
    rows = emit_overlays.pair([read(data, size=size)], [(0x00200000, size + 0x100)])
    assert [row["name"] for row in rows] == ["probe_rel4cd"]


@pytest.mark.parametrize("reservations, message", [
    ([(0x00300000, 0x300)], "reserves no window"),
    ([(0x00200000, 0x300), (0x00200000, 0x300)], "twice"),
    ([(0x00200000, 0x300), (0x00400000, 0x400)], "no blob fills"),
])
def test_a_pairing_that_is_not_a_bijection_is_a_named_stop(reservations, message):
    data, size = blob()
    with pytest.raises(emit_overlays.OverlayMismatch) as refusal:
        emit_overlays.pair([read(data, size=size)], reservations)
    assert message in str(refusal.value)


def test_two_blobs_may_not_claim_one_window():
    first, size = blob()
    second, _ = blob(name="other_rel4cd.prg")
    with pytest.raises(emit_overlays.OverlayMismatch) as refusal:
        emit_overlays.pair([read(first, "DATA00.BIN", size),
                            emit_overlays.read_blob(io.BytesIO(second), "DATA01.BIN", 0,
                                                    len(second))],
                           [(0x00200000, size + 0x100)])
    assert "both claim" in str(refusal.value)


def test_the_rendered_ledger_reads_back_as_the_same_rows(tmp_path):
    data, size = blob()
    rows = emit_overlays.pair([read(data, size=size)], [(0x00200000, size + 0x100)])
    path = tmp_path / "overlays.txt"
    emit_overlays.write(path, rows)
    loaded = targets.load_overlays(path)
    assert [overlay.name for overlay in loaded] == ["probe_rel4cd"]
    assert loaded[0].vaddr == 0x00200000 and loaded[0].memsz == size + 0x100


def test_the_directory_walk_refuses_a_duplicate_name():
    """Two files of one name would make "the blob called DATA03.BIN" ambiguous."""
    with pytest.raises(emit_overlays.OverlayMismatch):
        emit_overlays.iso_root(io.BytesIO(b"\x00" * (emit_overlays.PVD_SECTOR * 2048)))


@pytest.mark.skipif(not TARGET.elf.is_file() or not TARGET.image.is_file(),
                    reason=f"{TARGET.name}: its retail ELF or disc image is not on this host")
def test_the_committed_ledger_is_a_fresh_derivation_from_both_files():
    rows = emit_overlays.derive(TARGET.elf, TARGET.image)
    assert emit_overlays.render(rows) == TARGET.overlays.read_text()
    assert [targets.Overlay(row["name"], row["vaddr"], row["filesize"], row["code_end"],
                            row["data_size"], row["bss"], row["image_offset"])
            for row in rows] == list(TARGET.geometry_required().overlays)
