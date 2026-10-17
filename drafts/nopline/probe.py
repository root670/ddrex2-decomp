#!/usr/bin/env python3
"""nopline probe -- which C statement compiles to a `.line` record whose code is one `nop`?

Compiles one small C file with the pinned compiler pair and prints, per function, the
`.text` bytes and the DWARF 1 line table, so a construct's line record and its code can be
read off together.

    python3 drafts/nopline/probe.py drafts/nopline/control.c
    python3 drafts/nopline/measure.py            # the whole candidate set, as a table

Read-only w.r.t. the repo: the object goes to a temp dir.
"""

from __future__ import annotations

import pathlib
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

import elf  # noqa: E402
from dwarf1 import Dwarf  # noqa: E402
from toolchain import fetch, probe  # noqa: E402

FLAGS = ("-c", "-lang", "c", "-O3", "-g")
BUILD = "3.0-011126"


def compile_to_object(source: pathlib.Path) -> pathlib.Path:
    compiler_dir = fetch.compiler(BUILD)
    wibo = fetch.wibo()
    out = pathlib.Path(tempfile.mkdtemp(prefix="nopline-")) / (source.stem + ".o")
    probe.compile(source, out, compiler_dir, wibo, list(FLAGS))
    return out


def text_functions(e: elf.Elf):
    """[(name, size, offset)] for the named functions in .text sections, in section order."""
    text_indexes = [i for i, s in enumerate(e.sections)
                    if s.name == ".text" or s.name.startswith(".text")]
    by_index = {i: e.sections[i] for i in text_indexes}
    out = []
    for sym in e.symbols:
        if sym.shndx in by_index and sym.name and sym.type == 2:  # STT_FUNC
            out.append((sym.name, sym.size, by_index[sym.shndx].offset + sym.value))
    return out


def measure(source: pathlib.Path, label: str | None = None) -> dict:
    """Compile `source`; return {func: (hex, [(addr, line)])} for each function in it."""
    e = elf.Elf(compile_to_object(source))
    data = e.data
    result = {"label": label or source.stem, "source": str(source), "funcs": {}}
    for name, size, off in text_functions(e):
        result["funcs"][name] = (bytes(data[off:off + size]).hex(), [])
    d = Dwarf(e)
    for cu in d.cus:
        rows = d.line_table(cu)
        if not rows:
            continue
        key = cu.name
        # function CUs are named after the file; match them to the single function
        if len(result["funcs"]) == 1:
            key = next(iter(result["funcs"]))
        if key in result["funcs"]:
            hexbytes, _ = result["funcs"][key]
            result["funcs"][key] = (hexbytes, [(a, ln) for a, ln in rows])
    return result


def words(hexbytes: str):
    return [hexbytes[i:i + 8] for i in range(0, len(hexbytes), 8)]


def show(source: pathlib.Path) -> None:
    m = measure(source)
    print(f"=== {m['label']}  ({source})")
    for name, (hexbytes, rows) in m["funcs"].items():
        w = words(hexbytes)
        print(f"  func {name} size=0x{len(w) * 4:X} ({len(w)} words)")
        for i in range(0, len(w), 4):
            print("    " + " ".join(w[i:i + 4]))
        print(f"  line records ({len(rows)}): " +
              " ".join(f"{ln}@0x{a:X}" for a, ln in rows))


def main() -> int:
    for s in sys.argv[1:]:
        show(pathlib.Path(s).resolve())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
