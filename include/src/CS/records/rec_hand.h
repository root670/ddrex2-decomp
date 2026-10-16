/*
 * C:\work2\usaex2\src\CS\records\rec_hand.c
 * MW MIPS C Compiler, overlay rec_rel4cd.prg; 13 functions, code 0x007F9EA0-0x007FBC24
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_rec_hand_c_H
#define DDR_UNIT_src_CS_records_rec_hand_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8Record1.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cMusicData.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (17) */

/* anon_0_248 -- @anon0, 0x8 bytes, rec_hand.c (DIE 0x489E7B) */
struct anon_0_248 {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

/* anon_1_248 -- @anon1, 0x94 bytes, rec_hand.c (DIE 0x48A0C0) */
struct anon_1_248 {   // size 0x94
    /* 0x000 */ struct _tag_cDDR8Record1 dt;          // 0x8C
    /* 0x08C */ struct _tag_cDDR8Record1 *ori;        // 0x4
    /* 0x090 */ struct _tag_cMusicData *md;           // 0x4
};

/* anon_2_248 -- @anon2, 0x10 bytes, rec_hand.c (DIE 0x48A298) */
struct anon_2_248 {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
};

/* anon_3_248 -- @anon3, 0x48 bytes, rec_hand.c (DIE 0x48A815) */
struct anon_3_248 {   // size 0x48
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

/* anon_4_248 -- @anon4, 0xD40 bytes, rec_hand.c (DIE 0x48AB2B) */
struct anon_4_248 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_5_248 -- @anon5, 0x14 bytes, rec_hand.c (DIE 0x48AE12) */
struct anon_5_248 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_6_248 -- @anon6, 0xC bytes, rec_hand.c (DIE 0x48AF94) */
struct anon_6_248 {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
};

/* anon_7_248 -- @anon7, 0xC bytes, rec_hand.c (DIE 0x48B14E) */
struct anon_7_248 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_8_248 -- @anon8, 0x1300 bytes, rec_hand.c (DIE 0x48B324) */
struct anon_8_248 {   // size 0x1300
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
    /* 0x360 */ struct anon_5_248 subject[200];       // 0xFA0
};

/* anon_12_248 -- @anon12, 0x4 bytes, rec_hand.c (DIE 0x48BB7C) */
struct anon_12_248 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_9_248 -- @anon9, 0x4 bytes, rec_hand.c (DIE 0x48B55E) */
union anon_9_248 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_12_248 s;                 // 0x4
};

/* anon_10_248 -- @anon10, 0x504 bytes, rec_hand.c (DIE 0x48B5E0) */
struct anon_10_248 {   // size 0x504
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char step_s;                 // 0x1
    /* 0x002 */ unsigned char mode;                   // 0x1
    /* 0x003 */ unsigned char flag;                   // 0x1
    /* 0x004 */ unsigned char top_cur;                // 0x1
    /* 0x005 */ unsigned char top_old_cur;            // 0x1
    /* 0x006 */ unsigned char cur_x;                  // 0x1
    /* 0x007 */ unsigned char cur_y;                  // 0x1
    /* 0x008 */ float timer;                          // 0x4
    /* 0x00C */ float timer2;                         // 0x4
    /* 0x010 */ float disap_timer;                    // 0x4
    /* 0x014 */ unsigned int str_addr;                // 0x4
    /* 0x018 */ float win_y;                          // 0x4
    /* 0x01C */ int idx;                              // 0x4
    /* 0x020 */ int repcnt;                           // 0x4
    /* 0x024 */ void *record_ad;                      // 0x4
    /* 0x028 */ int m_num;                            // 0x4
    /* 0x02C */ float star_t;                         // 0x4
    /* 0x030 */ float scr_y;                          // 0x4
    /* 0x034 */ struct anon_0_248 title_info[80];     // 0x280
    /* 0x2B4 */ struct anon_6_248 xmove[40];          // 0x1E0
    /* 0x494 */ float scr_t;                          // 0x4
    /* 0x498 */ unsigned char er_step;                // 0x1
    /* 0x499 */ unsigned char yn_cur;                 // 0x1
    /* 0x49A */ unsigned char del_alpha;              // 0x1
    /* 0x49B */ // 0x1 bytes padding
    /* 0x49C */ short tex_start;                      // 0x2
    /* 0x49E */ // 0x2 bytes padding
    /* 0x4A0 */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x4AC */ void *obj_p[22];                      // 0x58
};

/* anon_15_248 -- @anon15, 0x4 bytes, rec_hand.c (DIE 0x48C20C) */
union anon_15_248 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_11_248 -- @anon11, 0x24 bytes, rec_hand.c (DIE 0x48B9E7) */
struct anon_11_248 {   // size 0x24
    /* 0x000 */ union anon_15_248 x0;                 // 0x4
    /* 0x004 */ union anon_15_248 y0;                 // 0x4
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

/* anon_13_248 -- @anon13, 0x12E0 bytes, rec_hand.c (DIE 0x48BDF6) */
struct anon_13_248 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_7_248 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_14_248 -- @anon14, 0x2134 bytes, rec_hand.c (DIE 0x48C029) */
struct anon_14_248 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_9_248 userpass;            // 0x4
    /* 0x008 */ struct anon_13_248 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_4_248 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_16_248 -- @anon16, 0x4 bytes, rec_hand.c (DIE 0x48C36A) */
struct anon_16_248 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};


/* variables (2) */
struct anon_10_248 *rw;                                          /* @0x002DDFB4 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (13) */
static int check_data_enable_hand(struct _tag_cDDR8Record1 *src); /* 0x007F9EA0-0x007F9F34 lines 849-878 */
static void rec_hand_item_disp_sub(struct _tag_cDDR8Record1 *hr, float x, float y, unsigned char erase_bri); /* 0x007F9F40-0x007FA348 lines 751-824 */
static void rec_hand_init(struct anon_10_248 *rw);               /* 0x007FA350-0x007FA54C lines 667-734 */
int Rec_Hand_BoolDelete(struct anon_10_248 *rw);                 /* 0x007FA550-0x007FA650 lines 640-657 */
int RCObj_hand_obj_disp(void);                                   /* 0x007FA650-0x007FA870 lines 583-632 */
int RCObj_hand_obj_disap(void *wp);                              /* 0x007FA870-0x007FA9D4 lines 544-580 */
int RCObj_hand_obj_apper(void *wp);                              /* 0x007FA9E0-0x007FAB2C lines 500-541 */
int RCObj_hand_item_disp(void *wp);                              /* 0x007FAB30-0x007FAE74 lines 399-493 */
int RCObj_hand_item_disap(void *wp);                             /* 0x007FAE80-0x007FAF80 lines 366-396 */
int RCObj_hand_item_apper(void *wp);                             /* 0x007FAF80-0x007FB088 lines 332-363 */
void Rec_Hand_Delete(struct anon_10_248 *rw);                    /* 0x007FB090-0x007FB150 lines 311-326 */
void Rec_Hand_DetailDisp(void *wp);                              /* 0x007FB150-0x007FB564 lines 254-305 */
unsigned char Rec_Hand(struct anon_10_248 *rw);                  /* 0x007FB570-0x007FBC24 lines 68-249 */

#endif /* DDR_UNIT_src_CS_records_rec_hand_c_H */
