#!/usr/bin/env python3
"""Staggered live-definition probes: nine locals, two calls, each local defined on
one side or the other and read only on the far side.

The distinction from ``probe.py``'s interleaved mode is explicit here: the side each
definition falls on (``S``), the definition order inside each side (``EA``/``EB``) and
the declaration order (``D``) are three independent knobs.

    python3 drafts/regalloc/stagger.py --n5      # exhaustive declaration order, n=5
    python3 drafts/regalloc/stagger.py --n9      # the nine-value case, several orders
    python3 drafts/regalloc/stagger.py --target  # can the s4<->s0 swap be reached?
"""
from __future__ import annotations

import argparse
import itertools
import pathlib
import random
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch, probe  # noqa: E402

PAIR = "3.0b38-030307"
FLAGS = ["-c", "-lang", "c", "-O3", "-opt", "full", "-g"]
OUT = pathlib.Path("/tmp/regalloc/stagger")
OUT.mkdir(parents=True, exist_ok=True)
CONST = {i: 11 * (i + 1) for i in range(1, 10)}
COMP = None
WIBO = None


def source(n, D, S, EA, EB):
    """Declare in ``D``; define ``S`` before the first call in ``EA`` order, the rest
    between the calls in ``EB`` order; every value read after the second call."""
    L = ["extern int g_src;",
         "extern int " + ", ".join(f"g_out{i+1}" for i in range(9)) + ";",
         "extern void ext(void);", "", "int probe(void)", "{"]
    for i in D:
        L.append(f"    int v{i};")
    for i in EA:
        L.append(f"    v{i} = g_src + {CONST[i+1]};")
    L.append("    ext();")
    for i in EB:
        L.append(f"    v{i} = g_src + {CONST[i+1]};")
    L.append("    ext();")
    for i in range(n):
        L.append(f"    g_out{i+1} = v{i};")
    L += ["    return 0;", "}"]
    return "\n".join(L) + "\n"


def _compile(idx, text):
    src = OUT / f"c{idx}.c"
    obj = OUT / f"c{idx}.o"
    src.write_text(text)
    probe.compile(src, obj, COMP, WIBO, FLAGS)
    dis = subprocess.run(["mips-linux-gnu-objdump", "-d", "-m", "mips:5900", str(obj)],
                         capture_output=True, text=True, check=True).stdout
    return dis


def mapping(idx, text, n):
    import re
    dis = _compile(idx, text)
    held = {}
    out = {}
    for line in dis.splitlines():
        m = re.search(r"addiu\s+(\w+)\s*,\s*(\w+)\s*,\s*(\d+)", line)
        if m and int(m.group(3)) in CONST.values():
            held[m.group(1)] = int(m.group(3))
        for reg, imm in held.items():
            if reg.startswith(("s", "a", "t")):
                out.setdefault(imm, reg)
    return tuple(out.get(CONST[i + 1], "?") for i in range(n))


def run_batch(cases, n):
    with ThreadPoolExecutor(max_workers=8) as ex:
        return list(ex.map(lambda t: mapping(t[0], t[1], n),
                           [(i, source(n, *case)) for i, case in enumerate(cases)]))


def alloc(M):
    return tuple(sorted(range(len(M)), key=lambda v: int(M[v][1:])))


def fit(M, D):
    A = alloc(M)
    return tuple(k for k in range(1, len(D) + 1)
                 if tuple(reversed(D[:k])) + tuple(D[k:]) == A)


def main():
    global COMP, WIBO
    COMP, WIBO = fetch.compiler(PAIR), fetch.wibo()
    ap = argparse.ArgumentParser()
    ap.add_argument("--n5", action="store_true")
    ap.add_argument("--n9", action="store_true")
    ap.add_argument("--target", action="store_true")
    a = ap.parse_args()
    random.seed(5)

    if a.n5:
        # exhaustive declaration order, two fixed side partitions:
        #   S = {0,1} by value index, and S = first two declared.
        for name, mk in (("S by value {0,1}", lambda D: set(D[:2])),
                         ("S by value {3,4}", lambda D: set(D[3:5]))):
            cases = []
            for D in itertools.permutations(range(5)):
                S = mk(D)
                EA = tuple(i for i in D if i in S)
                EB = tuple(i for i in D if i not in S)
                cases.append((D, S, EA, EB))
            Ms = run_batch(cases, 5)
            fits = {}
            for (D, S, EA, EB), M in zip(cases, Ms):
                f = fit(M, D)
                fits[f] = fits.get(f, 0) + 1
            print(f"n=5, {name}: distinct mappings {len(set(Ms))}/120; "
                  f"reverse-decl fits by k: "
                  f"{{{', '.join(f'{k}: {v}' for k, v in sorted(fits.items(), key=str))}}}")
            for (D, S, EA, EB), M in list(zip(cases, Ms))[:3]:
                print(f"   D={D} EA={EA} EB={EB} -> {M}")

    if a.n9:
        # fixed partition S={0..4}: vary D, EA/EB; then vary the partition.
        base = tuple(range(9))
        for _ in range(4):
            D = list(range(9)); random.shuffle(D); D = tuple(D)
            S = {0, 1, 2, 3, 4}
            EA = tuple(i for i in D if i in S)
            EB = tuple(i for i in D if i not in S)
            cases = [(D, S, EA, EB),
                     (D, S, tuple(reversed(EA)), EB),          # definition order flipped, side A
                     (D, S, EA, tuple(reversed(EB))),          # definition order flipped, side B
                     (D, {0, 1, 5, 6, 7}, EA, EB)]             # another partition
            Ms = run_batch(cases, 9)
            print(f"D={D}")
            print(f"   base            -> {Ms[0]}  fits k={fit(Ms[0], D)}")
            print(f"   EA reversed     -> {Ms[1]}  fits k={fit(Ms[1], D)}")
            print(f"   EB reversed     -> {Ms[2]}  fits k={fit(Ms[2], D)}")
            print(f"   partition moved -> {Ms[3]}")

    if a.target:
        canon = ['s5', 's4', 's3', 's2', 's1', 's0', 's6', 's7', 's8']
        tgt = list(canon); tgt[1] = 's0'; tgt[5] = 's4'; tgt = tuple(tgt)
        A = alloc(tgt)
        D0 = tuple(reversed(A[:6])) + tuple(A[6:])
        cands = [D0]
        for i in range(9):
            for j in range(i + 1, 9):
                d = list(D0); d[i], d[j] = d[j], d[i]; cands.append(tuple(d))
        # both a fixed partition and the partition each order implies
        for label, part in (("S=first five declared", None), ("S={0..4}", {0, 1, 2, 3, 4})):
            cases = []
            for D in cands:
                S = set(D[:5]) if part is None else part
                cases.append((D, S, tuple(i for i in D if i in S),
                              tuple(i for i in D if i not in S)))
            Ms = run_batch(cases, 9)
            hits = [c[0] for c, M in zip(cases, Ms) if M == tgt]
            print(f"target {tgt} [{label}]: {len(hits)} of {len(cases)} candidate orders")
            if hits:
                print(f"   decl order {hits[0]}")


if __name__ == "__main__":
    main()
