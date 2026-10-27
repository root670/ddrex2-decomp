/*
 * C:\work2\usaex2\src\CS\advanced\adv_topmenu_obj.c
 * MW MIPS C Compiler, overlay main; 37 functions, code 0x0025F3E0-0x0026379C
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
#ifndef DDR_UNIT_src_CS_advanced_adv_topmenu_obj_c_H
#define DDR_UNIT_src_CS_advanced_adv_topmenu_obj_c_H

#include "types/_ADVANCED_MODE_W.h"
#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_EDS_GAME_DATA.h"
#include "types/_LES_RECT.h"
#include "types/_tag_cCoCursor01.h"
#include "types/g_game_w.h"

/* anonymous types (20) */

/* anon_0_147 -- @anon0, 0x1C bytes, adv_topmenu_obj.c (DIE 0x271E22) */
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
} anon_0_147;

/* anon_1_147 -- @anon1, 0x38 bytes, adv_topmenu_obj.c (DIE 0x272041) */
typedef struct {   // size 0x38
    /* 0x000 */ int t;                                // 0x4
    /* 0x004 */ int t_max;                            // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ float sx;                             // 0x4
    /* 0x014 */ float sy;                             // 0x4
    /* 0x018 */ float fx;                             // 0x4
    /* 0x01C */ float fy;                             // 0x4
    /* 0x020 */ float ofs_x;                          // 0x4
    /* 0x024 */ float ofs_y;                          // 0x4
    /* 0x028 */ unsigned char alpha;                  // 0x1
    /* 0x029 */ unsigned char salpha;                 // 0x1
    /* 0x02A */ unsigned char Mode;                   // 0x1
    /* 0x02B */ unsigned char step;                   // 0x1
    /* 0x02C */ unsigned char flag;                   // 0x1
    /* 0x02D */ unsigned char dummy;                  // 0x1
    /* 0x02E */ // 0x2 bytes padding
    /* 0x030 */ int anime_timer;                      // 0x4
    /* 0x034 */ int anime_frame;                      // 0x4
} anon_1_147;

/* anon_2_147 -- @anon2, 0xC bytes, adv_topmenu_obj.c (DIE 0x2722B6) */
typedef struct {   // size 0xC
    /* 0x000 */ int alpha;                            // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step_old;                         // 0x4
} anon_2_147;

/* anon_3_147 -- @anon3, 0xC bytes, adv_topmenu_obj.c (DIE 0x2726B6) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_3_147;

/* anon_17_147 -- @anon17, 0x90 bytes, adv_topmenu_obj.c (DIE 0x277021) */
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
} anon_17_147;

/* anon_21_147 -- @anon21, 0xC bytes, adv_topmenu_obj.c (DIE 0x277AEA) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_21_147;

/* anon_5_147 -- @anon5, 0x494 bytes, adv_topmenu_obj.c (DIE 0x272F9B) */
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
} anon_5_147;

/* anon_14_147 -- @anon14, 0x8 bytes, adv_topmenu_obj.c (DIE 0x2768A0) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_14_147;

/* anon_18_147 -- @anon18, 0x70 bytes, adv_topmenu_obj.c (DIE 0x2772A7) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_14_147 one[11];                  // 0x58
} anon_18_147;

/* anon_22_147 -- @anon22, 0x34 bytes, adv_topmenu_obj.c (DIE 0x2783F1) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_22_147;

/* anon_24_147 -- @anon24, 0xA0 bytes, adv_topmenu_obj.c (DIE 0x2789DE) */
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
    /* 0x038 */ anon_22_147 eva[2];                   // 0x68
} anon_24_147;

/* anon_4_147 -- @anon4, 0x7E0 bytes, adv_topmenu_obj.c (DIE 0x27273B) */
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
    /* 0x170 */ anon_17_147 doll;                     // 0x90
    /* 0x200 */ anon_3_147 eyetoy;                    // 0xC
    /* 0x20C */ anon_21_147 style;                    // 0xC
    /* 0x218 */ anon_0_147 chara;                     // 0x1C
    /* 0x234 */ anon_5_147 music;                     // 0x494
    /* 0x6C8 */ anon_18_147 option;                   // 0x70
    /* 0x738 */ anon_24_147 result;                   // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding
} __attribute__((aligned(16))) anon_4_147;

