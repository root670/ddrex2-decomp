/*
 * C:\work2\usaex2\src\CS\workout\workout_setting.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 20 functions, code 0x007F0080-0x007F25B0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_setting_c_H
#define DDR_UNIT_src_CS_workout_workout_setting_c_H

#include "types/oni_course.h"

/* anonymous types (20) */

/* anon_0_233 -- @anon0, 0x1C bytes, workout_setting.c (DIE 0x452A2A) */
struct anon_0_233 {   // size 0x1C
    /* 0x000 */ int func_no[2];                       // 0x8
    /* 0x008 */ int func_step[2];                     // 0x8
    /* 0x010 */ int step;                             // 0x4
    /* 0x014 */ int f_back_to_workout_list;           // 0x4
    /* 0x018 */ int f_back_to_workout_menu;           // 0x4
};

/* anon_1_233 -- @anon1, 0xC bytes, workout_setting.c (DIE 0x452B66) */
struct anon_1_233 {   // size 0xC
    /* 0x000 */ struct anon_3_233 *step_array;        // 0x4
    /* 0x004 */ void (*screen)(int);                  // 0x4
    /* 0x008 */ int step_idx;                         // 0x4
};

/* anon_18_233 -- @anon18, 0x4 bytes, workout_setting.c (DIE 0x4547B7) */
struct anon_18_233 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_17_233 -- @anon17, 0x4 bytes, workout_setting.c (DIE 0x454758) */
union anon_17_233 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_18_233 s;                 // 0x4
};

/* anon_11_233 -- @anon11, 0xC bytes, workout_setting.c (DIE 0x453D7D) */
struct anon_11_233 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_14_233 -- @anon14, 0x12E0 bytes, workout_setting.c (DIE 0x454140) */
struct anon_14_233 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_11_233 history[400];      // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_15_233 -- @anon15, 0xD40 bytes, workout_setting.c (DIE 0x4544F7) */
struct anon_15_233 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_2_233 -- @anon2, 0x2134 bytes, workout_setting.c (DIE 0x452BFE) */
struct anon_2_233 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_17_233 userpass;           // 0x4
    /* 0x008 */ struct anon_14_233 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_15_233 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_3_233 -- @anon3, 0x4 bytes, workout_setting.c (DIE 0x452DE0) */
struct anon_3_233 {   // size 0x4
    /* 0x000 */ struct anon_16_233 (*step_func)();    // 0x4
};

/* anon_4_233 -- @anon4, 0x2C bytes, workout_setting.c (DIE 0x452E2A) */
struct anon_4_233 {   // size 0x2C
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ int status;                           // 0x4
    /* 0x008 */ int weight_mask;                      // 0x4
    /* 0x00C */ int cur_item;                         // 0x4
    /* 0x010 */ int repeat_count;                     // 0x4
    /* 0x014 */ int repeat_key;                       // 0x4
    /* 0x018 */ int val_change_left;                  // 0x4
    /* 0x01C */ int val_change_right;                 // 0x4
    /* 0x020 */ int cursor_alpha;                     // 0x4
    /* 0x024 */ int step;                             // 0x4
    /* 0x028 */ int func;                             // 0x4
};

