"""Experiment 3: add a second loop that reuses i (as sb2), vary decl order of w,p,i."""
import sys, pathlib, re, itertools
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
T = """extern int *get(void); extern int arr[]; extern void ext(int, int);
void f(void)
{
%s
    w = get();
    p = arr;
    for (i = 0; i < 10; i++) { ext(*p++, i + 100); }
%s
    ext(*w, 0);
}
"""
L2 = {"none": "", "loop2": "    for (i = 0; i < 5; i++) { ext(w[i], i + 200); }",
      "loop2b": "    for (i = 0; i < 5; i++) { ext(w[i * 2], i + 200); }"}
for l2 in L2:
  for order in itertools.permutations("wpi"):
    decl = {"w": "int *w;", "p": "int *p;", "i": "int i;"}
    pre = "\n".join("    " + decl[k] for k in order)
    f = pathlib.Path("/tmp/regrules/g3.c"); f.write_text(T % (pre, L2[l2]))
    d = cc.dis(f)
    g = lambda r: (re.search(r, d) or [None, "?"])[1]
    print(l2, "".join(order), "i1=", g(r"addiu\s+a1,(s\d),100"), "p=", g(r"lw\s+a0,0\((s\d)\)"), "i2=", g(r"addiu\s+a1,(s\d),200"), "w=", re.findall(r"lw\s+\w+,0\((s\d)\)", d)[-1])
