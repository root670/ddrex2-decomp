#!/usr/bin/env python3
"""m2c_draft.py -- a mechanical first draft of one function, seeded by its split.

``m2c`` (matt-kempster/m2c, fetched and digest-pinned by ``tools/toolchain/fetch.py``)
turns assembly into plausible C.  It is a *drafting* aid, never a promotion proof: it
emits ``unk24`` fields, unrolled loops and ``var_N`` temporaries, and this tree's
promotion gate is byte equality (``./ddr verify --tu <tu>``).  What it is good for is
the part that takes longest to get wrong -- the control flow and the call/argument
shape of a hard function -- so a draft is something to edit, not something to trust.

The draft is written to **stdout**, or to ``drafts/`` with ``--out``; no path under
``src/``, ``include/`` or ``asm/`` is accepted, because ``asm/`` is generated (rule 2)
and ``src/`` is the hand-written tree.

Example::

    python3 tools/units/m2c_draft.py AM/s573/doll/ps1lib.c GsInitCoordinate2
    python3 tools/units/m2c_draft.py src/AM/s573/doll/ps1lib.c ps1rsin --out drafts/ps1rsin.c

What is fed to m2c:

* **the function's own split** -- the ``glabel <fn>`` .. ``endlabel <fn>`` block, with
  the preamble (``.include``/``.set``) the split needs, out of
  ``asm/nonmatchings/<segment>/<fn>.s`` (a generated tree; ``./ddr build`` writes it);
* **the types this tree already knows** -- ``include/src/<unit>.h`` and the
  ``include/types/*.h`` headers it includes, flattened for m2c's C parser (it wants a
  preprocessed context).  That is the same evidence a person gathers by hand, so the
  draft's argument and member types are retail's, not invented.

A function whose split is ``dlabel`` (DWARF says subroutine, the bytes are data) is
refused: m2c cannot decompile it, and the refusal is the finding.

Dependencies: none to install.  m2c is pure Python and vendors its own pycparser fork
(BSD-3-Clause) inside the pinned tree; its only declared dependency, ``graphviz``, is used
by ``--visualize`` alone, which this tool never passes.  ``python3 tools/toolchain/fetch.py
m2c`` is the whole setup, and the tree it installs is digest-verified before it runs.
"""

from __future__ import annotations

import argparse
import os
import pathlib
import re
import subprocess
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

from toolchain import fetch  # noqa: E402

#: m2c's PS2 triple: little-endian MIPS (EE), Metrowerks compiler, C.
M2C_TARGET = "mipsee-mwcc-c"

#: Where a draft may be written -- nowhere the build reads.
OUTPUT_DIR = "drafts"
REFUSED_DIRS = ("src", "include", "asm", "config", "build", "out")

#: One ``#include "..."`` line and one preprocessor directive, for the context flattener.
_INCLUDE = re.compile(r'\s*#\s*include\s+"([^"]+)"\s*')
_DIRECTIVE = re.compile(r"\s*#")
_GLABEL = re.compile(r"\s*glabel\s+(\S+)\s*")
_DLABEL = re.compile(r"\s*dlabel\s+(\S+)\s*")


class DraftError(Exception):
    """The draft cannot be produced, and the message says what to do instead."""


def _display(path: pathlib.Path) -> str:
    """``path`` relative to the repository when it is inside it."""
    path = path.resolve()
    return str(path.relative_to(REPO_ROOT)) if path.is_relative_to(REPO_ROOT) else str(path)


def unit_key(unit: str, target) -> str:
    """``src/AM/s573/doll/ps1lib.c`` -> ``AM/s573/doll/ps1lib`` (the header's own key)."""
    candidate = pathlib.Path(unit)
    if candidate.is_absolute():
        candidate = candidate.relative_to(REPO_ROOT) if candidate.is_relative_to(REPO_ROOT) else candidate
    parts = list(candidate.parts)
    if parts and parts[0] == "src":
        parts = parts[1:]
    if not parts:
        raise DraftError(f"{unit!r} names no unit: pass the path as `src/<dir>/<unit>.c` or `<dir>/<unit>.c`")
    if parts[-1].endswith(".c"):
        parts[-1] = parts[-1][: -len(".c")]
    key = "/".join(parts)
    header = unit_header(key, target)
    if header is None:
        raise DraftError(
            f"{unit!r} has no generated header under "
            f"{' or '.join(_display(p / 'src') for p in target.include_paths)}: the unit is "
            f"unknown to the oracle, or its headers are stale -- run `./ddr oracle` (or "
            f"`./ddr build`, which runs it) and check the path"
        )
    return key


