/*
 * C:\work2\usaex2\src\network\net_window\net_win_tab.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x0022D620-0x0022DA18
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
#ifndef DDR_UNIT_src_network_net_window_net_win_tab_c_H
#define DDR_UNIT_src_network_net_window_net_win_tab_c_H

#include "types/G_SYS_W_.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_tab_w.h"

/* variables (6) */
static int (*NetWin_TabFunc[3])(struct _CWS_WIN_W *);            /* @0x002BD6C8 size 0xC */
static void (*NetWin_TabCode[4])(struct _CWS_WIN_W *);           /* @0x002BD6E0 size 0x10 */
static struct _CWS_OBJ_TEX netwinmenu_plate_tab_line[6];         /* @0x002BD6F0 size 0x78 */
static struct _CWS_OBJ_TEX netwinmenu_plate_tab_box[5];          /* @0x002BD770 size 0x64 */
static struct _CWS_OBJ_SET netwintab[6];                         /* @0x002BD7E0 size 0x78 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */

/* functions defined (7) */
void NetWin_TabSetOff(struct _CWS_WIN_W *win);                   /* 0x0022D620-0x0022D6B0 lines 267-271 */
void NetWin_TabSetOn(struct _CWS_WIN_W *win, int tab_num);       /* 0x0022D6B0-0x0022D708 lines 251-260 */
void NetWin_TabSetSelect(struct _CWS_WIN_W *win, int tab_num);   /* 0x0022D710-0x0022D7BC lines 229-245 */
static int NetWin_TabEnd(struct _CWS_WIN_W *win);                /* 0x0022D7C0-0x0022D7D4 lines 221-223 */
static int NetWin_TabMain(struct _CWS_WIN_W *win);               /* 0x0022D7E0-0x0022D920 lines 185-216 */
static int NetWin_TabInit(struct _CWS_WIN_W *win);               /* 0x0022D920-0x0022D9B0 lines 168-178 */
int NetWin_Tab(struct _CWS_WIN_W *win);                          /* 0x0022D9B0-0x0022DA18 lines 157-163 */

#endif /* DDR_UNIT_src_network_net_window_net_win_tab_c_H */
