/*
 * C:\work2\usaex2\src\CS\edit_lib\el_disp_obj.c
 * MW MIPS C Compiler, overlay main; 32 functions, code 0x0028FEE0-0x00293190
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_CS_edit_lib_el_disp_obj_c_H
#define DDR_UNIT_src_CS_edit_lib_el_disp_obj_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/music_info.h"
#include "types/tex_bind.h"

/* anonymous types (23) */

/* anon_22_180 -- @anon22, 0x4 bytes, el_disp_obj.c (DIE 0x326EC4) */
typedef struct {   // size 0x4
    /* 0x000 */ short pos;                            // 0x2
    /* 0x002 */ unsigned char side;                   // 0x1
    /* 0x003 */ unsigned char dmy;                    // 0x1
} anon_22_180;

/* anon_19_180 -- @anon19, 0x8 bytes, el_disp_obj.c (DIE 0x326936) */
typedef struct {   // size 0x8
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int step;                             // 0x4
} anon_19_180;

/* anon_21_180 -- @anon21, 0x3C bytes, el_disp_obj.c (DIE 0x326C57) */
typedef struct {   // size 0x3C
    /* 0x000 */ float cur_x;                          // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float cur_sx;                         // 0x4
    /* 0x00C */ float cur_sy;                         // 0x4
    /* 0x010 */ int cur_w;                            // 0x4
    /* 0x014 */ int cur_h;                            // 0x4
    /* 0x018 */ int cur_sw;                           // 0x4
    /* 0x01C */ int cur_sh;                           // 0x4
    /* 0x020 */ unsigned char alpha;                  // 0x1
    /* 0x021 */ unsigned char s_alpha;                // 0x1
    /* 0x022 */ // 0x2 bytes padding
    /* 0x024 */ int time_x;                           // 0x4
    /* 0x028 */ int time_y;                           // 0x4
    /* 0x02C */ int time_w;                           // 0x4
    /* 0x030 */ int time_h;                           // 0x4
    /* 0x034 */ int time_a;                           // 0x4
    /* 0x038 */ unsigned int flg;                     // 0x4
} anon_21_180;