def unit_header(key: str, target) -> pathlib.Path | None:
    """``include/src/<key>.h`` searched along the target's include path."""
    for root in target.include_paths:
        candidate = root / "src" / f"{key}.h"
        if candidate.is_file():
            return candidate
    return None


def split_path(function: str, target) -> pathlib.Path:
    """The function's split file, naming ``./ddr build`` when the tree is not generated."""
    geometry = target.geometry_required()
    candidate = REPO_ROOT / "asm" / "nonmatchings" / geometry.code_segment / f"{function}.s"
    if candidate.is_file():
        return candidate
    matches = sorted((REPO_ROOT / "asm" / "nonmatchings").glob(f"*/{function}.s"))
    if len(matches) == 1:
        return matches[0]
    if matches:
        raise DraftError(
            f"{function!r} appears in {len(matches)} splits: "
            + ", ".join(_display(path) for path in matches)
            + "; the function name alone is ambiguous, so nothing is drafted"
        )
    raise DraftError(
        f"no split for {function!r} under asm/nonmatchings/{geometry.code_segment}/: "
        f"`asm/` is generated, so run `./ddr build` first (or check the symbol's spelling "
        f"against {_display(target.symbols)})"
    )


def extract_function(text: str, function: str, split: pathlib.Path) -> str:
    """The split's preamble plus the ``glabel <function>`` .. ``endlabel`` block.

    A split holds one function, but the preamble (``.include "macro.inc"``, ``.set
    noat``, ``.align``) is what m2c needs to read the body, and a file that also holds
    a neighbour's bytes must not have them drafted.
    """
    if any(_DLABEL.fullmatch(line) for line in text.splitlines() if line.strip()):
        raise DraftError(
            f"{_display(split)} is a `dlabel` split: retail's DWARF calls {function!r} a "
            f"subroutine but its bytes are data (.word), so m2c has no instructions to "
            f"decompile -- there is nothing to draft for this symbol"
        )
    lines = text.splitlines(keepends=True)
    stripped = [line.rstrip("\n") for line in lines]
    start = end = None
    first_label = len(lines)
    labels: list[str] = []
    for index, line in enumerate(stripped):
        match = _GLABEL.fullmatch(line)
        if match is None:
            continue
        labels.append(match.group(1))
        first_label = min(first_label, index)
        if match.group(1) == function:
            start = index
        elif start is not None:
            break
    if start is None:
        raise DraftError(
            f"{_display(split)} has no `glabel {function}`: the split defines "
            + (", ".join(labels) if labels else "no glabel at all")
        )
    for index in range(start + 1, len(lines)):
        if re.fullmatch(rf"\s*endlabel\s+{re.escape(function)}\s*", stripped[index]):
            end = index
            break
    if end is None:
        raise DraftError(f"{_display(split)} has `glabel {function}` but no `endlabel {function}`")
    preamble = [line for line in lines[:first_label] if not line.lstrip().startswith("nonmatching")]
    return "".join(preamble + lines[start : end + 1])


def flatten_context(header: pathlib.Path, roots: tuple) -> str:
    """``header`` with its ``#include`` lines replaced by the included files' text.

    m2c reads an already-preprocessed context, so include guards and the other
    directives are dropped; every ``#include "..."`` is resolved against the target's
    include path (then the including file's directory) and visited once.
    """
    lines: list[str] = []
    seen: set = set()

    def visit(path: pathlib.Path) -> None:
        resolved = path.resolve()
        if resolved in seen or not resolved.is_file():
            return
        seen.add(resolved)
        for line in resolved.read_text().splitlines(keepends=True):
            include = _INCLUDE.fullmatch(line)
            if include:
                name = include.group(1)
                for root in (*roots, resolved.parent):
                    candidate = root / name
                    if candidate.is_file():
                        visit(candidate)
                        break
                else:
                    raise DraftError(
                        f"#include \"{name}\" in {_display(resolved)} resolves under none of "
                        f"{', '.join(_display(pathlib.Path(root)) for root in roots)}: the "
                        f"generated headers are incomplete or stale -- run `./ddr oracle`"
                    )
                continue
            if _DIRECTIVE.match(line):
                continue
            lines.append(line)

    visit(header)
    return "".join(lines)


