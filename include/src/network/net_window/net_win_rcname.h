/*
 * C:\work2\usaex2\src\network\net_window\net_win_rcname.c
 * MW MIPS C Compiler, overlay main; 10 functions, code 0x00231630-0x00231A88
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_rcname_c_H
#define DDR_UNIT_src_network_net_window_net_win_rcname_c_H

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_rcname_w.h"

/* variables (9) */
static int (*NetWin_RcnameFunc[3])(struct _CWS_WIN_W *);         /* @0x002BE830 size 0xC */
static void (*NetWin_RcnameCode[4])(struct _CWS_WIN_W *);        /* @0x002BE840 size 0x10 */
static struct _CWS_OBJ_TEX netwinrcname_plate_cov_off[9];        /* @0x002BE850 size 0xB4 */
static struct _CWS_OBJ_TEX netwinrcname_plate_cov_on[9];         /* not allocated size 0xB4 */
static struct _CWS_OBJ_TEX netwinrcname_plate_board[1];          /* @0x002BE910 size 0x14 */
static struct _CWS_OBJ_TEX netwinrcname_plate_tagup[2];          /* @0x002BE930 size 0x28 */
static struct _CWS_OBJ_TEX netwinrcname_plate_tagdw[2];          /* @0x002BE960 size 0x28 */
static struct _CWS_OBJ_TEX netwinrcname_plate_add_option[1];     /* @0x002BE990 size 0x14 */
static struct _CWS_OBJ_SET netwinrcname[6];                      /* @0x002BE9B0 size 0x78 */

/* functions defined (10) */
void NetWin_RcnameSetOption(struct _CWS_WIN_W *win, char on_off); /* 0x00231630-0x00231678 lines 356-362 */
void NetWin_RcnameSetMax(struct _CWS_WIN_W *win, int _num);      /* 0x00231680-0x00231694 lines 351-351 */
void NetWin_RcnameSetNow(struct _CWS_WIN_W *win, int _num);      /* 0x002316A0-0x002316B4 lines 347-347 */
void NetWin_RcnameSetName(struct _CWS_WIN_W *win, unsigned char *name, int _num); /* 0x002316C0-0x002316D4 lines 343-343 */
void NetWin_RcnameSetCursor(struct _CWS_WIN_W *win, int cur);    /* 0x002316E0-0x00231758 lines 323-338 */
void NetWin_RcnameSetType(struct _CWS_WIN_W *win, int type);     /* 0x00231760-0x002317C0 lines 310-318 */
static int NetWin_RcnameEnd(struct _CWS_WIN_W *win);             /* 0x002317C0-0x002317D4 lines 301-303 */
static int NetWin_RcnameMain(struct _CWS_WIN_W *win);            /* 0x002317E0-0x00231870 lines 286-296 */
static int NetWin_RcnameInit(struct _CWS_WIN_W *win);            /* 0x00231870-0x00231A18 lines 250-283 */
int NetWin_Rcname(struct _CWS_WIN_W *win);                       /* 0x00231A20-0x00231A88 lines 239-245 */

#endif /* DDR_UNIT_src_network_net_window_net_win_rcname_c_H */
