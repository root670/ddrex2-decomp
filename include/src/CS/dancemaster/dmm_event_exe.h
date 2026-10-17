/*
 * C:\work2\usaex2\src\CS\dancemaster\dmm_event_exe.c
 * MW MIPS C Compiler, overlay dmm_rel4cd.prg; 18 functions, code 0x007F19B0-0x007F7404
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_dancemaster_dmm_event_exe_c_H
#define DDR_UNIT_src_CS_dancemaster_dmm_event_exe_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/play_mode.h"
#include "types/tex_bind.h"

/* anonymous types (35) */

/* anon_15_216 -- @anon15, 0xC bytes, dmm_event_exe.c (DIE 0x3DB01C) */
typedef struct {   // size 0xC
    /* 0x000 */ int no;                               // 0x4
    /* 0x004 */ int contents_id;                      // 0x4
    /* 0x008 */ int (*func)();                        // 0x4
} anon_15_216;

/* anon_1_216 -- @anon1, 0x1AC bytes, dmm_event_exe.c (DIE 0x3D76BD) */
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
    /* 0x02C */ anon_15_216 exe_w[32];                // 0x180
} anon_1_216;

/* anon_36_216 -- @anon36, 0x14 bytes, dmm_event_exe.c (DIE 0x3E0F56) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_36_216;

/* anon_2_216 -- @anon2, 0x1300 bytes, dmm_event_exe.c (DIE 0x3D7948) */
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
    /* 0x360 */ anon_36_216 subject[200];             // 0xFA0
} anon_2_216;

/* anon_32_216 -- @anon32, 0x38 bytes, dmm_event_exe.c (DIE 0x3DFBE6) */
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
} anon_32_216;

/* anon_20_216 -- @anon20, 0x10 bytes, dmm_event_exe.c (DIE 0x3DC247) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_20_216;

/* anon_22_216 -- @anon22, 0x28 bytes, dmm_event_exe.c (DIE 0x3DD173) */
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
} anon_22_216;

/* anon_23_216 -- @anon23, 0x10 bytes, dmm_event_exe.c (DIE 0x3DD3C6) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_23_216;

/* anon_19_216 -- @anon19, 0x1C bytes, dmm_event_exe.c (DIE 0x3DC064) */
typedef struct {   // size 0x1C
    /* 0x000 */ unsigned short note[10];              // 0x14
    /* 0x014 */ unsigned short total_notes;           // 0x2
    /* 0x016 */ unsigned short total_combo;           // 0x2
    /* 0x018 */ unsigned int align;                   // 0x4
} anon_19_216;

/* anon_4_216 -- @anon4, 0x1F0 bytes, dmm_event_exe.c (DIE 0x3D8E61) */
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
} anon_4_216;

/* anon_27_216 -- @anon27, 0x4 bytes, dmm_event_exe.c (DIE 0x3DDD7B) */
typedef struct {   // size 0x4
    /* 0x000 */ int cursor;                           // 0x4
} anon_27_216;

/* anon_26_216 -- @anon26, 0x10 bytes, dmm_event_exe.c (DIE 0x3DDB92) */
typedef struct {   // size 0x10
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int decide;                           // 0x4
    /* 0x00C */ int cancel;                           // 0x4
} anon_26_216;

/* anon_11_216 -- @anon11, 0x10 bytes, dmm_event_exe.c (DIE 0x3D9DF7) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int x;                                // 0x4
    /* 0x00C */ int y;                                // 0x4
} anon_11_216;

/* anon_39_216 -- @anon39, 0x14 bytes, dmm_event_exe.c (DIE 0x3E16F8) */
typedef struct {   // size 0x14
    /* 0x000 */ int flag;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step_s;                           // 0x4
    /* 0x00C */ int shop_mode_flag;                   // 0x4
    /* 0x010 */ int yesno;                            // 0x4
} anon_39_216;

/* anon_33_216 -- @anon33, 0x10 bytes, dmm_event_exe.c (DIE 0x3E0A01) */
typedef struct {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int count;                            // 0x4
    /* 0x00C */ signed char dir[2];                   // 0x2
    /* 0x00E */ signed char pading[2];                // 0x2
} anon_33_216;

/* anon_13_216 -- @anon13, 0xC bytes, dmm_event_exe.c (DIE 0x3DA5CD) */
typedef struct {   // size 0xC
    /* 0x000 */ int sbj_id;                           // 0x4
    /* 0x004 */ unsigned int bar_start;               // 0x4
    /* 0x008 */ unsigned int bar_end;                 // 0x4
} anon_13_216;

/* anon_9_216 -- @anon9, 0x28 bytes, dmm_event_exe.c (DIE 0x3D9A45) */
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
} anon_9_216;

/* anon_17_216 -- @anon17, 0xC bytes, dmm_event_exe.c (DIE 0x3DB42E) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char disp_flag;              // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ int tex_id;                           // 0x4
    /* 0x008 */ int a;                                // 0x4
} anon_17_216;

