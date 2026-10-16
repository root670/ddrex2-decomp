/*
 * C:\work2\usaex2\src\CS\info\infodoll.c
 * MW MIPS C Compiler, overlay info_rel4cd.prg; 5 functions, code 0x007F4D90-0x007F506C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_info_infodoll_c_H
#define DDR_UNIT_src_CS_info_infodoll_c_H

/* anonymous types (2) */

/* anon_0_184 -- @anon0, 0x18 bytes, infodoll.c (DIE 0x33F2FF) */
struct anon_0_184 {   // size 0x18
    /* 0x000 */ void *loadaddr;                       // 0x4
    /* 0x004 */ float cx;                             // 0x4
    /* 0x008 */ float cy;                             // 0x4
    /* 0x00C */ int p_counter;                        // 0x4
    /* 0x010 */ short step;                           // 0x2
    /* 0x012 */ short new_chr;                        // 0x2
    /* 0x014 */ short cur_chr;                        // 0x2
    /* 0x016 */ char loading;                         // 0x1
    /* 0x017 */ char req_in;                          // 0x1
};

/* anon_1_184 -- @anon1, 0x8 bytes, infodoll.c (DIE 0x33F45A) */
struct anon_1_184 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (3) */
static struct anon_1_184 crect;                                  /* @0x002DDE60 size 0x8 */
static struct anon_0_184 *wk;                                    /* @0x002DDE68 size 0x4 */
static struct anon_0_184 idd_work;                               /* @0x008078A0 size 0x18 */

/* functions defined (5) */
void req_info_doll_chara(int chara);                             /* 0x007F4D90-0x007F4DAC lines 253-257 */
void req_info_doll_in(int sw);                                   /* 0x007F4DB0-0x007F4DBC lines 243-245 */
int is_info_doll_loading(void);                                  /* 0x007F4DC0-0x007F4DCC lines 233-235 */
void View_InfoDollDisp(int disp);                                /* 0x007F4DD0-0x007F5018 lines 115-225 */
void Init_InfoDollDisp(void);                                    /* 0x007F5020-0x007F506C lines 89-109 */

#endif /* DDR_UNIT_src_CS_info_infodoll_c_H */
