/*
 * C:\work2\usaex2\src\CS\freeplay\fp_opt.c
 * MW MIPS C Compiler, overlay main; 16 functions, code 0x00220DF0-0x00223F98
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_freeplay_fp_opt_c_H
#define DDR_UNIT_src_CS_freeplay_fp_opt_c_H

#include "types/G_SYS_W_.h"
#include "types/_CWS_WIN_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (27) */

/* anon_31_75 -- @anon31, 0x14 bytes, fp_opt.c (DIE 0x1475A0) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_31_75;

/* anon_3_75 -- @anon3, 0x4 bytes, fp_opt.c (DIE 0x13DD83) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_3_75;

/* anon_1_75 -- @anon1, 0x4 bytes, fp_opt.c (DIE 0x13DC5A) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_3_75 s;                          // 0x4
} anon_1_75;

/* anon_2_75 -- @anon2, 0x8 bytes, fp_opt.c (DIE 0x13DD00) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_2_75;

/* anon_32_75 -- @anon32, 0xC bytes, fp_opt.c (DIE 0x1478B5) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_32_75;

/* anon_4_75 -- @anon4, 0x12E0 bytes, fp_opt.c (DIE 0x13E020) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_32_75 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_4_75;

/* anon_5_75 -- @anon5, 0xC bytes, fp_opt.c (DIE 0x13E53C) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_5_75;

/* anon_29_75 -- @anon29, 0xD40 bytes, fp_opt.c (DIE 0x146D9C) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_29_75;

/* anon_7_75 -- @anon7, 0x34 bytes, fp_opt.c (DIE 0x13E8EA) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_7_75;

/* anon_8_75 -- @anon8, 0x50 bytes, fp_opt.c (DIE 0x13F50B) */
typedef struct {   // size 0x50
    /* 0x000 */ float bri_t;                          // 0x4
    /* 0x004 */ float rot;                            // 0x4
    /* 0x008 */ float t[5];                           // 0x14
    /* 0x01C */ float item_t[11];                     // 0x2C
    /* 0x048 */ float line_t;                         // 0x4
    /* 0x04C */ unsigned char call;                   // 0x1
    /* 0x04D */ // 0x3 bytes padding
} anon_8_75;

/* anon_10_75 -- @anon10, 0xA0 bytes, fp_opt.c (DIE 0x13F6AA) */
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
    /* 0x038 */ anon_7_75 eva[2];                     // 0x68
} anon_10_75;

/* anon_11_75 -- @anon11, 0x10 bytes, fp_opt.c (DIE 0x13F90A) */
typedef struct {   // size 0x10
    /* 0x000 */ struct _CWS_WIN_W *win[2];            // 0x8
    /* 0x008 */ unsigned char old_cur[2];             // 0x2
    /* 0x00A */ unsigned char old_value[2];           // 0x2
    /* 0x00C */ unsigned char win_num;                // 0x1
    /* 0x00D */ // 0x3 bytes padding
} anon_11_75;

/* anon_16_75 -- @anon16, 0x4 bytes, fp_opt.c (DIE 0x140E56) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_16_75;

/* anon_12_75 -- @anon12, 0x1C bytes, fp_opt.c (DIE 0x13FA06) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_16_75 x0;                        // 0x4
    /* 0x004 */ anon_16_75 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_12_75;

/* anon_13_75 -- @anon13, 0x10 bytes, fp_opt.c (DIE 0x14026A) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_13_75;

/* anon_14_75 -- @anon14, 0x1C bytes, fp_opt.c (DIE 0x14053B) */
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
} anon_14_75;

/* anon_15_75 -- @anon15, 0x24 bytes, fp_opt.c (DIE 0x14089E) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_16_75 x0;                        // 0x4
    /* 0x004 */ anon_16_75 y0;                        // 0x4
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
} anon_15_75;

/* anon_17_75 -- @anon17, 0xC bytes, fp_opt.c (DIE 0x14134B) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_17_75;

/* anon_18_75 -- @anon18, 0x30 bytes, fp_opt.c (DIE 0x141444) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_16_75 x0;                        // 0x4
    /* 0x004 */ anon_16_75 y0;                        // 0x4
    /* 0x008 */ anon_16_75 x1;                        // 0x4
    /* 0x00C */ anon_16_75 y1;                        // 0x4
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
} anon_18_75;

