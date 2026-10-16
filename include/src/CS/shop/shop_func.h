/*
 * C:\work2\usaex2\src\CS\shop\shop_func.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x00253AE0-0x0025427C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_shop_shop_func_c_H
#define DDR_UNIT_src_CS_shop_shop_func_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (18) */

/* anon_0_128 -- @anon0, 0x8 bytes, shop_func.c (DIE 0x237602) */
struct anon_0_128 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_7_128 -- @anon7, 0x4 bytes, shop_func.c (DIE 0x239936) */
struct anon_7_128 {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
};

/* anon_4_128 -- @anon4, 0x10 bytes, shop_func.c (DIE 0x238E87) */
struct anon_4_128 {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
};

/* anon_6_128 -- @anon6, 0x10 bytes, shop_func.c (DIE 0x239830) */
struct anon_6_128 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
};

/* anon_11_128 -- @anon11, 0x10 bytes, shop_func.c (DIE 0x23AA44) */
struct anon_11_128 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
};

/* anon_13_128 -- @anon13, 0x14 bytes, shop_func.c (DIE 0x23AD66) */
struct anon_13_128 {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
};

/* anon_5_128 -- @anon5, 0x8 bytes, shop_func.c (DIE 0x2397AB) */
struct anon_5_128 {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
};

/* anon_3_128 -- @anon3, 0x14 bytes, shop_func.c (DIE 0x23892C) */
struct anon_3_128 {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
};

/* anon_1_128 -- @anon1, 0x518 bytes, shop_func.c (DIE 0x237707) */
struct anon_1_128 {   // size 0x518
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
    /* 0x234 */ struct anon_7_128 secret_list[50];    // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ struct anon_4_128 text_w;             // 0x10
    /* 0x310 */ struct anon_6_128 button_disp_w;      // 0x10
    /* 0x320 */ struct anon_11_128 fade_env;          // 0x10
    /* 0x330 */ struct anon_13_128 pad_w;             // 0x14
    /* 0x344 */ struct anon_5_128 mess_w;             // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ struct anon_3_128 move_w[9];          // 0xB4
    /* 0x510 */ struct anon_0_128 shop_rect;          // 0x8
};

/* anon_2_128 -- @anon2, 0x4 bytes, shop_func.c (DIE 0x237E1A) */
struct anon_2_128 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_8_128 -- @anon8, 0xD40 bytes, shop_func.c (DIE 0x23A26B) */
struct anon_8_128 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_9_128 -- @anon9, 0x14 bytes, shop_func.c (DIE 0x23A6C3) */
struct anon_9_128 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_10_128 -- @anon10, 0xC bytes, shop_func.c (DIE 0x23A921) */
struct anon_10_128 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_12_128 -- @anon12, 0x1300 bytes, shop_func.c (DIE 0x23AB97) */
struct anon_12_128 {   // size 0x1300
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
    /* 0x360 */ struct anon_9_128 subject[200];       // 0xFA0
};

/* anon_15_128 -- @anon15, 0x4 bytes, shop_func.c (DIE 0x23AEB2) */
struct anon_15_128 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_14_128 -- @anon14, 0x4 bytes, shop_func.c (DIE 0x23AE53) */
union anon_14_128 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_15_128 s;                 // 0x4
};

/* anon_16_128 -- @anon16, 0x12E0 bytes, shop_func.c (DIE 0x23B108) */
struct anon_16_128 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_10_128 history[400];      // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_17_128 -- @anon17, 0x2134 bytes, shop_func.c (DIE 0x23B317) */
struct anon_17_128 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_14_128 userpass;           // 0x4
    /* 0x008 */ struct anon_16_128 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_8_128 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};


/* variables (1) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (19) */
void shop_bgm_set(unsigned int call);                            /* 0x00253AE0-0x00253B08 lines 511-514 */
void shop_bgm_call(void);                                        /* 0x00253B10-0x00253B70 lines 496-507 */
void shop_bgm_init(void);                                        /* 0x00253B70-0x00253B98 lines 484-490 */
void shop_multi_win_destroy(struct anon_1_128 *work);            /* 0x00253BA0-0x00253BE8 lines 450-458 */
void shop_multi_win_init(struct anon_1_128 *work);               /* 0x00253BF0-0x00253C5C lines 408-441 */
void shop_bind_nm(void);                                         /* 0x00253C60-0x00253D20 lines 350-386 */
void shop_bind_tex(void);                                        /* 0x00253D20-0x00253E70 lines 282-323 */
int shop_wait_obj_move(struct anon_1_128 *work, int obj_kind);   /* 0x00253E70-0x00253EA8 lines 250-255 */
int shop_get_obj_frame(struct anon_1_128 *work, int obj_kind);   /* 0x00253EB0-0x00253EC8 lines 244-245 */
int shop_get_obj_count(struct anon_1_128 *work, int obj_kind);   /* 0x00253ED0-0x00253EF0 lines 238-239 */
void shop_set_obj_move(struct anon_1_128 *work, int obj_kind, int type, int frame); /* 0x00253EF0-0x00253F14 lines 229-233 */
int shop_init_obj_move_work(struct anon_1_128 *work);            /* 0x00253F20-0x00253F84 lines 212-219 */
int shop_get_secret_value(struct anon_1_128 *work, int list_no); /* 0x00253F90-0x00253FA0 lines 151-152 */
int shop_get_secret_no(struct anon_1_128 *work, int list_no);    /* 0x00253FA0-0x00253FB0 lines 137-138 */
int shop_get_disp_num(struct anon_1_128 *work);                  /* 0x00253FB0-0x00254018 lines 103-124 */
int shop_get_contents_num(struct anon_1_128 *work);              /* 0x00254020-0x00254028 lines 98-98 */
void shop_purchase(struct anon_1_128 *work);                     /* 0x00254030-0x00254134 lines 60-74 */
int shop_is_purchasable2(struct anon_1_128 *work, int list_no);  /* 0x00254140-0x002541DC lines 42-52 */
int shop_is_purchasable(struct anon_1_128 *work);                /* 0x002541E0-0x0025427C lines 29-39 */

#endif /* DDR_UNIT_src_CS_shop_shop_func_c_H */
