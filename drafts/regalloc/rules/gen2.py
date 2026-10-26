"""Experiment 2: W (call result, live to the end), P (explicit pointer, incremented), I (counter), all in a calling loop.
   All 6 declaration orders, with W initialised at declaration vs assigned later."""
import sys, pathlib, re, itertools
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
T = """extern int *get(void); extern int arr[]; extern void ext(int, int);
void f(void)
{
%s
%s
    for (i = 0; i < 10; i++) { ext(*p++, i + 100); }
    ext(*w, 0);
}
"""
for init_at_decl in (True, False):
  for order in itertools.permutations("wpi"):
    decl = {"w": "int *w" + (" = get()" if init_at_decl else "") + ";", "p": "int *p;", "i": "int i;"}
    pre = "\n".join("    " + decl[k] for k in order)
    pre2 = "" if init_at_decl else "    w = get();"
    pre2 += "\n    p = arr;"
    if init_at_decl: pre2 = "    p = arr;"
    f = pathlib.Path("/tmp/regrules/g2.c"); f.write_text(T % (pre, pre2))
    d = cc.dis(f)
    g = lambda r: (re.search(r, d) or [None, "?"])[1]
    print(init_at_decl, "".join(order), "i=", g(r"addiu\s+a1,(s\d),100"), "p=", g(r"lw\s+a0,0\((s\d)\)"), "w=", g(r"ext.*\n.*|lw\s+a0,0\((s\d)\)") if False else re.findall(r"lw\s+\w+,0\((s\d)\)", d)[-1])
