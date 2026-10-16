/*
 * C:\work2\usaex2\src\network\net_window\net_win_infosel.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x00271F70-0x00272328
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_infosel_c_H
#define DDR_UNIT_src_network_net_window_net_win_infosel_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (1) */

/* anon_0_151 -- @anon0, 0x8 bytes, net_win_infosel.c (DIE 0x2A0EAA) */
struct anon_0_151 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (6) */
static int (*NetWin_InfoselFunc[3])(struct _CWS_WIN_W *);        /* @0x002C0760 size 0xC */
static void (*NetWin_InfoselCode[4])(struct _CWS_WIN_W *);       /* @0x002C0770 size 0x10 */
static struct _CWS_OBJ_TEX netwinslby_plate_board[3];            /* @0x002C0780 size 0x3C */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_back[1];       /* @0x002C07C0 size 0x14 */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_face[1];       /* @0x002C07E0 size 0x14 */
static struct _CWS_OBJ_SET netwininfosel[3];                     /* @0x002C0800 size 0x3C */

/* functions defined (8) */
void NetWin_InfoselSetPoint(struct _CWS_WIN_W *win, int rule, unsigned int _point); /* 0x00271F70-0x00272064 lines 189-205 */
void NetWin_InfoselSetDancer(struct _CWS_WIN_W *win, int _num);  /* 0x00272070-0x002720FC lines 180-186 */
void NetWin_InfoselSetName(struct _CWS_WIN_W *win, unsigned char *_name); /* 0x00272100-0x00272114 lines 177-177 */
void NetWin_InfoselSetNumber(struct _CWS_WIN_W *win, int _num);  /* 0x00272120-0x00272134 lines 173-173 */
static int NetWin_InfoselEnd(struct _CWS_WIN_W *win);            /* 0x00272140-0x00272154 lines 164-166 */
static int NetWin_InfoselMain(void);                             /* 0x00272160-0x00272168 lines 159-159 */
static int NetWin_InfoselInit(struct _CWS_WIN_W *win);           /* 0x00272170-0x002722C0 lines 132-153 */
int NetWin_Infosel(struct _CWS_WIN_W *win);                      /* 0x002722C0-0x00272328 lines 121-127 */

#endif /* DDR_UNIT_src_network_net_window_net_win_infosel_c_H */
