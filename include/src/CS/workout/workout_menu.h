/*
 * C:\work2\usaex2\src\CS\workout\workout_menu.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 4 functions, code 0x00800140-0x00800E40
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
#ifndef DDR_UNIT_src_CS_workout_workout_menu_c_H
#define DDR_UNIT_src_CS_workout_workout_menu_c_H

/* anonymous types (9) */

/* anon_0_240 -- @anon0, 0x48 bytes, workout_menu.c (DIE 0x46C97C) */
typedef struct {   // size 0x48
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int cursor;                           // 0x4
    /* 0x008 */ int counter;                          // 0x4
    /* 0x00C */ int pos_x[3];                         // 0xC
    /* 0x018 */ int pos_y[3];                         // 0xC
    /* 0x024 */ int f_select;                         // 0x4
    /* 0x028 */ int f_cancel;                         // 0x4
    /* 0x02C */ int f_open;                           // 0x4
    /* 0x030 */ int f_finished;                       // 0x4
    /* 0x034 */ int f_setting;                        // 0x4
    /* 0x038 */ int f_record;                         // 0x4
    /* 0x03C */ int f_move;                           // 0x4
    /* 0x040 */ int move_cursor;                      // 0x4
    /* 0x044 */ int f_back_to_userlist;               // 0x4
} anon_0_240;

/* anon_1_240 -- @anon1, 0x48 bytes, workout_menu.c (DIE 0x46CBEC) */
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
} anon_1_240;

/* anon_2_240 -- @anon2, 0x8 bytes, workout_menu.c (DIE 0x46CE6E) */
typedef struct {   // size 0x8
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int param;                            // 0x4
} anon_2_240;

/* anon_3_240 -- @anon3, 0x4 bytes, workout_menu.c (DIE 0x46CED0) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_240;

/* anon_4_240 -- @anon4, 0x30 bytes, workout_menu.c (DIE 0x46CF2D) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_3_240 x0;                        // 0x4
    /* 0x004 */ anon_3_240 y0;                        // 0x4
    /* 0x008 */ anon_3_240 x1;                        // 0x4
    /* 0x00C */ anon_3_240 y1;                        // 0x4
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
} anon_4_240;

/* anon_5_240 -- @anon5, 0x4 bytes, workout_menu.c (DIE 0x46D122) */
typedef struct {   // size 0x4
    /* 0x000 */ anon_2_240 (*step_func)();            // 0x4
} anon_5_240;

/* anon_6_240 -- @anon6, 0xC bytes, workout_menu.c (DIE 0x46D17E) */
typedef struct {   // size 0xC
    /* 0x000 */ anon_5_240 *step_array;               // 0x4
    /* 0x004 */ void (*screen)(int);                  // 0x4
    /* 0x008 */ int step_idx;                         // 0x4
} anon_6_240;

/* anon_7_240 -- @anon7, 0x30 bytes, workout_menu.c (DIE 0x46D216) */
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
} anon_7_240;

/* anon_8_240 -- @anon8, 0x84 bytes, workout_menu.c (DIE 0x46D449) */
typedef struct {   // size 0x84
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int result;                           // 0x4
    /* 0x008 */ int date;                             // 0x4
    /* 0x00C */ int not_first;                        // 0x4
    /* 0x010 */ int f_cancel;                         // 0x4
    /* 0x014 */ unsigned int *am_local_dec_addr;      // 0x4
    /* 0x018 */ anon_7_240 player[2];                 // 0x60
    /* 0x078 */ anon_6_240 hstep;                     // 0xC
} anon_8_240;


/* variables (2) */
anon_0_240 wo_wokout_menu;                                       /* @0x00802540 size 0x48 */
anon_8_240 workout_work;                                         /* @0x0071D880 size 0x84 */

/* functions defined (4) */
static void WorkoutMenuDraw(void);                               /* 0x00800140-0x00800674 lines 296-370 */
static void WorkoutMenuAct(void);                                /* 0x00800680-0x00800D50 lines 97-292 */
anon_2_240 WorkoutMenuMain(void);                                /* 0x00800D50-0x00800DF0 lines 60-76 */
anon_2_240 WorkoutMenuInit(void);                                /* 0x00800DF0-0x00800E40 lines 53-57 */

#endif /* DDR_UNIT_src_CS_workout_workout_menu_c_H */
