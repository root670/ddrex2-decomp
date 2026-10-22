/*
 * C:\work2\usaex2\src\CS\bk_disp\bk_disp_sub.c
 * MW MIPS C Compiler, overlay main; 15 functions, code 0x00202840-0x00203EA8
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
#ifndef DDR_UNIT_src_CS_bk_disp_bk_disp_sub_c_H
#define DDR_UNIT_src_CS_bk_disp_bk_disp_sub_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (9) */

/* anon_14_59 -- @anon14, 0x10 bytes, bk_disp_sub.c (DIE 0xE248E) */
typedef struct {   // size 0x10
    /* 0x000 */ int start;                            // 0x4
    /* 0x004 */ int ti_start;                         // 0x4
    /* 0x008 */ int ti_end;                           // 0x4
    /* 0x00C */ unsigned char **list;                 // 0x4
} anon_14_59;

/* anon_22_59 -- @anon22, 0xC bytes, bk_disp_sub.c (DIE 0xE4D77) */
typedef struct {   // size 0xC
    /* 0x000 */ int use;                              // 0x4
    /* 0x004 */ int label;                            // 0x4
    /* 0x008 */ int data_ok;                          // 0x4
} anon_22_59;

/* anon_1_59 -- @anon1, 0x58 bytes, bk_disp_sub.c (DIE 0xDDFDB) */
typedef struct {   // size 0x58
    /* 0x000 */ unsigned char *buf[3];                // 0xC
    /* 0x00C */ anon_14_59 *tbl_addr;                 // 0x4
    /* 0x010 */ anon_22_59 buf_info[3];               // 0x24
    /* 0x034 */ int load_label;                       // 0x4
    /* 0x038 */ int play_label;                       // 0x4
    /* 0x03C */ int load_id;                          // 0x4
    /* 0x040 */ int play_id;                          // 0x4
    /* 0x044 */ unsigned char err_flg;                // 0x1
    /* 0x045 */ unsigned char prepare_flg;            // 0x1
    /* 0x046 */ unsigned char start_flg;              // 0x1
    /* 0x047 */ unsigned char eyetoy_flg;             // 0x1
    /* 0x048 */ unsigned char disp_flg;               // 0x1
    /* 0x049 */ unsigned char is_pv;                  // 0x1
    /* 0x04A */ unsigned char test_flg;               // 0x1
    /* 0x04B */ unsigned char pad;                    // 0x1
    /* 0x04C */ int ct;                               // 0x4
    /* 0x050 */ int state;                            // 0x4
    /* 0x054 */ int cue_label;                        // 0x4
} anon_1_59;

/* anon_5_59 -- @anon5, 0x10 bytes, bk_disp_sub.c (DIE 0xE0CE9) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_5_59;

/* anon_7_59 -- @anon7, 0x1C bytes, bk_disp_sub.c (DIE 0xE0F9F) */
typedef struct {   // size 0x1C
    /* 0x000 */ int tbp;                              // 0x4
    /* 0x004 */ int psm;                              // 0x4
    /* 0x008 */ int cbp;                              // 0x4
    /* 0x00C */ int cpsm;                             // 0x4
    /* 0x010 */ int width;                            // 0x4
    /* 0x014 */ int height;                           // 0x4
    /* 0x018 */ int colors;                           // 0x4
} anon_7_59;

/* anon_19_59 -- @anon19, 0x400 bytes, bk_disp_sub.c (DIE 0xE3600) */
typedef struct {   // size 0x400
    /* 0x000 */ unsigned int pix[256];                // 0x400
} anon_19_59;

/* anon_17_59 -- @anon17, 0x8 bytes, bk_disp_sub.c (DIE 0xE294F) */
typedef struct {   // size 0x8
    /* 0x000 */ anon_5_59 *decTags;                   // 0x4
    /* 0x004 */ anon_19_59 *cscBuff;                  // 0x4
} anon_17_59;

/* anon_18_59 -- @anon18, 0x68 bytes, bk_disp_sub.c (DIE 0xE3111) */
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
} anon_18_59;

/* anon_20_59 -- @anon20, 0x48 bytes, bk_disp_sub.c (DIE 0xE40ED) */
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
} anon_20_59;


/* variables (8) */
anon_1_59 *bkw;                                                  /* @0x002DDAE0 size 0x4 */
static anon_17_59 *mpw;                                          /* @0x002DDAE4 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_20_59 mpeg;                                                 /* @0x0032A5C0 size 0x48 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
anon_14_59 bk_mv_tbl[];                                          /* @0x002BAEA0 */
static anon_17_59 mpeg_disp_w;                                   /* @0x002DE518 size 0x8 */
static anon_1_59 bk_disp_w;                                      /* @0x0071D910 size 0x58 */

/* functions defined (15) */
anon_14_59 *bk_cur_mv_tbl(void);                                 /* 0x00202840-0x0020284C lines 831-832 */
int bk_is_start(void);                                           /* 0x00202850-0x0020285C lines 824-825 */
int bk_is_eyetoy(void);                                          /* 0x00202860-0x0020286C lines 817-818 */
int bk_is_prarare(void);                                         /* 0x00202870-0x0020287C lines 810-811 */
int bk_is_err(void);                                             /* 0x00202880-0x0020288C lines 803-804 */
void bk_mpeg_manager(void);                                      /* 0x00202890-0x00202A64 lines 768-793 */
static int bkm_man_request_load(int label);                      /* 0x00202A70-0x00202BCC lines 652-688 */
static void bkm_man_change_play_label(int label);                /* 0x00202BD0-0x00202D64 lines 590-646 */
void bk_mpeg_disp(void);                                         /* 0x00202D70-0x00203788 lines 392-578 */
void bk_mpeg_term(void);                                         /* 0x00203790-0x002037C8 lines 380-386 */
void bk_mpeg_play(void);                                         /* 0x002037D0-0x0020393C lines 327-376 */
void bk_mpeg_play_start(void);                                   /* 0x00203940-0x00203968 lines 319-322 */
void bk_mpeg_init(struct music_info *mip, int flg);              /* 0x00203970-0x00203B28 lines 232-314 */
static void bk_mpeg_SetDecTag(void);                             /* 0x00203B30-0x00203D5C lines 116-215 */
static int bk_mpeg_work_set(unsigned int *addr);                 /* 0x00203D60-0x00203EA8 lines 68-110 */

#endif /* DDR_UNIT_src_CS_bk_disp_bk_disp_sub_c_H */
