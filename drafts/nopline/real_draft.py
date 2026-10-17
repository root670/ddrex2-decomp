#!/usr/bin/env python3
"""nopline real -- the end-to-end check on unit-l's own draft.

Reads `git show wt-unit-l:drafts/dexport.c` (read-only; that branch's worktree is never touched),
injects (a) `__asm__ ("nop");` on line 103 inside the `if` body and (b) a `#line 104` marker on the
`do` statement's closing brace/`while` clause, then compares the built `ps2dancerInitHide` against
retail's own bytes and retail's own `.line` chunk for the function:

    retail bytes  = orig/SLUS_211.74 [0x1CF1B0, 0x1CF220)
    retail .line  = the CU chunk at 0xA9DE (base 0x1CF1B0, 8 records)

    python3 drafts/nopline/real_draft.py
"""

from __future__ import annotations

import pathlib
import subprocess
import sys
import tempfile

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
for _extra in (str(REPO_ROOT / "tools" / "oracle"), str(REPO_ROOT / "tools"), str(REPO_ROOT)):
    if _extra not in sys.path:
        sys.path.insert(0, _extra)

import elf  # noqa: E402
from toolchain import fetch, probe  # noqa: E402

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import measure  # noqa: E402

BUILD = "3.0-011126"
RETAL = REPO_ROOT / "orig" / "SLUS_211.74"
BASE, END = 0x1CF1B0, 0x1CF220
LINE_CHUNK, LINE_LEN = 0xA9DE, 0x58

DRAFT = subprocess.run(["git", "show", "wt-unit-l:drafts/dexport.c"], cwd=REPO_ROOT,
                       capture_output=True, text=True, check=True).stdout

ASM_AT_103 = ("\n#line 103\n        }\n#line 104",
              "\n#line 103\n            __asm__ (\"nop\");\n        }\n#line 104")
RELINE_DO = ("#line 104\n        i++;\n    } while (i < 0x2D);",
             "#line 104\n        i++;\n#line 104\n    } while (i < 0x2D);")


def variant(*edits) -> str:
    text = DRAFT
    for old, new in edits:
        if old not in text:
            raise SystemExit(f"the draft no longer contains {old!r}")
        text = text.replace(old, new)
    return text


def build(text: str, name: str):
    directory = pathlib.Path(tempfile.mkdtemp(prefix="nopline-"))
    src, obj = directory / f"{name}.c", directory / f"{name}.o"
    src.write_text(text)
    flags = ["-c", "-lang", "c", "-O3", "-g", f"-I{REPO_ROOT / 'include'}"]
    probe.compile(src, obj, fetch.compiler(BUILD), fetch.wibo(), flags)
    e = elf.Elf(obj)
    text_indexes = [i for i, s in enumerate(e.sections) if s.name == ".text"]
    by_index = {i: e.sections[i] for i in text_indexes}
    body, rows = None, None
    for sym in e.symbols:
        if sym.shndx in by_index and sym.name == "ps2dancerInitHide":
            section = by_index[sym.shndx]
            body = bytes(e.data[section.offset + sym.value:section.offset + sym.value + sym.size])
    for section in e.sections:
        if section.name == ".line":
            candidate = measure.decode_line(e.data, section.offset, section.size)
            if candidate and candidate[0][1] == 98:
                rows = candidate
    return body, rows


def main() -> int:
    retail_elf = elf.Elf(RETAL)
    retail = retail_elf.read(BASE, END - BASE)
    line_section = next(s for s in retail_elf.sections if s.name == ".line")
    retail_rows = measure.decode_line(retail_elf.data, line_section.offset + LINE_CHUNK, LINE_LEN)
    print("retail .text 0x%X, records %s" %
          (len(retail), " ".join(f"{ln}@{a - BASE:#x}" for a, ln in retail_rows)))

    for name, text in (("committed", DRAFT),
                       ("+asm@103", variant(ASM_AT_103)),
                       ("+asm@103+reline", variant(ASM_AT_103, RELINE_DO))):
        body, rows = build(text, name.replace("+", "").replace("@", "_"))
        print(f"{name:<16} .text 0x{len(body):X}, records "
              + " ".join(f"{ln}@{a:#x}" for a, ln in rows))
        if name == "+asm@103+reline":
            mask = bytearray(retail)
            mine = bytearray(body)
            for start, length in ((0x10, 4), (0x34, 8)):
                for i in range(start, start + length):
                    mask[i] = mine[i] = 0
            print(f"  .text identical to retail modulo the two relocation sites: "
                  f"{bytes(mask) == bytes(mine)}")
            print(f"  .line identical to retail: "
                  f"{[(a, l) for a, l in rows] == [(a - BASE, l) for a, l in retail_rows]}")
            print(f"  record 103: {[(a, l) for a, l in rows if l == 103]} "
                  f"(retail {[(a - BASE, l) for a, l in retail_rows if l == 103]})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
