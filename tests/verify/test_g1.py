"""G1 -- the whole-file gate, driven on synthetic images and a synthetic target.

The gate's verdict is a sha256 of two files, so its logic is testable without a retail binary:
identical files pass, a truncated one is reported at the offset where it runs out, and a
divergence inside a chunked section or the loadable image is named by the manifests.  The parts
that need a target's *measurement* -- the section bases, the loadable geometry -- are driven with
a synthetic geometry, and the pin logic with a synthetic ``checksums.txt``: what is under test is
that every input comes from the target, and that an unmeasured target degrades its *diagnostic*
(the localisation) while still answering the verdict.
"""

import dataclasses
import json
import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))       # `config.targets`

from tests import target_support  # noqa: E402
from config import targets  # noqa: E402
from verify import g1, g2  # noqa: E402

TARGET = target_support.registered()

DEBUG_BASE, DEBUG_SIZE = 0x1010, 0x400
LINE_BASE, LINE_SIZE = 0x1410, 0x100
ELF_SIZE = 0x2000
LOADABLE_ROM, LOADABLE_VRAM = 0x80, 0x00100000

GEOMETRY = targets.Geometry(
    elf_size=ELF_SIZE, loadable_rom=LOADABLE_ROM, loadable_end=0x1000,
    loadable_vram=LOADABLE_VRAM, bss_end=0x00110000,
    trailing=(("shstrtab", 0x1000, 0x10), ("debug", DEBUG_BASE, DEBUG_SIZE),
              ("line", LINE_BASE, LINE_SIZE),
              ("section_headers", 0x1510, ELF_SIZE - 0x1510)),
    debug_size=DEBUG_SIZE, line_size=LINE_SIZE, image_elf_offset=0x92000)


@pytest.fixture
def manifests(tmp_path):
    """A CU map and chunk manifest for the synthetic geometry: one TU, one function."""
    cus = [
        dict(index=0, kind="tu", offset=0, size=0x200, name="probe.c", file="src/probe.c",
             low_pc=None, high_pc=None, stmt_list=None),
        dict(index=1, kind="function", offset=0x200, size=DEBUG_SIZE - 0x200, name="probe_fn",
             file="src/probe.c", low_pc=LOADABLE_VRAM, high_pc=LOADABLE_VRAM + 0x10,
             stmt_list=0),
    ]
    chunks = [dict(section=".debug", offset=0, size=DEBUG_SIZE, tunits=[0, 1]),
              dict(section=".line", offset=0, size=LINE_SIZE, tunits=[1])]
    cus_path, chunks_path = tmp_path / "cus.json", tmp_path / "debug_chunks.json"
    cus_path.write_text(json.dumps(cus))
    chunks_path.write_text(json.dumps(chunks))
    return cus_path, chunks_path


def image(tmp_path, name="built", size=ELF_SIZE, pattern=b"\x3D"):
    path = tmp_path / name
    path.write_bytes(pattern * size)
    return path


def corrupted(tmp_path, source, offset, name="bad"):
    data = bytearray(source.read_bytes())
    data[offset] ^= 0xFF
    path = tmp_path / name
    path.write_bytes(bytes(data))
    return path


def test_identical_images_compare_ok(tmp_path):
    built, retail = image(tmp_path, "built"), image(tmp_path, "retail")
    assert g1.compare(built, retail) == "ok"
    assert g1.sha256(built) == g1.sha256(retail)


def test_a_truncated_image_is_reported_at_its_end(tmp_path):
    retail = image(tmp_path)
    bad = tmp_path / "short"
    bad.write_bytes(retail.read_bytes()[:1000])
    message = g1.compare(bad, retail)
    assert message.startswith("sha256 mismatch") and "0x3E8" in message
    assert g1.sha256(bad) in message and g1.sha256(retail) in message


def test_a_mismatch_says_the_byte_is_not_localised_while_the_geometry_is_unmeasured(
        tmp_path, monkeypatch):
    """The verdict never needs a measurement; the *diagnostic* does, and says so out loud."""
    retail = image(tmp_path)
    bad = corrupted(tmp_path, retail, 0x80 + 4)
    monkeypatch.setattr(g1, "TARGET", target_support.unmeasured(targets.get()))
    message = g1.compare(bad, retail)
    assert "0x84" in message and "not localised" in message


def test_g1_does_not_guess_a_translation_unit_for_a_code_byte(tmp_path, manifests):
    """G1 localises the chunked sections only; a code byte has no chunk manifest at all, and
    inventing one would be a second, weaker opinion about the same offset (R32)."""
    cus_path, chunks_path = manifests
    retail = image(tmp_path)
    message = g1.compare(corrupted(tmp_path, retail, LOADABLE_ROM + 4), retail,
                         cus_path, chunks_path, GEOMETRY)
    assert "0x84" in message and "src/probe.c" not in message


def test_a_loadable_byte_is_localised_by_the_address_it_maps_to(tmp_path, manifests):
    """The .text half is G2's: the file offset becomes a VA through the target's geometry, and
    the DWARF function CU covering that address names the unit."""
    cus_path, chunks_path = manifests
    symbols_path = tmp_path / "symbol_addrs.txt"
    symbols_path.write_text("probe_fn = 0x00100000;  // type:func size:0x10 dwarf:dwarf\n")
    retail = image(tmp_path)
    located = g2.localise(corrupted(tmp_path, retail, LOADABLE_ROM + 4), retail,
                          cus_path, chunks_path, symbols_path, GEOMETRY)
    assert located["section"] == ".text" and located["offset"] == LOADABLE_ROM + 4
    assert located["tu"] == "src/probe.c" and located["function"] == "probe_fn"
    assert g2.localise(retail, retail) is None


