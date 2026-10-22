/*
 * C:\work2\usaex2\src\network\net_window\net_win_suser.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0022CCF0-0x0022D618
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
#ifndef DDR_UNIT_src_network_net_window_net_win_suser_c_H
#define DDR_UNIT_src_network_net_window_net_win_suser_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/_net_win_suser_w.h"

/* variables (10) */
static int (*NetWin_SuserFunc[3])(struct _CWS_WIN_W *);          /* @0x002BD390 size 0xC */
static void (*NetWin_SuserCode[4])(struct _CWS_WIN_W *);         /* @0x002BD3A0 size 0x10 */
static struct _CWS_OBJ_TEX netwinsuser_plate_board_off[9];       /* @0x002BD3B0 size 0xB4 */
static struct _CWS_OBJ_TEX netwinsuser_plate_board_on[9];        /* @0x002BD470 size 0xB4 */
static struct _CWS_OBJ_TEX netwinsuser_plate_col00[3];           /* @0x002BD530 size 0x3C */
static struct _CWS_OBJ_TEX netwinsuser_plate_col01[3];           /* @0x002BD570 size 0x3C */
static struct _CWS_OBJ_TEX netwinsuser_plate_namewaku[3];        /* @0x002BD5B0 size 0x3C */
static struct _CWS_OBJ_TEX netwinsuser_plate_obj[3];             /* @0x002BD5F0 size 0x3C */
static struct _CWS_OBJ_TEX netwinsuser_plate_chara[1];           /* @0x002BD630 size 0x14 */
static struct _CWS_OBJ_SET netwinsuser[6];                       /* @0x002BD650 size 0x78 */

/* functions defined (8) */
void NetWin_SuserSetEntryMode(struct _CWS_WIN_W *win, char onoff); /* 0x0022CCF0-0x0022CD20 lines 549-556 */
void NetWin_SuserSetUserFile(struct _CWS_WIN_W *win, struct _NSV_USER_FILE_WORK *addr); /* 0x0022CD20-0x0022CD28 lines 543-543 */
void NetWin_SuserSetSelect(struct _CWS_WIN_W *win, int status);  /* 0x0022CD30-0x0022CDB0 lines 521-535 */
void NetWin_SuserSetNum(struct _CWS_WIN_W *win, int file_num);   /* 0x0022CDB0-0x0022CE04 lines 505-517 */
static int NetWin_SuserEnd(struct _CWS_WIN_W *win);              /* 0x0022CE10-0x0022CE24 lines 497-499 */
static int NetWin_SuserMain(struct _CWS_WIN_W *win);             /* 0x0022CE30-0x0022D22C lines 423-492 */
static int NetWin_SuserInit(struct _CWS_WIN_W *win);             /* 0x0022D230-0x0022D5B0 lines 354-420 */
int NetWin_Suser(struct _CWS_WIN_W *win);                        /* 0x0022D5B0-0x0022D618 lines 343-349 */

#endif /* DDR_UNIT_src_network_net_window_net_win_suser_c_H */
