/*
 * C:\work2\usaex2\src\CS\freeplay\fp_qmenu.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x00286F90-0x002876E8
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
#ifndef DDR_UNIT_src_CS_freeplay_fp_qmenu_c_H
#define DDR_UNIT_src_CS_freeplay_fp_qmenu_c_H

#include "types/_OPTMC_W.h"
#include "types/_tag_cCmes.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (12) */

/* anon_0_170 -- @anon0, 0xC bytes, fp_qmenu.c (DIE 0x2FC124) */
typedef struct {   // size 0xC
    /* 0x000 */ int (*func)();                        // 0x4
    /* 0x004 */ int (*ini)();                         // 0x4
    /* 0x008 */ unsigned char *str;                   // 0x4
} anon_0_170;

/* anon_1_170 -- @anon1, 0xC bytes, fp_qmenu.c (DIE 0x2FC34C) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_1_170;

/* anon_2_170 -- @anon2, 0x34 bytes, fp_qmenu.c (DIE 0x2FC4AB) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_2_170;

/* anon_3_170 -- @anon3, 0xA0 bytes, fp_qmenu.c (DIE 0x2FCA46) */
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
    /* 0x038 */ anon_2_170 eva[2];                    // 0x68
} anon_3_170;

/* anon_4_170 -- @anon4, 0x10 bytes, fp_qmenu.c (DIE 0x2FCD83) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_4_170;

/* anon_6_170 -- @anon6, 0x1C bytes, fp_qmenu.c (DIE 0x2FD101) */
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
} anon_6_170;

/* anon_20_170 -- @anon20, 0x90 bytes, fp_qmenu.c (DIE 0x301073) */
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
} anon_20_170;

/* anon_10_170 -- @anon10, 0xC bytes, fp_qmenu.c (DIE 0x2FDD0C) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_10_170;

/* anon_15_170 -- @anon15, 0x494 bytes, fp_qmenu.c (DIE 0x2FE6AC) */
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
} anon_15_170;

/* anon_18_170 -- @anon18, 0x8 bytes, fp_qmenu.c (DIE 0x300D67) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_18_170;

/* anon_19_170 -- @anon19, 0x70 bytes, fp_qmenu.c (DIE 0x300F14) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_18_170 one[11];                  // 0x58
} anon_19_170;

/* anon_8_170 -- @anon8, 0x7E0 bytes, fp_qmenu.c (DIE 0x2FD59E) */
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
    /* 0x170 */ anon_20_170 doll;                     // 0x90
    /* 0x200 */ anon_10_170 eyetoy;                   // 0xC
    /* 0x20C */ anon_1_170 style;                     // 0xC
    /* 0x218 */ anon_6_170 chara;                     // 0x1C
    /* 0x234 */ anon_15_170 music;                    // 0x494
    /* 0x6C8 */ anon_19_170 option;                   // 0x70
    /* 0x738 */ anon_3_170 result;                    // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_8_170;


/* variables (19) */
static anon_0_170 fp_qm_save;                                    /* @0x002C1B30 size 0xC */
static anon_0_170 fp_qm_rec;                                     /* @0x002C1B40 size 0xC */
static anon_0_170 fp_qm_sort;                                    /* @0x002C1B50 size 0xC */
static anon_0_170 fp_qm_camera;                                  /* @0x002C1B60 size 0xC */
struct _OPTMC_W *qmsw;                                           /* @0x002DDE0C size 0x4 */
static anon_0_170 *fp_nms_qm[2];                                 /* @0x002DDE10 size 0x8 */
static anon_0_170 *fp_ms_qm[4];                                  /* @0x002C1B70 size 0x10 */
static anon_0_170 *fp_ms_qm_eye[5];                              /* @0x002C1B80 size 0x14 */
static anon_0_170 *fp_ms_qm_edi[3];                              /* @0x002C1B98 size 0xC */
static anon_0_170 *fp_ms_qm_edi_eye[4];                          /* @0x002C1BB0 size 0x10 */
int RequestAutoSave;                                             /* @0x002DE1AC size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
anon_8_170 *fpw;                                                 /* @0x002DE540 size 0x4 */
struct _tag_cCmes *pCmes;                                        /* @0x002DA1D4 size 0x4 */
anon_15_170 *msw;                                                /* @0x002DE52C size 0x4 */
anon_4_170 fp_ms_objf[];                                         /* @0x002BEA80 */
unsigned char fp_msm_tab[];                                      /* @0x002DDB20 */
anon_10_170 *etw;                                                /* @0x002DE53C size 0x4 */
struct _OPTMC_W fp_qm_save_w;                                    /* @0x007230F0 size 0x54 */

/* functions defined (6) */
static int fp_qm_save_exec(void);                                /* 0x00286F90-0x0028707C lines 266-299 */
static int fp_qm_save_func(void);                                /* 0x00287080-0x002871A8 lines 224-263 */
static int fp_qm_save_init(void);                                /* 0x002871B0-0x002871E4 lines 216-221 */
static int fp_qm_sort_func(void);                                /* 0x002871F0-0x00287438 lines 163-210 */
static int fp_qm_sort_ini(void);                                 /* 0x00287440-0x00287450 lines 158-160 */
int fp_qmenu_func(void);                                         /* 0x00287450-0x002876E8 lines 88-148 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_qmenu_c_H */
