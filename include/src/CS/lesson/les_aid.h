/*
 * C:\work\usam2\src\CS\lesson\les_aid.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x00245690-0x002468E0
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

/* anonymous types (3) */

/* anon_2_39 -- @anon2, 0x4 bytes, les_aid.c (DIE 0x79B9C) */
union anon_2_39 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_39 -- @anon0, 0x74 bytes, les_aid.c (DIE 0x79185) */
struct anon_0_39 {   // size 0x74
    /* 0x000 */ union anon_2_39 x0;                   // 0x4
    /* 0x004 */ union anon_2_39 y0;                   // 0x4
    /* 0x008 */ union anon_2_39 x1;                   // 0x4
    /* 0x00C */ union anon_2_39 y1;                   // 0x4
    /* 0x010 */ union anon_2_39 x2;                   // 0x4
    /* 0x014 */ union anon_2_39 y2;                   // 0x4
    /* 0x018 */ union anon_2_39 x3;                   // 0x4
    /* 0x01C */ union anon_2_39 y3;                   // 0x4
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

/* anon_1_39 -- @anon1, 0x48 bytes, les_aid.c (DIE 0x796AC) */
struct anon_1_39 {   // size 0x48
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


/* variables (3) */
static int (*LesWin_Func[5])(struct _LESWIN_W *);                /* @0x002883E0 size 0x14 */
static struct _LESTEX_W LesMainTextureData[4];                   /* @0x00288400 size 0x80 */
static struct _LESTEX_INIT_SET LesMainWindowData[2];             /* @0x00288480 size 0x40 */

/* functions defined (13) */
void LesWinSetType(struct _LESWIN_W *winw, char type);           /* 0x00245690-0x002456F4 lines 617-624 */
void LesWinSetMode(struct _LESWIN_W *winw, int mode);            /* 0x00245700-0x0024581C lines 580-609 */
static void LesWinSetDefaultPartsWH(struct _LESWIN_W *winw);     /* 0x00245820-0x00245900 lines 530-572 */
static void LesWinDefaultAllSet(struct _LESWIN_W *winw);         /* 0x00245900-0x002459E0 lines 496-517 */
static int LesWinXYWHMove(struct _LESWIN_W *winw, int speed);    /* 0x002459E0-0x00245C80 lines 433-482 */
static void LesWinDisp(struct _LESWIN_W *winw);                  /* 0x00245C80-0x00246350 lines 295-390 */
static int LesWinDestroy(struct _LESWIN_W *winw);                /* 0x00246350-0x002463A8 lines 272-287 */
static int LesWinClose(struct _LESWIN_W *winw);                  /* 0x002463B0-0x00246590 lines 207-264 */
static int LesWinMain(void);                                     /* 0x00246590-0x00246598 lines 199-199 */
static int LesWinOpen(struct _LESWIN_W *winw);                   /* 0x002465A0-0x002467B0 lines 126-189 */
static int LesWinSet(struct _LESWIN_W *winw);                    /* 0x002467B0-0x002467BC lines 115-118 */
void LesWinGetInit(struct _LESWIN_W *winw, int id);              /* 0x002467C0-0x00246814 lines 101-106 */
void LesWinFunc(struct _LESWIN_W *winw);                         /* 0x00246820-0x002468E0 lines 73-94 */

#endif /* DDR_UNIT_src_CS_lesson_les_aid_c_H */
