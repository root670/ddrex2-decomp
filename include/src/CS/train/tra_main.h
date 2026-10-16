/*
 * C:\work2\usaex2\src\CS\train\tra_main.c
 * MW MIPS C Compiler, overlay main; 17 functions, code 0x00276520-0x00277E38
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_train_tra_main_c_H
#define DDR_UNIT_src_CS_train_tra_main_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cFilepackData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (32) */

/* anon_0_154 -- @anon0, 0x8 bytes, tra_main.c (DIE 0x2AD031) */
struct anon_0_154 {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
};

/* anon_1_154 -- @anon1, 0x8 bytes, tra_main.c (DIE 0x2AD342) */
struct anon_1_154 {   // size 0x8
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ unsigned char kind;                   // 0x1
    /* 0x005 */ unsigned char style;                  // 0x1
    /* 0x006 */ unsigned char level;                  // 0x1
    /* 0x007 */ // 0x1 bytes padding
};

/* anon_5_154 -- @anon5, 0x90 bytes, tra_main.c (DIE 0x2AFEA0) */
struct anon_5_154 {   // size 0x90
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

/* anon_6_154 -- @anon6, 0xC bytes, tra_main.c (DIE 0x2B07EA) */
struct anon_6_154 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
};

/* anon_7_154 -- @anon7, 0xC bytes, tra_main.c (DIE 0x2B0971) */
struct anon_7_154 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
};

