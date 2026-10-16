/*
 * C:\work\usam2\src\CS\endless\eds_box.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x0023a130-0x0023b77c
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_endless_eds_box_c_H
#define DDR_UNIT_src_CS_endless_eds_box_c_H

#include "types/_EDSBOX_MAIN.h"
#include "types/_EDSBOX_W.h"

/* anonymous types (2) */

/* anon_1_28 -- @anon1, 0x4 bytes, eds_box.c (DIE 0x62ee2) */
union anon_1_28 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_28 -- @anon0, 0x34 bytes, eds_box.c (DIE 0x62a07) */
struct anon_0_28 {   // size 0x34
    /* 0x000 */ union anon_1_28 x0;                   // 0x4
    /* 0x004 */ union anon_1_28 y0;                   // 0x4
    /* 0x008 */ union anon_1_28 x1;                   // 0x4
    /* 0x00c */ union anon_1_28 y1;                   // 0x4
    /* 0x010 */ union anon_1_28 x2;                   // 0x4
    /* 0x014 */ union anon_1_28 y2;                   // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01c */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02a */ unsigned char b1;                     // 0x1
    /* 0x02b */ unsigned char a1;                     // 0x1
    /* 0x02c */ unsigned char r2;                     // 0x1
    /* 0x02d */ unsigned char g2;                     // 0x1
    /* 0x02e */ unsigned char b2;                     // 0x1
    /* 0x02f */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
};


/* variables (4) */
static int (*EdsBox_Func[5])(struct _EDSBOX_W *);                /* @0x00285e40 size 0x14 */
static unsigned char EdsBoxRgbTbl[2][3];                         /* @0x002a2278 size 0x6 */
struct _EDSBOX_MAIN *EDSBOXM;                                    /* @0x002a2280 size 0x4 */
static struct _EDSBOX_MAIN _eds_box_w;                           /* @0x006b3880 size 0x8e8 */

/* functions defined (19) */
void EdsBox4SetRGBA(int num, int pos, unsigned char r, unsigned char g, unsigned char b, unsigned char a); /* 0x0023a130-0x0023a290 lines 643-656 */
void EdsBox4SetUV(int num, int pos, float u, float v);           /* 0x0023a290-0x0023a2dc lines 629-633 */
void EdsBoxSetWH(int num, float w, float h);                     /* 0x0023a2e0-0x0023a388 lines 603-613 */
void EdsBoxSetY(int num, float y);                               /* 0x0023a390-0x0023a3c0 lines 594-597 */
void EdsBoxSetXY(int num, float x, float y);                     /* 0x0023a3c0-0x0023a408 lines 572-589 */
void EdsBoxSetRGBAnime(int num, int type, int col);              /* 0x0023a410-0x0023a4c8 lines 553-565 */
void EdsBoxSetType(int num, char type);                          /* 0x0023a4d0-0x0023a530 lines 539-544 */
void EdsBoxSetMode(int num, int mode);                           /* 0x0023a530-0x0023a640 lines 513-531 */
static void EdsBoxRGBAnime(struct _EDSBOX_W *boxw);              /* 0x0023a640-0x0023ade0 lines 355-500 */
static int EdsBoxOpenCloseMove(struct _EDSBOX_W *boxw, int speed); /* 0x0023ade0-0x0023aef0 lines 309-348 */
static void EdsBoxDisp(struct _EDSBOX_W *boxw);                  /* 0x0023aef0-0x0023b3f8 lines 260-297 */
static int EdsBoxDestroy(void);                                  /* 0x0023b400-0x0023b408 lines 253-253 */
static int EdsBoxClose(struct _EDSBOX_W *boxw);                  /* 0x0023b410-0x0023b4c8 lines 196-230 */
static int EdsBoxMain(struct _EDSBOX_W *boxw);                   /* 0x0023b4d0-0x0023b4f0 lines 182-189 */
static int EdsBoxOpen(struct _EDSBOX_W *boxw);                   /* 0x0023b4f0-0x0023b5c0 lines 141-174 */
static int EdsBoxSet(void);                                      /* 0x0023b5c0-0x0023b5c8 lines 133-133 */
void EdsBoxGetInit(int num);                                     /* 0x0023b5d0-0x0023b658 lines 96-122 */
void EdsBoxFunc(void);                                           /* 0x0023b660-0x0023b76c lines 65-89 */
void EdsBoxAllInit(void);                                        /* 0x0023b770-0x0023b77c lines 56-56 */

#endif /* DDR_UNIT_src_CS_endless_eds_box_c_H */
