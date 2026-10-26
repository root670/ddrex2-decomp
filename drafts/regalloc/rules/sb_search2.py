"""shop_bind_nm with a declared table pointer `tbl` (tbl[i] in loop 1): permutations of the 6 declarations."""
import itertools, sys, pathlib, concurrent.futures as cf
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import climb, cmpfn
sys.path.insert(0, str(pathlib.Path(__file__).parent))
HDR = open(pathlib.Path(__file__).parent / "sb_hdr.txt").read()
L2 = """    for (i = 0; i < 0x1D; i++) {
        ofs = i * 8;
        base_addr = (unsigned int *)work->course_data_addr;
        func_0012CF10((char *)base_addr + *(unsigned int *)((char *)base_addr + ofs), i + 0x124);
    }
}
"""
DECL = {"tbl": "unsigned int *tbl;", "work": "W *work;", "i": "int i;", "music_addr": "unsigned int *music_addr;",
        "ofs": "int ofs;", "base_addr": "unsigned int *base_addr;"}
V = {"A": """    work = shop_get_work();
    tbl = (unsigned int *)0xA7D350;
    for (i = 0; i < 0x4C; i++) {
        base_addr = (unsigned int *)0xA7D350;
        ofs = tbl[i];
        music_addr = (unsigned int *)((int)base_addr + ofs);
        func_0012CF10((char *)music_addr + *music_addr, i + 0xD8);
    }
"""}
def job(a):
    v, order = a
    src = HDR + "".join("    " + DECL[k] + "\n" for k in order) + V[v] + L2
    return order, climb.score(src, "shop_bind_nm", 0)
if __name__ == "__main__":
    jobs = [(v, o) for v in V for o in itertools.permutations(DECL)]
    with cf.ThreadPoolExecutor(4) as ex:
        res = sorted(ex.map(job, jobs), key=lambda r: r[1])
    for o, s in res[:8]: print(s, o)