/* anon_0_180 -- @anon0, 0x280 bytes, el_disp_obj.c (DIE 0x321F26) */
typedef struct {   // size 0x280
    /* 0x000 */ unsigned char top_step;               // 0x1
    /* 0x001 */ unsigned char init_step;              // 0x1
    /* 0x002 */ unsigned char main_step;              // 0x1
    /* 0x003 */ unsigned char sub_step;               // 0x1
    /* 0x004 */ unsigned char play_step;              // 0x1
    /* 0x005 */ unsigned char fade_step;              // 0x1
    /* 0x006 */ unsigned char select_step;            // 0x1
    /* 0x007 */ unsigned char mcard_step;             // 0x1
    /* 0x008 */ unsigned char qsave_step;             // 0x1
    /* 0x009 */ unsigned char next_step;              // 0x1
    /* 0x00A */ unsigned char music_step;             // 0x1
    /* 0x00B */ unsigned char seq_init_type;          // 0x1
    /* 0x00C */ unsigned char *mes_e0_addr;           // 0x4
    /* 0x010 */ unsigned char *mes_e1_addr;           // 0x4
    /* 0x014 */ unsigned int *m_icon00_addr;          // 0x4
    /* 0x018 */ unsigned int *output_ico_addr;        // 0x4
    /* 0x01C */ unsigned int *icon_sys_addr;          // 0x4
    /* 0x020 */ int tex_id_offset;                    // 0x4
    /* 0x024 */ int tex_id_nm0;                       // 0x4
    /* 0x028 */ short ny_music_num;                   // 0x2
    /* 0x02A */ short music_num;                      // 0x2
    /* 0x02C */ char sel_music_num;                   // 0x1
    /* 0x02D */ char sel_music_num_pad;               // 0x1
    /* 0x02E */ unsigned char player;                 // 0x1
    /* 0x02F */ unsigned char level;                  // 0x1
    /* 0x030 */ unsigned char data_name[12];          // 0xC
    /* 0x03C */ unsigned char foot_num;               // 0x1
    /* 0x03D */ unsigned char foot_col;               // 0x1
    /* 0x03E */ unsigned char win_del_flg[4];         // 0x4
    /* 0x042 */ unsigned char shade_col[4];           // 0x4
    /* 0x046 */ unsigned char fade_col;               // 0x1
    /* 0x047 */ // 0x1 bytes padding
    /* 0x048 */ struct _tag_cCoCursor01 yesno_curw;   // 0xC
    /* 0x054 */ int beat_ct;                          // 0x4
    /* 0x058 */ unsigned long end_beat_ct;            // 0x8
    /* 0x060 */ unsigned long push_cont_timer;        // 0x8
    /* 0x068 */ anon_22_180 area[2];                  // 0x8
    /* 0x070 */ short area_size;                      // 0x2
    /* 0x072 */ short area_use;                       // 0x2
    /* 0x074 */ // 0x4 bytes padding
    /* 0x078 */ unsigned long cursor_col;             // 0x8
    /* 0x080 */ int mode_chng_deg;                    // 0x4
    /* 0x084 */ short note_num[2];                    // 0x4
    /* 0x088 */ short f_note_num[2];                  // 0x4
    /* 0x08C */ short cur_seq_pos;                    // 0x2
    /* 0x08E */ short scroll_ct;                      // 0x2
    /* 0x090 */ short disp_upper;                     // 0x2
    /* 0x092 */ short disp_lower;                     // 0x2
    /* 0x094 */ short f_disp_upper;                   // 0x2
    /* 0x096 */ short f_disp_lower;                   // 0x2
    /* 0x098 */ short window_ct[4];                   // 0x8
    /* 0x0A0 */ short msg_wait_ct;                    // 0x2
    /* 0x0A2 */ short mode_win_ct;                    // 0x2
    /* 0x0A4 */ short screen_deg;                     // 0x2
    /* 0x0A6 */ short disp_ct;                        // 0x2
    /* 0x0A8 */ unsigned char sel_player;             // 0x1
    /* 0x0A9 */ unsigned char sel_level;              // 0x1
    /* 0x0AA */ unsigned char first_menu_num;         // 0x1
    /* 0x0AB */ unsigned char seq_menu_num;           // 0x1
    /* 0x0AC */ unsigned char area_menu_num;          // 0x1
    /* 0x0AD */ unsigned char op_menu_num;            // 0x1
    /* 0x0AE */ unsigned char rev_menu_num;           // 0x1
    /* 0x0AF */ unsigned char quan_menu_num;          // 0x1
    /* 0x0B0 */ unsigned char rec_menu_num;           // 0x1
    /* 0x0B1 */ unsigned char move_mode;              // 0x1
    /* 0x0B2 */ unsigned char move_speed;             // 0x1
    /* 0x0B3 */ unsigned char play_type;              // 0x1
    /* 0x0B4 */ unsigned char play_repeat;            // 0x1
    /* 0x0B5 */ unsigned char play_speed;             // 0x1
    /* 0x0B6 */ unsigned char input_se;               // 0x1
    /* 0x0B7 */ unsigned char judge_type;             // 0x1
    /* 0x0B8 */ unsigned char play_bright;            // 0x1
    /* 0x0B9 */ unsigned char controller;             // 0x1
    /* 0x0BA */ unsigned char input_type;             // 0x1
    /* 0x0BB */ unsigned char bgm_type;               // 0x1
    /* 0x0BC */ unsigned char icon_exp;               // 0x1
    /* 0x0BD */ unsigned char menu_lang;              // 0x1
    /* 0x0BE */ unsigned char msg_num;                // 0x1
    /* 0x0BF */ unsigned char next_msg_num;           // 0x1
    /* 0x0C0 */ unsigned char msg_win_type;           // 0x1
    /* 0x0C1 */ unsigned char yes_no;                 // 0x1
    /* 0x0C2 */ unsigned char make_side;              // 0x1
    /* 0x0C3 */ unsigned char bar_max;                // 0x1
    /* 0x0C4 */ unsigned char zoom_mode;              // 0x1
    /* 0x0C5 */ unsigned char zoom_anime_ct;          // 0x1
    /* 0x0C6 */ unsigned char quan_anime_ct;          // 0x1
    /* 0x0C7 */ unsigned char quan_side;              // 0x1
    /* 0x0C8 */ unsigned char is_triple;              // 0x1
    /* 0x0C9 */ unsigned char tri_pos;                // 0x1
    /* 0x0CA */ unsigned char rev_act;                // 0x1
    /* 0x0CB */ unsigned char quan_act;               // 0x1
    /* 0x0CC */ unsigned char undo_num;               // 0x1
    /* 0x0CD */ unsigned char mode_chng_ct;           // 0x1
    /* 0x0CE */ unsigned char guide_num;              // 0x1
    /* 0x0CF */ unsigned char cursor_on[2];           // 0x2
    /* 0x0D1 */ unsigned char for_double;             // 0x1
    /* 0x0D2 */ unsigned char arrow_type;             // 0x1
    /* 0x0D3 */ unsigned char input_flg;              // 0x1
    /* 0x0D4 */ unsigned char mask_col;               // 0x1
    /* 0x0D5 */ unsigned char test_play_flg;          // 0x1
    /* 0x0D6 */ unsigned char top_pos;                // 0x1
    /* 0x0D7 */ // 0x1 bytes padding
    /* 0x0D8 */ short judge_note[2];                  // 0x4
    /* 0x0DC */ unsigned char j_msg_type[2];          // 0x2
    /* 0x0DE */ unsigned char j_msg_ct[2];            // 0x2
    /* 0x0E0 */ unsigned char j_arw_ct[2][4];         // 0x8
    /* 0x0E8 */ unsigned char j_arw_col;              // 0x1
    /* 0x0E9 */ unsigned char op_wait_ct;             // 0x1
    /* 0x0EA */ unsigned char bgm_flg;                // 0x1
    /* 0x0EB */ unsigned char force_end_flg;          // 0x1
    /* 0x0EC */ unsigned char input_size;             // 0x1
    /* 0x0ED */ unsigned char filter_ct;              // 0x1
    /* 0x0EE */ unsigned char reduce_rate;            // 0x1
    /* 0x0EF */ unsigned char data_disp_flg;          // 0x1
    /* 0x0F0 */ unsigned char dbl_caut_flg;           // 0x1
    /* 0x0F1 */ unsigned char adjust_bar;             // 0x1
    /* 0x0F2 */ unsigned char nameput_x;              // 0x1
    /* 0x0F3 */ unsigned char nameput_y;              // 0x1
    /* 0x0F4 */ unsigned char f_arrow_flg;            // 0x1
    /* 0x0F5 */ char guide_mes_num[9];                // 0x9
    /* 0x0FE */ unsigned char mc_step;                // 0x1
    /* 0x0FF */ // 0x1 bytes padding
    /* 0x100 */ int mc_comand;                        // 0x4
    /* 0x104 */ int herewe_count;                     // 0x4
    /* 0x108 */ float guide_move_y;                   // 0x4
    /* 0x10C */ float guide_move_y_buff;              // 0x4
    /* 0x110 */ float opt_w;                          // 0x4
    /* 0x114 */ float opt_h;                          // 0x4
    /* 0x118 */ float opt_x;                          // 0x4
    /* 0x11C */ float opt_y;                          // 0x4
    /* 0x120 */ float mes_bri;                        // 0x4
    /* 0x124 */ unsigned char guide_move_x_flg;       // 0x1
    /* 0x125 */ unsigned char sel_alpha[3];           // 0x3
    /* 0x128 */ unsigned char sel_clut_ani;           // 0x1
    /* 0x129 */ unsigned char check_loadseq;          // 0x1
    /* 0x12A */ // 0x2 bytes padding
    /* 0x12C */ float win_h;                          // 0x4
    /* 0x130 */ int play_music_wait;                  // 0x4
    /* 0x134 */ unsigned char save_check_flg;         // 0x1
    /* 0x135 */ unsigned char tmp_step;               // 0x1
    /* 0x136 */ char mc_check;                        // 0x1
    /* 0x137 */ // 0x1 bytes padding
    /* 0x138 */ int freeze_size_check[2];             // 0x8
    /* 0x140 */ unsigned char freeze_write_check;     // 0x1
    /* 0x141 */ char freeze_write_flag;               // 0x1
    /* 0x142 */ unsigned char freeze_but_flag;        // 0x1
    /* 0x143 */ unsigned char freeze_num;             // 0x1
    /* 0x144 */ unsigned char seq_buff1;              // 0x1
    /* 0x145 */ unsigned char seq_buff2;              // 0x1
    /* 0x146 */ unsigned char freeze_seq_buff1;       // 0x1
    /* 0x147 */ unsigned char freeze_seq_buff2;       // 0x1
    /* 0x148 */ char freeze_force_write;              // 0x1
    /* 0x149 */ char freeze_start_flag;               // 0x1
    /* 0x14A */ // 0x2 bytes padding
    /* 0x14C */ unsigned int n_num;                   // 0x4
    /* 0x150 */ int size;                             // 0x4
    /* 0x154 */ unsigned char fade_size;              // 0x1
    /* 0x155 */ // 0x3 bytes padding
    /* 0x158 */ float fade_size2;                     // 0x4
    /* 0x15C */ unsigned char tmp_mem;                // 0x1
    /* 0x15D */ unsigned char saveload_step;          // 0x1
    /* 0x15E */ unsigned char tmp_saveload_step;      // 0x1
    /* 0x15F */ unsigned char saveload_yes_no;        // 0x1
    /* 0x160 */ unsigned char quick_check_flg;        // 0x1
    /* 0x161 */ unsigned char quick_check_page;       // 0x1
    /* 0x162 */ unsigned char quick_check_num;        // 0x1
    /* 0x163 */ unsigned char input_freeze;           // 0x1
    /* 0x164 */ unsigned char saveload_pg;            // 0x1
    /* 0x165 */ unsigned char saveload_num;           // 0x1
    /* 0x166 */ unsigned char saveload_x;             // 0x1
    /* 0x167 */ unsigned char saveload_y;             // 0x1
    /* 0x168 */ unsigned char first_alpha;            // 0x1
    /* 0x169 */ unsigned char force_dark;             // 0x1
    /* 0x16A */ // 0x2 bytes padding
    /* 0x16C */ unsigned int lib_size;                // 0x4
    /* 0x170 */ unsigned char silent_mode;            // 0x1
    /* 0x171 */ unsigned char music_status;           // 0x1
    /* 0x172 */ unsigned char music_flg;              // 0x1
    /* 0x173 */ unsigned char mc_timer;               // 0x1
    /* 0x174 */ unsigned char event_timer;            // 0x1
    /* 0x175 */ unsigned char tex_id;                 // 0x1
    /* 0x176 */ short status_w;                       // 0x2
    /* 0x178 */ short status_h;                       // 0x2
    /* 0x17A */ char view_status;                     // 0x1
    /* 0x17B */ unsigned char final_libsize;          // 0x1
    /* 0x17C */ unsigned char status_wh;              // 0x1
    /* 0x17D */ // 0x3 bytes padding
    /* 0x180 */ float style_x[2];                     // 0x8
    /* 0x188 */ short f_check[2];                     // 0x4
    /* 0x18C */ unsigned char first_music_start;      // 0x1
    /* 0x18D */ unsigned char mc_access;              // 0x1
    /* 0x18E */ // 0x2 bytes padding
    /* 0x190 */ unsigned int input[8];                // 0x20
    /* 0x1B0 */ unsigned char input_check[8];         // 0x8
    /* 0x1B8 */ unsigned char new_check[8];           // 0x8
    /* 0x1C0 */ unsigned char pull_mc;                // 0x1
    /* 0x1C1 */ unsigned char nao_check;              // 0x1
    /* 0x1C2 */ char oni_check;                       // 0x1
    /* 0x1C3 */ // 0x1 bytes padding
    /* 0x1C4 */ int guide_item_list_alpha;            // 0x4
    /* 0x1C8 */ int guide_item_list_alpha_back;       // 0x4
    /* 0x1CC */ int prev_guide_num;                   // 0x4
    /* 0x1D0 */ int fade_guide_num;                   // 0x4
    /* 0x1D4 */ int check_guide_move;                 // 0x4
    /* 0x1D8 */ anon_19_180 ed_obj[2];                // 0x10
    /* 0x1E8 */ anon_21_180 cur_w;                    // 0x3C
    /* 0x224 */ int sel_lv_array[5];                  // 0x14
    /* 0x238 */ int sel_lv_pos;                       // 0x4
    /* 0x23C */ int sel_lv_pos_num;                   // 0x4
    /* 0x240 */ int sel_lv_cursor_anim_timer;         // 0x4
    /* 0x244 */ int total_available_music_num;        // 0x4
    /* 0x248 */ int move_sel_music;                   // 0x4
    /* 0x24C */ int move_sel_player;                  // 0x4
    /* 0x250 */ int move_sel_level;                   // 0x4
    /* 0x254 */ int sel_player_h;                     // 0x4
    /* 0x258 */ int sel_level_h;                      // 0x4
    /* 0x25C */ int sel_yesno_h;                      // 0x4
    /* 0x260 */ int push_flg;                         // 0x4
    /* 0x264 */ int push_time;                        // 0x4
    /* 0x268 */ int guide_time;                       // 0x4
    /* 0x26C */ int retry_check;                      // 0x4
    /* 0x270 */ int read_time;                        // 0x4
    /* 0x274 */ int read_flag;                        // 0x4
    /* 0x278 */ int no_read_flag;                     // 0x4
    /* 0x27C */ // 0x4 bytes padding
} anon_0_180;