def extract_draft(
    function: str, unit: str, target
) -> tuple[str, pathlib.Path, pathlib.Path, int]:
    """``(draft C, split used, context header, m2c's exit code)`` -- m2c runs only here."""
    install = fetch.installed_m2c()
    key = unit_key(unit, target)
    header = unit_header(key, target)
    assert header is not None  # unit_key proved it
    split = split_path(function, target)
    asm = extract_function(split.read_text(), function, split)
    context = flatten_context(header, target.include_paths)
    if function not in context:
        print(
            f"m2c_draft: {function!r} is not declared by {_display(header)}; running anyway "
            f"(the draft's signature then comes from the call sites)",
            file=sys.stderr,
        )
    with tempfile.TemporaryDirectory(prefix="m2c_draft-") as scratch:
        asm_path = pathlib.Path(scratch) / f"{function}.s"
        context_path = pathlib.Path(scratch) / f"{key.replace('/', '_')}.c"
        asm_path.write_text(asm)
        context_path.write_text(context)
        command = [
            sys.executable,
            "-B",
            str(install / fetch.M2C_ENTRY),
            "-t",
            M2C_TARGET,
            "-f",
            function,
            "--no-cache",
            "--context",
            str(context_path),
            str(asm_path),
        ]
        environment = dict(os.environ, PYTHONDONTWRITEBYTECODE="1")
        try:
            result = subprocess.run(
                command, capture_output=True, text=True, env=environment, timeout=300
            )
        except (OSError, subprocess.SubprocessError) as exc:
            raise DraftError(f"m2c at {_display(install)} could not run: {exc}") from exc
    if result.returncode != 0:
        sys.stderr.write(result.stderr)
        print(
            f"m2c_draft: m2c exited {result.returncode}; its output below is what it managed",
            file=sys.stderr,
        )
    return result.stdout, split, header, result.returncode


def output_path(destination: str | None, function: str) -> pathlib.Path | None:
    """Resolve ``--out`` and refuse any path the build reads (``src/`` above all)."""
    if destination is None:
        return None
    path = pathlib.Path(destination)
    if path.parts and path.parts[0] in REFUSED_DIRS:
        raise DraftError(
            f"--out {destination!r} names a tree the build reads ({path.parts[0]}/); a draft "
            f"is never written there -- write it under {OUTPUT_DIR}/ or leave --out off"
        )
    if not path.is_absolute():
        path = REPO_ROOT / path
    if not path.is_relative_to(REPO_ROOT / OUTPUT_DIR):
        raise DraftError(
            f"--out {destination!r} is outside {OUTPUT_DIR}/; a draft belongs there (or on "
            f"stdout), so nothing lands in the hand-written tree"
        )
    if path.name != f"{function}.c" and not path.suffix:
        path = path / f"{function}.c"
    return path


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Draft one function's C with m2c, from its split and this tree's types.",
        usage="%(prog)s [-t NAME] <unit> <function> [--out drafts/<function>.c]",
    )
    parser.add_argument("unit", help="translation unit: src/<dir>/<unit>.c, or <dir>/<unit>")
    parser.add_argument("function", help="the symbol to draft (its split's `glabel` name)")
    parser.add_argument(
        "--target", default=None, help="the registered target (default: this tree's)"
    )
    parser.add_argument(
        "--out",
        default=None,
        metavar="PATH",
        help=f"write the draft here instead of stdout (must be inside {OUTPUT_DIR}/)",
    )
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    from config import targets

    try:
        target = targets.get(args.target)
        draft, split, header, status = extract_draft(args.function, args.unit, target)
        destination = output_path(args.out, args.function)
    except targets.UnknownTarget as exc:
        print(f"m2c_draft: {exc}", file=sys.stderr)
        return 2
    except fetch.FetchError as exc:
        print(f"m2c_draft: {exc}", file=sys.stderr)
        return 2
    except (DraftError, OSError, targets.NotMeasured) as exc:
        print(f"m2c_draft: {exc}", file=sys.stderr)
        return 2
    if destination is None:
        sys.stdout.write(draft)
    else:
        try:
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(draft)
        except OSError as exc:
            print(f"m2c_draft: cannot write {_display(destination)}: {exc}", file=sys.stderr)
            return 2
        print(
            f"m2c_draft: {args.function} -> {_display(destination)} "
            f"(split {_display(split)}, context {_display(header)})",
            file=sys.stderr,
        )
    return 0 if status == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
