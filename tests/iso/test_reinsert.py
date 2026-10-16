"""G3 -- the splice itself, and the target it takes its image and offset from.

Reinsertion is one ``write`` into a copy plus a hash, so the mechanism is testable on small
synthetic files: everything outside the splice must be untouched, an ELF that does not fit or a
request to splice the image into itself must raise, and a mismatch must name both digests and the
first byte that differs.  The target-specific half -- which image a bare ``--iso`` means, and at
which offset the boot ELF sits -- is asserted through the descriptor, and an unmeasured target
must raise rather than splice at a guess.
"""

import dataclasses
import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))  # `config.targets`

from config import targets  # noqa: E402
from iso import reinsert  # noqa: E402
from verify import g1  # noqa: E402

#: The fixture's own layout: the splice offset these tests exercise.  The offset a *target* uses
#: is a measurement of its disc image (`reinsert.elf_offset(<target>)`), not a constant here.
AT = 0x100


def test_build_touches_only_the_elf_region(tmp_path):
    image = tmp_path / "image.iso"
    image.write_bytes(b"\x3D" * 4096)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    out = tmp_path / "rebuilt.iso"

    reinsert.build(image, elf, out, offset=AT)

    assert out.stat().st_size == 4096
    assert reinsert.read(out, AT, 64) == elf.read_bytes()
    assert reinsert.read(out, 0, AT) == b"\x3D" * AT
    assert reinsert.read(out, AT + 64, 4096 - AT - 64) == b"\x3D" * (4096 - AT - 64)


def test_build_refuses_an_elf_that_runs_past_the_end(tmp_path):
    """A splice that does not fit would grow the image and break byte-identity."""
    image = tmp_path / "image.iso"
    image.write_bytes(b"\x3D" * 512)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF" * 128)   # 512 bytes, spliced at 0x100 -> 0x300 > 0x200
    with pytest.raises(ValueError, match="does not fit"):
        reinsert.build(image, elf, tmp_path / "rebuilt.iso", offset=AT)


def test_build_refuses_to_overwrite_the_image(tmp_path):
    """The retail image is the only copy of the disc: in-place splicing is not offered."""
    image = tmp_path / "image.iso"
    image.write_bytes(b"\x3D" * 512)
    elf = tmp_path / "stamp.elf"
    elf.write_bytes(b"\x7fELF")
    with pytest.raises(ValueError, match="refusing to splice the image into itself"):
        reinsert.build(image, elf, image, offset=AT)


def test_verify_names_both_hashes_and_the_first_offset(tmp_path):
    """A wrong image must be reportable: which two digests, and where they diverge."""
    reference = tmp_path / "image.iso"
    reference.write_bytes(bytes(range(256)) * 4)
    data = bytearray(reference.read_bytes())
    data[0x180] ^= 0x01
    mutated = tmp_path / "mutated.iso"
    mutated.write_bytes(bytes(data))
    expected = reinsert.sha256(reference)

    message = reinsert.verify(mutated, expected, reference=reference)

    assert reinsert.sha256(mutated) in message and expected in message, message
    assert "0x180" in message, message


def test_verify_without_a_reference_to_compare_against_still_names_the_two_hashes(
        tmp_path, monkeypatch):
    """The hash is the gate; the offset is the diagnosis, and an unmounted image only costs the
    diagnosis."""
    bad = tmp_path / "rebuilt.iso"
    bad.write_bytes(b"not an image")
    monkeypatch.setattr(reinsert, "RETAIL_IMAGE", tmp_path / "absent.iso")
    message = reinsert.verify(bad, "0" * 64)
    assert reinsert.sha256(bad) in message and "0" * 64 in message, message
    assert "no reference image" in message, message


def test_verify_reports_ok_for_a_matching_hash(tmp_path):
    good = tmp_path / "rebuilt.iso"
    good.write_bytes(b"\x3D" * 512)
    assert reinsert.verify(good, reinsert.sha256(good)) == "ok"


# ---------------------------------------------------------------------------
# the target: its image, its offset, its pin
# ---------------------------------------------------------------------------


def test_a_bare_iso_means_the_targets_own_image():
    target = targets.get()
    assert reinsert.retail_image(target) == target.image
    assert reinsert.retail_image() == reinsert.RETAIL_IMAGE == targets.get().image
    assert reinsert.BUILT_ELF == target.built  # out/<the target's ELF name>