/* anon_5_233 -- @anon5, 0x48 bytes, workout_setting.c (DIE 0x452FEF) */
struct anon_5_233 {   // size 0x48
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

/* anon_6_233 -- @anon6, 0xC bytes, workout_setting.c (DIE 0x453271) */
struct anon_6_233 {   // size 0xC
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int counter;                          // 0x4
};

/* anon_7_233 -- @anon7, 0x30 bytes, workout_setting.c (DIE 0x4532F0) */
struct anon_7_233 {   // size 0x30
    /* 0x000 */ int active;                           // 0x4
    /* 0x004 */ int play_time;                        // 0x4
    /* 0x008 */ int calorie;                          // 0x4
    /* 0x00C */ int play_time_per_music;              // 0x4
    /* 0x010 */ int calorie_per_music;                // 0x4
    /* 0x014 */ int play_time_norm;                   // 0x4
    /* 0x018 */ int calorie_norm;                     // 0x4
    /* 0x01C */ int daily_data_index;                 // 0x4
    /* 0x020 */ int workout_data_load_flag;           // 0x4
    /* 0x024 */ int workout_data_change_flag;         // 0x4
    /* 0x028 */ int workout_data_save_flag;           // 0x4
    /* 0x02C */ int music_play_count;                 // 0x4
};

/* anon_12_233 -- @anon12, 0x4 bytes, workout_setting.c (DIE 0x453E7A) */
union anon_12_233 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_8_233 -- @anon8, 0x1C bytes, workout_setting.c (DIE 0x453523) */
struct anon_8_233 {   // size 0x1C
    /* 0x000 */ union anon_12_233 x0;                 // 0x4
    /* 0x004 */ union anon_12_233 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_9_233 -- @anon9, 0x24 bytes, workout_setting.c (DIE 0x453A57) */
struct anon_9_233 {   // size 0x24
    /* 0x000 */ union anon_12_233 x0;                 // 0x4
    /* 0x004 */ union anon_12_233 y0;                 // 0x4
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

/* anon_10_233 -- @anon10, 0x84 bytes, workout_setting.c (DIE 0x453BEB) */
struct anon_10_233 {   // size 0x84
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int result;                           // 0x4
    /* 0x008 */ int date;                             // 0x4
    /* 0x00C */ int not_first;                        // 0x4
    /* 0x010 */ int f_cancel;                         // 0x4
    /* 0x014 */ unsigned int *am_local_dec_addr;      // 0x4
    /* 0x018 */ struct anon_7_233 player[2];          // 0x60
    /* 0x078 */ struct anon_1_233 hstep;              // 0xC
};

/* anon_13_233 -- @anon13, 0x30 bytes, workout_setting.c (DIE 0x453EFE) */
struct anon_13_233 {   // size 0x30
    /* 0x000 */ union anon_12_233 x0;                 // 0x4
    /* 0x004 */ union anon_12_233 y0;                 // 0x4
    /* 0x008 */ union anon_12_233 x1;                 // 0x4
    /* 0x00C */ union anon_12_233 y1;                 // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ float w;                              // 0x4
    /* 0x01C */ float h;                              // 0x4
    /* 0x020 */ float u;                              // 0x4
    /* 0x024 */ float v;                              // 0x4
    /* 0x028 */ unsigned char r0;                     // 0x1
    /* 0x029 */ unsigned char g0;                     // 0x1
    /* 0x02A */ unsigned char b0;                     // 0x1
    /* 0x02B */ unsigned char a0;                     // 0x1
    /* 0x02C */ int flg;                              // 0x4
};

/* anon_16_233 -- @anon16, 0x8 bytes, workout_setting.c (DIE 0x4546F5) */
struct anon_16_233 {   // size 0x8
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int param;                            // 0x4
};

/* anon_19_233 -- @anon19, 0x4 bytes, workout_setting.c (DIE 0x45481B) */
struct anon_19_233 {   // size 0x4
    /* 0x000 */ void (*func)(int);                    // 0x4
};


/* variables (7) */
static int sheet_target_y[7];                                    /* @0x00801180 size 0x1C */
static int sheet_target_h[7];                                    /* @0x008011A0 size 0x1C */
struct anon_19_233 setting_func_list[10];                        /* @0x008011C0 size 0x28 */
struct anon_4_233 wo_setting_work[2];                            /* @0x00801D80 size 0x58 */
struct anon_6_233 wo_setting_sheet[7];                           /* @0x00801D00 size 0x54 */
struct anon_0_233 wo_setting_sheet_ctrl;                         /* @0x00801D60 size 0x1C */
struct anon_10_233 workout_work;                                 /* @0x0071D880 size 0x84 */

/* functions defined (20) */
static int GetKeyRepeat(int player, int key);                    /* 0x007F0080-0x007F021C lines 985-1005 */
static void CheckKeyRepeat(void);                                /* 0x007F0220-0x007F02BC lines 937-969 */
static void wos_step_func_draw_program(int pno);                 /* 0x007F02C0-0x007F03AC lines 889-910 */
static void wos_step_func_draw_simultaneousstep(int pno);        /* 0x007F03B0-0x007F049C lines 866-887 */
static void wos_step_func_draw_workoutstep(int pno);             /* 0x007F04A0-0x007F058C lines 843-865 */
static void wos_step_func_draw_goal(int pno);                    /* 0x007F0590-0x007F065C lines 820-842 */
static void wos_step_func_draw_menu(int pno);                    /* 0x007F0660-0x007F0740 lines 797-819 */
static void woSettingSheetDraw(void);                            /* 0x007F0740-0x007F14EC lines 593-776 */
static void wos_step_func_end_wait(int pno);                     /* 0x007F14F0-0x007F15E4 lines 548-567 */
static void wos_step_func_ok(int pno);                           /* 0x007F15F0-0x007F16BC lines 536-547 */
static void wos_step_func_program(int pno);                      /* 0x007F16C0-0x007F1848 lines 512-535 */
static void wos_step_func_simultaneousstep(int pno);             /* 0x007F1850-0x007F1998 lines 487-510 */
static void wos_step_func_workoutstep(int pno);                  /* 0x007F19A0-0x007F1B04 lines 457-486 */
static void wos_step_func_goal(int pno);                         /* 0x007F1B10-0x007F1C98 lines 423-456 */
static void wos_step_func_menu(int pno);                         /* 0x007F1CA0-0x007F1E10 lines 389-422 */
static void wos_step_func_weight(int pno);                       /* 0x007F1E10-0x007F1FF8 lines 348-388 */
static void wos_step_func_start_wait(int pno);                   /* 0x007F2000-0x007F2074 lines 336-346 */
struct anon_16_233 WorkoutSetting_Term(void);                    /* 0x007F2080-0x007F2104 lines 307-329 */
struct anon_16_233 WorkoutSetting_Main(void);                    /* 0x007F2110-0x007F2538 lines 190-305 */
struct anon_16_233 WorkoutSetting_Init(void);                    /* 0x007F2540-0x007F25B0 lines 179-187 */

#endif /* DDR_UNIT_src_CS_workout_workout_setting_c_H */
