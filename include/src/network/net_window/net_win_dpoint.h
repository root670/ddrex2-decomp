/*
 * C:\work2\usaex2\src\network\net_window\net_win_dpoint.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x00287A50-0x00287DE8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_dpoint_c_H
#define DDR_UNIT_src_network_net_window_net_win_dpoint_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* variables (6) */
static int (*NetWin_DPointFunc[3])(struct _CWS_WIN_W *);         /* @0x002C1CB0 size 0xC */
static void (*NetWin_DPointCode[4])(struct _CWS_WIN_W *);        /* @0x002C1CC0 size 0x10 */
static struct _CWS_OBJ_TEX netwinslby_plate_board[3];            /* @0x002C1CD0 size 0x3C */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_back[1];       /* @0x002C1D10 size 0x14 */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_face[1];       /* @0x002C1D30 size 0x14 */
static struct _CWS_OBJ_SET netwininfosel[3];                     /* @0x002C1D50 size 0x3C */

/* functions defined (8) */
void NetWin_DPointSetDancer(struct _CWS_WIN_W *win, int dancer_id); /* 0x00287A50-0x00287ACC lines 219-223 */
void NetWin_DPointSetPoint(struct _CWS_WIN_W *win, int rule, unsigned int _point); /* 0x00287AD0-0x00287BC4 lines 201-217 */
void NetWin_DPointSetName(struct _CWS_WIN_W *win, unsigned char *_name); /* 0x00287BD0-0x00287BE4 lines 197-197 */
void NetWin_DPointSetNumber(struct _CWS_WIN_W *win, int _num);   /* 0x00287BF0-0x00287C04 lines 193-193 */
static int NetWin_DPointEnd(struct _CWS_WIN_W *win);             /* 0x00287C10-0x00287C24 lines 184-186 */
static int NetWin_DPointMain(void);                              /* 0x00287C30-0x00287C38 lines 179-179 */
static int NetWin_DPointInit(struct _CWS_WIN_W *win);            /* 0x00287C40-0x00287D80 lines 132-154 */
int NetWin_DPoint(struct _CWS_WIN_W *win);                       /* 0x00287D80-0x00287DE8 lines 121-127 */

#endif /* DDR_UNIT_src_network_net_window_net_win_dpoint_c_H */
