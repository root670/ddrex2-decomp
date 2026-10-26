"""shop_bind_nm: body variants x declaration permutations; score = register mismatches + word-count gap against retail."""
import itertools, sys, pathlib, re, collections, concurrent.futures as cf
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cmpfn, cc
HDR = """typedef struct { char pad[12]; char *course_data_addr; } W;
extern W *shop_get_work(void);
extern void func_0012CF10(void *, int);
void shop_bind_nm(void) {
"""
DECL = {"music_addr": "unsigned int *music_addr;", "ofs": "int ofs;", "i": "int i;",
        "base_addr": "unsigned int *base_addr;", "work": "W *work;"}
L2 = """    for (i = 0; i < 0x1D; i++) {
        ofs = i * 8;
        base_addr = (unsigned int *)work->course_data_addr;
        func_0012CF10((char *)base_addr + *(unsigned int *)((char *)base_addr + ofs), i + 0x124);
    }
}
"""
BODY = {
 "V1": """    work = shop_get_work();
    for (i = 0; i < 0x4C; i++) {
        base_addr = (unsigned int *)0xA7D350;
        ofs = base_addr[i];
        music_addr = (unsigned int *)((int)base_addr + ofs);
        func_0012CF10((char *)music_addr + *music_addr, i + 0xD8);
    }
""",
 "V2": """    base_addr = (unsigned int *)0xA7D350;
    work = shop_get_work();
    for (i = 0; i < 0x4C; i++) {
        ofs = base_addr[i];
        music_addr = (unsigned int *)((int)base_addr + ofs);
        func_0012CF10((char *)music_addr + *music_addr, i + 0xD8);
    }
""",
 "V3": """    work = shop_get_work();
    base_addr = (unsigned int *)0xA7D350;
    for (i = 0; i < 0x4C; i++) {
        ofs = base_addr[i];
        music_addr = (unsigned int *)((int)base_addr + ofs);
        func_0012CF10((char *)music_addr + *music_addr, i + 0xD8);
    }
""",
}
def score(args):
    var, order, n = args
    src = HDR + "".join("    " + DECL[k] + "\n" for k in order) + BODY[var] + L2
    f = pathlib.Path(f"/tmp/regrules/sbs{n}.c"); f.write_text(src)
    try:
        A = cmpfn.ours(f, "shop_bind_nm", [])
    except Exception as e:
        return var, order, None
    B = cmpfn.retail("shop_bind_nm")
    sub = 0
    for a, b in zip(A, B):
        ra = [cmpfn.num(r) for r in cmpfn.regs(a)]; rb = [cmpfn.num(r) for r in cmpfn.regs(b)]
        if len(ra) == len(rb): sub += sum(x != y for x, y in zip(ra, rb))
    return var, order, (len(A) - len(B), sub)
if __name__ == "__main__":
    jobs = [(v, o, k) for k, (v, o) in enumerate((v, o) for v in BODY for o in itertools.permutations(DECL))]
    best = collections.defaultdict(list)
    with cf.ThreadPoolExecutor(4) as ex:
        for var, order, sc in ex.map(score, jobs):
            if sc: best[(var, sc)].append(order)
    for k, v in sorted(best.items(), key=lambda kv: (abs(kv[0][1][0]), kv[0][1][1]))[:12]:
        print(k, len(v), v[0])