/* anon_7_147 -- @anon7, 0x48 bytes, adv_topmenu_obj.c (DIE 0x273786) */
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
} anon_7_147;

/* anon_8_147 -- @anon8, 0x178 bytes, adv_topmenu_obj.c (DIE 0x273A2C) */
typedef struct {   // size 0x178
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char step_s;                 // 0x1
    /* 0x002 */ unsigned char cursor;                 // 0x1
    /* 0x003 */ unsigned char cursor_max;             // 0x1
    /* 0x004 */ unsigned char menu_data[16];          // 0x10
    /* 0x014 */ unsigned char option_step;            // 0x1
    /* 0x015 */ unsigned char curX;                   // 0x1
    /* 0x016 */ unsigned char curY;                   // 0x1
    /* 0x017 */ unsigned char cur_batch;              // 0x1
    /* 0x018 */ int music_line_num[12];               // 0x30
    /* 0x048 */ int cur_music;                        // 0x4
    /* 0x04C */ int top_music;                        // 0x4
    /* 0x050 */ int MusicMax;                         // 0x4
    /* 0x054 */ int PlayMusicMax;                     // 0x4
    /* 0x058 */ unsigned char MusicNo[76];            // 0x4C
    /* 0x0A4 */ unsigned char PlayTbl[76];            // 0x4C
    /* 0x0F0 */ struct _EDS_GAME_DATA data;           // 0x34
    /* 0x124 */ void *window;                         // 0x4
    /* 0x128 */ void *name;                           // 0x4
    /* 0x12C */ void *frame;                          // 0x4
    /* 0x130 */ void *menu_item;                      // 0x4
    /* 0x134 */ void *program_item;                   // 0x4
    /* 0x138 */ void *program_title;                  // 0x4
    /* 0x13C */ void *program_cursor;                 // 0x4
    /* 0x140 */ int timer;                            // 0x4
    /* 0x144 */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x150 */ struct _COM_SCROLLBAR_WORK sb;        // 0x28
} anon_8_147;

/* anon_19_147 -- @anon19, 0x18 bytes, adv_topmenu_obj.c (DIE 0x277498) */
typedef struct {   // size 0x18
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ float btn_cx;                         // 0x4
    /* 0x008 */ float btn_cy;                         // 0x4
    /* 0x00C */ int ex;                               // 0x4
    /* 0x010 */ float ex_x;                           // 0x4
    /* 0x014 */ float ex_cy;                          // 0x4
} anon_19_147;

/* anon_11_147 -- @anon11, 0x18 bytes, adv_topmenu_obj.c (DIE 0x2764FC) */
typedef struct {   // size 0x18
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char fp_step;                // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ float dx;                             // 0x4
    /* 0x008 */ float dy;                             // 0x4
    /* 0x00C */ float t;                              // 0x4
    /* 0x010 */ anon_19_147 *info[2];                 // 0x8
} anon_11_147;

/* anon_12_147 -- @anon12, 0x10 bytes, adv_topmenu_obj.c (DIE 0x2765E0) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *name;                           // 0x4
    /* 0x008 */ void *item;                           // 0x4
    /* 0x00C */ int timer;                            // 0x4
} anon_12_147;