/* anon_21_216 -- @anon21, 0x14 bytes, dmm_event_exe.c (DIE 0x3DC77F) */
typedef struct {   // size 0x14
    /* 0x000 */ int disp_flag;                        // 0x4
    /* 0x004 */ float timer;                          // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ int a;                                // 0x4
} anon_21_216;

/* anon_3_216 -- @anon3, 0x3D7C bytes, dmm_event_exe.c (DIE 0x3D7B16) */
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
    /* 0x2A0 */ anon_2_216 swap_save_data;            // 0x1300
    /* 0x15A0 */ anon_32_216 mc_w;                    // 0x38
    /* 0x15D8 */ anon_20_216 button_disp_w;           // 0x10
    /* 0x15E8 */ anon_22_216 record_w;                // 0x28
    /* 0x1610 */ anon_23_216 fade_env;                // 0x10
    /* 0x1620 */ int total_record[4];                 // 0x10
    /* 0x1630 */ anon_19_216 preres[2];               // 0x38
    /* 0x1668 */ anon_4_216 result[2];                // 0x3E0
    /* 0x1A48 */ unsigned short cur_note[2];          // 0x4
    /* 0x1A4C */ short old_point[2];                  // 0x4
    /* 0x1A50 */ unsigned int subj_opt;               // 0x4
    /* 0x1A54 */ anon_27_216 style_menu;              // 0x4
    /* 0x1A58 */ anon_26_216 pad_w;                   // 0x10
    /* 0x1A68 */ anon_11_216 move_w[6];               // 0x60
    /* 0x1AC8 */ anon_1_216 ev_w;                     // 0x1AC
    /* 0x1C74 */ anon_39_216 qmenu_w;                 // 0x14
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
    /* 0x1CD0 */ anon_33_216 worldw;                  // 0x10
    /* 0x1CE0 */ anon_13_216 cha_sbj_info_w;          // 0xC
    /* 0x1CEC */ anon_13_216 sel_sbj_info_w[8];       // 0x60
    /* 0x1D4C */ anon_9_216 panel_disp_w[200];        // 0x1F40
    /* 0x3C8C */ anon_17_216 cone_disp_w[8];          // 0x60
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
    /* 0x3D54 */ anon_21_216 blind_w;                 // 0x14
    /* 0x3D68 */ int result_state;                    // 0x4
    /* 0x3D6C */ int result_cnt;                      // 0x4
    /* 0x3D70 */ int total_result_cnt;                // 0x4
    /* 0x3D74 */ int result_mask_cnt;                 // 0x4
    /* 0x3D78 */ int dummy;                           // 0x4
} anon_3_216;

/* anon_18_216 -- @anon18, 0xC bytes, dmm_event_exe.c (DIE 0x3DB4FB) */
typedef struct {   // size 0xC
    /* 0x000 */ int id;                               // 0x4
    /* 0x004 */ int hide;                             // 0x4
    /* 0x008 */ int func_No;                          // 0x4
} anon_18_216;

/* anon_10_216 -- @anon10, 0x1C bytes, dmm_event_exe.c (DIE 0x3D9C0F) */
typedef struct {   // size 0x1C
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
} anon_10_216;

/* anon_5_216 -- @anon5, 0x90 bytes, dmm_event_exe.c (DIE 0x3D91BF) */
typedef struct {   // size 0x90
    /* 0x000 */ anon_18_216 connect[8];               // 0x60
    /* 0x060 */ unsigned int area;                    // 0x4
    /* 0x064 */ int pos_x;                            // 0x4
    /* 0x068 */ int pos_y;                            // 0x4
    /* 0x06C */ int hide;                             // 0x4
    /* 0x070 */ int ex_arrow;                         // 0x4
    /* 0x074 */ anon_10_216 sbj_data;                 // 0x1C
} anon_5_216;

/* anon_8_216 -- @anon8, 0x4 bytes, dmm_event_exe.c (DIE 0x3D94D6) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_8_216;

/* anon_6_216 -- @anon6, 0x4 bytes, dmm_event_exe.c (DIE 0x3D92D6) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_8_216 s;                         // 0x4
} anon_6_216;

/* anon_38_216 -- @anon38, 0xC bytes, dmm_event_exe.c (DIE 0x3E158D) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_38_216;

/* anon_7_216 -- @anon7, 0x12E0 bytes, dmm_event_exe.c (DIE 0x3D9358) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_38_216 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_7_216;

/* anon_34_216 -- @anon34, 0xD40 bytes, dmm_event_exe.c (DIE 0x3E0AF0) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_34_216;

/* anon_31_216 -- @anon31, 0x4 bytes, dmm_event_exe.c (DIE 0x3DFA61) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_31_216;

/* anon_14_216 -- @anon14, 0x24 bytes, dmm_event_exe.c (DIE 0x3DADDA) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_31_216 x0;                       // 0x4
    /* 0x004 */ anon_31_216 y0;                       // 0x4
    /* 0x008 */ anon_31_216 x1;                       // 0x4
    /* 0x00C */ anon_31_216 y1;                       // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ unsigned char r1;                     // 0x1
    /* 0x01D */ unsigned char g1;                     // 0x1
    /* 0x01E */ unsigned char b1;                     // 0x1
    /* 0x01F */ unsigned char a1;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
} anon_14_216;

