/*
 * C:\work2\usaex2\src\CS\shop\shop_list.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x00248A80-0x002496AC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_shop_shop_list_c_H
#define DDR_UNIT_src_CS_shop_shop_list_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (18) */

/* anon_0_123 -- @anon0, 0x8 bytes, shop_list.c (DIE 0x21482E) */
struct anon_0_123 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_4_123 -- @anon4, 0x4 bytes, shop_list.c (DIE 0x215C18) */
struct anon_4_123 {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
};

/* anon_5_123 -- @anon5, 0x10 bytes, shop_list.c (DIE 0x21611A) */
struct anon_5_123 {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
};

/* anon_7_123 -- @anon7, 0x10 bytes, shop_list.c (DIE 0x216AC3) */
struct anon_7_123 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
};

/* anon_11_123 -- @anon11, 0x10 bytes, shop_list.c (DIE 0x21800E) */
struct anon_11_123 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
};

/* anon_13_123 -- @anon13, 0x14 bytes, shop_list.c (DIE 0x218354) */
struct anon_13_123 {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
};

/* anon_6_123 -- @anon6, 0x8 bytes, shop_list.c (DIE 0x216A3E) */
struct anon_6_123 {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
};

/* anon_3_123 -- @anon3, 0x14 bytes, shop_list.c (DIE 0x215B58) */
struct anon_3_123 {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
};

/* anon_1_123 -- @anon1, 0x518 bytes, shop_list.c (DIE 0x21497D) */
struct anon_1_123 {   // size 0x518
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
    /* 0x234 */ struct anon_4_123 secret_list[50];    // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ struct anon_5_123 text_w;             // 0x10
    /* 0x310 */ struct anon_7_123 button_disp_w;      // 0x10
    /* 0x320 */ struct anon_11_123 fade_env;          // 0x10
    /* 0x330 */ struct anon_13_123 pad_w;             // 0x14
    /* 0x344 */ struct anon_6_123 mess_w;             // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ struct anon_3_123 move_w[9];          // 0xB4
    /* 0x510 */ struct anon_0_123 shop_rect;          // 0x8
};

/* anon_2_123 -- @anon2, 0x4 bytes, shop_list.c (DIE 0x215046) */
struct anon_2_123 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_8_123 -- @anon8, 0xD40 bytes, shop_list.c (DIE 0x2179B5) */
struct anon_8_123 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_9_123 -- @anon9, 0x14 bytes, shop_list.c (DIE 0x217C69) */
struct anon_9_123 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_10_123 -- @anon10, 0xC bytes, shop_list.c (DIE 0x217EC7) */
struct anon_10_123 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_12_123 -- @anon12, 0x1300 bytes, shop_list.c (DIE 0x218185) */
struct anon_12_123 {   // size 0x1300
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
    /* 0x360 */ struct anon_9_123 subject[200];       // 0xFA0
};

/* anon_15_123 -- @anon15, 0x4 bytes, shop_list.c (DIE 0x2184E8) */
struct anon_15_123 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_14_123 -- @anon14, 0x4 bytes, shop_list.c (DIE 0x218489) */
union anon_14_123 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_15_123 s;                 // 0x4
};

/* anon_16_123 -- @anon16, 0x12E0 bytes, shop_list.c (DIE 0x218762) */
struct anon_16_123 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_10_123 history[400];      // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_17_123 -- @anon17, 0x2134 bytes, shop_list.c (DIE 0x218995) */
struct anon_17_123 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_14_123 userpass;           // 0x4
    /* 0x008 */ struct anon_16_123 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_8_123 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};


/* variables (1) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (7) */
static void shop_make_contents_list_other(struct anon_1_123 *work); /* 0x00248A80-0x00248C40 lines 389-442 */
static void shop_make_contents_list_custom(struct anon_1_123 *work); /* 0x00248C40-0x00248DE8 lines 323-379 */
static void shop_make_contents_list_info(struct anon_1_123 *work); /* 0x00248DF0-0x00248FB0 lines 261-314 */
static void shop_make_contents_list_outfit(struct anon_1_123 *work); /* 0x00248FB0-0x00249128 lines 211-252 */
static void shop_make_contents_list_course(struct anon_1_123 *work); /* 0x00249130-0x00249380 lines 128-199 */
static void shop_make_contents_list_music(struct anon_1_123 *work); /* 0x00249380-0x00249604 lines 53-124 */
void shop_make_contents_list(struct anon_1_123 *work);           /* 0x00249610-0x002496AC lines 24-49 */

#endif /* DDR_UNIT_src_CS_shop_shop_list_c_H */