/* anon_19_75 -- @anon19, 0x10 bytes, fp_opt.c (DIE 0x141EBA) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_16_75 x0;                        // 0x4
    /* 0x004 */ anon_16_75 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_19_75;

/* anon_21_75 -- @anon21, 0x494 bytes, fp_opt.c (DIE 0x14248B) */
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
} anon_21_75;

/* anon_30_75 -- @anon30, 0x90 bytes, fp_opt.c (DIE 0x1470AA) */
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
    /* 0x054 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x060 */ float cam_p[4];                       // 0x10
    /* 0x070 */ float eye_p[4];                       // 0x10
    /* 0x080 */ void *fpanel;                         // 0x4
    /* 0x084 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
} anon_30_75;

/* anon_25_75 -- @anon25, 0x70 bytes, fp_opt.c (DIE 0x143C1B) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_2_75 one[11];                    // 0x58
} anon_25_75;

/* anon_22_75 -- @anon22, 0x7E0 bytes, fp_opt.c (DIE 0x142BE7) */
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
    /* 0x170 */ anon_30_75 doll;                      // 0x90
    /* 0x200 */ anon_17_75 eyetoy;                    // 0xC
    /* 0x20C */ anon_5_75 style;                      // 0xC
    /* 0x218 */ anon_14_75 chara;                     // 0x1C
    /* 0x234 */ anon_21_75 music;                     // 0x494
    /* 0x6C8 */ anon_25_75 option;                    // 0x70
    /* 0x738 */ anon_10_75 result;                    // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_22_75;

/* anon_23_75 -- @anon23, 0x68 bytes, fp_opt.c (DIE 0x14302B) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_16_75 x0;                        // 0x4
    /* 0x004 */ anon_16_75 y0;                        // 0x4
    /* 0x008 */ anon_16_75 x1;                        // 0x4
    /* 0x00C */ anon_16_75 y1;                        // 0x4
    /* 0x010 */ anon_16_75 x2;                        // 0x4
    /* 0x014 */ anon_16_75 y2;                        // 0x4
    /* 0x018 */ anon_16_75 x3;                        // 0x4
    /* 0x01C */ anon_16_75 y3;                        // 0x4
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
} anon_23_75;

/* anon_24_75 -- @anon24, 0x20 bytes, fp_opt.c (DIE 0x143A9D) */
typedef struct {   // size 0x20
    /* 0x000 */ anon_16_75 x0;                        // 0x4
    /* 0x004 */ anon_16_75 y0;                        // 0x4
    /* 0x008 */ anon_16_75 x1;                        // 0x4
    /* 0x00C */ anon_16_75 y1;                        // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ int flg;                              // 0x4
} anon_24_75;

/* anon_28_75 -- @anon28, 0x24 bytes, fp_opt.c (DIE 0x144631) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_16_75 x0;                        // 0x4
    /* 0x004 */ anon_16_75 y0;                        // 0x4
    /* 0x008 */ anon_16_75 x1;                        // 0x4
    /* 0x00C */ anon_16_75 y1;                        // 0x4
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
} anon_28_75;


