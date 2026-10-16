/*
 * C:\work2\usaex2\src\CS\edit\ed_select.c
 * MW MIPS C Compiler, overlay main; 23 functions, code 0x0028ABC0-0x0028CFB0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_edit_ed_select_c_H
#define DDR_UNIT_src_CS_edit_ed_select_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/music_info.h"
#include "types/tex_bind.h"

/* anonymous types (29) */

/* anon_0_177 -- @anon0, 0x3C bytes, ed_select.c (DIE 0x31219D) */
struct anon_0_177 {   // size 0x3C
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
};

/* anon_1_177 -- @anon1, 0x4 bytes, ed_select.c (DIE 0x3123E5) */
struct anon_1_177 {   // size 0x4
    /* 0x000 */ short pos;                            // 0x2
    /* 0x002 */ unsigned char side;                   // 0x1
    /* 0x003 */ unsigned char dmy;                    // 0x1
};

/* anon_2_177 -- @anon2, 0xC bytes, ed_select.c (DIE 0x312465) */
struct anon_2_177 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
};

/* anon_3_177 -- @anon3, 0x8 bytes, ed_select.c (DIE 0x31250E) */
struct anon_3_177 {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
};

/* anon_4_177 -- @anon4, 0x30 bytes, ed_select.c (DIE 0x312591) */
struct anon_4_177 {   // size 0x30
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
    /* 0x008 */ float ct2;                            // 0x4
    /* 0x00C */ struct _tag_cCoCursor01 curw[3];      // 0x24
};

