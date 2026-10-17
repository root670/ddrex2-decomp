/*
 * C:\work2\usaex2\src\CS\workout\workout_userlist.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 49 functions, code 0x007F2F40-0x007FB4EC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_userlist_c_H
#define DDR_UNIT_src_CS_workout_workout_userlist_c_H

#include "types/oni_course.h"

/* anonymous types (27) */

/* anon_0_236 -- @anon0, 0x8 bytes, workout_userlist.c (DIE 0x45C97C) */
typedef struct {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int f_open;                           // 0x4
} anon_0_236;

/* anon_1_236 -- @anon1, 0x24 bytes, workout_userlist.c (DIE 0x45CA05) */
typedef struct {   // size 0x24
    /* 0x000 */ int ctype;                            // 0x4
    /* 0x004 */ int ptype;                            // 0x4
    /* 0x008 */ int uno;                              // 0x4
    /* 0x00C */ int pno;                              // 0x4
    /* 0x010 */ int status : 8;                       // bits 0..7
    /* 0x010 */ int step : 8;                         // bits 8..15
    /* 0x010 */ int wait : 8;                         // bits 16..23
    /* 0x010 */ int u_pos : 7;                        // bits 24..30
    /* 0x010 */ int fEnable : 1;                      // bits 31..31
    /* 0x014 */ int fade;                             // 0x4
    /* 0x018 */ int counter;                          // 0x4
    /* 0x01C */ float x0;                             // 0x4
    /* 0x020 */ float y0;                             // 0x4
} anon_1_236;

/* anon_5_236 -- @anon5, 0x4 bytes, workout_userlist.c (DIE 0x45CDBB) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_5_236;

/* anon_2_236 -- @anon2, 0x4 bytes, workout_userlist.c (DIE 0x45CC08) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_5_236 s;                         // 0x4
} anon_2_236;

/* anon_3_236 -- @anon3, 0x10 bytes, workout_userlist.c (DIE 0x45CC66) */
typedef struct {   // size 0x10
    /* 0x000 */ int wait_counter;                     // 0x4
    /* 0x004 */ int pos_y;                            // 0x4
    /* 0x008 */ int step;                             // 0x4
    /* 0x00C */ int f_open;                           // 0x4
} anon_3_236;

/* anon_4_236 -- @anon4, 0x30 bytes, workout_userlist.c (DIE 0x45CD14) */
typedef struct {   // size 0x30
    /* 0x000 */ float m[3][3];                        // 0x24
    /* 0x024 */ float t[3];                           // 0xC
} anon_4_236;

/* anon_6_236 -- @anon6, 0x14 bytes, workout_userlist.c (DIE 0x45CE44) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char chr;                    // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ int u;                                // 0x4
    /* 0x008 */ int v;                                // 0x4
    /* 0x00C */ int w;                                // 0x4
    /* 0x010 */ int h;                                // 0x4
} anon_6_236;

/* anon_22_236 -- @anon22, 0xC bytes, workout_userlist.c (DIE 0x45EC09) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_22_236;

/* anon_24_236 -- @anon24, 0x12E0 bytes, workout_userlist.c (DIE 0x45EFCC) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_22_236 history[400];             // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_24_236;

/* anon_25_236 -- @anon25, 0xD40 bytes, workout_userlist.c (DIE 0x45F14B) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_25_236;

/* anon_7_236 -- @anon7, 0x2134 bytes, workout_userlist.c (DIE 0x45CF1F) */
typedef struct {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ anon_2_236 userpass;                  // 0x4
    /* 0x008 */ anon_24_236 pwork;                    // 0x12E0
    /* 0x12E8 */ anon_25_236 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
} anon_7_236;

/* anon_8_236 -- @anon8, 0x28 bytes, workout_userlist.c (DIE 0x45D471) */
typedef struct {   // size 0x28
    /* 0x000 */ int pos_x;                            // 0x4
    /* 0x004 */ int pos_y;                            // 0x4
    /* 0x008 */ int depth_z;                          // 0x4
    /* 0x00C */ int cur_x;                            // 0x4
    /* 0x010 */ int cur_y;                            // 0x4
    /* 0x014 */ int item_x;                           // 0x4
    /* 0x018 */ int item_y;                           // 0x4
    /* 0x01C */ int dist_x;                           // 0x4
    /* 0x020 */ int dist_y;                           // 0x4
    /* 0x024 */ int counter;                          // 0x4
} anon_8_236;

