/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_main.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x00224270-0x0022457C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_main_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_main_c_H

#include "types/_NETWORK_W.h"
#include "types/g_game_w.h"

/* anonymous types (7) */

/* anon_0_77 -- @anon0, 0x8 bytes, net_sys_main.c (DIE 0x14B8E1) */
struct anon_0_77 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_77 -- @anon1, 0x4 bytes, net_sys_main.c (DIE 0x14D988) */
struct anon_1_77 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_2_77 -- @anon2, 0x18 bytes, net_sys_main.c (DIE 0x14E195) */
struct anon_2_77 {   // size 0x18
    /* 0x000 */ void *func;                           // 0x4
    /* 0x004 */ int x;                                // 0x4
    /* 0x008 */ int y;                                // 0x4
    /* 0x00C */ int w;                                // 0x4
    /* 0x010 */ int h;                                // 0x4
    /* 0x014 */ int z;                                // 0x4
};

/* anon_4_77 -- @anon4, 0x4 bytes, net_sys_main.c (DIE 0x150761) */
union anon_4_77 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_5_77 -- @anon5, 0x10 bytes, net_sys_main.c (DIE 0x151520) */
struct anon_5_77 {   // size 0x10
    /* 0x000 */ union anon_4_77 x0;                   // 0x4
    /* 0x004 */ union anon_4_77 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_3_77 -- @anon3, 0x184 bytes, net_sys_main.c (DIE 0x14F239) */
struct anon_3_77 {   // size 0x184
    /* 0x000 */ struct anon_5_77 line_a[8];           // 0x80
    /* 0x080 */ struct anon_5_77 line_b[8];           // 0x80
    /* 0x100 */ struct anon_5_77 line_c[8];           // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_6_77 -- @anon6, 0x14 bytes, net_sys_main.c (DIE 0x151A7E) */
struct anon_6_77 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};


/* variables (1) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (2) */
void NetSysRuleStartInit(struct _NETWORK_W *);                   /* @0x00228290 */
void NetSysTopInit(struct _NETWORK_W *);                         /* @0x00226600 */

/* functions defined (2) */
void NetSysEnd(struct _NETWORK_W *netw);                         /* 0x00224270-0x00224330 lines 150-183 */
void NetSysInit(struct _NETWORK_W *netw);                        /* 0x00224330-0x0022457C lines 14-146 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_main_c_H */
