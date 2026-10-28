#!/usr/bin/env python3
"""Fetch and hash-verify the CodeWarrior PS2 compilers, wibo, m2c and the permuter.

Nothing is ever extracted, installed, cached or *executed* before it has been checked
against ``PINNED`` / ``WIBO_PINNED`` / ``M2C_PINNED`` (spec Review Focus 3: verify *before* use).  A
corrupt or partial download is rejected with :class:`HashMismatch` while the bytes are
still a ``.part`` file in ``toolchain/.downloads/``, so a half-verified compiler — or an
altered runner — can never be mistaken for a working one.

The archives are proprietary and are never vendored (``.gitignore`` ignores
``toolchain/``): they are fetched from the decomp.me compiler releases and
re-verified against the pinned digests on every fetch.

Usage::

    python3 tools/toolchain/fetch.py                 # wibo + m2c + every candidate build
    python3 tools/toolchain/fetch.py 2.4-001213      # the required build only
    python3 tools/toolchain/fetch.py wibo
    python3 tools/toolchain/fetch.py m2c
    python3 tools/toolchain/fetch.py --root /tmp/tc 2.4-001213

``2.4-001213`` is the *required* build, as is wibo where a runner is needed: if either fails
the command exits non-zero.  wibo is fetched per host — ``wibo-macos`` on Darwin,
``wibo-x86_64`` on Linux — and *not at all* on Windows, whose compilers are native PE
binaries; there :func:`wibo` returns ``None`` and the ``wibo`` target is recorded as
``not needed``.  ``m2c`` is pinned by commit and by a digest of its whole extracted
tree; it is a drafting aid (``tools/units/m2c_draft.py``) rather than a build input,
so a failure to fetch it is recorded and does not fail the sweep.  The other candidate
builds are optional alternates used later to select the compiler build by
byte-matching a known function; a failure there is
recorded in ``toolchain/PROVENANCE.txt`` and the run continues.  A candidate named
explicitly on the command line is required for that run.
"""

from __future__ import annotations

import argparse
import datetime
import hashlib
import json
import os
import pathlib
import platform
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.error
import urllib.request

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
TOOLCHAIN_ROOT = REPO_ROOT / "toolchain"
CACHE_DIR = TOOLCHAIN_ROOT / ".downloads"
STATE_FILE = TOOLCHAIN_ROOT / ".fetched.json"
PROVENANCE_FILE = TOOLCHAIN_ROOT / "PROVENANCE.txt"

# PROVENANCE.txt is rendered from the fetch state, but the *host* tools the build calls by
# name (assembler, linker, objcopy, ninja, splat, objdiff) are recorded in the same file by
# tools/toolchain/check_deps.py.  That section is marked so a refetch carries it across
# verbatim instead of silently dropping the developer's host record.
HOST_TOOLS_BEGIN = "# --- host tools: tools/toolchain/check_deps.py ---"
HOST_TOOLS_END = "# --- end host tools ---"
HOST_TOOLS_OWNER = "tools/toolchain/check_deps.py"

BASE_URL = "https://github.com/decompme/compilers/releases/download/compilers"
ARTIFACTS = {
    "2.4-001213": "mwcps2-2.4-001213.tar.gz",
    "3.0-011126": "mwcps2-3.0-011126.tar.gz",
    "3.0.1-020123": "mwcps2-3.0.1-020123.tar.gz",
    "3.0b38-030307": "mwcps2-3.0b38-030307.tar.gz",
    "3.0.3-020716": "mwcps2-3.0.3-020716.tar.gz",
}
CANDIDATES = tuple(ARTIFACTS)
REQUIRED = "2.4-001213"

WIBO_BASE = "https://github.com/decompals/wibo/releases/latest/download"
#: The release asset each host runs.  A host listed in :data:`WIBO_NATIVE` needs no runner
#: at all; any other host without an asset here cannot run the compilers and says so.
WIBO_ASSETS = {"darwin": "wibo-macos", "linux": "wibo-x86_64"}
#: Hosts whose compilers are native binaries: ``mwccps2.exe`` and ``mwldps2.exe`` are PE
#: images, so Windows executes them directly and wibo would only be a second copy of Windows.
WIBO_NATIVE = ("windows",)
WIBO_NAME = "wibo"
WIBO_LOCAL_FALLBACK = pathlib.Path.home() / "ac-decomp" / ".cache" / "wibo"
ALREADY_INSTALLED = "already installed"
IN_PLACE = "in place (origin not recorded)"
TIMEOUT = 120
DESCRIPTION = ("Fetch and hash-verify the CodeWarrior PS2 compilers, wibo, m2c "
               "and decomp-permuter into toolchain/.")

# wibo is published under ``releases/latest``, so its URL cannot be pinned: the digest of the
# binary we accept is pinned here instead and is checked *before* wibo is executed (R15).
# Both the release assets and the patched fallback build are pinned; an installed wibo that
# matches neither its host's pin nor the fallback is refused rather than run.  Each digest is
# of the bytes of the 1.2.0 asset as downloaded from that release and hashed here.
WIBO_PINNED = {
    "wibo-macos": "2b3000ef6a7a490c24ccd71967735ae0005e218922e51806cca1b8d77fd3cf7c",  # 1.2.0
    "wibo-x86_64": "13f86a2d618f0dbe67179d349625345eabf9b46450295cb4c904e49f6aff85af",  # 1.2.0
}
WIBO_FALLBACK_PINNED = "d94d832136c74fec3960047e55a30382e74bb06848bba5386b15abd17380b314"  # 1.2.0-1-g09b973a

# ---------------------------------------------------------------------------
# decomp-permuter: the source-permutation search `tools/units/permute.py` drives.
#
# It is a tool, not a compiler: MIT-licensed Python, fetched from GitHub and verified
# before it is imported.  The project publishes no tag or release, so the *commit* is the
# version.  ``archive`` detects a corrupt or partial download before it is opened;
# ``tree`` -- the same digest of every regular file m2c pins -- is what is verified
# before the tree is published or imported, so a re-packaged tarball is accepted only
# when its content is exactly this.  Nothing is vendored: ``toolchain/`` is gitignored
# exactly like the compiler archives.
# ---------------------------------------------------------------------------
PERMUTER_NAME = "decomp-permuter"
PERMUTER_VERSION = "8556c81d80d1c1af98a858c8f4dc951357f29139"
PERMUTER_URL = ("https://codeload.github.com/simonlindholm/decomp-permuter/tar.gz/"
                + PERMUTER_VERSION)
