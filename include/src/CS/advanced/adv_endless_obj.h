/*
 * C:\work2\usaex2\src\CS\advanced\adv_endless_obj.c
 * MW MIPS C Compiler, overlay main; 42 functions, code 0x002637A0-0x0026A354
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
#ifndef DDR_UNIT_src_CS_advanced_adv_endless_obj_c_H
#define DDR_UNIT_src_CS_advanced_adv_endless_obj_c_H

#include "types/G_SYS_W_.h"
#include "types/_ADVANCED_MODE_W.h"
#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_EDS_GAME_DATA.h"
#include "types/_LES_RECT.h"
#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cMusicData.h"
#include "types/g_game_w.h"
#include "types/music_info.h"
#include "types/oni_course.h"
#include "types/play_mode.h"
#include "types/play_w.h"
#include "types/tex_bind.h"

/* anonymous types (19) */

/* anon_0_148 -- @anon0, 0xC bytes, adv_endless_obj.c (DIE 0x27C95C) */
typedef struct {   // size 0xC
    /* 0x000 */ int mode_quit_flg;                    // 0x4
    /* 0x004 */ int state;                            // 0x4
    /* 0x008 */ int renewal_record_flag;              // 0x4
} anon_0_148;

/* anon_1_148 -- @anon1, 0x1C bytes, adv_endless_obj.c (DIE 0x27C9F7) */
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
} anon_1_148;

/* anon_2_148 -- @anon2, 0x1C bytes, adv_endless_obj.c (DIE 0x27CCCE) */
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
} anon_2_148;

/* anon_3_148 -- @anon3, 0xC bytes, adv_endless_obj.c (DIE 0x27E3FD) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int timer;                            // 0x4
    /* 0x008 */ void *item;                           // 0x4
} anon_3_148;

/* anon_17_148 -- @anon17, 0x90 bytes, adv_endless_obj.c (DIE 0x2840B5) */
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
} anon_17_148;

/* anon_26_148 -- @anon26, 0xC bytes, adv_endless_obj.c (DIE 0x2858C1) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char cur;                    // 0x1
    /* 0x001 */ unsigned char max;                    // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ void *item;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
} anon_26_148;

/* anon_7_148 -- @anon7, 0x494 bytes, adv_endless_obj.c (DIE 0x27FB0D) */
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
} anon_7_148;

/* anon_14_148 -- @anon14, 0x8 bytes, adv_endless_obj.c (DIE 0x2839BC) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned char n;                      // 0x1
    /* 0x001 */ unsigned char cur[2];                 // 0x2
    /* 0x003 */ // 0x1 bytes padding
    /* 0x004 */ unsigned char **str;                  // 0x4
} anon_14_148;

/* anon_18_148 -- @anon18, 0x70 bytes, adv_endless_obj.c (DIE 0x28433B) */
typedef struct {   // size 0x70
    /* 0x000 */ int timer;                            // 0x4
    /* 0x004 */ unsigned char cur[2];                 // 0x2
    /* 0x006 */ unsigned char auto_f[2];              // 0x2
    /* 0x008 */ float repcnt[2];                      // 0x8
    /* 0x010 */ void *item;                           // 0x4
    /* 0x014 */ void *win;                            // 0x4
    /* 0x018 */ anon_14_148 one[11];                  // 0x58
} anon_18_148;

/* anon_29_148 -- @anon29, 0x34 bytes, adv_endless_obj.c (DIE 0x285D9B) */
typedef struct {   // size 0x34
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int score;                            // 0x4
    /* 0x024 */ int bonus;                            // 0x4
    /* 0x028 */ int oni_point;                        // 0x4
    /* 0x02C */ short dance_level;                    // 0x2
    /* 0x02E */ unsigned char is_fcombo;              // 0x1
    /* 0x02F */ unsigned char is_newrec;              // 0x1
    /* 0x030 */ int pnt;                              // 0x4
} anon_29_148;

/* anon_32_148 -- @anon32, 0xA0 bytes, adv_endless_obj.c (DIE 0x286389) */
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
    /* 0x038 */ anon_29_148 eva[2];                   // 0x68
} anon_32_148;

