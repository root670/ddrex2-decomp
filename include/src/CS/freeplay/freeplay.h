/*
 * C:\work2\usaex2\src\CS\freeplay\freeplay.c
 * MW MIPS C Compiler, overlay main; 40 functions, code 0x00213680-0x0021764C
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
#ifndef DDR_UNIT_src_CS_freeplay_freeplay_c_H
#define DDR_UNIT_src_CS_freeplay_freeplay_c_H

#include "types/_EYETOY_W.h"
#include "types/g_game_w.h"

/* anonymous types (22) */

/* anon_25_72 -- @anon25, 0x34 bytes, freeplay.c (DIE 0x120045) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_25_72;

/* anon_0_72 -- @anon0, 0xA0 bytes, freeplay.c (DIE 0x11A184) */
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
    /* 0x038 */ anon_25_72 eva[2];                    // 0x68
} anon_0_72;

/* anon_1_72 -- @anon1, 0x10 bytes, freeplay.c (DIE 0x11AB00) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_1_72;

/* anon_4_72 -- @anon4, 0x18 bytes, freeplay.c (DIE 0x11AF6A) */
typedef struct {   // size 0x18
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ float btn_cx;                         // 0x4
    /* 0x008 */ float btn_cy;                         // 0x4
    /* 0x00C */ int ex;                               // 0x4
    /* 0x010 */ float ex_x;                           // 0x4
    /* 0x014 */ float ex_cy;                          // 0x4
} anon_4_72;

/* anon_2_72 -- @anon2, 0x18 bytes, freeplay.c (DIE 0x11ABB8) */
typedef struct {   // size 0x18
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char fp_step;                // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ float dx;                             // 0x4
    /* 0x008 */ float dy;                             // 0x4
    /* 0x00C */ float t;                              // 0x4
    /* 0x010 */ anon_4_72 *info[2];                   // 0x8
} anon_2_72;

/* anon_3_72 -- @anon3, 0x48 bytes, freeplay.c (DIE 0x11AC9B) */
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
} anon_3_72;

/* anon_5_72 -- @anon5, 0x1C bytes, freeplay.c (DIE 0x11B051) */
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
} anon_5_72;

/* anon_6_72 -- @anon6, 0xC bytes, freeplay.c (DIE 0x11B6EE) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_6_72;

/* anon_7_72 -- @anon7, 0x10 bytes, freeplay.c (DIE 0x11B773) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_7_72;

/* anon_8_72 -- @anon8, 0x8 bytes, freeplay.c (DIE 0x11B880) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
} anon_8_72;

/* anon_9_72 -- @anon9, 0x1C bytes, freeplay.c (DIE 0x11B948) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_9_72;

/* anon_10_72 -- @anon10, 0xC bytes, freeplay.c (DIE 0x11C386) */
typedef struct {   // size 0xC
    /* 0x000 */ void *obj_p;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ unsigned char step;                   // 0x1
    /* 0x009 */ unsigned char next;                   // 0x1
    /* 0x00A */ // 0x2 bytes padding
} anon_10_72;

/* anon_11_72 -- @anon11, 0x494 bytes, freeplay.c (DIE 0x11C44F) */
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
} anon_11_72;

/* anon_12_72 -- @anon12, 0x4 bytes, freeplay.c (DIE 0x11CB87) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
} anon_12_72;

/* anon_16_72 -- @anon16, 0xC bytes, freeplay.c (DIE 0x11D1E1) */
typedef struct {   // size 0xC
    /* 0x000 */ int mode_quit_flg;                    // 0x4
    /* 0x004 */ int state;                            // 0x4
    /* 0x008 */ int renewal_record_flag;              // 0x4
} anon_16_72;

/* anon_21_72 -- @anon21, 0x90 bytes, freeplay.c (DIE 0x11F6CE) */
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
} anon_21_72;

