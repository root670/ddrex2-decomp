/*
 * C:\work2\usaex2\src\CS\records\rec_co.c
 * MW MIPS C Compiler, overlay rec_rel4cd.prg; 28 functions, code 0x007F0F60-0x007F3ECC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_records_rec_co_c_H
#define DDR_UNIT_src_CS_records_rec_co_c_H

#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_CWS_WIN_W.h"
#include "types/_tag_cCoCursor01.h"
#include "types/tex_bind.h"

/* anonymous types (16) */

/* anon_9_243 -- @anon9, 0x4 bytes, rec_co.c (DIE 0x476127) */
union anon_9_243 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_243 -- @anon0, 0x34 bytes, rec_co.c (DIE 0x474827) */
struct anon_0_243 {   // size 0x34
    /* 0x000 */ union anon_9_243 x0;                  // 0x4
    /* 0x004 */ union anon_9_243 y0;                  // 0x4
    /* 0x008 */ union anon_9_243 x1;                  // 0x4
    /* 0x00C */ union anon_9_243 y1;                  // 0x4
    /* 0x010 */ union anon_9_243 x2;                  // 0x4
    /* 0x014 */ union anon_9_243 y2;                  // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
};

/* anon_1_243 -- @anon1, 0x48 bytes, rec_co.c (DIE 0x474CFD) */
struct anon_1_243 {   // size 0x48
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

/* anon_2_243 -- @anon2, 0x8 bytes, rec_co.c (DIE 0x474F7F) */
struct anon_2_243 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_3_243 -- @anon3, 0x10 bytes, rec_co.c (DIE 0x47516E) */
struct anon_3_243 {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
};

/* anon_4_243 -- @anon4, 0x1C bytes, rec_co.c (DIE 0x47563C) */
struct anon_4_243 {   // size 0x1C
    /* 0x000 */ union anon_9_243 x0;                  // 0x4
    /* 0x004 */ union anon_9_243 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
};

/* anon_5_243 -- @anon5, 0x4 bytes, rec_co.c (DIE 0x47597D) */
struct anon_5_243 {   // size 0x4
    /* 0x000 */ struct _CWS_WIN_W *win;               // 0x4
};

/* anon_6_243 -- @anon6, 0x24 bytes, rec_co.c (DIE 0x475A82) */
struct anon_6_243 {   // size 0x24
    /* 0x000 */ union anon_9_243 x0;                  // 0x4
    /* 0x004 */ union anon_9_243 y0;                  // 0x4
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

/* anon_15_243 -- @anon15, 0x8 bytes, rec_co.c (DIE 0x476F2B) */
struct anon_15_243 {   // size 0x8
    /* 0x000 */ unsigned int address;                 // 0x4
    /* 0x004 */ unsigned short link_num;              // 0x2
    /* 0x006 */ unsigned short tex_num;               // 0x2
};

/* anon_11_243 -- @anon11, 0xC bytes, rec_co.c (DIE 0x476833) */
struct anon_11_243 {   // size 0xC
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char mode;                   // 0x1
    /* 0x002 */ unsigned char call;                   // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ float x;                              // 0x4
};

/* anon_7_243 -- @anon7, 0x504 bytes, rec_co.c (DIE 0x475C16) */
struct anon_7_243 {   // size 0x504
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
    /* 0x034 */ struct anon_15_243 title_info[80];    // 0x280
    /* 0x2B4 */ struct anon_11_243 xmove[40];         // 0x1E0
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

/* anon_8_243 -- @anon8, 0x4 bytes, rec_co.c (DIE 0x476066) */
struct anon_8_243 {   // size 0x4
    /* 0x000 */ unsigned char r;                      // 0x1
    /* 0x001 */ unsigned char g;                      // 0x1
    /* 0x002 */ unsigned char b;                      // 0x1
    /* 0x003 */ unsigned char cd;                     // 0x1
};

/* anon_10_243 -- @anon10, 0x30 bytes, rec_co.c (DIE 0x4763EB) */
struct anon_10_243 {   // size 0x30
    /* 0x000 */ union anon_9_243 x0;                  // 0x4
    /* 0x004 */ union anon_9_243 y0;                  // 0x4
    /* 0x008 */ union anon_9_243 x1;                  // 0x4
    /* 0x00C */ union anon_9_243 y1;                  // 0x4
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

/* anon_12_243 -- @anon12, 0x10 bytes, rec_co.c (DIE 0x476936) */
struct anon_12_243 {   // size 0x10
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ int exp;                              // 0x4
    /* 0x008 */ float bu_cx;                          // 0x4
    /* 0x00C */ float ex_x;                           // 0x4
};

/* anon_13_243 -- @anon13, 0x20 bytes, rec_co.c (DIE 0x476A6E) */
struct anon_13_243 {   // size 0x20
    /* 0x000 */ union anon_9_243 x0;                  // 0x4
    /* 0x004 */ union anon_9_243 y0;                  // 0x4
    /* 0x008 */ union anon_9_243 x1;                  // 0x4
    /* 0x00C */ union anon_9_243 y1;                  // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ int flg;                              // 0x4
};

/* anon_14_243 -- @anon14, 0x24 bytes, rec_co.c (DIE 0x476C34) */
struct anon_14_243 {   // size 0x24
    /* 0x000 */ union anon_9_243 x0;                  // 0x4
    /* 0x004 */ union anon_9_243 y0;                  // 0x4
    /* 0x008 */ union anon_9_243 x1;                  // 0x4
    /* 0x00C */ union anon_9_243 y1;                  // 0x4
    /* 0x010 */ unsigned int z0;                      // 0x4
    /* 0x014 */ unsigned int z1;                      // 0x4
    /* 0x018 */ unsigned char r0;                     // 0x1
    /* 0x019 */ unsigned char g0;                     // 0x1
    /* 0x01A */ unsigned char b0;                     // 0x1
    /* 0x01B */ unsigned char a0;                     // 0x1
    /* 0x01C */ unsigned char r1;                     // 0x1
    /* 0x01D */ unsigned char g1;                     // 0x1
    /* 0x01E */ unsigned char b1;                     // 0x1
    /* 0x01F */ unsigned char a1;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
};


/* variables (12) */
static void (*rec_detail_disp_func[7])(void *);                  /* @0x007FBE30 size 0x1C */
static void (*rec_delete_func[7])(struct anon_7_243 *);          /* @0x007FBE50 size 0x1C */
static int (*rec_bool_del[7])(struct anon_7_243 *);              /* @0x007FBE70 size 0x1C */
static float hi_del_win_y[5];                                    /* @0x007FBE90 size 0x14 */
static float end_del_win_y[6];                                   /* @0x007FBEB0 size 0x18 */
static float suv_del_win_y[9];                                   /* @0x007FBED0 size 0x24 */
static float *del_win_y[7];                                      /* @0x007FBF00 size 0x1C */
static struct anon_12_243 hi_btn_info[4];                        /* @0x007FBF20 size 0x40 */
static struct anon_12_243 nhi_btn_info[3];                       /* @0x007FBF60 size 0x30 */
struct anon_7_243 *rw;                                           /* @0x002DDFB4 size 0x4 */
struct tex_bind tex_bind[375];                                   /* @0x0058C390 size 0x2904 */
struct _tag_cCoCursor01 rc_del_cur_w;                            /* @0x007FC908 size 0xC */

/* functions defined (28) */
void rec_star_disp(float x, float y, int pri, unsigned char kind, unsigned char bri, unsigned char alpha); /* 0x007F0F60-0x007F10E4 lines 1359-1389 */
static void rec_cursor_disp(float cx, float cy, unsigned char mode, unsigned char bri); /* 0x007F10F0-0x007F1448 lines 1287-1349 */
int RCObj_erase_disp(void *wp);                                  /* 0x007F1450-0x007F1614 lines 1212-1275 */
int RCObj_erase_func(void *wp);                                  /* 0x007F1620-0x007F1A10 lines 1067-1209 */
int RCObj_btn_disp(void *wp);                                    /* 0x007F1A10-0x007F1BEC lines 982-1056 */
int RCObj_btn_disap(void *wp);                                   /* 0x007F1BF0-0x007F1C44 lines 973-979 */
int RCObj_btn_apper(void *wp);                                   /* 0x007F1C50-0x007F1CAC lines 964-970 */
int RCObj_scr_bar_disp(void *wp);                                /* 0x007F1CB0-0x007F1F94 lines 901-957 */
int RCObj_scr_bar_disap(void *wp);                               /* 0x007F1FA0-0x007F1FF4 lines 890-898 */
int RCObj_scr_bar_apper(void *wp);                               /* 0x007F2000-0x007F205C lines 879-887 */
int RCObj_detail_disp(void *wp);                                 /* 0x007F2060-0x007F20BC lines 858-868 */
int RCObj_detail_disap(void *wp);                                /* 0x007F20C0-0x007F2114 lines 847-854 */
int RCObj_detail_apper(void *wp);                                /* 0x007F2120-0x007F217C lines 837-844 */
int RCObj_cur_disp(void *wp);                                    /* 0x007F2180-0x007F26D4 lines 754-831 */
int RCObj_cur_exec(void *wp);                                    /* 0x007F26E0-0x007F272C lines 728-751 */
int RCObj_win_disp(void);                                        /* 0x007F2730-0x007F2738 lines 722-722 */
int RCObj_win_func(void *w);                                     /* 0x007F2740-0x007F2870 lines 680-715 */
int RCObj_fade(struct anon_3_243 *w, float time, int kind);      /* 0x007F2870-0x007F2978 lines 633-651 */
void RCObj_fadeset(struct anon_3_243 *w, float wait, int kind);  /* 0x007F2980-0x007F29BC lines 622-629 */
void Rec_PutZBuffBoard(float y, float h);                        /* 0x007F29C0-0x007F2A80 lines 594-612 */
void Rec_obj_board_disp(float x, float len);                     /* 0x007F2A80-0x007F2CA0 lines 545-584 */
void Rec_line_disp(float x, float y, float w);                   /* 0x007F2CA0-0x007F2D24 lines 484-495 */
void Rec_Board_Disp(struct anon_2_243 r, int pri_add, unsigned char flag); /* 0x007F2D30-0x007F2F78 lines 442-477 */
void Rec_DetailItemDisp(float cx, float cy, unsigned char kind, unsigned char bri, unsigned char alpha, unsigned char flag); /* 0x007F2F80-0x007F3158 lines 400-434 */
void Rec_DanceLevelDisp(float x, float y, unsigned char level, int pri, unsigned char flag, unsigned char alpha, unsigned char bri); /* 0x007F3160-0x007F34D0 lines 307-390 */
void Rec_res_slash_disp(float x0, float y0, int pri, unsigned char type, unsigned char alpha, unsigned char bri); /* 0x007F34D0-0x007F3618 lines 277-295 */
void Rec_res_time_disp(float x, float y, int val, unsigned char bri, int pri, unsigned char alpha); /* 0x007F3620-0x007F393C lines 205-265 */
void Rec_res_digit_disp(float x0, float y0, int val, int pri, unsigned char keta, unsigned char type, unsigned char alpha, unsigned char bri, unsigned char flag); /* 0x007F3940-0x007F3ECC lines 116-199 */

#endif /* DDR_UNIT_src_CS_records_rec_co_c_H */
