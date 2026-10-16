/*
 * C:\work2\usaex2\src\CS\workout\workout_useredit.c
 * MW MIPS C Compiler, overlay workout_rel4cd.prg; 18 functions, code 0x007FB4F0-0x007FE17C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_workout_workout_useredit_c_H
#define DDR_UNIT_src_CS_workout_workout_useredit_c_H

#include "types/oni_course.h"

/* anonymous types (16) */

/* anon_4_237 -- @anon4, 0x4 bytes, workout_useredit.c (DIE 0x4641B4) */
struct anon_4_237 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_3_237 -- @anon3, 0x4 bytes, workout_useredit.c (DIE 0x464156) */
union anon_3_237 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_4_237 s;                  // 0x4
};

/* anon_13_237 -- @anon13, 0xC bytes, workout_useredit.c (DIE 0x465424) */
struct anon_13_237 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_14_237 -- @anon14, 0x12E0 bytes, workout_useredit.c (DIE 0x46556B) */
struct anon_14_237 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_13_237 history[400];      // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_15_237 -- @anon15, 0xD40 bytes, workout_useredit.c (DIE 0x4656EA) */
struct anon_15_237 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_0_237 -- @anon0, 0x2134 bytes, workout_useredit.c (DIE 0x463E43) */
struct anon_0_237 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_3_237 userpass;            // 0x4
    /* 0x008 */ struct anon_14_237 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_15_237 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_1_237 -- @anon1, 0xC bytes, workout_useredit.c (DIE 0x464025) */
struct anon_1_237 {   // size 0xC
    /* 0x000 */ int cur_x;                            // 0x4
    /* 0x004 */ int cur_y;                            // 0x4
    /* 0x008 */ int scrl;                             // 0x4
};

/* anon_2_237 -- @anon2, 0x8 bytes, workout_useredit.c (DIE 0x4640CD) */
struct anon_2_237 {   // size 0x8
    /* 0x000 */ int cur_x;                            // 0x4
    /* 0x004 */ int cur_y;                            // 0x4
};

/* anon_5_237 -- @anon5, 0x48 bytes, workout_useredit.c (DIE 0x4645F8) */
struct anon_5_237 {   // size 0x48
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

/* anon_6_237 -- @anon6, 0x28 bytes, workout_useredit.c (DIE 0x46487A) */
struct anon_6_237 {   // size 0x28
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
};

/* anon_7_237 -- @anon7, 0x18 bytes, workout_useredit.c (DIE 0x464A06) */
struct anon_7_237 {   // size 0x18
    /* 0x000 */ int x0;                               // 0x4
    /* 0x004 */ int y0;                               // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int step;                             // 0x4
    /* 0x014 */ int counter;                          // 0x4
};

/* anon_11_237 -- @anon11, 0x4 bytes, workout_useredit.c (DIE 0x464F96) */
union anon_11_237 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_8_237 -- @anon8, 0x1C bytes, workout_useredit.c (DIE 0x464B08) */
struct anon_8_237 {   // size 0x1C
    /* 0x000 */ union anon_11_237 x0;                 // 0x4
    /* 0x004 */ union anon_11_237 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_9_237 -- @anon9, 0x28 bytes, workout_useredit.c (DIE 0x464C60) */
struct anon_9_237 {   // size 0x28
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

/* anon_10_237 -- @anon10, 0x24 bytes, workout_useredit.c (DIE 0x464DDB) */
struct anon_10_237 {   // size 0x24
    /* 0x000 */ union anon_11_237 x0;                 // 0x4
    /* 0x004 */ union anon_11_237 y0;                 // 0x4
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

/* anon_12_237 -- @anon12, 0x30 bytes, workout_useredit.c (DIE 0x464FF4) */
struct anon_12_237 {   // size 0x30
    /* 0x000 */ union anon_11_237 x0;                 // 0x4
    /* 0x004 */ union anon_11_237 y0;                 // 0x4
    /* 0x008 */ union anon_11_237 x1;                 // 0x4
    /* 0x00C */ union anon_11_237 y1;                 // 0x4
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


/* variables (9) */
static void (*act_func[7])(int);                                 /* @0x008017C0 size 0x1C */
int size_of_editfact[5];                                         /* @0x008017E0 size 0x14 */
static unsigned char str_passchar[5];                            /* not allocated size 0x5 */
static int cursor_y_pos[5];                                      /* not allocated size 0x14 */
struct anon_6_237 wou_edit_work[2];                              /* @0x00802440 size 0x50 */
struct anon_2_237 editframework[2];                              /* @0x008023E0 size 0x10 */
struct anon_1_237 editiconwork[2];                               /* @0x008023F0 size 0x18 */
struct anon_7_237 editsheetwork[2];                              /* @0x00802410 size 0x30 */
struct anon_9_237 wo_cursor[2];                                  /* @0x008024F0 size 0x50 */

/* functions defined (18) */
void wouGuestPlayerDataInit(int pno);                            /* 0x007FB4F0-0x007FB688 lines 1422-1447 */
void wouCreatePlayerDataInit(int pno, int uno);                  /* 0x007FB690-0x007FB820 lines 1391-1413 */
void wouEditPlayerDataInit(int pno);                             /* 0x007FB820-0x007FB980 lines 1369-1379 */
static void wouEditFinalAct(int pno);                            /* 0x007FB980-0x007FBF74 lines 1233-1323 */
static void wouEditRegistPassAct(int pno);                       /* 0x007FBF80-0x007FC2D4 lines 1149-1209 */
static void wouEditUsePassAct(int pno);                          /* 0x007FC2E0-0x007FC590 lines 1042-1098 */
static void wouEditFrameIconDraw(int pno);                       /* 0x007FC590-0x007FC824 lines 841-894 */
static void wouEditFrameIconAct(int pno);                        /* 0x007FC830-0x007FCB04 lines 794-833 */
static void wouEditFaceIconDraw(int pno);                        /* 0x007FCB10-0x007FCEB4 lines 675-742 */
static void wouEditFaceIconAct(int pno);                         /* 0x007FCEC0-0x007FD274 lines 606-666 */
static void wouEditSheet_Draw(int pno);                          /* 0x007FD280-0x007FDA70 lines 427-531 */
static int wouEditSheet_Act(int pno);                            /* 0x007FDA70-0x007FDD30 lines 272-348 */
void wouEditStatusFinish(int pno);                               /* 0x007FDD30-0x007FDD88 lines 209-211 */
void wouEditTerm(int pno);                                       /* 0x007FDD90-0x007FDDBC lines 192-199 */
void wouEditDraw(int pno);                                       /* 0x007FDDC0-0x007FDDEC lines 178-183 */
void wouEditAct(int pno);                                        /* 0x007FDDF0-0x007FDFA0 lines 133-168 */
static void wouEditEndAct(int pno);                              /* 0x007FDFA0-0x007FDFC0 lines 118-120 */
void wouEditInit(int pno);                                       /* 0x007FDFC0-0x007FE17C lines 90-100 */

#endif /* DDR_UNIT_src_CS_workout_workout_useredit_c_H */