/* anon_4_148 -- @anon4, 0x7E0 bytes, adv_endless_obj.c (DIE 0x27E482) */
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
    /* 0x170 */ anon_17_148 doll;                     // 0x90
    /* 0x200 */ anon_3_148 eyetoy;                    // 0xC
    /* 0x20C */ anon_26_148 style;                    // 0xC
    /* 0x218 */ anon_1_148 chara;                     // 0x1C
    /* 0x234 */ anon_7_148 music;                     // 0x494
    /* 0x6C8 */ anon_18_148 option;                   // 0x70
    /* 0x738 */ anon_32_148 result;                   // 0xA0
    /* 0x7D8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
} anon_4_148;

/* anon_5_148 -- @anon5, 0x178 bytes, adv_endless_obj.c (DIE 0x27F238) */
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
} anon_5_148;

/* anon_6_148 -- @anon6, 0x4 bytes, adv_endless_obj.c (DIE 0x27F735) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char a;                      // 0x1
} anon_6_148;

/* anon_9_148 -- @anon9, 0x48 bytes, adv_endless_obj.c (DIE 0x280340) */
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
} anon_9_148;

/* anon_10_148 -- @anon10, 0x1C bytes, adv_endless_obj.c (DIE 0x280D3F) */
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
} anon_10_148;

/* anon_13_148 -- @anon13, 0x30 bytes, adv_endless_obj.c (DIE 0x2837C6) */
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
} anon_13_148;

/* anon_27_148 -- @anon27, 0x8 bytes, adv_endless_obj.c (DIE 0x2859F7) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_27_148;

/* anon_31_148 -- @anon31, 0x10 bytes, adv_endless_obj.c (DIE 0x2862D0) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_31_148;


/* variables (23) */
anon_31_148 endless_menu_objf;                                   /* @0x002C00A0 size 0x10 */
anon_31_148 endless_program_objf;                                /* @0x002C00B0 size 0x10 */
anon_31_148 endless_program_cursor_objf;                         /* @0x002C00C0 size 0x10 */
anon_31_148 endless_program_title_objf;                          /* @0x002C00D0 size 0x10 */
unsigned char *EndlessMenuStrData[7];                            /* @0x002C00E0 size 0x1C */
static unsigned char *PlayMenuValueStrData[2];                   /* @0x002DDDA0 size 0x8 */
static unsigned char *StepMenuValueStrData[5];                   /* @0x002C0100 size 0x14 */
static unsigned char *BreakMenuValueStrData[12];                 /* @0x002C0120 size 0x30 */
static unsigned char *BatchDeletionValueStrData[5];              /* @0x002C0150 size 0x14 */
unsigned char **EndlessMenuValueStrDataTable[7];                 /* @0x002C0170 size 0x1C */
anon_5_148 *endless_wp;                                          /* @0x002DDDA8 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct music_info minfo_tab[84];                                 /* @0x002A86E0 size 0x3480 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _tag_cMusicData *alphabet_order_table[128];               /* @0x005F7DD0 size 0x200 */
struct _ADVANCED_MODE_W *advwp;                                  /* @0x002DDDC0 size 0x4 */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
anon_0_148 usr_work;                                             /* @0x00328A20 size 0xC */
anon_4_148 *fpw;                                                 /* @0x002DE540 size 0x4 */
anon_31_148 advanced_name_objf;                                  /* @0x002C0010 size 0x10 */
anon_31_148 advanced_sel1_objf;                                  /* @0x002C0640 size 0x10 */
anon_31_148 advanced_window_objf;                                /* @0x002C05B0 size 0x10 */
anon_5_148 adv_endless_w;                                        /* @0x00722070 size 0x178 */

