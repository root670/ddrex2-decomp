/*
 * C:\work2\usaex2\src\CS\option\opt_adjust.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 2 functions, code 0x007F0080-0x007F0600
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_option_opt_adjust_c_H
#define DDR_UNIT_src_CS_option_opt_adjust_c_H

#include "types/_OPTSYS_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (9) */

/* anon_7_225 -- @anon7, 0x14 bytes, opt_adjust.c (DIE 0x430C10) */
struct anon_7_225 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_0_225 -- @anon0, 0x1300 bytes, opt_adjust.c (DIE 0x42D1AA) */
struct anon_0_225 {   // size 0x1300
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
    /* 0x360 */ struct anon_7_225 subject[200];       // 0xFA0
};

/* anon_3_225 -- @anon3, 0x4 bytes, opt_adjust.c (DIE 0x42DAED) */
struct anon_3_225 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_1_225 -- @anon1, 0x4 bytes, opt_adjust.c (DIE 0x42D3C5) */
union anon_1_225 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_3_225 s;                  // 0x4
};

/* anon_8_225 -- @anon8, 0xC bytes, opt_adjust.c (DIE 0x430E4A) */
struct anon_8_225 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_2_225 -- @anon2, 0x12E0 bytes, opt_adjust.c (DIE 0x42D96F) */
struct anon_2_225 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_8_225 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_6_225 -- @anon6, 0xD40 bytes, opt_adjust.c (DIE 0x43095C) */
struct anon_6_225 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_4_225 -- @anon4, 0x2134 bytes, opt_adjust.c (DIE 0x42DDF6) */
struct anon_4_225 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_1_225 userpass;            // 0x4
    /* 0x008 */ struct anon_2_225 pwork;              // 0x12E0
    /* 0x12E8 */ struct anon_6_225 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_5_225 -- @anon5, 0x4 bytes, opt_adjust.c (DIE 0x42E0D8) */
struct anon_5_225 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};


/* variables (2) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */

/* functions referenced (2) */
void OptMenuInit2(struct _OPTSYS_W *);                           /* @0x007F5E70 */
void OptAdjustMain(struct _OPTSYS_W *);                          /* @0x007F0080 */

/* functions defined (2) */
void OptAdjustMain(struct _OPTSYS_W *_opt);                      /* 0x007F0080-0x007F0598 lines 27-135 */
void OptAdjustInit(struct _OPTSYS_W *_opt);                      /* 0x007F05A0-0x007F0600 lines 9-22 */

#endif /* DDR_UNIT_src_CS_option_opt_adjust_c_H */
