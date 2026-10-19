#!/usr/bin/env python3
"""Register-assignment probes for mwccps2-3.0b38-030307.

Not part of the build.  Each probe makes every live value identifiable by the
constant that materialises it, compiles with the retail pair, and reads the
register back out of the disassembly:

    value K = g_src + K          ->  addiu sN,v0,K   (or tN/aN, depending)

A value is forced to live across the call because ``g_src`` is loaded before the
call and each value is consumed after it, into its own global.

    python3 drafts/regalloc/probe.py             # the callee-saved sweeps
    python3 drafts/regalloc/probe.py --search 5  # exhaustive declaration-order search
    python3 drafts/regalloc/probe.py --volatile  # the a-class scan-counter sweep
    python3 drafts/regalloc/probe.py --interleaved  # definitions split across two calls
"""
from __future__ import annotations

import argparse
import itertools
import json
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))
from toolchain import fetch, probe  # noqa: E402

PAIR = "3.0b38-030307"
FLAGS = ["-c", "-lang", "c", "-O3", "-opt", "full", "-g"]
OUT = pathlib.Path("/tmp/regalloc")
OUT.mkdir(parents=True, exist_ok=True)
CONST = {i: 11 * (i + 1) for i in range(1, 10)}
KIND = {"int": "int", "unsigned": "unsigned", "char": "char", "short": "short"}


def source(n: int, decl=(), init=(), use=(), kind="int", split=False,
           call_between=(), two_calls=False):
    """One probe function.

    ``decl`` / ``init`` / ``use`` are permutations of ``range(n)``.  ``split``
    declares every local first and initialises later; otherwise each local is
    initialised at its declaration (in ``decl`` order, ``init`` ignored).
    """
    t = KIND[kind]
    L = ["extern int g_src;", "extern int g_out1, g_out2, g_out3, g_out4, g_out5,"
         " g_out6, g_out7, g_out8, g_out9;", "extern void ext(void);", "",
         "int probe(void)", "{"]
    names = [f"v{i}" for i in range(n)]
    if split:
        for i in decl:
            L.append(f"    {t} {names[i]};")
        for i in init:
            L.append(f"    {names[i]} = g_src + {CONST[i + 1]};")
    else:
        for i in decl:
            L.append(f"    {t} {names[i]} = g_src + {CONST[i + 1]};")
    if two_calls:
        L.append("    ext();")
    L.append("    ext();")
    for i in use:
        L.append(f"    g_out{i + 1} = {names[i]};")
    L.append("    return 0;")
    L.append("}")
    return "\n".join(L) + "\n"


_ADDIU = re.compile(r"addiu\s+([a-z][a-z0-9]*)\s*,\s*([a-z][a-z0-9]*)\s*,\s*(\d+)")
_LI = re.compile(r"\bli\s+([a-z][a-z0-9]*)\s*,\s*(\d+)")


def assemble(name: str, text: str):
    src = OUT / f"{name}.c"
    obj = OUT / f"{name}.o"
    src.write_text(text)
    probe.compile(src, obj, fetch.compiler(PAIR), fetch.wibo(), FLAGS)
    dis = subprocess.run(["mips-linux-gnu-objdump", "-d", "-m", "mips:5900", str(obj)],
                         capture_output=True, text=True, check=True).stdout
    return dis


_SHIFT = re.compile(r"(?:dsll32|dsra32|dsll|dsra|sll|sra|andi|seb|seh)\s+"
                    r"([a-z][a-z0-9]*)\s*,\s*([a-z][a-z0-9]*)")


def mapping(dis: str) -> dict[int, str]:
    """constant -> register that ends up holding it, just before the call.

    ``int`` values are one ``addiu``; ``char``/``short`` values are materialised in
    ``v0``/``v1`` and then sign-extended into the saved register with
    ``dsll32``/``dsra32``, so the value is followed through those.
    """
    out = {}
    held: dict[str, int] = {}
    for line in dis.splitlines():
        m = _ADDIU.search(line)
        if m:
            imm = int(m.group(3))
            if imm in CONST.values():
                held[m.group(1)] = imm
        m = _LI.search(line)
        if m:
            imm = int(m.group(2))
            if imm in CONST.values():
                held[m.group(1)] = imm
        m = _SHIFT.search(line)
        if m and m.group(2) in held:
            held[m.group(1)] = held[m.group(2)]
        for reg, imm in held.items():
            if reg.startswith("s") or reg.startswith("a") or reg.startswith("t"):
                out.setdefault(imm, reg)
    return out


def run(name, **kw):
    dis = assemble(name, source(**kw))
    return mapping(dis), dis