/* functions defined (42) */
void EdsSupGetScore(int *ScoreMax);                              /* 0x002637A0-0x002637BC lines 3273-3276 */
void EdsSupCalcScore(void);                                      /* 0x002637C0-0x00263814 lines 3261-3269 */
int EdsSupGetPlayLevel(void);                                    /* 0x00263820-0x0026382C lines 3257-3258 */
void EdsSupScoreCreate(int _value);                              /* 0x00263830-0x00263D74 lines 3139-3253 */
void EdsSupNextStageCreate(void);                                /* 0x00263D80-0x00263FA8 lines 3025-3093 */
void EdsSupBeforeStageDataSet(void);                             /* 0x00263FB0-0x00264008 lines 2966-3002 */
struct music_info *EdsSupGetMipTable(int _num);                  /* 0x00264010-0x002640E0 lines 2906-2938 */
static int EdsSupInitMipTable(void);                             /* 0x002640E0-0x002642A4 lines 2847-2883 */
int EdsSupGetLevelType(int num);                                 /* 0x002642B0-0x00264488 lines 2776-2827 */
static void EdsSupTrackSorting(void);                            /* 0x00264490-0x00264614 lines 2440-2754 */
static void EdsInitOrderFlag(void);                              /* 0x00264620-0x00264820 lines 2388-2437 */
static void EdsSetupParameter(void);                             /* 0x00264820-0x00264D18 lines 2245-2364 */
static void EdsResetPlayLevel(void);                             /* 0x00264D20-0x00264E94 lines 2187-2242 */
static void adv_endless_setup(void);                             /* 0x00264EA0-0x00264F8C lines 2121-2184 */
static int get_bpm_from_dance_num(int dance_num, int kind);      /* 0x00264F90-0x00265084 lines 2046-2082 */
static int set_check_mark(int kind);                             /* 0x00265090-0x002652D4 lines 1980-2010 */
static int disp_batch_yes_no_window(void);                       /* 0x002652E0-0x00265528 lines 1912-1946 */
static int endless_program_title_disp(void *w);                  /* 0x00265530-0x0026579C lines 1864-1909 */
static int endless_program_title_disap(void *w);                 /* 0x002657A0-0x00265A3C lines 1816-1861 */
static int endless_program_title_exec(void);                     /* 0x00265A40-0x00265A48 lines 1813-1813 */
static int endless_program_title_apper(void *w);                 /* 0x00265A50-0x00265CE8 lines 1757-1806 */
static int endless_program_cursor_disp(void);                    /* 0x00265CF0-0x00265CF8 lines 1755-1755 */
static int endless_program_cursor_disap(void *w);                /* 0x00265D00-0x00265EF4 lines 1678-1723 */
static int endless_program_cursor_exec(void *w);                 /* 0x00265F00-0x00265F74 lines 1669-1675 */
static int endless_program_cursor_apper(void *w);                /* 0x00265F80-0x00266170 lines 1615-1664 */
static int endless_program_item_disp(void *w);                   /* 0x00266170-0x00267118 lines 1422-1613 */
static void draw_endless_frame(int x, int y, int z, int alpha, int on); /* 0x00267120-0x00267400 lines 1360-1420 */
static int endless_program_item_disap(void *w);                  /* 0x00267400-0x002676C0 lines 1247-1293 */
static int endless_program_item_exec(void *w);                   /* 0x002676C0-0x00267B58 lines 1190-1244 */
static int endless_program_item_apper(void *w);                  /* 0x00267B60-0x00268008 lines 1128-1187 */
static int endless_menu_item_disp(void *w);                      /* 0x00268010-0x00268790 lines 967-1126 */
static int endless_menu_item_disap(void *w);                     /* 0x00268790-0x002689A0 lines 918-964 */
static int endless_menu_item_exec(void);                         /* 0x002689A0-0x002689A8 lines 915-915 */
static int endless_menu_item_apper(void *w);                     /* 0x002689B0-0x00268C70 lines 857-909 */
static void endless_program_select(void);                        /* 0x00268C70-0x00269024 lines 782-855 */
static void endless_program(void);                               /* 0x00269030-0x00269714 lines 625-779 */
static void endless_menu_select(void);                           /* 0x00269720-0x00269B28 lines 534-606 */
void adv_endless_sel_finish_all(void);                           /* 0x00269B30-0x00269B84 lines 477-483 */
void adv_endless_sel_finish(void);                               /* 0x00269B90-0x00269B98 lines 474-474 */
int adv_endless_sel_step(void);                                  /* 0x00269BA0-0x00269FF8 lines 349-470 */
void adv_endless_sel_init(void);                                 /* 0x0026A000-0x0026A254 lines 277-346 */
void adv_endless_setup__for_combo_and_survival(int level);       /* 0x0026A260-0x0026A354 lines 239-273 */

#endif /* DDR_UNIT_src_CS_advanced_adv_endless_obj_c_H */
