/*
 * C:\work2\usaex2\src\CS\dancemaster\dmm_event_cond.c
 * MW MIPS C Compiler, overlay dmm_rel4cd.prg; 25 functions, code 0x007F0CC0-0x007F19A8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_dancemaster_dmm_event_cond_c_H
#define DDR_UNIT_src_CS_dancemaster_dmm_event_cond_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/play_mode.h"

/* anonymous types (32) */

/* anon_0_215 -- @anon0, 0x14 bytes, dmm_event_cond.c (DIE 0x3CC272) */
struct anon_0_215 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_29_215 -- @anon29, 0x14 bytes, dmm_event_cond.c (DIE 0x3D4F20) */
struct anon_29_215 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_1_215 -- @anon1, 0x1300 bytes, dmm_event_cond.c (DIE 0x3CC3F8) */
struct anon_1_215 {   // size 0x1300
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
    /* 0x360 */ struct anon_29_215 subject[200];      // 0xFA0
};

/* anon_2_215 -- @anon2, 0x1F0 bytes, dmm_event_cond.c (DIE 0x3CC60E) */
struct anon_2_215 {   // size 0x1F0
    /* 0x000 */ unsigned short total_notes;           // 0x2
    /* 0x002 */ unsigned short total_combo;           // 0x2
    /* 0x004 */ unsigned short dance_level;           // 0x2
    /* 0x006 */ unsigned short fixed_level;           // 0x2
    /* 0x008 */ int max_combo;                        // 0x4
    /* 0x00C */ int cur_combo;                        // 0x4
    /* 0x010 */ unsigned short note[10];              // 0x14
    /* 0x024 */ unsigned short value[6][10];          // 0x78
    /* 0x09C */ unsigned short oldval1[6][10];        // 0x78
    /* 0x114 */ unsigned short oldval2[6][10];        // 0x78
    /* 0x18C */ unsigned short total[6];              // 0xC
    /* 0x198 */ unsigned short values[6];             // 0xC
    /* 0x1A4 */ unsigned short beatval[6][4];         // 0x30
    /* 0x1D4 */ unsigned short freeze[3];             // 0x6
    /* 0x1DA */ unsigned short old_freeze[3];         // 0x6
    /* 0x1E0 */ unsigned short freeze_total;          // 0x2
    /* 0x1E2 */ unsigned short cur_note;              // 0x2
    /* 0x1E4 */ short cur_point;                      // 0x2
    /* 0x1E6 */ // 0x2 bytes padding
    /* 0x1E8 */ unsigned int score;                   // 0x4
    /* 0x1EC */ unsigned int align;                   // 0x4
};

/* anon_5_215 -- @anon5, 0x4 bytes, dmm_event_cond.c (DIE 0x3CCB69) */
struct anon_5_215 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_3_215 -- @anon3, 0x4 bytes, dmm_event_cond.c (DIE 0x3CC969) */
union anon_3_215 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_5_215 s;                  // 0x4
};

/* anon_30_215 -- @anon30, 0xC bytes, dmm_event_cond.c (DIE 0x3D51C7) */
struct anon_30_215 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_4_215 -- @anon4, 0x12E0 bytes, dmm_event_cond.c (DIE 0x3CC9EB) */
struct anon_4_215 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_30_215 history[400];      // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_25_215 -- @anon25, 0x38 bytes, dmm_event_cond.c (DIE 0x3D3AD1) */
struct anon_25_215 {   // size 0x38
    /* 0x000 */ int disp_win;                         // 0x4
    /* 0x004 */ int msg_id;                           // 0x4
    /* 0x008 */ int step;                             // 0x4
    /* 0x00C */ int swap_fg;                          // 0x4
    /* 0x010 */ int next_step;                        // 0x4
    /* 0x014 */ int stop_mode;                        // 0x4
    /* 0x018 */ unsigned int address;                 // 0x4
    /* 0x01C */ void *handle;                         // 0x4
    /* 0x020 */ int status;                           // 0x4
    /* 0x024 */ int old_status;                       // 0x4
    /* 0x028 */ int trg_status;                       // 0x4
    /* 0x02C */ int yesno_step;                       // 0x4
    /* 0x030 */ int ok_step;                          // 0x4
    /* 0x034 */ int is_done_ok;                       // 0x4
};