PERMUTER_ARCHIVE = f"{PERMUTER_NAME}-{PERMUTER_VERSION}.tar.gz"
PERMUTER_PINNED = {
    "archive": ("57cfb45141a2f97ce27e74c1882aab162ff203c2f4688b4617fc2ec3a6ca9907", 2870176),
    "tree": ("7a073645521e41b202cf59c8b6150daf8f627cd63b5d2b6f84486b48ac39ae89", 255),
}
#: The entry point the driver imports; it needs its own directory on ``sys.path``.
PERMUTER_ENTRY = "permuter.py"
PERMUTER_REMEDY = "python3 tools/toolchain/fetch.py decomp-permuter"


# ---------------------------------------------------------------------------
# m2c: the MIPS-to-C decompiler used to seed a draft (tools/units/m2c_draft.py).
#
# It is a pure-Python tool that vendors its own pycparser fork (``m2c_pycparser``,
# BSD-3-Clause), so it has no third-party dependency we would have to install; only
# ``--visualize`` wants ``graphviz``, and the draft path never asks for it.  m2c itself
# is GPL-3.0-only, which is exactly why it is *fetched* into the gitignored
# ``toolchain/`` and never vendored into this tree (THIRD_PARTY_NOTICES.md records it).
#
# Two digests are pinned.  ``archive`` detects a corrupt or partial download before it
# is opened; ``tree`` -- sha256 over ``"<file sha256>  <relpath>\n"`` for every regular
# file, sorted by relpath -- is what is actually verified before the tree is published
# or used, because it names the *content* rather than GitHub's tarball packaging (a
# re-generated archive is accepted only when it holds exactly this tree).
# ---------------------------------------------------------------------------
M2C_NAME = "m2c"
M2C_COMMIT = "c632946b8cfbe8fce442b522dba92dfa72f1f317"
M2C_TARBALL = f"m2c-{M2C_COMMIT}.tar.gz"
M2C_URL = f"https://codeload.github.com/matt-kempster/m2c/tar.gz/{M2C_COMMIT}"
M2C_PINNED = {
    "archive": ("b95b6eabd4c879292b896120cbf8e2bb8aed9700cd83d45e964f145f99be47e2", 713313),
    "tree": ("54a4a71f5aa3d0f1b9d5cef82b0fba4c485cf167793acd4154569ed3cb1ee7b4", 1519),
}
#: The repository's entry point; running it needs its own directory on ``sys.path``.
M2C_ENTRY = "m2c.py"
M2C_REMEDY = "python3 tools/toolchain/fetch.py m2c"

# ---------------------------------------------------------------------------
# Pinned digests: the gate every artifact must pass before it is used.
#
# ``2.4-001213`` was verified before this module existed (archive and members
# hashed and matched against the pre-flight record), so its digests are
# authoritative.  The four alternates are first-fetch pins observed 2026-10-14
# from the same release; they detect a corrupt, partial or silently replaced
# download, they do not establish authorship.
#
# layout: version -> {"archive": (sha256, bytes), "members": {name: (sha256, bytes)}}
# ---------------------------------------------------------------------------
PINNED = {
    "2.4-001213": {
        "archive": ("0ebe09436b4163c3a109b0431517281501d2de1bd5a0b049d33057710a943e3e", 1216571),
        "members": {
            "mwccps2.exe": ("98d3fb6fc362c6b28208e1cc05ff25e32b7c78ffca0c3114cde5392a67c06294", 1379328),
            "mwldps2.exe": ("9d161412e67bb96d3b0c6f75b89eb9ebc2b7601215cbd2565c6cb814c40e2737", 532992),
            "asm_r5900_elf.exe": ("6f215bcca5bc11028dd358b1b4c34d69020e35516de2c81a88cc627ede6683b3", 534632),
            "LMGR326B.DLL": ("bd9415ab11f4aef42c372e8547a8303b02464b59549745be597cf09e460737e8", 306688),
        },
    },
    "3.0-011126": {
        "archive": ("b83fef398fd765aaeb48576dae0fa0751bf9c1496036d0d878e7a2a0e71c2a7f", 1064442),
        "members": {
            "mwccps2.exe": ("0e16a5d6205101f840f85c02664f21cd63b39a0dec2dff417b3a61b4477f0e00", 1411584),
            "asm_r5900_elf.exe": ("0553857c9391ba6f550c846869d1b7491c5c13c72e12812d75d59fe54d4316fb", 251392),
            "LMGR326B.dll": ("cf78f32244ad6b5a716589403663030de9cb604f4027d0a3da92de2a91506d83", 653419),
        },
    },
    "3.0.1-020123": {
        "archive": ("72d823d85943c92ca13378e93d56ac1870298ccbfda0ef8a2efb9650692e968c", 1065101),
        "members": {
            "mwccps2.exe": ("488675890770ef9940a0db12ae2181e729bad55bccd8991e0d370754e4a021b8", 1413120),
            "asm_r5900_elf.exe": ("0553857c9391ba6f550c846869d1b7491c5c13c72e12812d75d59fe54d4316fb", 251392),
            "LMGR326B.dll": ("cf78f32244ad6b5a716589403663030de9cb604f4027d0a3da92de2a91506d83", 653419),
        },
    },
    "3.0b38-030307": {
        "archive": ("db3d0606c77d4335d2ad884a1285a4bc3b9e68cdd6161dd46d6e2a2cd3313276", 1237047),
        "members": {
            "mwccps2.exe": ("acf1088553362dddef7eee2d269848b03208e29fd26caa441848e57b6299786a", 1639424),
            "mwldps2.exe": ("7bd36d23d9f71da967ef4ba5abfd3efba19cb1b8d825be40ec057e14213470bc", 491520),
            "asm_r5900_elf.exe": ("0553857c9391ba6f550c846869d1b7491c5c13c72e12812d75d59fe54d4316fb", 251392),
            "LMGR326B.DLL": ("bd9415ab11f4aef42c372e8547a8303b02464b59549745be597cf09e460737e8", 306688),
        },
    },
    "3.0.3-020716": {
        "archive": ("63f89baae691403294724178efbcfc9e1b9ac48151536b6a321b17eb8f9970e5", 1064904),
        "members": {
            "mwccps2.exe": ("c894c769efbce7938f7c334ee408e6e3c1fae2da033e02cbdecfe9f88210f236", 1413120),
            "asm_r5900_elf.exe": ("0553857c9391ba6f550c846869d1b7491c5c13c72e12812d75d59fe54d4316fb", 251392),
            "LMGR326B.dll": ("cf78f32244ad6b5a716589403663030de9cb604f4027d0a3da92de2a91506d83", 653419),
        },
    },
}


