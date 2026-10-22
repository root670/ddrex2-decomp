/*
 * C:\work2\usaex2\src\CS\freeplay\fp_msel_obj.c
 * MW MIPS C Compiler, overlay main; 39 functions, code 0x00233C50-0x0023CA38
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
#ifndef DDR_UNIT_src_CS_freeplay_fp_msel_obj_c_H
#define DDR_UNIT_src_CS_freeplay_fp_msel_obj_c_H

#include "types/G_SYS_W_.h"
#include "types/_CWS_WIN_W.h"
#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/music_info.h"
#include "types/oni_course.h"
#include "types/tex_bind.h"

/* anonymous types (35) */

/* anon_0_104 -- @anon0, 0xB8 bytes, fp_msel_obj.c (DIE 0x1D2548) */
typedef struct {   // size 0xB8
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
} anon_0_104;

/* anon_3_104 -- @anon3, 0x24 bytes, fp_msel_obj.c (DIE 0x1D316F) */
typedef struct {   // size 0x24
    /* 0x000 */ float t[2];                           // 0x8
    /* 0x008 */ float h[2];                           // 0x8
    /* 0x010 */ float alpha[2];                       // 0x8
    /* 0x018 */ float bri[2];                         // 0x8
    /* 0x020 */ unsigned char step[2];                // 0x2
    /* 0x022 */ // 0x2 bytes padding
} anon_3_104;

/* anon_1_104 -- @anon1, 0x14C bytes, fp_msel_obj.c (DIE 0x1D2EF2) */
typedef struct {   // size 0x14C
    /* 0x000 */ anon_3_104 ic[9];                     // 0x144
    /* 0x144 */ int entry_flag;                       // 0x4
    /* 0x148 */ unsigned char entry_step;             // 0x1
    /* 0x149 */ // 0x3 bytes padding
} anon_1_104;

/* anon_15_104 -- @anon15, 0x14 bytes, fp_msel_obj.c (DIE 0x1D5ACA) */
typedef struct {   // size 0x14
    /* 0x000 */ float t;                              // 0x4
    /* 0x004 */ float cy;                             // 0x4
    /* 0x008 */ float dx;                             // 0x4
    /* 0x00C */ float dy;                             // 0x4
    /* 0x010 */ unsigned short kind;                  // 0x2
    /* 0x012 */ unsigned char step;                   // 0x1
    /* 0x013 */ unsigned char off;                    // 0x1
} anon_15_104;

/* anon_2_104 -- @anon2, 0x11C bytes, fp_msel_obj.c (DIE 0x1D2F80) */
typedef struct {   // size 0x11C
    /* 0x000 */ anon_15_104 one[13];                  // 0x104
    /* 0x104 */ float star_t;                         // 0x4
    /* 0x108 */ float spe_t;                          // 0x4
    /* 0x10C */ float spe_val[2];                     // 0x8
    /* 0x114 */ int spe_ct;                           // 0x4
    /* 0x118 */ short d_num;                          // 0x2
    /* 0x11A */ // 0x2 bytes padding
} anon_2_104;

/* anon_4_104 -- @anon4, 0x28 bytes, fp_msel_obj.c (DIE 0x1D39AD) */
typedef struct {   // size 0x28
    /* 0x000 */ float dy;                             // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float bri_t;                          // 0x4
    /* 0x00C */ float bpm_t;                          // 0x4
    /* 0x010 */ int bpm;                              // 0x4
    /* 0x014 */ int bpm_step;                         // 0x4
    /* 0x018 */ struct music_info *mip;               // 0x4
    /* 0x01C */ unsigned short radar_max[5];          // 0xA
    /* 0x026 */ // 0x2 bytes padding
} anon_4_104;

