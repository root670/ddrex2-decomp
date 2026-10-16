/*
 * C:\work\usam2\src\CS\records\recend.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x0022b050-0x0022e6a0
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

/* anon_6_17 -- @anon6, 0x4 bytes, recend.c (DIE 0x391cb) */
union anon_6_17 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_17 -- @anon0, 0x74 bytes, recend.c (DIE 0x36f83) */
struct anon_0_17 {   // size 0x74
    /* 0x000 */ union anon_6_17 x0;                   // 0x4
    /* 0x004 */ union anon_6_17 y0;                   // 0x4
    /* 0x008 */ union anon_6_17 x1;                   // 0x4
    /* 0x00c */ union anon_6_17 y1;                   // 0x4
    /* 0x010 */ union anon_6_17 x2;                   // 0x4
    /* 0x014 */ union anon_6_17 y2;                   // 0x4
    /* 0x018 */ union anon_6_17 x3;                   // 0x4
    /* 0x01c */ union anon_6_17 y3;                   // 0x4
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

/* anon_1_17 -- @anon1, 0x48 bytes, recend.c (DIE 0x37777) */
struct anon_1_17 {   // size 0x48
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

/* anon_2_17 -- @anon2, 0xcc8 bytes, recend.c (DIE 0x379f9) */
struct anon_2_17 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_3_17 -- @anon3, 0xc bytes, recend.c (DIE 0x3860e) */
struct anon_3_17 {   // size 0xc
    /* 0x000 */ int year;                             // 0x4
    /* 0x004 */ int month;                            // 0x4
    /* 0x008 */ int day;                              // 0x4
};

/* anon_4_17 -- @anon4, 0x1c bytes, recend.c (DIE 0x38e4b) */
struct anon_4_17 {   // size 0x1c
    /* 0x000 */ union anon_6_17 x0;                   // 0x4
    /* 0x004 */ union anon_6_17 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00c */ float w;                              // 0x4
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


/* variables (5) */
struct _tag_cRecEnd *pRecEnd;                                    /* @0x002a2250 size 0x4 */
static struct _recend_tex RecendTexDataTable[21];                /* @0x00282940 size 0x2a0 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */
struct _tag_cRec *pRec;                                          /* @0x002a06b8 size 0x4 */
static struct _tag_cRecEnd _pRecEnd;                             /* @0x006b2980 size 0x340 */

/* functions defined (13) */
static void RecendPrintDigit(int _x, int _y, int _tex_num, unsigned int _dig00, unsigned int _dig01, char _figure, unsigned char _alpha); /* 0x0022b050-0x0022b358 lines 1082-1145 */
static void RecendTexDisp(int num);                              /* 0x0022b360-0x0022b720 lines 999-1052 */
static void RecendAllDisp(void);                                 /* 0x0022b720-0x0022bf04 lines 846-993 */
static void RecendTexWaveRGB(int num);                           /* 0x0022bf10-0x0022c078 lines 800-841 */
static void RecendTexMoveXY(int num);                            /* 0x0022c080-0x0022c2d0 lines 759-795 */
static void RecendTexSetPage(int page);                          /* 0x0022c2d0-0x0022ca38 lines 643-732 */
static void RecendDataDelete(int _page, int _cur);               /* 0x0022ca40-0x0022cca8 lines 620-635 */
static void RecendTexDelEdge(int x, int y);                      /* 0x0022ccb0-0x0022d020 lines 500-592 */
static void RecendTexDelOpen(void);                              /* 0x0022d020-0x0022d18c lines 478-487 */
int Update_Recend(void);                                         /* 0x0022d190-0x0022d358 lines 382-410 */
int View_Recend(void);                                           /* 0x0022d360-0x0022d398 lines 368-377 */
int Control_Recend(void);                                        /* 0x0022d3a0-0x0022db28 lines 186-363 */
int Init_Recend(void);                                           /* 0x0022db30-0x0022e6a0 lines 115-181 */

#endif /* DDR_UNIT_src_CS_records_recend_c_H */