class FetchError(Exception):
    """A toolchain artifact could not be fetched."""


class HashMismatch(FetchError):
    """Downloaded bytes do not match the pinned digest; nothing was extracted."""


class DownloadFailed(FetchError):
    """The artifact could not be transferred."""


class UnpinnedArtifact(FetchError):
    """No digest is pinned for this artifact, so it cannot be trusted and is refused."""


def sha256_file(path: pathlib.Path) -> str:
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for block in iter(lambda: handle.read(1 << 20), b""):
            digest.update(block)
    return digest.hexdigest()


def _now() -> str:
    return datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def wibo_url(asset: str | None = None) -> str:
    """Release asset URL for wibo on this host (``wibo-macos``/``wibo-x86_64``)."""
    asset = asset or wibo_asset()
    if asset is None:
        raise UnpinnedArtifact(_no_runner())
    return f"{WIBO_BASE}/{asset}"


def _download(url: str, dest: pathlib.Path) -> None:
    """Stream ``url`` (http/https/file) to ``dest``, removing it on any failure."""
    request = urllib.request.Request(url, headers={"User-Agent": "ddrex-decomp-toolchain-fetch"})
    try:
        with urllib.request.urlopen(request, timeout=TIMEOUT) as response:
            with open(dest, "wb") as handle:
                shutil.copyfileobj(response, handle)
    except (urllib.error.URLError, OSError, ValueError) as exc:
        dest.unlink(missing_ok=True)
        raise DownloadFailed(f"{url}: {exc}") from exc


def _verify_archive(path: pathlib.Path, version: str) -> None:
    """Check a tarball against its pinned digest, before it is opened."""
    pin = PINNED.get(version)
    if pin is None:
        raise UnpinnedArtifact(f"no pinned digest for compiler build {version!r}; refusing to use it")
    expected_sha, expected_size = pin["archive"]
    actual_size = path.stat().st_size
    actual_sha = sha256_file(path)
    if actual_sha != expected_sha or actual_size != expected_size:
        raise HashMismatch(
            f"{path.name}: sha256 {actual_sha} ({actual_size} bytes) "
            f"!= pinned {expected_sha} ({expected_size} bytes)"
        )


def _verified_members(archive: pathlib.Path, version: str) -> dict[str, bytes]:
    """Read every pinned member out of ``archive``, verifying each digest in memory.

    Nothing is written here: a mismatch raises before any byte reaches the
    destination directory.
    """
    members: dict[str, bytes] = {}
    try:
        with tarfile.open(archive, "r:gz") as tar:
            entries = {
                pathlib.PurePosixPath(member.name).name: member
                for member in tar.getmembers()
                if member.isfile()
            }
            for name, (expected_sha, expected_size) in PINNED[version]["members"].items():
                if name not in entries:
                    raise HashMismatch(f"{archive.name}: pinned member {name} is missing")
                blob = tar.extractfile(entries[name]).read()
                actual_sha = hashlib.sha256(blob).hexdigest()
                if actual_sha != expected_sha or len(blob) != expected_size:
                    raise HashMismatch(
                        f"{archive.name}:{name}: sha256 {actual_sha} ({len(blob)} bytes) "
                        f"!= pinned {expected_sha} ({expected_size} bytes)"
                    )
                members[name] = blob
    except tarfile.TarError as exc:
        raise HashMismatch(f"{archive.name} is not a readable tar archive: {exc}") from exc
    return members


def _dest_members_ok(dest: pathlib.Path, version: str) -> bool:
    """True when ``dest`` already holds every pinned member byte-for-byte."""
    for name, (expected_sha, expected_size) in PINNED[version]["members"].items():
        member = dest / name
        if not member.is_file() or member.stat().st_size != expected_size:
            return False
        if sha256_file(member) != expected_sha:
            return False
    return True


def _publish(dest: pathlib.Path, members: dict[str, str], version: str) -> None:
    """Materialise verified members in ``dest`` through a per-process staging directory.

    ``dest`` is shared by every compile edge, so a *fixed* staging name (``<dest>.staging``)
    made two edges delete each other's tree mid-write on a cold runner.  Each process now
    stages privately, and the rename is the only step that races -- it is atomic, so the
    loser simply finds a complete ``dest`` and discards its own copy.
    """
    staging = pathlib.Path(tempfile.mkdtemp(dir=dest.parent, prefix=f".{dest.name}."))
    try:
        for name, blob in members.items():
            member = staging / name
            member.parent.mkdir(parents=True, exist_ok=True)
            member.write_bytes(blob)
        try:
            staging.rename(dest)
        except OSError:
            # Someone else published first: keep theirs if it is complete, else replace it.
            if not _dest_members_ok(dest, version):
                shutil.rmtree(dest, ignore_errors=True)
                staging.rename(dest)
    finally:
        shutil.rmtree(staging, ignore_errors=True)


