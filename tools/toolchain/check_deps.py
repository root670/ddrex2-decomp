#!/usr/bin/env python3
"""Verify the host tools the build and the matching loop invoke by name.

The build calls ``mips-linux-gnu-as``/``-ld``/``-objcopy``, ``ninja``,
``python3 -m splat`` and ``objdiff-cli``; each is installed by the developer with the host
package manager, never vendored (``.gitignore`` ignores ``toolchain/``).  This module is
the single place that says what "installed" means:

* :func:`require` probes every tool, returns its version, and raises
  :class:`MissingDependency` naming the *exact* command that provides the tool when one is
  absent — it never installs anything and never touches the network, so a test may call it.
* :func:`assembles_r5900` proves the assembler really accepts the retail flag set
  (``-EL -march=5900 -mabi=eabi``) by assembling a three-word source and reading the object
  back.
* :func:`record` rewrites the host-tool section of ``toolchain/PROVENANCE.txt`` with the
  observed version, path, digest and how each tool was obtained.  ``fetch.py`` owns that
  file and carries the section across a refetch, so a compiler re-fetch never erases it.

Usage::

    python3 tools/toolchain/check_deps.py             # probe, record, report
    python3 tools/toolchain/check_deps.py --check     # probe only, do not write the manifest
"""

from __future__ import annotations

import argparse
import datetime
import importlib.metadata
import importlib.util
import pathlib
import platform
import shutil
import subprocess
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
if str(REPO_ROOT / "tools") not in sys.path:  # `python3 tools/toolchain/check_deps.py`
    sys.path.insert(0, str(REPO_ROOT / "tools"))

from toolchain import fetch

PROVENANCE_FILE = fetch.PROVENANCE_FILE
HOST_TOOLS_BEGIN = fetch.HOST_TOOLS_BEGIN
HOST_TOOLS_END = fetch.HOST_TOOLS_END

# The remedies below are the routes that actually provide each tool on this host (macOS
# arm64).  They are printed verbatim when the tool is missing, so they must stay runnable.
BREW_BINUTILS = "brew install mips-linux-gnu-binutils"
BREW_NINJA = "brew install ninja"
# splat64 declares spimdisasm under its extra, not as a plain dependency, yet splat imports
# it unconditionally: `pip install splat64` alone yields a `python3 -m splat` that dies with
# ModuleNotFoundError.  The mips extra is what makes the command work.
PIP_SPLAT = "python3 -m pip install --user 'splat64[mips]'"
SPLAT_PACKAGE = "splat64"

OBJDIFF_VERSION = "v3.8.2"
OBJDIFF_RELEASES = "https://github.com/encounter/objdiff/releases"
OBJDIFF_ASSETS = {
    ("darwin", "arm64"): "objdiff-cli-macos-arm64",
    ("darwin", "x86_64"): "objdiff-cli-macos-x86_64",
    ("linux", "aarch64"): "objdiff-cli-linux-aarch64",
    ("linux", "x86_64"): "objdiff-cli-linux-x86_64",
}
CARGO_OBJDIFF = "cargo install objdiff-cli"
HOMEBREW_CELLAR = pathlib.Path("/opt/homebrew/Cellar")

DESCRIPTION = "Verify the host assembler, linker, objcopy, ninja, splat and objdiff are installed."
TIMEOUT = 60

# The three words the R5900 check assembles.  ``jr $ra`` makes the object a complete
# function, so binutils has nothing to report at the end of the section.
R5900_SOURCE = "lui $t0, 0x1234\naddiu $t1, $t0, 0x5678\njr $ra\n"
R5900_AS_FLAGS = ("-EL", "-march=5900", "-mabi=eabi")


class MissingDependency(RuntimeError):
    """A tool the build calls by name is absent; ``remedy`` is the command that provides it."""

    def __init__(self, what: str, remedy: str) -> None:
        super().__init__(f"{what} is not installed — remedy: {remedy}")
        self.what = what
        self.remedy = remedy


class Tool:
    """One host tool: an executable on ``PATH``, or a module run as ``python3 -m <module>``."""

    def __init__(
        self,
        key: str,
        remedy: str,
        *,
        binary: str | None = None,
        module: str | None = None,
        package: str | None = None,
    ) -> None:
        assert (binary is None) != (module is None), f"{key}: exactly one of binary/module"
        self.key = key
        self.remedy = remedy
        self.binary = binary
        self.module = module
        self.package = package or module

    def argv(self, resolved: str) -> list[str]:
        if self.module is not None:
            return [sys.executable, "-m", self.module, "--version"]
        return [resolved, "--version"]

    def __repr__(self) -> str:  # pragma: no cover - debugging aid
        return f"Tool({self.key!r}, binary={self.binary!r}, module={self.module!r})"


