/*
 * C:\work2\usaex2\src\network\net_window\net_win_listsel.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x00257D70-0x002581D8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_listsel_c_H
#define DDR_UNIT_src_network_net_window_net_win_listsel_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_listsel_w.h"
#include "types/_nsv_player_list_file.h"

/* variables (8) */
static int (*NetWin_ListselFunc[3])(struct _CWS_WIN_W *);        /* @0x002BF6E8 size 0xC */
static void (*NetWin_ListselCode[4])(struct _CWS_WIN_W *);       /* @0x002BF700 size 0x10 */
static struct _CWS_OBJ_TEX netwinslby_plate_board[1];            /* @0x002BF710 size 0x14 */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_back[1];       /* @0x002BF730 size 0x14 */
static struct _CWS_OBJ_TEX netwinslby_plate_chara_face[1];       /* @0x002BF750 size 0x14 */
static struct _CWS_OBJ_TEX netwinslby_plate_status[3];           /* @0x002BF770 size 0x3C */
static struct _CWS_OBJ_TEX netwinslby_plate_line[4];             /* @0x002BF7B0 size 0x50 */
static struct _CWS_OBJ_SET netwinlistsel[5];                     /* @0x002BF800 size 0x64 */

/* functions defined (7) */
void NetWin_ListselSetSelect(struct _CWS_WIN_W *win, char onoff); /* 0x00257D70-0x00257DB8 lines 262-267 */
void NetWin_ListselSetPlayerListFile(struct _CWS_WIN_W *win, struct _nsv_player_list_file *addr); /* 0x00257DC0-0x00257DC8 lines 258-258 */
void NetWin_ListselSetNumber(struct _CWS_WIN_W *win, int _num);  /* 0x00257DD0-0x00257DE4 lines 252-252 */
static int NetWin_ListselEnd(struct _CWS_WIN_W *win);            /* 0x00257DF0-0x00257E04 lines 243-245 */
static int NetWin_ListselMain(struct _CWS_WIN_W *win);           /* 0x00257E10-0x00258048 lines 193-238 */
static int NetWin_ListselInit(struct _CWS_WIN_W *win);           /* 0x00258050-0x0025816C lines 171-190 */
int NetWin_Listsel(struct _CWS_WIN_W *win);                      /* 0x00258170-0x002581D8 lines 160-166 */

#endif /* DDR_UNIT_src_network_net_window_net_win_listsel_c_H */
