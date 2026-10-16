/*
 * C:\work2\usaex2\src\CS\freeplay\fp_res.c
 * MW MIPS C Compiler, overlay main; 32 functions, code 0x002199C0-0x00220DEC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_freeplay_fp_res_c_H
#define DDR_UNIT_src_CS_freeplay_fp_res_c_H

#include "types/G_SYS_W_.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/eval_w.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/tex_bind.h"

/* anonymous types (41) */

/* anon_0_74 -- @anon0, 0x494 bytes, fp_res.c (DIE 0x12E99C) */
struct anon_0_74 {   // size 0x494
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

/* anon_1_74 -- @anon1, 0x4 bytes, fp_res.c (DIE 0x12F0D3) */
struct anon_1_74 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_2_74 -- @anon2, 0x48 bytes, fp_res.c (DIE 0x12F2DB) */
struct anon_2_74 {   // size 0x48
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

/* anon_10_74 -- @anon10, 0x4 bytes, fp_res.c (DIE 0x1328C2) */
union anon_10_74 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_74 -- @anon3, 0x1C bytes, fp_res.c (DIE 0x12FAD7) */
struct anon_3_74 {   // size 0x1C
    /* 0x000 */ union anon_10_74 x0;                  // 0x4
    /* 0x004 */ union anon_10_74 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_18_74 -- @anon18, 0x10 bytes, fp_res.c (DIE 0x1337D7) */
struct anon_18_74 {   // size 0x10
    /* 0x000 */ union anon_10_74 x0;                  // 0x4
    /* 0x004 */ union anon_10_74 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_4_74 -- @anon4, 0x184 bytes, fp_res.c (DIE 0x12FE13) */
struct anon_4_74 {   // size 0x184
    /* 0x000 */ struct anon_18_74 line_a[8];          // 0x80
    /* 0x080 */ struct anon_18_74 line_b[8];          // 0x80
    /* 0x100 */ struct anon_18_74 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_5_74 -- @anon5, 0x10 bytes, fp_res.c (DIE 0x130426) */
struct anon_5_74 {   // size 0x10
    /* 0x000 */ float dx;                             // 0x4
    /* 0x004 */ float dy;                             // 0x4
    /* 0x008 */ float t;                              // 0x4
    /* 0x00C */ float pad;                            // 0x4
};

/* anon_6_74 -- @anon6, 0x24 bytes, fp_res.c (DIE 0x13050B) */
struct anon_6_74 {   // size 0x24
    /* 0x000 */ union anon_10_74 x0;                  // 0x4
    /* 0x004 */ union anon_10_74 y0;                  // 0x4
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

/* anon_9_74 -- @anon9, 0x1C bytes, fp_res.c (DIE 0x131A8A) */
struct anon_9_74 {   // size 0x1C
    /* 0x000 */ float t;                              // 0x4
    /* 0x004 */ float acc;                            // 0x4
    /* 0x008 */ float sp;                             // 0x4
    /* 0x00C */ float pos;                            // 0x4
    /* 0x010 */ unsigned char cur;                    // 0x1
    /* 0x011 */ unsigned char step;                   // 0x1
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ float star_alpha;                     // 0x4
    /* 0x018 */ float star_bri;                       // 0x4
};

/* anon_7_74 -- @anon7, 0x4C bytes, fp_res.c (DIE 0x1307AD) */
struct anon_7_74 {   // size 0x4C
    /* 0x000 */ float star_t;                         // 0x4
    /* 0x004 */ float bri_t;                          // 0x4
    /* 0x008 */ float dy;                             // 0x4
    /* 0x00C */ float t;                              // 0x4
    /* 0x010 */ struct anon_9_74 rlt[2];              // 0x38
    /* 0x048 */ unsigned char step;                   // 0x1
    /* 0x049 */ // 0x3 bytes padding
};

/* anon_8_74 -- @anon8, 0x18 bytes, fp_res.c (DIE 0x13197D) */
struct anon_8_74 {   // size 0x18
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ float btn_cx;                         // 0x4
    /* 0x008 */ float btn_cy;                         // 0x4
    /* 0x00C */ int ex;                               // 0x4
    /* 0x010 */ float ex_x;                           // 0x4
    /* 0x014 */ float ex_cy;                          // 0x4
};

/* anon_11_74 -- @anon11, 0x8 bytes, fp_res.c (DIE 0x132A91) */
struct anon_11_74 {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
};

/* anon_19_74 -- @anon19, 0x90 bytes, fp_res.c (DIE 0x133942) */
struct anon_19_74 {   // size 0x90
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

/* anon_40_74 -- @anon40, 0xC bytes, fp_res.c (DIE 0x137B73) */
struct anon_40_74 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
};

/* anon_33_74 -- @anon33, 0xC bytes, fp_res.c (DIE 0x135586) */
struct anon_33_74 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
};

/* anon_39_74 -- @anon39, 0x1C bytes, fp_res.c (DIE 0x137031) */
struct anon_39_74 {   // size 0x1C
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

/* anon_17_74 -- @anon17, 0x70 bytes, fp_res.c (DIE 0x1334F8) */
struct anon_17_74 {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ struct anon_11_74 one[11];            // 0x58
};

/* anon_36_74 -- @anon36, 0x34 bytes, fp_res.c (DIE 0x1359A6) */
struct anon_36_74 {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
};

/* anon_27_74 -- @anon27, 0xA0 bytes, fp_res.c (DIE 0x134A85) */
struct anon_27_74 {   // size 0xA0
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
    /* 0x038 */ struct anon_36_74 eva[2];             // 0x68
};

/* anon_12_74 -- @anon12, 0x7E0 bytes, fp_res.c (DIE 0x132C17) */
struct anon_12_74 {   // size 0x7E0
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
    /* 0x170 */ struct anon_19_74 doll;               // 0x90
    /* 0x200 */ struct anon_40_74 eyetoy;             // 0xC
    /* 0x20C */ struct anon_33_74 style;              // 0xC
    /* 0x218 */ struct anon_39_74 chara;              // 0x1C
    /* 0x234 */ struct anon_0_74 music;               // 0x494
    /* 0x6C8 */ struct anon_17_74 option;             // 0x70
    /* 0x738 */ struct anon_27_74 result;             // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_13_74 -- @anon13, 0x10 bytes, fp_res.c (DIE 0x133013) */
struct anon_13_74 {   // size 0x10
    /* 0x000 */ float t;                              // 0x4
    /* 0x004 */ float dy;                             // 0x4
    /* 0x008 */ float hi;                             // 0x4
    /* 0x00C */ unsigned char step;                   // 0x1
    /* 0x00D */ // 0x3 bytes padding
};

/* anon_14_74 -- @anon14, 0x14 bytes, fp_res.c (DIE 0x1330D4) */
struct anon_14_74 {   // size 0x14
    /* 0x000 */ int bonus;                            // 0x4
    /* 0x004 */ int oni_score;                        // 0x4
    /* 0x008 */ float t;                              // 0x4
    /* 0x00C */ float new_t;                          // 0x4
    /* 0x010 */ unsigned char loop;                   // 0x1
    /* 0x011 */ unsigned char step;                   // 0x1
    /* 0x012 */ // 0x2 bytes padding
};

/* anon_15_74 -- @anon15, 0x30 bytes, fp_res.c (DIE 0x1331BE) */
struct anon_15_74 {   // size 0x30
    /* 0x000 */ union anon_10_74 x0;                  // 0x4
    /* 0x004 */ union anon_10_74 y0;                  // 0x4
    /* 0x008 */ union anon_10_74 x1;                  // 0x4
    /* 0x00C */ union anon_10_74 y1;                  // 0x4
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

/* anon_16_74 -- @anon16, 0xD40 bytes, fp_res.c (DIE 0x133420) */
struct anon_16_74 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_20_74 -- @anon20, 0xC bytes, fp_res.c (DIE 0x133BC8) */
struct anon_20_74 {   // size 0xC
    /* 0x000 */ int mode_quit_flg;                    // 0x4
    /* 0x004 */ int state;                            // 0x4
    /* 0x008 */ int renewal_record_flag;              // 0x4
};

/* anon_21_74 -- @anon21, 0x30 bytes, fp_res.c (DIE 0x133E65) */
struct anon_21_74 {   // size 0x30
    /* 0x000 */ float bri_t;                          // 0x4
    /* 0x004 */ float rot;                            // 0x4
    /* 0x008 */ struct anon_14_74 each[2];            // 0x28
};

/* anon_22_74 -- @anon22, 0x14 bytes, fp_res.c (DIE 0x133F56) */
struct anon_22_74 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_23_74 -- @anon23, 0x8 bytes, fp_res.c (DIE 0x134123) */
struct anon_23_74 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_24_74 -- @anon24, 0x68 bytes, fp_res.c (DIE 0x134299) */
struct anon_24_74 {   // size 0x68
    /* 0x000 */ union anon_10_74 x0;                  // 0x4
    /* 0x004 */ union anon_10_74 y0;                  // 0x4
    /* 0x008 */ union anon_10_74 x1;                  // 0x4
    /* 0x00C */ union anon_10_74 y1;                  // 0x4
    /* 0x010 */ union anon_10_74 x2;                  // 0x4
    /* 0x014 */ union anon_10_74 y2;                  // 0x4
    /* 0x018 */ union anon_10_74 x3;                  // 0x4
    /* 0x01C */ union anon_10_74 y3;                  // 0x4
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
};

/* anon_25_74 -- @anon25, 0xC bytes, fp_res.c (DIE 0x1346DF) */
struct anon_25_74 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_26_74 -- @anon26, 0x14 bytes, fp_res.c (DIE 0x13486E) */
struct anon_26_74 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_28_74 -- @anon28, 0x1300 bytes, fp_res.c (DIE 0x134CE5) */
struct anon_28_74 {   // size 0x1300
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
    /* 0x360 */ struct anon_22_74 subject[200];       // 0xFA0
};

/* anon_30_74 -- @anon30, 0x4 bytes, fp_res.c (DIE 0x134FEB) */
struct anon_30_74 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_29_74 -- @anon29, 0x4 bytes, fp_res.c (DIE 0x134F44) */
union anon_29_74 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_30_74 s;                  // 0x4
};

/* anon_31_74 -- @anon31, 0x12E0 bytes, fp_res.c (DIE 0x135265) */
struct anon_31_74 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_25_74 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_32_74 -- @anon32, 0x20 bytes, fp_res.c (DIE 0x1353E4) */
struct anon_32_74 {   // size 0x20
    /* 0x000 */ union anon_10_74 x0;                  // 0x4
    /* 0x004 */ union anon_10_74 y0;                  // 0x4
    /* 0x008 */ union anon_10_74 x1;                  // 0x4
    /* 0x00C */ union anon_10_74 y1;                  // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ int flg;                              // 0x4
};

/* anon_34_74 -- @anon34, 0x4 bytes, fp_res.c (DIE 0x135706) */
struct anon_34_74 {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
};

/* anon_35_74 -- @anon35, 0x2134 bytes, fp_res.c (DIE 0x1357C3) */
struct anon_35_74 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_29_74 userpass;            // 0x4
    /* 0x008 */ struct anon_31_74 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_16_74 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_37_74 -- @anon37, 0x4 bytes, fp_res.c (DIE 0x136510) */
struct anon_37_74 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_38_74 -- @anon38, 0x10 bytes, fp_res.c (DIE 0x136DA8) */
struct anon_38_74 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};


/* variables (12) */
struct anon_38_74 fp_rs_objf[5];                                 /* @0x002BC120 size 0x50 */
static int fp_rs_dlevel_uv[8][2];                                /* @0x002BC170 size 0x40 */
static struct anon_8_74 fp_btn_res[2];                           /* @0x002BC1B0 size 0x30 */
static struct anon_8_74 tr_btn_res[2];                           /* @0x002BC1E0 size 0x30 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct anon_12_74 *fpw;                                          /* @0x002DE540 size 0x4 */
struct anon_27_74 *rsw;                                          /* @0x002DE524 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct anon_0_74 *msw;                                           /* @0x002DE52C size 0x4 */
unsigned char fp_star_pat_tbl[];                                 /* @0x002DDC00 */
struct anon_20_74 usr_work;                                      /* @0x00328A20 size 0xC */

/* functions defined (32) */
static int endless_rs_score_disp(void);                          /* 0x002199C0-0x00219E40 lines 2568-2659 */
static int nonstop_rs_score_disp(void);                          /* 0x00219E40-0x0021A2AC lines 2495-2567 */
static void adv_rs_utime_disp(float x0, float y0, int _time, unsigned char alpha, int pri); /* 0x0021A2B0-0x0021A5E0 lines 2436-2492 */
static void adv_rs_frame_disp(float x, float y, int w, int h, int alpha, int pri); /* 0x0021A5E0-0x0021A794 lines 2399-2431 */
static void adv_endless_number_disp(float x0, float y0, unsigned int _num1, unsigned int _num2, unsigned char bri, unsigned char alpha); /* 0x0021A7A0-0x0021AAC0 lines 2343-2397 */
static int fp_rs_btn_disp(void *w);                              /* 0x0021AAC0-0x0021ABA0 lines 2312-2332 */
static int fp_rs_btn_move(void *w);                              /* 0x0021ABA0-0x0021ACA0 lines 2281-2309 */
static int fp_rs_score_disp(void *w);                            /* 0x0021ACA0-0x0021BA74 lines 1994-2272 */
static int fp_rs_score_disap(void);                              /* 0x0021BA80-0x0021BA88 lines 1991-1991 */
static int fp_rs_score_func(void *w);                            /* 0x0021BA90-0x0021C0E8 lines 1857-1987 */
static int fp_rs_point_disp(void *w);                            /* 0x0021C0F0-0x0021C45C lines 1765-1820 */
static int fp_rs_point_move(void *w);                            /* 0x0021C460-0x0021C560 lines 1734-1762 */
static int fp_rs_value_disp(void *w);                            /* 0x0021C560-0x0021CC14 lines 1590-1725 */
static int fp_rs_value_exec(void);                               /* 0x0021CC20-0x0021CC28 lines 1587-1587 */
static int fp_rs_value_disap(void *w);                           /* 0x0021CC30-0x0021CD78 lines 1546-1581 */
static int fp_rs_value_apper(void *w);                           /* 0x0021CD80-0x0021CEA8 lines 1515-1543 */
static int fp_rs_base_disp(void *w);                             /* 0x0021CEB0-0x0021D968 lines 1343-1493 */
static int fp_rs_base_func(void *w);                             /* 0x0021D970-0x0021E3B0 lines 1080-1340 */
static void fp_rs_cs00_disp(float cx, float cy, float len, int pri, unsigned char alpha); /* 0x0021E3B0-0x0021E5A0 lines 1035-1069 */
static void fp_rs_meter_disp(float x0, float y0, float w, unsigned int denominator, unsigned int numerator, int pid, int pri); /* 0x0021E5A0-0x0021EB08 lines 927-1029 */
static void fp_rs_utime_disp(int kind, float x0, float y0, int _time, unsigned char alpha, int pri); /* 0x0021EB10-0x0021EEF8 lines 833-919 */
static void fp_rs_number_disp(unsigned char kind, float x0, float y0, unsigned int _num, unsigned char keta, unsigned char alpha); /* 0x0021EF00-0x0021F518 lines 731-828 */
static void fp_rs_line_square_disp(struct anon_23_74 *rect, unsigned char r, unsigned char g, unsigned char b, int pri); /* 0x0021F520-0x0021F85C lines 693-724 */
static void fp_rs_ujudge_disp(float y0, unsigned char pid, int pri, unsigned char alpha); /* 0x0021F860-0x0021FA20 lines 646-688 */
static void fp_rs_uname_disp(float y0, unsigned char pid, int pri, unsigned char alpha); /* 0x0021FA20-0x0021FCE0 lines 586-640 */
static int fp_rs_disap(void);                                    /* 0x0021FCE0-0x0021FE54 lines 545-580 */
static int fp_rs_apper(void);                                    /* 0x0021FE60-0x0022002C lines 492-541 */
void fp_result_finish_all(void);                                 /* 0x00220030-0x00220038 lines 485-485 */
void fp_result_finish(void);                                     /* 0x00220040-0x00220048 lines 480-480 */
int fp_result_step(void);                                        /* 0x00220050-0x002202FC lines 404-474 */
void fp_result_init(void);                                       /* 0x00220300-0x00220B28 lines 269-399 */
void fp_result_init_all(void);                                   /* 0x00220B30-0x00220DEC lines 161-264 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_res_c_H */
