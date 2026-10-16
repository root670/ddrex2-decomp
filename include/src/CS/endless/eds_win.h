/*
 * C:\work\usam2\src\CS\endless\eds_win.c
 * MW MIPS C Compiler, overlay main; 25 functions, code 0x00233de0-0x00236160
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_endless_eds_win_c_H
#define DDR_UNIT_src_CS_endless_eds_win_c_H

#include "types/_EDSSYS_W.h"
#include "types/_EDSTEX_INIT_SET.h"
#include "types/_EDSTEX_W.h"
#include "types/_EDSWIN_W.h"
#include "types/demo_loop_w.h"
#include "types/play_loop_w.h"

/* anonymous types (7) */

/* anon_0_23 -- @anon0, 0x8008 bytes, eds_win.c (DIE 0x4e2fd) */
union anon_0_23 {   // size 0x8008
    /* 0x000 */ struct demo_loop_w demo_loop_w;       // 0x8008
    /* 0x000 */ struct play_loop_w play_loop_w;       // 0x8008
};

/* anon_5_23 -- @anon5, 0x4 bytes, eds_win.c (DIE 0x4fb0d) */
union anon_5_23 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_23 -- @anon1, 0x74 bytes, eds_win.c (DIE 0x4e601) */
struct anon_1_23 {   // size 0x74
    /* 0x000 */ union anon_5_23 x0;                   // 0x4
    /* 0x004 */ union anon_5_23 y0;                   // 0x4
    /* 0x008 */ union anon_5_23 x1;                   // 0x4
    /* 0x00c */ union anon_5_23 y1;                   // 0x4
    /* 0x010 */ union anon_5_23 x2;                   // 0x4
    /* 0x014 */ union anon_5_23 y2;                   // 0x4
    /* 0x018 */ union anon_5_23 x3;                   // 0x4
    /* 0x01c */ union anon_5_23 y3;                   // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02c */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03c */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04c */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05c */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ unsigned char r1;                     // 0x1
    /* 0x065 */ unsigned char g1;                     // 0x1
    /* 0x066 */ unsigned char b1;                     // 0x1
    /* 0x067 */ unsigned char a1;                     // 0x1
    /* 0x068 */ unsigned char r2;                     // 0x1
    /* 0x069 */ unsigned char g2;                     // 0x1
    /* 0x06a */ unsigned char b2;                     // 0x1
    /* 0x06b */ unsigned char a2;                     // 0x1
    /* 0x06c */ unsigned char r3;                     // 0x1
    /* 0x06d */ unsigned char g3;                     // 0x1
    /* 0x06e */ unsigned char b3;                     // 0x1
    /* 0x06f */ unsigned char a3;                     // 0x1
    /* 0x070 */ int flg;                              // 0x4
};

/* anon_2_23 -- @anon2, 0x48 bytes, eds_win.c (DIE 0x4eb28) */
struct anon_2_23 {   // size 0x48
    /* 0x000 */ unsigned long *addr;                  // 0x4
    /* 0x004 */ unsigned long *pict_addr;             // 0x4
    /* 0x008 */ unsigned long *clut_addr;             // 0x4
    /* 0x00c */ // 0x4 bytes padding
    /* 0x010 */ unsigned long regTex0;                // 0x8
    /* 0x018 */ unsigned long size;                   // 0x8
    /* 0x020 */ unsigned long flg;                    // 0x8
    /* 0x028 */ float rw;                             // 0x4
    /* 0x02c */ float rh;                             // 0x4
    /* 0x030 */ unsigned short pict_size;             // 0x2
    /* 0x032 */ unsigned short clut_size;             // 0x2
    /* 0x034 */ unsigned short w;                     // 0x2
    /* 0x036 */ unsigned short h;                     // 0x2
    /* 0x038 */ unsigned short tbw;                   // 0x2
    /* 0x03a */ unsigned short tw;                    // 0x2
    /* 0x03c */ unsigned short th;                    // 0x2
    /* 0x03e */ unsigned short psm;                   // 0x2
    /* 0x040 */ unsigned short cpsm;                  // 0x2
    /* 0x042 */ unsigned short colors;                // 0x2
    /* 0x044 */ // 0x4 bytes padding
};

