/*
 * C:\work2\usaex2\src\CS\dancemaster\dmm_data.c
 * MW MIPS C Compiler, overlay main; 18 functions, code 0x002293E0-0x00229EDC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_dancemaster_dmm_data_c_H
#define DDR_UNIT_src_CS_dancemaster_dmm_data_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"
#include "types/play_mode.h"

/* anonymous types (33) */

/* anon_0_85 -- @anon0, 0xC bytes, dmm_data.c (DIE 0x17924A) */
struct anon_0_85 {   // size 0xC
    /* 0x000 */ unsigned char disp_flag;              // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ int tex_id;                           // 0x4
    /* 0x008 */ int a;                                // 0x4
};

/* anon_31_85 -- @anon31, 0xC bytes, dmm_data.c (DIE 0x17FC54) */
struct anon_31_85 {   // size 0xC
    /* 0x000 */ int id;                               // 0x4
    /* 0x004 */ int hide;                             // 0x4
    /* 0x008 */ int func_No;                          // 0x4
};

/* anon_13_85 -- @anon13, 0x1C bytes, dmm_data.c (DIE 0x17C9CF) */
struct anon_13_85 {   // size 0x1C
    /* 0x000 */ short music_num;                      // 0x2
    /* 0x002 */ unsigned char seq_number;             // 0x1
    /* 0x003 */ unsigned char seq_kind;               // 0x1
    /* 0x004 */ unsigned int attribute;               // 0x4
    /* 0x008 */ unsigned int data_num;                // 0x4
    /* 0x00C */ unsigned int bar_start;               // 0x4
    /* 0x010 */ unsigned int bar_end;                 // 0x4
    /* 0x014 */ signed char start_life;               // 0x1
    /* 0x015 */ unsigned char difficulty;             // 0x1
    /* 0x016 */ unsigned char perfect_type;           // 0x1
    /* 0x017 */ // 0x1 bytes padding
    /* 0x018 */ unsigned int play_mode;               // 0x4
};

/* anon_1_85 -- @anon1, 0x90 bytes, dmm_data.c (DIE 0x1792F2) */
struct anon_1_85 {   // size 0x90
    /* 0x000 */ struct anon_31_85 connect[8];         // 0x60
    /* 0x060 */ unsigned int area;                    // 0x4
    /* 0x064 */ int pos_x;                            // 0x4
    /* 0x068 */ int pos_y;                            // 0x4
    /* 0x06C */ int hide;                             // 0x4
    /* 0x070 */ int ex_arrow;                         // 0x4
    /* 0x074 */ struct anon_13_85 sbj_data;           // 0x1C
};

/* anon_2_85 -- @anon2, 0x10 bytes, dmm_data.c (DIE 0x17952F) */
struct anon_2_85 {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int parm1;                            // 0x4
    /* 0x008 */ int parm2;                            // 0x4
    /* 0x00C */ int parm3;                            // 0x4
};

/* anon_3_85 -- @anon3, 0x1C bytes, dmm_data.c (DIE 0x179670) */
struct anon_3_85 {   // size 0x1C
    /* 0x000 */ unsigned short note[10];              // 0x14
    /* 0x014 */ unsigned short total_notes;           // 0x2
    /* 0x016 */ unsigned short total_combo;           // 0x2
    /* 0x018 */ unsigned int align;                   // 0x4
};

/* anon_4_85 -- @anon4, 0x10 bytes, dmm_data.c (DIE 0x179748) */
struct anon_4_85 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
};

/* anon_5_85 -- @anon5, 0x4 bytes, dmm_data.c (DIE 0x1797E2) */
struct anon_5_85 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_6_85 -- @anon6, 0x8 bytes, dmm_data.c (DIE 0x1798E1) */
struct anon_6_85 {   // size 0x8
    /* 0x000 */ int beat_count;                       // 0x4
    /* 0x004 */ int dir;                              // 0x4
};

/* anon_7_85 -- @anon7, 0x14 bytes, dmm_data.c (DIE 0x17A0BF) */
struct anon_7_85 {   // size 0x14
    /* 0x000 */ int disp_flag;                        // 0x4
    /* 0x004 */ float timer;                          // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ int a;                                // 0x4
};

/* anon_8_85 -- @anon8, 0xC bytes, dmm_data.c (DIE 0x17A329) */
struct anon_8_85 {   // size 0xC
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ int time;                             // 0x4
    /* 0x008 */ float rate;                           // 0x4
};

/* anon_9_85 -- @anon9, 0x28 bytes, dmm_data.c (DIE 0x17A41D) */
struct anon_9_85 {   // size 0x28
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

/* anon_10_85 -- @anon10, 0x10 bytes, dmm_data.c (DIE 0x17A894) */
struct anon_10_85 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
};

