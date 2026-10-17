/*
 * C:\work2\usaex2\src\CS\edit\ed_edit_disp.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00293190-0x00293CB0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_edit_ed_edit_disp_c_H
#define DDR_UNIT_src_CS_edit_ed_edit_disp_c_H

#include "types/G_SYS_W_.h"
#include "types/_tag_cCoCursor01.h"

/* anonymous types (11) */

/* anon_0_181 -- @anon0, 0x2C bytes, ed_edit_disp.c (DIE 0x32A6B6) */
typedef struct {   // size 0x2C
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float ict[9];                         // 0x24
} anon_0_181;

/* anon_1_181 -- @anon1, 0x4 bytes, ed_edit_disp.c (DIE 0x32A780) */
typedef struct {   // size 0x4
    /* 0x000 */ short pos;                            // 0x2
    /* 0x002 */ unsigned char side;                   // 0x1
    /* 0x003 */ unsigned char dmy;                    // 0x1
} anon_1_181;

/* anon_9_181 -- @anon9, 0x8 bytes, ed_edit_disp.c (DIE 0x32DAFA) */
typedef struct {   // size 0x8
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int step;                             // 0x4
} anon_9_181;

/* anon_10_181 -- @anon10, 0x3C bytes, ed_edit_disp.c (DIE 0x32DB7C) */
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
} anon_10_181;

/* anon_2_181 -- @anon2, 0x280 bytes, ed_edit_disp.c (DIE 0x32A891) */
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
    /* 0x068 */ anon_1_181 area[2];                   // 0x8
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
    /* 0x1D8 */ anon_9_181 ed_obj[2];                 // 0x10
    /* 0x1E8 */ anon_10_181 cur_w;                    // 0x3C
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
} anon_2_181;

/* anon_3_181 -- @anon3, 0x48 bytes, ed_edit_disp.c (DIE 0x32C9E2) */
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
} anon_3_181;

/* anon_6_181 -- @anon6, 0x4 bytes, ed_edit_disp.c (DIE 0x32D4D5) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_6_181;

/* anon_4_181 -- @anon4, 0x1C bytes, ed_edit_disp.c (DIE 0x32D17D) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_6_181 x0;                        // 0x4
    /* 0x004 */ anon_6_181 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_4_181;

/* anon_5_181 -- @anon5, 0x24 bytes, ed_edit_disp.c (DIE 0x32D2D5) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_6_181 x0;                        // 0x4
    /* 0x004 */ anon_6_181 y0;                        // 0x4
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
} anon_5_181;

/* anon_7_181 -- @anon7, 0x10 bytes, ed_edit_disp.c (DIE 0x32D82F) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_7_181;

/* anon_8_181 -- @anon8, 0x10 bytes, ed_edit_disp.c (DIE 0x32D9A4) */
typedef struct {   // size 0x10
    /* 0x000 */ void *lrframe_ow;                     // 0x4
    /* 0x004 */ void *seqbase_ow;                     // 0x4
    /* 0x008 */ unsigned char next_main_step;         // 0x1
    /* 0x009 */ // 0x3 bytes padding
    /* 0x00C */ int cur_icon;                         // 0x4
} anon_8_181;


/* variables (8) */
anon_7_181 ed_lrframe_objf;                                      /* @0x002C2410 size 0x10 */
static int EdIconTbl[9];                                         /* @0x002C2420 size 0x24 */
static float ny_ico_tbl_e[9];                                    /* @0x002C2450 size 0x24 */
static float *EdIconWTbl[6];                                     /* @0x002C2480 size 0x18 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
anon_8_181 *edw;                                                 /* @0x002DDE1C size 0x4 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (4) */
static int ed_lrframe_disp(void *w);                             /* 0x00293190-0x00293A88 lines 171-331 */
static int ed_lrframe_dsap(void *w);                             /* 0x00293A90-0x00293B20 lines 155-168 */
static int ed_lrframe_exec(void *w);                             /* 0x00293B20-0x00293BFC lines 136-151 */
static int ed_lrframe_appr(void *w);                             /* 0x00293C00-0x00293CB0 lines 120-134 */

#endif /* DDR_UNIT_src_CS_edit_ed_edit_disp_c_H */
