/*
 * C:\work2\usaex2\src\network\net_window\net_win_perrank.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00286390-0x00286748
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
#ifndef DDR_UNIT_src_network_net_window_net_win_perrank_c_H
#define DDR_UNIT_src_network_net_window_net_win_perrank_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_nsv_user_rc_param_work.h"

/* variables (7) */
static int (*NetWin_PerRankFunc[3])(struct _CWS_WIN_W *);        /* @0x002C1610 size 0xC */
static void (*NetWin_PerRankCode[4])(struct _CWS_WIN_W *);       /* @0x002C1620 size 0x10 */
static unsigned char *perstats_title[5];                         /* not allocated size 0x14 */
static struct _CWS_OBJ_TEX per_stats_rank[3];                    /* @0x002C1630 size 0x3C */
static struct _CWS_OBJ_TEX per_stats_title[3];                   /* @0x002C1670 size 0x3C */
static struct _CWS_OBJ_TEX per_stats_borad[18];                  /* @0x002C16B0 size 0x168 */
static struct _CWS_OBJ_SET netwinperhed[3];                      /* @0x002C1820 size 0x3C */

/* functions defined (4) */
static int NetWin_PerRankEnd(struct _CWS_WIN_W *win);            /* 0x00286390-0x002863A4 lines 338-340 */
static int NetWin_PerRankMain(struct _CWS_WIN_W *win);           /* 0x002863B0-0x00286654 lines 285-333 */
static int NetWin_PerRankInit(struct _CWS_WIN_W *win);           /* 0x00286660-0x002866DC lines 272-281 */
int NetWin_PerRank(struct _CWS_WIN_W *win);                      /* 0x002866E0-0x00286748 lines 261-267 */

#endif /* DDR_UNIT_src_network_net_window_net_win_perrank_c_H */