/* anon_13_147 -- @anon13, 0x30 bytes, adv_topmenu_obj.c (DIE 0x2766AA) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
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
} anon_13_147;

/* anon_16_147 -- @anon16, 0x70 bytes, adv_topmenu_obj.c (DIE 0x276AD5) */
typedef struct {   // size 0x70
    /* 0x000 */ int mode;                             // 0x4
    /* 0x004 */ unsigned char step;                   // 0x1
    /* 0x005 */ unsigned char step_s;                 // 0x1
    /* 0x006 */ unsigned char curX;                   // 0x1
    /* 0x007 */ unsigned char curY;                   // 0x1
    /* 0x008 */ unsigned char maxX;                   // 0x1
    /* 0x009 */ unsigned char maxY;                   // 0x1
    /* 0x00A */ unsigned char cur_level;              // 0x1
    /* 0x00B */ unsigned char cur_level_max;          // 0x1
    /* 0x00C */ unsigned char cur_music;              // 0x1
    /* 0x00D */ unsigned char top_music;              // 0x1
    /* 0x00E */ unsigned char cur_orderX;             // 0x1
    /* 0x00F */ unsigned char cur_order_maxX;         // 0x1
    /* 0x010 */ unsigned char cur_orderY;             // 0x1
    /* 0x011 */ unsigned char cur_order_maxY;         // 0x1
    /* 0x012 */ unsigned char option_step;            // 0x1
    /* 0x013 */ unsigned char dummy00;                // 0x1
    /* 0x014 */ unsigned char dummy01;                // 0x1
    /* 0x015 */ unsigned char dummy02;                // 0x1
    /* 0x016 */ short db;                             // 0x2
    /* 0x018 */ short course_id;                      // 0x2
    /* 0x01A */ short course_max;                     // 0x2
    /* 0x01C */ short course_music_max;               // 0x2
    /* 0x01E */ short course_music_num;               // 0x2
    /* 0x020 */ short course_music_list[20];          // 0x28
    /* 0x048 */ void *window;                         // 0x4
    /* 0x04C */ void *name;                           // 0x4
    /* 0x050 */ void *frame;                          // 0x4
    /* 0x054 */ void *meter;                          // 0x4
    /* 0x058 */ void *left_item[2];                   // 0x8
    /* 0x060 */ void *music_item[2];                  // 0x8
    /* 0x068 */ void *order_item;                     // 0x4
    /* 0x06C */ int timer;                            // 0x4
} anon_16_147;

/* anon_23_147 -- @anon23, 0x10 bytes, adv_topmenu_obj.c (DIE 0x278901) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_23_147;


/* variables (19) */
anon_12_147 *adv_meter_wp;                                       /* @0x002DDD74 size 0x4 */
anon_12_147 *adv_diff_wp;                                        /* @0x002DDD78 size 0x4 */
anon_23_147 advanced_top_objf;                                   /* @0x002BFF20 size 0x10 */
anon_23_147 advanced_button_objf;                                /* @0x002BFF30 size 0x10 */
static anon_19_147 advanced_btn_info[4];                         /* @0x002BFF90 size 0x60 */
anon_23_147 advanced_meter_objf;                                 /* @0x002BFFF0 size 0x10 */
anon_23_147 advanced_difficulty_objf;                            /* @0x002C0000 size 0x10 */
anon_23_147 advanced_name_objf;                                  /* @0x002C0010 size 0x10 */
anon_23_147 adv_display_objf[2];                                 /* @0x002C0080 size 0x20 */
anon_4_147 *fpw;                                                 /* @0x002DE540 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_23_147 fp_objf[];                                           /* @0x002BBD80 */
anon_17_147 *dw;                                                 /* @0x002DE534 size 0x4 */
anon_23_147 fp_fpanel_objf;                                      /* @0x002BE770 size 0x10 */
struct _ADVANCED_MODE_W *advwp;                                  /* @0x002DDDC0 size 0x4 */
anon_8_147 *endless_wp;                                          /* @0x002DDDA8 size 0x4 */
anon_16_147 *nstop_wp;                                           /* @0x002DDDD4 size 0x4 */
anon_12_147 adv_difficulty_w;                                    /* @0x00722050 size 0x10 */
anon_12_147 adv_meter_w;                                         /* @0x00722060 size 0x10 */

