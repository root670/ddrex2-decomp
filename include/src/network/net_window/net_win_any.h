/*
 * C:\work2\usaex2\src\network\net_window\net_win_any.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x0020A250-0x0020A458
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_any_c_H
#define DDR_UNIT_src_network_net_window_net_win_any_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_WIN_W.h"

/* variables (3) */
static int (*NetWin_AnyFunc[3])(struct _CWS_WIN_W *);            /* @0x002BB838 size 0xC */
static void (*NetWin_AnyCode[4])(struct _CWS_WIN_W *);           /* @0x002BB850 size 0x10 */
static struct _CWS_OBJ_SET netwinany[2];                         /* @0x002BB860 size 0x28 */

/* functions defined (5) */
void NetWin_AnySetTexture(struct _CWS_WIN_W *win, int _tex_id, int _tu, int _tv, int _tw, int _th); /* 0x0020A250-0x0020A2C8 lines 109-115 */
static int NetWin_AnyEnd(struct _CWS_WIN_W *win);                /* 0x0020A2D0-0x0020A2E4 lines 102-104 */
static int NetWin_AnyMain(struct _CWS_WIN_W *win);               /* 0x0020A2F0-0x0020A360 lines 84-97 */
static int NetWin_AnyInit(struct _CWS_WIN_W *win);               /* 0x0020A360-0x0020A3F0 lines 72-81 */
int NetWin_Any(struct _CWS_WIN_W *win);                          /* 0x0020A3F0-0x0020A458 lines 61-67 */

#endif /* DDR_UNIT_src_network_net_window_net_win_any_c_H */
