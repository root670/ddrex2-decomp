"""Experiment 7: SR temp whose initial value is a declared pointer p (dead after the loop).  Does the temp take
p's place in the colouring order?  Declaration permutations of p, w, i; w live across (used after loop)."""
import sys, pathlib, re, itertools
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
T = """extern int *get(void); extern int *gtab; extern void ext(int, int);
void f(void)
{
%s
    w = get();
    p = gtab;
    for (i = 0; i < 10; i++) { ext(p[i], i + 100); }
    ext(*w, 0);
}
"""
for order in itertools.permutations("pwi"):
    decl = {"w": "int *w;", "p": "int *p;", "i": "int i;"}
    f = pathlib.Path("/tmp/regrules/g7.c"); f.write_text(T % "\n".join("    " + decl[k] for k in order))
    d = cc.dis(f)
    g = lambda r: (re.search(r, d) or [None, "?"])[1]
    print("".join(order), "i=", g(r"addiu\s+a1,(s\d),100"), "ptr=", g(r"lw\s+a0,0\((s\d)\)"), "w=", re.findall(r"lw\s+\w+,0\((s\d)\)", d)[-1])