/* anon_11_85 -- @anon11, 0x10 bytes, dmm_data.c (DIE 0x17AD81) */
struct anon_11_85 {   // size 0x10
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int decide;                           // 0x4
    /* 0x00C */ int cancel;                           // 0x4
};

/* anon_22_85 -- @anon22, 0x14 bytes, dmm_data.c (DIE 0x17EB80) */
struct anon_22_85 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_26_85 -- @anon26, 0x1300 bytes, dmm_data.c (DIE 0x17F312) */
struct anon_26_85 {   // size 0x1300
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
    /* 0x360 */ struct anon_22_85 subject[200];       // 0xFA0
};

/* anon_17_85 -- @anon17, 0x38 bytes, dmm_data.c (DIE 0x17D79D) */
struct anon_17_85 {   // size 0x38
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

/* anon_21_85 -- @anon21, 0x1F0 bytes, dmm_data.c (DIE 0x17E824) */
struct anon_21_85 {   // size 0x1F0
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

/* anon_14_85 -- @anon14, 0x4 bytes, dmm_data.c (DIE 0x17CBB9) */
struct anon_14_85 {   // size 0x4
    /* 0x000 */ int cursor;                           // 0x4
};

/* anon_23_85 -- @anon23, 0x10 bytes, dmm_data.c (DIE 0x17EE9D) */
struct anon_23_85 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int x;                                // 0x4
    /* 0x00C */ int y;                                // 0x4
};

/* anon_15_85 -- @anon15, 0xC bytes, dmm_data.c (DIE 0x17CFAF) */
struct anon_15_85 {   // size 0xC
    /* 0x000 */ int no;                               // 0x4
    /* 0x004 */ int contents_id;                      // 0x4
    /* 0x008 */ int (*func)();                        // 0x4
};

/* anon_16_85 -- @anon16, 0x1AC bytes, dmm_data.c (DIE 0x17D0DE) */
struct anon_16_85 {   // size 0x1AC
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
    /* 0x02C */ struct anon_15_85 exe_w[32];          // 0x180
};

/* anon_19_85 -- @anon19, 0x14 bytes, dmm_data.c (DIE 0x17E2AF) */
struct anon_19_85 {   // size 0x14
    /* 0x000 */ int flag;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step_s;                           // 0x4
    /* 0x00C */ int shop_mode_flag;                   // 0x4
    /* 0x010 */ int yesno;                            // 0x4
};

/* anon_18_85 -- @anon18, 0x10 bytes, dmm_data.c (DIE 0x17DACB) */
struct anon_18_85 {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int count;                            // 0x4
    /* 0x00C */ signed char dir[2];                   // 0x2
    /* 0x00E */ signed char pading[2];                // 0x2
};

/* anon_25_85 -- @anon25, 0xC bytes, dmm_data.c (DIE 0x17F1CD) */
struct anon_25_85 {   // size 0xC
    /* 0x000 */ int sbj_id;                           // 0x4
    /* 0x004 */ unsigned int bar_start;               // 0x4
    /* 0x008 */ unsigned int bar_end;                 // 0x4
};

/* anon_27_85 -- @anon27, 0x28 bytes, dmm_data.c (DIE 0x17F59B) */
struct anon_27_85 {   // size 0x28
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

/* anon_12_85 -- @anon12, 0x3D7C bytes, dmm_data.c (DIE 0x17AE25) */
struct anon_12_85 {   // size 0x3D7C
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
    /* 0x2A0 */ struct anon_26_85 swap_save_data;     // 0x1300
    /* 0x15A0 */ struct anon_17_85 mc_w;              // 0x38
    /* 0x15D8 */ struct anon_4_85 button_disp_w;      // 0x10
    /* 0x15E8 */ struct anon_9_85 record_w;           // 0x28
    /* 0x1610 */ struct anon_10_85 fade_env;          // 0x10
    /* 0x1620 */ int total_record[4];                 // 0x10
    /* 0x1630 */ struct anon_3_85 preres[2];          // 0x38
    /* 0x1668 */ struct anon_21_85 result[2];         // 0x3E0
    /* 0x1A48 */ unsigned short cur_note[2];          // 0x4
    /* 0x1A4C */ short old_point[2];                  // 0x4
    /* 0x1A50 */ unsigned int subj_opt;               // 0x4
    /* 0x1A54 */ struct anon_14_85 style_menu;        // 0x4
    /* 0x1A58 */ struct anon_11_85 pad_w;             // 0x10
    /* 0x1A68 */ struct anon_23_85 move_w[6];         // 0x60
    /* 0x1AC8 */ struct anon_16_85 ev_w;              // 0x1AC
    /* 0x1C74 */ struct anon_19_85 qmenu_w;           // 0x14
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
    /* 0x1CD0 */ struct anon_18_85 worldw;            // 0x10
    /* 0x1CE0 */ struct anon_25_85 cha_sbj_info_w;    // 0xC
    /* 0x1CEC */ struct anon_25_85 sel_sbj_info_w[8];  // 0x60
    /* 0x1D4C */ struct anon_27_85 panel_disp_w[200];  // 0x1F40
    /* 0x3C8C */ struct anon_0_85 cone_disp_w[8];     // 0x60
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
    /* 0x3D54 */ struct anon_7_85 blind_w;            // 0x14
    /* 0x3D68 */ int result_state;                    // 0x4
    /* 0x3D6C */ int result_cnt;                      // 0x4
    /* 0x3D70 */ int total_result_cnt;                // 0x4
    /* 0x3D74 */ int result_mask_cnt;                 // 0x4
    /* 0x3D78 */ int dummy;                           // 0x4
};

/* anon_20_85 -- @anon20, 0xD40 bytes, dmm_data.c (DIE 0x17E3EF) */
struct anon_20_85 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_24_85 -- @anon24, 0xC bytes, dmm_data.c (DIE 0x17EFF4) */
struct anon_24_85 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_29_85 -- @anon29, 0x4 bytes, dmm_data.c (DIE 0x17F7A1) */
struct anon_29_85 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_28_85 -- @anon28, 0x4 bytes, dmm_data.c (DIE 0x17F71C) */
union anon_28_85 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_29_85 s;                  // 0x4
};

/* anon_30_85 -- @anon30, 0x12E0 bytes, dmm_data.c (DIE 0x17FA41) */
struct anon_30_85 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_24_85 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_32_85 -- @anon32, 0x2134 bytes, dmm_data.c (DIE 0x17FD8E) */
struct anon_32_85 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_28_85 userpass;            // 0x4
    /* 0x008 */ struct anon_30_85 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_20_85 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};


