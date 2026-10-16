/*
 * C:\work2\usaex2\src\network\net_window\net_win_slby.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x00256FF0-0x00257448
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_slby_c_H
#define DDR_UNIT_src_network_net_window_net_win_slby_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_slby_w.h"

/* anonymous types (1) */

/* anon_0_134 -- @anon0, 0x8 bytes, net_win_slby.c (DIE 0x250616) */
struct anon_0_134 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (7) */
static int (*NetWin_SlbyFunc[3])(struct _CWS_WIN_W *);           /* @0x002BF3B0 size 0xC */
static void (*NetWin_SlbyCode[4])(struct _CWS_WIN_W *);          /* @0x002BF3C0 size 0x10 */
static struct _CWS_OBJ_TEX netwinslby_plate_waku_off[9];         /* @0x002BF3D0 size 0xB4 */
static struct _CWS_OBJ_TEX netwinslby_plate_waku_on[9];          /* @0x002BF490 size 0xB4 */
static struct _CWS_OBJ_TEX netwinslby_plate_graph[3];            /* @0x002BF550 size 0x3C */
static struct _CWS_OBJ_TEX netwinslby_plate_gauge[1];            /* @0x002BF590 size 0x14 */
static struct _CWS_OBJ_SET netwinslby[3];                        /* @0x002BF5B0 size 0x3C */

/* functions defined (8) */
void NetWin_SlbySetMaxNum(struct _CWS_WIN_W *win, int _maxnum);  /* 0x00256FF0-0x00257080 lines 314-325 */
void NetWin_SlbySetNowNum(struct _CWS_WIN_W *win, int _nownum);  /* 0x00257080-0x00257110 lines 299-310 */
void NetWin_SlbySetName(struct _CWS_WIN_W *win, unsigned char *name); /* 0x00257110-0x00257124 lines 294-294 */
void NetWin_SlbySetSelect(struct _CWS_WIN_W *win, char status);  /* 0x00257130-0x002571B8 lines 275-289 */
static int NetWin_SlbyEnd(struct _CWS_WIN_W *win);               /* 0x002571C0-0x002571D4 lines 265-267 */
static int NetWin_SlbyMain(struct _CWS_WIN_W *win);              /* 0x002571E0-0x00257228 lines 252-260 */
static int NetWin_SlbyInit(struct _CWS_WIN_W *win);              /* 0x00257230-0x002573DC lines 219-248 */
int NetWin_Slby(struct _CWS_WIN_W *win);                         /* 0x002573E0-0x00257448 lines 208-214 */

#endif /* DDR_UNIT_src_network_net_window_net_win_slby_c_H */
