/*
 * C:\work\usam2\src\CS\lesson\les_sel_lv.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0021C450-0x0021D8CC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_lesson_les_sel_lv_c_H
#define DDR_UNIT_src_CS_lesson_les_sel_lv_c_H

#include "types/_tag_cLes.h"
#include "types/_tag_cLesSelLevel.h"
#include "types/_tag_cLesSelLevelCursor.h"

/* anonymous types (6) */

/* anon_0_1 -- @anon0, 0x10 bytes, les_sel_lv.c (DIE 0x8AB) */
struct anon_0_1 {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
};

/* anon_3_1 -- @anon3, 0x4 bytes, les_sel_lv.c (DIE 0xDC8) */
union anon_3_1 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_1 -- @anon1, 0x1C bytes, les_sel_lv.c (DIE 0xA2C) */
struct anon_1_1 {   // size 0x1C
    /* 0x000 */ union anon_3_1 x0;                    // 0x4
    /* 0x004 */ union anon_3_1 y0;                    // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_2_1 -- @anon2, 0x24 bytes, les_sel_lv.c (DIE 0xBFE) */
struct anon_2_1 {   // size 0x24
    /* 0x000 */ union anon_3_1 x0;                    // 0x4
    /* 0x004 */ union anon_3_1 y0;                    // 0x4
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

/* anon_4_1 -- @anon4, 0x68 bytes, les_sel_lv.c (DIE 0x132E) */
struct anon_4_1 {   // size 0x68
    /* 0x000 */ union anon_3_1 x0;                    // 0x4
    /* 0x004 */ union anon_3_1 y0;                    // 0x4
    /* 0x008 */ union anon_3_1 x1;                    // 0x4
    /* 0x00C */ union anon_3_1 y1;                    // 0x4
    /* 0x010 */ union anon_3_1 x2;                    // 0x4
    /* 0x014 */ union anon_3_1 y2;                    // 0x4
    /* 0x018 */ union anon_3_1 x3;                    // 0x4
    /* 0x01C */ union anon_3_1 y3;                    // 0x4
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
    /* 0x064 */ int flg;                              // 0x4
};

/* anon_5_1 -- @anon5, 0x48 bytes, les_sel_lv.c (DIE 0x174D) */
struct anon_5_1 {   // size 0x48
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


/* variables (7) */
struct _tag_cLesSelLevel *pLesSelLevel;                          /* @0x002A2124 size 0x4 */
static short anime_offset[18];                                   /* @0x00294F50 size 0x24 */
static int cur_y_table[3];                                       /* @0x0027EB68 size 0xC */
struct _tag_cLes *pLes;                                          /* @0x002A2128 size 0x4 */
static struct _tag_cLesSelLevel _pLesSelLevel;                   /* @0x006AF450 size 0xB0 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (8) */
static void draw_cur(void);                                      /* 0x0021C450-0x0021C8F0 lines 693-771 */
static void control_cur(void);                                   /* 0x0021C8F0-0x0021CC28 lines 627-677 */
static void init_cur(void);                                      /* 0x0021CC30-0x0021CD40 lines 596-625 */
int Update_LesSelLevel(void);                                    /* 0x0021CD40-0x0021CE70 lines 484-503 */
int View_LesSelLevel(void);                                      /* 0x0021CE70-0x0021D470 lines 325-480 */
static int cursor_ud(int dir);                                   /* 0x0021D470-0x0021D570 lines 283-309 */
int Control_LesSelLevel(void);                                   /* 0x0021D570-0x0021D7BC lines 186-280 */
int Init_LesSelLevel(void);                                      /* 0x0021D7C0-0x0021D8CC lines 108-182 */

#endif /* DDR_UNIT_src_CS_lesson_les_sel_lv_c_H */