def fmt(mp, n):
    return " ".join(f"{CONST[i+1]}={mp.get(CONST[i+1], '?')}" for i in range(n))


def sweeps():
    rows = []
    # 1. N from 2..9, canonical order everywhere.
    for n in range(2, 10):
        mp, _ = run(f"n{n}", n=n, decl=range(n), use=range(n))
        rows.append(("canonical", n, fmt(mp, n)))
        print(f"N={n:<2} canonical      {fmt(mp, n)}")

    # 2. declaration order reversed, init order canonical (at-decl follows decl).
    for n in range(2, 10):
        mp, _ = run(f"n{n}r", n=n, decl=reversed(range(n)), use=range(n))
        rows.append(("decl rev", n, fmt(mp, n)))
        print(f"N={n:<2} decl reversed  {fmt(mp, n)}")

    # 3. declare all, initialise in reverse order (code order reverses, DIE order doesn't).
    for n in range(2, 10):
        mp, _ = run(f"n{n}i", n=n, decl=range(n), init=reversed(range(n)), use=range(n), split=True)
        rows.append(("init rev", n, fmt(mp, n)))
        print(f"N={n:<2} init reversed  {fmt(mp, n)}")

    # 4. post-call use order reversed.
    for n in range(2, 10):
        mp, _ = run(f"n{n}u", n=n, decl=range(n), use=reversed(range(n)))
        rows.append(("use rev", n, fmt(mp, n)))
        print(f"N={n:<2} use reversed   {fmt(mp, n)}")

    # 5. value kinds at N=5.
    for kind in KIND:
        mp, _ = run(f"k{kind}", n=5, decl=range(5), use=range(5), kind=kind)
        rows.append((f"kind {kind}", 5, fmt(mp, 5)))
        print(f"N=5  kind={kind:<9}{fmt(mp, 5)}")

    # 6. two calls.
    for n in (5, 9):
        mp, _ = run(f"c{n}", n=n, decl=range(n), use=range(n), two_calls=True)
        rows.append(("two calls", n, fmt(mp, n)))
        print(f"N={n:<2} two calls      {fmt(mp, n)}")
    return rows


VOL_NAMES = ["c", "n", "acc", "lim"]
VOL_CONST = {"c": "0", "n": "p0 + 22", "acc": "p1 + 11", "lim": "p0 + 33"}


def volatile_source(decl, init="at"):
    """The scan-counter shape: ``c`` is the counter, ``n`` bounds the loop.

    Values are identified from the immediate in the addiu that computes them
    (``a0``/``a1`` are the parameters), and ``c`` by the register that the
    ``addiu X,X,1`` increments.
    """
    L = ["extern int g_out1, g_out2, g_out3, g_out4;", "extern int *g_p;",
         "int probe(int p0, int p1)", "{"]
    if init == "at":
        for i in decl:
            L.append(f"    int {VOL_NAMES[i]} = {VOL_CONST[VOL_NAMES[i]]};")
    else:
        for i in decl:
            L.append(f"    int {VOL_NAMES[i]};")
        for i in decl:
            L.append(f"    {VOL_NAMES[i]} = {VOL_CONST[VOL_NAMES[i]]};")
    L += ["    while (c < n) {", "        if (g_p[c] == acc) break;", "        c++;", "    }",
          "    g_out1 = c;", "    g_out2 = n;", "    g_out3 = acc;", "    g_out4 = lim;",
          "    return 0;", "}"]
    return "\n".join(L) + "\n"


def volatile_mapping(dis: str) -> dict[str, str]:
    out = {}
    for line in dis.splitlines():
        for pattern, key in ((r"addiu\s+(\w+),a0,22", "n"),
                             (r"addiu\s+(\w+),a1,11", "acc"),
                             (r"addiu\s+(\w+),a0,33", "lim"),
                             (r"move\s+(\w+),zero", "c")):
            m = re.search(pattern, line)
            if m:
                out.setdefault(key, m.group(1))
        m = re.search(r"addiu\s+(\w+),\1,1", line)
        if m:
            out["inc"] = m.group(1)
    return out


def interleaved_source(decl, n, split):
    """Every value crosses a call, but not the same one: ``split`` values are
    defined before the first call, the rest between the two calls."""
    L = ["extern int g_src;", "extern int g_out1, g_out2, g_out3, g_out4, g_out5,"
         " g_out6, g_out7, g_out8, g_out9;", "extern void ext(void);", "",
         "int probe(void)", "{"]
    for i in decl:
        L.append(f"    int v{i};")
    for i in decl:
        if i < split:
            L.append(f"    v{i} = g_src + {CONST[i + 1]};")
    L.append("    ext();")
    for i in decl:
        if i >= split:
            L.append(f"    v{i} = g_src + {CONST[i + 1]};")
    L.append("    ext();")
    for i in range(n):
        L.append(f"    g_out{i + 1} = v{i};")
    L += ["    return 0;", "}"]
    return "\n".join(L) + "\n"


