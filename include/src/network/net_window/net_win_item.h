/*
 * C:\work2\usaex2\src\network\net_window\net_win_item.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x0022E740-0x0022EEB8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_item_c_H
#define DDR_UNIT_src_network_net_window_net_win_item_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_item_w.h"

/* variables (14) */
static int (*NetWin_ItemFunc[3])(struct _CWS_WIN_W *);           /* @0x002BDB30 size 0xC */
static void (*NetWin_ItemCode[4])(struct _CWS_WIN_W *);          /* @0x002BDB40 size 0x10 */
static struct _CWS_OBJ_TEX netwinitem_plate_mini_off[9];         /* @0x002BDB50 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_mini_on[9];          /* @0x002BDC10 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_big_off[9];          /* @0x002BDCD0 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_big_on[9];           /* @0x002BDD90 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_music_off[9];        /* @0x002BDE50 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_music_on[9];         /* @0x002BDF10 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_rc_off[9];           /* @0x002BDFD0 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_rc_on[9];            /* @0x002BE090 size 0xB4 */
static struct _CWS_OBJ_TEX netwinitem_plate_arrow[2];            /* @0x002BE150 size 0x28 */
static struct _CWS_OBJ_TEX netwinitem_plate_th[1];               /* @0x002BE180 size 0x14 */
static struct _CWS_OBJ_TEX netwinitem_plate_option[1];           /* @0x002BE1A0 size 0x14 */
static struct _CWS_OBJ_SET netwinitem[5];                        /* @0x002BE1C0 size 0x64 */

/* functions defined (6) */
void NetWin_ItemSetSelect(struct _CWS_WIN_W *win, int status);   /* 0x0022E740-0x0022EB30 lines 452-528 */
void NetWin_ItemSetType(struct _CWS_WIN_W *win, int type);       /* 0x0022EB30-0x0022ED60 lines 404-448 */
static int NetWin_ItemEnd(struct _CWS_WIN_W *win);               /* 0x0022ED60-0x0022ED74 lines 396-398 */
static int NetWin_ItemMain(void);                                /* 0x0022ED80-0x0022ED88 lines 391-391 */
static int NetWin_ItemInit(struct _CWS_WIN_W *win);              /* 0x0022ED90-0x0022EE50 lines 373-385 */
int NetWin_Item(struct _CWS_WIN_W *win);                         /* 0x0022EE50-0x0022EEB8 lines 362-368 */

#endif /* DDR_UNIT_src_network_net_window_net_win_item_c_H */
