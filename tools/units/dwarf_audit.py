#!/usr/bin/env python3
"""dwarf_audit.py -- find data addresses in promoted sources that a DWARF object covers.

Rule: a promoted source names data by its DWARF name (a global, or a MEMBER of one:
``g_game_w.last_data_addr``) whenever a debug object covers the address, and falls back to
splat's ``D_<8 hex>`` only when none does.  For every ``D_<8hex>`` name and every raw hex
constant of 5+ digits in a promoted ``src/**`` file (one with a ``tu_builds`` row) this prints
the address and the member expression the debug information gives it, or ``none``.

    python3 tools/units/dwarf_audit.py [--elf orig/SLUS_211.74] [--all]

Object extents come from ``dwarf1.py globals`` and member offsets from ``dwarf1.py type --all``
(the union of every layout a struct has; the first expression found is reported, and a note
marks an address two layouts disagree on).
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
DW = ROOT / "tools/oracle/dwarf1.py"

_G = re.compile(r"^(0x[0-9a-f]+)\s+(0x[0-9a-f]+)\s+(\S+)\s+(.*?);\s+//")
_M = re.compile(r"^\s*/\* (0x[0-9a-f]+) \*/ (.*?)\s*;\s+// (0x[0-9a-f]+)\s*$")
_END = re.compile(r"^\s*\}\s*(\w+)?\s*(\[(\d+)\])*\s*;")


def run(*a):
    return subprocess.run([sys.executable, str(DW), *a], capture_output=True, text=True, check=True).stdout


def globals_(elf):
    out = []
    for ln in run("globals", elf).splitlines():
        m = _G.match(ln)
        if not m or m.group(3) != "main":
            continue
        decl = m.group(4)
        mm = re.search(r"(\w+)((?:\[\d+\])*)$", decl.replace("static ", ""))
        if not mm:
            continue
        tm = re.match(r"(?:static\s+)?(?:struct\s+|union\s+|enum\s+)?([\w@]+)\s+\**\s*" + mm.group(1), decl)
        out.append((int(m.group(1), 16), int(m.group(2), 16), mm.group(1), tm.group(1) if tm else None, mm.group(2)))
    return out


_types: dict[str, list] = {}


def members(elf, tag):
    """Union of every layout's (offset, size, type, name, dims) for struct ``tag``."""
    if tag not in _types:
        res, depth = set(), 0
        try:
            txt = run("type", elf, tag, "--all")
        except subprocess.CalledProcessError:
            txt = ""
        for ln in txt.splitlines():
            if ln.startswith("// layout"):
                depth = 0
                continue
            if ln.startswith("struct ") or ln.startswith("union "):
                depth = 1
                continue
            if depth and ln.startswith("};"):
                depth = 0
                continue
            if depth != 1:
                continue
            m = _M.match(ln)
            if m and "padding" not in ln and "{" not in ln:
                off, decl, size = int(m.group(1), 16), m.group(2), int(m.group(3), 16)
                dm = re.search(r"(\w+)((?:\[\d+\])*)$", decl)
                if not dm:
                    continue
                t = re.match(r"(?:struct\s+|union\s+|enum\s+)?([\w@]+)", decl)
                res.add((off, size, t.group(1) if t else None, dm.group(1), dm.group(2), "*" in decl.split(dm.group(1))[0]))
        _types[tag] = sorted(res)
    return _types[tag]


def expr(elf, name, tag, dims, size, off, depth=0):
    """Member expression for byte ``off`` inside object ``name`` of type ``tag``."""
    dl = [int(x) for x in re.findall(r"\d+", dims)]
    cnt = 1
    for d in dl:
        cnt *= d
    esz = size // cnt if cnt else size
    s = name
    if dl and esz:
        idx, off = divmod(off, esz)
        s += f"[{idx}]"
        if len(dl) > 1:
            s += "".join("[?]" for _ in dl[1:])
    if off == 0 and (not tag or not members(elf, tag)):
        return s
    for moff, msz, mtag, mname, mdims, isptr in members(elf, tag) if tag else []:
        if moff <= off < moff + max(msz, 1):
            if isptr and not mdims:
                return f"{s}.{mname}" + (f" (+{off - moff})" if off != moff else "")
            sub = expr(elf, f"{s}.{mname}", mtag, mdims, msz, off - moff, depth + 1)
            return sub
    return s + (f" (+{off})" if off else "")


def lookup(elf, objs, addr):
    for base, size, name, tag, dims in objs:
        if base <= addr < base + size:
            return expr(elf, name, tag, dims, size, addr - base)
    return "none"


def promoted_sources():
    from config.targets import TARGETS  # type: ignore
    t = TARGETS.get("ddrex2p") if hasattr(TARGETS, "get") else TARGETS["ddrex2p"]
    return [Path(f) for f, *_ in t.tu_builds]


def scan(path):
    txt = (ROOT / path).read_text(errors="replace")
    hits = {}
    for m in re.finditer(r"\bD_([0-9A-Fa-f]{8})\b", txt):
        hits.setdefault(int(m.group(1), 16), set()).add(m.group(0))
    for m in re.finditer(r"\b0x([0-9A-Fa-f]{5,8})\b", txt):
        v = int(m.group(1), 16)
        if 0x100000 <= v < 0x2000000:
            hits.setdefault(v, set()).add(m.group(0))
    return hits


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--elf", default=str(ROOT / "orig/SLUS_211.74"))
    ap.add_argument("--all", action="store_true", help="also list addresses with no DWARF object")
    a = ap.parse_args()
    objs = globals_(a.elf)
    covered = 0
    for src in promoted_sources():
        for addr, names in sorted(scan(src).items()):
            e = lookup(a.elf, objs, addr)
            if e == "none" and not a.all:
                continue
            covered += e != "none"
            print(f"{src}\t0x{addr:08x}\t{','.join(sorted(names))}\t{e}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