def _cached_archive(version: str) -> tuple[pathlib.Path, str]:
    """Verify or fetch the tarball into the shared cache; only verified bytes are kept."""
    archive = CACHE_DIR / ARTIFACTS[version]
    if archive.is_file():
        try:
            _verify_archive(archive, version)
            return archive, "cache"
        except HashMismatch:
            archive.unlink()  # poisoned cache entry: never reuse it
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    # A cold tree has one download per compile edge in flight at once, so the scratch file
    # cannot be shared: a single `<artifact>.part` let one process rename it into the cache
    # while another was still verifying it, which is a FileNotFoundError from `stat`, not a
    # hash mismatch (measured on a fresh macOS runner).  Each process downloads privately and
    # publishes by an atomic replace.
    with tempfile.NamedTemporaryFile(dir=CACHE_DIR, prefix=f".{ARTIFACTS[version]}.",
                                     suffix=".part", delete=False) as scratch:
        partial = pathlib.Path(scratch.name)
    try:
        _download(f"{BASE_URL}/{ARTIFACTS[version]}", partial)
        _verify_archive(partial, version)
        partial.replace(archive)
    except BaseException:
        partial.unlink(missing_ok=True)
        # Another process may have published a good copy while this one was failing.
        if archive.is_file():
            try:
                _verify_archive(archive, version)
                return archive, "cache"
            except HashMismatch:
                archive.unlink()
        raise
    return archive, "download"


def _install_compiler(
    version: str, root: pathlib.Path, override_url: str | None = None
) -> tuple[pathlib.Path, str]:
    """Verify and install build ``version``; return (directory, how it was obtained)."""
    dest = root / pathlib.Path(ARTIFACTS[version]).name[: -len(".tar.gz")]
    if override_url is not None:
        # Overrides are never cached, so a bad URL cannot poison the cache.
        CACHE_DIR.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=CACHE_DIR, prefix=".override-") as scratch:
            archive = pathlib.Path(scratch) / ARTIFACTS[version]
            _download(override_url, archive)
            _verify_archive(archive, version)
            _publish(dest, _verified_members(archive, version), version)
        return dest, override_url
    if _dest_members_ok(dest, version):
        return dest, ALREADY_INSTALLED
    archive, source = _cached_archive(version)
    _publish(dest, _verified_members(archive, version), version)
    return dest, source


def compiler(
    version: str,
    root: pathlib.Path | str | None = None,
    override_url: str | None = None,
) -> pathlib.Path:
    """Fetch, verify and extract compiler build ``version``; return its directory.

    ``override_url`` bypasses the cache and is intended for tests; fetched bytes
    are still verified against ``PINNED`` before anything is extracted.
    """
    if version not in ARTIFACTS:
        raise FetchError(f"unknown compiler build {version!r}; known builds: {', '.join(CANDIDATES)}")
    if version not in PINNED:
        raise UnpinnedArtifact(f"no pinned digest for compiler build {version!r}; refusing to use it")
    root = pathlib.Path(root) if root is not None else TOOLCHAIN_ROOT
    return _install_compiler(version, root, override_url)[0]


def _wibo_version(binary: pathlib.Path) -> str | None:
    """Run ``binary --version``; return the reported version, or None if it does not run."""
    try:
        result = subprocess.run([str(binary), "--version"], capture_output=True, text=True, timeout=60)
    except (OSError, subprocess.SubprocessError):
        return None
    out = result.stdout.strip()
    line = out.splitlines()[0] if out else ""
    return line if result.returncode == 0 and line.startswith("wibo ") else None


def wibo_local_fallback() -> pathlib.Path | None:
    """The pinned patched wibo already built on this machine, or None.

    The digest is checked here (before the binary is ever executed or installed),
    so a rebuilt-but-unpinned local wibo is not silently substituted.
    """
    candidates = sorted(WIBO_LOCAL_FALLBACK.glob("*/wibo"), key=lambda p: p.stat().st_mtime)
    for candidate in reversed(candidates):
        if candidate.is_file() and sha256_file(candidate) == WIBO_FALLBACK_PINNED:
            return candidate
    return None


def _no_runner() -> str:
    """The one refusal for a host that has no pinned runner; names why there is none."""
    host = platform.system()
    if host.lower() in WIBO_NATIVE:
        return (f"no wibo runner is needed on {host}: mwccps2.exe and mwldps2.exe are "
                f"native there")
    return (f"no wibo release asset is known for {host}: add it to WIBO_ASSETS and pin its "
            f"digest in WIBO_PINNED before use")


def wibo_asset() -> str | None:
    """wibo release asset this host runs, or ``None`` where the compilers are native.

    ``wibo-macos`` on Darwin, ``wibo-x86_64`` (a static x86-64 ELF) on Linux; Windows runs
    the compilers directly, so :func:`wibo` installs nothing there.
    """
    host = platform.system().lower()
    if host in WIBO_NATIVE:
        return None
    return WIBO_ASSETS.get(host)


def wibo_pin(asset: str | None = None) -> str:
    """Pinned digest of the wibo asset this host accepts; refuses to run an unpinned one."""
    asset = asset or wibo_asset()
    if asset is None:
        raise UnpinnedArtifact(_no_runner())
    digest = WIBO_PINNED.get(asset)
    if digest is None:
        raise UnpinnedArtifact(
            f"no pinned digest for wibo asset {asset!r}; add it to WIBO_PINNED before use"
        )
    return digest


def _verify_wibo_digest(path: pathlib.Path, expected: str, what: str) -> None:
    """Digest gate for wibo, applied before the binary is executed or installed."""
    actual = sha256_file(path)
    if actual != expected:
        raise HashMismatch(f"{what}: sha256 {actual} != pinned {expected}")


def _install_wibo(
    root: pathlib.Path, override_url: str | None = None, in_place_source: str | None = None
) -> tuple[pathlib.Path, str]:
    """Install a digest-pinned wibo and report where the chosen binary came from."""
    root.mkdir(parents=True, exist_ok=True)
    dest = root / WIBO_NAME
    expected = wibo_pin()
    if dest.is_file() and os.access(dest, os.X_OK):
        digest = sha256_file(dest)
        if digest not in (expected, WIBO_FALLBACK_PINNED):
            raise HashMismatch(
                f"{dest}: sha256 {digest} matches neither the pinned {wibo_asset()} asset "
                f"({expected}) nor the pinned local fallback ({WIBO_FALLBACK_PINNED})"
            )
        if _wibo_version(dest):
            return dest, in_place_source or IN_PLACE
    url = override_url or wibo_url()
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=CACHE_DIR, prefix=".wibo-") as scratch:
        staged = pathlib.Path(scratch) / WIBO_NAME
        source = url
        try:
            _download(url, staged)
            _verify_wibo_digest(staged, expected, url)  # before it is executed
            os.chmod(staged, 0o755)
            if not _wibo_version(staged):
                raise DownloadFailed(f"{url}: downloaded wibo does not run on this host")
        except DownloadFailed:
            # Transport or execution failure only: a digest mismatch must surface.
            fallback = wibo_local_fallback()
            if fallback is None:
                raise
            _verify_wibo_digest(fallback, WIBO_FALLBACK_PINNED, str(fallback))
            source = str(fallback)
            shutil.copy2(fallback, staged)
            os.chmod(staged, 0o755)
            if not _wibo_version(staged):
                raise DownloadFailed(f"{source}: pinned fallback wibo does not run on this host")
        # Install by atomic rename, never by copying over `dest`: every compile edge installs
        # the same runner, and on Linux overwriting a file another edge is executing fails with
        # ETXTBSY ("Text file busy").  A rename leaves the running image alone.
        os.replace(staged, dest)
    return dest, source