/* anon_14_215 -- @anon14, 0x10 bytes, dmm_event_cond.c (DIE 0x3D04FC) */
struct anon_14_215 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
};

/* anon_16_215 -- @anon16, 0x28 bytes, dmm_event_cond.c (DIE 0x3D1428) */
struct anon_16_215 {   // size 0x28
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float timer;                          // 0x4
    /* 0x008 */ float ox;                             // 0x4
    /* 0x00C */ float oy;                             // 0x4
    /* 0x010 */ float dstx;                           // 0x4
    /* 0x014 */ float dsty;                           // 0x4
    /* 0x018 */ float spdx;                           // 0x4
    /* 0x01C */ float spdy;                           // 0x4
    /* 0x020 */ int all_clear;                        // 0x4
    /* 0x024 */ int all_perfect;                      // 0x4
};

/* anon_17_215 -- @anon17, 0x10 bytes, dmm_event_cond.c (DIE 0x3D167B) */
struct anon_17_215 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
};

/* anon_13_215 -- @anon13, 0x1C bytes, dmm_event_cond.c (DIE 0x3D0319) */
struct anon_13_215 {   // size 0x1C
    /* 0x000 */ unsigned short note[10];              // 0x14
    /* 0x014 */ unsigned short total_notes;           // 0x2
    /* 0x016 */ unsigned short total_combo;           // 0x2
    /* 0x018 */ unsigned int align;                   // 0x4
};

/* anon_20_215 -- @anon20, 0x4 bytes, dmm_event_cond.c (DIE 0x3D1DAD) */
struct anon_20_215 {   // size 0x4
    /* 0x000 */ int cursor;                           // 0x4
};

/* anon_19_215 -- @anon19, 0x10 bytes, dmm_event_cond.c (DIE 0x3D1BC4) */
struct anon_19_215 {   // size 0x10
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int decide;                           // 0x4
    /* 0x00C */ int cancel;                           // 0x4
};

/* anon_7_215 -- @anon7, 0x10 bytes, dmm_event_cond.c (DIE 0x3CE25F) */
struct anon_7_215 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int x;                                // 0x4
    /* 0x00C */ int y;                                // 0x4
};

/* anon_21_215 -- @anon21, 0xC bytes, dmm_event_cond.c (DIE 0x3D1E3C) */
struct anon_21_215 {   // size 0xC
    /* 0x000 */ int no;                               // 0x4
    /* 0x004 */ int contents_id;                      // 0x4
    /* 0x008 */ int (*func)();                        // 0x4
};

/* anon_22_215 -- @anon22, 0x1AC bytes, dmm_event_cond.c (DIE 0x3D20B9) */
struct anon_22_215 {   // size 0x1AC
    /* 0x000 */ int event_flag;                       // 0x4
    /* 0x004 */ int cur_no;                           // 0x4
    /* 0x008 */ int num;                              // 0x4
    /* 0x00C */ int step;                             // 0x4
    /* 0x010 */ int step1;                            // 0x4
    /* 0x014 */ int step2;                            // 0x4
    /* 0x018 */ int step3;                            // 0x4
    /* 0x01C */ int count;                            // 0x4
    /* 0x020 */ int anime_count;                      // 0x4
    /* 0x024 */ int logo_count;                       // 0x4
    /* 0x028 */ unsigned char fade_in_flag;           // 0x1
    /* 0x029 */ unsigned char fade_out_flag;          // 0x1
    /* 0x02A */ unsigned char shop_info_flag;         // 0x1
    /* 0x02B */ char pad;                             // 0x1
    /* 0x02C */ struct anon_21_215 exe_w[32];         // 0x180
};

/* anon_31_215 -- @anon31, 0x14 bytes, dmm_event_cond.c (DIE 0x3D5332) */
struct anon_31_215 {   // size 0x14
    /* 0x000 */ int flag;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step_s;                           // 0x4
    /* 0x00C */ int shop_mode_flag;                   // 0x4
    /* 0x010 */ int yesno;                            // 0x4
};