/* variables (53) */
static struct anon_2_85 Dnon[1];                                 /* @0x002BC810 size 0x10 */
static struct anon_2_85 Dful[2];                                 /* @0x002BC820 size 0x20 */
static struct anon_2_85 Dgre[2];                                 /* @0x002BC840 size 0x20 */
static struct anon_2_85 Dgoo[2];                                 /* @0x002BC860 size 0x20 */
static struct anon_2_85 Doni[3];                                 /* @0x002BC880 size 0x30 */
static struct anon_2_85 Deoni[3];                                /* @0x002BC8B0 size 0x30 */
static struct anon_2_85 Dfok[2];                                 /* @0x002BC8E0 size 0x20 */
static struct anon_2_85 Dfng[2];                                 /* @0x002BC900 size 0x20 */
static struct anon_2_85 Dsc0[2];                                 /* @0x002BC920 size 0x20 */
static struct anon_2_85 Dsc1[2];                                 /* @0x002BC940 size 0x20 */
static struct anon_2_85 Dsc2[2];                                 /* @0x002BC960 size 0x20 */
static struct anon_2_85 Dsc3[2];                                 /* @0x002BC980 size 0x20 */
static struct anon_2_85 Ddl0[2];                                 /* @0x002BC9A0 size 0x20 */
static struct anon_2_85 Ddl1[2];                                 /* @0x002BC9C0 size 0x20 */
static struct anon_2_85 Ddl2[2];                                 /* @0x002BC9E0 size 0x20 */
static struct anon_2_85 Ddi0[2];                                 /* @0x002BCA00 size 0x20 */
static struct anon_2_85 Ddi1[2];                                 /* @0x002BCA20 size 0x20 */
static struct anon_2_85 Ddi1a[3];                                /* @0x002BCA40 size 0x30 */
static struct anon_2_85 Ddi2[3];                                 /* @0x002BCA70 size 0x30 */
static struct anon_2_85 Ddi3[2];                                 /* @0x002BCAA0 size 0x20 */
static struct anon_2_85 Dev0[3];                                 /* @0x002BCAC0 size 0x30 */
static struct anon_2_85 Dev1[2];                                 /* @0x002BCAF0 size 0x20 */
static struct anon_2_85 Dev2[2];                                 /* @0x002BCB10 size 0x20 */
static struct anon_2_85 Dev3[5];                                 /* @0x002BCB30 size 0x50 */
static struct anon_2_85 Dbe0[2];                                 /* @0x002BCB80 size 0x20 */
static struct anon_2_85 Dbe1[2];                                 /* @0x002BCBA0 size 0x20 */
static struct anon_2_85 Dnga[2];                                 /* @0x002BCBC0 size 0x20 */
static struct anon_2_85 Dga0[2];                                 /* @0x002BCBE0 size 0x20 */
static struct anon_2_85 Dga1[2];                                 /* @0x002BCC00 size 0x20 */
static struct anon_2_85 Dga2[4];                                 /* @0x002BCC20 size 0x40 */
static struct anon_2_85 Dga3[3];                                 /* @0x002BCC60 size 0x30 */
static struct anon_2_85 Dga4[2];                                 /* @0x002BCC90 size 0x20 */
static struct anon_2_85 Dcs0[4];                                 /* @0x002BCCB0 size 0x40 */
static struct anon_2_85 Dcs1[4];                                 /* @0x002BCCF0 size 0x40 */
static struct anon_2_85 Dco0[3];                                 /* @0x002BCD30 size 0x30 */
static struct anon_2_85 Dte0[4];                                 /* @0x002BCD60 size 0x40 */
static struct anon_2_85 Dte1[3];                                 /* @0x002BCDA0 size 0x30 */
static struct anon_2_85 Dte2[3];                                 /* @0x002BCDD0 size 0x30 */
static struct anon_2_85 Dc00[3];                                 /* @0x002BCE00 size 0x30 */
static struct anon_2_85 Dc01[4];                                 /* @0x002BCE30 size 0x40 */
static struct anon_2_85 Dc01a[4];                                /* @0x002BCE70 size 0x40 */
static struct anon_2_85 Dc02[4];                                 /* @0x002BCEB0 size 0x40 */
static struct anon_2_85 Dc03[3];                                 /* @0x002BCEF0 size 0x30 */
static struct anon_2_85 Dbu0[3];                                 /* @0x002BCF20 size 0x30 */
static struct anon_2_85 Dbu1[3];                                 /* @0x002BCF50 size 0x30 */
static struct anon_2_85 *sbj_dat[45];                            /* @0x002BCF80 size 0xB4 */
static struct anon_8_85 cspd00[2];                               /* @0x002BD040 size 0x18 */
static struct anon_8_85 cspd01[7];                               /* @0x002BD060 size 0x54 */
static struct anon_8_85 cspd02[12];                              /* @0x002BD0C0 size 0x90 */
static struct anon_8_85 *cspd[3];                                /* @0x002BD150 size 0xC */
static struct anon_6_85 extra_arrow_data[30];                    /* @0x002BD160 size 0xF0 */
struct anon_1_85 dmm_subject_w[200];                             /* @0x00806220 size 0x7080 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (18) */
struct anon_8_85 *dmm_data_get_change_music_speed(int id);       /* 0x002293E0-0x002293F8 lines 1178-1179 */
void dmm_data_convert_play_mode(struct anon_12_85 *work, int id); /* 0x00229400-0x002296B0 lines 1085-1172 */
struct anon_6_85 *dmm_get_extra_arrow_data(int extra_arrow_id);  /* 0x002296B0-0x002296C4 lines 1076-1077 */
int dmm_get_boss_No(int area, int id);                           /* 0x002296D0-0x00229730 lines 1024-1035 */
struct anon_2_85 *dmm_data_get_subject_dat(int id);              /* 0x00229730-0x00229764 lines 921-922 */
void dmm_clear_route(void);                                      /* 0x00229770-0x002297C0 lines 888-892 */
void dmm_set_route(int sbj_id);                                  /* 0x002297C0-0x00229818 lines 872-881 */
int dmm_is_default_connect_appear_ok(struct anon_1_85 *sbjw, int connect_id); /* 0x00229820-0x00229890 lines 727-736 */
void dmm_set_connect_sbj_state_playable(int id);                 /* 0x00229890-0x00229B48 lines 608-723 */
int dmm_is_change_chart_ok(void);                                /* 0x00229B50-0x00229BD8 lines 571-587 */
int dmm_is_sbj_allclear_expect_for_lastboss(void);               /* 0x00229BE0-0x00229CC0 lines 545-553 */
int dmm_is_area_boss_allclear(int area);                         /* 0x00229CC0-0x00229D40 lines 522-539 */
int dmm_get_clear_sbj_num(void);                                 /* 0x00229D40-0x00229D94 lines 509-517 */
int dmm_search_appear_area(void);                                /* 0x00229DA0-0x00229DF4 lines 488-504 */
int dmm_get_subject_area_no(int sbj_id);                         /* 0x00229E00-0x00229E60 lines 467-482 */
int dmm_get_subject_area(int sbj_id);                            /* 0x00229E60-0x00229E80 lines 460-461 */
int dmm_get_all_sbj_num(void);                                   /* 0x00229E80-0x00229EB8 lines 447-455 */
struct anon_1_85 *dmm_get_subject_w(int sbj_id);                 /* 0x00229EC0-0x00229EDC lines 430-431 */

#endif /* DDR_UNIT_src_CS_dancemaster_dmm_data_c_H */