/* anon_1_180 -- @anon1, 0x8 bytes, el_disp_obj.c (DIE 0x324077) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char stat;                   // 0x1
    /* 0x001 */ unsigned char second;                 // 0x1
    /* 0x002 */ unsigned char minute;                 // 0x1
    /* 0x003 */ unsigned char hour;                   // 0x1
    /* 0x004 */ unsigned char pad;                    // 0x1
    /* 0x005 */ unsigned char day;                    // 0x1
    /* 0x006 */ unsigned char month;                  // 0x1
    /* 0x007 */ unsigned char year;                   // 0x1
} anon_1_180;

/* anon_2_180 -- @anon2, 0x4 bytes, el_disp_obj.c (DIE 0x3241C7) */
typedef struct {   // size 0x4
    /* 0x000 */ int step;                             // 0x4
} anon_2_180;

/* anon_16_180 -- @anon16, 0x10 bytes, el_disp_obj.c (DIE 0x3260B7) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned char player;                 // 0x1
    /* 0x005 */ unsigned char level;                  // 0x1
    /* 0x006 */ unsigned char beat;                   // 0x1
    /* 0x007 */ unsigned char arrow_num;              // 0x1
    /* 0x008 */ short code;                           // 0x2
    /* 0x00A */ unsigned char foot_info;              // 0x1
    /* 0x00B */ unsigned char freeze_arrow;           // 0x1
    /* 0x00C */ unsigned char pad[4];                 // 0x4
} anon_16_180;

