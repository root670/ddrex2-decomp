/*
 * C:\work2\usaex2\src\network\net_window\net_win_listdtl3.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x0025BF30-0x0025C6C8
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
#ifndef DDR_UNIT_src_network_net_window_net_win_listdtl3_c_H
#define DDR_UNIT_src_network_net_window_net_win_listdtl3_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_listdtl3_w.h"
#include "types/_nsv_player_list_file.h"

/* variables (6) */
static int (*NetWin_Listdtl3Func[3])(struct _CWS_WIN_W *);       /* @0x002BFC30 size 0xC */
static void (*NetWin_Listdtl3Code[4])(struct _CWS_WIN_W *);      /* @0x002BFC40 size 0x10 */
static struct _CWS_OBJ_TEX netwinlistdtl3_plate_board[6];        /* @0x002BFC50 size 0x78 */
static struct _CWS_OBJ_TEX netwinlistdtl3_plate_waku[4];         /* @0x002BFCD0 size 0x50 */
static struct _CWS_OBJ_TEX netwinlistdtl3_plate_font[8];         /* @0x002BFD20 size 0xA0 */
static struct _CWS_OBJ_SET netwinlistdtl3[3];                    /* @0x002BFDC0 size 0x3C */

/* functions defined (5) */
void NetWin_Listdtl3SetPlayerListFile(struct _CWS_WIN_W *win, struct _nsv_player_list_file *addr); /* 0x0025BF30-0x0025BF38 lines 417-417 */
static int NetWin_Listdtl3End(struct _CWS_WIN_W *win);           /* 0x0025BF40-0x0025BF54 lines 406-408 */
static int NetWin_Listdtl3Main(struct _CWS_WIN_W *win);          /* 0x0025BF60-0x0025C1D8 lines 354-401 */
static int NetWin_Listdtl3Init(struct _CWS_WIN_W *win);          /* 0x0025C1E0-0x0025C654 lines 259-351 */
int NetWin_Listdtl3(struct _CWS_WIN_W *win);                     /* 0x0025C660-0x0025C6C8 lines 248-254 */

#endif /* DDR_UNIT_src_network_net_window_net_win_listdtl3_c_H */
