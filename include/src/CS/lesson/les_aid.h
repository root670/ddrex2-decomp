/*
 * C:\work2\usaex2\src\CS\lesson\les_aid.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 13 functions, code 0x007F15F0-0x007F2880
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_les_aid_c_H
#define DDR_UNIT_src_CS_lesson_les_aid_c_H

#include "types/_LESTEX_INIT_SET.h"
#include "types/_LESTEX_W.h"
#include "types/_LESWIN_W.h"
#include "types/_tag_cLes.h"

/* anonymous types (3) */

/* anon_2_192 -- @anon2, 0x4 bytes, les_aid.c (DIE 0x3601CD) */
union anon_2_192 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_192 -- @anon0, 0x74 bytes, les_aid.c (DIE 0x35EE3D) */
struct anon_0_192 {   // size 0x74
    /* 0x000 */ union anon_2_192 x0;                  // 0x4
    /* 0x004 */ union anon_2_192 y0;                  // 0x4
    /* 0x008 */ union anon_2_192 x1;                  // 0x4
    /* 0x00C */ union anon_2_192 y1;                  // 0x4
    /* 0x010 */ union anon_2_192 x2;                  // 0x4
    /* 0x014 */ union anon_2_192 y2;                  // 0x4
    /* 0x018 */ union anon_2_192 x3;                  // 0x4
    /* 0x01C */ union anon_2_192 y3;                  // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
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
    /* 0x06A */ unsigned char b2;                     // 0x1
    /* 0x06B */ unsigned char a2;                     // 0x1
    /* 0x06C */ unsigned char r3;                     // 0x1
    /* 0x06D */ unsigned char g3;                     // 0x1
    /* 0x06E */ unsigned char b3;                     // 0x1
    /* 0x06F */ unsigned char a3;                     // 0x1
    /* 0x070 */ int flg;                              // 0x4
};

/* anon_1_192 -- @anon1, 0x48 bytes, les_aid.c (DIE 0x35F90D) */
struct anon_1_192 {   // size 0x48
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


/* variables (4) */
static int (*LesWin_Func[5])(struct _LESWIN_W *);                /* @0x007FA130 size 0x14 */
static struct _LESTEX_W LesMainTextureData[4];                   /* @0x007FB800 size 0x80 */
static struct _LESTEX_INIT_SET LesMainWindowData[1];             /* @0x007FA150 size 0x24 */
struct _tag_cLes *pLes;                                          /* @0x002DDE80 size 0x4 */

/* functions defined (13) */
void LesWinSetType(struct _LESWIN_W *winw, char type);           /* 0x007F15F0-0x007F1654 lines 658-665 */
void LesWinSetMode(struct _LESWIN_W *winw, int mode);            /* 0x007F1660-0x007F177C lines 621-650 */
static void LesWinSetDefaultPartsWH(struct _LESWIN_W *winw);     /* 0x007F1780-0x007F1860 lines 571-613 */
static void LesWinDefaultAllSet(struct _LESWIN_W *winw);         /* 0x007F1860-0x007F1918 lines 535-558 */
static int LesWinXYWHMove(struct _LESWIN_W *winw);               /* 0x007F1920-0x007F1B28 lines 451-521 */
static void LesWinDisp(struct _LESWIN_W *winw);                  /* 0x007F1B30-0x007F2210 lines 314-409 */
static int LesWinDestroy(struct _LESWIN_W *winw);                /* 0x007F2210-0x007F226C lines 291-306 */
static int LesWinClose(struct _LESWIN_W *winw);                  /* 0x007F2270-0x007F24B0 lines 218-283 */
static int LesWinMain(struct _LESWIN_W *winw);                   /* 0x007F24B0-0x007F24D0 lines 207-210 */
static int LesWinOpen(struct _LESWIN_W *winw);                   /* 0x007F24D0-0x007F2748 lines 128-199 */
static int LesWinSet(struct _LESWIN_W *winw);                    /* 0x007F2750-0x007F275C lines 117-120 */
void LesWinGetInit(struct _LESWIN_W *winw, int id);              /* 0x007F2760-0x007F27BC lines 103-108 */
void LesWinFunc(struct _LESWIN_W *winw);                         /* 0x007F27C0-0x007F2880 lines 75-96 */

#endif /* DDR_UNIT_src_CS_lesson_les_aid_c_H */
