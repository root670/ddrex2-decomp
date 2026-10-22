/*
 * C:\work2\usaex2\src\CS\freeplay\fp_chara.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x0020F8B0-0x00213680
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
#ifndef DDR_UNIT_src_CS_freeplay_fp_chara_c_H
#define DDR_UNIT_src_CS_freeplay_fp_chara_c_H

#include "types/G_SYS_W_.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (17) */

/* anon_0_71 -- @anon0, 0x24 bytes, fp_chara.c (DIE 0x10F3CD) */
typedef struct {   // size 0x24
    /* 0x000 */ float t;                              // 0x4
    /* 0x004 */ float rot_y;                          // 0x4
    /* 0x008 */ float len;                            // 0x4
    /* 0x00C */ float x;                              // 0x4
    /* 0x010 */ float dy;                             // 0x4
    /* 0x014 */ float cur_a[2];                       // 0x8
    /* 0x01C */ float cur_t;                          // 0x4
    /* 0x020 */ unsigned char step;                   // 0x1
    /* 0x021 */ // 0x3 bytes padding
} anon_0_71;

/* anon_1_71 -- @anon1, 0x4 bytes, fp_chara.c (DIE 0x10F673) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
} anon_1_71;

/* anon_3_71 -- @anon3, 0x14 bytes, fp_chara.c (DIE 0x110170) */
typedef struct {   // size 0x14
    /* 0x000 */ int name_u;                           // 0x4
    /* 0x004 */ int name_v;                           // 0x4
    /* 0x008 */ int face_u;                           // 0x4
    /* 0x00C */ int face_v;                           // 0x4
    /* 0x010 */ unsigned char doll;                   // 0x1
    /* 0x011 */ // 0x3 bytes padding
} anon_3_71;

/* anon_4_71 -- @anon4, 0x4 bytes, fp_chara.c (DIE 0x111DCB) */
typedef struct {   // size 0x4
    /* 0x000 */ float rot;                            // 0x4
} anon_4_71;

/* anon_5_71 -- @anon5, 0x8 bytes, fp_chara.c (DIE 0x112186) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_5_71;

/* anon_7_71 -- @anon7, 0x90 bytes, fp_chara.c (DIE 0x1128E3) */
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
} anon_7_71;

/* anon_10_71 -- @anon10, 0xC bytes, fp_chara.c (DIE 0x112E7E) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_10_71;

/* anon_12_71 -- @anon12, 0xC bytes, fp_chara.c (DIE 0x113280) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_12_71;

/* anon_14_71 -- @anon14, 0x1C bytes, fp_chara.c (DIE 0x11355F) */
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
} anon_14_71;

/* anon_16_71 -- @anon16, 0x494 bytes, fp_chara.c (DIE 0x113946) */
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
} anon_16_71;

/* anon_8_71 -- @anon8, 0x70 bytes, fp_chara.c (DIE 0x112B68) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_5_71 one[11];                    // 0x58
} anon_8_71;

/* anon_24_71 -- @anon24, 0x34 bytes, fp_chara.c (DIE 0x114F9A) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_24_71;

/* anon_26_71 -- @anon26, 0xA0 bytes, fp_chara.c (DIE 0x115D0B) */
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
    /* 0x038 */ anon_24_71 eva[2];                    // 0x68
} anon_26_71;

/* anon_6_71 -- @anon6, 0x7E0 bytes, fp_chara.c (DIE 0x11239E) */
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
    /* 0x170 */ anon_7_71 doll;                       // 0x90
    /* 0x200 */ anon_10_71 eyetoy;                    // 0xC
    /* 0x20C */ anon_12_71 style;                     // 0xC
    /* 0x218 */ anon_14_71 chara;                     // 0x1C
    /* 0x234 */ anon_16_71 music;                     // 0x494
    /* 0x6C8 */ anon_8_71 option;                     // 0x70
    /* 0x738 */ anon_26_71 result;                    // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_6_71;

/* anon_9_71 -- @anon9, 0x24 bytes, fp_chara.c (DIE 0x112CEA) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
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
} anon_9_71;

/* anon_28_71 -- @anon28, 0x10 bytes, fp_chara.c (DIE 0x116045) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_28_71;

/* anon_30_71 -- @anon30, 0x8 bytes, fp_chara.c (DIE 0x11819D) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_30_71;


/* variables (13) */
static anon_3_71 fp_cs_info[48];                                 /* @0x002BB8B0 size 0x3C0 */
anon_28_71 fp_cs_objf[3];                                        /* @0x002BBC70 size 0x30 */
anon_6_71 *fpw;                                                  /* @0x002DE540 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
anon_14_71 *chw;                                                 /* @0x002DE530 size 0x4 */
anon_7_71 *dw;                                                   /* @0x002DE534 size 0x4 */
anon_12_71 *stw;                                                 /* @0x002DE538 size 0x4 */
anon_28_71 fp_fpanel_objf;                                       /* @0x002BE770 size 0x10 */
anon_28_71 fp_objf[];                                            /* @0x002BBD80 */
anon_16_71 *msw;                                                 /* @0x002DE52C size 0x4 */
anon_10_71 *etw;                                                 /* @0x002DE53C size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */

/* functions defined (19) */
static int fp_cs_entry_disp(void *w);                            /* 0x0020F8B0-0x0020F980 lines 1353-1371 */
static int fp_cs_entry_exec(void *w);                            /* 0x0020F980-0x0020F9E4 lines 1339-1350 */
static int fp_cs_display_disp(void *w);                          /* 0x0020F9F0-0x002102B4 lines 1190-1333 */
static int fp_cs_display_disap(void);                            /* 0x002102C0-0x002102C8 lines 1188-1188 */
static int fp_cs_display_exec(void *w);                          /* 0x002102D0-0x00210320 lines 1179-1184 */
static int fp_cs_display_apper(void *w);                         /* 0x00210320-0x00210340 lines 1165-1173 */
static int fp_cs_item_disp(void *w);                             /* 0x00210340-0x00211AA8 lines 827-1153 */
static int fp_cs_item_disap(void *w);                            /* 0x00211AB0-0x00211D20 lines 766-824 */
static int fp_cs_item_exec(void *w);                             /* 0x00211D20-0x00211DC8 lines 730-763 */
static int fp_cs_item_apper(void *w);                            /* 0x00211DD0-0x00211FE8 lines 671-724 */
static int fp_cs_disap(void);                                    /* 0x00211FF0-0x00212214 lines 580-662 */
static int fp_cs_apper(void);                                    /* 0x00212220-0x0021246C lines 514-577 */
void fp_set_new_entry(int pid);                                  /* 0x00212470-0x002125C0 lines 438-483 */
int fp_get_doll_num(int pid);                                    /* 0x002125C0-0x002125EC lines 412-413 */
void fp_chara_sel_finish_all(void);                              /* 0x002125F0-0x002127EC lines 365-404 */
void fp_chara_sel_finish(void);                                  /* 0x002127F0-0x002127F8 lines 361-361 */
int fp_chara_sel_step(void);                                     /* 0x00212800-0x0021333C lines 193-356 */
void fp_chara_sel_init(void);                                    /* 0x00213340-0x002135CC lines 163-188 */
void fp_chara_sel_init_all(void);                                /* 0x002135D0-0x00213680 lines 145-158 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_chara_c_H */