/* anon_3_23 -- @anon3, 0x1c bytes, eds_win.c (DIE 0x4f661) */
struct anon_3_23 {   // size 0x1c
    /* 0x000 */ union anon_5_23 x0;                   // 0x4
    /* 0x004 */ union anon_5_23 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00c */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_4_23 -- @anon4, 0x24 bytes, eds_win.c (DIE 0x4f86f) */
struct anon_4_23 {   // size 0x24
    /* 0x000 */ union anon_5_23 x0;                   // 0x4
    /* 0x004 */ union anon_5_23 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00c */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01c */ unsigned char r0;                     // 0x1
    /* 0x01d */ unsigned char g0;                     // 0x1
    /* 0x01e */ unsigned char b0;                     // 0x1
    /* 0x01f */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};

/* anon_6_23 -- @anon6, 0x30 bytes, eds_win.c (DIE 0x4fb6a) */
struct anon_6_23 {   // size 0x30
    /* 0x000 */ union anon_5_23 x0;                   // 0x4
    /* 0x004 */ union anon_5_23 y0;                   // 0x4
    /* 0x008 */ union anon_5_23 x1;                   // 0x4
    /* 0x00c */ union anon_5_23 y1;                   // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01c */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02a */ unsigned char b0;                     // 0x1
    /* 0x02b */ unsigned char a0;                     // 0x1
    /* 0x02c */ int flg;                              // 0x4
};


/* variables (4) */
static int (*EdsWin_Func[5])(struct _EDSWIN_W *);                /* @0x00285200 size 0x14 */
static struct _EDSTEX_W EdsMainTextureData[54];                  /* @0x00285220 size 0x6c0 */
static struct _EDSTEX_INIT_SET EdsMainWindowData[28];            /* @0x002858e0 size 0x460 */
struct _EDSSYS_W *EDSSYSW;                                       /* @0x002a2254 size 0x4 */

/* functions defined (25) */
void EdsWinSelectAllFrameDisp(unsigned char _alpha);             /* 0x00233de0-0x00233e6c lines 1572-1582 */
static void EdsWinSelectFrame(int _x, int _y, unsigned char _alpha, int _size); /* 0x00233e70-0x00234148 lines 1496-1564 */
void EdsWinSelectBox(int _x, int _y, char _flag);                /* 0x00234150-0x00234214 lines 1471-1490 */
static void EdsOrderCheckList(int _y, char _no, unsigned char _alpha); /* 0x00234220-0x0023434c lines 1443-1463 */
static void EdsCheck(int _x, int _y, int _type, unsigned char _alpha); /* 0x00234350-0x00234528 lines 1397-1435 */
void EdsWinAllDestroy(void);                                     /* 0x00234530-0x002346d8 lines 1358-1376 */
void EdsWinSetTex(struct _EDSWIN_W *winw, unsigned char _tex, int _flag); /* 0x002346e0-0x00234764 lines 1337-1345 */
void EdsWinSetMoveXY(struct _EDSWIN_W *winw, float x, float y);  /* 0x00234770-0x002347f0 lines 1309-1316 */
void EdsWinSetXY(struct _EDSWIN_W *winw, float x, float y);      /* 0x002347f0-0x00234848 lines 1285-1289 */
void EdsWinSetType(struct _EDSWIN_W *winw, char type);           /* 0x00234850-0x002348b4 lines 1270-1277 */
void EdsWinSetMode(struct _EDSWIN_W *winw, int mode);            /* 0x002348c0-0x002349dc lines 1233-1262 */
static void EdsWinSetDefaultPartsWH(struct _EDSWIN_W *winw);     /* 0x002349e0-0x00234ac0 lines 1183-1225 */
static void EdsWinDefaultAllSet(struct _EDSWIN_W *winw);         /* 0x00234ac0-0x00234b98 lines 1150-1170 */
static int EdsWinAlphaAnime(struct _EDSWIN_W *winw);             /* 0x00234ba0-0x00234e38 lines 1089-1112 */
static int EdsWinWHMove(struct _EDSWIN_W *winw);                 /* 0x00234e40-0x00235008 lines 1042-1082 */
static int EdsWinXYMove(struct _EDSWIN_W *winw, int speed);      /* 0x00235010-0x00235220 lines 991-1035 */
static int EdsWinXYWHMove(struct _EDSWIN_W *winw, int speed);    /* 0x00235220-0x002354c0 lines 934-983 */
static void EdsWinDisp(struct _EDSWIN_W *winw);                  /* 0x002354c0-0x00235a18 lines 761-891 */
static int EdsWinDestroy(struct _EDSWIN_W *winw);                /* 0x00235a20-0x00235a80 lines 738-753 */
static int EdsWinClose(struct _EDSWIN_W *winw);                  /* 0x00235a80-0x00235c60 lines 670-730 */
static int EdsWinMain(struct _EDSWIN_W *winw);                   /* 0x00235c60-0x00235d28 lines 656-662 */
static int EdsWinOpen(struct _EDSWIN_W *winw);                   /* 0x00235d30-0x00235f98 lines 571-648 */
static int EdsWinSet(struct _EDSWIN_W *winw);                    /* 0x00235fa0-0x00235fac lines 560-563 */
struct _EDSWIN_W *EdsWinGetInit(int id);                         /* 0x00235fb0-0x00236094 lines 512-551 */
void EdsWinFunc(struct _EDSWIN_W *winw);                         /* 0x002360a0-0x00236160 lines 479-505 */

#endif /* DDR_UNIT_src_CS_endless_eds_win_c_H */