def test_the_targets_offset_is_a_measurement_not_a_constant(monkeypatch):
    """The splice offset is the target's own; a target nobody has measured raises.

    A default argument would have made this an *import-time* failure for every tool that reads
    this module, so `build()` resolves it when it is called.
    """
    unmeasured = dataclasses.replace(targets.get(), geometry=None)
    with pytest.raises(targets.NotMeasured):
        reinsert.elf_offset(unmeasured)
    monkeypatch.setattr(reinsert, "TARGET", unmeasured)
    with pytest.raises(targets.NotMeasured):
        reinsert.build(__file__, __file__, "/tmp/unused.iso")


# ---------------------------------------------------------------------------
# G3 on the registered target's own disc: the measurement, and the pin
#
# The splice itself is the *gate's* run -- `./ddr iso` writes the 1.84 GB copy to the
# gitignored out/rebuilt.iso and hashes it -- and the suite deliberately does not repeat it:
# a write into any generated tree fails tests/conftest.py's backstop (`out/` is where a build
# happens), and R30 says the copy is never a temporary directory either.  What is the suite's
# to pin, read-only, is the measurement that splice depends on: a wrong offset or a wrong pin
# would make that 1.84 GB comparison compare the wrong pair, and both are one read away from
# being checked.  The previous target's suite carried the same three checks, and these skip --
# never fail -- when the disc is not mounted, because the gate's evidence comes from the run
# where it is.
# ---------------------------------------------------------------------------

TARGET = targets.get()


def _mounted_or_skip():
    """The target's image, or a skip: the disc is mounted wherever its owner keeps it.

    The retail ELF is checked too -- it is gitignored, like the image, so a machine can lack
    either -- and both are *read* here, never written.
    """
    if not TARGET.image.is_file():
        pytest.skip(f"{TARGET.name}: its disc image is not mounted ({TARGET.image.name})")
    if not TARGET.elf.is_file():
        pytest.skip(f"{TARGET.name}: {TARGET.elf.name} is not present (orig/ is gitignored)")
    return TARGET.image


def test_the_boot_elf_is_where_the_descriptors_geometry_puts_it():
    """The bytes at the measured offset are the retail ELF itself: the offset is the image's.

    Splice *anywhere* else and the copy would carry the build's bytes where some other file's
    are, which no digest would report as anything but "the rebuild differs from the disc".
    """
    image = _mounted_or_skip()
    offset = reinsert.elf_offset(TARGET)
    retail = TARGET.elf.read_bytes()
    assert offset % 2048 == 0, "a plain 2048-byte ISO puts the boot ELF on a sector boundary"
    assert reinsert.read(image, offset, len(retail)) == retail


def test_the_extent_after_the_elf_is_zero_padding_and_then_the_image_goes_on():
    """The ELF ends 20 bytes inside its last sector; past that the image carries other data.

    So the copy's ELF region is the ELF's own 7,725,036 bytes -- the premise of G3 being one
    hash: ``build`` truncates the copy at the image's length and writes exactly the ELF (the
    synthetic test above asserts both sides of the region on a fixture image).
    """
    image = _mounted_or_skip()
    end = reinsert.elf_offset(TARGET) + TARGET.elf.stat().st_size
    assert end < image.stat().st_size
    assert reinsert.read(image, end, 20) == b"\x00" * 20, "zero padding to the sector's end"
    assert reinsert.read(image, end + 20, 4096) != b"\x00" * 4096, (
        "past the padding the image carries the next file's data: the extent is the ELF's")


def test_g3s_criterion_is_the_digest_the_targets_manifest_records_for_the_image():
    """The pin is resolved the way the gate resolves it: by file name in ``checksums.txt``."""
    pinned = g1.pinned_hash_for(TARGET.image.name, TARGET.checksums)
    assert pinned == TARGET.image_sha256
    assert pinned != TARGET.elf_sha256, "the two pins are different files: they cannot coincide"
    assert g1.pinned_hash_for("no-such-image.iso", TARGET.checksums) is None


def test_verify_diagnoses_against_the_targets_image_by_default():
    """The two-argument form is the gate's: the default reference is the target's image.

    A file that is not the image -- the ELF, 7.7 MB against 1.84 GB -- already differs at 0x0,
    and naming that offset is the whole of the diagnosis an unmounted reference costs.
    """
    image = _mounted_or_skip()
    assert reinsert.retail_image(TARGET) == reinsert.RETAIL_IMAGE == image
    message = reinsert.verify(TARGET.elf, TARGET.image_sha256)
    assert reinsert.sha256(TARGET.elf) in message and TARGET.image_sha256 in message
    assert f"first difference against {image} at 0x0" in message, message