/* anon_14_180 -- @anon14, 0x2028 bytes, el_disp_obj.c (DIE 0x325EF8) */
typedef struct {   // size 0x2028
    /* 0x000 */ unsigned char page;                   // 0x1
    /* 0x001 */ unsigned char number;                 // 0x1
    /* 0x002 */ unsigned char edit_name[12];          // 0xC
    /* 0x00E */ anon_1_180 edit_time;                 // 0x8
    /* 0x016 */ // 0x2 bytes padding
    /* 0x018 */ anon_16_180 edit_header;              // 0x10
    /* 0x028 */ unsigned char edit_data[8192];        // 0x2000
} anon_14_180;

/* anon_12_180 -- @anon12, 0x3C4D0 bytes, el_disp_obj.c (DIE 0x325C5F) */
typedef struct {   // size 0x3C4D0
    /* 0x000 */ unsigned char folder_num;             // 0x1
    /* 0x001 */ unsigned char file_num;               // 0x1
    /* 0x002 */ unsigned char file_flag[30];          // 0x1E
    /* 0x020 */ anon_14_180 edit_data[30];            // 0x3C4B0
} anon_12_180;

/* anon_3_180 -- @anon3, 0x12D814 bytes, el_disp_obj.c (DIE 0x3243F1) */
typedef struct {   // size 0x12D814
    /* 0x000 */ unsigned char folder_num_max;         // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ anon_12_180 folder[5];                // 0x12D810
} anon_3_180;

