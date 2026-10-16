/*
 * C:\work2\usaex2\src\CS\workout\workout_usrrpass.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 24 functions, code 0x007FE180-0x007FFE20
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_usrrpass_c_H
#define DDR_UNIT_src_CS_workout_workout_usrrpass_c_H

#include "types/_CWS_WIN_W.h"
#include "types/oni_course.h"

/* anonymous types (13) */

/* anon_0_238 -- @anon0, 0x30 bytes, workout_usrrpass.c (DIE 0x467A76) */
struct anon_0_238 {   // size 0x30
    /* 0x000 */ int x0;                               // 0x4
    /* 0x004 */ int y0;                               // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int step;                             // 0x4
    /* 0x014 */ int IsFinished;                       // 0x4
    /* 0x018 */ int counter;                          // 0x4
    /* 0x01C */ int step_w;                           // 0x4
    /* 0x020 */ int counter_w;                        // 0x4
    /* 0x024 */ int key_no;                           // 0x4
    /* 0x028 */ unsigned char pass[4];                // 0x4
    /* 0x02C */ unsigned char re_pass[4];             // 0x4
};

/* anon_2_238 -- @anon2, 0x4 bytes, workout_usrrpass.c (DIE 0x467C8E) */
struct anon_2_238 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_1_238 -- @anon1, 0x4 bytes, workout_usrrpass.c (DIE 0x467C30) */
union anon_1_238 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_2_238 s;                  // 0x4
};

/* anon_9_238 -- @anon9, 0xC bytes, workout_usrrpass.c (DIE 0x469158) */
struct anon_9_238 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_10_238 -- @anon10, 0x12E0 bytes, workout_usrrpass.c (DIE 0x4694E6) */
struct anon_10_238 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_9_238 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_11_238 -- @anon11, 0xD40 bytes, workout_usrrpass.c (DIE 0x46968E) */
struct anon_11_238 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_3_238 -- @anon3, 0x2134 bytes, workout_usrrpass.c (DIE 0x467CF1) */
struct anon_3_238 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_1_238 userpass;            // 0x4
    /* 0x008 */ struct anon_10_238 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_11_238 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_4_238 -- @anon4, 0x28 bytes, workout_usrrpass.c (DIE 0x46821F) */
struct anon_4_238 {   // size 0x28
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
};

/* anon_5_238 -- @anon5, 0x48 bytes, workout_usrrpass.c (DIE 0x4683BE) */
struct anon_5_238 {   // size 0x48
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

/* anon_7_238 -- @anon7, 0x4 bytes, workout_usrrpass.c (DIE 0x468A08) */
union anon_7_238 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_6_238 -- @anon6, 0x24 bytes, workout_usrrpass.c (DIE 0x468850) */
struct anon_6_238 {   // size 0x24
    /* 0x000 */ union anon_7_238 x0;                  // 0x4
    /* 0x004 */ union anon_7_238 y0;                  // 0x4
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
};

/* anon_8_238 -- @anon8, 0x30 bytes, workout_usrrpass.c (DIE 0x468C6B) */
struct anon_8_238 {   // size 0x30
    /* 0x000 */ union anon_7_238 x0;                  // 0x4
    /* 0x004 */ union anon_7_238 y0;                  // 0x4
    /* 0x008 */ union anon_7_238 x1;                  // 0x4
    /* 0x00C */ union anon_7_238 y1;                  // 0x4
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

/* anon_12_238 -- @anon12, 0x8 bytes, workout_usrrpass.c (DIE 0x4697D2) */
struct anon_12_238 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (7) */
static void (*regact_func[6])(int);                              /* @0x00801800 size 0x18 */
static unsigned char str_r_pass_a[9];                            /* not allocated size 0x9 */
static unsigned char str_r_pass_b[17];                           /* not allocated size 0x11 */
static unsigned char str_passchar[5];                            /* not allocated size 0x5 */
static void (*entact_func[5])(int);                              /* @0x00801820 size 0x14 */
struct anon_4_238 wo_cursor[2];                                  /* @0x008024F0 size 0x50 */
struct anon_0_238 r_pass[2];                                     /* @0x00802490 size 0x60 */

/* functions defined (24) */
void wouEnterPasswordDraw(int pno);                              /* 0x007FE180-0x007FE6E0 lines 702-787 */
int wouEnterPasswordIsRegisted(int pno);                         /* 0x007FE6E0-0x007FE748 lines 692-693 */
int wouEnterPasswordIsFinished(int pno);                         /* 0x007FE750-0x007FE770 lines 688-689 */
void wouEnterPasswordAct(int pno);                               /* 0x007FE770-0x007FE9C4 lines 628-684 */
void wouEnterPasswordInit(int pno);                              /* 0x007FE9D0-0x007FE9F0 lines 624-624 */
static void wouEnterPasswordWarningTerm(int pno);                /* 0x007FE9F0-0x007FEA64 lines 599-604 */
static void wouEnterPasswordWarning(int pno);                    /* 0x007FEA70-0x007FEAFC lines 585-597 */
static void wouEnterPasswordWarningInit(int pno);                /* 0x007FEB00-0x007FEC24 lines 564-582 */
static void wouEnterPasswordCloseWaiting(int pno);               /* 0x007FEC30-0x007FEC70 lines 553-558 */
static void wouEnterPasswordEntering(int pno);                   /* 0x007FEC70-0x007FED5C lines 502-535 */
unsigned int wouRegisterPasswordGetWord(int pno);                /* 0x007FED60-0x007FED80 lines 470-471 */
int wouRegisterPasswordIsRegisted(int pno);                      /* 0x007FED80-0x007FEDE8 lines 461-465 */
int wouRegisterPasswordIsFinished(int pno);                      /* 0x007FEDF0-0x007FEE10 lines 456-457 */
void wouRegisterPasswordTerm(void);                              /* 0x007FEE10-0x007FEE18 lines 450-450 */
void wouRegisterPasswordDraw(int pno);                           /* 0x007FEE20-0x007FF728 lines 283-440 */
void wouRegisterPasswordAct(int pno);                            /* 0x007FF730-0x007FF8F4 lines 228-268 */
void wouRegisterPasswordInit(int pno);                           /* 0x007FF900-0x007FF920 lines 218-218 */
static void wouRegisterPasswordCloseWaiting(int pno);            /* 0x007FF920-0x007FF960 lines 194-199 */
static void wouRegisterPasswordWarningTerm(int pno);             /* 0x007FF960-0x007FF9D4 lines 184-189 */
static void wouRegisterPasswordWarning(int pno);                 /* 0x007FF9E0-0x007FFA6C lines 170-182 */
static void wouRegisterPasswordWarningInit(int pno);             /* 0x007FFA70-0x007FFB94 lines 150-167 */
static void wouRegisterPasswordRetyping(int pno);                /* 0x007FFBA0-0x007FFC88 lines 112-140 */
static void wouRegisterPasswordEntering(int pno);                /* 0x007FFC90-0x007FFD40 lines 85-109 */
static int wouGetPassTyping(int pno);                            /* 0x007FFD40-0x007FFE20 lines 63-81 */

#endif /* DDR_UNIT_src_CS_workout_workout_usrrpass_c_H */
