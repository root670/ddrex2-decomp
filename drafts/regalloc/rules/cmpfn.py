"""cmpfn.py <C file> <function> [extra cc flags]: compile with the retail pair, compare function words with
retail's split asm (asm/nonmatchings/*/<function>.s of the main checkout) by register-number mapping.
Prints the register substitution table (ours -> retail) and the first differing lines."""
import pathlib, re, subprocess, sys, collections
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
MAIN = pathlib.Path("<checkout>")
R = pathlib.Path(__file__).resolve().parents[3]
NAMES = "zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra".split()
def retail(fn):
    p = next(MAIN.glob(f"asm/nonmatchings/*/{fn}.s"))
    out = []
    for l in p.read_text().splitlines():
        m = re.match(r"\s*/\* \w+ \w+ ([0-9A-F]{8}) \*/\s+(.*)", l)
        if m: out.append(m.group(2).split("#")[0].strip())
    return out
def ours(c, fn, flags):
    d = cc.dis(c, cc.FLAGS + ["-i", str(R / "include")] + flags)
    sec = d[d.index(f"<{fn}>:") + len(fn) + 3:]
    sec = re.split(r"\nDisassembly of section|\n[0-9a-f]{8} <", sec)[0]
    return [l for l in sec.splitlines() if l.strip()]
def regs(s):
    return re.findall(r"\$(\d+)|\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra)\b", s)
def num(r):
    return int(r[0]) if r[0] else NAMES.index(r[1])
if __name__ == "__main__":
    c, fn = sys.argv[1], sys.argv[2]
    A = ours(c, fn, sys.argv[3:]); B = retail(fn)
    # strip delay-slot style differences: compare opcode sequences only
    op = lambda s: re.split(r"\s+", s.strip())[0].replace("daddu", "move").replace("addu", "move")
    print("ours words", len(A), "retail words", len(B))
    sub = collections.Counter()
    for a, b in zip(A, B):
        ra, rb = [num(r) for r in regs(a)], [num(r) for r in regs(b)]
        if len(ra) == len(rb):
            for x, y in zip(ra, rb):
                if x != y: sub[(NAMES[x], NAMES[y])] += 1
    print("register ours->retail:", dict(sub))
