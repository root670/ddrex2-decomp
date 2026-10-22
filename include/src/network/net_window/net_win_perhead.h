/*
 * C:\work2\usaex2\src\network\net_window\net_win_perhead.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00285600-0x00285D68
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
#ifndef DDR_UNIT_src_network_net_window_net_win_perhead_c_H
#define DDR_UNIT_src_network_net_window_net_win_perhead_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_nsv_user_htoh_week_log_work.h"

/* variables (7) */
static int (*NetWin_PerHeadFunc[3])(struct _CWS_WIN_W *);        /* @0x002C1050 size 0xC */
static void (*NetWin_PerHeadCode[4])(struct _CWS_WIN_W *);       /* @0x002C1060 size 0x10 */
static unsigned char *perstats_title[5];                         /* not allocated size 0x14 */
static struct _CWS_OBJ_TEX per_stats_match[4];                   /* @0x002C1070 size 0x50 */
static struct _CWS_OBJ_TEX per_stats_title[5];                   /* @0x002C10C0 size 0x64 */
static struct _CWS_OBJ_TEX per_stats_borad[30];                  /* @0x002C1130 size 0x258 */
static struct _CWS_OBJ_SET netwinperhed[3];                      /* @0x002C1390 size 0x3C */

/* functions defined (4) */
static int NetWin_PerHeadEnd(struct _CWS_WIN_W *win);            /* 0x00285600-0x00285614 lines 460-462 */
static int NetWin_PerHeadMain(struct _CWS_WIN_W *win);           /* 0x00285620-0x00285C78 lines 378-455 */
static int NetWin_PerHeadInit(struct _CWS_WIN_W *win);           /* 0x00285C80-0x00285CFC lines 334-374 */
int NetWin_PerHead(struct _CWS_WIN_W *win);                      /* 0x00285D00-0x00285D68 lines 323-329 */

#endif /* DDR_UNIT_src_network_net_window_net_win_perhead_c_H */
