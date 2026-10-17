/*
 * C:\work2\usaex2\src\CS\workout\workout_usermanage.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 15 functions, code 0x007F25B0-0x007F29A8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_usermanage_c_H
#define DDR_UNIT_src_CS_workout_workout_usermanage_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (7) */

/* anon_5_234 -- @anon5, 0x4 bytes, workout_usermanage.c (DIE 0x4590D8) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_5_234;

/* anon_4_234 -- @anon4, 0x4 bytes, workout_usermanage.c (DIE 0x459054) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_5_234 s;                         // 0x4
} anon_4_234;

/* anon_3_234 -- @anon3, 0xC bytes, workout_usermanage.c (DIE 0x458DAA) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_3_234;

/* anon_6_234 -- @anon6, 0x12E0 bytes, workout_usermanage.c (DIE 0x459366) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_3_234 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_6_234;

/* anon_2_234 -- @anon2, 0xD40 bytes, workout_usermanage.c (DIE 0x45886B) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_2_234;

/* anon_1_234 -- @anon1, 0x2134 bytes, workout_usermanage.c (DIE 0x45760B) */
typedef struct {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ anon_4_234 userpass;                  // 0x4
    /* 0x008 */ anon_6_234 pwork;                     // 0x12E0
    /* 0x12E8 */ anon_2_234 workout_calorie_record;   // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
} anon_1_234;

/* anon_7_234 -- @anon7, 0x14 bytes, workout_usermanage.c (DIE 0x45962F) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_7_234;


/* variables (5) */
static anon_1_234 *gw;                                           /* @0x002DE680 size 0x4 */
int g_worknum;                                                   /* @0x002DE684 size 0x4 */
anon_1_234 *g_workwork[2];                                       /* @0x002DE688 size 0x8 */
int g_workno[2];                                                 /* @0x002DE690 size 0x8 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (15) */
void wumSetNormaCalorie(anon_1_234 *w, int iCalorie);            /* 0x007F25B0-0x007F25D8 lines 232-235 */
void wumSetNormaPlayTime(anon_1_234 *w, int iPlayTime);          /* 0x007F25E0-0x007F2608 lines 223-226 */
void wumSetWeight(anon_1_234 *w, unsigned int weight);           /* 0x007F2610-0x007F26C4 lines 211-216 */
int wumGetUserBlankNoSecond(void);                               /* 0x007F26D0-0x007F2730 lines 186-199 */
int wumGetUserBlankNoFirst(void);                                /* 0x007F2730-0x007F2778 lines 171-181 */
int wumGetUserPos(int uno);                                      /* 0x007F2780-0x007F2810 lines 148-161 */
anon_1_234 *wumGetUserWork(int uno);                             /* 0x007F2810-0x007F2824 lines 139-140 */
int wumGetUserNum(void);                                         /* 0x007F2830-0x007F2838 lines 122-122 */
void wumDeleteUser(int uno);                                     /* 0x007F2840-0x007F287C lines 110-113 */
anon_1_234 *wumCreateUser(int uno);                              /* 0x007F2880-0x007F2908 lines 83-99 */
anon_1_234 *wumGetPlayUserWork(int player);                      /* 0x007F2910-0x007F2924 lines 77-78 */
anon_1_234 *wumSetPlayUserWork(int player, int uno);             /* 0x007F2930-0x007F2964 lines 68-71 */
void wumSetSystemUserWork(void);                                 /* 0x007F2970-0x007F2980 lines 51-53 */
void wumGetSystemUserWork(void);                                 /* 0x007F2980-0x007F299C lines 41-44 */
void wumInit(void);                                              /* 0x007F29A0-0x007F29A8 lines 33-33 */

#endif /* DDR_UNIT_src_CS_workout_workout_usermanage_c_H */
