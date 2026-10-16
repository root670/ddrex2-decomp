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
