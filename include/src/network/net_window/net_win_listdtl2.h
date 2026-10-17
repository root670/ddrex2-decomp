/*
 * C:\work2\usaex2\src\network\net_window\net_win_listdtl2.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x0025B2D0-0x0025B678
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_listdtl2_c_H
#define DDR_UNIT_src_network_net_window_net_win_listdtl2_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_listdtl2_w.h"
#include "types/_nsv_player_list_file.h"

/* variables (6) */
static int (*NetWin_Listdtl2Func[3])(struct _CWS_WIN_W *);       /* @0x002BF908 size 0xC */
static void (*NetWin_Listdtl2Code[4])(struct _CWS_WIN_W *);      /* @0x002BF920 size 0x10 */
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_board[2];  /* @0x002BF930 size 0x28 */
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_waku[4];   /* @0x002BF960 size 0x50 */
static struct _CWS_OBJ_TEX netwinlistdtl2_plate_point_font[5];   /* @0x002BF9B0 size 0x64 */
static struct _CWS_OBJ_SET netwinlistdtl2[3];                    /* @0x002BFA20 size 0x3C */

/* functions defined (5) */
void NetWin_Listdtl2SetPlayerListFile(struct _CWS_WIN_W *win, struct _nsv_player_list_file *addr); /* 0x0025B2D0-0x0025B2D8 lines 273-273 */
static int NetWin_Listdtl2End(struct _CWS_WIN_W *win);           /* 0x0025B2E0-0x0025B2F4 lines 262-264 */
static int NetWin_Listdtl2Main(struct _CWS_WIN_W *win);          /* 0x0025B300-0x0025B428 lines 229-257 */
static int NetWin_Listdtl2Init(struct _CWS_WIN_W *win);          /* 0x0025B430-0x0025B608 lines 190-226 */
int NetWin_Listdtl2(struct _CWS_WIN_W *win);                     /* 0x0025B610-0x0025B678 lines 179-185 */

#endif /* DDR_UNIT_src_network_net_window_net_win_listdtl2_c_H */
