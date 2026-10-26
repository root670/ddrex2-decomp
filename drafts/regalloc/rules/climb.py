"""climb.py <draft.c> <function> : hill-climb over the order of the function's scalar local declarations
(adjacent/arbitrary moves of one declaration line) minimising register mismatches against retail's split asm.
The declarations considered are the lines in the function's leading declaration block that match
`^    (int|short|char|unsigned...) name;`  (no initialiser, single name)."""
import pathlib, random, re, sys, collections, concurrent.futures as cf
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cmpfn
def parts(src, fn):
    m = re.search(r"^[^\n;{}]*\b%s\([^)]*\)\s*\{\n" % fn, src, re.M)
    a = m.end(); lines = src[a:].split("\n")
    k = 0
    while k < len(lines) and re.match(r"^    [A-Za-z_][\w \*\[\]]*;$", lines[k]) or (k < len(lines) and lines[k].strip() == ""):
        k += 1
    return src[:a], lines[:k], "\n".join(lines[k:])
def score(src, fn, n):
    import hashlib; f = pathlib.Path("/tmp/regrules/cl_%s.c" % hashlib.md5(src.encode()).hexdigest()[:10]); f.write_text(src)
    try: A = cmpfn.ours(f, fn, [])
    except Exception: return 10**6
    B = cmpfn.retail(fn)
    s = abs(len(A) - len(B)) * 5
    for a, b in zip(A, B):
        ra = [cmpfn.num(r) for r in cmpfn.regs(a)]; rb = [cmpfn.num(r) for r in cmpfn.regs(b)]
        if len(ra) == len(rb): s += sum(x != y for x, y in zip(ra, rb))
        else: s += 1
    return s
def build(head, decls, tail): return head + "\n".join(decls) + "\n" + tail
if __name__ == "__main__":
    path, fn = sys.argv[1], sys.argv[2]
    head, decls, tail = parts(open(path).read(), fn)
    decls = [d for d in decls if d.strip()]
    print("decl lines:", len(decls))
    cur = score(build(head, decls, tail), fn, 0); print("start", cur); seen = {tuple(decls): cur}
    moves = [(i, j) for i in range(len(decls)) for j in range(len(decls)) if i != j]
    random.seed(1); random.shuffle(moves)
    improved = True
    while improved and cur > 0:
        improved = False
        cands = []
        for i, j in moves:
            d = decls[:]; x = d.pop(i); d.insert(j, x)
            if tuple(d) not in seen: cands.append(d)
        with cf.ThreadPoolExecutor(4) as ex:
            res = list(ex.map(lambda t: (score(build(head, t[1], tail), fn, t[0] % 8 + 1), t[1]), enumerate(cands)))
        for sc, d in res: seen[tuple(d)] = sc
        sc, d = min(res, key=lambda r: r[0])
        print("best neighbour", sc)
        if sc < cur: cur, decls, improved = sc, d, True; print("\n".join(decls))
    print("final", cur); open("/tmp/regrules/climb_best.c", "w").write(build(head, decls, tail))