/* anon_4_180 -- @anon4, 0x2 bytes, el_disp_obj.c (DIE 0x324482) */
typedef struct {   // size 0x2
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char disp_on;                // 0x1
} anon_4_180;

/* anon_5_180 -- @anon5, 0x8 bytes, el_disp_obj.c (DIE 0x3245C0) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ float t;                              // 0x4
} anon_5_180;

/* anon_6_180 -- @anon6, 0x2280 bytes, el_disp_obj.c (DIE 0x324666) */
typedef struct {   // size 0x2280
    /* 0x000 */ unsigned char is_load_only;           // 0x1
    /* 0x001 */ unsigned char is_change_name;         // 0x1
    /* 0x002 */ unsigned char name_buff[9];           // 0x9
    /* 0x00B */ unsigned char nameset_menu;           // 0x1
    /* 0x00C */ unsigned char nameset_x;              // 0x1
    /* 0x00D */ unsigned char nameset_y;              // 0x1
    /* 0x00E */ unsigned char nameset_num;            // 0x1
    /* 0x00F */ // 0x1 bytes padding
    /* 0x010 */ float menu_w;                         // 0x4
    /* 0x014 */ float menu_h;                         // 0x4
    /* 0x018 */ float icon_w;                         // 0x4
    /* 0x01C */ float icon_h;                         // 0x4
    /* 0x020 */ int check_status;                     // 0x4
    /* 0x024 */ unsigned char saveload_alpha;         // 0x1
    /* 0x025 */ unsigned char el_sub_step;            // 0x1
    /* 0x026 */ unsigned char main_step;              // 0x1
    /* 0x027 */ unsigned char el_type;                // 0x1
    /* 0x028 */ unsigned char menu_step;              // 0x1
    /* 0x029 */ unsigned char lib_step;               // 0x1
    /* 0x02A */ unsigned char lib_check_step;         // 0x1
    /* 0x02B */ unsigned char lib_check_status;       // 0x1
    /* 0x02C */ unsigned char out_step;               // 0x1
    /* 0x02D */ unsigned char file_step;              // 0x1
    /* 0x02E */ unsigned char page_step;              // 0x1
    /* 0x02F */ unsigned char yes_no;                 // 0x1
    /* 0x030 */ unsigned char after_load;             // 0x1
    /* 0x031 */ unsigned char mc_check_timer;         // 0x1
    /* 0x032 */ unsigned char check_libmc2;           // 0x1
    /* 0x033 */ unsigned char lib_menu_num;           // 0x1
    /* 0x034 */ unsigned char page_num;               // 0x1
    /* 0x035 */ unsigned char new_file_num;           // 0x1
    /* 0x036 */ unsigned char page_num_max_all;       // 0x1
    /* 0x037 */ unsigned char file_num[5];            // 0x5
    /* 0x03C */ unsigned char sel_status;             // 0x1
    /* 0x03D */ unsigned char editlib_alpha;          // 0x1
    /* 0x03E */ unsigned char status_flg;             // 0x1
    /* 0x03F */ unsigned char f0_pg;                  // 0x1
    /* 0x040 */ unsigned char f0_num;                 // 0x1
    /* 0x041 */ unsigned char f0_x;                   // 0x1
    /* 0x042 */ unsigned char f0_y;                   // 0x1
    /* 0x043 */ // 0x1 bytes padding
    /* 0x044 */ unsigned int f0_allnum;               // 0x4
    /* 0x048 */ unsigned char f1_pg;                  // 0x1
    /* 0x049 */ unsigned char f1_num;                 // 0x1
    /* 0x04A */ unsigned char f1_x;                   // 0x1
    /* 0x04B */ unsigned char f1_y;                   // 0x1
    /* 0x04C */ unsigned int f1_allnum;               // 0x4
    /* 0x050 */ unsigned char first_status;           // 0x1
    /* 0x051 */ unsigned char second_status;          // 0x1
    /* 0x052 */ unsigned char file_name[20];          // 0x14
    /* 0x066 */ unsigned char error_count;            // 0x1
    /* 0x067 */ unsigned char error_kind;             // 0x1
    /* 0x068 */ unsigned char out_mc_step;            // 0x1
    /* 0x069 */ unsigned char out_mc_comand;          // 0x1
    /* 0x06A */ unsigned char out_first_step;         // 0x1
    /* 0x06B */ unsigned char out_main_step;          // 0x1
    /* 0x06C */ unsigned char out_menu_step;          // 0x1
    /* 0x06D */ unsigned char tmp_out_menu_step;      // 0x1
    /* 0x06E */ unsigned char out_x;                  // 0x1
    /* 0x06F */ unsigned char out_y;                  // 0x1
    /* 0x070 */ unsigned char buff_file_num;          // 0x1
    /* 0x071 */ // 0x3 bytes padding
    /* 0x074 */ unsigned int out_file_max_mc;         // 0x4
    /* 0x078 */ unsigned int out_page_max_mc;         // 0x4
    /* 0x07C */ unsigned int out_page_mc;             // 0x4
    /* 0x080 */ unsigned char out_file_name[12];      // 0xC
    /* 0x08C */ unsigned short out_file_size;         // 0x2
    /* 0x08E */ // 0x2 bytes padding
    /* 0x090 */ unsigned char tmp_edit_data[8192] __attribute__((aligned(16)));  // 0x2000
    /* 0x2090 */ unsigned char read_flg;              // 0x1
    /* 0x2091 */ unsigned char disp_check_flg;        // 0x1
    /* 0x2092 */ unsigned char out_file_player;       // 0x1
    /* 0x2093 */ unsigned char out_file_freeze;       // 0x1
    /* 0x2094 */ short out_file_code;                 // 0x2
    /* 0x2096 */ unsigned char input_step;            // 0x1
    /* 0x2097 */ char out_file_list[20][9];           // 0xB4
    /* 0x214B */ char out_file_list_old[20][9];       // 0xB4
    /* 0x21FF */ unsigned char old_file_buff;         // 0x1
    /* 0x2200 */ int old_page_num;                    // 0x4
    /* 0x2204 */ unsigned int out_file_list_size[20];  // 0x50
    /* 0x2254 */ unsigned char tmp_file_name[16];     // 0x10
    /* 0x2264 */ char output_status;                  // 0x1
    /* 0x2265 */ char input_status;                   // 0x1
    /* 0x2266 */ unsigned char output_step;           // 0x1
    /* 0x2267 */ unsigned char out_name_flg;          // 0x1
    /* 0x2268 */ unsigned char rename_step;           // 0x1
    /* 0x2269 */ unsigned char win_ct;                // 0x1
    /* 0x226A */ unsigned char bright_rgb;            // 0x1
    /* 0x226B */ unsigned char bright_rgb2;           // 0x1
    /* 0x226C */ unsigned char mes_win_h;             // 0x1
    /* 0x226D */ unsigned char rename_status;         // 0x1
    /* 0x226E */ char change_status;                  // 0x1
    /* 0x226F */ unsigned char delete_filename[12];   // 0xC
    /* 0x227B */ unsigned char out_mes_check;         // 0x1
    /* 0x227C */ float zoom;                          // 0x4
} anon_6_180;

