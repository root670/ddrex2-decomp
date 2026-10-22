/*
 * C:\work2\usaex2\src\network\net_window\net_win_infoboard.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x0025C6D0-0x0025C7A8
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
#ifndef DDR_UNIT_src_network_net_window_net_win_infoboard_c_H
#define DDR_UNIT_src_network_net_window_net_win_infoboard_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"

/* variables (4) */
static int (*NetWin_InfoboardFunc[3])(struct _CWS_WIN_W *);      /* @0x002BFE00 size 0xC */
static void (*NetWin_InfoboardCode[4])(struct _CWS_WIN_W *);     /* @0x002BFE10 size 0x10 */
static struct _CWS_OBJ_TEX netwininfoboard_plate_back[11];       /* @0x002BFE20 size 0xDC */
static struct _CWS_OBJ_SET netwininfoboard[1];                   /* @0x002BFF00 size 0x14 */

/* functions defined (4) */
static int NetWin_InfoboardEnd(struct _CWS_WIN_W *win);          /* 0x0025C6D0-0x0025C6E4 lines 135-137 */
static int NetWin_InfoboardMain(void);                           /* 0x0025C6F0-0x0025C6F8 lines 130-130 */
static int NetWin_InfoboardInit(struct _CWS_WIN_W *win);         /* 0x0025C700-0x0025C740 lines 116-124 */
int NetWin_Infoboard(struct _CWS_WIN_W *win);                    /* 0x0025C740-0x0025C7A8 lines 105-111 */

#endif /* DDR_UNIT_src_network_net_window_net_win_infoboard_c_H */
