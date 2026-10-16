/*
 * C:\work2\usaex2\src\eyetoy\eye_system.c
 * MW MIPS C Compiler, overlay main; 14 functions, code 0x001D2180-0x001D4D74
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_eyetoy_eye_system_c_H
#define DDR_UNIT_src_eyetoy_eye_system_c_H

#include "types/_DOUBLE_DISP_W.h"
#include "types/_EYETOY_W.h"
#include "types/_eRECT.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (17) */

/* anon_13_32 -- @anon13, 0x14 bytes, eye_system.c (DIE 0x4EFCD) */
struct anon_13_32 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_0_32 -- @anon0, 0x1300 bytes, eye_system.c (DIE 0x47DC7) */
struct anon_0_32 {   // size 0x1300
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
    /* 0x360 */ struct anon_13_32 subject[200];       // 0xFA0
};

/* anon_3_32 -- @anon3, 0x4 bytes, eye_system.c (DIE 0x484EF) */
struct anon_3_32 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_1_32 -- @anon1, 0x4 bytes, eye_system.c (DIE 0x482EF) */
union anon_1_32 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_3_32 s;                   // 0x4
};

/* anon_14_32 -- @anon14, 0xC bytes, eye_system.c (DIE 0x4F250) */
struct anon_14_32 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_2_32 -- @anon2, 0x12E0 bytes, eye_system.c (DIE 0x48371) */
struct anon_2_32 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_14_32 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_11_32 -- @anon11, 0xD40 bytes, eye_system.c (DIE 0x4EBF7) */
struct anon_11_32 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_4_32 -- @anon4, 0x2134 bytes, eye_system.c (DIE 0x48D96) */
struct anon_4_32 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_1_32 userpass;             // 0x4
    /* 0x008 */ struct anon_2_32 pwork;               // 0x12E0
    /* 0x12E8 */ struct anon_11_32 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_5_32 -- @anon5, 0x4 bytes, eye_system.c (DIE 0x49E95) */
struct anon_5_32 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_x4ba1f_32 -- @enum, 0x1 bytes, eye_system.c (DIE 0x4BA1F) */
enum anon_x4ba1f_32 {   // size 0x1
    SCE_EYETOY_NOCAMERA = 0,
    SCE_EYETOY_CLOSED = 1,
    SCE_EYETOY_STOPPED = 2,
    SCE_EYETOY_STARTED = 3,
};

/* anon_6_32 -- @anon6, 0x4 bytes, eye_system.c (DIE 0x4BDF4) */
struct anon_6_32 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_7_32 -- @anon7, 0x48 bytes, eye_system.c (DIE 0x4BECC) */
struct anon_7_32 {   // size 0x48
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

/* anon_9_32 -- @anon9, 0x4 bytes, eye_system.c (DIE 0x4DC8A) */
union anon_9_32 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_12_32 -- @anon12, 0x10 bytes, eye_system.c (DIE 0x4ECCF) */
struct anon_12_32 {   // size 0x10
    /* 0x000 */ union anon_9_32 x0;                   // 0x4
    /* 0x004 */ union anon_9_32 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_8_32 -- @anon8, 0x184 bytes, eye_system.c (DIE 0x4C779) */
struct anon_8_32 {   // size 0x184
    /* 0x000 */ struct anon_12_32 line_a[8];          // 0x80
    /* 0x080 */ struct anon_12_32 line_b[8];          // 0x80
    /* 0x100 */ struct anon_12_32 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_10_32 -- @anon10, 0x30 bytes, eye_system.c (DIE 0x4E839) */
struct anon_10_32 {   // size 0x30
    /* 0x000 */ union anon_9_32 x0;                   // 0x4
    /* 0x004 */ union anon_9_32 y0;                   // 0x4
    /* 0x008 */ union anon_9_32 x1;                   // 0x4
    /* 0x00C */ union anon_9_32 y1;                   // 0x4
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

/* anon_15_32 -- @anon15, 0x14 bytes, eye_system.c (DIE 0x4F427) */
struct anon_15_32 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};


/* variables (5) */
struct _EYETOY_W *EYETOYW;                                       /* @0x002DD9A8 size 0x4 */
static int (*EyeSystem_Func[5])(struct _EYETOY_W *);             /* @0x002B6920 size 0x14 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
static struct _EYETOY_W _eyetoy_w;                               /* @0x007126E0 size 0x2DC */

/* functions defined (14) */
void EyeSceEnd(void);                                            /* 0x001D2180-0x001D21E4 lines 1092-1103 */
static void EyeSystemFilter(struct _DOUBLE_DISP_W *screen);      /* 0x001D21F0-0x001D2678 lines 944-1029 */
static void EyeSystemDispColorAnimeWindow(void);                 /* 0x001D2680-0x001D2E74 lines 668-865 */
static void EyeSystemDispWindow(struct _DOUBLE_DISP_W *screen, struct _eRECT *disp); /* 0x001D2E80-0x001D3200 lines 570-665 */
static void EyeSystemDrawPict(void);                             /* 0x001D3200-0x001D3810 lines 385-542 */
static int EyeSystemDestroy(void);                               /* 0x001D3810-0x001D392C lines 364-370 */
static int EyeSystemStop(struct _EYETOY_W *_eye);                /* 0x001D3930-0x001D3A9C lines 321-358 */
static int EyeSystemMain(struct _EYETOY_W *_eye);                /* 0x001D3AA0-0x001D3AF0 lines 303-315 */
static int EyeSystemStart(struct _EYETOY_W *_eye);               /* 0x001D3AF0-0x001D3C18 lines 262-292 */
static int EyeSystemSet(struct _EYETOY_W *_eye);                 /* 0x001D3C20-0x001D3C70 lines 239-253 */
int EyeSystemInit(void);                                         /* 0x001D3C70-0x001D4B2C lines 137-231 */
void EyeSystemFunc(void);                                        /* 0x001D4B30-0x001D4BBC lines 124-131 */
void EyeSystemReset(void);                                       /* 0x001D4BC0-0x001D4CD0 lines 61-74 */
void EyeSystemCreate(void);                                      /* 0x001D4CD0-0x001D4D74 lines 50-56 */

#endif /* DDR_UNIT_src_eyetoy_eye_system_c_H */