/* anon_26_215 -- @anon26, 0x10 bytes, dmm_event_cond.c (DIE 0x3D49EF) */
struct anon_26_215 {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int count;                            // 0x4
    /* 0x00C */ signed char dir[2];                   // 0x2
    /* 0x00E */ signed char pading[2];                // 0x2
};

/* anon_9_215 -- @anon9, 0xC bytes, dmm_event_cond.c (DIE 0x3CEA33) */
struct anon_9_215 {   // size 0xC
    /* 0x000 */ int sbj_id;                           // 0x4
    /* 0x004 */ unsigned int bar_start;               // 0x4
    /* 0x008 */ unsigned int bar_end;                 // 0x4
};

/* anon_10_215 -- @anon10, 0x28 bytes, dmm_event_cond.c (DIE 0x3CF367) */
struct anon_10_215 {   // size 0x28
    /* 0x000 */ int disp_flag;                        // 0x4
    /* 0x004 */ int sbj_no;                           // 0x4
    /* 0x008 */ int state;                            // 0x4
    /* 0x00C */ int z;                                // 0x4
    /* 0x010 */ int u;                                // 0x4
    /* 0x014 */ int v;                                // 0x4
    /* 0x018 */ int r;                                // 0x4
    /* 0x01C */ int g;                                // 0x4
    /* 0x020 */ int b;                                // 0x4
    /* 0x024 */ int a;                                // 0x4
};

/* anon_12_215 -- @anon12, 0xC bytes, dmm_event_cond.c (DIE 0x3D0041) */
struct anon_12_215 {   // size 0xC
    /* 0x000 */ unsigned char disp_flag;              // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ int tex_id;                           // 0x4
    /* 0x008 */ int a;                                // 0x4
};

/* anon_15_215 -- @anon15, 0x14 bytes, dmm_event_cond.c (DIE 0x3D0A34) */
struct anon_15_215 {   // size 0x14
    /* 0x000 */ int disp_flag;                        // 0x4
    /* 0x004 */ float timer;                          // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ int a;                                // 0x4
};

