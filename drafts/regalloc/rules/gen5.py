"""Experiment 5: three declared values a,b,c (g_src+11/22/33) live across a call; vary use counts after the call,
   and whether the uses sit inside a loop (depth 1) after the call."""
import sys, pathlib, re, itertools
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
def src(counts, loop):
    ref = {k: "".join(f" g_o{j} = {k} + {j};" for j in range(n)) + f" g_x{k} = {k};" for k, n in zip("abc", counts)}
    body = "".join(ref[k] for k in "abc")
    if loop:
        body = "for (i = 0; i < 4; i++) {" + body + " }"
    return f"""extern int g_xa, g_xb, g_xc, g_src, g_o0, g_o1, g_o2, g_o3, g_o4; extern void ext(void);
int f(int i)
{{
    int a = g_src + 11; int b = g_src + 22; int c = g_src + 33;
    ext();
    {body}
    return 0;
}}
"""
for loop in (False, True):
  for counts in [(1,1,1),(3,1,1),(1,3,1),(1,1,3),(1,0,0),(0,0,1),(4,2,1),(1,2,4),(0,1,0)]:
    f = pathlib.Path("/tmp/regrules/g5.c"); f.write_text(src(counts, loop))
    d = cc.dis(f)
    m = {}
    for reg, imm in re.findall(r"addiu\s+(s\d),\w+,(11|22|33)\b", d):
        m.setdefault(imm, reg)
    print("loop" if loop else "flat", counts, "a=%s b=%s c=%s" % (m.get("11"), m.get("22"), m.get("33")))
