/*
 * C:\work2\usaex2\src\CS\records\rec_end.c
 * MW MIPS C Compiler, overlay rec_rel4cd.prg; 9 functions, code 0x007F8EC0-0x007F9E98
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_records_rec_end_c_H
#define DDR_UNIT_src_CS_records_rec_end_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (13) */

/* anon_0_247 -- @anon0, 0x10 bytes, rec_end.c (DIE 0x485127) */
typedef struct {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
} anon_0_247;

/* anon_1_247 -- @anon1, 0xC bytes, rec_end.c (DIE 0x4853EF) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
} anon_1_247;

/* anon_2_247 -- @anon2, 0x48 bytes, rec_end.c (DIE 0x4854CD) */
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
} anon_2_247;

/* anon_3_247 -- @anon3, 0xD40 bytes, rec_end.c (DIE 0x485809) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_3_247;

/* anon_4_247 -- @anon4, 0x14 bytes, rec_end.c (DIE 0x485C3B) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_4_247;

/* anon_15_247 -- @anon15, 0x8 bytes, rec_end.c (DIE 0x48899D) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
} anon_15_247;

/* anon_5_247 -- @anon5, 0x504 bytes, rec_end.c (DIE 0x485DBD) */
typedef struct {   // size 0x504
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
    /* 0x034 */ anon_15_247 title_info[80];           // 0x280
    /* 0x2B4 */ anon_1_247 xmove[40];                 // 0x1E0
    /* 0x494 */ float scr_t;                          // 0x4
    /* 0x498 */ unsigned char er_step;                // 0x1
    /* 0x499 */ unsigned char yn_cur;                 // 0x1
    /* 0x49A */ unsigned char del_alpha;              // 0x1
    /* 0x49B */ // 0x1 bytes padding
    /* 0x49C */ short tex_start;                      // 0x2
    /* 0x49E */ // 0x2 bytes padding
    /* 0x4A0 */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x4AC */ void *obj_p[22];                      // 0x58
} anon_5_247;

/* anon_6_247 -- @anon6, 0xC bytes, rec_end.c (DIE 0x48629F) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_6_247;

/* anon_10_247 -- @anon10, 0x4 bytes, rec_end.c (DIE 0x486811) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_10_247;

/* anon_8_247 -- @anon8, 0x4 bytes, rec_end.c (DIE 0x48661F) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_10_247 s;                        // 0x4
} anon_8_247;

/* anon_12_247 -- @anon12, 0x4 bytes, rec_end.c (DIE 0x486C76) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_12_247;

/* anon_9_247 -- @anon9, 0x24 bytes, rec_end.c (DIE 0x48667D) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_12_247 x0;                       // 0x4
    /* 0x004 */ anon_12_247 y0;                       // 0x4
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
} anon_9_247;

/* anon_11_247 -- @anon11, 0x12E0 bytes, rec_end.c (DIE 0x486A67) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_6_247 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_11_247;


/* variables (2) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
anon_5_247 *rw;                                                  /* @0x002DDFB4 size 0x4 */

/* functions defined (9) */
static void rec_end_score_disp(float x, float y, unsigned int dig0, unsigned int dig1, int pri, unsigned char alpha); /* 0x007F8EC0-0x007F9180 lines 358-404 */
static void rec_end_item_disp_sub(float x, float y, unsigned char kind); /* 0x007F9180-0x007F93D4 lines 306-344 */
int Rec_End_BoolDelete(anon_5_247 *rw);                          /* 0x007F93E0-0x007F9468 lines 293-298 */
int RCObj_end_item_disp(void);                                   /* 0x007F9470-0x007F95A4 lines 250-288 */
int RCObj_end_item_disap(void *wp);                              /* 0x007F95B0-0x007F967C lines 219-247 */
int RCObj_end_item_apper(void *wp);                              /* 0x007F9680-0x007F976C lines 188-216 */
void Rec_End_Delete(anon_5_247 *rw);                             /* 0x007F9770-0x007F9890 lines 163-182 */
void Rec_End_DetailDisp(void *wp);                               /* 0x007F9890-0x007F9C70 lines 113-155 */
unsigned char Rec_End(anon_5_247 *rw);                           /* 0x007F9C70-0x007F9E98 lines 39-108 */

#endif /* DDR_UNIT_src_CS_records_rec_end_c_H */
