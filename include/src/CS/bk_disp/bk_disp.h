/*
 * C:\work2\usaex2\src\CS\bk_disp\bk_disp.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x00203EB0-0x002046C0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_bk_disp_bk_disp_c_H
#define DDR_UNIT_src_CS_bk_disp_bk_disp_c_H

#include "types/_EYETOY_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/play_w.h"
#include "types/tex_bind.h"

/* anonymous types (16) */

/* anon_0_60 -- @anon0, 0xD40 bytes, bk_disp.c (DIE 0xE698B) */
struct anon_0_60 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_1_60 -- @anon1, 0x48 bytes, bk_disp.c (DIE 0xE6A88) */
struct anon_1_60 {   // size 0x48
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

/* anon_2_60 -- @anon2, 0x14 bytes, bk_disp.c (DIE 0xE70B1) */
struct anon_2_60 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_3_60 -- @anon3, 0xC bytes, bk_disp.c (DIE 0xE7333) */
struct anon_3_60 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_4_60 -- @anon4, 0x14 bytes, bk_disp.c (DIE 0xE7B87) */
struct anon_4_60 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_5_60 -- @anon5, 0x10 bytes, bk_disp.c (DIE 0xE856D) */
union anon_5_60 {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
};

/* anon_6_60 -- @anon6, 0x1300 bytes, bk_disp.c (DIE 0xE869E) */
struct anon_6_60 {   // size 0x1300
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
    /* 0x360 */ struct anon_2_60 subject[200];        // 0xFA0
};

/* anon_8_60 -- @anon8, 0x4 bytes, bk_disp.c (DIE 0xE8AF6) */
struct anon_8_60 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_7_60 -- @anon7, 0x4 bytes, bk_disp.c (DIE 0xE8A2C) */
union anon_7_60 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_8_60 s;                   // 0x4
};

/* anon_9_60 -- @anon9, 0x12E0 bytes, bk_disp.c (DIE 0xE8D93) */
struct anon_9_60 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_3_60 history[400];        // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_10_60 -- @anon10, 0x2134 bytes, bk_disp.c (DIE 0xE9033) */
struct anon_10_60 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_7_60 userpass;             // 0x4
    /* 0x008 */ struct anon_9_60 pwork;               // 0x12E0
    /* 0x12E8 */ struct anon_0_60 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_11_60 -- @anon11, 0x4 bytes, bk_disp.c (DIE 0xE9316) */
union anon_11_60 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_12_60 -- @anon12, 0x4 bytes, bk_disp.c (DIE 0xE958B) */
struct anon_12_60 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_13_60 -- @anon13, 0x10 bytes, bk_disp.c (DIE 0xE977D) */
struct anon_13_60 {   // size 0x10
    /* 0x000 */ union anon_11_60 x0;                  // 0x4
    /* 0x004 */ union anon_11_60 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_14_60 -- @anon14, 0x4 bytes, bk_disp.c (DIE 0xEB792) */
struct anon_14_60 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_15_60 -- @anon15, 0x184 bytes, bk_disp.c (DIE 0xEBCB4) */
struct anon_15_60 {   // size 0x184
    /* 0x000 */ struct anon_13_60 line_a[8];          // 0x80
    /* 0x080 */ struct anon_13_60 line_b[8];          // 0x80
    /* 0x100 */ struct anon_13_60 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};


/* variables (4) */
static int ti_cnt;                                               /* @0x002DE520 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _EYETOY_W *EYETOYW;                                       /* @0x002DD9A8 size 0x4 */

/* functions defined (6) */
static void bk_disp_title(int bright, int blend);                /* 0x00203EB0-0x0020426C lines 272-358 */
void bk_play_disp_finish(void);                                  /* 0x00204270-0x0020429C lines 261-264 */
void bk_play_disp_step(void);                                    /* 0x002042A0-0x002045B4 lines 117-256 */
void bk_play_disp_init(void);                                    /* 0x002045C0-0x0020466C lines 88-112 */
int bk_disp_read_wait(void);                                     /* 0x00204670-0x002046AC lines 74-80 */
void bk_disp_read_set(int flg);                                  /* 0x002046B0-0x002046C0 lines 67-67 */

#endif /* DDR_UNIT_src_CS_bk_disp_bk_disp_c_H */
