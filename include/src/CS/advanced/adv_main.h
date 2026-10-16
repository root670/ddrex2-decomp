/*
 * C:\work2\usaex2\src\CS\advanced\adv_main.c
 * MW MIPS C Compiler, overlay main; 21 functions, code 0x0026A360-0x0026C12C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
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

/* anonymous types (20) */

/* anon_0_149 -- @anon0, 0x4 bytes, adv_main.c (DIE 0x28C327) */
struct anon_0_149 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_1_149 -- @anon1, 0x48 bytes, adv_main.c (DIE 0x28C579) */
struct anon_1_149 {   // size 0x48
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
};

/* anon_4_149 -- @anon4, 0x4 bytes, adv_main.c (DIE 0x290234) */
union anon_4_149 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_7_149 -- @anon7, 0x10 bytes, adv_main.c (DIE 0x290A4C) */
struct anon_7_149 {   // size 0x10
    /* 0x000 */ union anon_4_149 x0;                  // 0x4
    /* 0x004 */ union anon_4_149 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_2_149 -- @anon2, 0x184 bytes, adv_main.c (DIE 0x28D660) */
struct anon_2_149 {   // size 0x184
    /* 0x000 */ struct anon_7_149 line_a[8];          // 0x80
    /* 0x080 */ struct anon_7_149 line_b[8];          // 0x80
    /* 0x100 */ struct anon_7_149 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_3_149 -- @anon3, 0x1C bytes, adv_main.c (DIE 0x28D84B) */
struct anon_3_149 {   // size 0x1C
    /* 0x000 */ union anon_4_149 x0;                  // 0x4
    /* 0x004 */ union anon_4_149 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_5_149 -- @anon5, 0xD40 bytes, adv_main.c (DIE 0x2903FA) */
struct anon_5_149 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_6_149 -- @anon6, 0x30 bytes, adv_main.c (DIE 0x290675) */
struct anon_6_149 {   // size 0x30
    /* 0x000 */ union anon_4_149 x0;                  // 0x4
    /* 0x004 */ union anon_4_149 y0;                  // 0x4
    /* 0x008 */ union anon_4_149 x1;                  // 0x4
    /* 0x00C */ union anon_4_149 y1;                  // 0x4
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
};

/* anon_8_149 -- @anon8, 0x14 bytes, adv_main.c (DIE 0x290B90) */
struct anon_8_149 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_9_149 -- @anon9, 0xC bytes, adv_main.c (DIE 0x2910F0) */
struct anon_9_149 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_10_149 -- @anon10, 0x14 bytes, adv_main.c (DIE 0x2914C1) */
struct anon_10_149 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_11_149 -- @anon11, 0x1300 bytes, adv_main.c (DIE 0x291704) */
struct anon_11_149 {   // size 0x1300
    /* 0x000 */ unsigned char evboot[24];             // 0x18
    /* 0x018 */ unsigned char is_savedata;            // 0x1
    /* 0x019 */ signed char max_area;                 // 0x1
    /* 0x01A */ signed char disp_type;                // 0x1
    /* 0x01B */ char pading;                          // 0x1
    /* 0x01C */ unsigned char dancer_use_cnt[24];     // 0x18
    /* 0x034 */ int cur_cursor;                       // 0x4
    /* 0x038 */ unsigned int all_clear_count;         // 0x4
    /* 0x03C */ unsigned int all_play_time;           // 0x4
    /* 0x040 */ int route[200];                       // 0x320
    /* 0x360 */ struct anon_8_149 subject[200];       // 0xFA0
};

/* anon_13_149 -- @anon13, 0x4 bytes, adv_main.c (DIE 0x291AF2) */
struct anon_13_149 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_12_149 -- @anon12, 0x4 bytes, adv_main.c (DIE 0x291A4B) */
union anon_12_149 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_13_149 s;                 // 0x4
};

/* anon_14_149 -- @anon14, 0x12E0 bytes, adv_main.c (DIE 0x291D6C) */
struct anon_14_149 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_9_149 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_15_149 -- @anon15, 0x2134 bytes, adv_main.c (DIE 0x29200D) */
struct anon_15_149 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_12_149 userpass;           // 0x4
    /* 0x008 */ struct anon_14_149 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_5_149 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_16_149 -- @anon16, 0x8 bytes, adv_main.c (DIE 0x2921F0) */
struct anon_16_149 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};

/* anon_17_149 -- @anon17, 0x8 bytes, adv_main.c (DIE 0x292A3A) */
struct anon_17_149 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_18_149 -- @anon18, 0x4 bytes, adv_main.c (DIE 0x292D55) */
struct anon_18_149 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_19_149 -- @anon19, 0x10 bytes, adv_main.c (DIE 0x292E2F) */
struct anon_19_149 {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
};


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
struct anon_19_149 advanced_window_objf;                         /* @0x002C05B0 size 0x10 */
struct anon_19_149 advanced_option_objf;                         /* @0x002C05C0 size 0x10 */
struct _EXTRA_WORK *extra_wp;                                    /* @0x002DDDD0 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct anon_16_149 extras_data[];                                /* @0x002DD710 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct anon_16_149 advanced_data_bin[];                          /* @0x002DD708 */
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
