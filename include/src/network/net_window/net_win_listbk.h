/*
 * C:\work2\usaex2\src\network\net_window\net_win_listbk.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x002576D0-0x00257D68
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_listbk_c_H
#define DDR_UNIT_src_network_net_window_net_win_listbk_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (4) */

/* anon_0_136 -- @anon0, 0x8 bytes, net_win_listbk.c (DIE 0x253285) */
struct anon_0_136 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_136 -- @anon1, 0x48 bytes, net_win_listbk.c (DIE 0x2536C8) */
struct anon_1_136 {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02C */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03A */ unsigned short tw;                    // 0x2
    /* 0x03C */ unsigned short th;                    // 0x2
    /* 0x03E */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
};

/* anon_2_136 -- @anon2, 0x4 bytes, net_win_listbk.c (DIE 0x253E1C) */
union anon_2_136 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_136 -- @anon3, 0x30 bytes, net_win_listbk.c (DIE 0x2540E0) */
struct anon_3_136 {   // size 0x30
    /* 0x000 */ union anon_2_136 x0;                  // 0x4
    /* 0x004 */ union anon_2_136 y0;                  // 0x4
    /* 0x008 */ union anon_2_136 x1;                  // 0x4
    /* 0x00C */ union anon_2_136 y1;                  // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
};


/* variables (4) */
static int (*NetWin_ListbkFunc[3])(struct _CWS_WIN_W *);         /* @0x002BF5F0 size 0xC */
static void (*NetWin_ListbkCode[4])(struct _CWS_WIN_W *);        /* @0x002BF600 size 0x10 */
static struct _CWS_OBJ_TEX netwinslby_plate_back[9];             /* @0x002BF610 size 0xB4 */
static struct _CWS_OBJ_SET netwinlistbk[1];                      /* @0x002BF6D0 size 0x14 */

/* functions defined (5) */
static void CwsWin_ListbkDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x002576D0-0x00257C90 lines 131-236 */
static int NetWin_ListbkEnd(struct _CWS_WIN_W *win);             /* 0x00257C90-0x00257CA4 lines 126-128 */
static int NetWin_ListbkMain(void);                              /* 0x00257CB0-0x00257CB8 lines 121-121 */
static int NetWin_ListbkInit(struct _CWS_WIN_W *win);            /* 0x00257CC0-0x00257D00 lines 107-115 */
int NetWin_Listbk(struct _CWS_WIN_W *win);                       /* 0x00257D00-0x00257D68 lines 96-102 */

#endif /* DDR_UNIT_src_network_net_window_net_win_listbk_c_H */
