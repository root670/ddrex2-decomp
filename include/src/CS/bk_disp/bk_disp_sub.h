/*
 * C:\work2\usaex2\src\CS\bk_disp\bk_disp_sub.c
 * MW MIPS C Compiler, overlay main; 15 functions, code 0x00202840-0x00203EA8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_bk_disp_bk_disp_sub_c_H
#define DDR_UNIT_src_CS_bk_disp_bk_disp_sub_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (23) */

/* anon_13_59 -- @anon13, 0x4 bytes, bk_disp_sub.c (DIE 0xE1C8E) */
union anon_13_59 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_15_59 -- @anon15, 0x10 bytes, bk_disp_sub.c (DIE 0xE25F5) */
struct anon_15_59 {   // size 0x10
    /* 0x000 */ union anon_13_59 x0;                  // 0x4
    /* 0x004 */ union anon_13_59 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_0_59 -- @anon0, 0x184 bytes, bk_disp_sub.c (DIE 0xDDDCA) */
struct anon_0_59 {   // size 0x184
    /* 0x000 */ struct anon_15_59 line_a[8];          // 0x80
    /* 0x080 */ struct anon_15_59 line_b[8];          // 0x80
    /* 0x100 */ struct anon_15_59 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_22_59 -- @anon22, 0xC bytes, bk_disp_sub.c (DIE 0xE4D77) */
struct anon_22_59 {   // size 0xC
    /* 0x000 */ int use;                              // 0x4
    /* 0x004 */ int label;                            // 0x4
    /* 0x008 */ int data_ok;                          // 0x4
};

/* anon_1_59 -- @anon1, 0x58 bytes, bk_disp_sub.c (DIE 0xDDFDB) */
struct anon_1_59 {   // size 0x58
    /* 0x000 */ unsigned char *buf[3];                // 0xC
    /* 0x00C */ struct anon_14_59 *tbl_addr;          // 0x4
    /* 0x010 */ struct anon_22_59 buf_info[3];        // 0x24
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
};

/* anon_2_59 -- @anon2, 0xD40 bytes, bk_disp_sub.c (DIE 0xE0649) */
struct anon_2_59 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_3_59 -- @anon3, 0x14 bytes, bk_disp_sub.c (DIE 0xE0921) */
struct anon_3_59 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_4_59 -- @anon4, 0xC bytes, bk_disp_sub.c (DIE 0xE0BA3) */
struct anon_4_59 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_5_59 -- @anon5, 0x10 bytes, bk_disp_sub.c (DIE 0xE0CE9) */
union anon_5_59 {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
};

/* anon_6_59 -- @anon6, 0x14 bytes, bk_disp_sub.c (DIE 0xE0ECE) */
struct anon_6_59 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_7_59 -- @anon7, 0x1C bytes, bk_disp_sub.c (DIE 0xE0F9F) */
struct anon_7_59 {   // size 0x1C
    /* 0x000 */ int tbp;                              // 0x4
    /* 0x004 */ int psm;                              // 0x4
    /* 0x008 */ int cbp;                              // 0x4
    /* 0x00C */ int cpsm;                             // 0x4
    /* 0x010 */ int width;                            // 0x4
    /* 0x014 */ int height;                           // 0x4
    /* 0x018 */ int colors;                           // 0x4
};

/* anon_8_59 -- @anon8, 0x1300 bytes, bk_disp_sub.c (DIE 0xE1180) */
struct anon_8_59 {   // size 0x1300
    /* 0x000 */ unsigned char evboot[24];             // 0x18
    /* 0x018 */ unsigned char is_savedata;            // 0x1
    /* 0x019 */ signed char max_area;                 // 0x1
    /* 0x01A */ signed char disp_type;                // 0x1
    /* 0x01B */ char pading;                          // 0x1
    /* 0x01C */ unsigned char dancer_use_cnt[24];     // 0x18
    /* 0x034 */ int cur_cursor;                       // 0x4
    /* 0x038 */ unsigned int all_clear_count;         // 0x4
    /* 0x03C */ unsigned int all_play_time;           // 0x4
    /* 0x040 */ int route[200];                       // 0x320
    /* 0x360 */ struct anon_3_59 subject[200];        // 0xFA0
};

/* anon_11_59 -- @anon11, 0x4 bytes, bk_disp_sub.c (DIE 0xE1603) */
struct anon_11_59 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_9_59 -- @anon9, 0x4 bytes, bk_disp_sub.c (DIE 0xE1402) */
union anon_9_59 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_11_59 s;                  // 0x4
};

/* anon_10_59 -- @anon10, 0x12E0 bytes, bk_disp_sub.c (DIE 0xE1484) */
struct anon_10_59 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_4_59 history[400];        // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_12_59 -- @anon12, 0x2134 bytes, bk_disp_sub.c (DIE 0xE1A61) */
struct anon_12_59 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_9_59 userpass;             // 0x4
    /* 0x008 */ struct anon_10_59 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_2_59 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_14_59 -- @anon14, 0x10 bytes, bk_disp_sub.c (DIE 0xE248E) */
struct anon_14_59 {   // size 0x10
    /* 0x000 */ int start;                            // 0x4
    /* 0x004 */ int ti_start;                         // 0x4
    /* 0x008 */ int ti_end;                           // 0x4
    /* 0x00C */ unsigned char **list;                 // 0x4
};

/* anon_16_59 -- @anon16, 0x4 bytes, bk_disp_sub.c (DIE 0xE26F2) */
struct anon_16_59 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_17_59 -- @anon17, 0x8 bytes, bk_disp_sub.c (DIE 0xE294F) */
struct anon_17_59 {   // size 0x8
    /* 0x000 */ union anon_5_59 *decTags;             // 0x4
    /* 0x004 */ struct anon_19_59 *cscBuff;           // 0x4
};

/* anon_18_59 -- @anon18, 0x68 bytes, bk_disp_sub.c (DIE 0xE3111) */
struct anon_18_59 {   // size 0x68
    /* 0x000 */ union anon_13_59 x0;                  // 0x4
    /* 0x004 */ union anon_13_59 y0;                  // 0x4
    /* 0x008 */ union anon_13_59 x1;                  // 0x4
    /* 0x00C */ union anon_13_59 y1;                  // 0x4
    /* 0x010 */ union anon_13_59 x2;                  // 0x4
    /* 0x014 */ union anon_13_59 y2;                  // 0x4
    /* 0x018 */ union anon_13_59 x3;                  // 0x4
    /* 0x01C */ union anon_13_59 y3;                  // 0x4
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

/* anon_19_59 -- @anon19, 0x400 bytes, bk_disp_sub.c (DIE 0xE3600) */
struct anon_19_59 {   // size 0x400
    /* 0x000 */ unsigned int pix[256];                // 0x400
};

/* anon_20_59 -- @anon20, 0x48 bytes, bk_disp_sub.c (DIE 0xE40ED) */
struct anon_20_59 {   // size 0x48
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
};

/* anon_21_59 -- @anon21, 0x4 bytes, bk_disp_sub.c (DIE 0xE4BEA) */
struct anon_21_59 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};


/* variables (8) */
struct anon_1_59 *bkw;                                           /* @0x002DDAE0 size 0x4 */
static struct anon_17_59 *mpw;                                   /* @0x002DDAE4 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct anon_20_59 mpeg;                                          /* @0x0032A5C0 size 0x48 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct anon_14_59 bk_mv_tbl[];                                   /* @0x002BAEA0 */
static struct anon_17_59 mpeg_disp_w;                            /* @0x002DE518 size 0x8 */
static struct anon_1_59 bk_disp_w;                               /* @0x0071D910 size 0x58 */

/* functions defined (15) */
struct anon_14_59 *bk_cur_mv_tbl(void);                          /* 0x00202840-0x0020284C lines 831-832 */
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
