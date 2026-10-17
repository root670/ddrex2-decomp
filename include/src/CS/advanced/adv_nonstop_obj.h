/*
 * C:\work2\usaex2\src\CS\advanced\adv_nonstop_obj.c
 * MW MIPS C Compiler, overlay main; 33 functions, code 0x0026C130-0x00271F64
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_advanced_adv_nonstop_obj_c_H
#define DDR_UNIT_src_CS_advanced_adv_nonstop_obj_c_H

#include "types/G_SYS_W_.h"
#include "types/_ADVANCED_MODE_W.h"
#include "types/_LES_RECT.h"
#include "types/_tag_cCoCursor01.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/tex_bind.h"

/* anonymous types (21) */

/* anon_0_150 -- @anon0, 0x1C bytes, adv_nonstop_obj.c (DIE 0x295E5E) */
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
} anon_0_150;

/* anon_1_150 -- @anon1, 0x34 bytes, adv_nonstop_obj.c (DIE 0x2961C5) */
typedef struct {   // size 0x34
    /* 0x000 */ short t;                              // 0x2
    /* 0x002 */ short t_max;                          // 0x2
    /* 0x004 */ float x;                              // 0x4
    /* 0x008 */ float y;                              // 0x4
    /* 0x00C */ float sx;                             // 0x4
    /* 0x010 */ float sy;                             // 0x4
    /* 0x014 */ unsigned char alpha;                  // 0x1
    /* 0x015 */ unsigned char salpha;                 // 0x1
    /* 0x016 */ unsigned char step;                   // 0x1
    /* 0x017 */ unsigned char dummy;                  // 0x1
    /* 0x018 */ short pri;                            // 0x2
    /* 0x01A */ // 0x2 bytes padding
    /* 0x01C */ struct _tag_cCoCursor01 cur_left_w;   // 0xC
    /* 0x028 */ struct _tag_cCoCursor01 cur_right_w;  // 0xC
} anon_1_150;

/* anon_2_150 -- @anon2, 0x1C bytes, adv_nonstop_obj.c (DIE 0x2964C3) */
typedef struct {   // size 0x1C
    /* 0x000 */ short t;                              // 0x2
    /* 0x002 */ short t_max;                          // 0x2
    /* 0x004 */ float x;                              // 0x4
    /* 0x008 */ float y;                              // 0x4
    /* 0x00C */ float sx;                             // 0x4
    /* 0x010 */ float sy;                             // 0x4
    /* 0x014 */ unsigned char alpha;                  // 0x1
    /* 0x015 */ unsigned char salpha;                 // 0x1
    /* 0x016 */ unsigned char step;                   // 0x1
    /* 0x017 */ unsigned char dummy;                  // 0x1
    /* 0x018 */ short pri;                            // 0x2
    /* 0x01A */ // 0x2 bytes padding
} anon_2_150;

/* anon_3_150 -- @anon3, 0xC bytes, adv_nonstop_obj.c (DIE 0x2966F8) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_3_150;

/* anon_14_150 -- @anon14, 0x90 bytes, adv_nonstop_obj.c (DIE 0x29B19E) */
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
} anon_14_150;

/* anon_19_150 -- @anon19, 0xC bytes, adv_nonstop_obj.c (DIE 0x29C256) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_19_150;

/* anon_6_150 -- @anon6, 0x494 bytes, adv_nonstop_obj.c (DIE 0x2978A3) */
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
} anon_6_150;

/* anon_12_150 -- @anon12, 0x8 bytes, adv_nonstop_obj.c (DIE 0x29AF21) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_12_150;

/* anon_15_150 -- @anon15, 0x70 bytes, adv_nonstop_obj.c (DIE 0x29B424) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_12_150 one[11];                  // 0x58
} anon_15_150;

/* anon_21_150 -- @anon21, 0x34 bytes, adv_nonstop_obj.c (DIE 0x29CBF5) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_21_150;

/* anon_23_150 -- @anon23, 0xA0 bytes, adv_nonstop_obj.c (DIE 0x29D052) */
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
    /* 0x038 */ anon_21_150 eva[2];                   // 0x68
} anon_23_150;

