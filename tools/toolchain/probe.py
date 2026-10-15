#!/usr/bin/env python3
"""Run the vendored ``mwccps2.exe`` under wibo and read back what it produced.

This is the last unknown before the build system is wired up: it proves that the
hash-verified CodeWarrior 2.4 compiler *runs* on this host through wibo, accepts the
retail flag set, and emits Metrowerks DWARF 1 (``.debug``/``.line`` with section type
``0x70000005``, ``SHT_MIPS_DEBUG``) plus the per-function ``.text`` symbols named by the
oracle's DWARF.

Two facts measured on the archived tools, both visible in ``toolchain/PROVENANCE.txt``:

* ``mwccps2.exe -c`` writes ``.comment`` = ``MW MIPS C Compiler (2.4.1.01)\\0``.  The
  string ``PlayStation2`` does not occur anywhere in any vendored ``mwccps2.exe``
  (2.4-001213 and all four alternates), so no compile-only object can carry it.
* ``mwldps2.exe`` merges the compiler ident with its own ``PlayStation2`` entry, which is
  why the retail ELF's 43-byte ``.comment`` is attributed to MWLD in the design spec
  (§2, "compiler linker string").  :func:`link` and :func:`retail_comment` expose that
  half of the string.

The compiler is invoked with ``cwd`` set to the compiler directory — its licence lookup
is directory-relative (R17) — and receives absolute source and object paths, so the same
call works from any working directory.

Usage::

    python3 tools/toolchain/probe.py                 # compile the probe into build/probe/probe.o
    python3 tools/toolchain/probe.py --link          # also link it, to show the retail .comment
"""

from __future__ import annotations

import argparse
import pathlib
import re
import subprocess
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
ORACLE_DIR = REPO_ROOT / "tools" / "oracle"
if str(ORACLE_DIR) not in sys.path:  # the vendored reader, shared with the DWARF oracle
    sys.path.insert(0, str(ORACLE_DIR))
import elf  # noqa: E402

COMPILER_NAME = "mwccps2.exe"
LINKER_NAME = "mwldps2.exe"
DEFAULT_FLAGS = ("-c", "-lang", "c", "-O2", "-g")
PROBE_SOURCE = REPO_ROOT / "tests" / "toolchain" / "probe.c"
PROBE_OBJECT = REPO_ROOT / "build" / "probe" / "probe.o"
PROBE_ELF = REPO_ROOT / "build" / "probe" / "probe.elf"

#: ``SHT_MIPS_DEBUG``: the section type of Metrowerks DWARF 1 in a PS2 ELF.
SHT_MIPS_DEBUG = 0x70000005

#: What MWCC itself writes; what MWLD appends; the retail ELF's whole section.
MWCC_COMMENT = b"MW MIPS C Compiler (2.4.1.01)\x00"
MWLD_COMMENT = b"PlayStation2\x00"
RETAIL_COMMENT = MWCC_COMMENT + MWLD_COMMENT

#: The plan's sanctioned fallback if the archived compiler ever refuses to run.
FLEXLM_FALLBACK = (
    "the community-patched 2.4 build in the Internet Archive item "
    "'metrowerks-ps2-compiler' (Metrowerks PS2/mcwps2r3/)"
)

#: FLEXlm signatures.  Checked only after a non-zero exit, never on a successful run.
_LICENCE_MARKERS = ("flexlm", "licence", "license", "lmgr326b", "licensing")

#: ``### mwccps2.exe Usage Error:\n #   Unknown option 'proc'``
_REJECTED_OPTION = re.compile(r"Unknown option '([^']+)'", re.IGNORECASE)

TIMEOUT = 300


class ProbeError(Exception):
    """The probe could not be compiled or read."""


class CompilerFailed(ProbeError):
    """A tool exited non-zero, or exited zero without writing its output."""


class NothingToBuild(ProbeError):
    """The compiler refused to run over licensing; names the sanctioned fallback."""


def _resolve(path) -> pathlib.Path:
    return pathlib.Path(path).expanduser().resolve()


def _tool(compiler_dir: pathlib.Path, name: str) -> pathlib.Path:
    path = compiler_dir / name
    if not path.is_file():
        raise ProbeError(f"{path} is missing; run tools/toolchain/fetch.py first")
    return path