def allocation_order(mp):
    """Values sorted by the register they received: the order s0, s1, ... was handed out."""
    return tuple(sorted(range(len(mp)), key=lambda v: int(mp[v][1:])))


def search(n=5, order="decl"):
    """Every declaration (or initialisation) order -> the assignment it produces.

    ``order="decl"`` permutes the declarations themselves, which is the axis that
    moves registers; ``order="init"`` keeps the declarations fixed and permutes the
    separate initialisation statements, which is the control.
    """
    from concurrent.futures import ThreadPoolExecutor

    perms = list(itertools.permutations(range(n)))

    def one(item):
        idx, perm = item
        src = OUT / f"s{idx}.c"
        obj = OUT / f"s{idx}.o"
        if order == "decl":
            src.write_text(source(n=n, decl=perm, use=range(n)))
        else:
            src.write_text(source(n=n, decl=range(n), init=perm, use=range(n), split=True))
        probe.compile(src, obj, fetch.compiler(PAIR), fetch.wibo(), FLAGS)
        dis = subprocess.run(["mips-linux-gnu-objdump", "-d", "-m", "mips:5900", str(obj)],
                             capture_output=True, text=True, check=True).stdout
        return perm, mapping(dis)

    with ThreadPoolExecutor(max_workers=8) as ex:
        results = list(ex.map(one, enumerate(perms)))
    seen = {}
    for perm, mp in results:
        key = tuple(mp.get(CONST[i + 1], "?") for i in range(n))
        seen.setdefault(key, []).append(perm)
    print(f"\nexhaustive {order}-order search, N={n}, {len(perms)} permutations")
    print(f"  distinct assignments: {len(seen)}")
    for key, perms in sorted(seen.items()):
        print(f"  {key}  <- {len(perms)} orders, e.g. {perms[0]}")
    return seen


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--search", type=int, default=0,
                    help="exhaustive declaration-order search at N")
    ap.add_argument("--init-search", type=int, default=0,
                    help="exhaustive initialisation-order search at N (the control)")
    ap.add_argument("--volatile", action="store_true")
    ap.add_argument("--interleaved", action="store_true")
    args = ap.parse_args()
    if args.search:
        search(args.search, "decl")
    elif args.init_search:
        search(args.init_search, "init")
    elif args.volatile:
        for init in ("at", "later"):
            seen = {}
            for D in itertools.permutations(range(4)):
                mp = volatile_mapping(assemble("v", volatile_source(D, init)))
                key = tuple(mp.get(k) for k in ("c", "n", "acc", "lim"))
                seen.setdefault(key, []).append(D)
            print(f"volatile, initialisation {init}: {len(seen)} distinct "
                  f"(c, n, acc, lim) assignments of 24 declaration orders")
            for key, perms in sorted(seen.items(), key=str):
                print(f"  c={key[0]} n={key[1]} acc={key[2]} lim={key[3]}"
                      f"  <- {len(perms)} orders, e.g. {perms[0]}")
    elif args.interleaved:
        import random
        random.seed(3)
        # n=5 is exhaustive (120 orders); above that the space is sampled -- the
        # exhaustive n=6/7 sweeps are in the report's table and take minutes.
        for n, split, sample in ((5, 2, None), (6, 3, 60), (7, 3, 60), (9, 5, 60)):
            seen = {}
            orders = (list(itertools.permutations(range(n))) if sample is None else
                      [tuple(random.sample(range(n), n)) for _ in range(sample)])
            for D in orders:
                mp = mapping(assemble("il", interleaved_source(D, n, split)))
                M = tuple(mp.get(CONST[i + 1], "?") for i in range(n))
                seen.setdefault(allocation_order(M), []).append(D)
            fits = {}
            for A, perms in seen.items():
                for D in perms:
                    k = tuple(k for k in range(1, n + 1)
                              if tuple(reversed(D[:k])) + tuple(D[k:]) == A)
                    fits[k] = fits.get(k, 0) + 1
            print(f"n={n}: {len(seen)} distinct assignments; "
                  f"rule A=reverse(D[:k])+D[k:] fits by k: "
                  f"{{{', '.join(f'{k}: {v}' for k, v in sorted(fits.items(), key=str))}}}")
    else:
        sweeps()
