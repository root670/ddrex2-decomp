/*
 * C:\work2\usaex2\src\CS\workout\workout_user.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 12 functions, code 0x007F29B0-0x007F2F40
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_user_c_H
#define DDR_UNIT_src_CS_workout_workout_user_c_H

/* anonymous types (7) */

/* anon_0_235 -- @anon0, 0x8 bytes, workout_user.c (DIE 0x45B082) */
struct anon_0_235 {   // size 0x8
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int param;                            // 0x4
};

/* anon_1_235 -- @anon1, 0x4 bytes, workout_user.c (DIE 0x45B0E4) */
struct anon_1_235 {   // size 0x4
    /* 0x000 */ struct anon_0_235 (*step_func)();     // 0x4
};

/* anon_2_235 -- @anon2, 0xC bytes, workout_user.c (DIE 0x45B140) */
struct anon_2_235 {   // size 0xC
    /* 0x000 */ struct anon_1_235 *step_array;        // 0x4
    /* 0x004 */ void (*screen)(int);                  // 0x4
    /* 0x008 */ int step_idx;                         // 0x4
};

/* anon_3_235 -- @anon3, 0x18 bytes, workout_user.c (DIE 0x45B1D8) */
struct anon_3_235 {   // size 0x18
    /* 0x000 */ int func_no;                          // 0x4
    /* 0x004 */ int next_func;                        // 0x4
    /* 0x008 */ int status;                           // 0x4
    /* 0x00C */ int step;                             // 0x4
    /* 0x010 */ int f_finish;                         // 0x4
    /* 0x014 */ int f_Init;                           // 0x4
};

/* anon_4_235 -- @anon4, 0x30 bytes, workout_user.c (DIE 0x45B2CD) */
struct anon_4_235 {   // size 0x30
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
};

/* anon_5_235 -- @anon5, 0x10 bytes, workout_user.c (DIE 0x45B500) */
struct anon_5_235 {   // size 0x10
    /* 0x000 */ void (*init)(int);                    // 0x4
    /* 0x004 */ void (*act)(int);                     // 0x4
    /* 0x008 */ void (*draw)(int);                    // 0x4
    /* 0x00C */ void (*term)(int);                    // 0x4
};

/* anon_6_235 -- @anon6, 0x84 bytes, workout_user.c (DIE 0x45B622) */
struct anon_6_235 {   // size 0x84
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int result;                           // 0x4
    /* 0x008 */ int date;                             // 0x4
    /* 0x00C */ int not_first;                        // 0x4
    /* 0x010 */ int f_cancel;                         // 0x4
    /* 0x014 */ unsigned int *am_local_dec_addr;      // 0x4
    /* 0x018 */ struct anon_4_235 player[2];          // 0x60
    /* 0x078 */ struct anon_2_235 hstep;              // 0xC
};


/* variables (3) */
static struct anon_5_235 funclist[8];                            /* @0x00801210 size 0x80 */
struct anon_3_235 gwork[2];                                      /* @0x00801DE0 size 0x30 */
struct anon_6_235 workout_work;                                  /* @0x0071D880 size 0x84 */

/* functions defined (12) */
void WouFuncDraw(void);                                          /* 0x007F29B0-0x007F2A1C lines 292-301 */
void WouFuncAct(void);                                           /* 0x007F2A20-0x007F2A84 lines 281-289 */
int WorkoutUser_GetPlayerStatus(int pno);                        /* 0x007F2A90-0x007F2AB0 lines 277-278 */
void WorkoutUser_SetPlayerStatus(int pno, int status);           /* 0x007F2AB0-0x007F2AD0 lines 271-273 */
void WorkoutUser_SetFinish(int pno);                             /* 0x007F2AD0-0x007F2AF4 lines 259-261 */
int WorkoutUser_IsCreating(int pno);                             /* 0x007F2B00-0x007F2B40 lines 251-255 */
int WorkoutUser_GetFuncStep(int pno);                            /* 0x007F2B40-0x007F2B60 lines 243-244 */
void WorkoutUser_SetNextFunc(int pno, int func_no);              /* 0x007F2B60-0x007F2B80 lines 233-235 */
struct anon_0_235 WorkoutUser_Term(void);                        /* 0x007F2B80-0x007F2C58 lines 173-192 */
struct anon_0_235 WorkoutUser_Main(void);                        /* 0x007F2C60-0x007F2E20 lines 131-166 */
struct anon_0_235 WorkoutUser_Init(void);                        /* 0x007F2E20-0x007F2F2C lines 89-122 */
void WorkoutUser_DataInit(void);                                 /* 0x007F2F30-0x007F2F40 lines 80-80 */

#endif /* DDR_UNIT_src_CS_workout_workout_user_c_H */
