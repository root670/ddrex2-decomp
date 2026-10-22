/*
 * C:\work2\usaex2\src\CS\advanced\adv_main.c
 * MW MIPS C Compiler, overlay main; 21 functions, code 0x0026A360-0x0026C12C
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
#ifndef DDR_UNIT_src_CS_advanced_adv_main_c_H
#define DDR_UNIT_src_CS_advanced_adv_main_c_H

#include "types/_ADVANCED_MODE_W.h"
#include "types/_ADV_TEX_RECT.h"
#include "types/_CWS_WIN_W.h"
#include "types/_EDSSAVE_W.h"
#include "types/_EDS_OPTION_DATA.h"
#include "types/_EXTRA_WORK.h"
#include "types/_LES_RECT.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/oni_mode.h"

/* anonymous types (5) */

/* anon_1_149 -- @anon1, 0x48 bytes, adv_main.c (DIE 0x28C579) */
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
} anon_1_149;

/* anon_3_149 -- @anon3, 0x1C bytes, adv_main.c (DIE 0x28D84B) */
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
} anon_3_149;

/* anon_6_149 -- @anon6, 0x30 bytes, adv_main.c (DIE 0x290675) */
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
} anon_6_149;

/* anon_16_149 -- @anon16, 0x8 bytes, adv_main.c (DIE 0x2921F0) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
} anon_16_149;

/* anon_19_149 -- @anon19, 0x10 bytes, adv_main.c (DIE 0x292E2F) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_19_149;


/* variables (25) */
struct _ADVANCED_MODE_W *advwp;                                  /* @0x002DDDC0 size 0x4 */
static char EdsSystemDefaultCursorST[7];                         /* @0x002DDDC8 size 0x7 */
static char EdsOptionDefaultCursorST[9];                         /* @0x002C02A8 size 0x9 */
unsigned char *OptionMenuStrData[9];                             /* @0x002C02C0 size 0x24 */
static unsigned char *SpeedMenuStrData[7];                       /* @0x002C02F0 size 0x1C */
static unsigned char *BoostMenuStrData[3];                       /* @0x002C0310 size 0xC */
static unsigned char *AppearanceMenuStrData[5];                  /* @0x002C0320 size 0x14 */
static unsigned char *TurnMenuStrData[6];                        /* @0x002C0340 size 0x18 */
static unsigned char *LittleMenuStrData[3];                      /* @0x002C0358 size 0xC */
static unsigned char *DarkMenuStrData[3];                        /* @0x002C0368 size 0xC */
static unsigned char *SimultaneousMenuStrData[4];                /* @0x002C0380 size 0x10 */
static unsigned char *ScrollMenuStrData[3];                      /* @0x002C0390 size 0xC */
static unsigned char *FreezearrowMenuStrData[3];                 /* @0x002C03A0 size 0xC */
static unsigned char **OptionValueStrData[9];                    /* @0x002C03B0 size 0x24 */
static short icon_tex_parts_table[9][7];                         /* @0x002C03E0 size 0x7E */
static struct _ADV_TEX_RECT option_icon_tex[28];                 /* @0x002C0460 size 0x150 */
anon_19_149 advanced_window_objf;                                /* @0x002C05B0 size 0x10 */
anon_19_149 advanced_option_objf;                                /* @0x002C05C0 size 0x10 */
struct _EXTRA_WORK *extra_wp;                                    /* @0x002DDDD0 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_16_149 extras_data[];                                       /* @0x002DD710 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
anon_16_149 advanced_data_bin[];                                 /* @0x002DD708 */
struct _ADVANCED_MODE_W advanced_mode_work;                      /* @0x00722200 size 0x13C */
struct _EXTRA_WORK extra_work;                                   /* @0x007221F0 size 0x10 */

/* functions referenced (1) */
void ResetAdvancedModeTex(void *);                               /* @0x0026BE50 */

/* functions defined (21) */
int extras_main(void);                                           /* 0x0026A360-0x0026A9D0 lines 1058-1237 */
void extras_init(void);                                          /* 0x0026A9D0-0x0026A9DC lines 1055-1055 */
void advanced_option_icon_disp(int n, int x, int y, int z, int alpha); /* 0x0026A9E0-0x0026AB60 lines 964-979 */
static void advanced_option_menu_disp(void);                     /* 0x0026AB60-0x0026B1B8 lines 830-961 */
static int advanced_option_disp(void);                           /* 0x0026B1C0-0x0026B1F4 lines 823-827 */
static int advanced_window_disp(void);                           /* 0x0026B200-0x0026B208 lines 820-820 */
int advanced_select_options(void);                               /* 0x0026B210-0x0026B438 lines 764-817 */
void AdvancedModeSaveDataDefault(void);                          /* 0x0026B440-0x0026B8E4 lines 460-510 */
int EdsGetOptionDefaultStatus(int num);                          /* 0x0026B8F0-0x0026B904 lines 450-451 */
int EdsGetSystemDefaultStatus(int num);                          /* 0x0026B910-0x0026B920 lines 438-439 */
void load_endless_menu_data(unsigned char *data);                /* 0x0026B920-0x0026B95C lines 375-380 */
void save_option_data_for_endless(void);                         /* 0x0026B960-0x0026B968 lines 365-365 */
void load_option_data_for_endless(void);                         /* 0x0026B970-0x0026B978 lines 341-341 */
void save_option_data_for_nonstop(int course, int index);        /* 0x0026B980-0x0026BB44 lines 269-317 */
void load_option_data_for_nonstop(int course, int index);        /* 0x0026BB50-0x0026BC1C lines 221-259 */
int get_advanced_tex_id(int index);                              /* 0x0026BC20-0x0026BC34 lines 210-211 */
int set_advanced_tex_id(int index);                              /* 0x0026BC40-0x0026BD98 lines 178-206 */
int *get_nonstop_save_workp(int course, int index);              /* 0x0026BDA0-0x0026BE50 lines 159-172 */
void ResetAdvancedModeTex(void);                                 /* 0x0026BE50-0x0026BF58 lines 122-156 */
int advanced_data_load(void);                                    /* 0x0026BF60-0x0026C114 lines 51-119 */
void *get_advanced_datap(void);                                  /* 0x0026C120-0x0026C12C lines 47-48 */

#endif /* DDR_UNIT_src_CS_advanced_adv_main_c_H */