def objdiff_asset() -> str | None:
    """The objdiff release asset for this machine, or None when the release has none."""
    return OBJDIFF_ASSETS.get((sys.platform, platform.machine()))


def objdiff_remedy() -> str:
    """How to install ``objdiff-cli`` here: the release asset when one exists, else cargo."""
    asset = objdiff_asset()
    if asset is None:
        return CARGO_OBJDIFF
    url = f"{OBJDIFF_RELEASES}/download/{OBJDIFF_VERSION}/{asset}"
    return f"curl -sL -o ~/.local/bin/objdiff-cli {url} && chmod +x ~/.local/bin/objdiff-cli  (or: {CARGO_OBJDIFF})"


OBJDIFF_REMEDY = objdiff_remedy()

TOOLS = (
    Tool("as", BREW_BINUTILS, binary="mips-linux-gnu-as"),
    Tool("ld", BREW_BINUTILS, binary="mips-linux-gnu-ld"),
    Tool("objcopy", BREW_BINUTILS, binary="mips-linux-gnu-objcopy"),
    Tool("ninja", BREW_NINJA, binary="ninja"),
    Tool("splat", PIP_SPLAT, module="splat", package=SPLAT_PACKAGE),
    Tool("objdiff", OBJDIFF_REMEDY, binary="objdiff-cli"),
)
TOOLS_BY_KEY = {tool.key: tool for tool in TOOLS}


def _now() -> str:
    return datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def which(name: str) -> str | None:
    """Resolve an executable on ``PATH`` (a seam: tests replace this, not the host)."""
    return shutil.which(name)


def find_spec(name: str):
    """Resolve an importable module (a seam: tests replace this, not the host)."""
    return importlib.util.find_spec(name)


def resolve(tool: Tool) -> str:
    """Return the tool's executable path (or module name), or raise :class:`MissingDependency`."""
    if tool.module is not None:
        if find_spec(tool.module) is None:
            raise MissingDependency(f"python module {tool.module!r} (`python3 -m {tool.module}`)", tool.remedy)
        return tool.module
    assert tool.binary is not None
    found = which(tool.binary)
    if found is None:
        raise MissingDependency(f"{tool.binary!r} (looked up on PATH)", tool.remedy)
    return found


def version(tool: Tool) -> str:
    """Run the tool's ``--version`` and return the first line."""
    resolved = resolve(tool)
    argv = tool.argv(resolved)
    try:
        proc = subprocess.run(argv, capture_output=True, text=True, timeout=TIMEOUT)
    except OSError as exc:
        raise MissingDependency(f"{tool.key} (`{' '.join(argv)}` could not run: {exc})", tool.remedy) from exc
    first = (proc.stdout or "").strip().splitlines()
    if proc.returncode != 0 or not first:
        detail = (proc.stderr or proc.stdout or "").strip().splitlines()
        suffix = f": {detail[0]}" if detail else ""
        raise MissingDependency(
            f"{tool.key} (`{' '.join(argv)}` exited {proc.returncode}{suffix})", tool.remedy
        )
    return first[0]


def require() -> dict[str, str]:
    """Return ``{key: version}`` for every tool the build calls, raising for the first absence."""
    return {tool.key: version(tool) for tool in TOOLS}


# ---------------------------------------------------------------------------
# R5900 flag check
# ---------------------------------------------------------------------------


def assembles_r5900(workdir: pathlib.Path | None = None) -> bool:
    """True only when ``as`` accepts the retail flags and writes a little-endian MIPS object.

    ``workdir`` keeps the generated ``r5900.s``/``r5900.o`` for inspection; without it the
    pair is assembled in a temporary directory that is removed again.
    """
    if workdir is not None:
        return _assemble(pathlib.Path(workdir))
    with tempfile.TemporaryDirectory(prefix="r5900-") as tmp:
        return _assemble(pathlib.Path(tmp))


def _assemble(workdir: pathlib.Path) -> bool:
    assembler = which("mips-linux-gnu-as")
    if assembler is None:
        return False
    workdir.mkdir(parents=True, exist_ok=True)
    source = workdir / "r5900.s"
    obj = workdir / "r5900.o"
    source.write_text(R5900_SOURCE)
    if obj.exists():
        obj.unlink()
    proc = subprocess.run(
        [assembler, *R5900_AS_FLAGS, "-o", str(obj), str(source)],
        capture_output=True,
        text=True,
        timeout=TIMEOUT,
    )
    if proc.returncode != 0 or not obj.is_file() or obj.stat().st_size == 0:
        print(
            f"mips-linux-gnu-as {' '.join(R5900_AS_FLAGS)} failed (exit {proc.returncode}): "
            + (proc.stderr or "").strip(),
            file=sys.stderr,
        )
        return False
    header = obj.read_bytes()[:20]
    return header[:4] == b"\x7fELF" and header[5] == 1 and int.from_bytes(header[18:20], "little") == 8


