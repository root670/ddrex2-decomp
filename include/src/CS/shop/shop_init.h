/*
 * C:\work2\usaex2\src\CS\shop\shop_init.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x00248730-0x00248A78
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_shop_shop_init_c_H
#define DDR_UNIT_src_CS_shop_shop_init_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (25) */

/* anon_0_122 -- @anon0, 0xC bytes, shop_init.c (DIE 0x20D035) */
struct anon_0_122 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_1_122 -- @anon1, 0x14 bytes, shop_init.c (DIE 0x20D19F) */
struct anon_1_122 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_2_122 -- @anon2, 0x10 bytes, shop_init.c (DIE 0x20D2DD) */
struct anon_2_122 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
};

/* anon_17_122 -- @anon17, 0x4 bytes, shop_init.c (DIE 0x2115AB) */
struct anon_17_122 {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
};

/* anon_13_122 -- @anon13, 0x10 bytes, shop_init.c (DIE 0x21098B) */
struct anon_13_122 {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
};

/* anon_16_122 -- @anon16, 0x10 bytes, shop_init.c (DIE 0x211480) */
struct anon_16_122 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
};

/* anon_5_122 -- @anon5, 0x14 bytes, shop_init.c (DIE 0x20DE86) */
struct anon_5_122 {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
};

/* anon_14_122 -- @anon14, 0x8 bytes, shop_init.c (DIE 0x21102A) */
struct anon_14_122 {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
};

/* anon_12_122 -- @anon12, 0x14 bytes, shop_init.c (DIE 0x210164) */
struct anon_12_122 {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
};

/* anon_10_122 -- @anon10, 0x8 bytes, shop_init.c (DIE 0x20F1C3) */
struct anon_10_122 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_3_122 -- @anon3, 0x518 bytes, shop_init.c (DIE 0x20D42D) */
struct anon_3_122 {   // size 0x518
    /* 0x000 */ unsigned char *free_mem_addr;         // 0x4
    /* 0x004 */ unsigned char *mv_data_addr;          // 0x4
    /* 0x008 */ unsigned char *shop_data_addr;        // 0x4
    /* 0x00C */ unsigned char *course_data_addr;      // 0x4
    /* 0x010 */ unsigned char *mess_data_addr;        // 0x4
    /* 0x014 */ unsigned char step;                   // 0x1
    /* 0x015 */ unsigned char step_s;                 // 0x1
    /* 0x016 */ unsigned char mess_str[512];          // 0x200
    /* 0x216 */ // 0x2 bytes padding
    /* 0x218 */ unsigned int syscnt;                  // 0x4
    /* 0x21C */ unsigned int syscnt0;                 // 0x4
    /* 0x220 */ char tab_cursor;                      // 0x1
    /* 0x221 */ char tab_cursor_new;                  // 0x1
    /* 0x222 */ char contents_cursor;                 // 0x1
    /* 0x223 */ char contents_cursor_new;             // 0x1
    /* 0x224 */ char contents_cursor_disp_top;        // 0x1
    /* 0x225 */ char contents_cursor_disp_top_new;    // 0x1
    /* 0x226 */ char tab_state;                       // 0x1
    /* 0x227 */ char cont_state;                      // 0x1
    /* 0x228 */ char cursor_anime;                    // 0x1
    /* 0x229 */ char cursor_anime_flag;               // 0x1
    /* 0x22A */ char confirm_cursor;                  // 0x1
    /* 0x22B */ char info_cursor;                     // 0x1
    /* 0x22C */ char info_list_disp;                  // 0x1
    /* 0x22D */ unsigned char is_disp_dancer;         // 0x1
    /* 0x22E */ signed char start_pid_first;          // 0x1
    /* 0x22F */ signed char start_pid;                // 0x1
    /* 0x230 */ unsigned int secret_list_num;         // 0x4
    /* 0x234 */ struct anon_17_122 secret_list[50];   // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ struct anon_13_122 text_w;            // 0x10
    /* 0x310 */ struct anon_16_122 button_disp_w;     // 0x10
    /* 0x320 */ struct anon_2_122 fade_env;           // 0x10
    /* 0x330 */ struct anon_5_122 pad_w;              // 0x14
    /* 0x344 */ struct anon_14_122 mess_w;            // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ struct anon_12_122 move_w[9];         // 0xB4
    /* 0x510 */ struct anon_10_122 shop_rect;         // 0x8
};

/* anon_23_122 -- @anon23, 0x14 bytes, shop_init.c (DIE 0x2142CF) */
struct anon_23_122 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_4_122 -- @anon4, 0x1300 bytes, shop_init.c (DIE 0x20DB1A) */
struct anon_4_122 {   // size 0x1300
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
    /* 0x360 */ struct anon_23_122 subject[200];      // 0xFA0
};

/* anon_7_122 -- @anon7, 0x4 bytes, shop_init.c (DIE 0x20DFF4) */
struct anon_7_122 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_6_122 -- @anon6, 0x4 bytes, shop_init.c (DIE 0x20DF72) */
union anon_6_122 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_7_122 s;                  // 0x4
};

/* anon_8_122 -- @anon8, 0x12E0 bytes, shop_init.c (DIE 0x20E26D) */
struct anon_8_122 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_0_122 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_21_122 -- @anon21, 0xD40 bytes, shop_init.c (DIE 0x213D53) */
struct anon_21_122 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_9_122 -- @anon9, 0x2134 bytes, shop_init.c (DIE 0x20E863) */
struct anon_9_122 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_6_122 userpass;            // 0x4
    /* 0x008 */ struct anon_8_122 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_21_122 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_11_122 -- @anon11, 0x4 bytes, shop_init.c (DIE 0x20F4DE) */
struct anon_11_122 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_15_122 -- @anon15, 0x4 bytes, shop_init.c (DIE 0x2113CB) */
struct anon_15_122 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_20_122 -- @anon20, 0x4 bytes, shop_init.c (DIE 0x213CAD) */
union anon_20_122 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_22_122 -- @anon22, 0x10 bytes, shop_init.c (DIE 0x2141AE) */
struct anon_22_122 {   // size 0x10
    /* 0x000 */ union anon_20_122 x0;                 // 0x4
    /* 0x004 */ union anon_20_122 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_18_122 -- @anon18, 0x184 bytes, shop_init.c (DIE 0x2119D0) */
struct anon_18_122 {   // size 0x184
    /* 0x000 */ struct anon_22_122 line_a[8];         // 0x80
    /* 0x080 */ struct anon_22_122 line_b[8];         // 0x80
    /* 0x100 */ struct anon_22_122 line_c[8];         // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_19_122 -- @anon19, 0x8 bytes, shop_init.c (DIE 0x211A7F) */
struct anon_19_122 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};

/* anon_24_122 -- @anon24, 0xC bytes, shop_init.c (DIE 0x214452) */
struct anon_24_122 {   // size 0xC
    /* 0x000 */ int mode_quit_flg;                    // 0x4
    /* 0x004 */ int state;                            // 0x4
    /* 0x008 */ int renewal_record_flag;              // 0x4
};


/* variables (5) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct anon_24_122 usr_work;                                     /* @0x00328A20 size 0xC */
struct anon_19_122 course_bin[];                                 /* @0x002DA780 */
struct anon_19_122 shop_bin[];                                   /* @0x002DD700 */

/* functions defined (2) */
static void shop_init_work(struct anon_3_122 *work);             /* 0x00248730-0x002487D8 lines 237-263 */
void shop_init(struct anon_3_122 *work);                         /* 0x002487E0-0x00248A78 lines 36-225 */

#endif /* DDR_UNIT_src_CS_shop_shop_init_c_H */