/* anon_9_236 -- @anon9, 0x4 bytes, workout_userlist.c (DIE 0x45D612) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char a;                      // 0x1
} anon_9_236;

/* anon_10_236 -- @anon10, 0x1C bytes, workout_userlist.c (DIE 0x45D6A9) */
typedef struct {   // size 0x1C
    /* 0x000 */ int x0;                               // 0x4
    /* 0x004 */ int y0;                               // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int step;                             // 0x4
    /* 0x014 */ int f_ok;                             // 0x4
    /* 0x018 */ int f_open;                           // 0x4
} anon_10_236;

/* anon_11_236 -- @anon11, 0x48 bytes, workout_userlist.c (DIE 0x45D7A8) */
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
} anon_11_236;

/* anon_12_236 -- @anon12, 0x28 bytes, workout_userlist.c (DIE 0x45DA2B) */
typedef struct {   // size 0x28
    /* 0x000 */ int uno;                              // 0x4
    /* 0x004 */ int icon_no;                          // 0x4
    /* 0x008 */ int frame_no;                         // 0x4
    /* 0x00C */ int pass_sw;                          // 0x4
    /* 0x010 */ int cursor;                           // 0x4
    /* 0x014 */ int f_pass_entry;                     // 0x4
    /* 0x018 */ int f_already_ok;                     // 0x4
    /* 0x01C */ int f_finished;                       // 0x4
    /* 0x020 */ int step;                             // 0x4
    /* 0x024 */ unsigned char pass[4];                // 0x4
} anon_12_236;

/* anon_13_236 -- @anon13, 0x30 bytes, workout_userlist.c (DIE 0x45DCBC) */
typedef struct {   // size 0x30
    /* 0x000 */ int x0;                               // 0x4
    /* 0x004 */ int y0;                               // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int step;                             // 0x4
    /* 0x014 */ int next_step;                        // 0x4
    /* 0x018 */ int counter;                          // 0x4
    /* 0x01C */ int line_counter;                     // 0x4
    /* 0x020 */ int cursor;                           // 0x4
    /* 0x024 */ int f_start;                          // 0x4
    /* 0x028 */ int f_cancel;                         // 0x4
    /* 0x02C */ int f_edit;                           // 0x4
} anon_13_236;

/* anon_17_236 -- @anon17, 0x4 bytes, workout_userlist.c (DIE 0x45E2A8) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_17_236;

/* anon_14_236 -- @anon14, 0x1C bytes, workout_userlist.c (DIE 0x45DE79) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_17_236 x0;                       // 0x4
    /* 0x004 */ anon_17_236 y0;                       // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_14_236;

/* anon_15_236 -- @anon15, 0x8 bytes, workout_userlist.c (DIE 0x45E01E) */
typedef struct {   // size 0x8
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int param;                            // 0x4
} anon_15_236;

/* anon_16_236 -- @anon16, 0x24 bytes, workout_userlist.c (DIE 0x45E0A5) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_17_236 x0;                       // 0x4
    /* 0x004 */ anon_17_236 y0;                       // 0x4
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
} anon_16_236;

/* anon_18_236 -- @anon18, 0x30 bytes, workout_userlist.c (DIE 0x45E306) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_17_236 x0;                       // 0x4
    /* 0x004 */ anon_17_236 y0;                       // 0x4
    /* 0x008 */ anon_17_236 x1;                       // 0x4
    /* 0x00C */ anon_17_236 y1;                       // 0x4
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
} anon_18_236;

/* anon_19_236 -- @anon19, 0x4 bytes, workout_userlist.c (DIE 0x45E6A0) */
typedef struct {   // size 0x4
    /* 0x000 */ anon_15_236 (*step_func)();           // 0x4
} anon_19_236;

/* anon_20_236 -- @anon20, 0xC bytes, workout_userlist.c (DIE 0x45E726) */
typedef struct {   // size 0xC
    /* 0x000 */ anon_19_236 *step_array;              // 0x4
    /* 0x004 */ void (*screen)(int);                  // 0x4
    /* 0x008 */ int step_idx;                         // 0x4
} anon_20_236;

/* anon_21_236 -- @anon21, 0x68 bytes, workout_userlist.c (DIE 0x45E82F) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_17_236 x0;                       // 0x4
    /* 0x004 */ anon_17_236 y0;                       // 0x4
    /* 0x008 */ anon_17_236 x1;                       // 0x4
    /* 0x00C */ anon_17_236 y1;                       // 0x4
    /* 0x010 */ anon_17_236 x2;                       // 0x4
    /* 0x014 */ anon_17_236 y2;                       // 0x4
    /* 0x018 */ anon_17_236 x3;                       // 0x4
    /* 0x01C */ anon_17_236 y3;                       // 0x4
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
    /* 0x064 */ int flg;                              // 0x4
} anon_21_236;

