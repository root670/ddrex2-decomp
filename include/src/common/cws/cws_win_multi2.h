/*
 * C:\work2\usaex2\src\common\cws\cws_win_multi2.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00240070-0x00241018
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_common_cws_cws_win_multi2_c_H
#define DDR_UNIT_src_common_cws_cws_win_multi2_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_MULTI2_W.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (4) */

/* anon_0_111 -- @anon0, 0x8 bytes, cws_win_multi2.c (DIE 0x1F5D71) */
struct anon_0_111 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_111 -- @anon1, 0x48 bytes, cws_win_multi2.c (DIE 0x1F651F) */
struct anon_1_111 {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02C */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03A */ unsigned short tw;                    // 0x2
    /* 0x03C */ unsigned short th;                    // 0x2
    /* 0x03E */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
};

/* anon_2_111 -- @anon2, 0x4 bytes, cws_win_multi2.c (DIE 0x1F6A07) */
union anon_2_111 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_111 -- @anon3, 0x30 bytes, cws_win_multi2.c (DIE 0x1F6CCB) */
struct anon_3_111 {   // size 0x30
    /* 0x000 */ union anon_2_111 x0;                  // 0x4
    /* 0x004 */ union anon_2_111 y0;                  // 0x4
    /* 0x008 */ union anon_2_111 x1;                  // 0x4
    /* 0x00C */ union anon_2_111 y1;                  // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
};


/* variables (5) */
static int (*CwsWin_Multi2Func[3])(struct _CWS_WIN_W *);         /* @0x002BEF28 size 0xC */
static void (*CwsWin_Multi2Code[4])(struct _CWS_WIN_W *);        /* @0x002BEF40 size 0x10 */
static struct _CWS_OBJ_TEX cwswinmulti2_plate_back[9];           /* @0x002BEF50 size 0xB4 */
static struct _CWS_OBJ_TEX cwswinmulti2_plate_caution_mark[2];   /* @0x002BF010 size 0x28 */
static struct _CWS_OBJ_SET cwswinmulti2[3];                      /* @0x002BF040 size 0x3C */

/* functions defined (9) */
void CwsWin_Multi2SetCautionMark(struct _CWS_WIN_W *win, int mark); /* 0x00240070-0x002400A8 lines 510-517 */
void CwsWin_Multi2SetWinClut(struct _CWS_WIN_W *win, int clut);  /* 0x002400B0-0x002400C8 lines 500-504 */
static void CwsWin_Multi2Disp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x002400D0-0x00240710 lines 375-485 */
static int CwsWin_Multi2End(struct _CWS_WIN_W *win);             /* 0x00240710-0x00240724 lines 368-370 */
static int CwsWin_Multi2Main(struct _CWS_WIN_W *win);            /* 0x00240730-0x00240908 lines 332-363 */
static int CwsWin_Multi2Init(struct _CWS_WIN_W *win);            /* 0x00240910-0x002409CC lines 313-326 */
static void CwsWin_Multi2Close(struct _CWS_WIN_W *win);          /* 0x002409D0-0x00240CC4 lines 218-308 */
static void CwsWin_Multi2Open(struct _CWS_WIN_W *win);           /* 0x00240CD0-0x00240FAC lines 131-215 */
int CwsWin_Multi2(struct _CWS_WIN_W *win);                       /* 0x00240FB0-0x00241018 lines 121-127 */

#endif /* DDR_UNIT_src_common_cws_cws_win_multi2_c_H */