/* anon_24_72 -- @anon24, 0xC bytes, freeplay.c (DIE 0x11FF57) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_24_72;

/* anon_19_72 -- @anon19, 0x8 bytes, freeplay.c (DIE 0x11EAC2) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_19_72;

/* anon_20_72 -- @anon20, 0x70 bytes, freeplay.c (DIE 0x11F4FD) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_19_72 one[11];                   // 0x58
} anon_20_72;

/* anon_18_72 -- @anon18, 0x7E0 bytes, freeplay.c (DIE 0x11D590) */
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
    /* 0x170 */ anon_21_72 doll;                      // 0x90
    /* 0x200 */ anon_6_72 eyetoy;                     // 0xC
    /* 0x20C */ anon_24_72 style;                     // 0xC
    /* 0x218 */ anon_5_72 chara;                      // 0x1C
    /* 0x234 */ anon_11_72 music;                     // 0x494
    /* 0x6C8 */ anon_20_72 option;                    // 0x70
    /* 0x738 */ anon_0_72 result;                     // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding
} __attribute__((aligned(16))) anon_18_72;

/* anon_22_72 -- @anon22, 0x8 bytes, freeplay.c (DIE 0x11FA2E) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_22_72;

/* anon_26_72 -- @anon26, 0xC bytes, freeplay.c (DIE 0x120978) */
typedef struct {   // size 0xC
    /* 0x000 */ void (*ini)();                        // 0x4
    /* 0x004 */ int (*stp)();                         // 0x4
    /* 0x008 */ void (*fin)();                        // 0x4
} anon_26_72;


/* variables (24) */
static anon_26_72 fp_func[13];                                   /* @0x002BBCE0 size 0x9C */
anon_1_72 fp_objf[2];                                            /* @0x002BBD80 size 0x20 */
static anon_4_72 fp_btn_style[5];                                /* @0x002BBDA0 size 0x78 */
anon_4_72 fp_btn_chara[5];                                       /* @0x002BBE20 size 0x78 */
anon_4_72 fp_btn_msel[5];                                        /* @0x002BBEA0 size 0x78 */
anon_4_72 tr_btn_msel[3];                                        /* @0x002BBF20 size 0x48 */
anon_4_72 fp_btn_opt[4];                                         /* @0x002BBF70 size 0x60 */
anon_18_72 *fpw;                                                 /* @0x002DE540 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_11_72 *msw;                                                 /* @0x002DE52C size 0x4 */
anon_24_72 *stw;                                                 /* @0x002DE538 size 0x4 */
anon_0_72 *rsw;                                                  /* @0x002DE524 size 0x4 */
anon_20_72 *sow;                                                 /* @0x002DE528 size 0x4 */
anon_5_72 *chw;                                                  /* @0x002DE530 size 0x4 */
anon_21_72 *dw;                                                  /* @0x002DE534 size 0x4 */
anon_6_72 *etw;                                                  /* @0x002DE53C size 0x4 */
anon_18_72 fp_work;                                              /* @0x0071E790 size 0x7E0 */
anon_1_72 adv_display_objf[];                                    /* @0x002C0080 */
anon_1_72 fp_ms_objf[];                                          /* @0x002BEA80 */
anon_1_72 fp_cs_objf[];                                          /* @0x002BBC70 */
anon_1_72 fp_ss_objf[];                                          /* @0x002BBFF0 */
struct _EYETOY_W *EYETOYW;                                       /* @0x002DD9A8 size 0x4 */
anon_8_72 mg_solo_bin[];                                         /* @0x002DD400 */
anon_16_72 usr_work;                                             /* @0x00328A20 size 0xC */

/* functions referenced (2) */
void fp_trans_title_th(void *);                                  /* @0x00215E20 */
void fp_bind_load_th(void *);                                    /* @0x00215D60 */

