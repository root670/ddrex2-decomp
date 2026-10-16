/*
 * C:\work2\usaex2\src\common\cws\cws_win_multi.c
 * MW MIPS C Compiler, overlay main; 10 functions, code 0x002088C0-0x00209E18
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_common_cws_cws_win_multi_c_H
#define DDR_UNIT_src_common_cws_cws_win_multi_c_H

#include "types/_CWS_OBJ.h"
#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"
#include "types/_CWS_WIN_MULTI_W.h"
#include "types/_CWS_WIN_W.h"

/* anonymous types (6) */

/* anon_0_65 -- @anon0, 0x8 bytes, cws_win_multi.c (DIE 0xF7C92) */
struct anon_0_65 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_4_65 -- @anon4, 0x4 bytes, cws_win_multi.c (DIE 0xF8C81) */
union anon_4_65 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_65 -- @anon1, 0x24 bytes, cws_win_multi.c (DIE 0xF7D4D) */
struct anon_1_65 {   // size 0x24
    /* 0x000 */ union anon_4_65 x0;                   // 0x4
    /* 0x004 */ union anon_4_65 y0;                   // 0x4
    /* 0x008 */ union anon_4_65 x1;                   // 0x4
    /* 0x00C */ union anon_4_65 y1;                   // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ unsigned char r1;                     // 0x1
    /* 0x01D */ unsigned char g1;                     // 0x1
    /* 0x01E */ unsigned char b1;                     // 0x1
    /* 0x01F */ unsigned char a1;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};

/* anon_2_65 -- @anon2, 0x48 bytes, cws_win_multi.c (DIE 0xF8641) */
struct anon_2_65 {   // size 0x48
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

/* anon_3_65 -- @anon3, 0x1C bytes, cws_win_multi.c (DIE 0xF8A8F) */
struct anon_3_65 {   // size 0x1C
    /* 0x000 */ union anon_4_65 x0;                   // 0x4
    /* 0x004 */ union anon_4_65 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_5_65 -- @anon5, 0x30 bytes, cws_win_multi.c (DIE 0xF8F6B) */
struct anon_5_65 {   // size 0x30
    /* 0x000 */ union anon_4_65 x0;                   // 0x4
    /* 0x004 */ union anon_4_65 y0;                   // 0x4
    /* 0x008 */ union anon_4_65 x1;                   // 0x4
    /* 0x00C */ union anon_4_65 y1;                   // 0x4
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


/* variables (6) */
static int (*CwsWin_MultiFunc[3])(struct _CWS_WIN_W *);          /* @0x002BB448 size 0xC */
static void (*CwsWin_MultiCode[4])(struct _CWS_WIN_W *);         /* @0x002BB460 size 0x10 */
static struct _CWS_OBJ_TEX cwswinmulti_plate_line[1];            /* @0x002BB470 size 0x14 */
static struct _CWS_OBJ_TEX cwswinmulti_plate_back[9];            /* @0x002BB490 size 0xB4 */
static struct _CWS_OBJ_TEX cwswinmulti_plate_caution_mark[2];    /* @0x002BB550 size 0x28 */
static struct _CWS_OBJ_SET cwswinmulti[4];                       /* @0x002BB580 size 0x50 */

/* functions defined (10) */
void CwsWin_MultiSetCautionMark(struct _CWS_WIN_W *win, int mark); /* 0x002088C0-0x002088F8 lines 680-687 */
void CwsWin_MultiSetWinClut(struct _CWS_WIN_W *win, int clut);   /* 0x00208900-0x00208918 lines 671-675 */
static void CwsWin_LineDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x00208920-0x00208C40 lines 589-656 */
static void CwsWin_MultiDisp(struct _CWS_WIN_W *win, struct _CWS_OBJ *objw); /* 0x00208C40-0x00209428 lines 442-586 */
static int CwsWin_MultiEnd(struct _CWS_WIN_W *win);              /* 0x00209430-0x00209444 lines 435-437 */
static int CwsWin_MultiMain(struct _CWS_WIN_W *win);             /* 0x00209450-0x00209658 lines 395-430 */
static int CwsWin_MultiInit(struct _CWS_WIN_W *win);             /* 0x00209660-0x0020971C lines 379-392 */
static void CwsWin_MultiClose(struct _CWS_WIN_W *win);           /* 0x00209720-0x002099E4 lines 278-374 */
static void CwsWin_MultiOpen(struct _CWS_WIN_W *win);            /* 0x002099F0-0x00209DB0 lines 149-275 */
int CwsWin_Multi(struct _CWS_WIN_W *win);                        /* 0x00209DB0-0x00209E18 lines 138-145 */

#endif /* DDR_UNIT_src_common_cws_cws_win_multi_c_H */