/* anon_23_236 -- @anon23, 0x30 bytes, workout_userlist.c (DIE 0x45ED50) */
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
} anon_23_236;

/* anon_26_236 -- @anon26, 0x84 bytes, workout_userlist.c (DIE 0x45F34C) */
typedef struct {   // size 0x84
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int result;                           // 0x4
    /* 0x008 */ int date;                             // 0x4
    /* 0x00C */ int not_first;                        // 0x4
    /* 0x010 */ int f_cancel;                         // 0x4
    /* 0x014 */ unsigned int *am_local_dec_addr;      // 0x4
    /* 0x018 */ anon_23_236 player[2];                // 0x60
    /* 0x078 */ anon_20_236 hstep;                    // 0xC
} anon_26_236;


/* variables (21) */
static anon_9_236 cardcol_table[3];                              /* not allocated size 0xC */
static unsigned char str_guestcaution[74];                       /* @0x008012C0 size 0x4A */
static float cur_pos[2][3];                                      /* @0x00801310 size 0x18 */
anon_6_236 font_data_nr0[19];                                    /* @0x00801330 size 0x17C */
anon_6_236 font_data_nr2a[19];                                   /* @0x008014B0 size 0x17C */
anon_6_236 font_data_nr2b[19];                                   /* @0x00801630 size 0x17C */
anon_6_236 *font_data_list[3];                                   /* @0x008017B0 size 0xC */
anon_3_236 wo_please_wait[2];                                    /* @0x00801E50 size 0x20 */
anon_13_236 listmenuwork[2];                                     /* @0x00801F10 size 0x60 */
int scrbar_step[2];                                              /* @0x002DE6B0 size 0x8 */
anon_1_236 cardwork[24];                                         /* @0x00801F80 size 0x360 */
anon_0_236 wo_press_start[2];                                    /* @0x00801E70 size 0x10 */
anon_26_236 workout_work;                                        /* @0x0071D880 size 0x84 */
anon_1_236 playercardwork[2];                                    /* @0x00801E80 size 0x48 */
anon_12_236 wou_edit_work[2];                                    /* @0x00802440 size 0x50 */
int scrbar_pos[2];                                               /* @0x002DE6A8 size 0x8 */
anon_10_236 listgcautionwork[2];                                 /* @0x00801ED0 size 0x38 */
anon_8_236 wo_cursor[2];                                         /* @0x008024F0 size 0x50 */
int cursor_pos[2];                                               /* @0x002DE6B8 size 0x8 */
int selection_lock[2];                                           /* @0x002DE6C0 size 0x8 */
static anon_4_236 rot_mat[2];                                    /* not allocated size 0x60 */