/* anon_9_154 -- @anon9, 0x1C bytes, tra_main.c (DIE 0x2B0B5B) */
struct anon_9_154 {   // size 0x1C
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

/* anon_10_154 -- @anon10, 0x494 bytes, tra_main.c (DIE 0x2B0ECE) */
struct anon_10_154 {   // size 0x494
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

/* anon_3_154 -- @anon3, 0x70 bytes, tra_main.c (DIE 0x2AEA03) */
struct anon_3_154 {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ struct anon_0_154 one[11];            // 0x58
};

/* anon_16_154 -- @anon16, 0x34 bytes, tra_main.c (DIE 0x2B26B8) */
struct anon_16_154 {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
};

/* anon_13_154 -- @anon13, 0xA0 bytes, tra_main.c (DIE 0x2B1EC7) */
struct anon_13_154 {   // size 0xA0
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
    /* 0x038 */ struct anon_16_154 eva[2];            // 0x68
};

/* anon_2_154 -- @anon2, 0x7E0 bytes, tra_main.c (DIE 0x2AD51C) */
struct anon_2_154 {   // size 0x7E0
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
    /* 0x170 */ struct anon_5_154 doll;               // 0x90
    /* 0x200 */ struct anon_6_154 eyetoy;             // 0xC
    /* 0x20C */ struct anon_7_154 style;              // 0xC
    /* 0x218 */ struct anon_9_154 chara;              // 0x1C
    /* 0x234 */ struct anon_10_154 music;             // 0x494
    /* 0x6C8 */ struct anon_3_154 option;             // 0x70
    /* 0x738 */ struct anon_13_154 result;            // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_4_154 -- @anon4, 0xB8 bytes, tra_main.c (DIE 0x2AEB19) */
struct anon_4_154 {   // size 0xB8
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char step_s;                 // 0x1
    /* 0x002 */ unsigned char mode;                   // 0x1
    /* 0x003 */ unsigned char next_mode;              // 0x1
    /* 0x004 */ unsigned char sub_win_alpha;          // 0x1
    /* 0x005 */ unsigned char cur;                    // 0x1
    /* 0x006 */ unsigned char old_cur;                // 0x1
    /* 0x007 */ unsigned char opt_cur;                // 0x1
    /* 0x008 */ unsigned char asi_cur;                // 0x1
    /* 0x009 */ unsigned char co_win_suu;             // 0x1
    /* 0x00A */ // 0x6 bytes padding
    /* 0x010 */ unsigned long arrow_clut_ct;          // 0x8
    /* 0x018 */ unsigned int flag;                    // 0x4
    /* 0x01C */ int repcnt;                           // 0x4
    /* 0x020 */ float ftimer;                         // 0x4
    /* 0x024 */ short music_num;                      // 0x2
    /* 0x026 */ short old_music_num;                  // 0x2
    /* 0x028 */ unsigned char player;                 // 0x1
    /* 0x029 */ unsigned char level;                  // 0x1
    /* 0x02A */ unsigned char mspeed;                 // 0x1
    /* 0x02B */ unsigned char edit_data_on;           // 0x1
    /* 0x02C */ unsigned char clap;                   // 0x1
    /* 0x02D */ unsigned char metro;                  // 0x1
    /* 0x02E */ unsigned char track;                  // 0x1
    /* 0x02F */ unsigned char arrow_speed;            // 0x1
    /* 0x030 */ unsigned char boost;                  // 0x1
    /* 0x031 */ unsigned char appear;                 // 0x1
    /* 0x032 */ unsigned char turn;                   // 0x1
    /* 0x033 */ unsigned char little;                 // 0x1
    /* 0x034 */ unsigned char dark;                   // 0x1
    /* 0x035 */ unsigned char simu;                   // 0x1
    /* 0x036 */ unsigned char scroll;                 // 0x1
    /* 0x037 */ unsigned char freeze;                 // 0x1
    /* 0x038 */ unsigned char real_turn;              // 0x1
    /* 0x039 */ unsigned char c_bar_max;              // 0x1
    /* 0x03A */ unsigned char c_bar_adjust;           // 0x1
    /* 0x03B */ unsigned char bar_start;              // 0x1
    /* 0x03C */ unsigned char bar_end;                // 0x1
    /* 0x03D */ unsigned char bar_max;                // 0x1
    /* 0x03E */ unsigned char adjust_bar;             // 0x1
    /* 0x03F */ unsigned char cur_bar_w;              // 0x1
    /* 0x040 */ unsigned char special_bar;            // 0x1
    /* 0x041 */ // 0x1 bytes padding
    /* 0x042 */ short scroll_ct;                      // 0x2
    /* 0x044 */ unsigned char scroll_spd;             // 0x1
    /* 0x045 */ unsigned char start_side;             // 0x1
    /* 0x046 */ unsigned char finish_flg;             // 0x1
    /* 0x047 */ unsigned char music_step;             // 0x1
    /* 0x048 */ unsigned char finish_step;            // 0x1
    /* 0x049 */ unsigned char now_play_bar;           // 0x1
    /* 0x04A */ unsigned char old_play_bar;           // 0x1
    /* 0x04B */ unsigned char cur_point_pos[2];       // 0x2
    /* 0x04D */ unsigned char play_bright;            // 0x1
    /* 0x04E */ short obi_deg;                        // 0x2
    /* 0x050 */ short cur_clap_pos[2];                // 0x4
    /* 0x054 */ short cur_metro_pos;                  // 0x2
    /* 0x056 */ // 0x2 bytes padding
    /* 0x058 */ int now_music_data;                   // 0x4
    /* 0x05C */ int check_music_ct;                   // 0x4
    /* 0x060 */ unsigned long push_cont_timer;        // 0x8
    /* 0x068 */ unsigned char rs_cur;                 // 0x1
    /* 0x069 */ unsigned char ck_cur;                 // 0x1
    /* 0x06A */ unsigned char cur_chk_bar;            // 0x1
    /* 0x06B */ unsigned char check_mode_flg;         // 0x1
    /* 0x06C */ void *obj_p[10];                      // 0x28
    /* 0x094 */ void *ms_display;                     // 0x4
    /* 0x098 */ unsigned short tex_no[15];            // 0x1E
    /* 0x0B6 */ // 0x2 bytes padding
};

/* anon_8_154 -- @anon8, 0xD40 bytes, tra_main.c (DIE 0x2B0A84) */
struct anon_8_154 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_11_154 -- @anon11, 0x8 bytes, tra_main.c (DIE 0x2B1799) */
struct anon_11_154 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};

/* anon_12_154 -- @anon12, 0x14 bytes, tra_main.c (DIE 0x2B1886) */
struct anon_12_154 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_14_154 -- @anon14, 0xC bytes, tra_main.c (DIE 0x2B2195) */
struct anon_14_154 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_15_154 -- @anon15, 0x14 bytes, tra_main.c (DIE 0x2B2300) */
struct anon_15_154 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_17_154 -- @anon17, 0x1300 bytes, tra_main.c (DIE 0x2B2821) */
struct anon_17_154 {   // size 0x1300
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
    /* 0x360 */ struct anon_12_154 subject[200];      // 0xFA0
};

/* anon_20_154 -- @anon20, 0x4 bytes, tra_main.c (DIE 0x2B2CE1) */
struct anon_20_154 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_18_154 -- @anon18, 0x4 bytes, tra_main.c (DIE 0x2B2BDC) */
union anon_18_154 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_20_154 s;                 // 0x4
};

/* anon_19_154 -- @anon19, 0x4 bytes, tra_main.c (DIE 0x2B2C3B) */
union anon_19_154 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_21_154 -- @anon21, 0x12E0 bytes, tra_main.c (DIE 0x2B2F7F) */
struct anon_21_154 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_14_154 history[400];      // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_22_154 -- @anon22, 0x30 bytes, tra_main.c (DIE 0x2B3146) */
struct anon_22_154 {   // size 0x30
    /* 0x000 */ union anon_19_154 x0;                 // 0x4
    /* 0x004 */ union anon_19_154 y0;                 // 0x4
    /* 0x008 */ union anon_19_154 x1;                 // 0x4
    /* 0x00C */ union anon_19_154 y1;                 // 0x4
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

/* anon_23_154 -- @anon23, 0x2134 bytes, tra_main.c (DIE 0x2B343A) */
struct anon_23_154 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_18_154 userpass;           // 0x4
    /* 0x008 */ struct anon_21_154 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_8_154 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_24_154 -- @anon24, 0x10 bytes, tra_main.c (DIE 0x2B361D) */
struct anon_24_154 {   // size 0x10
    /* 0x000 */ union anon_19_154 x0;                 // 0x4
    /* 0x004 */ union anon_19_154 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_25_154 -- @anon25, 0x20 bytes, tra_main.c (DIE 0x2B422A) */
struct anon_25_154 {   // size 0x20
    /* 0x000 */ struct _CWS_WIN_W *win;               // 0x4
    /* 0x004 */ unsigned char win_no;                 // 0x1
    /* 0x005 */ unsigned char kind;                   // 0x1
    /* 0x006 */ unsigned char alpha;                  // 0x1
    /* 0x007 */ // 0x1 bytes padding
    /* 0x008 */ float win_t;                          // 0x4
    /* 0x00C */ float dy;                             // 0x4
    /* 0x010 */ float t;                              // 0x4
    /* 0x014 */ struct _tag_cCoCursor01 cur_w;        // 0xC
};

/* anon_26_154 -- @anon26, 0x4 bytes, tra_main.c (DIE 0x2B4549) */
struct anon_26_154 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_27_154 -- @anon27, 0x10 bytes, tra_main.c (DIE 0x2B5032) */
struct anon_27_154 {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
};

/* anon_28_154 -- @anon28, 0x10 bytes, tra_main.c (DIE 0x2B53A7) */
struct anon_28_154 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};

/* anon_29_154 -- @anon29, 0x8 bytes, tra_main.c (DIE 0x2B54D1) */
struct anon_29_154 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_30_154 -- @anon30, 0x4 bytes, tra_main.c (DIE 0x2B677A) */
struct anon_30_154 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_31_154 -- @anon31, 0x184 bytes, tra_main.c (DIE 0x2B6D0A) */
struct anon_31_154 {   // size 0x184
    /* 0x000 */ struct anon_24_154 line_a[8];         // 0x80
    /* 0x080 */ struct anon_24_154 line_b[8];         // 0x80
    /* 0x100 */ struct anon_24_154 line_c[8];         // 0x80
    /* 0x180 */ int num;                              // 0x4
};


/* variables (25) */
struct anon_4_154 *trw;                                          /* @0x002DDDDC size 0x4 */
static unsigned char (*tr_exec_func[5])();                       /* @0x002C0A70 size 0x14 */
static struct anon_28_154 tr_obj_f[10];                          /* @0x002C0A90 size 0xA0 */
unsigned char tr_obj_pri[10];                                    /* @0x002C0B30 size 0xA */
unsigned int tra_dance_addr;                                     /* @0x002DE578 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
unsigned int tra_seq_buff_th_addr;                               /* @0x002DE57C size 0x4 */
unsigned int tra_seq_buff_addr;                                  /* @0x002DE580 size 0x4 */
unsigned int tra_kanji_buff_addr;                                /* @0x002DE584 size 0x4 */
struct anon_13_154 *rsw;                                         /* @0x002DE524 size 0x4 */
struct anon_10_154 *msw;                                         /* @0x002DE52C size 0x4 */
unsigned int tra_logo_tex_addr;                                  /* @0x002DE588 size 0x4 */
unsigned int tra_cs_tex_addr;                                    /* @0x002DE58C size 0x4 */
struct anon_11_154 ue2_tr_bin[];                                 /* @0x002DD718 */
struct anon_2_154 *fpw;                                          /* @0x002DE540 size 0x4 */
unsigned int tra_am_tex_addr;                                    /* @0x002DE590 size 0x4 */
struct anon_3_154 *sow;                                          /* @0x002DE528 size 0x4 */
struct anon_9_154 *chw;                                          /* @0x002DE530 size 0x4 */
struct anon_5_154 *dw;                                           /* @0x002DE534 size 0x4 */
struct anon_7_154 *stw;                                          /* @0x002DE538 size 0x4 */
struct anon_6_154 *etw;                                          /* @0x002DE53C size 0x4 */
struct anon_2_154 tr_fp_work;                                    /* @0x00722430 size 0x7E0 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
unsigned int tra_kanji_data_addr;                                /* not allocated size 0x4 */
static struct anon_4_154 train_w;                                /* @0x00722C10 size 0xB8 */

/* functions referenced (2) */
void fp_trans_title_th(void *);                                  /* @0x00215E20 */
void DecodeFilepackData_Th(void *);                              /* @0x0016DC50 */

/* functions defined (17) */
static int tr_tex_init(void);                                    /* 0x00276520-0x00276800 lines 844-947 */
static int TRObj_seq_disp(void *wp);                             /* 0x00276800-0x00276984 lines 815-825 */
static int TRObj_seq_func(void *wp);                             /* 0x00276990-0x00276AE0 lines 780-813 */
static int TRObj_label_disap(void *wp);                          /* 0x00276AE0-0x00276B88 lines 748-766 */
static int TRObj_label_apper(void *wp);                          /* 0x00276B90-0x00276C30 lines 731-745 */
static int TRObj_win_disp(void);                                 /* 0x00276C30-0x00276C50 lines 718-722 */
int TRObj_win_func(void *wp);                                    /* 0x00276C50-0x00277188 lines 599-715 */
void tr_obj_disap(int obj_no);                                   /* 0x00277190-0x002771D8 lines 589-594 */
void *tr_obj_set(int obj_no);                                    /* 0x002771E0-0x0027726C lines 576-586 */
void Tr_frame_disp(float cx, float cy, float w, float h, int pri, unsigned char kind, unsigned char alpha); /* 0x00277270-0x002774B8 lines 422-456 */
unsigned int Tr_PadLRRepeat(unsigned int key);                   /* 0x002774C0-0x00277584 lines 398-416 */
unsigned int Tr_PadRepeat(unsigned int key);                     /* 0x00277590-0x002775DC lines 392-394 */
unsigned int Tr_PadPush(unsigned int key);                       /* 0x002775E0-0x0027762C lines 388-390 */
unsigned int Tr_PadTrg(unsigned int key);                        /* 0x00277630-0x0027767C lines 385-387 */
void Term_Train(void);                                           /* 0x00277680-0x00277688 lines 380-380 */
int Step_Train(void);                                            /* 0x00277690-0x00277BA8 lines 249-377 */
void Init_Train(void);                                           /* 0x00277BB0-0x00277E38 lines 173-246 */

#endif /* DDR_UNIT_src_CS_train_tra_main_c_H */