/* anon_5_177 -- @anon5, 0x48 bytes, ed_select.c (DIE 0x312633) */
struct anon_5_177 {   // size 0x48
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

/* anon_28_177 -- @anon28, 0x8 bytes, ed_select.c (DIE 0x317812) */
struct anon_28_177 {   // size 0x8
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int step;                             // 0x4
};

/* anon_6_177 -- @anon6, 0x280 bytes, ed_select.c (DIE 0x3128B5) */
struct anon_6_177 {   // size 0x280
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
    /* 0x068 */ struct anon_1_177 area[2];            // 0x8
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
    /* 0x1D8 */ struct anon_28_177 ed_obj[2];         // 0x10
    /* 0x1E8 */ struct anon_0_177 cur_w;              // 0x3C
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
};

/* anon_7_177 -- @anon7, 0x494 bytes, ed_select.c (DIE 0x314A99) */
struct anon_7_177 {   // size 0x494
    /* 0x000 */ float ftimer;                         // 0x4
    /* 0x004 */ float repcnt;                         // 0x4
    /* 0x008 */ float scr_sp;                         // 0x4
    /* 0x00C */ float scr_ct;                         // 0x4
    /* 0x010 */ unsigned int lr_obj_id;               // 0x4
    /* 0x014 */ void *lr;                             // 0x4
    /* 0x018 */ void *ud;                             // 0x4
    /* 0x01C */ void *radar;                          // 0x4
    /* 0x020 */ void *entry;                          // 0x4
    /* 0x024 */ void *base;                           // 0x4
    /* 0x028 */ void *sort_obj;                       // 0x4
    /* 0x02C */ void *scr;                            // 0x4
    /* 0x030 */ void *opt;                            // 0x4
    /* 0x034 */ void *edmc;                           // 0x4
    /* 0x038 */ unsigned char *th_up_addr;            // 0x4
    /* 0x03C */ unsigned char *th_dw_addr;            // 0x4
    /* 0x040 */ unsigned char ud_start;               // 0x1
    /* 0x041 */ unsigned char ud_end;                 // 0x1
    /* 0x042 */ unsigned char cur_ud[2];              // 0x2
    /* 0x044 */ unsigned char cur_ud_old[2];          // 0x2
    /* 0x046 */ unsigned char cur_ud_edi_old[2];      // 0x2
    /* 0x048 */ short cur_lr;                         // 0x2
    /* 0x04A */ short old_d_num;                      // 0x2
    /* 0x04C */ short old_lr;                         // 0x2
    /* 0x04E */ short ena_num;                        // 0x2
    /* 0x050 */ short sel_tab[128];                   // 0x100
    /* 0x150 */ short base_num;                       // 0x2
    /* 0x152 */ short base_tab[250];                  // 0x1F4
    /* 0x346 */ short kind_key[50];                   // 0x64
    /* 0x3AA */ short kind_ofs[50];                   // 0x64
    /* 0x40E */ short kind_len[50];                   // 0x64
    /* 0x472 */ short abc_open;                       // 0x2
    /* 0x474 */ unsigned char edit_sel;               // 0x1
    /* 0x475 */ unsigned char sort;                   // 0x1
    /* 0x476 */ unsigned char step;                   // 0x1
    /* 0x477 */ unsigned char rlt_stop_mode;          // 0x1
    /* 0x478 */ unsigned char rlt_turn_num;           // 0x1
    /* 0x479 */ unsigned char rlt_remain;             // 0x1
    /* 0x47A */ // 0x2 bytes padding
    /* 0x47C */ float rlt_t;                          // 0x4
    /* 0x480 */ float rlt_wait;                       // 0x4
    /* 0x484 */ char mcard_type;                      // 0x1
    /* 0x485 */ char msg_id;                          // 0x1
    /* 0x486 */ char yesno;                           // 0x1
    /* 0x487 */ char lib_num;                         // 0x1
    /* 0x488 */ char lib_sel_num;                     // 0x1
    /* 0x489 */ unsigned char lib_loaded;             // 0x1
    /* 0x48A */ short edi_start;                      // 0x2
    /* 0x48C */ unsigned char sn_f;                   // 0x1
    /* 0x48D */ // 0x3 bytes padding
    /* 0x490 */ float sn_t;                           // 0x4
};

/* anon_8_177 -- @anon8, 0x48 bytes, ed_select.c (DIE 0x3151F4) */
struct anon_8_177 {   // size 0x48
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step_s;                           // 0x4
    /* 0x008 */ int next_step;                        // 0x4
    /* 0x00C */ int cur_kind;                         // 0x4
    /* 0x010 */ int cur_item[3];                      // 0xC
    /* 0x01C */ int item_num_table[3];                // 0xC
    /* 0x028 */ struct music_info *cur_mip;           // 0x4
    /* 0x02C */ int next_flag;                        // 0x4
    /* 0x030 */ int back_flag;                        // 0x4
    /* 0x034 */ void *leftbase_ow;                    // 0x4
    /* 0x038 */ void *footmark_ow;                    // 0x4
    /* 0x03C */ void *banner_ow;                      // 0x4
    /* 0x040 */ void *upitem_ow;                      // 0x4
    /* 0x044 */ void *mainitem_ow;                    // 0x4
};

/* anon_9_177 -- @anon9, 0xC bytes, ed_select.c (DIE 0x315462) */
struct anon_9_177 {   // size 0xC
    /* 0x000 */ struct anon_10_177 *data;             // 0x4
    /* 0x004 */ int vertex_num;                       // 0x4
    /* 0x008 */ int flg;                              // 0x4
};

/* anon_15_177 -- @anon15, 0x4 bytes, ed_select.c (DIE 0x315BD2) */
union anon_15_177 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_10_177 -- @anon10, 0x10 bytes, ed_select.c (DIE 0x3154EE) */
struct anon_10_177 {   // size 0x10
    /* 0x000 */ union anon_15_177 x0;                 // 0x4
    /* 0x004 */ union anon_15_177 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_11_177 -- @anon11, 0x8 bytes, ed_select.c (DIE 0x3155EB) */
struct anon_11_177 {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
};

/* anon_12_177 -- @anon12, 0x4 bytes, ed_select.c (DIE 0x31566F) */
struct anon_12_177 {   // size 0x4
    /* 0x000 */ int step;                             // 0x4
};

/* anon_13_177 -- @anon13, 0x1C bytes, ed_select.c (DIE 0x3156B0) */
struct anon_13_177 {   // size 0x1C
    /* 0x000 */ union anon_15_177 x0;                 // 0x4
    /* 0x004 */ union anon_15_177 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_14_177 -- @anon14, 0x24 bytes, ed_select.c (DIE 0x315853) */
struct anon_14_177 {   // size 0x24
    /* 0x000 */ union anon_15_177 x0;                 // 0x4
    /* 0x004 */ union anon_15_177 y0;                 // 0x4
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

/* anon_16_177 -- @anon16, 0x30 bytes, ed_select.c (DIE 0x315C9C) */
struct anon_16_177 {   // size 0x30
    /* 0x000 */ union anon_15_177 x0;                 // 0x4
    /* 0x004 */ union anon_15_177 y0;                 // 0x4
    /* 0x008 */ union anon_15_177 x1;                 // 0x4
    /* 0x00C */ union anon_15_177 y1;                 // 0x4
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

/* anon_17_177 -- @anon17, 0x8 bytes, ed_select.c (DIE 0x315EDA) */
struct anon_17_177 {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
};

/* anon_20_177 -- @anon20, 0x90 bytes, ed_select.c (DIE 0x31668F) */
struct anon_20_177 {   // size 0x90
    /* 0x000 */ void *loadaddr;                       // 0x4
    /* 0x004 */ int doll_p_counter;                   // 0x4
    /* 0x008 */ unsigned char max;                    // 0x1
    /* 0x009 */ unsigned char fpanel_max;             // 0x1
    /* 0x00A */ unsigned char step;                   // 0x1
    /* 0x00B */ unsigned char dancing;                // 0x1
    /* 0x00C */ unsigned char cur[2];                 // 0x2
    /* 0x00E */ // 0x2 bytes padding
    /* 0x010 */ float fpanel_x[2];                    // 0x8
    /* 0x018 */ float fpanel_y[2];                    // 0x8
    /* 0x020 */ float cx[3];                          // 0xC
    /* 0x02C */ float cy[3];                          // 0xC
    /* 0x038 */ float cz[3];                          // 0xC
    /* 0x044 */ float adj_y[3];                       // 0xC
    /* 0x050 */ float timer;                          // 0x4
    /* 0x054 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x060 */ float cam_p[4];                       // 0x10
    /* 0x070 */ float eye_p[4];                       // 0x10
    /* 0x080 */ void *fpanel;                         // 0x4
    /* 0x084 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_23_177 -- @anon23, 0xC bytes, ed_select.c (DIE 0x316DAC) */
struct anon_23_177 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
};

/* anon_27_177 -- @anon27, 0x1C bytes, ed_select.c (DIE 0x317566) */
struct anon_27_177 {   // size 0x1C
    /* 0x000 */ unsigned char end_num;                // 0x1
    /* 0x001 */ unsigned char decide;                 // 0x1
    /* 0x002 */ unsigned char cancel;                 // 0x1
    /* 0x003 */ unsigned char cur[2];                 // 0x2
    /* 0x005 */ unsigned char rand_id[2];             // 0x2
    /* 0x007 */ // 0x1 bytes padding
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ int timer;                            // 0x4
    /* 0x014 */ void *item;                           // 0x4
    /* 0x018 */ void *entry;                          // 0x4
};

/* anon_19_177 -- @anon19, 0x70 bytes, ed_select.c (DIE 0x31647A) */
struct anon_19_177 {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ struct anon_17_177 one[11];           // 0x58
};

/* anon_24_177 -- @anon24, 0x34 bytes, ed_select.c (DIE 0x316E76) */
struct anon_24_177 {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
};

/* anon_25_177 -- @anon25, 0xA0 bytes, ed_select.c (DIE 0x3170DD) */
struct anon_25_177 {   // size 0xA0
    /* 0x000 */ float ftimer;                         // 0x4
    /* 0x004 */ void *base;                           // 0x4
    /* 0x008 */ void *value;                          // 0x4
    /* 0x00C */ void *point;                          // 0x4
    /* 0x010 */ void *score;                          // 0x4
    /* 0x014 */ void *btn;                            // 0x4
    /* 0x018 */ unsigned char *th_addr;               // 0x4
    /* 0x01C */ int total_pnt;                        // 0x4
    /* 0x020 */ int vo_code;                          // 0x4
    /* 0x024 */ short d_num;                          // 0x2
    /* 0x026 */ unsigned char push[2];                // 0x2
    /* 0x028 */ unsigned char edi_str[11];            // 0xB
    /* 0x033 */ unsigned char cheer;                  // 0x1
    /* 0x034 */ unsigned char vo_pid;                 // 0x1
    /* 0x035 */ // 0x3 bytes padding
    /* 0x038 */ struct anon_24_177 eva[2];            // 0x68
};

/* anon_18_177 -- @anon18, 0x7E0 bytes, ed_select.c (DIE 0x316036) */
struct anon_18_177 {   // size 0x7E0
    /* 0x000 */ float wsm[4][4];                      // 0x40
    /* 0x040 */ unsigned char step;                   // 0x1
    /* 0x041 */ unsigned char step_s;                 // 0x1
    /* 0x042 */ unsigned char next_step;              // 0x1
    /* 0x043 */ unsigned char qm_step;                // 0x1
    /* 0x044 */ unsigned char pad_type;               // 0x1
    /* 0x045 */ // 0x3 bytes padding
    /* 0x048 */ float fade_ct;                        // 0x4
    /* 0x04C */ int fade_kind;                        // 0x4
    /* 0x050 */ int tex_start;                        // 0x4
    /* 0x054 */ float quit_ct;                        // 0x4
    /* 0x058 */ unsigned char eye_step;               // 0x1
    /* 0x059 */ unsigned char fade_step;              // 0x1
    /* 0x05A */ unsigned char dp_alpha;               // 0x1
    /* 0x05B */ unsigned char start_pid;              // 0x1
    /* 0x05C */ unsigned char prev_step;              // 0x1
    /* 0x05D */ // 0x3 bytes padding
    /* 0x060 */ unsigned int flag;                    // 0x4
    /* 0x064 */ void *btn;                            // 0x4
    /* 0x068 */ unsigned int btn_obj_id;              // 0x4
    /* 0x06C */ unsigned char *str_addr;              // 0x4
    /* 0x070 */ unsigned char str_buf[256];           // 0x100
    /* 0x170 */ struct anon_20_177 doll;              // 0x90
    /* 0x200 */ struct anon_2_177 eyetoy;             // 0xC
    /* 0x20C */ struct anon_23_177 style;             // 0xC
    /* 0x218 */ struct anon_27_177 chara;             // 0x1C
    /* 0x234 */ struct anon_7_177 music;              // 0x494
    /* 0x6C8 */ struct anon_19_177 option;            // 0x70
    /* 0x738 */ struct anon_25_177 result;            // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_21_177 -- @anon21, 0x8 bytes, ed_select.c (DIE 0x316B57) */
struct anon_21_177 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_22_177 -- @anon22, 0x4 bytes, ed_select.c (DIE 0x316D13) */
struct anon_22_177 {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
};

/* anon_26_177 -- @anon26, 0x10 bytes, ed_select.c (DIE 0x3173A9) */
struct anon_26_177 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};


/* variables (15) */
static struct anon_8_177 *sw;                                    /* @0x002DDE24 size 0x4 */
static int diff_table[5];                                        /* @0x002C1E10 size 0x14 */
static int mess_table[4];                                        /* @0x002C1E30 size 0x10 */
struct anon_26_177 edit_sel_leftbase_objf;                       /* @0x002C1E40 size 0x10 */
struct anon_26_177 edit_sel_footmark_objf;                       /* @0x002C1E50 size 0x10 */
struct anon_26_177 edit_sel_upitem_objf;                         /* @0x002C1E60 size 0x10 */
struct anon_26_177 edit_sel_mainitem_objf;                       /* @0x002C1E70 size 0x10 */
struct anon_26_177 fp_ms_objf[];                                 /* @0x002BEA80 */
unsigned int edit_joy_rep;                                       /* @0x002DE400 size 0x4 */
unsigned int edit_joy_trg;                                       /* @0x002DE408 size 0x4 */
struct anon_7_177 *msw;                                          /* @0x002DE52C size 0x4 */
struct anon_18_177 *fpw;                                         /* @0x002DE540 size 0x4 */
static struct anon_8_177 ed_sel_w;                               /* @0x007235C0 size 0x48 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (23) */
static int edit_sel_mainitem_disp(void *w);                      /* 0x0028ABC0-0x0028AD98 lines 987-1030 */
static void edit_sel_disp_item_sub(struct anon_4_177 *miw);      /* 0x0028ADA0-0x0028B560 lines 893-984 */
static void edit_sel_disp_winbar(float x, float y);              /* 0x0028B560-0x0028B6E0 lines 864-890 */
static int edit_sel_mainitem_dsap(void *w);                      /* 0x0028B6E0-0x0028B728 lines 848-854 */
static int edit_sel_mainitem_exec(void *w);                      /* 0x0028B730-0x0028B820 lines 824-843 */
static int edit_sel_mainitem_appr(void *w);                      /* 0x0028B820-0x0028B874 lines 810-819 */
static int edit_sel_upitem_disp(void *w);                        /* 0x0028B880-0x0028BD64 lines 719-797 */
static int edit_sel_upitem_dsap(void *w);                        /* 0x0028BD70-0x0028BDB8 lines 709-715 */
static int edit_sel_upitem_exec(void *w);                        /* 0x0028BDC0-0x0028BDF8 lines 699-704 */
static int edit_sel_upitem_appr(void *w);                        /* 0x0028BE00-0x0028BE0C lines 693-695 */
static int edit_sel_footmark_disp(void *w);                      /* 0x0028BE10-0x0028C32C lines 576-673 */
static int edit_sel_footmark_dsap(void *w);                      /* 0x0028C330-0x0028C378 lines 567-573 */
static int edit_sel_footmark_exec(void *w);                      /* 0x0028C380-0x0028C3B8 lines 557-562 */
static int edit_sel_footmark_appr(void *w);                      /* 0x0028C3C0-0x0028C3CC lines 550-552 */
static int edit_sel_leftbase_disp(void);                         /* 0x0028C3D0-0x0028C3D8 lines 537-537 */
static int edit_sel_leftbase_dsap(void *w);                      /* 0x0028C3E0-0x0028C468 lines 521-533 */
static int edit_sel_leftbase_exec(void);                         /* 0x0028C470-0x0028C478 lines 518-518 */
static int edit_sel_leftbase_appr(void);                         /* 0x0028C480-0x0028C4CC lines 508-513 */
static int ed_select_items(void);                                /* 0x0028C4D0-0x0028CA34 lines 401-496 */
static int ed_select_music(void);                                /* 0x0028CA40-0x0028CC7C lines 329-397 */
void ed_select_fini(void);                                       /* 0x0028CC80-0x0028CC88 lines 323-323 */
int ed_select_step(void);                                        /* 0x0028CC90-0x0028CDD0 lines 273-319 */
void ed_select_init(void);                                       /* 0x0028CDD0-0x0028CFB0 lines 165-269 */

#endif /* DDR_UNIT_src_CS_edit_ed_select_c_H */
