#!/usr/bin/env python3
"""Sweep installed mwccps2 builds x flag families against three retail shapes.

Not part of the build; this is the evidence behind
.superpowers/sdd/2026-10-15-m3-promotion-loop/reports/flag-sweep-report.md.

    python3 drafts/flagsweep/sweep.py [--json out.json]
"""
from __future__ import annotations

import argparse
import copy
import json
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "oracle"))
import elf as elfmod  # noqa: E402
from elf import Elf  # noqa: E402
import dwarf1  # noqa: E402

TOOLCHAIN = ROOT / "toolchain"
WIBO = TOOLCHAIN / "wibo"
BUILDS = ["2.4-001213", "3.0-011126", "3.0.1-020123", "3.0.3-020716", "3.0b38-030307"]
OBJDUMP = "mips-linux-gnu-objdump"
OUT = pathlib.Path("/tmp/flagsweep/objs")
OUT.mkdir(parents=True, exist_ok=True)

# ---- option matrix ---------------------------------------------------------
# Every entry is added after the base "-c -lang c -g".  Families are named so the
# report can say which option class was exercised.  Rejected options are recorded,
# never silently dropped.
BASE = ["-c", "-lang", "c", "-g"]
FLAG_SETS = [
    ("baseline -O3", ["-O3"]),
    ("-O0", ["-O0"]),
    ("-O1", ["-O1"]),
    ("-O2", ["-O2"]),
    ("-O4", ["-O4"]),
    ("-Os", ["-Os"]),
    ("-Op", ["-Op"]),
    ("-opt off", ["-O3", "-opt", "off"]),
    ("-opt on", ["-O3", "-opt", "on"]),
    ("-opt full", ["-O3", "-opt", "full"]),
    ("-opt all", ["-O3", "-opt", "all"]),
    ("-O2 -opt full", ["-O2", "-opt", "full"]),
    ("-O1 -opt full", ["-O1", "-opt", "full"]),
    ("-O4 -opt full", ["-O4", "-opt", "full"]),
    ("-O3 -opt level=4", ["-O3", "-opt", "level=4"]),
    ("-O3 -opt level=2", ["-O3", "-opt", "level=2"]),
    ("-O3 -opt intrinsics", ["-O3", "-opt", "intrinsics"]),
    ("-O3 -opt nointrinsics", ["-O3", "-opt", "nointrinsics"]),
    ("-O3 -opt full,nointrinsics", ["-O3", "-opt", "full,nointrinsics"]),
    ("-inline off", ["-O3", "-inline", "off"]),
    ("-inline on", ["-O3", "-inline", "on"]),
    ("-inline auto", ["-O3", "-inline", "auto"]),
    ("-inline all", ["-O3", "-inline", "all"]),
    ("-inline deferred", ["-O3", "-inline", "deferred"]),
    ("-inline level=0", ["-O3", "-inline", "level=0"]),
    ("-inline level=8", ["-O3", "-inline", "level=8"]),
    ("-sym on", ["-O3", "-sym", "on"]),
    ("-sym full", ["-O3", "-sym", "full"]),
    ("-sym full,elf", ["-O3", "-sym", "full,elf"]),
    ("-sdatathreshold 0", ["-O3", "-sdatathreshold", "0"]),
    ("-sdatathreshold 4", ["-O3", "-sdatathreshold", "4"]),
    ("-sdatathreshold 64", ["-O3", "-sdatathreshold", "64"]),
    ("-fp off", ["-O3", "-fp", "off"]),
    ("-farcall on", ["-O3", "-farcall", "on"]),
    ("-char unsigned", ["-O3", "-char", "unsigned"]),
    ("-enum min", ["-O3", "-enum", "min"]),
    ("-lang c++", ["-O3", "-lang", "c++"]),
    # pragmas, through the documented -pragma equivalent
    ("pragma schedule off", ["-O3", "-pragma", "schedule off"]),
    ("pragma schedule on", ["-O3", "-pragma", "schedule on"]),
    ("pragma peephole off", ["-O3", "-pragma", "peephole off"]),
    ("pragma opt_lifetimes off", ["-O3", "-pragma", "opt_lifetimes off"]),
    ("pragma opt_common_subs off", ["-O3", "-pragma", "opt_common_subs off"]),
    ("pragma opt_propagation off", ["-O3", "-pragma", "opt_propagation off"]),
    ("pragma opt_strength_reduction off", ["-O3", "-pragma", "opt_strength_reduction off"]),
    ("pragma opt_loop_invariants off", ["-O3", "-pragma", "opt_loop_invariants off"]),
    ("pragma opt_dead_code off", ["-O3", "-pragma", "opt_dead_code off"]),
    ("pragma opt_unroll_loops off", ["-O3", "-pragma", "opt_unroll_loops off"]),
    ("pragma global_optimizer off", ["-O3", "-pragma", "global_optimizer off"]),
    ("pragma optimize_for_size on", ["-O3", "-pragma", "optimize_for_size on"]),
    ("pragma always_inline on", ["-O3", "-pragma", "always_inline on"]),
    ("pragma dont_inline on", ["-O3", "-pragma", "dont_inline on"]),
    ("pragma auto_inline on", ["-O3", "-pragma", "auto_inline on"]),
    ("pragma pool_strings on", ["-O3", "-pragma", "pool_strings on"]),
    ("pragma optimization_level 2", ["-O3", "-pragma", "optimization_level 2"]),
    ("pragma optimization_level 3", ["-O3", "-pragma", "optimization_level 3"]),
    ("pragma optimization_level 4", ["-O3", "-pragma", "optimization_level 4"]),
    # full optimizer with scheduling disabled: the two families cross here
    ("-opt full + schedule off", ["-O3", "-opt", "full", "-pragma", "schedule off"]),
    ("-opt full + peephole off", ["-O3", "-opt", "full", "-pragma", "peephole off"]),
    ("-opt full + unroll off", ["-O3", "-opt", "full", "-pragma", "opt_unroll_loops off"]),
    ("-opt full + global_optimizer off", ["-O3", "-opt", "full", "-pragma", "global_optimizer off"]),
    # 3.0b38-only surface, recorded as rejected on the other four
    ("-flag no-schedule", ["-O3", "-flag", "no-schedule"]),
    ("-flag no-peephole", ["-O3", "-flag", "no-peephole"]),
    ("-for_scoping on", ["-O3", "-for_scoping", "on"]),
    ("-inline bottomup", ["-O3", "-inline", "bottomup"]),
]

