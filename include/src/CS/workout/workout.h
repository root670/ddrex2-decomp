/*
 * C:\work2\usaex2\src\CS\workout\workout.c
 * MW MIPS C Compiler, overlay main; 21 functions, code 0x001F7F70-0x001F92B0
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
#ifndef DDR_UNIT_src_CS_workout_workout_c_H
#define DDR_UNIT_src_CS_workout_workout_c_H

#include "types/CO_OBJ_W.h"
#include "types/_tag_cFilepackData.h"
#include "types/g_game_w.h"

/* anonymous types (13) */

/* anon_0_50 -- @anon0, 0x24 bytes, workout.c (DIE 0xAB8F0) */
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
} anon_0_50;

/* anon_3_50 -- @anon3, 0xC bytes, workout.c (DIE 0xABDE2) */
typedef struct {   // size 0xC
    /* 0x000 */ int year;                             // 0x4
    /* 0x004 */ int month;                            // 0x4
    /* 0x008 */ int day;                              // 0x4
} anon_3_50;

/* anon_6_50 -- @anon6, 0xC bytes, workout.c (DIE 0xACDA3) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_6_50;

/* anon_5_50 -- @anon5, 0x12E0 bytes, workout.c (DIE 0xACC25) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_6_50 history[400];               // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_5_50;

/* anon_8_50 -- @anon8, 0x8 bytes, workout.c (DIE 0xAD082) */
typedef struct {   // size 0x8
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int param;                            // 0x4
} anon_8_50;

/* anon_9_50 -- @anon9, 0x74 bytes, workout.c (DIE 0xAD2F9) */
typedef struct {   // size 0x74
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
    /* 0x010 */ anon_d075beaabcd0 x2;                 // 0x4
    /* 0x014 */ anon_d075beaabcd0 y2;                 // 0x4
    /* 0x018 */ anon_d075beaabcd0 x3;                 // 0x4
    /* 0x01C */ anon_d075beaabcd0 y3;                 // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ unsigned char r1;                     // 0x1
    /* 0x065 */ unsigned char g1;                     // 0x1
    /* 0x066 */ unsigned char b1;                     // 0x1
    /* 0x067 */ unsigned char a1;                     // 0x1
    /* 0x068 */ unsigned char r2;                     // 0x1
    /* 0x069 */ unsigned char g2;                     // 0x1
    /* 0x06A */ unsigned char b2;                     // 0x1
    /* 0x06B */ unsigned char a2;                     // 0x1
    /* 0x06C */ unsigned char r3;                     // 0x1
    /* 0x06D */ unsigned char g3;                     // 0x1
    /* 0x06E */ unsigned char b3;                     // 0x1
    /* 0x06F */ unsigned char a3;                     // 0x1
    /* 0x070 */ int flg;                              // 0x4
} anon_9_50;

/* anon_10_50 -- @anon10, 0x4 bytes, workout.c (DIE 0xAD8D6) */
typedef struct {   // size 0x4
    /* 0x000 */ anon_8_50 (*step_func)();             // 0x4
} anon_10_50;

/* anon_11_50 -- @anon11, 0xC bytes, workout.c (DIE 0xAD99F) */
typedef struct {   // size 0xC
    /* 0x000 */ anon_10_50 *step_array;               // 0x4
    /* 0x004 */ void (*screen)(int);                  // 0x4
    /* 0x008 */ int step_idx;                         // 0x4
} anon_11_50;

/* anon_12_50 -- @anon12, 0x8 bytes, workout.c (DIE 0xADA5C) */
typedef struct {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int file_num;                         // 0x4
} anon_12_50;

/* anon_13_50 -- @anon13, 0x30 bytes, workout.c (DIE 0xADAC2) */
typedef struct {   // size 0x30
    /* 0x000 */ int active;                           // 0x4
    /* 0x004 */ int play_time;                        // 0x4
    /* 0x008 */ int calorie;                          // 0x4
    /* 0x00C */ int play_time_per_music;              // 0x4
    /* 0x010 */ int calorie_per_music;                // 0x4
    /* 0x014 */ int play_time_norm;                   // 0x4
    /* 0x018 */ int calorie_norm;                     // 0x4
    /* 0x01C */ int daily_data_index;                 // 0x4
    /* 0x020 */ int workout_data_load_flag;           // 0x4
    /* 0x024 */ int workout_data_change_flag;         // 0x4
    /* 0x028 */ int workout_data_save_flag;           // 0x4
    /* 0x02C */ int music_play_count;                 // 0x4
} anon_13_50;