/* anon_7_180 -- @anon7, 0xB4 bytes, el_disp_obj.c (DIE 0x325564) */
typedef struct {   // size 0xB4
    /* 0x000 */ unsigned char step[30];               // 0x1E
    /* 0x01E */ unsigned char is_disp[30];            // 0x1E
    /* 0x03C */ float t[30];                          // 0x78
} anon_7_180;

/* anon_8_180 -- @anon8, 0x48 bytes, el_disp_obj.c (DIE 0x325610) */
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
} anon_8_180;

/* anon_9_180 -- @anon9, 0x8 bytes, el_disp_obj.c (DIE 0x325922) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ float t;                              // 0x4
} anon_9_180;

/* anon_10_180 -- @anon10, 0x8 bytes, el_disp_obj.c (DIE 0x3259EC) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ float t;                              // 0x4
} anon_10_180;

/* anon_17_180 -- @anon17, 0x4 bytes, el_disp_obj.c (DIE 0x326593) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_17_180;

/* anon_11_180 -- @anon11, 0x1C bytes, el_disp_obj.c (DIE 0x325A98) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_17_180 x0;                       // 0x4
    /* 0x004 */ anon_17_180 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_11_180;

/* anon_13_180 -- @anon13, 0x24 bytes, el_disp_obj.c (DIE 0x325D3F) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_17_180 x0;                       // 0x4
    /* 0x004 */ anon_17_180 y0;                       // 0x4
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
} anon_13_180;