/* anon_5_104 -- @anon5, 0x3C bytes, fp_msel_obj.c (DIE 0x1D3BC9) */
typedef struct {   // size 0x3C
    /* 0x000 */ float dy;                             // 0x4
    /* 0x004 */ float win_w;                          // 0x4
    /* 0x008 */ float win_h;                          // 0x4
    /* 0x00C */ float t[5];                           // 0x14
    /* 0x020 */ float alpha;                          // 0x4
    /* 0x024 */ float rot;                            // 0x4
    /* 0x028 */ float bri_t;                          // 0x4
    /* 0x02C */ unsigned char rlt_num[6];             // 0x6
    /* 0x032 */ unsigned char rlt_ct[6];              // 0x6
    /* 0x038 */ short d_num;                          // 0x2
    /* 0x03A */ unsigned char edi;                    // 0x1
    /* 0x03B */ // 0x1 bytes padding
} anon_5_104;

/* anon_6_104 -- @anon6, 0x48 bytes, fp_msel_obj.c (DIE 0x1D3D5C) */
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
} anon_6_104;

/* anon_7_104 -- @anon7, 0x8 bytes, fp_msel_obj.c (DIE 0x1D4434) */
typedef struct {   // size 0x8
    /* 0x000 */ float t;                              // 0x4
    /* 0x004 */ unsigned char no;                     // 0x1
    /* 0x005 */ // 0x3 bytes padding
} anon_7_104;

/* anon_8_104 -- @anon8, 0x18 bytes, fp_msel_obj.c (DIE 0x1D4D65) */
typedef struct {   // size 0x18
    /* 0x000 */ int old_msg;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ struct _CWS_WIN_W *win;               // 0x4
    /* 0x00C */ struct _tag_cCoCursor01 cur_w;        // 0xC
} anon_8_104;

/* anon_28_104 -- @anon28, 0x4 bytes, fp_msel_obj.c (DIE 0x1D6FE0) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_28_104;

/* anon_11_104 -- @anon11, 0x10 bytes, fp_msel_obj.c (DIE 0x1D502B) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_28_104 x0;                       // 0x4
    /* 0x004 */ anon_28_104 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_11_104;

/* anon_10_104 -- @anon10, 0xC bytes, fp_msel_obj.c (DIE 0x1D4F9E) */
typedef struct {   // size 0xC
    /* 0x000 */ anon_11_104 *data;                    // 0x4
    /* 0x004 */ int vertex_num;                       // 0x4
    /* 0x008 */ int flg;                              // 0x4
} anon_10_104;

/* anon_12_104 -- @anon12, 0x8 bytes, fp_msel_obj.c (DIE 0x1D52EE) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_12_104;

/* anon_14_104 -- @anon14, 0x1C bytes, fp_msel_obj.c (DIE 0x1D56D0) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_28_104 x0;                       // 0x4
    /* 0x004 */ anon_28_104 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_14_104;

/* anon_16_104 -- @anon16, 0x90 bytes, fp_msel_obj.c (DIE 0x1D5BEB) */
typedef struct {   // size 0x90
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
    /* 0x054 */ // 0xC bytes padding
    /* 0x060 */ float cam_p[4] __attribute__((aligned(16)));  // 0x10
    /* 0x070 */ float eye_p[4];                       // 0x10
    /* 0x080 */ void *fpanel;                         // 0x4
    /* 0x084 */ // 0xC bytes padding
} anon_16_104;

/* anon_17_104 -- @anon17, 0x1C bytes, fp_msel_obj.c (DIE 0x1D5E95) */
typedef struct {   // size 0x1C
    /* 0x000 */ float t;                              // 0x4
    /* 0x004 */ float cur_t;                          // 0x4
    /* 0x008 */ unsigned char up_alpha;               // 0x1
    /* 0x009 */ // 0x3 bytes padding
    /* 0x00C */ int up_ta_num;                        // 0x4
    /* 0x010 */ int dw_ta_num;                        // 0x4
    /* 0x014 */ int up_num;                           // 0x4
    /* 0x018 */ int dw_num;                           // 0x4
} anon_17_104;

