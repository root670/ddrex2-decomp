/*
 * C:\work2\usaex2\src\CS\records\rec_nor.c
 * MW MIPS C Compiler, overlay main; 12 functions, code 0x002581E0-0x00259F0C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_rec_nor_c_H
#define DDR_UNIT_src_CS_records_rec_nor_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8OniRecord1.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (18) */

/* anon_0_138 -- @anon0, 0xC bytes, rec_nor.c (DIE 0x2566A7) */
struct anon_0_138 {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
};

/* anon_17_138 -- @anon17, 0x8 bytes, rec_nor.c (DIE 0x25A0A5) */
struct anon_17_138 {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

/* anon_1_138 -- @anon1, 0x504 bytes, rec_nor.c (DIE 0x256A0B) */
struct anon_1_138 {   // size 0x504
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
    /* 0x034 */ struct anon_17_138 title_info[80];    // 0x280
    /* 0x2B4 */ struct anon_0_138 xmove[40];          // 0x1E0
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

/* anon_2_138 -- @anon2, 0x48 bytes, rec_nor.c (DIE 0x256FCC) */
struct anon_2_138 {   // size 0x48
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

/* anon_3_138 -- @anon3, 0xD40 bytes, rec_nor.c (DIE 0x2572BE) */
struct anon_3_138 {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_4_138 -- @anon4, 0x14 bytes, rec_nor.c (DIE 0x2576F0) */
struct anon_4_138 {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
};

/* anon_5_138 -- @anon5, 0xC bytes, rec_nor.c (DIE 0x25794E) */
struct anon_5_138 {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
};

/* anon_6_138 -- @anon6, 0x5C bytes, rec_nor.c (DIE 0x257A70) */
struct anon_6_138 {   // size 0x5C
    /* 0x000 */ struct _tag_cDDR8OniRecord1 dt_n;     // 0x28
    /* 0x028 */ struct _tag_cDDR8OniRecord1 dt_d;     // 0x28
    /* 0x050 */ struct _tag_cDDR8OniRecord1 *ori_n;   // 0x4
    /* 0x054 */ struct _tag_cDDR8OniRecord1 *ori_d;   // 0x4
    /* 0x058 */ int course;                           // 0x4
};

/* anon_7_138 -- @anon7, 0x1300 bytes, rec_nor.c (DIE 0x257BB2) */
struct anon_7_138 {   // size 0x1300
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
    /* 0x360 */ struct anon_4_138 subject[200];       // 0xFA0
};

/* anon_10_138 -- @anon10, 0x4 bytes, rec_nor.c (DIE 0x257F96) */
struct anon_10_138 {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
};

/* anon_8_138 -- @anon8, 0x4 bytes, rec_nor.c (DIE 0x257DA4) */
union anon_8_138 {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ struct anon_10_138 s;                 // 0x4
};

/* anon_13_138 -- @anon13, 0x4 bytes, rec_nor.c (DIE 0x2583EC) */
union anon_13_138 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_9_138 -- @anon9, 0x24 bytes, rec_nor.c (DIE 0x257E02) */
struct anon_9_138 {   // size 0x24
    /* 0x000 */ union anon_13_138 x0;                 // 0x4
    /* 0x004 */ union anon_13_138 y0;                 // 0x4
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

/* anon_11_138 -- @anon11, 0x12E0 bytes, rec_nor.c (DIE 0x257FFA) */
struct anon_11_138 {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ struct anon_5_138 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
};

/* anon_12_138 -- @anon12, 0x2134 bytes, rec_nor.c (DIE 0x258209) */
struct anon_12_138 {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ union anon_8_138 userpass;            // 0x4
    /* 0x008 */ struct anon_11_138 pwork;             // 0x12E0
    /* 0x12E8 */ struct anon_3_138 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
};

/* anon_14_138 -- @anon14, 0x4 bytes, rec_nor.c (DIE 0x25854A) */
struct anon_14_138 {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
};

/* anon_15_138 -- @anon15, 0x10 bytes, rec_nor.c (DIE 0x258D50) */
struct anon_15_138 {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
};

/* anon_16_138 -- @anon16, 0x5C bytes, rec_nor.c (DIE 0x259609) */
struct anon_16_138 {   // size 0x5C
    /* 0x000 */ struct _tag_cDDR8OniRecord1 dt_n;     // 0x28
    /* 0x028 */ struct _tag_cDDR8OniRecord1 dt_d;     // 0x28
    /* 0x050 */ struct _tag_cDDR8OniRecord1 *ori_n;   // 0x4
    /* 0x054 */ struct _tag_cDDR8OniRecord1 *ori_d;   // 0x4
    /* 0x058 */ int course;                           // 0x4
};


/* variables (2) */
struct anon_1_138 *rw;                                           /* @0x002DDFB4 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (12) */
static void rec_nor_item_disp_sub(struct anon_6_138 *rd, float x, float y, unsigned char erase_bri); /* 0x002581E0-0x0025873C lines 632-745 */
static void rec_nor_init(struct anon_1_138 *rw);                 /* 0x00258740-0x00258A08 lines 557-616 */
int Rec_Nor_BoolDelete(struct anon_1_138 *rw);                   /* 0x00258A10-0x00258AE0 lines 535-548 */
int RCObj_nor_obj_disp(void *wp);                                /* 0x00258AE0-0x00258AE8 lines 525-525 */
int RCObj_nor_obj_disap(void *wp);                               /* 0x00258AF0-0x00258AF8 lines 518-518 */
int RCObj_nor_obj_apper(void *wp);                               /* 0x00258B00-0x00258B08 lines 511-511 */
int RCObj_nor_item_disp(void *wp);                               /* 0x00258B10-0x00258E54 lines 415-502 */
int RCObj_nor_item_disap(void *wp);                              /* 0x00258E60-0x00258F60 lines 382-412 */
int RCObj_nor_item_apper(void *wp);                              /* 0x00258F60-0x00259068 lines 348-379 */
void Rec_Nor_Delete(struct anon_1_138 *rw);                      /* 0x00259070-0x0025913C lines 322-342 */
void Rec_Nor_DetailDisp(void *wp);                               /* 0x00259140-0x00259968 lines 217-316 */
unsigned char Rec_Nor(struct anon_1_138 *rw);                    /* 0x00259970-0x00259F0C lines 48-212 */

#endif /* DDR_UNIT_src_CS_records_rec_nor_c_H */
