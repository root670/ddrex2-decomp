/*
 * C:\work2\usaex2\src\CS\dancemaster\dmm_play.c
 * MW MIPS C Compiler, overlay dmm_rel4cd.prg; 8 functions, code 0x007F8810-0x007F9DB4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_dancemaster_dmm_play_c_H
#define DDR_UNIT_src_CS_dancemaster_dmm_play_c_H

#include "types/G_SYS_W_.h"
#include "types/g_each_w.h"
#include "types/g_game_w.h"
#include "types/play_mode.h"
#include "types/play_w.h"
#include "types/sequence.h"

/* anonymous types (27) */

/* anon_0_218 -- @anon0, 0xC bytes, dmm_play.c (DIE 0x3EC050) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char disp_flag;              // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ int tex_id;                           // 0x4
    /* 0x008 */ int a;                                // 0x4
} anon_0_218;

/* anon_24_218 -- @anon24, 0x14 bytes, dmm_play.c (DIE 0x3F1918) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_24_218;

/* anon_27_218 -- @anon27, 0x1300 bytes, dmm_play.c (DIE 0x3F1E58) */
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
    /* 0x360 */ anon_24_218 subject[200];             // 0xFA0
} anon_27_218;

/* anon_16_218 -- @anon16, 0x38 bytes, dmm_play.c (DIE 0x3EEC64) */
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
} anon_16_218;

/* anon_3_218 -- @anon3, 0x10 bytes, dmm_play.c (DIE 0x3ED70E) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_3_218;

/* anon_8_218 -- @anon8, 0x28 bytes, dmm_play.c (DIE 0x3EDB20) */
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
} anon_8_218;

/* anon_9_218 -- @anon9, 0x10 bytes, dmm_play.c (DIE 0x3EDF02) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_9_218;

/* anon_2_218 -- @anon2, 0x1C bytes, dmm_play.c (DIE 0x3ED636) */
typedef struct {   // size 0x1C
    /* 0x000 */ unsigned short note[10];              // 0x14
    /* 0x014 */ unsigned short total_notes;           // 0x2
    /* 0x016 */ unsigned short total_combo;           // 0x2
    /* 0x018 */ unsigned int align;                   // 0x4
} anon_2_218;

/* anon_22_218 -- @anon22, 0x1F0 bytes, dmm_play.c (DIE 0x3F1507) */
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
} anon_22_218;

/* anon_12_218 -- @anon12, 0x4 bytes, dmm_play.c (DIE 0x3EE217) */
typedef struct {   // size 0x4
    /* 0x000 */ int cursor;                           // 0x4
} anon_12_218;

/* anon_11_218 -- @anon11, 0x10 bytes, dmm_play.c (DIE 0x3EE090) */
typedef struct {   // size 0x10
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int decide;                           // 0x4
    /* 0x00C */ int cancel;                           // 0x4
} anon_11_218;

/* anon_25_218 -- @anon25, 0x10 bytes, dmm_play.c (DIE 0x3F1B09) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int x;                                // 0x4
    /* 0x00C */ int y;                                // 0x4
} anon_25_218;

/* anon_14_218 -- @anon14, 0xC bytes, dmm_play.c (DIE 0x3EE650) */
typedef struct {   // size 0xC
    /* 0x000 */ int no;                               // 0x4
    /* 0x004 */ int contents_id;                      // 0x4
    /* 0x008 */ int (*func)();                        // 0x4
} anon_14_218;

/* anon_15_218 -- @anon15, 0x1AC bytes, dmm_play.c (DIE 0x3EE711) */
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
    /* 0x02C */ anon_14_218 exe_w[32];                // 0x180
} anon_15_218;

/* anon_21_218 -- @anon21, 0x14 bytes, dmm_play.c (DIE 0x3F13C7) */
typedef struct {   // size 0x14
    /* 0x000 */ int flag;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step_s;                           // 0x4
    /* 0x00C */ int shop_mode_flag;                   // 0x4
    /* 0x010 */ int yesno;                            // 0x4
} anon_21_218;

/* anon_18_218 -- @anon18, 0x10 bytes, dmm_play.c (DIE 0x3EF280) */
typedef struct {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int count;                            // 0x4
    /* 0x00C */ signed char dir[2];                   // 0x2
    /* 0x00E */ signed char pading[2];                // 0x2
} anon_18_218;

/* anon_26_218 -- @anon26, 0xC bytes, dmm_play.c (DIE 0x3F1D39) */
typedef struct {   // size 0xC
    /* 0x000 */ int sbj_id;                           // 0x4
    /* 0x004 */ unsigned int bar_start;               // 0x4
    /* 0x008 */ unsigned int bar_end;                 // 0x4
} anon_26_218;

/* anon_28_218 -- @anon28, 0x28 bytes, dmm_play.c (DIE 0x3F20DF) */
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
} anon_28_218;

/* anon_6_218 -- @anon6, 0x14 bytes, dmm_play.c (DIE 0x3ED8B4) */
typedef struct {   // size 0x14
    /* 0x000 */ int disp_flag;                        // 0x4
    /* 0x004 */ float timer;                          // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ int a;                                // 0x4
} anon_6_218;

