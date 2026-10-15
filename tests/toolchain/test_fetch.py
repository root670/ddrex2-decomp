# tests/toolchain/test_fetch.py
import hashlib, pathlib, pytest, sys
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch

MWCCPS2_SHA256 = "98d3fb6fc362c6b28208e1cc05ff25e32b7c78ffca0c3114cde5392a67c06294"

def test_compiler_archive_has_expected_members(tmp_path):
    d = fetch.compiler("2.4-001213", root=tmp_path)
    assert (d / "mwccps2.exe").stat().st_size == 1379328
    assert (d / "mwldps2.exe").exists() and (d / "asm_r5900_elf.exe").exists()

def test_compiler_binary_hash_is_pinned(tmp_path):
    d = fetch.compiler("2.4-001213", root=tmp_path)
    assert hashlib.sha256((d / "mwccps2.exe").read_bytes()).hexdigest() == MWCCPS2_SHA256

def test_corrupt_archive_is_rejected(tmp_path):
    bad = tmp_path / "mwcps2-2.4-001213.tar.gz"
    bad.write_bytes(b"not a tarball")
    with pytest.raises(fetch.HashMismatch):
        fetch.compiler("2.4-001213", root=tmp_path, override_url=f"file://{bad}")