/* anon_18_104 -- @anon18, 0x70 bytes, fp_msel_obj.c (DIE 0x1D5FAC) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_12_104 one[11];                  // 0x58
} anon_18_104;

/* anon_43_104 -- @anon43, 0xC bytes, fp_msel_obj.c (DIE 0x1DAE13) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_43_104;

/* anon_25_104 -- @anon25, 0xC bytes, fp_msel_obj.c (DIE 0x1D6E1B) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_25_104;

/* anon_41_104 -- @anon41, 0x1C bytes, fp_msel_obj.c (DIE 0x1D9CFB) */
typedef struct {   // size 0x1C
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
} anon_41_104;

/* anon_32_104 -- @anon32, 0x494 bytes, fp_msel_obj.c (DIE 0x1D7997) */
typedef struct {   // size 0x494
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
} anon_32_104;

/* anon_35_104 -- @anon35, 0x34 bytes, fp_msel_obj.c (DIE 0x1D88D2) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_35_104;

/* anon_39_104 -- @anon39, 0xA0 bytes, fp_msel_obj.c (DIE 0x1D95AD) */
typedef struct {   // size 0xA0
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
    /* 0x038 */ anon_35_104 eva[2];                   // 0x68
} anon_39_104;

/* anon_20_104 -- @anon20, 0x7E0 bytes, fp_msel_obj.c (DIE 0x1D62A1) */
typedef struct {   // size 0x7E0
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
    /* 0x170 */ anon_16_104 doll;                     // 0x90
    /* 0x200 */ anon_43_104 eyetoy;                   // 0xC
    /* 0x20C */ anon_25_104 style;                    // 0xC
    /* 0x218 */ anon_41_104 chara;                    // 0x1C
    /* 0x234 */ anon_32_104 music;                    // 0x494
    /* 0x6C8 */ anon_18_104 option;                   // 0x70
    /* 0x738 */ anon_39_104 result;                   // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_20_104;

/* anon_21_104 -- @anon21, 0x8 bytes, fp_msel_obj.c (DIE 0x1D6775) */
typedef struct {   // size 0x8
    /* 0x000 */ int score;                            // 0x4
    /* 0x004 */ char rank;                            // 0x1
    /* 0x005 */ unsigned char is_fcombo;              // 0x1
    /* 0x006 */ // 0x2 bytes padding
} anon_21_104;

/* anon_22_104 -- @anon22, 0x24 bytes, fp_msel_obj.c (DIE 0x1D6846) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_28_104 x0;                       // 0x4
    /* 0x004 */ anon_28_104 y0;                       // 0x4
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
} anon_22_104;

/* anon_23_104 -- @anon23, 0x4 bytes, fp_msel_obj.c (DIE 0x1D6A91) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
} anon_23_104;

/* anon_27_104 -- @anon27, 0x10 bytes, fp_msel_obj.c (DIE 0x1D6F44) */
typedef struct {   // size 0x10
    /* 0x000 */ float dx;                             // 0x4
    /* 0x004 */ float dy;                             // 0x4
    /* 0x008 */ float t;                              // 0x4
    /* 0x00C */ float pad;                            // 0x4
} anon_27_104;

/* anon_31_104 -- @anon31, 0x30 bytes, fp_msel_obj.c (DIE 0x1D777D) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_28_104 x0;                       // 0x4
    /* 0x004 */ anon_28_104 y0;                       // 0x4
    /* 0x008 */ anon_28_104 x1;                       // 0x4
    /* 0x00C */ anon_28_104 y1;                       // 0x4
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
} anon_31_104;

/* anon_34_104 -- @anon34, 0x68 bytes, fp_msel_obj.c (DIE 0x1D851E) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_28_104 x0;                       // 0x4
    /* 0x004 */ anon_28_104 y0;                       // 0x4
    /* 0x008 */ anon_28_104 x1;                       // 0x4
    /* 0x00C */ anon_28_104 y1;                       // 0x4
    /* 0x010 */ anon_28_104 x2;                       // 0x4
    /* 0x014 */ anon_28_104 y2;                       // 0x4
    /* 0x018 */ anon_28_104 x3;                       // 0x4
    /* 0x01C */ anon_28_104 y3;                       // 0x4
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
} anon_34_104;

