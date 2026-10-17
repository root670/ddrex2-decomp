/*
 * C:\work2\usaex2\src\CS\dancemaster\dmm_qmenu.c
 * MW MIPS C Compiler, overlay dmm_rel4cd.prg; 10 functions, code 0x007FAE20-0x007FB638
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_dancemaster_dmm_qmenu_c_H
#define DDR_UNIT_src_CS_dancemaster_dmm_qmenu_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/play_mode.h"

/* anonymous types (28) */

/* anon_0_220 -- @anon0, 0xC bytes, dmm_qmenu.c (DIE 0x3FE2A5) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char disp_flag;              // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ int tex_id;                           // 0x4
    /* 0x008 */ int a;                                // 0x4
} anon_0_220;

/* anon_1_220 -- @anon1, 0x1C bytes, dmm_qmenu.c (DIE 0x3FE63E) */
typedef struct {   // size 0x1C
    /* 0x000 */ unsigned short note[10];              // 0x14
    /* 0x014 */ unsigned short total_notes;           // 0x2
    /* 0x016 */ unsigned short total_combo;           // 0x2
    /* 0x018 */ unsigned int align;                   // 0x4
} anon_1_220;

/* anon_2_220 -- @anon2, 0x10 bytes, dmm_qmenu.c (DIE 0x3FE716) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_2_220;

/* anon_4_220 -- @anon4, 0x14 bytes, dmm_qmenu.c (DIE 0x3FEFB5) */
typedef struct {   // size 0x14
    /* 0x000 */ int disp_flag;                        // 0x4
    /* 0x004 */ float timer;                          // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ int a;                                // 0x4
} anon_4_220;

/* anon_5_220 -- @anon5, 0xC bytes, dmm_qmenu.c (DIE 0x3FF09A) */
typedef struct {   // size 0xC
    /* 0x000 */ int (*func)();                        // 0x4
    /* 0x004 */ int (*ini)();                         // 0x4
    /* 0x008 */ unsigned char *str;                   // 0x4
} anon_5_220;

/* anon_6_220 -- @anon6, 0x28 bytes, dmm_qmenu.c (DIE 0x3FF389) */
typedef struct {   // size 0x28
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
} anon_6_220;

/* anon_7_220 -- @anon7, 0x10 bytes, dmm_qmenu.c (DIE 0x3FF7FC) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_7_220;

/* anon_8_220 -- @anon8, 0x10 bytes, dmm_qmenu.c (DIE 0x3FFCE4) */
typedef struct {   // size 0x10
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int decide;                           // 0x4
    /* 0x00C */ int cancel;                           // 0x4
} anon_8_220;

/* anon_22_220 -- @anon22, 0x14 bytes, dmm_qmenu.c (DIE 0x4058A7) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_22_220;

/* anon_27_220 -- @anon27, 0x1300 bytes, dmm_qmenu.c (DIE 0x406100) */
typedef struct {   // size 0x1300
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
    /* 0x360 */ anon_22_220 subject[200];             // 0xFA0
} anon_27_220;

/* anon_15_220 -- @anon15, 0x38 bytes, dmm_qmenu.c (DIE 0x4025E1) */
typedef struct {   // size 0x38
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
} anon_15_220;

/* anon_20_220 -- @anon20, 0x1F0 bytes, dmm_qmenu.c (DIE 0x40544E) */
typedef struct {   // size 0x1F0
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
} anon_20_220;

/* anon_10_220 -- @anon10, 0x4 bytes, dmm_qmenu.c (DIE 0x40192E) */
typedef struct {   // size 0x4
    /* 0x000 */ int cursor;                           // 0x4
} anon_10_220;

/* anon_23_220 -- @anon23, 0x10 bytes, dmm_qmenu.c (DIE 0x405B2C) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int x;                                // 0x4
    /* 0x00C */ int y;                                // 0x4
} anon_23_220;

/* anon_12_220 -- @anon12, 0xC bytes, dmm_qmenu.c (DIE 0x401D8D) */
typedef struct {   // size 0xC
    /* 0x000 */ int no;                               // 0x4
    /* 0x004 */ int contents_id;                      // 0x4
    /* 0x008 */ int (*func)();                        // 0x4
} anon_12_220;

/* anon_13_220 -- @anon13, 0x1AC bytes, dmm_qmenu.c (DIE 0x401EBA) */
typedef struct {   // size 0x1AC
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
    /* 0x02C */ anon_12_220 exe_w[32];                // 0x180
} anon_13_220;

/* anon_14_220 -- @anon14, 0x14 bytes, dmm_qmenu.c (DIE 0x40238D) */
typedef struct {   // size 0x14
    /* 0x000 */ int flag;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step_s;                           // 0x4
    /* 0x00C */ int shop_mode_flag;                   // 0x4
    /* 0x010 */ int yesno;                            // 0x4
} anon_14_220;

/* anon_17_220 -- @anon17, 0x10 bytes, dmm_qmenu.c (DIE 0x402A9B) */
typedef struct {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int count;                            // 0x4
    /* 0x00C */ signed char dir[2];                   // 0x2
    /* 0x00E */ signed char pading[2];                // 0x2
} anon_17_220;

/* anon_26_220 -- @anon26, 0xC bytes, dmm_qmenu.c (DIE 0x405F99) */
typedef struct {   // size 0xC
    /* 0x000 */ int sbj_id;                           // 0x4
    /* 0x004 */ unsigned int bar_start;               // 0x4
    /* 0x008 */ unsigned int bar_end;                 // 0x4
} anon_26_220;

