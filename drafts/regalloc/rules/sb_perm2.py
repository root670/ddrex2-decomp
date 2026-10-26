import itertools, sys, pathlib, re
sys.path.insert(0, str(pathlib.Path(__file__).parent))
import cc
decls = {"p": "unsigned int *p;", "i": "int i;", "work": "W *work;", "x": "unsigned int *music_addr;", "y": "int ofs;", "z": "unsigned int *base_addr;"}
T = """typedef struct { char pad[12]; char *course_data_addr; } W;
extern W *shop_get_work(void);
extern void func_0012CF10(void *, int);
void shop_bind_nm(void) {
%s
    work = shop_get_work();
    p = (unsigned int *)0xA7D350;
    for (i = 0; i < 0x4C; i++) {
        base_addr = (unsigned int *)0xA7D350;
        ofs = *p++;
        music_addr = (unsigned int *)((int)base_addr + ofs);
        func_0012CF10((char *)music_addr + *music_addr, i + 0xD8);
    }
    for (i = 0; i < 0x1D; i++) {
        ofs = i * 8;
        base_addr = (unsigned int *)work->course_data_addr;
        func_0012CF10((char *)base_addr + *(unsigned int *)((char *)base_addr + ofs), i + 0x124);
    }
}
"""
seen = {}
for p in itertools.permutations("p i work".split()):
    names = list(p) + ["x", "y", "z"]
    f = pathlib.Path("/tmp/regrules/sp2.c"); f.write_text(T % "\n".join("    " + decls[k] for k in names))
    d = cc.dis(f)
    g = lambda r: (re.search(r, d) or [None, "?"])[1]
    print(p, "p=", g(r"lw\s+v1,0\((s\d)\)"), "i1=", g(r"addiu\s+a1,(s\d),216"), "work=", g(r"lw\s+v1,12\((s\d)\)"), "i2=", g(r"addiu\s+a1,(s\d),292"), "ofs2=", g(r"addu\s+v0,v1,(s\d)"))
