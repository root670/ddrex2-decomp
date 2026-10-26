"""Experiment 4: bisect between gen3 (w gets s2) and sb2 (w gets s0): which feature of loop 2 demotes w."""
import sys, pathlib, re
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
HEAD = "extern int *get(void); extern int arr[]; extern void ext(int, int);\n"
V = {
 "A w[i]":          "ext(w[i], i + 200);",
 "B w[i*2]":        "ext(w[i * 2], i + 200);",
 "C *(w+i*2)+w":    "ext((int)w + *(int *)((char *)w + i * 8), i + 200);",
 "D w base reload": "{ int *b = (int *)w[3]; ext((int)b + *(int *)((char *)b + i * 8), i + 200); }",
 "E sb-like":       "{ int *b = (int *)w[3]; int o = i * 8; ext((int)b + *(int *)((char *)b + o), i + 200); }",
}
for k, v in V.items():
    src = HEAD + f"""void f(void)
{{
    int *p; int i; int *w;
    w = get();
    p = arr;
    for (i = 0; i < 10; i++) {{ ext(*p++, i + 100); }}
    for (i = 0; i < 5; i++) {{ {v} }}
}}
"""
    f = pathlib.Path("/tmp/regrules/g4.c"); f.write_text(src)
    d = cc.dis(f)
    g = lambda r: (re.search(r, d) or [None, "?"])[1]
    print(k, "i1=", g(r"addiu\s+a1,(s\d),100"), "p=", g(r"lw\s+a0,0\((s\d)\)"), "i2=", g(r"addiu\s+a1,(s\d),200"), "w:", re.findall(r"(?:lw|move)\s+\w+,(?:\d+\()?(s\d)", d)[:6])