def test_a_debug_byte_names_its_translation_unit(tmp_path, manifests):
    cus_path, chunks_path = manifests
    retail = image(tmp_path)
    message = g1.compare(corrupted(tmp_path, retail, DEBUG_BASE + 4), retail,
                         cus_path, chunks_path, GEOMETRY)
    assert f"0x{DEBUG_BASE + 4:X}" in message and ".debug" in message
    assert "src/probe.c" in message and "compile unit 0 (" in message


def test_the_pin_comes_from_the_targets_own_checksum_manifest(tmp_path):
    """The manifest is read by path, so a target's pin can never be another target's."""
    elf_sha = "ef31c90f321328906c51144152d68676975b52cf157b3adb65aa1969a97c02cd"
    image_sha = "70a9056657665e978c7de9fc223cb753956902416418993176438316f6cd652b"
    manifest = tmp_path / "checksums.txt"
    manifest.write_text(f"{elf_sha}  out/SLUS_211.74\n{image_sha}  disc/probe.iso\n")
    assert g1.pinned_hash(manifest) == elf_sha
    assert g1.pinned_hash_for("probe.iso", manifest) == image_sha
    assert g1.pinned_hash_for("no-such-image.iso", manifest) is None
    missing = tmp_path / "absent.txt"
    assert g1._pins(missing) == [] and g1.pinned_hash(missing) is None
    # ... and the registered target's own manifest resolves its own two files, read by the
    # target's own path -- the same digests the descriptor carries, so the pin the gates check
    # and the pin the descriptor records cannot drift apart.
    target = targets.get()
    assert g1.pinned_hash(target.checksums) == target.elf_sha256
    assert g1.pinned_hash_for(target.image, target.checksums) == target.image_sha256


def test_the_cli_needs_the_targets_retail_binary(tmp_path, capsys, monkeypatch):
    """No retail binary, no verdict: G1 compares against *that file* or it says which is missing."""
    built = image(tmp_path, "built")
    real = targets.get()
    absent = tmp_path / "absent.elf"
    monkeypatch.setattr(g1.targets, "get",
                        lambda name=None: dataclasses.replace(real, elf=absent))
    assert g1.main([str(built)]) == 2
    err = capsys.readouterr().err
    assert str(absent) in err and "required" in err


def test_the_cli_reports_a_mismatch_against_an_explicit_retail_binary(tmp_path, capsys):
    built, retail = image(tmp_path, "built"), image(tmp_path, "retail", pattern=b"\x2E")
    # The manifest pins the *reference*, so the pin check passes and the gate gets to compare:
    # what is under test here is the mismatch report, not the pin.
    manifest = tmp_path / "checksums.txt"
    manifest.write_text(f"{g1.sha256(retail)}  retail\n")
    status = g1.main([str(built), "--retail", str(retail), "--checksums", str(manifest)])
    out = capsys.readouterr().out
    assert status == 1
    assert "sha256 mismatch" in out and g1.sha256(retail) in out


def test_the_cli_rejects_an_unknown_target(tmp_path, capsys):
    built = image(tmp_path)
    assert g1.main([str(built), "--target", "usam2"]) == 2
    err = capsys.readouterr().err
    assert "usam2" in err and targets.DEFAULT in err and "Traceback" not in err


def test_the_cli_refuses_a_retail_binary_that_is_not_the_pinned_one(tmp_path, capsys):
    """A self-consistent pair is not a green G1: the pin is checked *before* the comparison.

    The manifest is the target's own (the two digests its descriptor carries), and the impostor is
    a file that merely sits where a retail binary would: the gate must answer "this is not the
    binary" -- with both digests -- rather than compare two files that agree with each other.
    """
    if not TARGET.checksums.is_file():
        pytest.skip(f"{TARGET.name}: its checksums.txt is generated in Task 4")
    built = image(tmp_path, "built")
    impostor = tmp_path / "impostor"
    impostor.write_bytes(b"\x7fELF" + bytes(range(60)))
    status = g1.main([str(built), "--retail", str(impostor)])
    err = capsys.readouterr().err
    assert status == 1
    assert TARGET.elf_sha256 in err and g1.sha256(impostor) in err, err
    assert "G1" not in err or "pinned" in err


def test_the_cli_honours_an_explicit_expectation(tmp_path, capsys):
    """``--expected`` is the same pin, named on the command line instead of read from the file."""
    built, retail = image(tmp_path, "built"), image(tmp_path, "retail")
    status = g1.main([str(built), "--retail", str(retail), "--expected", "0" * 64])
    err = capsys.readouterr().err
    assert status == 1 and "0" * 64 in err and "different version" in err


def test_the_cli_reports_ok_for_two_identical_files(tmp_path, capsys):
    """G1's green path: the exit-0 branch, with no pin in play (`--checksums` names an absent
    manifest, so the comparison itself is what the verdict rests on)."""
    built, retail = image(tmp_path, "built"), image(tmp_path, "retail")
    status = g1.main([str(built), "--retail", str(retail),
                      "--checksums", str(tmp_path / "absent.txt")])
    out = capsys.readouterr().out
    assert status == 0
    assert out.startswith("ok: ") and g1.sha256(built) in out