/* anon_28_220 -- @anon28, 0x28 bytes, dmm_qmenu.c (DIE 0x406387) */
typedef struct {   // size 0x28
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
} anon_28_220;

/* anon_9_220 -- @anon9, 0x3D7C bytes, dmm_qmenu.c (DIE 0x3FFD87) */
typedef struct {   // size 0x3D7C
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
    /* 0x2A0 */ anon_27_220 swap_save_data;           // 0x1300
    /* 0x15A0 */ anon_15_220 mc_w;                    // 0x38
    /* 0x15D8 */ anon_2_220 button_disp_w;            // 0x10
    /* 0x15E8 */ anon_6_220 record_w;                 // 0x28
    /* 0x1610 */ anon_7_220 fade_env;                 // 0x10
    /* 0x1620 */ int total_record[4];                 // 0x10
    /* 0x1630 */ anon_1_220 preres[2];                // 0x38
    /* 0x1668 */ anon_20_220 result[2];               // 0x3E0
    /* 0x1A48 */ unsigned short cur_note[2];          // 0x4
    /* 0x1A4C */ short old_point[2];                  // 0x4
    /* 0x1A50 */ unsigned int subj_opt;               // 0x4
    /* 0x1A54 */ anon_10_220 style_menu;              // 0x4
    /* 0x1A58 */ anon_8_220 pad_w;                    // 0x10
    /* 0x1A68 */ anon_23_220 move_w[6];               // 0x60
    /* 0x1AC8 */ anon_13_220 ev_w;                    // 0x1AC
    /* 0x1C74 */ anon_14_220 qmenu_w;                 // 0x14
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
    /* 0x1CD0 */ anon_17_220 worldw;                  // 0x10
    /* 0x1CE0 */ anon_26_220 cha_sbj_info_w;          // 0xC
    /* 0x1CEC */ anon_26_220 sel_sbj_info_w[8];       // 0x60
    /* 0x1D4C */ anon_28_220 panel_disp_w[200];       // 0x1F40
    /* 0x3C8C */ anon_0_220 cone_disp_w[8];           // 0x60
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
    /* 0x3D54 */ anon_4_220 blind_w;                  // 0x14
    /* 0x3D68 */ int result_state;                    // 0x4
    /* 0x3D6C */ int result_cnt;                      // 0x4
    /* 0x3D70 */ int total_result_cnt;                // 0x4
    /* 0x3D74 */ int result_mask_cnt;                 // 0x4
    /* 0x3D78 */ int dummy;                           // 0x4
} anon_9_220;

/* anon_18_220 -- @anon18, 0x4 bytes, dmm_qmenu.c (DIE 0x404F4F) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_18_220;

/* anon_21_220 -- @anon21, 0x10 bytes, dmm_qmenu.c (DIE 0x405762) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_18_220 x0;                       // 0x4
    /* 0x004 */ anon_18_220 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_21_220;

/* anon_19_220 -- @anon19, 0xD40 bytes, dmm_qmenu.c (DIE 0x405019) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_19_220;

/* anon_24_220 -- @anon24, 0xC bytes, dmm_qmenu.c (DIE 0x405C5D) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_24_220;

/* anon_30_220 -- @anon30, 0x4 bytes, dmm_qmenu.c (DIE 0x4066DF) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_30_220;

/* anon_29_220 -- @anon29, 0x4 bytes, dmm_qmenu.c (DIE 0x406638) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_30_220 s;                        // 0x4
} anon_29_220;

/* anon_31_220 -- @anon31, 0x12E0 bytes, dmm_qmenu.c (DIE 0x40697D) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_24_220 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_31_220;


/* variables (8) */
static anon_5_220 dmm_qm_change;                                 /* @0x00806040 size 0xC */
static anon_5_220 dmm_qm_shop;                                   /* @0x00806050 size 0xC */
static anon_5_220 dmm_qm_save;                                   /* @0x00806060 size 0xC */
static anon_5_220 dmm_qm_return;                                 /* @0x00806070 size 0xC */
anon_5_220 *dmm_qm_tbl[5];                                       /* @0x00806080 size 0x14 */
anon_5_220 *dmm_qm_tbl_first[4];                                 /* @0x008060A0 size 0x10 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (10) */
static int _dmm_qmenu_func_return(void);                         /* 0x007FAE20-0x007FAE4C lines 485-488 */
static int _dmm_qmenu_func_save(void);                           /* 0x007FAE50-0x007FAEE8 lines 385-473 */
static int _dmm_qmenu_func_shop(void);                           /* 0x007FAEF0-0x007FB044 lines 316-381 */
static int _dmm_qmenu_func_change(void);                         /* 0x007FB050-0x007FB2AC lines 248-312 */
static int quick_menu_ctrl(void);                                /* 0x007FB2B0-0x007FB3B4 lines 222-241 */
anon_5_220 *get_qmenu_table(void);                               /* 0x007FB3C0-0x007FB3F8 lines 208-218 */
anon_14_220 *get_qmenu_work(void);                               /* 0x007FB400-0x007FB420 lines 200-202 */
void quick_menu_main(void);                                      /* 0x007FB420-0x007FB618 lines 105-192 */
void quick_menu_check(void);                                     /* 0x007FB620-0x007FB628 lines 100-100 */
void quick_menu_init(void);                                      /* 0x007FB630-0x007FB638 lines 90-90 */

#endif /* DDR_UNIT_src_CS_dancemaster_dmm_qmenu_c_H */