/* functions defined (37) */
static int adv_ds_display_disp(void *w);                         /* 0x0025F3E0-0x0025F670 lines 1760-1799 */
static int adv_ds_display_disap(void);                           /* 0x0025F670-0x0025F678 lines 1758-1758 */
static int adv_ds_display_exec(void *w);                         /* 0x0025F680-0x0025F6B8 lines 1747-1753 */
static int adv_ds_display_apper(void *w);                        /* 0x0025F6C0-0x0025F704 lines 1726-1736 */
static int adv_ms_display_disp(void *w);                         /* 0x0025F710-0x0025F9A8 lines 1684-1723 */
static int adv_ms_display_disap(void);                           /* 0x0025F9B0-0x0025F9B8 lines 1682-1682 */
static int adv_ms_display_exec(void *w);                         /* 0x0025F9C0-0x0025F9F8 lines 1671-1677 */
static int adv_ms_display_apper(void *w);                        /* 0x0025FA00-0x0025FA44 lines 1650-1660 */
static int adv_name_disp(void *w);                               /* 0x0025FA50-0x0025FE70 lines 1542-1615 */
static int adv_name_disap(void *w);                              /* 0x0025FE70-0x00260030 lines 1493-1539 */
static int adv_name_exec(void);                                  /* 0x00260030-0x00260038 lines 1490-1490 */
static int adv_name_apper(void *w);                              /* 0x00260040-0x002602A0 lines 1423-1484 */
static int adv_difficulty_item_disp(void *w);                    /* 0x002602A0-0x00260680 lines 1334-1421 */
static int adv_difficulty_item_disap(void *w);                   /* 0x00260680-0x002608A0 lines 1280-1331 */
static int adv_difficulty_item_exec(void);                       /* 0x002608A0-0x002608A8 lines 1277-1277 */
static int adv_difficulty_item_apper(void *w);                   /* 0x002608B0-0x00260D38 lines 1216-1271 */
static int adv_meter_item_disp(void *w);                         /* 0x00260D40-0x002613E0 lines 1082-1214 */
static int adv_meter_item_disap(void *w);                        /* 0x002613E0-0x002615D0 lines 1028-1079 */
static int adv_meter_item_exec(void);                            /* 0x002615D0-0x002615D8 lines 1025-1025 */
static int adv_meter_item_apper(void *w);                        /* 0x002615E0-0x00261938 lines 964-1019 */
void adv_difficulty_sel_finish_all(void);                        /* 0x00261940-0x002619EC lines 950-962 */
void adv_difficulty_sel_finish(void);                            /* 0x002619F0-0x002619F8 lines 948-948 */
int adv_difficulty_sel_step(void);                               /* 0x00261A00-0x00261E70 lines 822-945 */
void adv_difficulty_sel_init(void);                              /* 0x00261E70-0x00261E98 lines 816-820 */
void adv_meter_sel_finish(void);                                 /* 0x00261EA0-0x00261EA8 lines 810-810 */
int adv_meter_sel_step(void);                                    /* 0x00261EB0-0x00262388 lines 658-807 */
void adv_meter_sel_init(void);                                   /* 0x00262390-0x002623B8 lines 652-656 */
static int adv_btn_disp(void *w);                                /* 0x002623C0-0x00262520 lines 514-578 */
static int adv_btn_move(void *w);                                /* 0x00262520-0x00262618 lines 480-512 */
static int adv_top_item_disp(void *w);                           /* 0x00262620-0x00262C68 lines 327-451 */
static int adv_top_item_disap(void *w);                          /* 0x00262C70-0x00262E70 lines 273-324 */
static int adv_top_item_exec(void);                              /* 0x00262E70-0x00262E78 lines 270-270 */
static int adv_top_item_apper(void *w);                          /* 0x00262E80-0x00263290 lines 209-264 */
void adv_topmenu_sel_finish(void);                               /* 0x00263290-0x0026336C lines 189-204 */
int adv_topmenu_sel_step(void);                                  /* 0x00263370-0x002636B4 lines 92-187 */
void adv_topmenu_sel_init(void);                                 /* 0x002636C0-0x00263790 lines 72-90 */
void adv_topmenu_sel_init_all(void);                             /* 0x00263790-0x0026379C lines 68-68 */

#endif /* DDR_UNIT_src_CS_advanced_adv_topmenu_obj_c_H */
