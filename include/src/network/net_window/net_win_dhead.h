/*
 * C:\work2\usaex2\src\network\net_window\net_win_dhead.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x002876F0-0x00287A48
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_dhead_c_H
#define DDR_UNIT_src_network_net_window_net_win_dhead_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* variables (6) */
static int (*NetWin_DHeadFunc[3])(struct _CWS_WIN_W *);          /* @0x002C1BC0 size 0xC */
static void (*NetWin_DHeadCode[4])(struct _CWS_WIN_W *);         /* @0x002C1BD0 size 0x10 */
static struct _CWS_OBJ_TEX netwinslby_plate_board[4];            /* @0x002C1BE0 size 0x50 */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_back[1];       /* @0x002C1C30 size 0x14 */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_face[1];       /* @0x002C1C50 size 0x14 */
static struct _CWS_OBJ_SET netwininfosel[3];                     /* @0x002C1C70 size 0x3C */

/* functions defined (8) */
void NetWin_DHeadSetPoint(struct _CWS_WIN_W *win, int rule, unsigned int _point); /* 0x002876F0-0x0028775C lines 226-241 */
void NetWin_DHeadSetDancer(struct _CWS_WIN_W *win, int dancer_id); /* 0x00287760-0x002877DC lines 217-221 */
void NetWin_DHeadSetName(struct _CWS_WIN_W *win, unsigned char *_name); /* 0x002877E0-0x002877F4 lines 214-214 */
void NetWin_DHeadSetNumber(struct _CWS_WIN_W *win, int _num);    /* 0x00287800-0x00287814 lines 210-210 */
static int NetWin_DHeadEnd(struct _CWS_WIN_W *win);              /* 0x00287820-0x00287834 lines 201-203 */
static int NetWin_DHeadMain(void);                               /* 0x00287840-0x00287848 lines 196-196 */
static int NetWin_DHeadInit(struct _CWS_WIN_W *win);             /* 0x00287850-0x002879D4 lines 145-171 */
int NetWin_DHead(struct _CWS_WIN_W *win);                        /* 0x002879E0-0x00287A48 lines 134-140 */

#endif /* DDR_UNIT_src_network_net_window_net_win_dhead_c_H */
