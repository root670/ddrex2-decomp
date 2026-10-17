/*
 * C:\work2\usaex2\src\CS\records\rec_cmb.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0025AB40-0x0025B2C8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_records_rec_cmb_c_H
#define DDR_UNIT_src_CS_records_rec_cmb_c_H

#include "types/_tag_cCoCursor01.h"

/* anonymous types (8) */

/* anon_0_140 -- @anon0, 0x48 bytes, rec_cmb.c (DIE 0x25D41E) */
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
} anon_0_140;

/* anon_4_140 -- @anon4, 0x4 bytes, rec_cmb.c (DIE 0x25DCD7) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_4_140;

/* anon_1_140 -- @anon1, 0x24 bytes, rec_cmb.c (DIE 0x25D6A0) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_4_140 x0;                        // 0x4
    /* 0x004 */ anon_4_140 y0;                        // 0x4
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
} anon_1_140;

/* anon_6_140 -- @anon6, 0x8 bytes, rec_cmb.c (DIE 0x25DF16) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
} anon_6_140;

/* anon_5_140 -- @anon5, 0xC bytes, rec_cmb.c (DIE 0x25DD80) */
typedef struct {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
} anon_5_140;

/* anon_2_140 -- @anon2, 0x504 bytes, rec_cmb.c (DIE 0x25D834) */
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
    /* 0x034 */ anon_6_140 title_info[80];            // 0x280
    /* 0x2B4 */ anon_5_140 xmove[40];                 // 0x1E0
    /* 0x494 */ float scr_t;                          // 0x4
    /* 0x498 */ unsigned char er_step;                // 0x1
    /* 0x499 */ unsigned char yn_cur;                 // 0x1
    /* 0x49A */ unsigned char del_alpha;              // 0x1
    /* 0x49B */ // 0x1 bytes padding
    /* 0x49C */ short tex_start;                      // 0x2
    /* 0x49E */ // 0x2 bytes padding
    /* 0x4A0 */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x4AC */ void *obj_p[22];                      // 0x58
} anon_2_140;

/* anon_3_140 -- @anon3, 0x10 bytes, rec_cmb.c (DIE 0x25DC3A) */
typedef struct {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
} anon_3_140;

/* anon_7_140 -- @anon7, 0x8 bytes, rec_cmb.c (DIE 0x25DFA2) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned int score;                   // 0x4
    /* 0x004 */ int stage;                            // 0x4
} anon_7_140;


/* variables (2) */
static anon_7_140 dummy_data[9];                                 /* @0x002BF8C0 size 0x48 */
anon_2_140 *rw;                                                  /* @0x002DDFB4 size 0x4 */

/* functions defined (8) */
static void rec_cmb_item_disp_sub(float x, float y, unsigned char kind); /* 0x0025AB40-0x0025AD6C lines 227-268 */
int Rec_Cmb_BoolDelete(anon_2_140 *rw);                          /* 0x0025AD70-0x0025AD90 lines 217-219 */
int RCObj_cmb_item_disp(void);                                   /* 0x0025AD90-0x0025AEC4 lines 171-209 */
int RCObj_cmb_item_disap(void *wp);                              /* 0x0025AED0-0x0025AED8 lines 167-167 */
int RCObj_cmb_item_apper(void *wp);                              /* 0x0025AEE0-0x0025AEE8 lines 162-162 */
void Rec_Cmb_Delete(anon_2_140 *rw);                             /* 0x0025AEF0-0x0025AF10 lines 151-155 */
void Rec_Cmb_DetailDisp(void *wp);                               /* 0x0025AF10-0x0025B0F4 lines 120-144 */
unsigned char Rec_Cmb(anon_2_140 *rw);                           /* 0x0025B100-0x0025B2C8 lines 47-115 */

#endif /* DDR_UNIT_src_CS_records_rec_cmb_c_H */
