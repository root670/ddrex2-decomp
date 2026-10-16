/*
 * C:\work2\usaex2\src\network\net_window\net_win_peruser.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x002853E0-0x002855F8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_peruser_c_H
#define DDR_UNIT_src_network_net_window_net_win_peruser_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (1) */

/* anon_0_165 -- @anon0, 0x8 bytes, net_win_peruser.c (DIE 0x2F4B63) */
struct anon_0_165 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (9) */
static int (*NetWin_PerUserPointFunc[3])(struct _CWS_WIN_W *);   /* @0x002C0F90 size 0xC */
static int (*NetWin_PerUserTimeFunc[3])(struct _CWS_WIN_W *);    /* not allocated size 0xC */
static void (*NetWin_PerUserCode[4])(struct _CWS_WIN_W *);       /* @0x002C0FA0 size 0x10 */
static struct _CWS_OBJ_TEX netwinperuser_chara[1];               /* @0x002C0FB0 size 0x14 */
static struct _CWS_OBJ_TEX netwinperuser_name[1];                /* @0x002C0FD0 size 0x14 */
static struct _CWS_OBJ_TEX netwinperuser_point[1];               /* @0x002C0FF0 size 0x14 */
static struct _CWS_OBJ_TEX netwinperuser_time[1];                /* not allocated size 0x14 */
static struct _CWS_OBJ_SET netwinperuser0[3];                    /* @0x002C1010 size 0x3C */
static struct _CWS_OBJ_SET netwinperuser1[3];                    /* not allocated size 0x3C */

/* functions defined (4) */
static int NetWin_PerUserPointEnd(struct _CWS_WIN_W *win);       /* 0x002853E0-0x002853F4 lines 286-288 */
static int NetWin_PerUserPointMain(void);                        /* 0x00285400-0x00285408 lines 281-281 */
static int NetWin_PerUserPointInit(struct _CWS_WIN_W *win);      /* 0x00285410-0x00285590 lines 209-238 */
int NetWin_PerUserPoint(struct _CWS_WIN_W *win);                 /* 0x00285590-0x002855F8 lines 200-206 */

#endif /* DDR_UNIT_src_network_net_window_net_win_peruser_c_H */
