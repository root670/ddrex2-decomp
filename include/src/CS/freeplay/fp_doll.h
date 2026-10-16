/*
 * C:\work2\usaex2\src\CS\freeplay\fp_doll.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x0022F990-0x00230540
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_freeplay_fp_doll_c_H
#define DDR_UNIT_src_CS_freeplay_fp_doll_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (28) */

/* anon_0_98 -- @anon0, 0x10 bytes, fp_doll.c (DIE 0x1AFD2C) */
struct anon_0_98 {   // size 0x10
    /* 0x000 */ float ofs_x;                          // 0x4
    /* 0x004 */ float ofs_y;                          // 0x4
    /* 0x008 */ int step;                             // 0x4
    /* 0x00C */ void *doll;                           // 0x4
};

/* anon_1_98 -- @anon1, 0x320 bytes, fp_doll.c (DIE 0x1AFE66) */
struct anon_1_98 {   // size 0x320
    /* 0x000 */ float cam_p[4];                       // 0x10
    /* 0x010 */ float eye_p[4];                       // 0x10
    /* 0x020 */ float cam_zd[4];                      // 0x10
    /* 0x030 */ float cam_yd[4];                      // 0x10
    /* 0x040 */ float cam_rot[4];                     // 0x10
    /* 0x050 */ float lgt_amb[4];                     // 0x10
    /* 0x060 */ float lgt_vec[3][4];                  // 0x30
    /* 0x090 */ float lgt_col[3][4];                  // 0x30
    /* 0x0C0 */ float obj_trans[4];                   // 0x10
    /* 0x0D0 */ float obj_rot[4];                     // 0x10
    /* 0x0E0 */ float fog[4];                         // 0x10
    /* 0x0F0 */ float local_world[4][4];              // 0x40
    /* 0x130 */ float world_view[4][4];               // 0x40
    /* 0x170 */ float view_screen[4][4];              // 0x40
    /* 0x1B0 */ float local_screen[4][4];             // 0x40
    /* 0x1F0 */ float normal_light[4][4];             // 0x40
    /* 0x230 */ float light_color[4][4];              // 0x40
    /* 0x270 */ float local_light[4][4];              // 0x40
    /* 0x2B0 */ float local_color[4][4];              // 0x40
    /* 0x2F0 */ int pkind;                            // 0x4
    /* 0x2F4 */ int pnum;                             // 0x4
    /* 0x2F8 */ int vnct;                             // 0x4
    /* 0x2FC */ int vsize;                            // 0x4
    /* 0x300 */ unsigned int prim;                    // 0x4
    /* 0x304 */ float (*vp)[4];                       // 0x4
    /* 0x308 */ float (*np)[4];                       // 0x4
    /* 0x30C */ float (*tp)[4];                       // 0x4
    /* 0x310 */ float (*cp)[4];                       // 0x4
    /* 0x314 */ // 0xC bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_10_98 -- @anon10, 0x4 bytes, fp_doll.c (DIE 0x1B38F3) */
union anon_10_98 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_14_98 -- @anon14, 0x10 bytes, fp_doll.c (DIE 0x1B3F11) */
struct anon_14_98 {   // size 0x10
    /* 0x000 */ union anon_10_98 x0;                  // 0x4
    /* 0x004 */ union anon_10_98 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_2_98 -- @anon2, 0x184 bytes, fp_doll.c (DIE 0x1B0337) */
struct anon_2_98 {   // size 0x184
    /* 0x000 */ struct anon_14_98 line_a[8];          // 0x80
    /* 0x080 */ struct anon_14_98 line_b[8];          // 0x80
    /* 0x100 */ struct anon_14_98 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_3_98 -- @anon3, 0x8 bytes, fp_doll.c (DIE 0x1B277B) */
struct anon_3_98 {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
};

/* anon_5_98 -- @anon5, 0x90 bytes, fp_doll.c (DIE 0x1B2E90) */
struct anon_5_98 {   // size 0x90
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

/* anon_7_98 -- @anon7, 0xC bytes, fp_doll.c (DIE 0x1B3297) */
struct anon_7_98 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
};

/* anon_9_98 -- @anon9, 0xC bytes, fp_doll.c (DIE 0x1B3673) */
struct anon_9_98 {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
};

/* anon_11_98 -- @anon11, 0x1C bytes, fp_doll.c (DIE 0x1B3951) */
struct anon_11_98 {   // size 0x1C
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

/* anon_25_98 -- @anon25, 0x494 bytes, fp_doll.c (DIE 0x1B7B79) */
struct anon_25_98 {   // size 0x494
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

/* anon_6_98 -- @anon6, 0x70 bytes, fp_doll.c (DIE 0x1B3115) */
struct anon_6_98 {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ struct anon_3_98 one[11];             // 0x58
};

/* anon_20_98 -- @anon20, 0x34 bytes, fp_doll.c (DIE 0x1B4C06) */
struct anon_20_98 {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
};

/* anon_22_98 -- @anon22, 0xA0 bytes, fp_doll.c (DIE 0x1B5953) */
struct anon_22_98 {   // size 0xA0
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
    /* 0x038 */ struct anon_20_98 eva[2];             // 0x68
};

/* anon_4_98 -- @anon4, 0x7E0 bytes, fp_doll.c (DIE 0x1B2993) */
struct anon_4_98 {   // size 0x7E0
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
    /* 0x170 */ struct anon_5_98 doll;                // 0x90
    /* 0x200 */ struct anon_7_98 eyetoy;              // 0xC
    /* 0x20C */ struct anon_9_98 style;               // 0xC
    /* 0x218 */ struct anon_11_98 chara;              // 0x1C
    /* 0x234 */ struct anon_25_98 music;              // 0x494
    /* 0x6C8 */ struct anon_6_98 option;              // 0x70
    /* 0x738 */ struct anon_22_98 result;             // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

/* anon_8_98 -- @anon8, 0xD40 bytes, fp_doll.c (DIE 0x1B331C) */
struct anon_8_98 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_12_98 -- @anon12, 0x14 bytes, fp_doll.c (DIE 0x1B3AD7) */
struct anon_12_98 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_13_98 -- @anon13, 0xC bytes, fp_doll.c (DIE 0x1B3DC8) */
struct anon_13_98 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_15_98 -- @anon15, 0x14 bytes, fp_doll.c (DIE 0x1B40E7) */
struct anon_15_98 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_16_98 -- @anon16, 0x1300 bytes, fp_doll.c (DIE 0x1B42B5) */
struct anon_16_98 {   // size 0x1300
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
    /* 0x360 */ struct anon_12_98 subject[200];       // 0xFA0
};

/* anon_18_98 -- @anon18, 0x4 bytes, fp_doll.c (DIE 0x1B46C7) */
struct anon_18_98 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_17_98 -- @anon17, 0x4 bytes, fp_doll.c (DIE 0x1B4620) */
union anon_17_98 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_18_98 s;                  // 0x4
};

/* anon_19_98 -- @anon19, 0x12E0 bytes, fp_doll.c (DIE 0x1B4989) */
struct anon_19_98 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_13_98 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_21_98 -- @anon21, 0x2134 bytes, fp_doll.c (DIE 0x1B4D6F) */
struct anon_21_98 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_17_98 userpass;            // 0x4
    /* 0x008 */ struct anon_19_98 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_8_98 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_23_98 -- @anon23, 0x4 bytes, fp_doll.c (DIE 0x1B5B8F) */
struct anon_23_98 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_24_98 -- @anon24, 0x10 bytes, fp_doll.c (DIE 0x1B5C8D) */
struct anon_24_98 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};

/* anon_26_98 -- @anon26, 0x4 bytes, fp_doll.c (DIE 0x1B82B1) */
struct anon_26_98 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_27_98 -- @anon27, 0x8 bytes, fp_doll.c (DIE 0x1B8464) */
struct anon_27_98 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (10) */
struct anon_24_98 fp_doll_objf;                                  /* @0x002BE760 size 0x10 */
struct anon_24_98 fp_fpanel_objf;                                /* @0x002BE770 size 0x10 */
struct anon_5_98 *dw;                                            /* @0x002DE534 size 0x4 */
struct anon_4_98 *fpw;                                           /* @0x002DE540 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct anon_11_98 *chw;                                          /* @0x002DE530 size 0x4 */
struct anon_7_98 *etw;                                           /* @0x002DE53C size 0x4 */
struct anon_9_98 *stw;                                           /* @0x002DE538 size 0x4 */
struct anon_1_98 *gs3d;                                          /* @0x002DD998 size 0x4 */

/* functions defined (11) */
static int fp_foot_panel_disp(void *w);                          /* 0x0022F990-0x0022FB8C lines 590-620 */
static int fp_foot_panel_disap(void *w);                         /* 0x0022FB90-0x0022FC60 lines 570-587 */
static int fp_foot_panel_exec(void *w);                          /* 0x0022FC60-0x0022FC90 lines 561-567 */
static int fp_foot_panel_apper(void *w);                         /* 0x0022FC90-0x0022FD90 lines 528-558 */
static int fp_doll_disp(void);                                   /* 0x0022FD90-0x0022FFBC lines 457-522 */
static int fp_doll_exec(void);                                   /* 0x0022FFC0-0x00230070 lines 347-454 */
static void fp_doll_set_pos(void);                               /* 0x00230070-0x002301C4 lines 279-313 */
void fp_doll_fpanel_update(void);                                /* 0x002301D0-0x00230314 lines 235-270 */
void fp_doll_cam_set(int pid, float mdl_x, float mdl_z);         /* 0x00230320-0x002303EC lines 220-229 */
int fp_doll_load(void);                                          /* 0x002303F0-0x00230500 lines 153-206 */
void fp_doll_init(void);                                         /* 0x00230500-0x00230540 lines 127-147 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_doll_c_H */