/* anon_4_150 -- @anon4, 0x7E0 bytes, adv_nonstop_obj.c (DIE 0x29677D) */
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
    /* 0x170 */ anon_14_150 doll;                     // 0x90
    /* 0x200 */ anon_3_150 eyetoy;                    // 0xC
    /* 0x20C */ anon_19_150 style;                    // 0xC
    /* 0x218 */ anon_0_150 chara;                     // 0x1C
    /* 0x234 */ anon_6_150 music;                     // 0x494
    /* 0x6C8 */ anon_15_150 option;                   // 0x70
    /* 0x738 */ anon_23_150 result;                   // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_4_150;

/* anon_10_150 -- @anon10, 0x4 bytes, adv_nonstop_obj.c (DIE 0x29A35E) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_10_150;

/* anon_5_150 -- @anon5, 0x34 bytes, adv_nonstop_obj.c (DIE 0x296F36) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_10_150 x0;                       // 0x4
    /* 0x004 */ anon_10_150 y0;                       // 0x4
    /* 0x008 */ anon_10_150 x1;                       // 0x4
    /* 0x00C */ anon_10_150 y1;                       // 0x4
    /* 0x010 */ anon_10_150 x2;                       // 0x4
    /* 0x014 */ anon_10_150 y2;                       // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
} anon_5_150;

/* anon_8_150 -- @anon8, 0x48 bytes, adv_nonstop_obj.c (DIE 0x29808E) */
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
} anon_8_150;

/* anon_13_150 -- @anon13, 0x10 bytes, adv_nonstop_obj.c (DIE 0x29B035) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_10_150 x0;                       // 0x4
    /* 0x004 */ anon_10_150 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_13_150;

/* anon_11_150 -- @anon11, 0x30 bytes, adv_nonstop_obj.c (DIE 0x29AD2B) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_10_150 x0;                       // 0x4
    /* 0x004 */ anon_10_150 y0;                       // 0x4
    /* 0x008 */ anon_10_150 x1;                       // 0x4
    /* 0x00C */ anon_10_150 y1;                       // 0x4
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
} anon_11_150;

/* anon_16_150 -- @anon16, 0x10 bytes, adv_nonstop_obj.c (DIE 0x29B5A9) */
typedef struct {   // size 0x10
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *name;                           // 0x4
    /* 0x008 */ void *item;                           // 0x4
    /* 0x00C */ int timer;                            // 0x4
} anon_16_150;

/* anon_17_150 -- @anon17, 0x70 bytes, adv_nonstop_obj.c (DIE 0x29B808) */
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
} anon_17_150;

/* anon_20_150 -- @anon20, 0x8 bytes, adv_nonstop_obj.c (DIE 0x29C320) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_20_150;

/* anon_22_150 -- @anon22, 0x10 bytes, adv_nonstop_obj.c (DIE 0x29CF75) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_22_150;


/* variables (17) */
anon_17_150 *nstop_wp;                                           /* @0x002DDDD4 size 0x4 */
anon_22_150 advanced_sel0_objf;                                  /* @0x002C0630 size 0x10 */
anon_22_150 advanced_sel1_objf;                                  /* @0x002C0640 size 0x10 */
anon_22_150 nonstop_meter_objf;                                  /* @0x002C0650 size 0x10 */
anon_22_150 nonstop_music_objf;                                  /* @0x002C0660 size 0x10 */
anon_22_150 nonstop_level_objf;                                  /* @0x002C0670 size 0x10 */
anon_22_150 nonstop_order_objf;                                  /* @0x002C0680 size 0x10 */
anon_4_150 *fpw;                                                 /* @0x002DE540 size 0x4 */
struct _ADVANCED_MODE_W *advwp;                                  /* @0x002DDDC0 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_16_150 *adv_meter_wp;                                       /* @0x002DDD74 size 0x4 */
struct music_info minfo_tab[84];                                 /* @0x002A86E0 size 0x3480 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
anon_22_150 fp_objf[];                                           /* @0x002BBD80 */
anon_22_150 advanced_name_objf;                                  /* @0x002C0010 size 0x10 */
anon_22_150 advanced_window_objf;                                /* @0x002C05B0 size 0x10 */
anon_17_150 adv_nonstop_w;                                       /* @0x00722340 size 0x70 */

