/*
 * C:\work2\usaex2\src\AM\s573\play\onimode.c
 * MW MIPS C Compiler, overlay main; 34 functions, code 0x001B3D90-0x001B78F4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_play_onimode_c_H
#define DDR_UNIT_src_AM_s573_play_onimode_c_H

#include "types/_tag_cDDR8OniRecord1.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_cource_work.h"
#include "types/oni_course.h"
#include "types/oni_mode.h"
#include "types/play_mode.h"
#include "types/sequence.h"

/* anonymous types (15) */

/* anon_0_3 -- @anon0, 0x4 bytes, onimode.c (DIE 0x51A6) */
struct anon_0_3 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_1_3 -- @anon1, 0x4 bytes, onimode.c (DIE 0x5891) */
union anon_1_3 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_2_3 -- @anon2, 0xD40 bytes, onimode.c (DIE 0x59A4) */
struct anon_2_3 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_4_3 -- @anon4, 0x10 bytes, onimode.c (DIE 0x5D50) */
struct anon_4_3 {   // size 0x10
    /* 0x000 */ union anon_1_3 x0;                    // 0x4
    /* 0x004 */ union anon_1_3 y0;                    // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_3_3 -- @anon3, 0x184 bytes, onimode.c (DIE 0x5C7C) */
struct anon_3_3 {   // size 0x184
    /* 0x000 */ struct anon_4_3 line_a[8];            // 0x80
    /* 0x080 */ struct anon_4_3 line_b[8];            // 0x80
    /* 0x100 */ struct anon_4_3 line_c[8];            // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_5_3 -- @anon5, 0x14 bytes, onimode.c (DIE 0x5F89) */
struct anon_5_3 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_6_3 -- @anon6, 0xC bytes, onimode.c (DIE 0x629F) */
struct anon_6_3 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_7_3 -- @anon7, 0x1300 bytes, onimode.c (DIE 0x7ED0) */
struct anon_7_3 {   // size 0x1300
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
    /* 0x360 */ struct anon_5_3 subject[200];         // 0xFA0
};

/* anon_9_3 -- @anon9, 0x4 bytes, onimode.c (DIE 0x81B5) */
struct anon_9_3 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_8_3 -- @anon8, 0x4 bytes, onimode.c (DIE 0x80E6) */
union anon_8_3 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_9_3 s;                    // 0x4
};

/* anon_10_3 -- @anon10, 0x12E0 bytes, onimode.c (DIE 0x823C) */
struct anon_10_3 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_6_3 history[400];         // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_11_3 -- @anon11, 0x2134 bytes, onimode.c (DIE 0x84DD) */
struct anon_11_3 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_8_3 userpass;              // 0x4
    /* 0x008 */ struct anon_10_3 pwork;               // 0x12E0
    /* 0x12E8 */ struct anon_2_3 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_12_3 -- @anon12, 0x8 bytes, onimode.c (DIE 0x86C0) */
struct anon_12_3 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};

/* anon_13_3 -- @anon13, 0x4 bytes, onimode.c (DIE 0x8889) */
struct anon_13_3 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_14_3 -- @anon14, 0x14 bytes, onimode.c (DIE 0x893F) */
struct anon_14_3 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};


/* variables (8) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct oni_cource_work *oni_w;                                   /* @0x002DE490 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct oni_course course_list[];                                 /* @0x002AFD40 */
struct anon_12_3 course_n_bin[];                                 /* not allocated */
struct anon_12_3 course_d_bin[];                                 /* not allocated */
struct oni_cource_work oni_work;                                 /* @0x0070FC60 size 0xCC */
struct oni_course playing_course_work;                           /* @0x0070FB50 size 0x10C */