# ---- DIE reading -----------------------------------------------------------

_orig_init = Elf.__init__


def _patched(self, path):
    _orig_init(self, path)
    if not any(s.type == 1 and s.filesz > 0 for s in self.segments):
        self.segments = list(self.segments) + [elfmod.Segment(1, 0, 0, 1, 0x100000, 0)]


Elf.__init__ = _patched


def debug_contributions(path):
    base = Elf(str(path))
    for sec in [s for s in base.sections if s.name == ".debug"]:
        e = copy.copy(base)
        e.sections = [sec]
        yield dwarf1.Dwarf(e)


def top_level_dies(path):
    """[(tag_name, name)] for the TU declaration CU's objects."""
    out = []
    for dw in debug_contributions(path):
        for cu in dw.cus:
            for d in cu.children:
                if d.tag in (dwarf1.TAG_global_variable, dwarf1.TAG_local_variable):
                    out.append((dwarf1.TAG[d.tag], d.name))
    return out


def local_count(path):
    """local_variable DIEs inside function CUs (our DWARF's function locals)."""
    n = 0
    for dw in debug_contributions(path):
        for cu in dw.cus:
            stack = list(cu.children)
            while stack:
                d = stack.pop()
                if d.tag == dwarf1.TAG_local_variable:
                    n += 1
                stack.extend(d.children)
    return n


