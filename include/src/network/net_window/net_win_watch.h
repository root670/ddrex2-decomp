/*
 * C:\work2\usaex2\src\network\net_window\net_win_watch.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x0022DA20-0x0022DDD8
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
#ifndef DDR_UNIT_src_network_net_window_net_win_watch_c_H
#define DDR_UNIT_src_network_net_window_net_win_watch_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_watch_w.h"

/* variables (4) */
static int (*NetWin_WatchFunc[3])(struct _CWS_WIN_W *);          /* @0x002BD858 size 0xC */
static void (*NetWin_WatchCode[4])(struct _CWS_WIN_W *);         /* @0x002BD870 size 0x10 */
static struct _CWS_OBJ_TEX netwinwatch_plate_obj[3];             /* @0x002BD880 size 0x3C */
static struct _CWS_OBJ_SET netwinwatch[3];                       /* @0x002BD8C0 size 0x3C */

/* functions defined (6) */
void NetWin_WatchSetRestTime(struct _CWS_WIN_W *win, unsigned int rest_time); /* 0x0022DA20-0x0022DAA0 lines 195-202 */
void NetWin_WatchSetWeek(struct _CWS_WIN_W *win, char week);     /* 0x0022DAA0-0x0022DAD0 lines 184-189 */
static int NetWin_WatchEnd(struct _CWS_WIN_W *win);              /* 0x0022DAD0-0x0022DAE4 lines 175-177 */
static int NetWin_WatchMain(struct _CWS_WIN_W *win);             /* 0x0022DAF0-0x0022DC38 lines 144-170 */
static int NetWin_WatchInit(struct _CWS_WIN_W *win);             /* 0x0022DC40-0x0022DD68 lines 121-141 */
int NetWin_Watch(struct _CWS_WIN_W *win);                        /* 0x0022DD70-0x0022DDD8 lines 110-116 */

#endif /* DDR_UNIT_src_network_net_window_net_win_watch_c_H */