/* anon_6_215 -- @anon6, 0x3D7C bytes, dmm_event_cond.c (DIE 0x3CCF12) */
struct anon_6_215 {   // size 0x3D7C
    /* 0x000 */ unsigned char *free_mem_addr;         // 0x4
    /* 0x004 */ unsigned char *tex_bind_addr;         // 0x4
    /* 0x008 */ unsigned char *mess_data_addr;        // 0x4
    /* 0x00C */ unsigned char *chara_work_addr;       // 0x4
    /* 0x010 */ void *chara_data_addr;                // 0x4
    /* 0x014 */ unsigned char *result_work_addr;      // 0x4
    /* 0x018 */ unsigned int syscnt;                  // 0x4
    /* 0x01C */ unsigned int syscnt0;                 // 0x4
    /* 0x020 */ unsigned int syscnt1;                 // 0x4
    /* 0x024 */ unsigned char step;                   // 0x1
    /* 0x025 */ unsigned char step_s;                 // 0x1
    /* 0x026 */ unsigned char music_load_step;        // 0x1
    /* 0x027 */ signed char is_disp_dancer;           // 0x1
    /* 0x028 */ signed char is_disp_movie;            // 0x1
    /* 0x029 */ signed char is_shop_info_disp;        // 0x1
    /* 0x02A */ signed char is_area_disp;             // 0x1
    /* 0x02B */ unsigned char is_retry;               // 0x1
    /* 0x02C */ unsigned char is_retry_sel;           // 0x1
    /* 0x02D */ char pad[1];                          // 0x1
    /* 0x02E */ signed char start_pid_first;          // 0x1
    /* 0x02F */ signed char start_pid;                // 0x1
    /* 0x030 */ unsigned int sel_light_cnt;           // 0x4
    /* 0x034 */ unsigned int cha_light_cnt;           // 0x4
    /* 0x038 */ unsigned int before_state;            // 0x4
    /* 0x03C */ int subject_id;                       // 0x4
    /* 0x040 */ int next_cursor;                      // 0x4
    /* 0x044 */ int old_cursor;                       // 0x4
    /* 0x048 */ int sel_cursor;                       // 0x4
    /* 0x04C */ int sel_old_cursor;                   // 0x4
    /* 0x050 */ int sel_cursor_disp;                  // 0x4
    /* 0x054 */ int sel_cursor_dir;                   // 0x4
    /* 0x058 */ int route_no;                         // 0x4
    /* 0x05C */ unsigned char string[256];            // 0x100
    /* 0x15C */ int is_sp_score;                      // 0x4
    /* 0x160 */ int sp_score[2];                      // 0x8
    /* 0x168 */ int max_bar[76];                      // 0x130
    /* 0x298 */ float zoom;                           // 0x4
    /* 0x29C */ float timer;                          // 0x4
    /* 0x2A0 */ struct anon_1_215 swap_save_data;     // 0x1300
    /* 0x15A0 */ struct anon_25_215 mc_w;             // 0x38
    /* 0x15D8 */ struct anon_14_215 button_disp_w;    // 0x10
    /* 0x15E8 */ struct anon_16_215 record_w;         // 0x28
    /* 0x1610 */ struct anon_17_215 fade_env;         // 0x10
    /* 0x1620 */ int total_record[4];                 // 0x10
    /* 0x1630 */ struct anon_13_215 preres[2];        // 0x38
    /* 0x1668 */ struct anon_2_215 result[2];         // 0x3E0
    /* 0x1A48 */ unsigned short cur_note[2];          // 0x4
    /* 0x1A4C */ short old_point[2];                  // 0x4
    /* 0x1A50 */ unsigned int subj_opt;               // 0x4
    /* 0x1A54 */ struct anon_20_215 style_menu;       // 0x4
    /* 0x1A58 */ struct anon_19_215 pad_w;            // 0x10
    /* 0x1A68 */ struct anon_7_215 move_w[6];         // 0x60
    /* 0x1AC8 */ struct anon_22_215 ev_w;             // 0x1AC
    /* 0x1C74 */ struct anon_31_215 qmenu_w;          // 0x14
    /* 0x1C88 */ unsigned char is_chart_disp;         // 0x1
    /* 0x1C89 */ unsigned char is_cursor_disp;        // 0x1
    /* 0x1C8A */ unsigned char is_grid_disp;          // 0x1
    /* 0x1C8B */ char is_pad;                         // 0x1
    /* 0x1C8C */ int dancer[2];                       // 0x8
    /* 0x1C94 */ int chart_alpha;                     // 0x4
    /* 0x1C98 */ int disp_ofsx;                       // 0x4
    /* 0x1C9C */ int disp_ofsy;                       // 0x4
    /* 0x1CA0 */ int cursor_x;                        // 0x4
    /* 0x1CA4 */ int cursor_y;                        // 0x4
    /* 0x1CA8 */ int world_posx;                      // 0x4
    /* 0x1CAC */ int world_posy;                      // 0x4
    /* 0x1CB0 */ int world_posx1;                     // 0x4
    /* 0x1CB4 */ int world_posy1;                     // 0x4
    /* 0x1CB8 */ int world_movex;                     // 0x4
    /* 0x1CBC */ int world_movey;                     // 0x4
    /* 0x1CC0 */ int world_posx_max[2];               // 0x8
    /* 0x1CC8 */ int world_posy_max[2];               // 0x8
    /* 0x1CD0 */ struct anon_26_215 worldw;           // 0x10
    /* 0x1CE0 */ struct anon_9_215 cha_sbj_info_w;    // 0xC
    /* 0x1CEC */ struct anon_9_215 sel_sbj_info_w[8];  // 0x60
    /* 0x1D4C */ struct anon_10_215 panel_disp_w[200];  // 0x1F40
    /* 0x3C8C */ struct anon_12_215 cone_disp_w[8];   // 0x60
    /* 0x3CEC */ unsigned int cur_track;              // 0x4
    /* 0x3CF0 */ unsigned int reserve_track;          // 0x4
    /* 0x3CF4 */ int track_delay_time;                // 0x4
    /* 0x3CF8 */ short music_num;                     // 0x2
    /* 0x3CFA */ // 0x2 bytes padding
    /* 0x3CFC */ int loaded_music_num;                // 0x4
    /* 0x3D00 */ unsigned int play_option;            // 0x4
    /* 0x3D04 */ unsigned char life_mode;             // 0x1
    /* 0x3D05 */ unsigned char seq_number;            // 0x1
    /* 0x3D06 */ unsigned char seq_kind;              // 0x1
    /* 0x3D07 */ unsigned char shuffle;               // 0x1
    /* 0x3D08 */ unsigned char use_marvelous;         // 0x1
    /* 0x3D09 */ // 0x3 bytes padding
    /* 0x3D0C */ struct play_mode play_mode;          // 0xC
    /* 0x3D18 */ unsigned int bar_start;              // 0x4
    /* 0x3D1C */ unsigned int bar_end;                // 0x4
    /* 0x3D20 */ unsigned int adjust_bc;              // 0x4
    /* 0x3D24 */ int bar_start_load;                  // 0x4
    /* 0x3D28 */ int note_start_bc;                   // 0x4
    /* 0x3D2C */ int note_end_bc;                     // 0x4
    /* 0x3D30 */ float music_speed;                   // 0x4
    /* 0x3D34 */ unsigned char bar_max;               // 0x1
    /* 0x3D35 */ unsigned char assist;                // 0x1
    /* 0x3D36 */ unsigned char rest_num[2];           // 0x2
    /* 0x3D38 */ unsigned char pass_flg[2];           // 0x2
    /* 0x3D3A */ unsigned char congra_flg;            // 0x1
    /* 0x3D3B */ unsigned char vs_result;             // 0x1
    /* 0x3D3C */ unsigned char force_exit_ct[2];      // 0x2
    /* 0x3D3E */ unsigned char is_force_exit;         // 0x1
    /* 0x3D3F */ unsigned char step_mark_color;       // 0x1
    /* 0x3D40 */ unsigned char arrow_pos_pattern;     // 0x1
    /* 0x3D41 */ unsigned char music_no_play;         // 0x1
    /* 0x3D42 */ unsigned char use_blind_plate;       // 0x1
    /* 0x3D43 */ unsigned char chng_mspd_id;          // 0x1
    /* 0x3D44 */ unsigned char undead_flag;           // 0x1
    /* 0x3D45 */ char pad2[3];                        // 0x3
    /* 0x3D48 */ int gauge_sub;                       // 0x4
    /* 0x3D4C */ int strictness;                      // 0x4
    /* 0x3D50 */ int game_time;                       // 0x4
    /* 0x3D54 */ struct anon_15_215 blind_w;          // 0x14
    /* 0x3D68 */ int result_state;                    // 0x4
    /* 0x3D6C */ int result_cnt;                      // 0x4
    /* 0x3D70 */ int total_result_cnt;                // 0x4
    /* 0x3D74 */ int result_mask_cnt;                 // 0x4
    /* 0x3D78 */ int dummy;                           // 0x4
};

