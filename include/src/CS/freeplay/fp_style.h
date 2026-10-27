/*
 * C:\work2\usaex2\src\CS\freeplay\fp_style.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x00217650-0x002199B8
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
#ifndef DDR_UNIT_src_CS_freeplay_fp_style_c_H
#define DDR_UNIT_src_CS_freeplay_fp_style_c_H

#include "types/G_SYS_W_.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (15) */

/* anon_1_73 -- @anon1, 0x494 bytes, fp_style.c (DIE 0x1242FA) */
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
} anon_1_73;

/* anon_2_73 -- @anon2, 0x8 bytes, fp_style.c (DIE 0x124B2F) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_2_73;

/* anon_3_73 -- @anon3, 0x10 bytes, fp_style.c (DIE 0x125048) */
typedef union {   // size 0x10
    /* 0x000 */ unsigned __int128 ul128;              // 0x10
    /* 0x000 */ unsigned long ul64[2];                // 0x10
    /* 0x000 */ unsigned int ui32[4];                 // 0x10
    /* 0x000 */ int i32[4];                           // 0x10
    /* 0x000 */ float f32[4];                         // 0x10
    /* 0x000 */ float fv[4];                          // 0x10
    /* 0x000 */ int iv[4];                            // 0x10
} anon_3_73;

/* anon_5_73 -- @anon5, 0x20 bytes, fp_style.c (DIE 0x1254E3) */
typedef struct {   // size 0x20
    /* 0x000 */ float ofs[4];                         // 0x10
    /* 0x010 */ float t;                              // 0x4
    /* 0x014 */ float rot_y;                          // 0x4
    /* 0x018 */ int step;                             // 0x4
    /* 0x01C */ // 0x4 bytes padding
} __attribute__((aligned(16))) anon_5_73;

/* anon_7_73 -- @anon7, 0x8 bytes, fp_style.c (DIE 0x127CC5) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_7_73;

/* anon_9_73 -- @anon9, 0x90 bytes, fp_style.c (DIE 0x1282D7) */
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
} anon_9_73;

/* anon_13_73 -- @anon13, 0xC bytes, fp_style.c (DIE 0x128AC8) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_13_73;

/* anon_14_73 -- @anon14, 0xC bytes, fp_style.c (DIE 0x128D29) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_14_73;

/* anon_28_73 -- @anon28, 0x1C bytes, fp_style.c (DIE 0x12B9B4) */
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
} anon_28_73;

/* anon_11_73 -- @anon11, 0x70 bytes, fp_style.c (DIE 0x12867E) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_7_73 one[11];                    // 0x58
} anon_11_73;

/* anon_24_73 -- @anon24, 0x34 bytes, fp_style.c (DIE 0x12A0EB) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_24_73;

/* anon_26_73 -- @anon26, 0xA0 bytes, fp_style.c (DIE 0x12AD2F) */
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
    /* 0x038 */ anon_24_73 eva[2];                    // 0x68
} anon_26_73;

/* anon_8_73 -- @anon8, 0x7E0 bytes, fp_style.c (DIE 0x127E4A) */
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
    /* 0x170 */ anon_9_73 doll;                       // 0x90
    /* 0x200 */ anon_13_73 eyetoy;                    // 0xC
    /* 0x20C */ anon_14_73 style;                     // 0xC
    /* 0x218 */ anon_28_73 chara;                     // 0x1C
    /* 0x234 */ anon_1_73 music;                      // 0x494
    /* 0x6C8 */ anon_11_73 option;                    // 0x70
    /* 0x738 */ anon_26_73 result;                    // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding
} __attribute__((aligned(16))) anon_8_73;

/* anon_22_73 -- @anon22, 0x4 bytes, fp_style.c (DIE 0x129E4B) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
} anon_22_73;

/* anon_27_73 -- @anon27, 0x10 bytes, fp_style.c (DIE 0x12B705) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_27_73;


/* variables (15) */
unsigned char fp_style_tab[4];                                   /* @0x002DDB38 size 0x4 */
anon_27_73 fp_ss_objf[2];                                        /* @0x002BBFF0 size 0x20 */
static float ss_3item_xy[3][4];                                  /* @0x002BC010 size 0x30 */
static float ss_4item_xy[4][4];                                  /* @0x002BC040 size 0x40 */
anon_8_73 *fpw;                                                  /* @0x002DE540 size 0x4 */
anon_14_73 *stw;                                                 /* @0x002DE538 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
anon_9_73 *dw;                                                   /* @0x002DE534 size 0x4 */
anon_27_73 fp_objf[];                                            /* @0x002BBD80 */
anon_27_73 fp_fpanel_objf;                                       /* @0x002BE770 size 0x10 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_1_73 *msw;                                                  /* @0x002DE52C size 0x4 */
anon_11_73 *sow;                                                 /* @0x002DE528 size 0x4 */
anon_13_73 *etw;                                                 /* @0x002DE53C size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (14) */
static int fp_ss_display_disp(void);                             /* 0x00217650-0x002179AC lines 1095-1162 */
static int fp_ss_display_disap(void);                            /* 0x002179B0-0x002179B8 lines 1093-1093 */
static int fp_ss_display_apper(void);                            /* 0x002179C0-0x002179C8 lines 1089-1089 */
static int fp_ss_item_disp(void *w);                             /* 0x002179D0-0x00218674 lines 724-1081 */
static int fp_ss_item_disap(void *w);                            /* 0x00218680-0x00218954 lines 660-720 */
static int fp_ss_item_exec(void *w);                             /* 0x00218960-0x00218AC4 lines 599-657 */
static int fp_ss_item_apper(void *w);                            /* 0x00218AD0-0x00218DB4 lines 533-596 */
static int fp_ss_disap(void);                                    /* 0x00218DC0-0x00219074 lines 417-524 */
static int fp_ss_apper(void);                                    /* 0x00219080-0x00219280 lines 356-414 */
void fp_style_sel_finish_all(void);                              /* 0x00219280-0x002193E0 lines 315-348 */
void fp_style_sel_finish(void);                                  /* 0x002193E0-0x00219514 lines 271-310 */
int fp_style_sel_step(void);                                     /* 0x00219520-0x00219870 lines 137-267 */
void fp_style_sel_init(void);                                    /* 0x00219870-0x00219948 lines 106-135 */
void fp_style_sel_init_all(void);                                /* 0x00219950-0x002199B8 lines 90-101 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_style_c_H */
