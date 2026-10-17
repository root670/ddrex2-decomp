/*
 * C:\work2\usaex2\src\CS\records\rec_hi.c
 * MW MIPS C Compiler, overlay rec_rel4cd.prg; 13 functions, code 0x007F5130-0x007F6F84
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_records_rec_hi_c_H
#define DDR_UNIT_src_CS_records_rec_hi_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cDDR8Record1.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/_tag_cMusicData.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (14) */

/* anon_0_245 -- @anon0, 0xC bytes, rec_hi.c (DIE 0x47CC92) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
} anon_0_245;

/* anon_1_245 -- @anon1, 0x8 bytes, rec_hi.c (DIE 0x47CD70) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
} anon_1_245;

/* anon_2_245 -- @anon2, 0x10 bytes, rec_hi.c (DIE 0x47D001) */
typedef struct {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
} anon_2_245;

/* anon_3_245 -- @anon3, 0x48 bytes, rec_hi.c (DIE 0x47D6CB) */
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
} anon_3_245;

/* anon_4_245 -- @anon4, 0x94 bytes, rec_hi.c (DIE 0x47D973) */
typedef struct {   // size 0x94
    /* 0x000 */ struct _tag_cDDR8Record1 dt;          // 0x8C
    /* 0x08C */ struct _tag_cDDR8Record1 *ori;        // 0x4
    /* 0x090 */ struct _tag_cMusicData *md;           // 0x4
} anon_4_245;

/* anon_5_245 -- @anon5, 0xD40 bytes, rec_hi.c (DIE 0x47DA6A) */
typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_5_245;

/* anon_6_245 -- @anon6, 0x14 bytes, rec_hi.c (DIE 0x47DD75) */
typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_6_245;

/* anon_7_245 -- @anon7, 0xC bytes, rec_hi.c (DIE 0x47DFD3) */
typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_7_245;

/* anon_12_245 -- @anon12, 0x4 bytes, rec_hi.c (DIE 0x47EA01) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char d[4];                   // 0x4
} anon_12_245;

/* anon_9_245 -- @anon9, 0x4 bytes, rec_hi.c (DIE 0x47E3E3) */
typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_12_245 s;                        // 0x4
} anon_9_245;

/* anon_10_245 -- @anon10, 0x504 bytes, rec_hi.c (DIE 0x47E465) */
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
    /* 0x034 */ anon_1_245 title_info[80];            // 0x280
    /* 0x2B4 */ anon_0_245 xmove[40];                 // 0x1E0
    /* 0x494 */ float scr_t;                          // 0x4
    /* 0x498 */ unsigned char er_step;                // 0x1
    /* 0x499 */ unsigned char yn_cur;                 // 0x1
    /* 0x49A */ unsigned char del_alpha;              // 0x1
    /* 0x49B */ // 0x1 bytes padding
    /* 0x49C */ short tex_start;                      // 0x2
    /* 0x49E */ // 0x2 bytes padding
    /* 0x4A0 */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x4AC */ void *obj_p[22];                      // 0x58
} anon_10_245;

/* anon_15_245 -- @anon15, 0x4 bytes, rec_hi.c (DIE 0x47F091) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_15_245;

/* anon_11_245 -- @anon11, 0x24 bytes, rec_hi.c (DIE 0x47E86C) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_15_245 x0;                       // 0x4
    /* 0x004 */ anon_15_245 y0;                       // 0x4
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
} anon_11_245;

/* anon_13_245 -- @anon13, 0x12E0 bytes, rec_hi.c (DIE 0x47EC7B) */
typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_7_245 history[400];              // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_13_245;


/* variables (2) */
anon_10_245 *rw;                                                 /* @0x002DDFB4 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (13) */
static int check_data_enable_hi(struct _tag_cDDR8Record1 *src);  /* 0x007F5130-0x007F51C4 lines 868-897 */
static void rec_hi_item_disp_sub(struct _tag_cDDR8Record1 *hr, float x, float y, unsigned char erase_bri); /* 0x007F51D0-0x007F5638 lines 765-843 */
static void rec_hi_init(anon_10_245 *rw);                        /* 0x007F5640-0x007F582C lines 682-748 */
int Rec_Hi_BoolDelete(anon_10_245 *rw);                          /* 0x007F5830-0x007F5910 lines 655-672 */
int RCObj_hi_obj_disp(void);                                     /* 0x007F5910-0x007F5BD0 lines 586-647 */
int RCObj_hi_obj_disap(void *wp);                                /* 0x007F5BD0-0x007F5D5C lines 542-583 */
int RCObj_hi_obj_apper(void *wp);                                /* 0x007F5D60-0x007F5ED4 lines 495-539 */
int RCObj_hi_item_disp(void *wp);                                /* 0x007F5EE0-0x007F6224 lines 395-489 */
int RCObj_hi_item_disap(void *wp);                               /* 0x007F6230-0x007F6330 lines 362-392 */
int RCObj_hi_item_apper(void *wp);                               /* 0x007F6330-0x007F6438 lines 330-359 */
void Rec_Hi_Delete(anon_10_245 *rw);                             /* 0x007F6440-0x007F64E4 lines 308-323 */
void Rec_Hi_DetailDisp(void *wp);                                /* 0x007F64F0-0x007F68EC lines 251-302 */
unsigned char Rec_Hi(anon_10_245 *rw);                           /* 0x007F68F0-0x007F6F84 lines 68-246 */

#endif /* DDR_UNIT_src_CS_records_rec_hi_c_H */