def producer_strings(path):
    out = set()
    for dw in debug_contributions(path):
        for cu in dw.cus:
            p = cu.attrs.get(dwarf1.AT_producer)
            if p is not None:
                out.add(str(p))
    return sorted(out)


# ---- compile / disassemble -------------------------------------------------

def compile_probe(build, flags, src, tag):
    cdir = TOOLCHAIN / f"mwcps2-{build}"
    obj = OUT / f"{tag}_{src.stem}_{build}_{abs(hash(tuple(flags))) & 0xffff:x}.o"
    argv = [str(WIBO), "mwccps2.exe", *flags, "-o", str(obj), str(src)]
    try:
        p = subprocess.run(argv, cwd=cdir, capture_output=True, text=True, timeout=300)
    except subprocess.TimeoutExpired:
        return None, "timeout"
    if p.returncode != 0 or not obj.is_file():
        text = (p.stdout + p.stderr).strip()
        m = re.search(r"Unknown option '([^']+)'", text)
        if m:
            return None, f"rejected:-{m.group(1)}"
        return None, "failed:" + " ".join(text.split())[:120]
    return obj, None


LINE = re.compile(r"^\s+([0-9a-f]+):\s+([0-9a-f]+)\s+(\S+)(?:\s+(.*?))?\s*$")


def disasm(path):
    p = subprocess.run([OBJDUMP, "-m", "mips", "-EL", "-d", str(path)],
                       capture_output=True, text=True)
    out = []
    for line in p.stdout.splitlines():
        m = LINE.match(line)
        if m:
            out.append((int(m.group(1), 16), m.group(3), (m.group(4) or "").strip()))
    return out


def classify_coalesce(ins):
    """Retail-like: bgez; nop; move; subu.  Coalesced: bgez; subu."""
    for i, (_, op, _) in enumerate(ins):
        if op == "bgez" and i + 3 < len(ins):
            nxt = [x[1] for x in ins[i + 1:i + 5]]
            if nxt[0] == "subu":
                return "coalesced", len(ins)
            if nxt[0] == "nop" and nxt[1] == "move" and nxt[2] == "subu":
                return "retail_like", len(ins)
    return "other", len(ins)


def _symbol_bases(ins):
    """Registers loaded from a symbol: lui R,0x0 followed by addiu R,R,0."""
    bases = {}
    for i, (off, op, args) in enumerate(ins):
        if op != "lui":
            continue
        parts = [x.strip() for x in args.split(",")]
        if len(parts) != 2 or parts[1] not in ("0x0", "0"):
            continue
        reg = parts[0]
        for j in range(i + 1, min(i + 9, len(ins))):
            p = [x.strip() for x in ins[j][2].split(",")]
            if ins[j][1] == "addiu" and len(p) >= 3 and p[0] == reg and p[1] == reg \
                    and p[2] in ("0x0", "0"):
                bases.setdefault(reg, []).append(off)
                break
    return bases


def _loop_range(ins):
    """Offsets of the innermost backward-branch loop, or None."""
    for off, op, args in ins:
        if op in ("bnez", "beqz", "bgez", "blez", "bltz", "bgtz") or op == "b":
            p = [x.strip() for x in args.split(",")]
            m = re.match(r"^([0-9a-f]+)", p[-1])
            if not m:
                continue
            target = int(m.group(1), 16)
            if target < off:
                return target, off
    return None


