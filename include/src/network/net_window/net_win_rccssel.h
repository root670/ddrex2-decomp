/*
 * C:\work2\usaex2\src\network\net_window\net_win_rccssel.c
 * MW MIPS C Compiler, overlay main; 10 functions, code 0x00272330-0x00273518
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_window_net_win_rccssel_c_H
#define DDR_UNIT_src_network_net_window_net_win_rccssel_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_W.h"
#include "types/_net_win_rccssel_w.h"
#include "types/_nsv_rc_table_param_work.h"

/* anonymous types (2) */

/* anon_3_152 -- @anon3, 0x4 bytes, net_win_rccssel.c (DIE 0x2A3A91) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_152;

/* anon_1_152 -- @anon1, 0x34 bytes, net_win_rccssel.c (DIE 0x2A31E4) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_3_152 x0;                        // 0x4
    /* 0x004 */ anon_3_152 y0;                        // 0x4
    /* 0x008 */ anon_3_152 x1;                        // 0x4
    /* 0x00C */ anon_3_152 y1;                        // 0x4
    /* 0x010 */ anon_3_152 x2;                        // 0x4
    /* 0x014 */ anon_3_152 y2;                        // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
} anon_1_152;


/* variables (7) */
static int (*NetWin_RccsselFunc[3])(struct _CWS_WIN_W *);        /* @0x002C0840 size 0xC */
static void (*NetWin_RccsselCode[4])(struct _CWS_WIN_W *);       /* @0x002C0850 size 0x10 */
static struct _CWS_OBJ_TEX netwinrccssel_plate_back[5];          /* @0x002C0860 size 0x64 */
static struct _CWS_OBJ_TEX netwinrccssel_plate_num1_5[5];        /* @0x002C08D0 size 0x64 */
static struct _CWS_OBJ_TEX netwinrccssel_plate_num6_10[5];       /* @0x002C0940 size 0x64 */
static struct _CWS_OBJ_TEX netwinrccssel_plate_nm[1];            /* @0x002C09B0 size 0x14 */
static struct _CWS_OBJ_SET netwinrccssel[7];                     /* @0x002C09D0 size 0x8C */

/* functions defined (10) */
void NetWin_RccsselReflash(struct _CWS_WIN_W *win);              /* 0x00272330-0x002723B4 lines 574-584 */
void NetWin_RccsselSetPage(struct _CWS_WIN_W *win, int page);    /* 0x002723C0-0x002724D4 lines 547-570 */
void NetWin_RccsselSetLinePosY(struct _CWS_WIN_W *win, int pos_y); /* 0x002724E0-0x002724E8 lines 545-545 */
void NetWin_RccsselSetRcData(struct _CWS_WIN_W *win, struct _nsv_rc_table_param_work *addr); /* 0x002724F0-0x002724F8 lines 540-540 */
static void NetWin_RccsselLineDisp(struct _CWS_WIN_W *win);      /* 0x00272500-0x00272A90 lines 391-532 */
static void NetWin_RccsselBoardDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x00272A90-0x002730B0 lines 302-387 */
static int NetWin_RccsselEnd(struct _CWS_WIN_W *win);            /* 0x002730B0-0x002730C4 lines 293-295 */
static int NetWin_RccsselMain(struct _CWS_WIN_W *win);           /* 0x002730D0-0x002733F0 lines 228-288 */
static int NetWin_RccsselInit(struct _CWS_WIN_W *win);           /* 0x002733F0-0x002734AC lines 211-225 */
int NetWin_Rccssel(struct _CWS_WIN_W *win);                      /* 0x002734B0-0x00273518 lines 200-206 */

#endif /* DDR_UNIT_src_network_net_window_net_win_rccssel_c_H */
