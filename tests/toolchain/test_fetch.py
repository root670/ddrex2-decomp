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

def _wibo_seed():
    """A real wibo binary to tamper with, or None when this machine has none (no network)."""
    installed = ROOT / "toolchain/wibo"
    if installed.is_file():
        return installed
    built = sorted((pathlib.Path.home() / "ac-decomp/.cache/wibo").glob("*/wibo"))
    return built[-1] if built else None

def test_tampered_wibo_is_rejected(tmp_path):
    tampered = tmp_path / "wibo-macos"
    seed = _wibo_seed()
    if seed is None:
        tampered.write_bytes(b"not wibo")
    else:
        blob = bytearray(seed.read_bytes())
        blob[-1] ^= 0xFF
        tampered.write_bytes(bytes(blob))
    root = tmp_path / "tc"
    with pytest.raises(fetch.HashMismatch):
        fetch.wibo(root=root, override_url=f"file://{tampered}")
    assert not (root / "wibo").exists()

M2C_TREE_SHA256 = "54a4a71f5aa3d0f1b9d5cef82b0fba4c485cf167793acd4154569ed3cb1ee7b4"

def test_m2c_tree_matches_the_pinned_digest(tmp_path):
    d = fetch.m2c(root=tmp_path)
    assert (d / "m2c.py").is_file() and (d / "m2c_pycparser/c_parser.py").is_file()
    assert fetch._tree_digest(d) == (M2C_TREE_SHA256, 1519)

def test_m2c_is_reverified_in_place(tmp_path):
    d = fetch.m2c(root=tmp_path)
    assert fetch.m2c(root=tmp_path) == d
    assert fetch.installed_m2c(tmp_path) == d

def test_corrupt_m2c_archive_is_rejected(tmp_path):
    bad = tmp_path / "m2c.tar.gz"
    bad.write_bytes(b"not a tarball")
    root = tmp_path / "tc"
    with pytest.raises(fetch.HashMismatch):
        fetch.m2c(root=root, override_url=f"file://{bad}")
    assert not fetch.m2c_dir(root).exists()

def test_unpinned_m2c_content_is_rejected(tmp_path):
    import io, tarfile
    archive = tmp_path / "m2c.tar.gz"
    with tarfile.open(archive, "w:gz") as tar:
        blob = b"print('not m2c')\n"
        info = tarfile.TarInfo(f"m2c-{'0' * 40}/m2c.py")
        info.size = len(blob)
        tar.addfile(info, io.BytesIO(blob))
    with pytest.raises(fetch.HashMismatch, match="tree sha256"):
        fetch.m2c(root=tmp_path / "tc", override_url=f"file://{archive}")
