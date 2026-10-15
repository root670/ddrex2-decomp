"""G1 -- the whole-file gate: the built image must equal the retail one, byte for byte.

The gate is the milestone's acceptance criterion, so it is tested against the real
retail binary (the pinned hash) and against the two ways it can go wrong that matter:
a truncated image, and a single corrupted byte -- which must be reported with its file
offset *and* the translation unit that owns it, read out of the oracle's manifests.
"""

import json
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from verify import g1  # noqa: E402  (path set up above, as the brief specifies)

RETAIL = ROOT / "orig/SLUS_207.11"
SHA = "a7596e8ab3da823236ed8e5f3f2804db3daee47265ae73e22f3311a5218aa8cc"
# The two chunked sections' retail file offsets; the same geometry configure.py pins.
DEBUG = 0x1A2740
LINE = 0x2430E0


def load(name):
    return json.loads((ROOT / "config/usam2" / name).read_text())


def corrupted(tmp_path, offset, name="SLUS_207.11"):
    """A copy of the retail image with one byte at ``offset`` flipped."""
    data = bytearray(RETAIL.read_bytes())
    data[offset] ^= 0xFF
    path = tmp_path / name
    path.write_bytes(bytes(data))
    return path


def test_retail_hash_is_pinned():
    assert g1.sha256(RETAIL) == SHA


def test_truncated_copy_is_rejected(tmp_path):
    bad = tmp_path / "SLUS_207.11"
    bad.write_bytes(RETAIL.read_bytes()[:1000])
    msg = g1.compare(bad, RETAIL)
    assert msg.startswith("sha256 mismatch") and "0x" in msg


def test_identical_copies_compare_ok(tmp_path):
    same = tmp_path / "SLUS_207.11"
    same.write_bytes(RETAIL.read_bytes())
    assert g1.compare(same, RETAIL) == "ok"


def test_a_truncated_image_is_reported_at_its_end(tmp_path):
    """The first difference of a short file is the offset where it runs out."""
    bad = tmp_path / "SLUS_207.11"
    bad.write_bytes(RETAIL.read_bytes()[:1000])
    msg = g1.compare(bad, RETAIL)
    assert "0x3E8" in msg, msg
    assert g1.sha256(bad) in msg and SHA in msg, msg


def test_a_debug_byte_names_its_translation_unit(tmp_path):
    """The localisation that makes G2 a diagnostic: the offset decides the TU."""
    cus = load("cus.json")
    chunk = next(c for c in load("debug_chunks.json") if c["section"] == ".debug")
    tu = cus[chunk["tunits"][0]]
    offset = DEBUG + chunk["offset"]
    msg = g1.compare(corrupted(tmp_path, offset), RETAIL)
    assert f"0x{offset:X}" in msg, msg
    assert tu["file"] in msg, msg
    assert ".debug" in msg, msg


def test_a_line_byte_names_its_translation_unit(tmp_path):
    cus = load("cus.json")
    chunks = load("debug_chunks.json")
    chunk = next(c for c in chunks if c["section"] == ".line")
    record = cus[chunk["tunits"][0]]
    owner = next(c for c in chunks if c["section"] == ".debug"
                 and record["index"] in c["tunits"])
    tu = cus[owner["tunits"][0]]
    offset = LINE + chunk["offset"]
    msg = g1.compare(corrupted(tmp_path, offset), RETAIL)
    assert f"0x{offset:X}" in msg and ".line" in msg, msg
    assert tu["file"] in msg, msg


def test_a_loadable_byte_is_reported_without_a_translation_unit(tmp_path):
    """Only .debug/.line bytes belong to a compile unit; code bytes must not be guessed."""
    msg = g1.compare(corrupted(tmp_path, 0x80 + 0x100), RETAIL)
    assert f"0x{0x80 + 0x100:X}" in msg, msg


def test_the_pinned_hash_comes_from_the_checksum_file():
    assert g1.pinned_hash() == SHA


def test_cli_accepts_a_byte_identical_image(tmp_path, capsys):
    good = tmp_path / "SLUS_207.11"
    good.write_bytes(RETAIL.read_bytes())
    assert g1.main([str(good)]) == 0
    assert "ok" in capsys.readouterr().out


def test_cli_rejects_a_corrupted_image(tmp_path, capsys):
    assert g1.main([str(corrupted(tmp_path, DEBUG + 4))]) == 1
    assert "sha256 mismatch" in capsys.readouterr().out


def test_cli_refuses_a_missing_retail_binary(tmp_path, capsys):
    built = tmp_path / "SLUS_207.11"
    built.write_bytes(RETAIL.read_bytes())
    absent = tmp_path / "absent"
    assert g1.main([str(built), "--retail", str(absent)]) != 0
    assert str(absent) in capsys.readouterr().err


def test_cli_refuses_a_wrong_retail_binary(tmp_path, capsys):
    """Review Focus 2: a missing, truncated or different retail binary fails loudly."""
    truncated = tmp_path / "retail"
    truncated.write_bytes(RETAIL.read_bytes()[:1000])
    built = tmp_path / "SLUS_207.11"
    built.write_bytes(RETAIL.read_bytes())
    assert g1.main([str(built), "--retail", str(truncated)]) != 0
    err = capsys.readouterr().err
    assert SHA in err and "1000 bytes" in err, err