/* functions defined (33) */
static void nonstop_order_info_select(void);                     /* 0x0026C130-0x0026C4AC lines 2315-2386 */
static void nonstop_order_index_select(void);                    /* 0x0026C4B0-0x0026C690 lines 2246-2271 */
static void nonstop_course_select(void);                         /* 0x0026C690-0x0026C9C0 lines 2088-2172 */
static void set_nonstop_course_change(void);                     /* 0x0026C9C0-0x0026CB58 lines 2057-2086 */
static void set_nonstop_course_prim(void);                       /* 0x0026CB60-0x0026CBE8 lines 2032-2051 */
int get_nonstop_meter_type(void);                                /* 0x0026CBF0-0x0026CBFC lines 2027-2028 */
int get_nonstop_course_no(void);                                 /* 0x0026CC00-0x0026CC0C lines 2017-2018 */
static void set_nonstop_course_list(void);                       /* 0x0026CC10-0x0026CD68 lines 1975-2013 */
static int nonstop_order_item_disp(void *w);                     /* 0x0026CD70-0x0026DA9C lines 1757-1972 */
static int nonstop_order_item_disap(void *w);                    /* 0x0026DAA0-0x0026DCB8 lines 1706-1754 */
static int nonstop_order_item_exec(void);                        /* 0x0026DCC0-0x0026DCC8 lines 1703-1703 */
static int nonstop_order_item_apper(void *w);                    /* 0x0026DCD0-0x0026DFF8 lines 1632-1697 */
static int nonstop_left_item_disp(void *w);                      /* 0x0026E000-0x0026EAB8 lines 1422-1627 */
static int nonstop_left_item_disap(void *w);                     /* 0x0026EAC0-0x0026ED4C lines 1368-1419 */
static int nonstop_left_item_exec(void *w);                      /* 0x0026ED50-0x0026ED88 lines 1358-1365 */
static int nonstop_left_item_apper(void *w);                     /* 0x0026ED90-0x0026F0DC lines 1290-1354 */
static int nonstop_music_item_disp(void *w);                     /* 0x0026F0E0-0x0026F7A8 lines 1149-1285 */
static int nonstop_music_item_disap(void *w);                    /* 0x0026F7B0-0x0026F9E0 lines 1074-1146 */
static int nonstop_music_item_exec(void *w);                     /* 0x0026F9E0-0x0026FD3C lines 1028-1071 */
static int nonstop_music_item_apper(void *w);                    /* 0x0026FD40-0x002700E4 lines 949-1025 */
static int nonstop_meter_disp(void *w);                          /* 0x002700F0-0x00270484 lines 870-944 */
static int nonstop_meter_disap(void *w);                         /* 0x00270490-0x00270648 lines 824-867 */
static int nonstop_meter_exec(void);                             /* 0x00270650-0x00270658 lines 821-821 */
static int nonstop_meter_apper(void *w);                         /* 0x00270660-0x002708F0 lines 769-815 */
static int adv_sel1_disp(void *w);                               /* 0x002708F0-0x00270A88 lines 702-763 */
static int adv_sel0_disp(void *w);                               /* 0x00270A90-0x00270E44 lines 620-699 */
static int adv_sel0_disap(void *w);                              /* 0x00270E50-0x00270FE0 lines 571-617 */
static int adv_sel0_exec(void);                                  /* 0x00270FE0-0x00270FE8 lines 568-568 */
static int adv_sel0_apper(void *w);                              /* 0x00270FF0-0x00271290 lines 515-562 */
void adv_nonstop_sel_finish_all(void);                           /* 0x00271290-0x0027131C lines 501-513 */
void adv_nonstop_sel_finish(void);                               /* 0x00271320-0x00271328 lines 499-499 */
int adv_nonstop_sel_step(void);                                  /* 0x00271330-0x00271E3C lines 215-496 */
void adv_nonstop_sel_init(void);                                 /* 0x00271E40-0x00271F64 lines 182-212 */

#endif /* DDR_UNIT_src_CS_advanced_adv_nonstop_obj_c_H */
