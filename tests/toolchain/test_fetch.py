# tests/toolchain/test_fetch.py
import hashlib, pathlib, pytest, sys, types
ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch

MWCCPS2_SHA256 = "98d3fb6fc362c6b28208e1cc05ff25e32b7c78ffca0c3114cde5392a67c06294"


def _a_host(monkeypatch, name):
    """Make this process *look like* ``name``: asset selection is the only question asked."""
    monkeypatch.setattr(fetch, "platform", types.SimpleNamespace(system=lambda: name))


@pytest.mark.parametrize("host, asset", [
    ("Darwin", "wibo-macos"),
    ("Linux", "wibo-x86_64"),
    ("Windows", None),          # native compilers: nothing to translate, nothing to fetch
])
def test_the_runner_asset_follows_the_host(monkeypatch, host, asset):
    _a_host(monkeypatch, host)
    assert fetch.wibo_asset() == asset


def test_the_url_names_the_hosts_asset(monkeypatch):
    _a_host(monkeypatch, "Linux")
    assert fetch.wibo_url() == f"{fetch.WIBO_BASE}/wibo-x86_64"


def test_windows_installs_no_runner_and_says_why(monkeypatch, capsys):
    """``wibo()`` returns ``None`` there, which is what probe passes through to run natively."""
    _a_host(monkeypatch, "Windows")
    assert fetch.wibo() is None
    assert "native" in capsys.readouterr().err
    with pytest.raises(fetch.UnpinnedArtifact, match="native"):
        fetch.wibo_pin()


def test_a_host_with_no_asset_is_refused_not_guessed(monkeypatch):
    """An unlisted host must not be handed a runner it cannot execute."""
    _a_host(monkeypatch, "FreeBSD")
    assert fetch.wibo_asset() is None
    with pytest.raises(fetch.UnpinnedArtifact, match="WIBO_ASSETS"):
        fetch.wibo_pin()
    with pytest.raises(fetch.UnpinnedArtifact):
        fetch.wibo_url()


def test_an_unpinned_asset_is_refused(monkeypatch):
    _a_host(monkeypatch, "Linux")
    with pytest.raises(fetch.UnpinnedArtifact, match="no pinned digest"):
        fetch.wibo_pin("wibo-arm64")


#: The 1.2.0 release assets, hashed after download (the URL is ``releases/latest``, so the
#: digest -- not the tag -- is what is pinned) and recorded here so a silent re-pin is a test
#: failure rather than a diff nobody reads.
WIBO_1_2_0 = {
    "wibo-macos": "2b3000ef6a7a490c24ccd71967735ae0005e218922e51806cca1b8d77fd3cf7c",
    "wibo-x86_64": "13f86a2d618f0dbe67179d349625345eabf9b46450295cb4c904e49f6aff85af",
}


@pytest.mark.parametrize("asset", sorted(WIBO_1_2_0))
def test_every_release_asset_is_pinned_to_its_observed_digest(asset):
    digest = fetch.WIBO_PINNED[asset]
    assert digest == WIBO_1_2_0[asset]
    assert len(digest) == 64 and digest == digest.lower()


def test_every_asset_a_host_runs_is_pinned():
    """No asset is selectable unless its digest is pinned: ``wibo_pin`` is the only gate."""
    assert set(fetch.WIBO_ASSETS.values()) <= set(fetch.WIBO_PINNED)


def test_a_windows_sweep_records_no_runner_and_still_succeeds(monkeypatch, tmp_path):
    """The ``wibo`` target on a native host is *not needed*, not a failed download."""
    _a_host(monkeypatch, "Windows")
    state, provenance = tmp_path / "state.json", tmp_path / "PROVENANCE.txt"
    assert fetch.main(["wibo", "--root", str(tmp_path / "tc"),
                       "--state", str(state),
                       "--provenance", str(provenance)]) == 0
    assert not (tmp_path / "tc" / "wibo").exists()
    record = provenance.read_text()
    assert "[wibo] runner not needed" in record
    assert "native" in record and "no runner" in record

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


def test_a_cold_tree_does_not_share_one_partial_between_compile_edges(tmp_path, monkeypatch):
    """Every `cc` edge calls the fetch, so on a cold runner several download at once.  A single
    `<artifact>.part` let one process rename it into the cache while another was verifying it,
    which fails as FileNotFoundError from `stat` - measured on a fresh macOS runner."""
    payload = b"compiler archive stand-in"
    digest = hashlib.sha256(payload).hexdigest()
    monkeypatch.setattr(fetch, "CACHE_DIR", tmp_path / "downloads")
    monkeypatch.setattr(fetch, "ARTIFACTS", {"probe-1": "probe-1.tar.gz"})
    monkeypatch.setattr(fetch, "PINNED", {"probe-1": {"archive": (digest, len(payload))}})
    monkeypatch.setattr(fetch, "BASE_URL", "https://example.invalid")

    seen = []

    def download(url, dest):
        seen.append(dest.name)
        assert dest.name != "probe-1.tar.gz.part", "the shared partial name is back"
        dest.write_bytes(payload)

    monkeypatch.setattr(fetch, "_download", download)
    archive, how = fetch._cached_archive("probe-1")
    assert archive.read_bytes() == payload and how == "download"
    assert len(seen) == 1