/* anon_37_104 -- @anon37, 0x10 bytes, fp_msel_obj.c (DIE 0x1D8B81) */
typedef struct {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
} anon_37_104;

/* anon_38_104 -- @anon38, 0x10 bytes, fp_msel_obj.c (DIE 0x1D94F4) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_38_104;

/* anon_40_104 -- @anon40, 0x20 bytes, fp_msel_obj.c (DIE 0x1D996E) */
typedef struct {   // size 0x20
    /* 0x000 */ anon_28_104 x0;                       // 0x4
    /* 0x004 */ anon_28_104 y0;                       // 0x4
    /* 0x008 */ anon_28_104 x1;                       // 0x4
    /* 0x00C */ anon_28_104 y1;                       // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ int flg;                              // 0x4
} anon_40_104;

/* anon_44_104 -- @anon44, 0x8 bytes, fp_msel_obj.c (DIE 0x1DAF9B) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_44_104;


/* variables (26) */
static anon_23_104 fp_ms_ud_col[7];                              /* @0x002BEA50 size 0x1C */
static anon_23_104 fp_ms_ud_col_edi[2];                          /* @0x002DDBF0 size 0x8 */
static anon_23_104 fp_ms_spe_col[4];                             /* @0x002BEA70 size 0x10 */
anon_38_104 fp_ms_objf[11];                                      /* @0x002BEA80 size 0xB0 */
static unsigned char *fp_ed_mc_msg[8];                           /* @0x002BEB30 size 0x20 */
static unsigned char fp_mc_yes[4];                               /* @0x002DDBF8 size 0x4 */
static unsigned char fp_mc_no[3];                                /* @0x002DDBFC size 0x3 */
static float fp_ed_mc_msg_y[8];                                  /* @0x002BEB50 size 0x20 */
unsigned char fp_star_pat_tbl[4];                                /* @0x002DDC00 size 0x4 */
static float ap_t0[13];                                          /* @0x002BEB70 size 0x34 */
static float ap2_t0[13];                                         /* @0x002BEBB0 size 0x34 */
static int fp_radar_tab[5];                                      /* @0x002D5120 size 0x14 */
static unsigned short radar_test[6][5];                          /* not allocated size 0x3C */
static float radar_pos[6][4];                                    /* @0x002BEC30 size 0x60 */
struct tex_bind tex_bind[375];                                   /* @0x0058C390 size 0x2904 */
anon_32_104 *msw;                                                /* @0x002DE52C size 0x4 */
anon_20_104 *fpw;                                                /* @0x002DE540 size 0x4 */
unsigned char fp_msm_tab[];                                      /* @0x002DDB20 */
unsigned char fp_so_def_tbl[];                                   /* @0x002BC3D0 */
anon_18_104 *sow;                                                /* @0x002DE528 size 0x4 */
anon_25_104 *stw;                                                /* @0x002DE538 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
unsigned char fp_ms_disp_ename[360];                             /* @0x0071E4B0 size 0x168 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
anon_0_104 *trw;                                                 /* @0x002DDDDC size 0x4 */
anon_38_104 fp_objf[];                                           /* @0x002BBD80 */