/* functions defined (40) */
int editmode_msel_pre(void);                                     /* 0x00213680-0x0021374C lines 2369-2388 */
void editmode_msel_init(unsigned char *addr);                    /* 0x00213750-0x00213848 lines 2333-2366 */
void onlineplay_result_finish(void);                             /* 0x00213850-0x00213914 lines 2283-2318 */
int onlineplay_result_step(void);                                /* 0x00213920-0x002139E0 lines 2208-2278 */
void onlineplay_result_init(void);                               /* 0x002139E0-0x00213D18 lines 2097-2202 */
void onlineplay_chara_finish(void);                              /* 0x00213D20-0x00213D4C lines 2082-2091 */
int onlineplay_chara_step(void);                                 /* 0x00213D50-0x00213E10 lines 2009-2076 */
void onlineplay_chara_init(void);                                /* 0x00213E10-0x00214080 lines 1953-2004 */
int dmm_freeplay_step(void);                                     /* 0x00214080-0x002142C4 lines 1893-1944 */
int dmm_freeplay_result_load(void);                              /* 0x002142D0-0x0021436C lines 1867-1889 */
void dmm_freeplay_result_init(unsigned char *addr);              /* 0x00214370-0x002147BC lines 1767-1864 */
void dmm_freeplay_chara_finish(int *id_1, int *id_2);            /* 0x002147C0-0x002148C8 lines 1751-1762 */
int dmm_freeplay_chara_load(void);                               /* 0x002148D0-0x002149CC lines 1704-1747 */
void dmm_freeplay_chara_init(unsigned char *addr);               /* 0x002149D0-0x00214DE4 lines 1612-1701 */
int fp_win_disp_obj(void);                                       /* 0x00214DF0-0x00214E10 lines 1599-1602 */
static int fp_display_disp(void);                                /* 0x00214E10-0x00214ED8 lines 1571-1594 */
static int fp_display_disap(void *w);                            /* 0x00214EE0-0x00214F10 lines 1562-1568 */
static int fp_display_exec(void *w);                             /* 0x00214F10-0x00215344 lines 1471-1560 */
static int fp_btn_disp(void *w);                                 /* 0x00215350-0x00215558 lines 1400-1464 */
static int fp_btn_change(void *w);                               /* 0x00215560-0x0021576C lines 1344-1398 */
static int fp_btn_move(void *w);                                 /* 0x00215770-0x002158C0 lines 1302-1340 */
void fp_make_enenu_str20(short lim_x, unsigned char *str);       /* 0x002158C0-0x002159C8 lines 1242-1282 */
unsigned char *fp_OutStrGet(int id);                             /* 0x002159D0-0x002159EC lines 1228-1237 */
float fp_RotTransPersF(float *v0, float (*m0)[4], float *v1);    /* 0x002159F0-0x00215A5C lines 1214-1222 */
void fp_ApplyMatrixXYZ1(float *v0, float (*m0)[4], float *v1);   /* 0x00215A60-0x00215A8C lines 1197-1208 */
static int fp_pre_end(void);                                     /* 0x00215A90-0x00215D5C lines 1091-1161 */
static void fp_bind_load_th(void);                               /* 0x00215D60-0x00215DE8 lines 991-1023 */
void fp_sel_tex_set(anon_3_72 *info, int _id);                   /* 0x00215DF0-0x00215E14 lines 984-988 */
void fp_trans_title_th(void);                                    /* 0x00215E20-0x00215EF8 lines 945-980 */
static int fp_prepare(void);                                     /* 0x00215F00-0x0021624C lines 818-943 */
void fp_prim_packet_set_sp_col(anon_22_72 pos, anon_22_72 uv, int pri, anon_12_72 col); /* 0x00216250-0x0021637C lines 757-809 */
void fp_prim_packet_set_sp(anon_22_72 pos, anon_22_72 uv, int pri, unsigned char alpha, unsigned char bri); /* 0x00216380-0x002164B8 lines 702-754 */
void fp_prim_packet_set_f4(float (*pos)[4], int pri, anon_12_72 col); /* 0x002164C0-0x00216660 lines 649-699 */
void fp_prim_packet_set_gt4(float (*pos)[4], float (*stq)[4], int pri, unsigned char alpha, unsigned char bri); /* 0x00216660-0x0021686C lines 551-646 */
int fp_cancel_quit_check(void);                                  /* 0x00216870-0x00216914 lines 524-543 */
unsigned int fp_PadPush(unsigned int key, unsigned int pid);     /* 0x00216920-0x00216AC4 lines 492-517 */
unsigned int fp_PadTrg(unsigned int key, unsigned int pid);      /* 0x00216AD0-0x00216C74 lines 464-489 */
void freeplay_finish(void);                                      /* 0x00216C80-0x00216D04 lines 433-454 */
int freeplay_step(void);                                         /* 0x00216D10-0x00216FF8 lines 330-428 */
void freeplay_init(unsigned char *addr);                         /* 0x00217000-0x0021764C lines 234-323 */

#endif /* DDR_UNIT_src_CS_freeplay_freeplay_c_H */
