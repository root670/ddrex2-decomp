/*
 * C:\work2\usaex2\src\network\net_window\net_win_perpoint.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00285D70-0x00286388
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_perpoint_c_H
#define DDR_UNIT_src_network_net_window_net_win_perpoint_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_nsv_user_point_week_log_work.h"

/* variables (7) */
static int (*NetWin_PerPointFunc[3])(struct _CWS_WIN_W *);       /* @0x002C13D0 size 0xC */
static void (*NetWin_PerPointCode[4])(struct _CWS_WIN_W *);      /* @0x002C13E0 size 0x10 */
static unsigned char *perstats_title[5];                         /* not allocated size 0x14 */
static struct _CWS_OBJ_TEX per_stats_match[2];                   /* @0x002C13F0 size 0x28 */
static struct _CWS_OBJ_TEX per_stats_title[3];                   /* @0x002C1420 size 0x3C */
static struct _CWS_OBJ_TEX per_stats_borad[18];                  /* @0x002C1460 size 0x168 */
static struct _CWS_OBJ_SET netwinperhed[3];                      /* @0x002C15D0 size 0x3C */

/* functions defined (4) */
static int NetWin_PerPointEnd(struct _CWS_WIN_W *win);           /* 0x00285D70-0x00285D84 lines 359-361 */
static int NetWin_PerPointMain(struct _CWS_WIN_W *win);          /* 0x00285D90-0x002862A0 lines 285-354 */
static int NetWin_PerPointInit(struct _CWS_WIN_W *win);          /* 0x002862A0-0x0028631C lines 265-281 */
int NetWin_PerPoint(struct _CWS_WIN_W *win);                     /* 0x00286320-0x00286388 lines 254-260 */

#endif /* DDR_UNIT_src_network_net_window_net_win_perpoint_c_H */
