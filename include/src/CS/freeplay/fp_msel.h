/*
 * C:\work2\usaex2\src\CS\freeplay\fp_msel.c
 * MW MIPS C Compiler, overlay main; 22 functions, code 0x0020A460-0x0020F084
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_freeplay_fp_msel_c_H
#define DDR_UNIT_src_CS_freeplay_fp_msel_c_H

#include "types/_tag_cDDR8Record1.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cMusicData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (20) */

/* anon_11_69 -- @anon11, 0x4 bytes, fp_msel.c (DIE 0x101ACE) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_11_69;

/* anon_16_69 -- @anon16, 0x10 bytes, fp_msel.c (DIE 0x1027A5) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_11_69 x0;                        // 0x4
    /* 0x004 */ anon_11_69 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_16_69;

/* anon_25_69 -- @anon25, 0x34 bytes, fp_msel.c (DIE 0x106249) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_25_69;

/* anon_1_69 -- @anon1, 0xA0 bytes, fp_msel.c (DIE 0xFF6A6) */
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
    /* 0x038 */ anon_25_69 eva[2];                    // 0x68
} anon_1_69;

/* anon_2_69 -- @anon2, 0x10 bytes, fp_msel.c (DIE 0x10048D) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_2_69;

/* anon_3_69 -- @anon3, 0x1C bytes, fp_msel.c (DIE 0x100906) */
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
} anon_3_69;

/* anon_4_69 -- @anon4, 0xD40 bytes, fp_msel.c (DIE 0x100AFC) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_4_69;

/* anon_5_69 -- @anon5, 0x14 bytes, fp_msel.c (DIE 0x100E52) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_5_69;

/* anon_6_69 -- @anon6, 0xC bytes, fp_msel.c (DIE 0x1010FB) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_6_69;

/* anon_8_69 -- @anon8, 0xC bytes, fp_msel.c (DIE 0x101350) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_8_69;

/* anon_22_69 -- @anon22, 0x90 bytes, fp_msel.c (DIE 0x10540B) */
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
} anon_22_69;

/* anon_15_69 -- @anon15, 0xC bytes, fp_msel.c (DIE 0x1026DB) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_15_69;

/* anon_12_69 -- @anon12, 0x494 bytes, fp_msel.c (DIE 0x101CA4) */
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
} anon_12_69;

/* anon_21_69 -- @anon21, 0x8 bytes, fp_msel.c (DIE 0x1046DC) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_21_69;

/* anon_19_69 -- @anon19, 0x70 bytes, fp_msel.c (DIE 0x1035E2) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_21_69 one[11];                   // 0x58
} anon_19_69;

/* anon_9_69 -- @anon9, 0x7E0 bytes, fp_msel.c (DIE 0x1014E0) */
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
    /* 0x170 */ anon_22_69 doll;                      // 0x90
    /* 0x200 */ anon_6_69 eyetoy;                     // 0xC
    /* 0x20C */ anon_15_69 style;                     // 0xC
    /* 0x218 */ anon_3_69 chara;                      // 0x1C
    /* 0x234 */ anon_12_69 music;                     // 0x494
    /* 0x6C8 */ anon_19_69 option;                    // 0x70
    /* 0x738 */ anon_1_69 result;                     // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_9_69;

/* anon_14_69 -- @anon14, 0x4 bytes, fp_msel.c (DIE 0x10269B) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_14_69;

/* anon_13_69 -- @anon13, 0x4 bytes, fp_msel.c (DIE 0x102424) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_14_69 s;                         // 0x4
} anon_13_69;

/* anon_17_69 -- @anon17, 0x12E0 bytes, fp_msel.c (DIE 0x1028C6) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_8_69 history[400];               // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_17_69;

/* anon_24_69 -- @anon24, 0x8 bytes, fp_msel.c (DIE 0x105BAB) */
typedef struct {   // size 0x8
    /* 0x000 */ int score;                            // 0x4
    /* 0x004 */ char rank;                            // 0x1
    /* 0x005 */ unsigned char is_fcombo;              // 0x1
    /* 0x006 */ // 0x2 bytes padding
} anon_24_69;


