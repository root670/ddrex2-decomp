/*
 * C:\work2\usaex2\src\AM\s573\doll\dexport.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001CF1B0-0x001CF378
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_dexport_c_H
#define DDR_UNIT_src_AM_s573_doll_dexport_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (15) */

/* anon_4_26 -- @anon4, 0x4 bytes, dexport.c (DIE 0x3AC88) */
union anon_4_26 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_7_26 -- @anon7, 0x10 bytes, dexport.c (DIE 0x3B041) */
struct anon_7_26 {   // size 0x10
    /* 0x000 */ union anon_4_26 x0;                   // 0x4
    /* 0x004 */ union anon_4_26 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_0_26 -- @anon0, 0x184 bytes, dexport.c (DIE 0x37F9F) */
struct anon_0_26 {   // size 0x184
    /* 0x000 */ struct anon_7_26 line_a[8];           // 0x80
    /* 0x080 */ struct anon_7_26 line_b[8];           // 0x80
    /* 0x100 */ struct anon_7_26 line_c[8];           // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_1_26 -- @anon1, 0x31 bytes, dexport.c (DIE 0x383D2) */
struct anon_1_26 {   // size 0x31
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[48];                          // 0x30
};

/* anon_2_26 -- @anon2, 0xD40 bytes, dexport.c (DIE 0x3A5D2) */
struct anon_2_26 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_3_26 -- @anon3, 0x14 bytes, dexport.c (DIE 0x3AA2A) */
struct anon_3_26 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_5_26 -- @anon5, 0xC bytes, dexport.c (DIE 0x3AD09) */
struct anon_5_26 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_6_26 -- @anon6, 0x14 bytes, dexport.c (DIE 0x3AE73) */
struct anon_6_26 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_8_26 -- @anon8, 0x1300 bytes, dexport.c (DIE 0x3B161) */
struct anon_8_26 {   // size 0x1300
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
    /* 0x360 */ struct anon_3_26 subject[200];        // 0xFA0
};

/* anon_10_26 -- @anon10, 0x4 bytes, dexport.c (DIE 0x3B54D) */
struct anon_10_26 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_9_26 -- @anon9, 0x4 bytes, dexport.c (DIE 0x3B4CB) */
union anon_9_26 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_10_26 s;                  // 0x4
};

/* anon_11_26 -- @anon11, 0x12E0 bytes, dexport.c (DIE 0x3B7C7) */
struct anon_11_26 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_5_26 history[400];        // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_12_26 -- @anon12, 0x2134 bytes, dexport.c (DIE 0x3BA68) */
struct anon_12_26 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_9_26 userpass;             // 0x4
    /* 0x008 */ struct anon_11_26 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_2_26 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_13_26 -- @anon13, 0x4 bytes, dexport.c (DIE 0x3C64C) */
struct anon_13_26 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_14_26 -- @anon14, 0x4 bytes, dexport.c (DIE 0x3E371) */
struct anon_14_26 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};


/* variables (2) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions defined (2) */
void ps2dancerInitHide(void);                                    /* 0x001CF1B0-0x001CF220 lines 98-105 */
void ps2dancerGetDollList(struct anon_1_26 *wk, int mode);       /* 0x001CF220-0x001CF378 lines 61-82 */

#endif /* DDR_UNIT_src_AM_s573_doll_dexport_c_H */
