/*
 * C:\work2\usaex2\src\CS\records\rec_suv.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00259F10-0x0025AB38
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_rec_suv_c_H
#define DDR_UNIT_src_CS_records_rec_suv_c_H

#include "types/_tag_cCoCursor01.h"

/* anonymous types (8) */

/* anon_0_139 -- @anon0, 0xC bytes, rec_suv.c (DIE 0x25B995) */
struct anon_0_139 {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
};

/* anon_6_139 -- @anon6, 0x8 bytes, rec_suv.c (DIE 0x25C4D5) */
struct anon_6_139 {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

/* anon_1_139 -- @anon1, 0x504 bytes, rec_suv.c (DIE 0x25BA73) */
struct anon_1_139 {   // size 0x504
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
    /* 0x034 */ struct anon_6_139 title_info[80];     // 0x280
    /* 0x2B4 */ struct anon_0_139 xmove[40];          // 0x1E0
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

/* anon_2_139 -- @anon2, 0x48 bytes, rec_suv.c (DIE 0x25BE79) */
struct anon_2_139 {   // size 0x48
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

/* anon_4_139 -- @anon4, 0x4 bytes, rec_suv.c (DIE 0x25C2D7) */
union anon_4_139 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_139 -- @anon3, 0x24 bytes, rec_suv.c (DIE 0x25C143) */
struct anon_3_139 {   // size 0x24
    /* 0x000 */ union anon_4_139 x0;                  // 0x4
    /* 0x004 */ union anon_4_139 y0;                  // 0x4
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

/* anon_5_139 -- @anon5, 0x10 bytes, rec_suv.c (DIE 0x25C334) */
struct anon_5_139 {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
};

/* anon_7_139 -- @anon7, 0x8 bytes, rec_suv.c (DIE 0x25C561) */
struct anon_7_139 {   // size 0x8
    /* 0x000 */ unsigned int time;                    // 0x4
    /* 0x004 */ int stage;                            // 0x4
};


/* variables (2) */
static struct anon_7_139 dummy_data[9];                          /* @0x002BF870 size 0x48 */
struct anon_1_139 *rw;                                           /* @0x002DDFB4 size 0x4 */

/* functions defined (9) */
static void rec_suv_time_disp(float x, float y, int val, unsigned char alpha); /* 0x00259F10-0x0025A23C lines 329-389 */
static void rec_suv_item_disp_sub(float x, float y, unsigned char kind); /* 0x0025A240-0x0025A454 lines 280-320 */
int Rec_Suv_BoolDelete(struct anon_1_139 *rw);                   /* 0x0025A460-0x0025A480 lines 270-272 */
int RCObj_suv_item_disp(void);                                   /* 0x0025A480-0x0025A5B4 lines 224-262 */
int RCObj_suv_item_disap(void *wp);                              /* 0x0025A5C0-0x0025A68C lines 193-221 */
int RCObj_suv_item_apper(void *wp);                              /* 0x0025A690-0x0025A77C lines 162-190 */
void Rec_Suv_Delete(struct anon_1_139 *rw);                      /* 0x0025A780-0x0025A7A0 lines 152-156 */
void Rec_Suv_DetailDisp(void *wp);                               /* 0x0025A7A0-0x0025A970 lines 121-145 */
unsigned char Rec_Suv(struct anon_1_139 *rw);                    /* 0x0025A970-0x0025AB38 lines 48-116 */

#endif /* DDR_UNIT_src_CS_records_rec_suv_c_H */