/* anon_15_50 -- @anon15, 0x84 bytes, workout.c (DIE 0xAE1A4) */
typedef struct {   // size 0x84
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int result;                           // 0x4
    /* 0x008 */ int date;                             // 0x4
    /* 0x00C */ int not_first;                        // 0x4
    /* 0x010 */ int f_cancel;                         // 0x4
    /* 0x014 */ unsigned int *am_local_dec_addr;      // 0x4
    /* 0x018 */ anon_13_50 player[2];                 // 0x60
    /* 0x078 */ anon_11_50 hstep;                     // 0xC
} anon_15_50;

/* anon_16_50 -- @anon16, 0xF4 bytes, workout.c (DIE 0xAE382) */
typedef struct {   // size 0xF4
    /* 0x000 */ anon_3_50 date;                       // 0xC
    /* 0x00C */ int abs_date_min;                     // 0x4
    /* 0x010 */ int abs_date_max;                     // 0x4
    /* 0x014 */ int Step2;                            // 0x4
    /* 0x018 */ int Step3;                            // 0x4
    /* 0x01C */ struct _tag_cFilepackData tblFilepack[27];  // 0xD8
} anon_16_50;

/* anon_18_50 -- @anon18, 0x48 bytes, workout.c (DIE 0xAE755) */
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
} anon_18_50;


/* variables (12) */
anon_16_50 *pWorkout;                                            /* @0x002DDA88 size 0x4 */
static anon_10_50 step_tbl[13];                                  /* @0x002B9550 size 0x34 */
static int title_step;                                           /* @0x002DE50C size 0x4 */
static int title_x;                                              /* not allocated size 0x4 */
static int title_y;                                              /* not allocated size 0x4 */
anon_16_50 gw_work;                                              /* @0x0071B1C0 size 0xF4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_5_50 workout_data[2];                                       /* @0x0071B2C0 size 0x25C0 */
anon_12_50 dload_work;                                           /* not allocated size 0x8 */
anon_15_50 workout_work;                                         /* @0x0071D880 size 0x84 */
struct CO_OBJ_W wo_co_obj_addr[32];                              /* @0x007161C0 size 0x5000 */
anon_5_50 workout_data_store[2];                                 /* not allocated size 0x25C0 */

/* functions referenced (1) */
void DecodeFilepackData_Th(void *);                              /* @0x0016DC50 */

/* functions defined (21) */
static anon_8_50 StepGetDate(void);                              /* 0x001F7F70-0x001F80B0 lines 1258-1298 */
static anon_8_50 WorkoutStepInit(void);                          /* 0x001F80B0-0x001F810C lines 1243-1255 */
static anon_8_50 StepNextDataLoad(void);                         /* 0x001F8110-0x001F8278 lines 1194-1236 */
static int WorkoutTexInit(void);                                 /* 0x001F8280-0x001F85A8 lines 1065-1178 */
void Workout_DispTitleFlameOut(void);                            /* 0x001F85B0-0x001F85BC lines 1031-1033 */
static void Workout_DispTitleDraw(void);                         /* 0x001F85C0-0x001F8A8C lines 938-1025 */
int is_workout_simultaneous_step(int pid);                       /* 0x001F8A90-0x001F8AB8 lines 721-726 */
int is_workout_step(void);                                       /* 0x001F8AC0-0x001F8AC8 lines 713-713 */
int is_workout_program(void);                                    /* 0x001F8AD0-0x001F8AF8 lines 698-699 */
int csWorkoutGetNormTime(int side);                              /* 0x001F8B00-0x001F8B48 lines 522-527 */
int csWorkoutGetNormCalorie(int side);                           /* 0x001F8B50-0x001F8B8C lines 505-510 */
int csWorkoutGetWeight(int side);                                /* 0x001F8B90-0x001F8BAC lines 472-473 */
void csWorkoutDataDefault(int side);                             /* 0x001F8BB0-0x001F8E70 lines 432-461 */
int csWorkoutGetFlagCancel(void);                                /* 0x001F8E70-0x001F8E7C lines 413-414 */
void csWorkoutSetFlagCancel(int flag);                           /* 0x001F8E80-0x001F8E8C lines 406-407 */
void csWorkoutFinish(void);                                      /* 0x001F8E90-0x001F8ECC lines 388-399 */
int csWorkoutStep(void);                                         /* 0x001F8ED0-0x001F8FC8 lines 358-382 */
static void csWorkoutInit_GameWork(void);                        /* 0x001F8FD0-0x001F910C lines 310-345 */
void csWorkoutInit(void);                                        /* 0x001F9110-0x001F91FC lines 270-307 */
static anon_8_50 Workout_FadeOut(void);                          /* 0x001F9200-0x001F9250 lines 256-261 */
static anon_8_50 Workout_FadeIn(void);                           /* 0x001F9250-0x001F92B0 lines 246-254 */

#endif /* DDR_UNIT_src_CS_workout_workout_c_H */