/* functions defined (49) */
void wouPleaseWaitTerm(void);                                    /* 0x007F2F40-0x007F2F48 lines 3384-3384 */
void wouPleaseWaitDraw(int pno);                                 /* 0x007F2F50-0x007F3064 lines 3355-3380 */
void wouPleaseWaitAct(int pno);                                  /* 0x007F3070-0x007F3450 lines 3294-3353 */
void wouPleaseWaitInit(int pno);                                 /* 0x007F3450-0x007F3468 lines 3290-3290 */
void wouPressStartSetStatusCloase(int pno);                      /* 0x007F3470-0x007F3498 lines 3140-3144 */
void wouPressStartTerm(void);                                    /* 0x007F34A0-0x007F34A8 lines 3137-3137 */
void wouPressStartDraw(int pno);                                 /* 0x007F34B0-0x007F35BC lines 3109-3133 */
void wouPressStartAct(int pno);                                  /* 0x007F35C0-0x007F3744 lines 3065-3104 */
void wouPressStartInit(int pno);                                 /* 0x007F3750-0x007F3768 lines 3061-3061 */
void wouPlayerCardSetStatusOut(int pno);                         /* 0x007F3770-0x007F37A8 lines 3034-3037 */
void wouPlayerCardTerm(void);                                    /* 0x007F37B0-0x007F37B8 lines 3023-3023 */
void wouPlayerCardDraw(int pno);                                 /* 0x007F37C0-0x007F514C lines 2641-3012 */
void wouPlayerCardAct(int pno);                                  /* 0x007F5150-0x007F5388 lines 2611-2632 */
void wouPlayerCardInit(int pno);                                 /* 0x007F5390-0x007F53FC lines 2541-2547 */
void wouFontPrint(int x, int y, unsigned char *str, int pri, int font_type); /* 0x007F5400-0x007F5610 lines 2466-2501 */
void wouScrBarStepOpen(int pno);                                 /* 0x007F5610-0x007F5628 lines 2296-2297 */
void wouScrBarStepFinish(int pno);                               /* 0x007F5630-0x007F5648 lines 2287-2288 */
void wouScrBarDraw(int pno);                                     /* 0x007F5650-0x007F5858 lines 2249-2278 */
void wouScrBarAct(int pno, int pos, int max, int length);        /* 0x007F5860-0x007F5B18 lines 2206-2241 */
void wouUserGuestCautionTerm(void);                              /* 0x007F5B20-0x007F5B28 lines 2152-2152 */
void wouUserGuestCautionDraw(int pno);                           /* 0x007F5B30-0x007F5BF4 lines 2130-2142 */
void wouUserGuestCautionAct(int pno);                            /* 0x007F5C00-0x007F5EC0 lines 2058-2120 */
void wouUserGuestCautionInit(int pno);                           /* 0x007F5EC0-0x007F5EE0 lines 2046-2046 */
void wouUserMenuStatusReopen(int pno);                           /* 0x007F5EE0-0x007F5F10 lines 1994-2002 */
int wouUserMenuIsFinished(int pno);                              /* 0x007F5F10-0x007F5F50 lines 1968-1969 */
void wouUserMenuTerm(void);                                      /* 0x007F5F50-0x007F5F58 lines 1957-1957 */
void wouUserMenuDraw(int pno);                                   /* 0x007F5F60-0x007F60F8 lines 1912-1946 */
void wouUserMenuAct(int pno);                                    /* 0x007F6100-0x007F6830 lines 1711-1903 */
void wouUserMenuInit(int pno);                                   /* 0x007F6830-0x007F6850 lines 1701-1701 */
void wouCardStatusReopen(int pno);                               /* 0x007F6850-0x007F6A34 lines 1612-1634 */
void wouCardStatusFinish(int pno);                               /* 0x007F6A40-0x007F6AA8 lines 1604-1610 */
void wouCardStatusDelete(int pno);                               /* 0x007F6AB0-0x007F6CD8 lines 1568-1591 */
void wouCardEntry(int pno);                                      /* 0x007F6CE0-0x007F6EC4 lines 1520-1531 */
void wouCardEntryUser(int cno, int pno, int uno);                /* 0x007F6ED0-0x007F6F98 lines 1493-1511 */
void wouCardAct(int pno);                                        /* 0x007F6FA0-0x007F7114 lines 1404-1429 */
static void wouCardDrawCreate(int cno);                          /* 0x007F7120-0x007F7A64 lines 1267-1394 */
static void wouCardDrawGuest(int cno);                           /* 0x007F7A70-0x007F83B4 lines 1130-1257 */
static void wouCardDrawUser(int cno);                            /* 0x007F83C0-0x007FA488 lines 753-1121 */
static void wouCardAct_Stay(int cno);                            /* 0x007FA490-0x007FA5C4 lines 678-701 */
static void wouCardAct_Out(int cno);                             /* 0x007FA5D0-0x007FA780 lines 619-669 */
static void wouCardAct_In(int cno);                              /* 0x007FA780-0x007FA99C lines 561-611 */
int wouListCursorGetCardNo(int pno);                             /* 0x007FA9A0-0x007FAA38 lines 438-454 */
int wouListtIsFinished(int pno);                                 /* 0x007FAA40-0x007FAAE0 lines 392-395 */
void wouListTerm(void);                                          /* 0x007FAAE0-0x007FAAE8 lines 382-382 */
void wouListDraw(int pno);                                       /* 0x007FAAF0-0x007FAC1C lines 363-372 */
void wouListAct(int pno);                                        /* 0x007FAC20-0x007FB294 lines 262-353 */
void wouListInit(int pno);                                       /* 0x007FB2A0-0x007FB3B0 lines 244-252 */
void wouListReopen(int pno);                                     /* 0x007FB3B0-0x007FB3E0 lines 224-227 */
void wouListNext(void);                                          /* 0x007FB3E0-0x007FB4EC lines 189-195 */

#endif /* DDR_UNIT_src_CS_workout_workout_userlist_c_H */