def wibo(root: pathlib.Path | str | None = None, override_url: str | None = None) -> pathlib.Path | None:
    """Fetch wibo, verify it against the pinned digest, prove it runs, and return its path.

    wibo is published under ``releases/latest``, so the URL cannot be pinned; instead
    the digest of the accepted binary (:data:`WIBO_PINNED`) is checked before wibo is
    executed, and an installed wibo matching neither that pin nor the pinned patched
    fallback (:data:`WIBO_FALLBACK_PINNED`) is refused with :class:`HashMismatch`.
    When the download is unreachable, or the downloaded binary does not run under
    Rosetta, the pinned patched binary in ``~/ac-decomp/.cache/wibo`` is installed.

    ``None`` means *this host needs no runner*: the compilers are native Windows binaries,
    so on Windows nothing is fetched and every caller passes ``None`` through to
    :mod:`toolchain.probe`, which then runs the tool itself.
    """
    if wibo_asset() is None:
        print(f"wibo: no runner needed on {platform.system()}: the compilers are native there",
              file=sys.stderr)
        return None
    root = pathlib.Path(root) if root is not None else TOOLCHAIN_ROOT
    return _install_wibo(root, override_url)[0]


# ---------------------------------------------------------------------------
# m2c
# ---------------------------------------------------------------------------


class MissingTool(FetchError):
    """An installed, pinned tool is absent; the message names the command that installs it."""


def _tree_digest(root: pathlib.Path) -> tuple[str, int]:
    """``(sha256, files)`` of a directory's content: every regular file, by relpath.

    The digest is over ``"<file sha256>  <relpath>\\n"`` lines sorted by relpath, so it
    names what the tree *is* and is blind to an archive's mtimes or gzip settings.
    Interpreted bytecode is not content -- m2c is run with ``-B`` so it writes none, and
    a ``__pycache__`` left by a careless run must not make an installed tree "differ".
    """
    rows: list[str] = []
    count = 0
    for path in sorted(root.rglob("*")):
        if not path.is_file():
            continue
        relpath = path.relative_to(root)
        if "__pycache__" in relpath.parts or path.suffix == ".pyc":
            continue
        rows.append(f"{sha256_file(path)}  {relpath.as_posix()}\n")
        count += 1
    return hashlib.sha256("".join(rows).encode()).hexdigest(), count


def _m2c_tree_ok(root: pathlib.Path) -> bool:
    """True when ``root`` already holds the pinned m2c tree, byte for byte."""
    if not (root / M2C_ENTRY).is_file():
        return False
    expected_sha, expected_count = M2C_PINNED["tree"]
    sha, count = _tree_digest(root)
    return sha == expected_sha and count == expected_count


def _verify_m2c_tree(root: pathlib.Path, what: str) -> None:
    expected_sha, expected_count = M2C_PINNED["tree"]
    sha, count = _tree_digest(root)
    if sha != expected_sha or count != expected_count:
        raise HashMismatch(
            f"{what}: tree sha256 {sha} ({count} files) "
            f"!= pinned {expected_sha} ({expected_count} files)"
        )


def _extract_m2c(archive: pathlib.Path, dest: pathlib.Path) -> None:
    """Unpack ``archive`` (one top-level ``m2c-<commit>/``) into ``dest``, strictly.

    Only regular files and directories are accepted: a link, an absolute member or a
    ``..`` component refuses the archive rather than writing outside ``dest``.
    """
    try:
        with tarfile.open(archive, "r:gz") as tar:
            for member in tar.getmembers():
                parts = pathlib.PurePosixPath(member.name).parts
                if not parts or pathlib.PurePosixPath(member.name).is_absolute() or ".." in parts:
                    raise HashMismatch(f"{archive.name}: unsafe member {member.name!r}")
                relative = pathlib.PurePosixPath(*parts[1:]) if len(parts) > 1 else None
                if relative is None or not relative.parts:
                    continue
                if member.isdir():
                    (dest / relative).mkdir(parents=True, exist_ok=True)
                elif member.isfile():
                    payload = tar.extractfile(member)
                    if payload is None:
                        raise HashMismatch(f"{archive.name}:{member.name}: unreadable member")
                    target = dest / relative
                    target.parent.mkdir(parents=True, exist_ok=True)
                    target.write_bytes(payload.read())
                else:
                    raise HashMismatch(f"{archive.name}:{member.name}: not a regular file")
    except tarfile.TarError as exc:
        raise HashMismatch(f"{archive.name} is not a readable tar archive: {exc}") from exc


def m2c_dir(root: pathlib.Path | str | None = None) -> pathlib.Path:
    """Where m2c is installed under ``root`` (``toolchain/m2c/<commit>/``)."""
    root = pathlib.Path(root) if root is not None else TOOLCHAIN_ROOT
    return root / M2C_NAME / M2C_COMMIT


def installed_m2c(root: pathlib.Path | str | None = None) -> pathlib.Path:
    """The verified m2c tree, or :class:`MissingTool` naming the command that installs it."""
    dest = m2c_dir(root)
    if _m2c_tree_ok(dest):
        return dest
    raise MissingTool(
        f"m2c {M2C_COMMIT[:12]} is not installed at {_relative(dest)} (or its tree no longer "
        f"matches the pinned digest); install it with: {M2C_REMEDY}"
    )


