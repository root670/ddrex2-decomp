#!/usr/bin/env python3
"""Compile one or more probe sources with the retail pair and print compact disassembly.

    python3 drafts/regalloc/rules/cc.py drafts/regalloc/rules/a1.c [more.c ...]
"""
import pathlib, subprocess, sys, re
ROOT = pathlib.Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT)); sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch, probe
PAIR = "3.0b38-030307"
FLAGS = ["-c", "-lang", "c", "-O3", "-opt", "full", "-g"]
OUT = pathlib.Path("/tmp/regrules"); OUT.mkdir(exist_ok=True)

def dis(src, flags=FLAGS):
    src = pathlib.Path(src).resolve()
    obj = OUT / (src.stem + ".o")
    probe.compile(src, obj, fetch.compiler(PAIR), fetch.wibo(), flags)
    t = subprocess.run(["mips-linux-gnu-objdump", "-d", "-EL", "-m", "mips:5900", "--no-show-raw-insn", str(obj)],
                       capture_output=True, text=True, check=True).stdout
    return "\n".join(l.split(":", 1)[1].strip() if ":" in l and l.startswith(" ") else l
                     for l in t.splitlines()[6:] if l.strip())

if __name__ == "__main__":
    for f in sys.argv[1:]:
        print("==", f); print(dis(f))