def classify_fold(ins):
    """Classify the loop's induction variable.

    pointer_iv: the symbol base is loaded before the loop and the same register is
    advanced by `addu R,R,stride` at the bottom.  index_iv: the base is
    re-materialised inside the loop, or a separate index is added to it.
    unrolled: no backward branch.
    """
    bases = _symbol_bases(ins)
    loop = _loop_range(ins)
    if loop is None:
        return "unrolled", len(ins), (sorted(bases)[0] if bases else None)
    start, end = loop
    hoisted = {r: offs for r, offs in bases.items() if any(o < start for o in offs)}
    for off, op, args in ins:
        if not (start <= off <= end + 4):   # +4: the branch delay slot counts
            continue
        p = [x.strip() for x in args.split(",")]
        if op == "addu" and len(p) >= 3 and p[0] == p[1] and p[0] in hoisted:
            return "pointer_iv", len(ins), p[0]
        if op == "addiu" and len(p) >= 3 and p[0] == p[1] and p[0] in hoisted:
            return "pointer_iv", len(ins), p[0]
    return "index_iv", len(ins), (sorted(hoisted)[0] if hoisted else None)


# ---- sweeps ----------------------------------------------------------------

STATIC_EXPECTED = [
    ("local_variable", "anime_id_tbl"),
    ("local_variable", "hold_release"),
    ("local_variable", "pre_hold_flag"),
    ("global_variable", "g_game_w"),
    ("global_variable", "paw_p"),
    ("global_variable", "play_anime_w"),
]


def run(builds, flag_sets):
    probes = {
        "static": ROOT / "drafts/flagsweep/static_order.c",
        "coalesce": ROOT / "drafts/flagsweep/coalesce.c",
        "fold_index": ROOT / "drafts/flagsweep/fold_index.c",
        "fold_ptr": ROOT / "drafts/flagsweep/fold_ptr.c",
    }
    rows = []
    for build in builds:
        for family, extra in flag_sets:
            flags = BASE + extra
            row = {"build": build, "family": family, "flags": flags}
            obj, err = compile_probe(build, flags, probes["static"], "static")
            if obj:
                row["static_dies"] = top_level_dies(obj)
                row["static_match"] = row["static_dies"] == STATIC_EXPECTED
                row["producer"] = producer_strings(obj)
            else:
                row["static_error"] = err

            obj, err = compile_probe(build, flags, probes["coalesce"], "coalesce")
            if obj:
                row["coalesce"], row["coalesce_inst"] = classify_coalesce(disasm(obj))
            else:
                row["coalesce_error"] = err

            obj, err = compile_probe(build, flags, probes["fold_index"], "fold_index")
            if obj:
                shape, inst, base = classify_fold(disasm(obj))
                row["fold_index"] = shape
                row["fold_index_inst"] = inst
                row["fold_index_base"] = base
                row["fold_index_locals"] = local_count(obj)
            else:
                row["fold_index_error"] = err

            obj, err = compile_probe(build, flags, probes["fold_ptr"], "fold_ptr")
            if obj:
                shape, inst, base = classify_fold(disasm(obj))
                row["fold_ptr"] = shape
                row["fold_ptr_inst"] = inst
                row["fold_ptr_base"] = base
                row["fold_ptr_locals"] = local_count(obj)
            else:
                row["fold_ptr_error"] = err
            rows.append(row)
            print(".", end="", flush=True)
    print()
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", default="/tmp/flagsweep/sweep.json")
    ap.add_argument("--builds", nargs="*", default=BUILDS)
    args = ap.parse_args()
    rows = run(args.builds, FLAG_SETS)
    pathlib.Path(args.json).write_text(json.dumps(rows, indent=1))
    print(f"wrote {args.json}: {len(rows)} cells")

    def summaries(key, want=None):
        hit = [r for r in rows if r.get(key) == want] if want else [r for r in rows if key in r]
        return hit

    print("\nstatic matches:", len(summaries("static_match", True)),
          "of", len([r for r in rows if "static_match" in r]))
    print("coalesce retail_like:", len(summaries("coalesce", "retail_like")),
          "of", len([r for r in rows if "coalesce" in r]))
    print("fold_index pointer_iv:", len(summaries("fold_index", "pointer_iv")),
          "of", len([r for r in rows if "fold_index" in r]))
    print("fold_ptr pointer_iv:", len(summaries("fold_ptr", "pointer_iv")),
          "of", len([r for r in rows if "fold_ptr" in r]))


if __name__ == "__main__":
    main()