def _publish_m2c(archive: pathlib.Path, dest: pathlib.Path) -> pathlib.Path:
    """Extract ``archive`` beside ``dest``, prove the tree, then publish it."""
    staging = dest.parent / f"{dest.name}.staging"
    shutil.rmtree(staging, ignore_errors=True)
    try:
        staging.mkdir(parents=True)
        _extract_m2c(archive, staging)
        for cache in staging.rglob("__pycache__"):
            shutil.rmtree(cache, ignore_errors=True)
        # The tree digest is the gate: packaging may differ, content may not.
        _verify_m2c_tree(staging, M2C_TARBALL)
        if dest.is_dir():
            shutil.rmtree(dest)
        staging.rename(dest)
    except BaseException:
        shutil.rmtree(staging, ignore_errors=True)
        raise
    return dest


def _install_m2c(
    root: pathlib.Path, override_url: str | None = None
) -> tuple[pathlib.Path, str]:
    """Fetch, verify and install pinned m2c; return (directory, how it was obtained)."""
    dest = m2c_dir(root)
    if _m2c_tree_ok(dest):
        return dest, ALREADY_INSTALLED
    if override_url is not None:
        # Overrides are never cached, so a bad URL cannot poison the cache.
        CACHE_DIR.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=CACHE_DIR, prefix=".m2c-") as scratch:
            archive = pathlib.Path(scratch) / M2C_TARBALL
            _download(override_url, archive)
            return _publish_m2c(archive, dest), override_url
    archive = CACHE_DIR / M2C_TARBALL
    if archive.is_file():
        try:
            # A corrupt or partial cached download is rejected without extracting it.
            _verify_archive_digest(archive, M2C_PINNED["archive"], M2C_TARBALL)
            return _publish_m2c(archive, dest), "cache"
        except HashMismatch:
            archive.unlink()  # poisoned cache entry: never reuse it
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    partial = CACHE_DIR / f"{M2C_TARBALL}.part"
    partial.unlink(missing_ok=True)
    _download(M2C_URL, partial)
    partial.replace(archive)
    try:
        return _publish_m2c(archive, dest), "download"
    except BaseException:
        archive.unlink(missing_ok=True)
        raise


def _verify_archive_digest(
    path: pathlib.Path, pin: tuple[str, int], what: str
) -> None:
    """Size and sha256 against a ``(sha256, bytes)`` pin, before the archive is opened."""
    expected_sha, expected_size = pin
    actual_size = path.stat().st_size
    actual_sha = sha256_file(path)
    if actual_sha != expected_sha or actual_size != expected_size:
        raise HashMismatch(
            f"{what}: sha256 {actual_sha} ({actual_size} bytes) "
            f"!= pinned {expected_sha} ({expected_size} bytes)"
        )


def m2c(root: pathlib.Path | str | None = None, override_url: str | None = None) -> pathlib.Path:
    """Fetch, verify and extract pinned m2c; return its directory.

    The archive digest is a fast rejection of a corrupt download; the *extracted tree*
    must match :data:`M2C_PINNED` ``["tree"]`` before it is published, so a re-generated
    tarball can only replace the archive, never the content.
    """
    root = pathlib.Path(root) if root is not None else TOOLCHAIN_ROOT
    return _install_m2c(root, override_url)[0]


# ---------------------------------------------------------------------------
# decomp-permuter
# ---------------------------------------------------------------------------


def permuter_dir(root: pathlib.Path | str | None = None) -> pathlib.Path:
    """Where the permuter is installed under ``root`` (``toolchain/decomp-permuter/<commit>/``)."""
    root = pathlib.Path(root) if root is not None else TOOLCHAIN_ROOT
    return root / PERMUTER_NAME / PERMUTER_VERSION


def _permuter_tree_ok(root: pathlib.Path) -> bool:
    """True when ``root`` already holds the pinned permuter tree, byte for byte."""
    if not (root / PERMUTER_ENTRY).is_file():
        return False
    expected_sha, expected_count = PERMUTER_PINNED["tree"]
    sha, count = _tree_digest(root)
    return sha == expected_sha and count == expected_count


def _verify_permuter_tree(root: pathlib.Path, what: str) -> None:
    expected_sha, expected_count = PERMUTER_PINNED["tree"]
    sha, count = _tree_digest(root)
    if sha != expected_sha or count != expected_count:
        raise HashMismatch(
            f"{what}: tree sha256 {sha} ({count} files) "
            f"!= pinned {expected_sha} ({expected_count} files)"
        )


def _extract_permuter(archive: pathlib.Path, dest: pathlib.Path) -> None:
    """Unpack ``archive`` (one top-level ``decomp-permuter-<commit>/``) into ``dest``.

    The archive is GitHub's tarball of one repository at one commit, which is exactly
    the shape :func:`_extract_m2c` unpacks -- and its strictness (no links, no absolute
    or ``..`` members) is what both want.
    """
    _extract_m2c(archive, dest)


def _publish_permuter(archive: pathlib.Path, dest: pathlib.Path) -> pathlib.Path:
    """Extract ``archive`` beside ``dest``, prove the tree, then publish it."""
    staging = dest.parent / f"{dest.name}.staging"
    shutil.rmtree(staging, ignore_errors=True)
    try:
        staging.mkdir(parents=True)
        _extract_permuter(archive, staging)
        for cache in staging.rglob("__pycache__"):
            shutil.rmtree(cache, ignore_errors=True)
        _verify_permuter_tree(staging, PERMUTER_ARCHIVE)
        if dest.is_dir():
            shutil.rmtree(dest)
        staging.rename(dest)
    except BaseException:
        shutil.rmtree(staging, ignore_errors=True)
        raise
    return dest