/* anon_15_180 -- @anon15, 0x10 bytes, el_disp_obj.c (DIE 0x325FFE) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_15_180;

/* anon_18_180 -- @anon18, 0x30 bytes, el_disp_obj.c (DIE 0x3266AA) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_17_180 x0;                       // 0x4
    /* 0x004 */ anon_17_180 y0;                       // 0x4
    /* 0x008 */ anon_17_180 x1;                       // 0x4
    /* 0x00C */ anon_17_180 y1;                       // 0x4
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
} anon_18_180;

/* anon_20_180 -- @anon20, 0x34 bytes, el_disp_obj.c (DIE 0x326995) */
typedef struct {   // size 0x34
    /* 0x000 */ void *leftbase_ow;                    // 0x4
    /* 0x004 */ void *list_ow;                        // 0x4
    /* 0x008 */ void *foldermenu_ow;                  // 0x4
    /* 0x00C */ void *mpanel_ow;                      // 0x4
    /* 0x010 */ void *newfolder_ow;                   // 0x4
    /* 0x014 */ void *yesno_ow;                       // 0x4
    /* 0x018 */ struct _tag_cCoCursor01 curw;         // 0xC
    /* 0x024 */ unsigned char mode;                   // 0x1
    /* 0x025 */ unsigned char cur_where;              // 0x1
    /* 0x026 */ unsigned char is_decide;              // 0x1
    /* 0x027 */ unsigned char next_step;              // 0x1
    /* 0x028 */ unsigned char filemenu_step;          // 0x1
    /* 0x029 */ char filemenu_cur;                    // 0x1
    /* 0x02A */ unsigned char filemenu_stat;          // 0x1
    /* 0x02B */ unsigned char is_unable[7];           // 0x7
    /* 0x032 */ unsigned char yesno_step;             // 0x1
    /* 0x033 */ // 0x1 bytes padding
} anon_20_180;