/* anon_27_215 -- @anon27, 0xD40 bytes, dmm_event_cond.c (DIE 0x3D4ADE) */
struct anon_27_215 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_8_215 -- @anon8, 0x2134 bytes, dmm_event_cond.c (DIE 0x3CE775) */
struct anon_8_215 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_3_215 userpass;            // 0x4
    /* 0x008 */ struct anon_4_215 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_27_215 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_11_215 -- @anon11, 0x4 bytes, dmm_event_cond.c (DIE 0x3CF530) */
struct anon_11_215 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_18_215 -- @anon18, 0x4 bytes, dmm_event_cond.c (DIE 0x3D1A7F) */
struct anon_18_215 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_24_215 -- @anon24, 0x4 bytes, dmm_event_cond.c (DIE 0x3D3A4F) */
union anon_24_215 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_28_215 -- @anon28, 0x10 bytes, dmm_event_cond.c (DIE 0x3D4BB6) */
struct anon_28_215 {   // size 0x10
    /* 0x000 */ union anon_24_215 x0;                 // 0x4
    /* 0x004 */ union anon_24_215 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_23_215 -- @anon23, 0x184 bytes, dmm_event_cond.c (DIE 0x3D24AD) */
struct anon_23_215 {   // size 0x184
    /* 0x000 */ struct anon_28_215 line_a[8];         // 0x80
    /* 0x080 */ struct anon_28_215 line_b[8];         // 0x80
    /* 0x100 */ struct anon_28_215 line_c[8];         // 0x80
    /* 0x180 */ int num;                              // 0x4
};


/* variables (2) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (25) */
int _dmm_evboot_func_sp_cone01(void);                            /* 0x007F0CC0-0x007F0CC8 lines 722-722 */
int _dmm_evboot_func_sp_cone00(void);                            /* 0x007F0CD0-0x007F0D4C lines 695-712 */
int _dmm_evboot_func_info_chart(int chance);                     /* 0x007F0D50-0x007F0DB0 lines 669-683 */
int _dmm_evboot_func_info_shop(void);                            /* 0x007F0DB0-0x007F0DE8 lines 597-661 */
int _dmm_evboot_func_lastboss(int chance);                       /* 0x007F0DF0-0x007F0E50 lines 568-582 */
int _dmm_evboot_func_area05(int chance);                         /* 0x007F0E50-0x007F0EB0 lines 546-560 */
int _dmm_evboot_func_area04(int chance);                         /* 0x007F0EB0-0x007F0F10 lines 524-538 */
int _dmm_evboot_func_area03(int chance);                         /* 0x007F0F10-0x007F0F70 lines 502-516 */
int _dmm_evboot_func_area02(int chance);                         /* 0x007F0F70-0x007F0FD0 lines 473-494 */
int _dmm_evboot_func_ending_last(int chance);                    /* 0x007F0FD0-0x007F1048 lines 444-461 */
int _dmm_evboot_func_ending_E01(int chance);                     /* 0x007F1050-0x007F10E8 lines 416-437 */
int _dmm_evboot_func_ending_D03(int chance);                     /* 0x007F10F0-0x007F1188 lines 388-409 */
int _dmm_evboot_func_ending_D02(int chance);                     /* 0x007F1190-0x007F1228 lines 360-381 */
int _dmm_evboot_func_ending_D01(int chance);                     /* 0x007F1230-0x007F12C8 lines 332-353 */
int _dmm_evboot_func_ending_C04(int chance);                     /* 0x007F12D0-0x007F1368 lines 304-325 */
int _dmm_evboot_func_ending_C03(int chance);                     /* 0x007F1370-0x007F1408 lines 276-297 */
int _dmm_evboot_func_ending_C02(int chance);                     /* 0x007F1410-0x007F14A8 lines 248-269 */
int _dmm_evboot_func_ending_C01(int chance);                     /* 0x007F14B0-0x007F1548 lines 220-241 */
int _dmm_evboot_func_ending_B05(int chance);                     /* 0x007F1550-0x007F15E8 lines 192-213 */
int _dmm_evboot_func_ending_B04(int chance);                     /* 0x007F15F0-0x007F1688 lines 164-185 */
int _dmm_evboot_func_ending_B03(int chance);                     /* 0x007F1690-0x007F1728 lines 136-157 */
int _dmm_evboot_func_ending_B02(int chance);                     /* 0x007F1730-0x007F17C8 lines 108-129 */
int _dmm_evboot_func_ending_B01(int chance);                     /* 0x007F17D0-0x007F1868 lines 80-101 */
int _dmm_evboot_func_ending_A02(int chance);                     /* 0x007F1870-0x007F1908 lines 52-73 */
int _dmm_evboot_func_ending_A01(int chance);                     /* 0x007F1910-0x007F19A8 lines 23-45 */

#endif /* DDR_UNIT_src_CS_dancemaster_dmm_event_cond_c_H */