def _install_permuter(
    root: pathlib.Path, override_url: str | None = None
) -> tuple[pathlib.Path, str]:
    """Fetch, verify and install the pinned permuter; return (directory, how it was obtained)."""
    dest = permuter_dir(root)
    if _permuter_tree_ok(dest):
        return dest, ALREADY_INSTALLED
    if override_url is not None:
        # Overrides are never cached, so a bad URL cannot poison the cache.
        CACHE_DIR.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=CACHE_DIR, prefix=".permuter-") as scratch:
            archive = pathlib.Path(scratch) / PERMUTER_ARCHIVE
            _download(override_url, archive)
            return _publish_permuter(archive, dest), override_url
    archive = CACHE_DIR / PERMUTER_ARCHIVE
    if archive.is_file():
        try:
            _verify_archive_digest(archive, PERMUTER_PINNED["archive"], PERMUTER_ARCHIVE)
            return _publish_permuter(archive, dest), "cache"
        except HashMismatch:
            archive.unlink()  # poisoned cache entry: never reuse it
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    partial = CACHE_DIR / f"{PERMUTER_ARCHIVE}.part"
    partial.unlink(missing_ok=True)
    _download(PERMUTER_URL, partial)
    partial.replace(archive)
    try:
        return _publish_permuter(archive, dest), "download"
    except BaseException:
        archive.unlink(missing_ok=True)
        raise


def permuter(root: pathlib.Path | str | None = None,
             override_url: str | None = None) -> pathlib.Path:
    """Fetch, verify and extract the pinned permuter; return its directory.

    The archive digest is a fast rejection of a corrupt download; the *extracted tree*
    must match :data:`PERMUTER_PINNED` ``["tree"]`` before it is published, so a
    re-generated tarball can only replace the archive, never the content.
    """
    root = pathlib.Path(root) if root is not None else TOOLCHAIN_ROOT
    return _install_permuter(root, override_url)[0]


def installed_permuter(root: pathlib.Path | str | None = None) -> pathlib.Path:
    """The verified permuter tree, or :class:`MissingTool` naming the command that installs it.

    This is the *read* side: it never downloads.  ``tools/units/permute.py`` calls it so a
    checkout without the tool gets one line naming the remedy instead of a traceback.
    """
    dest = permuter_dir(root)
    if _permuter_tree_ok(dest):
        return dest
    raise MissingTool(
        f"decomp-permuter {PERMUTER_VERSION[:12]} is not installed at {_relative(dest)} "
        f"(or its tree no longer matches the pinned digest); install it with: "
        f"{PERMUTER_REMEDY}")


# ---------------------------------------------------------------------------
# Provenance manifest
# ---------------------------------------------------------------------------


def record_state(entries: dict, state_file: pathlib.Path | None = None) -> None:
    """Merge ``entries`` (keyed by target) into the fetch state."""
    state_file = state_file or STATE_FILE
    state = load_state(state_file)
    state.update(entries)
    state_file.parent.mkdir(parents=True, exist_ok=True)
    state_file.write_text(json.dumps(state, indent=2, sort_keys=True) + "\n")


def load_state(state_file: pathlib.Path | None = None) -> dict:
    state_file = state_file or STATE_FILE
    if state_file.is_file():
        try:
            return json.loads(state_file.read_text())
        except (json.JSONDecodeError, OSError):
            return {}
    return {}


_PROVENANCE_KEYS = (
    "url",
    "source",
    "version",
    "archive",
    "archive_sha256",
    "installed",
    "installed_sha256",
    "pinned_sha256",
    "files",
    "runner",
    "note",
    "reason",
)


def _render_provenance(state: dict, host_tools: str = "") -> str:
    runner = (WIBO_NAME if wibo_asset() is not None
              else f"no runner (the compilers are native on {platform.system()})")
    lines = [
        "# toolchain/PROVENANCE.txt - generated by tools/toolchain/fetch.py; do not edit.",
        "# The compiler archives are proprietary: fetched from the decomp.me compiler",
        "# releases, never vendored. Every artifact below passed the digests pinned in",
        "# tools/toolchain/fetch.py before it was extracted or run; failures are recorded",
        "# here, never silently skipped.",
        f"# required: {REQUIRED} and {runner}; optional: {M2C_NAME} and the alternates "
        + ", ".join(v for v in CANDIDATES if v != REQUIRED),
        f"# host tools (assembler, linker, objcopy, ninja, splat, objdiff) are recorded by {HOST_TOOLS_OWNER}",
        "",
    ]
    for target in sorted(state):
        entry = state[target]
        lines.append(
            f"[{target}] {entry.get('kind', '?')} {entry.get('status', '?')}"
            f"  required={'yes' if entry.get('required') else 'no'}"
        )
        lines.append(f"  observed        {entry.get('observed', '?')}")
        for key in _PROVENANCE_KEYS:
            if entry.get(key) is not None:
                lines.append(f"  {key:<15} {entry[key]}")
        for name, info in sorted(entry.get("members", {}).items()):
            lines.append(f"  member {name}  {info['bytes']} bytes  sha256 {info['sha256']}")
        lines.append("")
    rendered = "\n".join(lines)
    return rendered + host_tools if host_tools else rendered


def host_tools_section(text: str) -> str:
    """The host-tool section already in ``text``, verbatim, or ``""`` when it has none."""
    begin = text.find(HOST_TOOLS_BEGIN)
    if begin < 0:
        return ""
    end = text.find(HOST_TOOLS_END, begin)
    if end < 0:
        return ""
    return text[begin : end + len(HOST_TOOLS_END)] + "\n"


def write_provenance(state_file: pathlib.Path | None = None, path: pathlib.Path | None = None) -> pathlib.Path:
    """Render ``PROVENANCE.txt`` from the recorded fetch state, keeping the host-tool section."""
    path = path or PROVENANCE_FILE
    path.parent.mkdir(parents=True, exist_ok=True)
    host_tools = host_tools_section(path.read_text()) if path.is_file() else ""
    path.write_text(_render_provenance(load_state(state_file), host_tools))
    return path


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------


def _relative(path: pathlib.Path) -> str:
    path = path.resolve()
    return str(path.relative_to(REPO_ROOT)) if path.is_relative_to(REPO_ROOT) else str(path)


def _compiler_entry(version: str, dest: pathlib.Path, source: str, required: bool) -> dict:
    return {
        "kind": "compiler",
        "status": "verified",
        "required": required,
        "observed": _now(),
        "url": f"{BASE_URL}/{ARTIFACTS[version]}",
        "source": source,
        "archive": _relative(CACHE_DIR / ARTIFACTS[version]),
        "archive_sha256": PINNED[version]["archive"][0],
        "installed": _relative(dest),
        "members": {
            name: {"bytes": size, "sha256": sha} for name, (sha, size) in PINNED[version]["members"].items()
        },
    }


