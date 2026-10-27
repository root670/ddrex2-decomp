/*
 * C:\work2\usaex2\src\CS\freeplay\fp_eyetoy.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x0020F090-0x0020F8A8
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
#ifndef DDR_UNIT_src_CS_freeplay_fp_eyetoy_c_H
#define DDR_UNIT_src_CS_freeplay_fp_eyetoy_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_tag_cCoCursor01.h"
#include "types/g_game_w.h"
#include "types/tex_bind.h"

/* anonymous types (13) */

/* anon_1_70 -- @anon1, 0xC bytes, fp_eyetoy.c (DIE 0x108E32) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_1_70;

/* anon_2_70 -- @anon2, 0x34 bytes, fp_eyetoy.c (DIE 0x109016) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_2_70;

/* anon_3_70 -- @anon3, 0xA0 bytes, fp_eyetoy.c (DIE 0x10AF0B) */
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
    /* 0x038 */ anon_2_70 eva[2];                     // 0x68
} anon_3_70;

/* anon_4_70 -- @anon4, 0x10 bytes, fp_eyetoy.c (DIE 0x10B18E) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_4_70;

/* anon_5_70 -- @anon5, 0x24 bytes, fp_eyetoy.c (DIE 0x10B291) */
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
} anon_5_70;

/* anon_6_70 -- @anon6, 0x1C bytes, fp_eyetoy.c (DIE 0x10B44B) */
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
} anon_6_70;

/* anon_18_70 -- @anon18, 0x90 bytes, fp_eyetoy.c (DIE 0x10E22C) */
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
} anon_18_70;

/* anon_12_70 -- @anon12, 0xC bytes, fp_eyetoy.c (DIE 0x10C029) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_12_70;

/* anon_13_70 -- @anon13, 0x494 bytes, fp_eyetoy.c (DIE 0x10C349) */
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
} anon_13_70;

/* anon_15_70 -- @anon15, 0x8 bytes, fp_eyetoy.c (DIE 0x10DBC3) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_15_70;

/* anon_16_70 -- @anon16, 0x70 bytes, fp_eyetoy.c (DIE 0x10DCD7) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_15_70 one[11];                   // 0x58
} anon_16_70;

/* anon_7_70 -- @anon7, 0x7E0 bytes, fp_eyetoy.c (DIE 0x10B799) */
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
    /* 0x170 */ anon_18_70 doll;                      // 0x90
    /* 0x200 */ anon_12_70 eyetoy;                    // 0xC
    /* 0x20C */ anon_1_70 style;                      // 0xC
    /* 0x218 */ anon_6_70 chara;                      // 0x1C
    /* 0x234 */ anon_13_70 music;                     // 0x494
    /* 0x6C8 */ anon_16_70 option;                    // 0x70
    /* 0x738 */ anon_3_70 result;                     // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding
} __attribute__((aligned(16))) anon_7_70;

/* anon_9_70 -- @anon9, 0x10 bytes, fp_eyetoy.c (DIE 0x10BCF0) */
typedef struct {   // size 0x10
    /* 0x000 */ struct _CWS_WIN_W *win;               // 0x4
    /* 0x004 */ struct _tag_cCoCursor01 cur_w;        // 0xC
} anon_9_70;


/* variables (10) */
static anon_4_70 fp_es_objf[2];                                  /* @0x002BB890 size 0x20 */
static unsigned char fp_es_ask[12];                              /* not allocated size 0xC */
static unsigned char fp_es_yes[4];                               /* not allocated size 0x4 */
static unsigned char fp_es_no[3];                                /* not allocated size 0x3 */
anon_12_70 *etw;                                                 /* @0x002DE53C size 0x4 */
anon_7_70 *fpw;                                                  /* @0x002DE540 size 0x4 */
struct tex_bind tex_bind[375];                                   /* @0x0058C390 size 0x2904 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_13_70 *msw;                                                 /* @0x002DE52C size 0x4 */
anon_1_70 *stw;                                                  /* @0x002DE538 size 0x4 */

/* functions defined (11) */
static int fp_es_warn_disp(void);                                /* 0x0020F090-0x0020F098 lines 384-384 */
static int fp_es_warn_disap(void);                               /* 0x0020F0A0-0x0020F0A8 lines 381-381 */
static int fp_es_warn_exec(void);                                /* 0x0020F0B0-0x0020F0B8 lines 378-378 */
static int fp_es_warn_apper(void);                               /* 0x0020F0C0-0x0020F0C8 lines 375-375 */
static int fp_es_item_disp(void *w);                             /* 0x0020F0D0-0x0020F214 lines 333-368 */
static int fp_es_item_func(void *w);                             /* 0x0020F220-0x0020F470 lines 264-331 */
void fp_eyetoy_sel_finish_all(void);                             /* 0x0020F470-0x0020F5C0 lines 150-181 */
void fp_eyetoy_sel_finish(void);                                 /* 0x0020F5C0-0x0020F5C8 lines 145-145 */
int fp_eyetoy_sel_step(void);                                    /* 0x0020F5D0-0x0020F81C lines 96-138 */
void fp_eyetoy_sel_init(void);                                   /* 0x0020F820-0x0020F86C lines 83-91 */
void fp_eyetoy_sel_init_all(void);                               /* 0x0020F870-0x0020F8A8 lines 68-78 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_eyetoy_c_H */
