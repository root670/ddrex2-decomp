/*
 * C:\work2\usaex2\src\network\net_window\net_win_bar.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00248590-0x00248728
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
#ifndef DDR_UNIT_src_network_net_window_net_win_bar_c_H
#define DDR_UNIT_src_network_net_window_net_win_bar_c_H

#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_bar_w.h"

/* variables (3) */
static int (*NetWin_BarFunc[3])(struct _CWS_WIN_W *);            /* @0x002BF238 size 0xC */
static void (*NetWin_BarCode[4])(struct _CWS_WIN_W *);           /* @0x002BF250 size 0x10 */
static struct _CWS_OBJ_SET netwinbar[1];                         /* @0x002BF260 size 0x14 */

/* functions defined (9) */
void NetWin_BarSetH(struct _CWS_WIN_W *win, int h);              /* 0x00248590-0x00248598 lines 133-133 */
void NetWin_BarSetNow(struct _CWS_WIN_W *win, int now);          /* 0x002485A0-0x002485A8 lines 128-128 */
void NetWin_BarSetNum(struct _CWS_WIN_W *win, int num);          /* 0x002485B0-0x002485B8 lines 123-123 */
void NetWin_BarSetMax(struct _CWS_WIN_W *win, int max);          /* 0x002485C0-0x002485C8 lines 118-118 */
static void NetWin_BarDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x002485D0-0x00248644 lines 96-111 */
static int NetWin_BarEnd(struct _CWS_WIN_W *win);                /* 0x00248650-0x00248664 lines 91-93 */
static int NetWin_BarMain(void);                                 /* 0x00248670-0x00248678 lines 86-86 */
static int NetWin_BarInit(struct _CWS_WIN_W *win);               /* 0x00248680-0x002486C0 lines 71-79 */
int NetWin_Bar(struct _CWS_WIN_W *win);                          /* 0x002486C0-0x00248728 lines 60-66 */

#endif /* DDR_UNIT_src_network_net_window_net_win_bar_c_H */