def _m2c_entry(source: str, installed: pathlib.Path, required: bool) -> dict:
    sha, count = _tree_digest(installed)
    return {
        "kind": "decompiler",
        "status": "verified",
        "required": required,
        "observed": _now(),
        "url": M2C_URL,
        "source": source,
        "version": M2C_COMMIT,
        "installed": _relative(installed),
        "installed_sha256": sha,
        "pinned_sha256": M2C_PINNED["tree"][0],
        "files": f"{count} files, tree digest {sha}",
    }


def _permuter_entry(source: str, installed: pathlib.Path, required: bool) -> dict:
    sha, count = _tree_digest(installed)
    return {
        "kind": "permuter",
        "status": "verified",
        "required": required,
        "observed": _now(),
        "url": PERMUTER_URL,
        "source": source,
        "version": PERMUTER_VERSION,
        "installed": _relative(installed),
        "installed_sha256": sha,
        "pinned_sha256": PERMUTER_PINNED["tree"][0],
        "files": f"{count} files, tree digest {sha}",
    }


def _wibo_entry(source: str, installed: pathlib.Path, required: bool) -> dict:
    digest = sha256_file(installed)
    pinned = WIBO_FALLBACK_PINNED if digest == WIBO_FALLBACK_PINNED else wibo_pin()
    return {
        "kind": "runner",
        "status": "verified",
        "required": required,
        "observed": _now(),
        "url": wibo_url(),
        "source": source,
        "version": _wibo_version(installed),
        "installed": _relative(installed),
        "installed_sha256": digest,
        "pinned_sha256": pinned,
    }


def _native_entry(required: bool) -> dict:
    """The runner record for a host whose compilers are native: nothing was fetched."""
    return {
        "kind": "runner",
        "status": "not needed",
        "required": required,
        "observed": _now(),
        "runner": "native",
        "note": f"{platform.system()} runs mwccps2.exe and mwldps2.exe directly",
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=DESCRIPTION)
    parser.add_argument(
        "targets",
        nargs="*",
        metavar="TARGET",
        help="compiler build (e.g. 2.4-001213), 'wibo', 'm2c' or 'decomp-permuter'; "
             "default: all four and every build",
    )
    parser.add_argument("--root", default=None, help="destination root (default: toolchain/)")
    parser.add_argument("--state", default=None, help="fetch state file (default: toolchain/.fetched.json)")
    parser.add_argument("--provenance", default=None, help="manifest to write (default: toolchain/PROVENANCE.txt)")
    args = parser.parse_args(argv)

    known = (WIBO_NAME, M2C_NAME, PERMUTER_NAME, *CANDIDATES)
    unknown = [t for t in args.targets if t not in known]
    if unknown:
        parser.error(f"unknown target(s): {', '.join(unknown)} (known: {', '.join(known)})")

    root = pathlib.Path(args.root) if args.root else TOOLCHAIN_ROOT
    state_file = pathlib.Path(args.state) if args.state else STATE_FILE
    provenance = pathlib.Path(args.provenance) if args.provenance else PROVENANCE_FILE

    sweep = not args.targets
    targets = [WIBO_NAME, M2C_NAME, PERMUTER_NAME, *CANDIDATES] if sweep else args.targets
    previous = load_state(state_file)

    entries: dict[str, dict] = {}
    required_failures: list[str] = []
    for target in targets:
        # In the default sweep only the required build and wibo are mandatory; the
        # alternates may legitimately be unavailable and must not fail the run.
        required = not sweep or target in (REQUIRED, WIBO_NAME)
        try:
            if target == PERMUTER_NAME:
                dest, source = _install_permuter(root)
                if source == ALREADY_INSTALLED:
                    source = previous.get(PERMUTER_NAME, {}).get('source') or IN_PLACE
                entries[target] = _permuter_entry(source, dest, required)
                print(f"{target}: verified {PERMUTER_VERSION[:12]} at {dest} (source: {source})")
            elif target == M2C_NAME:
                dest, source = _install_m2c(root)
                if source == ALREADY_INSTALLED:
                    source = previous.get(M2C_NAME, {}).get("source") or IN_PLACE
                entries[target] = _m2c_entry(source, dest, required)
                print(f"{target}: verified {M2C_COMMIT[:12]} at {dest} (source: {source})")
            elif target == WIBO_NAME:
                if wibo_asset() is None:
                    # Nothing to download: this host runs the compilers itself, and a
                    # failed "fetch" of a runner that is never used would be a lie.
                    entries[target] = _native_entry(required)
                    print(f"{target}: not needed on {platform.system()}: "
                          f"the compilers are native there")
                    continue
                dest, source = _install_wibo(
                    root, in_place_source=previous.get(WIBO_NAME, {}).get("source")
                )
                entries[target] = _wibo_entry(source, dest, required)
                print(f"{target}: verified {entries[target]['version']} at {dest} (source: {source})")
            else:
                dest, source = _install_compiler(target, root)
                if source == ALREADY_INSTALLED:
                    # re-verified in place: report where those bytes originally came from
                    source = previous.get(target, {}).get("source") or IN_PLACE
                entries[target] = _compiler_entry(target, dest, source, required)
                print(f"{target}: verified {dest} (source: {source})")
        except FetchError as exc:
            entries[target] = {
                "kind": {WIBO_NAME: "runner", M2C_NAME: "decompiler",
                 PERMUTER_NAME: "permuter"}.get(target, "compiler"),
                "status": "FAILED",
                "required": required,
                "observed": _now(),
                "url": wibo_url() if target == WIBO_NAME
                else (M2C_URL if target == M2C_NAME
                      else (PERMUTER_URL if target == PERMUTER_NAME
                            else f"{BASE_URL}/{ARTIFACTS[target]}")),
                "reason": f"{type(exc).__name__}: {exc}",
            }
            label = "REQUIRED" if required else "optional"
            print(f"{target}: {label} fetch failed ({type(exc).__name__}: {exc})", file=sys.stderr)
            if required:
                required_failures.append(target)

    record_state(entries, state_file)
    manifest = write_provenance(state_file, provenance)
    print(f"provenance: {manifest}")
    if required_failures:
        print(f"required artifacts failed: {', '.join(required_failures)}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