def _licence_failure(text: str) -> bool:
    lowered = text.lower()
    return any(marker in lowered for marker in _LICENCE_MARKERS)


def _rejected_flag(text: str, flags) -> str | None:
    """The command-line flag the compiler named as unknown, if it named one."""
    match = _REJECTED_OPTION.search(text)
    if match is None:
        return None
    name = match.group(1)
    for flag in flags:
        if flag.lstrip("-").split("=")[0].startswith(name):
            return flag
    return f"-{name}"


def _invoke(wibo_path, compiler_dir: pathlib.Path, tool: str, argv) -> subprocess.CompletedProcess:
    """Run ``wibo <compiler_dir>/<tool> <argv>`` with cwd in the compiler directory."""
    command = [str(_resolve(wibo_path)), str(_tool(compiler_dir, tool)), *argv]
    try:
        return subprocess.run(
            command, cwd=compiler_dir, capture_output=True, text=True, timeout=TIMEOUT
        )
    except subprocess.TimeoutExpired as exc:
        raise CompilerFailed(f"{tool}: timed out after {TIMEOUT}s") from exc
    except OSError as exc:
        raise CompilerFailed(f"{tool}: could not be executed: {exc}") from exc


def _checked(
    result: subprocess.CompletedProcess,
    output: pathlib.Path,
    tool: str,
    flags,
    compiler_dir: pathlib.Path,
) -> None:
    if result.returncode == 0 and output.is_file():
        return
    text = f"{result.stdout}\n{result.stderr}".strip()
    invoked = f"{tool} {' '.join(flags)}" if flags else tool
    if _licence_failure(text):
        raise NothingToBuild(
            f"{tool} in {compiler_dir} failed its FLEXlm licensing check:\n{text}\n"
            f"Sanctioned fallback: {FLEXLM_FALLBACK}"
        )
    rejected = _rejected_flag(text, flags)
    if rejected is not None:
        raise CompilerFailed(
            f"{tool} rejected {rejected!r} (exit {result.returncode}); "
            f"invoked as: {invoked}\n{text}"
        )
    missing = "" if output.is_file() else f" (no output at {output})"
    raise CompilerFailed(f"{invoked}: exit {result.returncode}{missing}\n{text}")


def compile(src, obj, compiler_dir, wibo, flags) -> None:
    """Compile ``src`` to ``obj`` with ``mwccps2.exe`` under wibo.

    ``flags`` is passed through verbatim — a flag the compiler rejects is reported by
    name in :class:`CompilerFailed`, never dropped.  ``compiler_dir`` is the directory
    returned by :func:`fetch.compiler`; ``wibo`` is the path from :func:`fetch.wibo`.
    """
    src = _resolve(src)
    obj = _resolve(obj)
    compiler_dir = _resolve(compiler_dir)
    if not src.is_file():
        raise ProbeError(f"{src} does not exist")
    obj.parent.mkdir(parents=True, exist_ok=True)
    flags = list(flags)
    result = _invoke(wibo, compiler_dir, COMPILER_NAME,
                     [*flags, "-o", str(obj), str(src)])
    _checked(result, obj, COMPILER_NAME, flags, compiler_dir)


def link(objects, out, compiler_dir, wibo, flags=(), entry=None) -> None:
    """Link ``objects`` into ``out`` with ``mwldps2.exe`` under wibo.

    MWLD is what contributes ``PlayStation2`` to ``.comment``; linking is used only to
    show that half of the retail string.  A whole application is not being built, so
    ``entry`` names the symbol MWLD should use instead of the default ``__start``;
    without it MWLD fails on ``undefined: "__start"``.
    """
    compiler_dir = _resolve(compiler_dir)
    out = _resolve(out)
    objects = [_resolve(o) for o in objects]
    for obj in objects:
        if not obj.is_file():
            raise ProbeError(f"{obj} does not exist")
    out.parent.mkdir(parents=True, exist_ok=True)
    flags = list(flags)
    if entry:
        flags += ["-m", entry]
    argv = [*flags, "-o", str(out), *map(str, objects)]
    result = _invoke(wibo, compiler_dir, LINKER_NAME, argv)
    _checked(result, out, LINKER_NAME, flags, compiler_dir)


def retail_comment() -> bytes:
    """The 43-byte ``.comment`` of the retail ELF: MWCC's ident plus MWLD's entry."""
    return RETAIL_COMMENT


