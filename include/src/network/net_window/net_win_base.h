/*
 * C:\work2\usaex2\src\network\net_window\net_win_base.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x00283390-0x00283818
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_base_c_H
#define DDR_UNIT_src_network_net_window_net_win_base_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (3) */

/* anon_0_163 -- @anon0, 0x8 bytes, net_win_base.c (DIE 0x2F0954) */
struct anon_0_163 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_2_163 -- @anon2, 0x4 bytes, net_win_base.c (DIE 0x2F16DC) */
union anon_2_163 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_163 -- @anon1, 0x34 bytes, net_win_base.c (DIE 0x2F0F34) */
struct anon_1_163 {   // size 0x34
    /* 0x000 */ union anon_2_163 x0;                  // 0x4
    /* 0x004 */ union anon_2_163 y0;                  // 0x4
    /* 0x008 */ union anon_2_163 x1;                  // 0x4
    /* 0x00C */ union anon_2_163 y1;                  // 0x4
    /* 0x010 */ union anon_2_163 x2;                  // 0x4
    /* 0x014 */ union anon_2_163 y2;                  // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
};


/* variables (5) */
static int (*NetWin_BaseFunc[3])(struct _CWS_WIN_W *);           /* @0x002C0E88 size 0xC */
static void (*NetWin_BaseCode[4])(struct _CWS_WIN_W *);          /* @0x002C0EA0 size 0x10 */
static struct _CWS_OBJ_TEX netwinbase_plate_back[1];             /* @0x002C0EB0 size 0x14 */
static struct _CWS_OBJ_TEX netwinbase_plate_cover[1];            /* @0x002C0ED0 size 0x14 */
static struct _CWS_OBJ_SET netwinbase[2];                        /* @0x002C0EF0 size 0x28 */

/* functions defined (6) */
void NetWin_BaseSetName(struct _CWS_WIN_W *win, unsigned char *_str); /* 0x00283390-0x0028339C lines 187-187 */
static void NetWin_BaseBoardDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x002833A0-0x002836B8 lines 126-182 */
static int NetWin_BaseEnd(struct _CWS_WIN_W *win);               /* 0x002836C0-0x002836D4 lines 120-122 */
static int NetWin_BaseMain(void);                                /* 0x002836E0-0x002836E8 lines 115-115 */
static int NetWin_BaseInit(struct _CWS_WIN_W *win);              /* 0x002836F0-0x002837AC lines 95-106 */
int NetWin_Base(struct _CWS_WIN_W *win);                         /* 0x002837B0-0x00283818 lines 84-90 */

#endif /* DDR_UNIT_src_network_net_window_net_win_base_c_H */