/* anon_1_218 -- @anon1, 0x3D7C bytes, dmm_play.c (DIE 0x3EC357) */
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
    /* 0x2A0 */ anon_27_218 swap_save_data;           // 0x1300
    /* 0x15A0 */ anon_16_218 mc_w;                    // 0x38
    /* 0x15D8 */ anon_3_218 button_disp_w;            // 0x10
    /* 0x15E8 */ anon_8_218 record_w;                 // 0x28
    /* 0x1610 */ anon_9_218 fade_env;                 // 0x10
    /* 0x1620 */ int total_record[4];                 // 0x10
    /* 0x1630 */ anon_2_218 preres[2];                // 0x38
    /* 0x1668 */ anon_22_218 result[2];               // 0x3E0
    /* 0x1A48 */ unsigned short cur_note[2];          // 0x4
    /* 0x1A4C */ short old_point[2];                  // 0x4
    /* 0x1A50 */ unsigned int subj_opt;               // 0x4
    /* 0x1A54 */ anon_12_218 style_menu;              // 0x4
    /* 0x1A58 */ anon_11_218 pad_w;                   // 0x10
    /* 0x1A68 */ anon_25_218 move_w[6];               // 0x60
    /* 0x1AC8 */ anon_15_218 ev_w;                    // 0x1AC
    /* 0x1C74 */ anon_21_218 qmenu_w;                 // 0x14
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
    /* 0x1CD0 */ anon_18_218 worldw;                  // 0x10
    /* 0x1CE0 */ anon_26_218 cha_sbj_info_w;          // 0xC
    /* 0x1CEC */ anon_26_218 sel_sbj_info_w[8];       // 0x60
    /* 0x1D4C */ anon_28_218 panel_disp_w[200];       // 0x1F40
    /* 0x3C8C */ anon_0_218 cone_disp_w[8];           // 0x60
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
    /* 0x3D54 */ anon_6_218 blind_w;                  // 0x14
    /* 0x3D68 */ int result_state;                    // 0x4
    /* 0x3D6C */ int result_cnt;                      // 0x4
    /* 0x3D70 */ int total_result_cnt;                // 0x4
    /* 0x3D74 */ int result_mask_cnt;                 // 0x4
    /* 0x3D78 */ int dummy;                           // 0x4
} anon_1_218;

/* anon_4_218 -- @anon4, 0x10 bytes, dmm_play.c (DIE 0x3ED7A8) */
typedef struct {   // size 0x10
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ int parm1;                            // 0x4
    /* 0x008 */ int parm2;                            // 0x4
    /* 0x00C */ int parm3;                            // 0x4
} anon_4_218;

/* anon_5_218 -- @anon5, 0x8 bytes, dmm_play.c (DIE 0x3ED84E) */
typedef struct {   // size 0x8
    /* 0x000 */ int beat_count;                       // 0x4
    /* 0x004 */ int dir;                              // 0x4
} anon_5_218;

/* anon_7_218 -- @anon7, 0x14 bytes, dmm_play.c (DIE 0x3ED975) */
typedef struct {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
} anon_7_218;

/* anon_10_218 -- @anon10, 0xC bytes, dmm_play.c (DIE 0x3EDFC4) */
typedef struct {   // size 0xC
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ int time;                             // 0x4
    /* 0x008 */ float rate;                           // 0x4
} anon_10_218;

/* anon_20_218 -- @anon20, 0x4 bytes, dmm_play.c (DIE 0x3F1345) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_20_218;

/* anon_23_218 -- @anon23, 0x10 bytes, dmm_play.c (DIE 0x3F181B) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_20_218 x0;                       // 0x4
    /* 0x004 */ anon_20_218 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_23_218;

/* anon_19_218 -- @anon19, 0x24 bytes, dmm_play.c (DIE 0x3F04A3) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_20_218 x0;                       // 0x4
    /* 0x004 */ anon_20_218 y0;                       // 0x4
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
} anon_19_218;


/* variables (4) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
unsigned char *edi_freeze_seq;                                   /* @0x002DE2D8 size 0x4 */
unsigned char *edi_normal_seq;                                   /* @0x002DE2DC size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */

/* functions defined (8) */
static void dmm_play_control(anon_1_218 *work);                  /* 0x007F8810-0x007F8B0C lines 980-1044 */
void dmm_play_disp(void);                                        /* 0x007F8B10-0x007F8DB8 lines 895-969 */
static void dmm_dance_play_chain(anon_1_218 *work);              /* 0x007F8DC0-0x007F9444 lines 619-886 */
static int dmm_dance_play_finish(anon_1_218 *work);              /* 0x007F9450-0x007F9520 lines 567-606 */
static int dmm_dance_play_main(anon_1_218 *work);                /* 0x007F9520-0x007F98E0 lines 386-559 */
static int dmm_dance_play_pre(anon_1_218 *work);                 /* 0x007F98E0-0x007F99F0 lines 312-377 */
static void dmm_dance_play_init(anon_1_218 *work);               /* 0x007F99F0-0x007F9BA0 lines 157-244 */
void dmm_play(anon_1_218 *work);                                 /* 0x007F9BA0-0x007F9DB4 lines 71-147 */

#endif /* DDR_UNIT_src_CS_dancemaster_dmm_play_c_H */
