/*
 * C:\work2\usaex2\src\CS\dancemaster\dmm_event.c
 * MW MIPS C Compiler, overlay dmm_rel4cd.prg; 10 functions, code 0x007F0080-0x007F0CC0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_dancemaster_dmm_event_c_H
#define DDR_UNIT_src_CS_dancemaster_dmm_event_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"
#include "types/play_mode.h"

/* anonymous types (30) */

/* anon_0_214 -- @anon0, 0xC bytes, dmm_event.c (DIE 0x3C507F) */
struct anon_0_214 {   // size 0xC
    /* 0x000 */ unsigned char disp_flag;              // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ int tex_id;                           // 0x4
    /* 0x008 */ int a;                                // 0x4
};

/* anon_28_214 -- @anon28, 0xC bytes, dmm_event.c (DIE 0x3CB1FC) */
struct anon_28_214 {   // size 0xC
    /* 0x000 */ int id;                               // 0x4
    /* 0x004 */ int hide;                             // 0x4
    /* 0x008 */ int func_No;                          // 0x4
};

/* anon_20_214 -- @anon20, 0x1C bytes, dmm_event.c (DIE 0x3CA472) */
struct anon_20_214 {   // size 0x1C
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

/* anon_1_214 -- @anon1, 0x90 bytes, dmm_event.c (DIE 0x3C5127) */
struct anon_1_214 {   // size 0x90
    /* 0x000 */ struct anon_28_214 connect[8];        // 0x60
    /* 0x060 */ unsigned int area;                    // 0x4
    /* 0x064 */ int pos_x;                            // 0x4
    /* 0x068 */ int pos_y;                            // 0x4
    /* 0x06C */ int hide;                             // 0x4
    /* 0x070 */ int ex_arrow;                         // 0x4
    /* 0x074 */ struct anon_20_214 sbj_data;          // 0x1C
};

/* anon_2_214 -- @anon2, 0xC bytes, dmm_event.c (DIE 0x3C52F4) */
struct anon_2_214 {   // size 0xC
    /* 0x000 */ int no;                               // 0x4
    /* 0x004 */ int contents_id;                      // 0x4
    /* 0x008 */ int (*func)();                        // 0x4
};

/* anon_3_214 -- @anon3, 0x1C bytes, dmm_event.c (DIE 0x3C53F0) */
struct anon_3_214 {   // size 0x1C
    /* 0x000 */ unsigned short note[10];              // 0x14
    /* 0x014 */ unsigned short total_notes;           // 0x2
    /* 0x016 */ unsigned short total_combo;           // 0x2
    /* 0x018 */ unsigned int align;                   // 0x4
};

/* anon_4_214 -- @anon4, 0x10 bytes, dmm_event.c (DIE 0x3C54C8) */
struct anon_4_214 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
};

/* anon_5_214 -- @anon5, 0x4 bytes, dmm_event.c (DIE 0x3C5562) */
struct anon_5_214 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_6_214 -- @anon6, 0x14 bytes, dmm_event.c (DIE 0x3C5D67) */
struct anon_6_214 {   // size 0x14
    /* 0x000 */ int disp_flag;                        // 0x4
    /* 0x004 */ float timer;                          // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ int a;                                // 0x4
};

