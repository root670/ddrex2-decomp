"""Experiment 8: temp-class (no call in loop): i, SR pointer (from a declared base b that stays live), and a
declared accumulator n.  Report each web's register for declaration permutations."""
import sys, pathlib, re, itertools
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
T = """extern int *gb; extern int g_out;
void f(void)
{
%s
    b = gb;
    n = 0;
    for (i = 0; i < 3; i++) { n += b[i] + 7; b[i + 40] = 1; }
    g_out = n + b[0];
}
"""
for order in itertools.permutations("bni"):
    decl = {"b": "int *b;", "n": "int n;", "i": "int i;"}
    f = pathlib.Path("/tmp/regrules/g8.c"); f.write_text(T % "\n".join("    " + decl[k] for k in order))
    d = cc.dis(f)
    body = "\n".join(l for l in d.splitlines())
    print("".join(order), [l for l in body.splitlines() if re.match(r"(move|addiu|slti|lw|addu|sw)\s", l)][:14])
