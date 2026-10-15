"""Per-translation-unit C skeletons -> `include/<relpath>.h`.

The text of each header is produced by `dwarf1.py`'s `header --cu` command, so
there is exactly one renderer: the CLI walks all 57 translation units and
writes what the same `render` call returns.  Hex offsets are upper-cased for
the generated tree (`0x0021C410-0x0021C41C`).

These headers are generated artifacts.  `include/README.md` says so; hand
edits belong in `src/` or `include/` files that are not generated.
"""
import argparse, contextlib, io, pathlib, re, sys

import dwarf1
from dwarf1 import Dwarf

import emit_cus

CACHE = {}

_H = re.compile(r"0x([0-9a-fA-F]+)")


class NoSuchUnit(LookupError):
    """No translation unit (or included source file) matches the string."""


def dwarf(elf_path):
    """The parsed ELF, cached: the CLI renders 57 headers from one parse."""
    key = str(elf_path)
    if key not in CACHE:
        CACHE[key] = Dwarf(key)
    return CACHE[key]


def header_text(dw, cu_substring):
    """`dwarf1 header --cu <cu_substring>` for one ELF, as a string."""
    out = io.StringIO()
    args = argparse.Namespace(cu=cu_substring, overlay=None)
    with contextlib.redirect_stdout(out):
        rc = dwarf1.cmd_header(dw, args)
    text = out.getvalue()
    if rc != 0 or not text.strip():
        raise NoSuchUnit(f"no translation unit matches {cu_substring!r}")
    return text


def render(elf_path, cu_substring):
    """The header text for the translation unit whose source path contains
    `cu_substring` (a full path or file name, as `dwarf1 header --cu` takes)."""
    return _H.sub(lambda m: "0x" + m.group(1).upper(),
                  header_text(dwarf(elf_path), cu_substring))


def header_for(relpath):
    """`src/sys/sys_scf.c` -> `src/sys/sys_scf.h`."""
    return re.sub(r"\.[^./]+$", "", relpath) + ".h"


def write_all(elf_path, outdir):
    """Write `include/<relpath>.h` for every translation unit; returns paths."""
    dw = dwarf(elf_path)
    outdir = pathlib.Path(outdir)
    written, seen = [], {}
    for tu in dw.tus:
        rel = emit_cus.relpath(tu.name)
        dest = outdir / header_for(rel)
        if dest in seen:
            raise NoSuchUnit(f"{tu.name} and {seen[dest]} both write {dest}")
        seen[dest] = tu.name
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text(render(elf_path, tu.name))
        written.append(dest)
    readme = outdir / "README.md"
    readme.write_text(README)
    return written


README = """# include/

Generated per-translation-unit C skeletons recovered from `orig/SLUS_207.11`
by `tools/oracle/emit_headers.py`.  Do not hand-edit these files: a fresh run
of the oracle overwrites them.  Hand-written declarations and any corrected
reconstruction live under `src/` or in headers outside this generated set.
"""


if __name__ == "__main__":
    elf = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else "include"
    paths = write_all(elf, out)
    print(f"{len(paths)} headers written -> {out}")