/* variables (13) */
unsigned char fp_ms_ud_tab[7];                                   /* @0x002DDB10 size 0x7 */
char fp_ms_difficulty_tab[7];                                    /* @0x002DDB18 size 0x7 */
unsigned char fp_msm_tab[4];                                     /* @0x002DDB20 size 0x4 */
anon_12_69 *msw;                                                 /* @0x002DE52C size 0x4 */
anon_9_69 *fpw;                                                  /* @0x002DE540 size 0x4 */
anon_2_69 fp_ms_objf[];                                          /* @0x002BEA80 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
anon_15_69 *stw;                                                 /* @0x002DE538 size 0x4 */
unsigned char fp_ms_ename[360];                                  /* @0x0071E620 size 0x168 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
unsigned char fp_ms_disp_ename[360];                             /* @0x0071E4B0 size 0x168 */
anon_6_69 *etw;                                                  /* @0x002DE53C size 0x4 */
anon_19_69 *sow;                                                 /* @0x002DE528 size 0x4 */

/* functions defined (22) */
int editmode_music_sel_step(void);                               /* 0x0020A460-0x0020AA58 lines 2334-2515 */
void editmode_music_sel_set(void);                               /* 0x0020AA60-0x0020AAD0 lines 2317-2325 */
int nonstop_music_sel_step(void);                                /* 0x0020AAD0-0x0020B1C0 lines 2118-2298 */
void nonstop_music_sel_set(void);                                /* 0x0020B1C0-0x0020B214 lines 2104-2109 */
int fp_ms_get_dnum_info(int d_num, int diff, anon_24_69 *d_info); /* 0x0020B220-0x0020B3B0 lines 2045-2089 */
int fp_is_step_exist(short d_num, int diff);                     /* 0x0020B3B0-0x0020B4D0 lines 1994-2035 */
int fp_ms_adj_cur_ud(short d_num, int pid);                      /* 0x0020B4D0-0x0020B5DC lines 1901-1934 */
void fp_ms_close_abc_kind(int d_num);                            /* 0x0020B5E0-0x0020B6C8 lines 1869-1896 */
void fp_ms_open_abc_kind(int d_num);                             /* 0x0020B6D0-0x0020B984 lines 1839-1863 */
short fp_ms_get_abc_kind(short d_num);                           /* 0x0020B990-0x0020BA88 lines 1809-1833 */
void fp_ms_set_cur_lr(void);                                     /* 0x0020BA90-0x0020BB38 lines 1778-1800 */
void fp_ms_create_sel_tab(void);                                 /* 0x0020BB40-0x0020C270 lines 1520-1773 */
int fp_msel_get_sn(short d_num);                                 /* 0x0020C270-0x0020C324 lines 1459-1478 */
void fp_msel_sd_call(unsigned int call, float time);             /* 0x0020C330-0x0020C38C lines 1446-1454 */
static int fp_ms_roulette(int *scr_end);                         /* 0x0020C390-0x0020CA10 lines 1268-1440 */
static int fp_ms_ed_mcard(void);                                 /* 0x0020CA10-0x0020CE74 lines 1128-1262 */
unsigned int fp_ms_PadRepeat(unsigned int key);                  /* 0x0020CE80-0x0020CF00 lines 1104-1121 */
void fp_music_sel_finish_all(void);                              /* 0x0020CF00-0x0020D6EC lines 812-1095 */
void fp_music_sel_finish(void);                                  /* 0x0020D6F0-0x0020D714 lines 800-807 */
int fp_music_sel_step(void);                                     /* 0x0020D720-0x0020E908 lines 326-794 */
void fp_music_sel_init(void);                                    /* 0x0020E910-0x0020ED6C lines 236-321 */
void fp_music_sel_init_all(void);                                /* 0x0020ED70-0x0020F084 lines 159-231 */

#endif /* DDR_UNIT_src_CS_freeplay_fp_msel_c_H */