/* functions defined (39) */
static int fp_ms_edmc_msg_disp(void *w);                         /* 0x00233C50-0x00233CF8 lines 3435-3450 */
static int fp_ms_edmc_msg_func(void *w);                         /* 0x00233D00-0x00234058 lines 3340-3432 */
static int fp_ms_entry_disp(void *w);                            /* 0x00234060-0x00234150 lines 3314-3333 */
static int fp_ms_entry_exec(void *w);                            /* 0x00234150-0x002341B4 lines 3300-3311 */
static int fp_ms_base_disp(void *w);                             /* 0x002341C0-0x002342E0 lines 3260-3289 */
static int fp_ms_base_disap(void *w);                            /* 0x002342E0-0x00234360 lines 3244-3257 */
static int fp_ms_base_apper(void *w);                            /* 0x00234360-0x002343E8 lines 3227-3241 */
static int fp_ms_scbar_disp(void *w);                            /* 0x002343F0-0x00234758 lines 3156-3216 */
static int fp_ms_scbar_alpha(void *w);                           /* 0x00234760-0x00234800 lines 3133-3153 */
static int fp_ms_sort_disp(void *w);                             /* 0x00234800-0x00234DC8 lines 3036-3126 */
static int fp_ms_sort_exec(void);                                /* 0x00234DD0-0x00234DD8 lines 3033-3033 */
static int fp_ms_sort_move(void *w);                             /* 0x00234DE0-0x00234EE8 lines 2954-2983 */
void fp_ms_entry_opt_set(int pid);                               /* 0x00234EF0-0x00234F34 lines 2920-2926 */
static int fp_ms_option_disp(void *w);                           /* 0x00234F40-0x002352F4 lines 2870-2917 */
static int fp_ms_option_disap(void *w);                          /* 0x00235300-0x002354EC lines 2816-2867 */
static int fp_ms_option_exec(void *w);                           /* 0x002354F0-0x00235768 lines 2753-2814 */
static int fp_ms_option_apper(void *w);                          /* 0x00235770-0x002359BC lines 2684-2744 */
static int fp_ms_radar_disp(void *w);                            /* 0x002359C0-0x00236558 lines 2462-2656 */
static int fp_ms_radar_disap(void *w);                           /* 0x00236560-0x002365F0 lines 2446-2459 */
static int fp_ms_radar_exec(void *w);                            /* 0x002365F0-0x00236804 lines 2391-2443 */
static int fp_ms_radar_apper(void *w);                           /* 0x00236810-0x0023694C lines 2356-2388 */
static void fp_ms_banner_one_disp(int d_num, unsigned char ud, unsigned char alpha, unsigned char ani_no); /* 0x00236950-0x00237050 lines 2086-2267 */
static int fp_ms_display_disp(void *w);                          /* 0x00237050-0x00237160 lines 2068-2081 */
static int fp_ms_display_disap(void);                            /* 0x00237160-0x00237168 lines 2066-2066 */
static int fp_ms_display_exec(void *w);                          /* 0x00237170-0x0023745C lines 2003-2061 */
static int fp_ms_display_apper(void *w);                         /* 0x00237460-0x002374BC lines 1985-2000 */
static int fp_ms_ud_item_disp(void *w);                          /* 0x002374C0-0x00238FBC lines 1609-1966 */
static int fp_ms_ud_item_disap(void *w);                         /* 0x00238FC0-0x0023909C lines 1585-1606 */
static int fp_ms_ud_item_exec(void *w);                          /* 0x002390A0-0x00239508 lines 1496-1582 */
static int fp_ms_ud_item_apper(void *w);                         /* 0x00239510-0x00239720 lines 1450-1493 */
static void fp_ms_nm_one_disp(float x0, float cy, int d_num, unsigned char kind, char best, unsigned char cur); /* 0x00239720-0x0023A2A0 lines 1151-1402 */
static int fp_ms_lr_item_disp(void *w);                          /* 0x0023A2A0-0x0023B4AC lines 854-1145 */
static void fp_ms_spe(anon_2_104 *lrw, unsigned char ini);       /* 0x0023B4B0-0x0023B884 lines 792-851 */
static int fp_ms_lr_item_disap(void *w);                         /* 0x0023B890-0x0023BB20 lines 669-726 */
static int fp_ms_lr_item_exec(void *w);                          /* 0x0023BB20-0x0023BBBC lines 644-665 */
static int fp_ms_lr_item_apper2(void *w);                        /* 0x0023BBC0-0x0023BED0 lines 573-640 */
static int fp_ms_lr_item_apper(void *w);                         /* 0x0023BED0-0x0023C158 lines 498-570 */
int fp_ms_disap(void);                                           /* 0x0023C160-0x0023C554 lines 321-432 */
int fp_ms_apper(void);                                           /* 0x0023C560-0x0023CA38 lines 190-316 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_msel_obj_c_H */