/* functions defined (34) */
void setup_nonstop_option(int pid, int stage_num);               /* 0x001B3D90-0x001B427C lines 2863-2966 */
struct oni_mode *get_course_list_work(int id, int stage);        /* 0x001B4280-0x001B4300 lines 2850-2857 */
int get_nonstop_best_record(int course, int type);               /* 0x001B4300-0x001B44CC lines 2828-2847 */
int is_option_changed_this_course(int course, int index);        /* 0x001B44D0-0x001B469C lines 2809-2824 */
void set_course_real_stage_num(int id, int stage);               /* 0x001B46A0-0x001B4750 lines 2797-2805 */
int get_course_real_stage_num(int id);                           /* 0x001B4750-0x001B47B8 lines 2781-2793 */
int is_this_course_option_locked(int id);                        /* 0x001B47C0-0x001B4974 lines 2758-2776 */
struct oni_mode *onimode_get_save_course(int id);                /* 0x001B4980-0x001B49F8 lines 2248-2252 */
struct oni_course *onimode_get_save_order(int id);               /* 0x001B4A00-0x001B4A90 lines 2219-2241 */
struct oni_course *onimode_get_course_list(int id);              /* 0x001B4A90-0x001B4AB8 lines 2211-2212 */
void onimode_get_order_mode(int id, int stage_num);              /* 0x001B4AC0-0x001B4D1C lines 2133-2165 */
int onimode_is_course_order(int id);                             /* 0x001B4D20-0x001B4D58 lines 2108-2126 */
void onimode_order_setup(void);                                  /* 0x001B4D60-0x001B5348 lines 1966-2090 */
void onimode_random_setup_patch_for_easy(void);                  /* 0x001B5350-0x001B55A8 lines 1888-1947 */
void onimode_random_setup(void);                                 /* 0x001B55B0-0x001B64A8 lines 1480-1878 */
void onimode_set_linknum(int id, int stage, struct music_info *mip); /* 0x001B64B0-0x001B65D8 lines 1458-1471 */
int onimode_ta_load(int id);                                     /* 0x001B65E0-0x001B6624 lines 1414-1450 */
int onimode_get_real_stage_num(int id);                          /* 0x001B6630-0x001B6698 lines 1380-1393 */
int onimode_get_stage_allnum(int id);                            /* 0x001B66A0-0x001B66F0 lines 1363-1374 */
int onimode_get_stage_num(int id);                               /* 0x001B66F0-0x001B6740 lines 1346-1357 */
int onimode_set_playmode(int stage_num, int mode);               /* 0x001B6740-0x001B6898 lines 1261-1338 */
int onimode_get_add_life(int stage_num);                         /* 0x001B68A0-0x001B6910 lines 1170-1193 */
void onimode_set_seqkind(int id, int stage_num, int kind);       /* 0x001B6910-0x001B6A58 lines 1139-1164 */
int onimode_get_seqkind(int stage_num, int mode);                /* 0x001B6A60-0x001B6B08 lines 1072-1101 */
void onimode_set_course_difficulty(int id, int mode);            /* 0x001B6B10-0x001B6EB0 lines 994-1066 */
struct music_info *onimode_get_disp_mip(int id, int stage_num);  /* 0x001B6EB0-0x001B6F7C lines 860-891 */
struct music_info *onimode_get_mip(int stage_num);               /* 0x001B6F80-0x001B705C lines 832-857 */
int onimode_get_steps(int style);                                /* 0x001B7060-0x001B70A8 lines 815-828 */
void onimode_set_steps(void);                                    /* 0x001B70B0-0x001B7468 lines 759-809 */
int onimode_get_start_life(void);                                /* 0x001B7470-0x001B74C0 lines 721-738 */
int onimode_get_irid(int id, int mode);                          /* 0x001B74C0-0x001B7510 lines 607-625 */
int onimode_course_load(int id);                                 /* 0x001B7510-0x001B77C4 lines 298-362 */
int onimode_is_course_data(int id);                              /* 0x001B77D0-0x001B7810 lines 240-251 */
void onimode_boot(void);                                         /* 0x001B7810-0x001B78F4 lines 171-231 */

#endif /* DDR_UNIT_src_AM_s573_play_onimode_c_H */