/* anon_7_214 -- @anon7, 0x28 bytes, dmm_event.c (DIE 0x3C602C) */
struct anon_7_214 {   // size 0x28
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

/* anon_18_214 -- @anon18, 0x14 bytes, dmm_event.c (DIE 0x3CA104) */
struct anon_18_214 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_23_214 -- @anon23, 0x1300 bytes, dmm_event.c (DIE 0x3CA952) */
struct anon_23_214 {   // size 0x1300
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
    /* 0x360 */ struct anon_18_214 subject[200];      // 0xFA0
};

/* anon_13_214 -- @anon13, 0x38 bytes, dmm_event.c (DIE 0x3C8E73) */
struct anon_13_214 {   // size 0x38
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

/* anon_10_214 -- @anon10, 0x10 bytes, dmm_event.c (DIE 0x3C792D) */
struct anon_10_214 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
};

/* anon_17_214 -- @anon17, 0x1F0 bytes, dmm_event.c (DIE 0x3C9DCC) */
struct anon_17_214 {   // size 0x1F0
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

/* anon_12_214 -- @anon12, 0x4 bytes, dmm_event.c (DIE 0x3C8716) */
struct anon_12_214 {   // size 0x4
    /* 0x000 */ int cursor;                           // 0x4
};

/* anon_11_214 -- @anon11, 0x10 bytes, dmm_event.c (DIE 0x3C7DF4) */
struct anon_11_214 {   // size 0x10
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int decide;                           // 0x4
    /* 0x00C */ int cancel;                           // 0x4
};

/* anon_19_214 -- @anon19, 0x10 bytes, dmm_event.c (DIE 0x3CA389) */
struct anon_19_214 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int x;                                // 0x4
    /* 0x00C */ int y;                                // 0x4
};

/* anon_9_214 -- @anon9, 0x1AC bytes, dmm_event.c (DIE 0x3C76EA) */
struct anon_9_214 {   // size 0x1AC
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
    /* 0x02C */ struct anon_2_214 exe_w[32];          // 0x180
};

/* anon_15_214 -- @anon15, 0x14 bytes, dmm_event.c (DIE 0x3C98A3) */
struct anon_15_214 {   // size 0x14
    /* 0x000 */ int flag;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step_s;                           // 0x4
    /* 0x00C */ int shop_mode_flag;                   // 0x4
    /* 0x010 */ int yesno;                            // 0x4
};

/* anon_14_214 -- @anon14, 0x10 bytes, dmm_event.c (DIE 0x3C91C9) */
struct anon_14_214 {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int count;                            // 0x4
    /* 0x00C */ signed char dir[2];                   // 0x2
    /* 0x00E */ signed char pading[2];                // 0x2
};

/* anon_22_214 -- @anon22, 0xC bytes, dmm_event.c (DIE 0x3CA857) */
struct anon_22_214 {   // size 0xC
    /* 0x000 */ int sbj_id;                           // 0x4
    /* 0x004 */ unsigned int bar_start;               // 0x4
    /* 0x008 */ unsigned int bar_end;                 // 0x4
};

/* anon_24_214 -- @anon24, 0x28 bytes, dmm_event.c (DIE 0x3CABB5) */
struct anon_24_214 {   // size 0x28
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

/* anon_8_214 -- @anon8, 0x3D7C bytes, dmm_event.c (DIE 0x3C61C2) */
struct anon_8_214 {   // size 0x3D7C
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
    /* 0x2A0 */ struct anon_23_214 swap_save_data;    // 0x1300
    /* 0x15A0 */ struct anon_13_214 mc_w;             // 0x38
    /* 0x15D8 */ struct anon_4_214 button_disp_w;     // 0x10
    /* 0x15E8 */ struct anon_7_214 record_w;          // 0x28
    /* 0x1610 */ struct anon_10_214 fade_env;         // 0x10
    /* 0x1620 */ int total_record[4];                 // 0x10
    /* 0x1630 */ struct anon_3_214 preres[2];         // 0x38
    /* 0x1668 */ struct anon_17_214 result[2];        // 0x3E0
    /* 0x1A48 */ unsigned short cur_note[2];          // 0x4
    /* 0x1A4C */ short old_point[2];                  // 0x4
    /* 0x1A50 */ unsigned int subj_opt;               // 0x4
    /* 0x1A54 */ struct anon_12_214 style_menu;       // 0x4
    /* 0x1A58 */ struct anon_11_214 pad_w;            // 0x10
    /* 0x1A68 */ struct anon_19_214 move_w[6];        // 0x60
    /* 0x1AC8 */ struct anon_9_214 ev_w;              // 0x1AC
    /* 0x1C74 */ struct anon_15_214 qmenu_w;          // 0x14
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
    /* 0x1CD0 */ struct anon_14_214 worldw;           // 0x10
    /* 0x1CE0 */ struct anon_22_214 cha_sbj_info_w;   // 0xC
    /* 0x1CEC */ struct anon_22_214 sel_sbj_info_w[8];  // 0x60
    /* 0x1D4C */ struct anon_24_214 panel_disp_w[200];  // 0x1F40
    /* 0x3C8C */ struct anon_0_214 cone_disp_w[8];    // 0x60
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
    /* 0x3D54 */ struct anon_6_214 blind_w;           // 0x14
    /* 0x3D68 */ int result_state;                    // 0x4
    /* 0x3D6C */ int result_cnt;                      // 0x4
    /* 0x3D70 */ int total_result_cnt;                // 0x4
    /* 0x3D74 */ int result_mask_cnt;                 // 0x4
    /* 0x3D78 */ int dummy;                           // 0x4
};

/* anon_16_214 -- @anon16, 0xD40 bytes, dmm_event.c (DIE 0x3C99BD) */
struct anon_16_214 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_21_214 -- @anon21, 0xC bytes, dmm_event.c (DIE 0x3CA6A2) */
struct anon_21_214 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_26_214 -- @anon26, 0x4 bytes, dmm_event.c (DIE 0x3CADB9) */
struct anon_26_214 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_25_214 -- @anon25, 0x4 bytes, dmm_event.c (DIE 0x3CAD36) */
union anon_25_214 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_26_214 s;                 // 0x4
};

/* anon_27_214 -- @anon27, 0x12E0 bytes, dmm_event.c (DIE 0x3CB00F) */
struct anon_27_214 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_21_214 history[400];      // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_29_214 -- @anon29, 0x2134 bytes, dmm_event.c (DIE 0x3CB310) */
struct anon_29_214 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_25_214 userpass;           // 0x4
    /* 0x008 */ struct anon_27_214 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_16_214 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};


/* variables (4) */
int (*dmm_event_func[7])();                                      /* @0x00805F80 size 0x1C */
static int (*dmm_evboot_func[23])(int);                          /* @0x00805FA0 size 0x5C */
static int (*dmm_evboot_sp_cone_func[2])();                      /* @0x002DDED0 size 0x8 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (10) */
int dmm_sp_connect_hide_check(int No);                           /* 0x007F0080-0x007F00C4 lines 633-640 */
void dmm_event_boot_check(int chance);                           /* 0x007F00D0-0x007F0150 lines 608-617 */
static void dmm_event_set_fade(struct anon_9_214 *evw);          /* 0x007F0150-0x007F02D8 lines 482-560 */
int dmm_event_wait_count(int cnt);                               /* 0x007F02E0-0x007F0340 lines 467-478 */
int dmm_event_get_count(void);                                   /* 0x007F0340-0x007F0360 lines 460-464 */
void dmm_event_set_count(void);                                  /* 0x007F0360-0x007F0380 lines 453-457 */
int dmm_event_main(void);                                        /* 0x007F0380-0x007F05B8 lines 327-396 */
static void dmm_set_sbj_special_connect_event(void);             /* 0x007F05C0-0x007F0768 lines 170-225 */
static void dmm_set_sbj_normal_connect_event(void);              /* 0x007F0770-0x007F0928 lines 130-166 */
void dmm_event_check(void);                                      /* 0x007F0930-0x007F0CC0 lines 89-122 */

#endif /* DDR_UNIT_src_CS_dancemaster_dmm_event_c_H */
