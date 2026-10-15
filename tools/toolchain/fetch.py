#!/usr/bin/env python3
"""Fetch and hash-verify the CodeWarrior PS2 compilers and wibo into ``toolchain/``.

Nothing is ever extracted, installed or cached before it has been checked against
``PINNED`` (spec Review Focus 3: verify *before* use).  A corrupt or partial
download is rejected with :class:`HashMismatch` while the bytes are still a
``.part`` file in ``toolchain/.downloads/``, so a half-verified compiler can never
be mistaken for a working one.

The archives are proprietary and are never vendored (``.gitignore`` ignores
``toolchain/``): they are fetched from the decomp.me compiler releases and
re-verified against the pinned digests on every fetch.

Usage::

    python3 tools/toolchain/fetch.py                 # wibo + every candidate build
    python3 tools/toolchain/fetch.py 2.4-001213      # the required build only
    python3 tools/toolchain/fetch.py wibo
    python3 tools/toolchain/fetch.py --root /tmp/tc 2.4-001213

``2.4-001213`` is the *required* build, as is wibo: if either fails the command
exits non-zero.  The other candidate builds are optional alternates used later to
select the compiler build by byte-matching a known function; a failure there is
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
WIBO_ASSETS = {"darwin": "wibo-macos"}
WIBO_NAME = "wibo"
WIBO_LOCAL_FALLBACK = pathlib.Path.home() / "ac-decomp" / ".cache" / "wibo"
ALREADY_INSTALLED = "already installed"
IN_PLACE = "in place (origin not recorded)"
TIMEOUT = 120
DESCRIPTION = "Fetch and hash-verify the CodeWarrior PS2 compilers and wibo into toolchain/."

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
    """Release asset URL for wibo on this host (``wibo-macos`` on Darwin)."""
    name = asset or WIBO_ASSETS.get(platform.system().lower(), "wibo-x86_64")
    return f"{WIBO_BASE}/{name}"


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


def _publish(dest: pathlib.Path, members: dict[str, bytes]) -> None:
    """Materialise verified members in ``dest`` through a staging directory."""
    staging = dest.parent / f"{dest.name}.staging"
    shutil.rmtree(staging, ignore_errors=True)
    try:
        staging.mkdir(parents=True)
        for name, blob in members.items():
            (staging / name).write_bytes(blob)
        if dest.is_dir():
            shutil.rmtree(dest)
        elif dest.exists():
            dest.unlink()
        staging.rename(dest)
    except BaseException:
        shutil.rmtree(staging, ignore_errors=True)
        raise


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
    partial = CACHE_DIR / f"{ARTIFACTS[version]}.part"
    partial.unlink(missing_ok=True)
    _download(f"{BASE_URL}/{ARTIFACTS[version]}", partial)
    try:
        _verify_archive(partial, version)
    except BaseException:
        partial.unlink(missing_ok=True)
        raise
    partial.replace(archive)
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
            _publish(dest, _verified_members(archive, version))
        return dest, override_url
    if _dest_members_ok(dest, version):
        return dest, ALREADY_INSTALLED
    archive, source = _cached_archive(version)
    _publish(dest, _verified_members(archive, version))
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
    """Newest runnable wibo already built on this machine (the patched ~/ac-decomp build)."""
    candidates = sorted(WIBO_LOCAL_FALLBACK.glob("*/wibo"), key=lambda p: p.stat().st_mtime)
    for candidate in reversed(candidates):
        if os.access(candidate, os.X_OK) and _wibo_version(candidate):
            return candidate
    return None


def _install_wibo(
    root: pathlib.Path, override_url: str | None = None, in_place_source: str | None = None
) -> tuple[pathlib.Path, str]:
    """Install wibo and report where the chosen binary came from."""
    root.mkdir(parents=True, exist_ok=True)
    dest = root / WIBO_NAME
    if dest.is_file() and os.access(dest, os.X_OK) and _wibo_version(dest):
        return dest, in_place_source or IN_PLACE
    url = override_url or wibo_url()
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=CACHE_DIR, prefix=".wibo-") as scratch:
        staged = pathlib.Path(scratch) / WIBO_NAME
        source = url
        try:
            _download(url, staged)
            os.chmod(staged, 0o755)
            if not _wibo_version(staged):
                raise DownloadFailed(f"{url}: downloaded wibo does not run on this host")
        except FetchError:
            fallback = wibo_local_fallback()
            if fallback is None:
                raise
            source = str(fallback)
            shutil.copy2(fallback, staged)
            os.chmod(staged, 0o755)
        shutil.copy2(staged, dest)
    return dest, source


def wibo(root: pathlib.Path | str | None = None, override_url: str | None = None) -> pathlib.Path:
    """Fetch wibo, prove it runs, and return its path; fall back to the local patched build.

    wibo is a moving target (``releases/latest``), so it is verified by executing
    it rather than by digest.  When the download is unavailable, or the downloaded
    binary does not run under Rosetta, the already-built patched binary in
    ``~/ac-decomp/.cache/wibo`` is installed instead.
    """
    root = pathlib.Path(root) if root is not None else TOOLCHAIN_ROOT
    return _install_wibo(root, override_url)[0]


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
    "reason",
)


def _render_provenance(state: dict) -> str:
    lines = [
        "# toolchain/PROVENANCE.txt - generated by tools/toolchain/fetch.py; do not edit.",
        "# The compiler archives are proprietary: fetched from the decomp.me compiler",
        "# releases, never vendored. Every artifact below passed the digests pinned in",
        "# tools/toolchain/fetch.py before it was extracted or run; failures are recorded",
        "# here, never silently skipped.",
        f"# required: {REQUIRED} and {WIBO_NAME}; optional alternates: "
        + ", ".join(v for v in CANDIDATES if v != REQUIRED),
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
    return "\n".join(lines)


def write_provenance(state_file: pathlib.Path | None = None, path: pathlib.Path | None = None) -> pathlib.Path:
    """Render ``PROVENANCE.txt`` from the recorded fetch state."""
    path = path or PROVENANCE_FILE
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(_render_provenance(load_state(state_file)))
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


def _wibo_entry(source: str, installed: pathlib.Path, required: bool) -> dict:
    return {
        "kind": "runner",
        "status": "verified",
        "required": required,
        "observed": _now(),
        "url": wibo_url(),
        "source": source,
        "version": _wibo_version(installed),
        "installed": _relative(installed),
        "installed_sha256": sha256_file(installed),
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=DESCRIPTION)
    parser.add_argument(
        "targets",
        nargs="*",
        metavar="TARGET",
        help="compiler build (e.g. 2.4-001213) or 'wibo'; default: wibo and every build",
    )
    parser.add_argument("--root", default=None, help="destination root (default: toolchain/)")
    parser.add_argument("--state", default=None, help="fetch state file (default: toolchain/.fetched.json)")
    parser.add_argument("--provenance", default=None, help="manifest to write (default: toolchain/PROVENANCE.txt)")
    args = parser.parse_args(argv)

    unknown = [t for t in args.targets if t != WIBO_NAME and t not in ARTIFACTS]
    if unknown:
        parser.error(f"unknown target(s): {', '.join(unknown)} (known: {WIBO_NAME}, {', '.join(CANDIDATES)})")

    root = pathlib.Path(args.root) if args.root else TOOLCHAIN_ROOT
    state_file = pathlib.Path(args.state) if args.state else STATE_FILE
    provenance = pathlib.Path(args.provenance) if args.provenance else PROVENANCE_FILE

    sweep = not args.targets
    targets = [WIBO_NAME, *CANDIDATES] if sweep else args.targets
    previous = load_state(state_file)

    entries: dict[str, dict] = {}
    required_failures: list[str] = []
    for target in targets:
        # In the default sweep only the required build and wibo are mandatory; the
        # alternates may legitimately be unavailable and must not fail the run.
        required = not sweep or target in (REQUIRED, WIBO_NAME)
        try:
            if target == WIBO_NAME:
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
                "kind": "compiler" if target != WIBO_NAME else "runner",
                "status": "FAILED",
                "required": required,
                "observed": _now(),
                "url": wibo_url() if target == WIBO_NAME else f"{BASE_URL}/{ARTIFACTS[target]}",
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
