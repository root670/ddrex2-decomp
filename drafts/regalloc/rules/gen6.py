"""Experiment 6: live-range length. Values x,y,z (src+11/22/33) all defined before call 1.
   Last-use position varies: use sites after call 1 / call 2 / call 3. Declaration orders permuted."""
import sys, pathlib, re, itertools
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
def src(order, last):          # last[v] in {1,2,3}: use after that call number
    decl = "\n".join(f"    int {v} = g_src + {c};" for v, c in ((v, {"x": 11, "y": 22, "z": 33}[v]) for v in order))
    out = []
    for n in (1, 2, 3):
        out.append("    ext();")
        for v in "xyz":
            if last[v] == n:
                out.append(f"    g_o{v} = {v};")
    return "extern int g_src, g_ox, g_oy, g_oz; extern void ext(void);\nvoid f(void)\n{\n" + decl + "\n" + "\n".join(out) + "\n}\n"
def regs(d):
    m = {}
    for reg, imm in re.findall(r"addiu\s+(s\d),\w+,(11|22|33)\b", d):
        m.setdefault(imm, reg)
    return "x=%s y=%s z=%s" % (m.get("11"), m.get("22"), m.get("33"))
for last in [(1,2,3),(3,2,1),(2,2,2),(1,3,3),(3,1,1),(1,1,3),(2,1,3)]:
    L = dict(zip("xyz", last))
    for order in ("xyz", "zyx", "yxz"):
        f = pathlib.Path("/tmp/regrules/g6.c"); f.write_text(src(order, L))
        print("last", last, "decl", order, regs(cc.dis(f)))
