/*
 * C:\work2\usaex2\src\AM\s573\demo\title_demo.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x001E7710-0x001E8068
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_AM_s573_demo_title_demo_c_H
#define DDR_UNIT_src_AM_s573_demo_title_demo_c_H

#include "types/g_game_w.h"

/* anonymous types (8) */

/* anon_1_41 -- @anon1, 0x10 bytes, title_demo.c (DIE 0x6AB84) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_1_41;

/* anon_2_41 -- @anon2, 0x400 bytes, title_demo.c (DIE 0x6AC91) */
typedef struct {   // size 0x400
    /* 0x000 */ unsigned int pix[256];                // 0x400
} anon_2_41;

/* anon_0_41 -- @anon0, 0x30 bytes, title_demo.c (DIE 0x6A960) */
typedef struct {   // size 0x30
    /* 0x000 */ unsigned char *buf[6];                // 0x18
    /* 0x018 */ anon_1_41 *decTags;                   // 0x4
    /* 0x01C */ anon_2_41 *cscBuff;                   // 0x4
    /* 0x020 */ unsigned char *vag_addr;              // 0x4
    /* 0x024 */ float ct;                             // 0x4
    /* 0x028 */ unsigned char step;                   // 0x1
    /* 0x029 */ unsigned char cur_play;               // 0x1
    /* 0x02A */ unsigned char cur_read;               // 0x1
    /* 0x02B */ unsigned char ini_flg;                // 0x1
    /* 0x02C */ unsigned char disp_flg;               // 0x1
    /* 0x02D */ unsigned char vag_flg;                // 0x1
    /* 0x02E */ unsigned char read_step;              // 0x1
    /* 0x02F */ unsigned char play_flg;               // 0x1
} anon_0_41;

/* anon_4_41 -- @anon4, 0x48 bytes, title_demo.c (DIE 0x6B894) */
typedef struct {   // size 0x48
    /* 0x000 */ int width;                            // 0x4
    /* 0x004 */ int height;                           // 0x4
    /* 0x008 */ int frameCount;                       // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ long pts;                             // 0x8
    /* 0x018 */ long dts;                             // 0x8
    /* 0x020 */ unsigned long flags;                  // 0x8
    /* 0x028 */ long pts2nd;                          // 0x8
    /* 0x030 */ long dts2nd;                          // 0x8
    /* 0x038 */ unsigned long flags2nd;               // 0x8
    /* 0x040 */ void *sys;                            // 0x4
    /* 0x044 */ // 0x4 bytes padding
} anon_4_41;

/* anon_5_41 -- @anon5, 0x1C bytes, title_demo.c (DIE 0x6BCFE) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_5_41;

/* anon_6_41 -- @anon6, 0x1C bytes, title_demo.c (DIE 0x6BEE8) */
typedef struct {   // size 0x1C
    /* 0x000 */ int tbp;                              // 0x4
    /* 0x004 */ int psm;                              // 0x4
    /* 0x008 */ int cbp;                              // 0x4
    /* 0x00C */ int cpsm;                             // 0x4
    /* 0x010 */ int width;                            // 0x4
    /* 0x014 */ int height;                           // 0x4
    /* 0x018 */ int colors;                           // 0x4
} anon_6_41;

/* anon_10_41 -- @anon10, 0x68 bytes, title_demo.c (DIE 0x6C6AD) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
    /* 0x010 */ anon_d075beaabcd0 x2;                 // 0x4
    /* 0x014 */ anon_d075beaabcd0 y2;                 // 0x4
    /* 0x018 */ anon_d075beaabcd0 x3;                 // 0x4
    /* 0x01C */ anon_d075beaabcd0 y3;                 // 0x4
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
} anon_10_41;

/* anon_11_41 -- @anon11, 0x8 bytes, title_demo.c (DIE 0x6CAF3) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
} anon_11_41;


/* variables (6) */
static unsigned char *ti_mv_list[6];                             /* @0x002B8B90 size 0x18 */
static anon_0_41 *tmw;                                           /* @0x002DDA80 size 0x4 */
anon_4_41 mpeg;                                                  /* @0x0032A5C0 size 0x48 */
anon_11_41 ex2_movie_vag[];                                      /* @0x002DA280 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
static anon_0_41 ti_movie_w;                                     /* @0x00713DF0 size 0x30 */

/* functions defined (8) */
static void ti_movie_SetDecTag(void);                            /* 0x001E7710-0x001E78A8 lines 376-462 */
static int ti_movie_work_set(unsigned int *addr);                /* 0x001E78B0-0x001E798C lines 325-360 */
static void ti_movie_play(void);                                 /* 0x001E7990-0x001E7B14 lines 277-319 */
void title_movie_disp(unsigned int pri);                         /* 0x001E7B20-0x001E7DB4 lines 199-268 */
int title_movie_manage(void);                                    /* 0x001E7DC0-0x001E7FB4 lines 131-190 */
int title_movie_play_ok(void);                                   /* 0x001E7FC0-0x001E7FCC lines 125-126 */
void title_movie_play_start(void);                               /* 0x001E7FD0-0x001E7FE0 lines 119-120 */
void title_movie_init(void);                                     /* 0x001E7FE0-0x001E8068 lines 96-113 */

#endif /* DDR_UNIT_src_AM_s573_demo_title_demo_c_H */
