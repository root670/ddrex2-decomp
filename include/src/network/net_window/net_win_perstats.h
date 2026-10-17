/*
 * C:\work2\usaex2\src\network\net_window\net_win_perstats.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00286750-0x00286F88
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_perstats_c_H
#define DDR_UNIT_src_network_net_window_net_win_perstats_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* variables (7) */
static int (*NetWin_PerStatsFunc[3])(struct _CWS_WIN_W *);       /* @0x002C1860 size 0xC */
static void (*NetWin_PerStatsCode[4])(struct _CWS_WIN_W *);      /* @0x002C1870 size 0x10 */
static unsigned char *perstats_title[5];                         /* @0x002C1880 size 0x14 */
static struct _CWS_OBJ_TEX per_stats_match[4];                   /* @0x002C18A0 size 0x50 */
static struct _CWS_OBJ_TEX per_stats_title[5];                   /* @0x002C18F0 size 0x64 */
static struct _CWS_OBJ_TEX per_stats_borad[20];                  /* @0x002C1960 size 0x190 */
static struct _CWS_OBJ_SET netwinperhed[3];                      /* @0x002C1AF0 size 0x3C */

/* functions defined (4) */
static int NetWin_PerStatsEnd(struct _CWS_WIN_W *win);           /* 0x00286750-0x00286764 lines 418-420 */
static int NetWin_PerStatsMain(struct _CWS_WIN_W *win);          /* 0x00286770-0x00286E98 lines 333-413 */
static int NetWin_PerStatsInit(struct _CWS_WIN_W *win);          /* 0x00286EA0-0x00286F1C lines 290-330 */
int NetWin_PerStats(struct _CWS_WIN_W *win);                     /* 0x00286F20-0x00286F88 lines 279-285 */

#endif /* DDR_UNIT_src_network_net_window_net_win_perstats_c_H */
