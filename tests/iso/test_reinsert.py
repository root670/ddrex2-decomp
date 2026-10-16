"""G3 -- the disc-image gate: ``out/SLUS_207.11`` spliced back into the retail image at
``0x92000`` must give the retail image back, sha256 for sha256.

The rebuilt image is ~1.24 GB, so it is written once, to the gitignored ``out/rebuilt.iso``,
and only ever hashed streaming (R30).  The retail image sits on a read-only mount and is
read, never written; both image tests skip when that mount is absent, because the gate's
evidence comes from the run where it is present.  The synthetic tests below exercise the
same code paths on small files, so a broken tool still fails loudly without the mount.
"""

import pathlib
import sys

import pytest

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT))  # `config.targets`

from config import targets  # noqa: E402
from iso import reinsert  # noqa: E402  (path set up above, as the brief specifies)

IMAGE = pathlib.Path("/Volumes/My Passport/PS2 Games/DDRMAX2 Dance Dance Revolution (USA).iso")
SHA = "b8519c9106b43cc83bc57948cbc02a83851d3182fcbd4e7d341c573758bb3ec8"
BUILT = ROOT / "out/SLUS_207.11"
REBUILT = ROOT / "out/rebuilt.iso"   # gitignored: 1.24 GB, never pytest's tmp (R30)


@pytest.fixture(scope="session")
def rebuilt():
    """The one rebuild the session needs, spliced once instead of per test."""
    if not IMAGE.exists():
        pytest.skip("retail image not available")
    reinsert.build(IMAGE, BUILT, REBUILT)
    return REBUILT


def test_elf_lands_at_the_right_offset():
    if not IMAGE.exists():
        pytest.skip("retail image not available")
    head = reinsert.read(IMAGE, 0x92000, 8)
    assert head[:4] == b"\x7fELF"


def test_reinsertion_reproduces_the_image(rebuilt):
    assert reinsert.verify(rebuilt, SHA) == "ok"
    assert reinsert.sha256(rebuilt) == SHA


def test_the_rebuilt_image_carries_the_built_elf(rebuilt):
    """The copy's ELF region, not just its hash: the image's bytes there must be ours."""
    assert reinsert.read(rebuilt, reinsert.ELF_OFFSET, BUILT.stat().st_size) == \
        BUILT.read_bytes()


def test_build_touches_only_the_elf_region(tmp_path):
    """Everything outside the splice -- including the image's length -- is untouched."""
    image = tmp_path / "image.iso"
    image.write_bytes(b"\x3D" * 4096)
    elf = tmp_path / "SLUS_207.11"
    elf.write_bytes(b"\x7fELF" + bytes(range(60)))
    out = tmp_path / "rebuilt.iso"

    reinsert.build(image, elf, out, offset=0x100)

    assert out.stat().st_size == 4096
    assert reinsert.read(out, 0x100, 64) == elf.read_bytes()
    assert reinsert.read(out, 0, 0x100) == b"\x3D" * 0x100
    assert reinsert.read(out, 0x140, 4096 - 0x140) == b"\x3D" * (4096 - 0x140)


def test_build_refuses_an_elf_that_runs_past_the_end(tmp_path):
    """A splice that does not fit would grow the image and break byte-identity."""
    image = tmp_path / "image.iso"
    image.write_bytes(b"\x3D" * 512)
    elf = tmp_path / "SLUS_207.11"
    elf.write_bytes(b"\x7fELF" * 128)   # 512 bytes, spliced at 0x100 -> 0x300 > 0x200

    with pytest.raises(ValueError, match="does not fit"):
        reinsert.build(image, elf, tmp_path / "rebuilt.iso", offset=0x100)


def test_build_refuses_to_overwrite_the_image(tmp_path):
    """The retail image is the only copy of the disc: in-place splicing is not offered.

    The splice has to fit (``0x100`` + 4 bytes in 512), or the bounds check would be the
    guard under test and deleting this one would keep the suite green.
    """
    image = tmp_path / "image.iso"
    image.write_bytes(b"\x3D" * 512)
    elf = tmp_path / "SLUS_207.11"
    elf.write_bytes(b"\x7fELF")

    with pytest.raises(ValueError, match="refusing to splice the image into itself"):
        reinsert.build(image, elf, image, offset=0x100)


def test_verify_names_both_hashes_and_the_first_offset(tmp_path):
    """A wrong image must be reportable: which two digests, and where they diverge."""
    reference = tmp_path / "image.iso"
    reference.write_bytes(bytes(range(256)) * 4)
    data = bytearray(reference.read_bytes())
    data[0x180] ^= 0x01
    mutated = tmp_path / "mutated.iso"
    mutated.write_bytes(bytes(data))

    message = reinsert.verify(mutated, SHA, reference=reference)

    assert reinsert.sha256(mutated) in message and SHA in message, message
    assert "0x180" in message, message


def test_verify_diagnoses_against_the_retail_image_by_default():
    """The two-argument form is the gate's: the default reference is the retail image."""
    if not IMAGE.exists():
        pytest.skip("retail image not available")
    assert reinsert.RETAIL_IMAGE == IMAGE

    message = reinsert.verify(BUILT, SHA)   # the ELF is not the image: 0x0 already differs

    assert reinsert.sha256(BUILT) in message and SHA in message, message
    assert f"first difference against {IMAGE} at 0x0" in message, message


def test_verify_without_a_reference_to_compare_against_still_names_the_two_hashes(
        tmp_path, monkeypatch):
    """The hash is the gate; the offset is the diagnosis, and an unmounted image only
    costs the diagnosis."""
    bad = tmp_path / "rebuilt.iso"
    bad.write_bytes(b"not an image")
    monkeypatch.setattr(reinsert, "RETAIL_IMAGE", tmp_path / "absent.iso")

    message = reinsert.verify(bad, SHA)     # the default reference, which is not mounted

    assert reinsert.sha256(bad) in message and SHA in message, message
    assert "no reference image" in message, message


def test_verify_reports_ok_for_a_matching_hash(tmp_path):
    good = tmp_path / "rebuilt.iso"
    good.write_bytes(b"\x3D" * 512)
    assert reinsert.verify(good, reinsert.sha256(good)) == "ok"


# ---------------------------------------------------------------------------
# --target: the image, its offset and its pin are the target's
# ---------------------------------------------------------------------------


@pytest.mark.parametrize("name", targets.names())
def test_each_targets_image_offset_and_pin_are_its_own(name):
    """Bare ``--iso`` means the *target's* mounted image, at the *target's* offset.

    The two current targets share neither the image nor the pin, and the retarget's offset
    is deliberately not measured yet: asking for it raises rather than splicing the new
    build into the old disc's geometry.
    """
    target = targets.get(name)
    other = targets.get("ddrex2p" if name == targets.DEFAULT else targets.DEFAULT)
    assert reinsert.retail_image(target) == target.image
    assert reinsert.retail_image(target) != reinsert.retail_image(other)
    if target.geometry is None:
        with pytest.raises(targets.NotMeasured):
            reinsert.elf_offset(target)
    else:
        assert reinsert.elf_offset(target) == target.geometry.image_elf_offset


def test_the_default_targets_offset_is_the_mounted_images_boot_elf():
    """The value the whole G3 ladder was built on, now read from the descriptor."""
    assert reinsert.ELF_OFFSET == targets.get(targets.DEFAULT).geometry.image_elf_offset
    assert reinsert.ELF_OFFSET == 0x92000