/* anon_25_216 -- @anon25, 0x48 bytes, dmm_event_exe.c (DIE 0x3DD87F) */
typedef struct {   // size 0x48
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
} anon_25_216;

/* anon_28_216 -- @anon28, 0x1C bytes, dmm_event_exe.c (DIE 0x3DDF18) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_31_216 x0;                       // 0x4
    /* 0x004 */ anon_31_216 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_28_216;

/* anon_35_216 -- @anon35, 0x10 bytes, dmm_event_exe.c (DIE 0x3E0BC8) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_31_216 x0;                       // 0x4
    /* 0x004 */ anon_31_216 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_35_216;

/* anon_30_216 -- @anon30, 0x24 bytes, dmm_event_exe.c (DIE 0x3DE5AC) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_31_216 x0;                       // 0x4
    /* 0x004 */ anon_31_216 y0;                       // 0x4
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
} anon_30_216;

/* anon_37_216 -- @anon37, 0x68 bytes, dmm_event_exe.c (DIE 0x3E116B) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_31_216 x0;                       // 0x4
    /* 0x004 */ anon_31_216 y0;                       // 0x4
    /* 0x008 */ anon_31_216 x1;                       // 0x4
    /* 0x00C */ anon_31_216 y1;                       // 0x4
    /* 0x010 */ anon_31_216 x2;                       // 0x4
    /* 0x014 */ anon_31_216 y2;                       // 0x4
    /* 0x018 */ anon_31_216 x3;                       // 0x4
    /* 0x01C */ anon_31_216 y3;                       // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
} anon_37_216;


/* variables (6) */
unsigned char *dmm_str_sp_cone_info;                             /* @0x002DDED8 size 0x4 */
unsigned char *dmm_str_area_info;                                /* @0x002DDEDC size 0x4 */
unsigned char *dmm_str_info[2];                                  /* @0x002DDEE0 size 0x8 */
unsigned char *data_path_tbl[15];                                /* @0x00806000 size 0x3C */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (18) */
static int _dmm_event_sub_disp_chart(anon_3_216 *work);          /* 0x007F19B0-0x007F1AFC lines 2339-2391 */
int _dmm_event_disp_chart(void);                                 /* 0x007F1B00-0x007F1BD0 lines 2305-2336 */
static int _dmm_event_func04_sub(anon_3_216 *work, int id);      /* 0x007F1BD0-0x007F1E18 lines 2230-2298 */
int _dmm_event_func04(void);                                     /* 0x007F1E20-0x007F1F20 lines 2187-2226 */
static void _dmm_event_func03_sub_set_state(int contents_id);    /* 0x007F1F20-0x007F2124 lines 2120-2176 */
static void _dmm_event_func03_sub_disp_area1_start(anon_3_216 *work, int _br, int _alpha); /* 0x007F2130-0x007F2380 lines 2055-2116 */
static void _dmm_event_func03_sub_disp(anon_3_216 *work, int contents_id, int pane_alpha, int pane_br, int cone_alpha, int old_area_alpha, int new_area_alpha); /* 0x007F2380-0x007F27A8 lines 1960-2051 */
static void _dmm_event_func03_sub_init(anon_3_216 *work, int contents_id); /* 0x007F27B0-0x007F2B24 lines 1865-1956 */
static int _dmm_event_func03_sub(anon_3_216 *work, int contents_id); /* 0x007F2B30-0x007F3098 lines 1698-1860 */
int _dmm_event_func03(void);                                     /* 0x007F30A0-0x007F3188 lines 1661-1694 */
static int _dmm_event_func02_play_ending_logo(anon_3_216 *work); /* 0x007F3190-0x007F5BA0 lines 1035-1546 */
static int _dmm_event_func02_ending(anon_3_216 *work, int id);   /* 0x007F5BA0-0x007F5E34 lines 782-884 */
int _dmm_event_func02(void);                                     /* 0x007F5E40-0x007F5F98 lines 738-778 */
static int _dmm_event_func01_sub(anon_3_216 *work, int id);      /* 0x007F5FA0-0x007F6938 lines 444-686 */
int _dmm_event_func01(void);                                     /* 0x007F6940-0x007F6A10 lines 408-440 */
static int _dmm_event_func00_sub(anon_3_216 *work, int id);      /* 0x007F6A10-0x007F7270 lines 183-398 */
int _dmm_event_func00(void);                                     /* 0x007F7270-0x007F7340 lines 148-179 */
static int dmm_reset_to_playable(anon_3_216 *work, int sbj_id);  /* 0x007F7340-0x007F7404 lines 97-135 */

#endif /* DDR_UNIT_src_CS_dancemaster_dmm_event_exe_c_H */