# ---------------------------------------------------------------------------
# Provenance manifest
# ---------------------------------------------------------------------------


def _origin(tool: Tool, path: pathlib.Path) -> str:
    """How the binary at ``path`` was obtained, derived from where it lives."""
    resolved = path.resolve()
    if resolved.is_relative_to(HOMEBREW_CELLAR):
        parts = resolved.relative_to(HOMEBREW_CELLAR).parts
        return f"Homebrew {parts[0]} {parts[1]}" if len(parts) > 1 else "Homebrew"
    if resolved.is_relative_to(pathlib.Path.home() / ".cargo" / "bin"):
        return CARGO_OBJDIFF
    if (
        tool.key == "objdiff"
        and objdiff_asset() is not None
        and resolved.is_relative_to(pathlib.Path.home() / ".local" / "bin")
    ):
        return f"download {objdiff_asset()} {OBJDIFF_VERSION}"
    return fetch.IN_PLACE


def _entry(tool: Tool, ver: str) -> dict[str, str]:
    """One provenance entry: what was observed, where it came from, how to obtain it again."""
    entry = {"observed": _now(), "version": ver, "required": "yes", "obtained": tool.remedy.split("  (")[0]}
    if tool.module is not None:
        spec = find_spec(tool.module)
        package_dir = pathlib.Path(spec.origin or "").parent if spec else pathlib.Path("")
        try:
            installed = importlib.metadata.version(tool.package)  # type: ignore[arg-type]
        except importlib.metadata.PackageNotFoundError:  # pragma: no cover - broken install
            installed = "unknown"
        entry.update(
            module=tool.module,
            path=str(package_dir),
            package=f"{tool.package} {installed}",
            origin=f"pip --user {tool.package} {installed}",
        )
        return entry
    assert tool.binary is not None
    path = pathlib.Path(which(tool.binary) or "")
    entry.update(
        path=str(path),
        sha256=fetch.sha256_file(path.resolve()),
        origin=_origin(tool, path),
    )
    return entry


def _host_tools_section(entries: dict[str, dict[str, str]]) -> str:
    lines = [
        HOST_TOOLS_BEGIN,
        "# Host tools are installed by the developer with the host package manager, never",
        "# vendored. This section is rewritten by tools/toolchain/check_deps.py and carried",
        "# across a refetch by fetch.py; every version below was observed on this machine.",
        f"# observed: {_now()}",
        "",
    ]
    for tool in TOOLS:
        entry = entries[tool.key]
        lines.append(f"[host {tool.key}] verified  required={entry['required']}")
        for key in ("observed", "version", "module", "path", "package", "sha256", "obtained", "origin"):
            if entry.get(key):
                lines.append(f"  {key:<15} {entry[key]}")
        lines.append("")
    lines.append(HOST_TOOLS_END)
    return "\n".join(lines) + "\n"


def record(path: pathlib.Path | None = None, entries: dict[str, dict[str, str]] | None = None) -> dict[str, str]:
    """Rewrite the host-tool section of ``PROVENANCE.txt`` and return ``{key: version}``.

    Everything before the section (``fetch.py``'s compiler record) is preserved verbatim and
    the section is *replaced*, so reruns are idempotent instead of appending twice.
    """
    manifest = pathlib.Path(path) if path is not None else PROVENANCE_FILE
    if entries is None:
        entries = {tool.key: _entry(tool, version(tool)) for tool in TOOLS}
    existing = manifest.read_text() if manifest.is_file() else ""
    head = existing[: existing.find(HOST_TOOLS_BEGIN)] if HOST_TOOLS_BEGIN in existing else existing
    head = head.rstrip("\n")
    manifest.parent.mkdir(parents=True, exist_ok=True)
    manifest.write_text((head + "\n\n" if head else "") + _host_tools_section(entries))
    return {key: entry["version"] for key, entry in entries.items()}


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=DESCRIPTION)
    parser.add_argument("--check", action="store_true", help="probe only; do not write the manifest")
    parser.add_argument(
        "--provenance", default=None, help="manifest to write (default: toolchain/PROVENANCE.txt)"
    )
    args = parser.parse_args(argv)

    try:
        entries = {tool.key: _entry(tool, version(tool)) for tool in TOOLS}
    except MissingDependency as exc:
        print(f"host dependency missing: {exc}", file=sys.stderr)
        return 1

    for tool in TOOLS:
        entry = entries[tool.key]
        print(f"{tool.key:<8} {entry['version']}  [{entry['origin']}]")

    if not assembles_r5900():
        print("mips-linux-gnu-as cannot assemble the R5900 probe", file=sys.stderr)
        return 1
    if not args.check:
        manifest = pathlib.Path(args.provenance) if args.provenance else PROVENANCE_FILE
        record(path=manifest, entries=entries)
        print(f"provenance: {manifest}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
