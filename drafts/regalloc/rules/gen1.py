"""Experiment 1: three webs in one calling loop -- long-lived A (declared), induction i, SR pointer.
   Vary the number of uses of A inside the loop and the declaration order of A and i."""
import sys, pathlib, re
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
def build(nA, order, sr=True):
    body = "".join(f" g_o{k} = *a + {k};" for k in range(nA))
    decl = {"a": "int *a = gp_a;", "i": "int i;"}
    d = "\n".join("    " + decl[k] for k in order)
    use = "arr[i]" if sr else "ext2(i)"
    return f"""extern int arr[]; extern int *gp_a; extern int g_o0, g_o1, g_o2, g_o3; extern void ext(int, int);
void f(void)
{{
{d}
    for (i = 0; i < 10; i++) {{ ext({use}, i + 100);{body} }}
    ext(*a, 0);
}}
"""
for nA in range(0, 5):
    for order in (("a", "i"), ("i", "a")):
        f = pathlib.Path("/tmp/regrules/g1.c"); f.write_text(build(nA, order))
        d = cc.dis(f)
        g = lambda r: (re.search(r, d) or [None, "?"])[1]
        print(f"nA={nA} decl={''.join(order)}  i={g(r'addiu\s+a1,(s\d),100')} ptr={g(r'lw\s+a0,0\((s\d)\)')} a={g(r'lw\s+a0,0\((s\d)\)') if False else g(r'lw\s+a0,0\((s\d)\)')}", end="")
        m = re.findall(r"lw\s+\w+,0\((s\d)\)", d); print("  loads:", m)
