/*
 * C:\work2\usaex2\src\network\net_window\net_win_menu.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x00223FA0-0x00224268
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_menu_c_H
#define DDR_UNIT_src_network_net_window_net_win_menu_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_menu_w.h"

/* variables (7) */
static int (*NetWin_MenuFunc[3])(struct _CWS_WIN_W *);           /* @0x002BC4B0 size 0xC */
static void (*NetWin_MenuCode[4])(struct _CWS_WIN_W *);          /* @0x002BC4C0 size 0x10 */
static struct _CWS_OBJ_TEX netwinmenu_plate_board_off[3];        /* @0x002BC4D0 size 0x3C */
static struct _CWS_OBJ_TEX netwinmenu_plate_board_on[3];         /* @0x002BC510 size 0x3C */
static struct _CWS_OBJ_TEX netwinmenu_plate_board_col[4];        /* @0x002BC550 size 0x50 */
static struct _CWS_OBJ_TEX netwinmenu_plate_font[6];             /* @0x002BC5A0 size 0x78 */
static struct _CWS_OBJ_SET netwinmenu[3];                        /* @0x002BC620 size 0x3C */

/* functions defined (6) */
void NetWin_MenuSetSelect(struct _CWS_WIN_W *win, int status);   /* 0x00223FA0-0x00223FF4 lines 259-271 */
void NetWin_MenuSetFont(struct _CWS_WIN_W *win, int font_num);   /* 0x00224000-0x00224150 lines 213-255 */
static int NetWin_MenuEnd(struct _CWS_WIN_W *win);               /* 0x00224150-0x00224164 lines 205-207 */
static int NetWin_MenuMain(void);                                /* 0x00224170-0x00224178 lines 200-200 */
static int NetWin_MenuInit(struct _CWS_WIN_W *win);              /* 0x00224180-0x002241FC lines 186-194 */
int NetWin_Menu(struct _CWS_WIN_W *win);                         /* 0x00224200-0x00224268 lines 175-181 */

#endif /* DDR_UNIT_src_network_net_window_net_win_menu_c_H */
