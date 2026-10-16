/*
 * C:\work\usam2\src\CS\records\recend.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x0022B050-0x0022E6A0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_recend_c_H
#define DDR_UNIT_src_CS_records_recend_c_H

#include "types/_recend_tex.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cRec.h"
#include "types/_tag_cRecEnd.h"

/* anonymous types (7) */

/* anon_6_17 -- @anon6, 0x4 bytes, recend.c (DIE 0x391CB) */
union anon_6_17 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_17 -- @anon0, 0x74 bytes, recend.c (DIE 0x36F83) */
struct anon_0_17 {   // size 0x74
    /* 0x000 */ union anon_6_17 x0;                   // 0x4
    /* 0x004 */ union anon_6_17 y0;                   // 0x4
    /* 0x008 */ union anon_6_17 x1;                   // 0x4
    /* 0x00C */ union anon_6_17 y1;                   // 0x4
    /* 0x010 */ union anon_6_17 x2;                   // 0x4
    /* 0x014 */ union anon_6_17 y2;                   // 0x4
    /* 0x018 */ union anon_6_17 x3;                   // 0x4
    /* 0x01C */ union anon_6_17 y3;                   // 0x4
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

/* anon_1_17 -- @anon1, 0x48 bytes, recend.c (DIE 0x37777) */
struct anon_1_17 {   // size 0x48
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

/* anon_2_17 -- @anon2, 0xCC8 bytes, recend.c (DIE 0x379F9) */
struct anon_2_17 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_3_17 -- @anon3, 0xC bytes, recend.c (DIE 0x3860E) */
struct anon_3_17 {   // size 0xC
    /* 0x000 */ int year;                             // 0x4
    /* 0x004 */ int month;                            // 0x4
    /* 0x008 */ int day;                              // 0x4
};

/* anon_4_17 -- @anon4, 0x1C bytes, recend.c (DIE 0x38E4B) */
struct anon_4_17 {   // size 0x1C
    /* 0x000 */ union anon_6_17 x0;                   // 0x4
    /* 0x004 */ union anon_6_17 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_5_17 -- @anon5, 0x24 bytes, recend.c (DIE 0x39037) */
struct anon_5_17 {   // size 0x24
    /* 0x000 */ union anon_6_17 x0;                   // 0x4
    /* 0x004 */ union anon_6_17 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01C */ unsigned char r0;                     // 0x1
    /* 0x01D */ unsigned char g0;                     // 0x1
    /* 0x01E */ unsigned char b0;                     // 0x1
    /* 0x01F */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};


/* variables (5) */
struct _tag_cRecEnd *pRecEnd;                                    /* @0x002A2250 size 0x4 */
static struct _recend_tex RecendTexDataTable[21];                /* @0x00282940 size 0x2A0 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
struct _tag_cRec *pRec;                                          /* @0x002A06B8 size 0x4 */
static struct _tag_cRecEnd _pRecEnd;                             /* @0x006B2980 size 0x340 */

/* functions defined (13) */
static void RecendPrintDigit(int _x, int _y, int _tex_num, unsigned int _dig00, unsigned int _dig01, char _figure, unsigned char _alpha); /* 0x0022B050-0x0022B358 lines 1082-1145 */
static void RecendTexDisp(int num);                              /* 0x0022B360-0x0022B720 lines 999-1052 */
static void RecendAllDisp(void);                                 /* 0x0022B720-0x0022BF04 lines 846-993 */
static void RecendTexWaveRGB(int num);                           /* 0x0022BF10-0x0022C078 lines 800-841 */
static void RecendTexMoveXY(int num);                            /* 0x0022C080-0x0022C2D0 lines 759-795 */
static void RecendTexSetPage(int page);                          /* 0x0022C2D0-0x0022CA38 lines 643-732 */
static void RecendDataDelete(int _page, int _cur);               /* 0x0022CA40-0x0022CCA8 lines 620-635 */
static void RecendTexDelEdge(int x, int y);                      /* 0x0022CCB0-0x0022D020 lines 500-592 */
static void RecendTexDelOpen(void);                              /* 0x0022D020-0x0022D18C lines 478-487 */
int Update_Recend(void);                                         /* 0x0022D190-0x0022D358 lines 382-410 */
int View_Recend(void);                                           /* 0x0022D360-0x0022D398 lines 368-377 */
int Control_Recend(void);                                        /* 0x0022D3A0-0x0022DB28 lines 186-363 */
int Init_Recend(void);                                           /* 0x0022DB30-0x0022E6A0 lines 115-181 */

#endif /* DDR_UNIT_src_CS_records_recend_c_H */