/* variables (15) */
static anon_20_180 *eldw;                                        /* @0x002DDE44 size 0x4 */
anon_15_180 el_leftbase_objf;                                    /* @0x002C22A0 size 0x10 */
anon_15_180 el_filelist_objf;                                    /* @0x002C22B0 size 0x10 */
anon_15_180 el_folder_menu_objf;                                 /* @0x002C22C0 size 0x10 */
anon_15_180 el_main_panel_objf;                                  /* @0x002C22D0 size 0x10 */
anon_15_180 el_new_folder_objf;                                  /* @0x002C22E0 size 0x10 */
anon_15_180 el_yesno_objf;                                       /* @0x002C22F0 size 0x10 */
static unsigned char *el_filemenu_str[9];                        /* @0x002C2310 size 0x24 */
static int el_filemenu_table[3][7];                              /* @0x002C2340 size 0x54 */
int sel_yesno;                                                   /* @0x002DE594 size 0x4 */
unsigned int edit_joy_trg;                                       /* @0x002DE408 size 0x4 */
unsigned int edit_joy_rep;                                       /* @0x002DE400 size 0x4 */
static anon_20_180 el_disp_w;                                    /* @0x007236B0 size 0x34 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (32) */
int el_exec_select_yesno(int *result);                           /* 0x0028FEE0-0x0028FF84 lines 2039-2057 */
static int el_yesno_disp(void);                                  /* 0x0028FF90-0x002900A0 lines 1893-1934 */
static int el_yesno_dsap(void);                                  /* 0x002900A0-0x002900D4 lines 1885-1890 */
static int el_yesno_exec(void *w);                               /* 0x002900E0-0x00290134 lines 1872-1883 */
static int el_yesno_appr(void *w);                               /* 0x00290140-0x002901A8 lines 1854-1870 */
static int el_new_folder_disp(void *w);                          /* 0x002901B0-0x0029025C lines 1656-1672 */
static int el_new_folder_dsap(void *w);                          /* 0x00290260-0x002902F0 lines 1639-1653 */
static int el_new_folder_exec(void);                             /* 0x002902F0-0x002902F8 lines 1633-1633 */
static int el_new_folder_appr(void *w);                          /* 0x00290300-0x00290390 lines 1614-1628 */
static void el_disp_music_info(float x, float y, int z);         /* 0x00290390-0x002907E8 lines 1460-1595 */
static void el_disp_message_all(float y0);                       /* 0x002907F0-0x00290AD0 lines 1349-1449 */
static int el_main_panel_disp(void *w);                          /* 0x00290AD0-0x002910EC lines 1208-1342 */
static int el_main_panel_dsap(void *w);                          /* 0x002910F0-0x00291180 lines 1191-1205 */
static int el_main_panel_exec(void);                             /* 0x00291180-0x00291188 lines 1185-1185 */
static int el_main_panel_appr(void *w);                          /* 0x00291190-0x00291220 lines 1166-1180 */
static int el_folder_menu_disp(void *w);                         /* 0x00291220-0x002918E4 lines 1029-1145 */
static int el_folder_menu_dsap(void *w);                         /* 0x002918F0-0x00291980 lines 1011-1025 */
static int el_folder_menu_exec(void);                            /* 0x00291980-0x00291988 lines 1006-1006 */
static int el_folder_menu_appr(void *w);                         /* 0x00291990-0x00291A20 lines 987-1001 */
static int el_filelist_disp(void *w);                            /* 0x00291A20-0x0029200C lines 865-970 */
static int el_filelist_dsap(void *w);                            /* 0x00292010-0x00292178 lines 832-862 */
static int el_filelist_exec(void);                               /* 0x00292180-0x00292188 lines 826-826 */
static int el_filelist_appr(void *w);                            /* 0x00292190-0x00292318 lines 786-821 */
static int el_leftbase_disp(void);                               /* 0x00292320-0x00292328 lines 763-763 */
static int el_leftbase_dsap(void *w);                            /* 0x00292330-0x00292398 lines 737-747 */
static int el_leftbase_exec(void);                               /* 0x002923A0-0x002923A8 lines 734-734 */
static int el_leftbase_appr(void);                               /* 0x002923B0-0x002923FC lines 721-729 */
static void el_disp_message(float y0, int z, int kind, int sub_id); /* 0x00292400-0x002924E8 lines 688-709 */
static void el_filemenu_disp(void);                              /* 0x002924F0-0x002926F0 lines 640-675 */
static void el_filemenu_init(void);                              /* 0x002926F0-0x0029287C lines 587-637 */
int el_filemenu_main(int cur_step);                              /* 0x00292880-0x00292E80 lines 329-582 */
int el_disp_control(int type);                                   /* 0x00292E80-0x00293190 lines 185-268 */

#endif /* DDR_UNIT_src_CS_edit_lib_el_disp_obj_c_H */