/* variables (38) */
static anon_13_75 fp_so_objf[2];                                 /* @0x002BC2F0 size 0x20 */
static unsigned char *fp_so_str_onoff[2];                        /* @0x002DDB50 size 0x8 */
static unsigned char *fp_so_str_spd[6];                          /* @0x002BC310 size 0x18 */
static unsigned char *fp_so_str_apr[4];                          /* @0x002BC330 size 0x10 */
static unsigned char *fp_so_str_tne[5];                          /* @0x002BC340 size 0x14 */
static unsigned char *fp_so_str_tne_db[2];                       /* not allocated size 0x8 */
static unsigned char *fp_so_str_sim[3];                          /* @0x002BC358 size 0xC */
static unsigned char *fp_so_str_scr[2];                          /* @0x002DDB58 size 0x8 */
static unsigned char *fp_so_str_step[6];                         /* @0x002BC370 size 0x18 */
static unsigned char fp_so_str_step_edi[5];                      /* @0x002DDB60 size 0x5 */
static unsigned char *fp_so_str_play[1];                         /* @0x002DDB68 size 0x4 */
static unsigned char *fp_so_str_tbl[11];                         /* @0x002BC390 size 0x2C */
static unsigned char fp_so_num_tbl[11];                          /* @0x002BC3C0 size 0xB */
unsigned char fp_so_def_tbl[11];                                 /* @0x002BC3D0 size 0xB */
static unsigned char fp_so_ex_str_spd[6];                        /* @0x002DDB70 size 0x6 */
static unsigned char fp_so_ex_str_onoff[6];                      /* not allocated size 0x6 */
static unsigned char fp_so_ex_str_bst[2];                        /* @0x002DDB78 size 0x2 */
static unsigned char fp_so_ex_str_apr[4];                        /* @0x002DDB7C size 0x4 */
static unsigned char fp_so_ex_str_tne[5];                        /* @0x002DDB80 size 0x5 */
static unsigned char fp_so_ex_str_ltl[2];                        /* @0x002DDB88 size 0x2 */
static unsigned char fp_so_ex_str_drk[2];                        /* @0x002DDB8C size 0x2 */
static unsigned char fp_so_ex_str_sim[3];                        /* @0x002DDB90 size 0x3 */
static unsigned char fp_so_ex_str_scr[2];                        /* @0x002DDB94 size 0x2 */
static unsigned char fp_so_ex_str_frz[2];                        /* @0x002DDB98 size 0x2 */
static unsigned char fp_so_ex_str_step[6];                       /* @0x002DDBA0 size 0x6 */
static unsigned char fp_so_ex_str_play[1];                       /* @0x002DDBA8 size 0x1 */
static unsigned char *fp_so_ex_str_no[11];                       /* @0x002BC3E0 size 0x2C */
static int fp_so_sp_tbl[6];                                      /* @0x002BC410 size 0x18 */
static int fp_so_turn_tbl[13];                                   /* @0x002BC430 size 0x34 */
anon_25_75 *sow;                                                 /* @0x002DE528 size 0x4 */
anon_22_75 *fpw;                                                 /* @0x002DE540 size 0x4 */
anon_21_75 *msw;                                                 /* @0x002DE52C size 0x4 */
anon_5_75 *stw;                                                  /* @0x002DE538 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
unsigned char fp_ms_ud_tab[7];                                   /* @0x002DDB10 size 0x7 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
static int fp_op_step_kind_tbl[5];                               /* not allocated size 0x14 */

/* functions defined (16) */
static int fp_so_win_disap(void *w);                             /* 0x00220DF0-0x00220EBC lines 1341-1365 */
static int fp_so_win_exec(void *w);                              /* 0x00220EC0-0x00220FF8 lines 1304-1338 */
static int fp_so_win_apper(void *w);                             /* 0x00221000-0x002212CC lines 1245-1301 */
static int fp_so_item_one_disp(float cx, float cy, unsigned char pid, unsigned char item_no, unsigned char kind, unsigned char alpha); /* 0x002212D0-0x00221938 lines 1113-1239 */
static void fp_so_line_disp(float x0, float y0, unsigned char alpha); /* 0x00221940-0x00221B38 lines 1087-1108 */
static int fp_so_item_disp(void *w);                             /* 0x00221B40-0x0022285C lines 872-1084 */
static int fp_so_item_disap(void *w);                            /* 0x00222860-0x00222904 lines 835-869 */
static int fp_so_item_exec(void *w);                             /* 0x00222910-0x00222990 lines 822-832 */
static int fp_so_item_apper(void *w);                            /* 0x00222990-0x00222BAC lines 776-815 */
static int fp_so_disap(void);                                    /* 0x00222BB0-0x00222D14 lines 714-767 */
static int fp_so_apper(void);                                    /* 0x00222D20-0x00222E28 lines 676-711 */
void fp_sel_option_finish_all(void);                             /* 0x00222E30-0x00223090 lines 586-644 */
void fp_sel_option_finish(void);                                 /* 0x00223090-0x00223160 lines 573-581 */
int fp_sel_option_step(void);                                    /* 0x00223160-0x00223AE8 lines 359-565 */
void fp_sel_option_init(void);                                   /* 0x00223AF0-0x00223CF4 lines 290-354 */
void fp_sel_option_init_all(void);                               /* 0x00223D00-0x00223F98 lines 226-285 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_opt_c_H */