def _first(e: elf.Elf, name: str) -> elf.Section | None:
    return next((s for s in e.sections if s.name == name), None)


def inspect(obj) -> dict:
    """Read back a Metrowerks object: ``sections``, ``comment``, ``debug_kind``, ``text``.

    MWCC emits one ``.text``/``.debug``/``.line`` group per function, so section names
    repeat; ``sections`` maps each name to the first occurrence's
    ``(type, size, offset)`` and ``section_names`` lists every occurrence.  ``text``
    maps the name of each symbol defined in a ``.text`` section to its size, and
    ``text_symbols`` is the sorted list of those names.
    """
    path = _resolve(obj)
    if not path.is_file():
        raise ProbeError(f"{path} does not exist")
    e = elf.Elf(path)

    sections: dict[str, tuple[int, int, int]] = {}
    for s in e.sections:
        if s.name:
            sections.setdefault(s.name, (s.type, s.size, s.offset))
    section_names = [s.name for s in e.sections if s.name]

    comment_section = _first(e, ".comment")
    comment = (
        bytes(e.data[comment_section.offset:comment_section.offset + comment_section.size])
        if comment_section
        else b""
    )
    debug_section = _first(e, ".debug")
    debug_kind = elf.SHT.get(debug_section.type, hex(debug_section.type)) if debug_section else None

    text_indexes = {
        i for i, s in enumerate(e.sections)
        if s.name == ".text" or s.name.startswith(".text")
    }
    text = {
        sym.name: sym.size
        for sym in e.symbols
        if sym.shndx in text_indexes and sym.name and sym.type != 3
    }

    return {
        "sections": sections,
        "section_names": section_names,
        "comment": comment,
        "debug_kind": debug_kind,
        "text": text,
        "text_symbols": sorted(text),
    }


def _print_report(info: dict, path: pathlib.Path) -> None:
    print(f"{path}: {len(info['section_names'])} sections")
    print(f"  .comment      {info['comment']!r}")
    print(f"  debug_kind    {info['debug_kind']}")
    for name in (".debug", ".line"):
        section = info["sections"].get(name)
        if section:
            print(f"  {name:<13} type={section[0]:#010x} size={section[1]}")
    print(f"  .text symbols {', '.join(info['text_symbols']) or '(none)'}")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--version", default="2.4-001213", help="compiler build to use")
    parser.add_argument("--source", default=str(PROBE_SOURCE), help="C source to compile")
    parser.add_argument("--object", default=str(PROBE_OBJECT), help="object to write")
    parser.add_argument("--flags", nargs="*", default=list(DEFAULT_FLAGS),
                        help=f"compiler flags (default: {' '.join(DEFAULT_FLAGS)})")
    parser.add_argument("--link", action="store_true",
                        help="also link with mwldps2.exe to show the retail .comment")
    args = parser.parse_args(argv)

    sys.path.insert(0, str(REPO_ROOT / "tools"))
    from toolchain import fetch

    try:
        compiler_dir = fetch.compiler(args.version)
        wibo = fetch.wibo()
        print(f"compiler {compiler_dir}")
        print(f"runner   {wibo}")
        compile(args.source, args.object, compiler_dir, wibo, args.flags)
        info = inspect(args.object)
        print(f"command  {wibo} {compiler_dir / COMPILER_NAME} "
              f"{' '.join(args.flags)} -o {args.object} {args.source}")
        _print_report(info, pathlib.Path(args.object))
        if info["comment"] != MWCC_COMMENT:
            print(f"unexpected .comment {info['comment']!r}", file=sys.stderr)
            return 1
        if info["debug_kind"] != "MIPS_DEBUG":
            print(f".debug is {info['debug_kind']!r}, expected MIPS_DEBUG", file=sys.stderr)
            return 1
        if args.link:
            # No __start exists here; MWLD needs some defined symbol as its entry point.
            entry = info["text_symbols"][0]
            link([args.object], PROBE_ELF, compiler_dir, wibo, entry=entry)
            linked = inspect(PROBE_ELF)
            print(f"linked   {PROBE_ELF}: .comment = {linked['comment']!r}")
            if linked["comment"] != retail_comment():
                print("linked .comment does not match the retail ELF", file=sys.stderr)
                return 1
    except ProbeError as exc:
        print(f"probe failed: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
