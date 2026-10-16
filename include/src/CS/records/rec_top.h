/*
 * C:\work2\usaex2\src\CS\records\rec_top.c
 * MW MIPS C Compiler, overlay rec_rel4cd.prg; 15 functions, code 0x007F3ED0-0x007F5130
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_rec_top_c_H
#define DDR_UNIT_src_CS_records_rec_top_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/tex_bind.h"

/* anonymous types (10) */

/* anon_0_244 -- @anon0, 0x10 bytes, rec_top.c (DIE 0x47A4A0) */
struct anon_0_244 {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
};

/* anon_1_244 -- @anon1, 0x48 bytes, rec_top.c (DIE 0x47A727) */
struct anon_1_244 {   // size 0x48
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

/* anon_5_244 -- @anon5, 0x4 bytes, rec_top.c (DIE 0x47B031) */
union anon_5_244 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_2_244 -- @anon2, 0x24 bytes, rec_top.c (DIE 0x47A9CF) */
struct anon_2_244 {   // size 0x24
    /* 0x000 */ union anon_5_244 x0;                  // 0x4
    /* 0x004 */ union anon_5_244 y0;                  // 0x4
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

/* anon_3_244 -- @anon3, 0x10 bytes, rec_top.c (DIE 0x47AB63) */
struct anon_3_244 {   // size 0x10
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ int exp;                              // 0x4
    /* 0x008 */ float bu_cx;                          // 0x4
    /* 0x00C */ float ex_x;                           // 0x4
};

/* anon_9_244 -- @anon9, 0x8 bytes, rec_top.c (DIE 0x47B4FC) */
struct anon_9_244 {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

/* anon_7_244 -- @anon7, 0xC bytes, rec_top.c (DIE 0x47B283) */
struct anon_7_244 {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
};

/* anon_4_244 -- @anon4, 0x504 bytes, rec_top.c (DIE 0x47AC05) */
struct anon_4_244 {   // size 0x504
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
    /* 0x034 */ struct anon_9_244 title_info[80];     // 0x280
    /* 0x2B4 */ struct anon_7_244 xmove[40];          // 0x1E0
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

/* anon_6_244 -- @anon6, 0x30 bytes, rec_top.c (DIE 0x47B08E) */
struct anon_6_244 {   // size 0x30
    /* 0x000 */ union anon_5_244 x0;                  // 0x4
    /* 0x004 */ union anon_5_244 y0;                  // 0x4
    /* 0x008 */ union anon_5_244 x1;                  // 0x4
    /* 0x00C */ union anon_5_244 y1;                  // 0x4
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

/* anon_8_244 -- @anon8, 0x8 bytes, rec_top.c (DIE 0x47B3D4) */
struct anon_8_244 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* variables (5) */
static int rec_cap_str[7];                                       /* @0x007FC080 size 0x1C */
static struct anon_3_244 top_btn_info[4];                        /* @0x007FC0A0 size 0x40 */
struct anon_4_244 *rw;                                           /* @0x002DDFB4 size 0x4 */
int old_cur;                                                     /* @0x002DE6D4 size 0x4 */
struct tex_bind tex_bind[375];                                   /* @0x0058C390 size 0x2904 */

/* functions defined (15) */
int RCObj_top_btn_disp(void *wp);                                /* 0x007F3ED0-0x007F3FF8 lines 557-576 */
int RCObj_top_exp_disp(void *wp);                                /* 0x007F4000-0x007F41E0 lines 488-531 */
int RCObj_top_exp_disap(void *wp);                               /* 0x007F41E0-0x007F42C4 lines 464-485 */
int RCObj_top_exp_exec(void *wp);                                /* 0x007F42D0-0x007F43EC lines 430-461 */
int RCObj_top_exp_apper(void *wp);                               /* 0x007F43F0-0x007F4464 lines 415-427 */
int RCObj_label_disap(void *wp);                                 /* 0x007F4470-0x007F4518 lines 381-400 */
int RCObj_label_apper(void *wp);                                 /* 0x007F4520-0x007F45C8 lines 364-378 */
int RCObj_base_disp(void);                                       /* 0x007F45D0-0x007F48B8 lines 307-358 */
int RCObj_base_disap(void *wp);                                  /* 0x007F48C0-0x007F499C lines 285-305 */
int RCObj_base_apper(void *wp);                                  /* 0x007F49A0-0x007F4A20 lines 270-282 */
int RCObj_top_item_disp(void *wp);                               /* 0x007F4A20-0x007F4CBC lines 202-262 */
int RCObj_top_item_disap(void *wp);                              /* 0x007F4CC0-0x007F4DE0 lines 166-199 */
int RCObj_top_item_exec(void *wp);                               /* 0x007F4DE0-0x007F4E28 lines 159-163 */
int RCObj_top_item_apper(void *wp);                              /* 0x007F4E30-0x007F4FC0 lines 115-153 */
unsigned char Rec_Top(struct anon_4_244 *rw);                    /* 0x007F4FC0-0x007F5130 lines 48-100 */

#endif /* DDR_UNIT_src_CS_records_rec_top_c_H */
