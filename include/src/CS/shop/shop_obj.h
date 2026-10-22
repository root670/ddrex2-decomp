/*
 * C:\work2\usaex2\src\CS\shop\shop_obj.c
 * MW MIPS C Compiler, overlay main; 26 functions, code 0x00249910-0x00252530
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_CS_shop_shop_obj_c_H
#define DDR_UNIT_src_CS_shop_shop_obj_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"
#include "types/tex_bind.h"

/* anonymous types (14) */

/* anon_9_125 -- @anon9, 0x4 bytes, shop_obj.c (DIE 0x22161B) */
typedef struct {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
} anon_9_125;

/* anon_5_125 -- @anon5, 0x10 bytes, shop_obj.c (DIE 0x220118) */
typedef struct {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
} anon_5_125;

/* anon_7_125 -- @anon7, 0x10 bytes, shop_obj.c (DIE 0x221254) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_7_125;

/* anon_21_125 -- @anon21, 0x10 bytes, shop_obj.c (DIE 0x2257AD) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_21_125;

/* anon_24_125 -- @anon24, 0x14 bytes, shop_obj.c (DIE 0x225CC2) */
typedef struct {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
} anon_24_125;

/* anon_6_125 -- @anon6, 0x8 bytes, shop_obj.c (DIE 0x220BFE) */
typedef struct {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
} anon_6_125;

/* anon_4_125 -- @anon4, 0x14 bytes, shop_obj.c (DIE 0x21FB3B) */
typedef struct {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
} anon_4_125;

/* anon_0_125 -- @anon0, 0x518 bytes, shop_obj.c (DIE 0x21DE8C) */
typedef struct {   // size 0x518
    /* 0x000 */ unsigned char *free_mem_addr;         // 0x4
    /* 0x004 */ unsigned char *mv_data_addr;          // 0x4
    /* 0x008 */ unsigned char *shop_data_addr;        // 0x4
    /* 0x00C */ unsigned char *course_data_addr;      // 0x4
    /* 0x010 */ unsigned char *mess_data_addr;        // 0x4
    /* 0x014 */ unsigned char step;                   // 0x1
    /* 0x015 */ unsigned char step_s;                 // 0x1
    /* 0x016 */ unsigned char mess_str[512];          // 0x200
    /* 0x216 */ // 0x2 bytes padding
    /* 0x218 */ unsigned int syscnt;                  // 0x4
    /* 0x21C */ unsigned int syscnt0;                 // 0x4
    /* 0x220 */ char tab_cursor;                      // 0x1
    /* 0x221 */ char tab_cursor_new;                  // 0x1
    /* 0x222 */ char contents_cursor;                 // 0x1
    /* 0x223 */ char contents_cursor_new;             // 0x1
    /* 0x224 */ char contents_cursor_disp_top;        // 0x1
    /* 0x225 */ char contents_cursor_disp_top_new;    // 0x1
    /* 0x226 */ char tab_state;                       // 0x1
    /* 0x227 */ char cont_state;                      // 0x1
    /* 0x228 */ char cursor_anime;                    // 0x1
    /* 0x229 */ char cursor_anime_flag;               // 0x1
    /* 0x22A */ char confirm_cursor;                  // 0x1
    /* 0x22B */ char info_cursor;                     // 0x1
    /* 0x22C */ char info_list_disp;                  // 0x1
    /* 0x22D */ unsigned char is_disp_dancer;         // 0x1
    /* 0x22E */ signed char start_pid_first;          // 0x1
    /* 0x22F */ signed char start_pid;                // 0x1
    /* 0x230 */ unsigned int secret_list_num;         // 0x4
    /* 0x234 */ anon_9_125 secret_list[50];           // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ anon_5_125 text_w;                    // 0x10
    /* 0x310 */ anon_7_125 button_disp_w;             // 0x10
    /* 0x320 */ anon_21_125 fade_env;                 // 0x10
    /* 0x330 */ anon_24_125 pad_w;                    // 0x14
    /* 0x344 */ anon_6_125 mess_w;                    // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ anon_4_125 move_w[9];                 // 0xB4
    /* 0x510 */ anon_b14b78a0b5d3 shop_rect;          // 0x8
} anon_0_125;

/* anon_2_125 -- @anon2, 0x24 bytes, shop_obj.c (DIE 0x21E8B9) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
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
} anon_2_125;

/* anon_10_125 -- @anon10, 0x48 bytes, shop_obj.c (DIE 0x221682) */
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
} anon_10_125;

/* anon_12_125 -- @anon12, 0x1C bytes, shop_obj.c (DIE 0x222187) */
typedef struct {   // size 0x1C
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ unsigned char r0;                     // 0x1
    /* 0x015 */ unsigned char g0;                     // 0x1
    /* 0x016 */ unsigned char b0;                     // 0x1
    /* 0x017 */ unsigned char a0;                     // 0x1
    /* 0x018 */ int flg;                              // 0x4
} anon_12_125;

/* anon_13_125 -- @anon13, 0x24 bytes, shop_obj.c (DIE 0x2240B7) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
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
} anon_13_125;

/* anon_16_125 -- @anon16, 0x30 bytes, shop_obj.c (DIE 0x224B39) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
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
} anon_16_125;

/* anon_20_125 -- @anon20, 0x68 bytes, shop_obj.c (DIE 0x2253D5) */
typedef struct {   // size 0x68
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ anon_d075beaabcd0 x1;                 // 0x4
    /* 0x00C */ anon_d075beaabcd0 y1;                 // 0x4
    /* 0x010 */ anon_d075beaabcd0 x2;                 // 0x4
    /* 0x014 */ anon_d075beaabcd0 y2;                 // 0x4
    /* 0x018 */ anon_d075beaabcd0 x3;                 // 0x4
    /* 0x01C */ anon_d075beaabcd0 y3;                 // 0x4
    /* 0x020 */ unsigned int z0;                      // 0x4
    /* 0x024 */ unsigned int z1;                      // 0x4
    /* 0x028 */ unsigned int z2;                      // 0x4
    /* 0x02C */ unsigned int z3;                      // 0x4
    /* 0x030 */ float s0;                             // 0x4
    /* 0x034 */ float t0;                             // 0x4
    /* 0x038 */ float q0;                             // 0x4
    /* 0x03C */ float s1;                             // 0x4
    /* 0x040 */ float t1;                             // 0x4
    /* 0x044 */ float q1;                             // 0x4
    /* 0x048 */ float s2;                             // 0x4
    /* 0x04C */ float t2;                             // 0x4
    /* 0x050 */ float q2;                             // 0x4
    /* 0x054 */ float s3;                             // 0x4
    /* 0x058 */ float t3;                             // 0x4
    /* 0x05C */ float q3;                             // 0x4
    /* 0x060 */ unsigned char r0;                     // 0x1
    /* 0x061 */ unsigned char g0;                     // 0x1
    /* 0x062 */ unsigned char b0;                     // 0x1
    /* 0x063 */ unsigned char a0;                     // 0x1
    /* 0x064 */ int flg;                              // 0x4
} anon_20_125;


/* variables (11) */
unsigned char *shp_str_hint;                                     /* @0x002DDD2C size 0x4 */
unsigned char *shp_str_ea_hint;                                  /* @0x002DDD30 size 0x4 */
unsigned char *shp_str_hint_exp;                                 /* @0x002DDD34 size 0x4 */
unsigned char *shp_str_ea_hint_exp;                              /* @0x002DDD38 size 0x4 */
unsigned char *shp_str_arrow;                                    /* @0x002DDD3C size 0x4 */
unsigned char *shp_str_arrow_exp;                                /* @0x002DDD40 size 0x4 */
unsigned char *shp_str_branch;                                   /* @0x002DDD44 size 0x4 */
unsigned char *shp_str_advanced[3];                              /* @0x002BF2B8 size 0xC */
unsigned char *shp_str_branch_exp;                               /* @0x002DDD48 size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions defined (26) */
void shop_select_info_disp_course_list(anon_0_125 *work, int x0, int y0, int z0); /* 0x00249910-0x00249CFC lines 3227-3291 */
void shop_select_info_disp_course(anon_0_125 *work, struct _CWS_WIN_W *winp, int x0, int y0); /* 0x00249D00-0x00249EC8 lines 3153-3218 */
void shop_select_info_disp_music(struct _CWS_WIN_W *winp, int x0, int y0); /* 0x00249ED0-0x0024A0BC lines 3058-3145 */
static void shop_select_info_disp_button(int x0, int y0, int z0, int br, int a); /* 0x0024A0C0-0x0024A308 lines 2992-3052 */
static void shop_select_info_disp_th(int x, int y, int z);       /* 0x0024A310-0x0024A4DC lines 2948-2987 */
void shop_disp_my_point(anon_0_125 *work);                       /* 0x0024A4E0-0x0024A87C lines 2837-2937 */
static void shop_disp_contents_explain_other(int secret_no, int x0, int y0, int ofsx, int width, int height, int alpha); /* 0x0024A880-0x0024AAA4 lines 2794-2824 */
static void shop_disp_contents_other(anon_0_125 *work);          /* 0x0024AAB0-0x0024B980 lines 2518-2790 */
static void shop_disp_contents_explain_custom(int secret_no, int x0, int y0, int ofsx, int width, int height, int alpha); /* 0x0024B980-0x0024BBE4 lines 2467-2495 */
static void shop_disp_contents_custom(anon_0_125 *work);         /* 0x0024BBF0-0x0024C9C0 lines 2198-2463 */
static void shop_disp_contents_info(anon_0_125 *work);           /* 0x0024C9C0-0x0024D7F0 lines 1891-2163 */
static void shop_disp_contents_explain_outfit(int chara_no, int x, int y, int ofsx); /* 0x0024D7F0-0x0024D9D8 lines 1854-1871 */
static void shop_disp_contents_outfit(anon_0_125 *work);         /* 0x0024D9E0-0x0024E778 lines 1578-1850 */
static void shop_disp_contents_explain_course(int course_num, int x, int y, int ofsy); /* 0x0024E780-0x0024E9D0 lines 1511-1563 */
static void shop_disp_contents_course(anon_0_125 *work);         /* 0x0024E9D0-0x0024F778 lines 1235-1507 */
static void shop_disp_contents_explain_music(int secret_no, int dance_num, int x, int y, int ofsx, int ofsy); /* 0x0024F780-0x0024FA8C lines 1168-1227 */
static void shop_disp_contents_music(anon_0_125 *work);          /* 0x0024FA90-0x00250A20 lines 868-1163 */
static void shop_disp_contents_explain_frame(int x, int y, int width, int height); /* 0x00250A20-0x00250F3C lines 765-834 */
static void shop_disp_point(int secret_no, int x, int y, int rr, int gg, int bb); /* 0x00250F40-0x002510D0 lines 727-755 */
void shop_disp_cursor(anon_0_125 *work, int x, int y, int pri, int anime_on); /* 0x002510D0-0x00251250 lines 695-721 */
void shop_disp_contents(anon_0_125 *work);                       /* 0x00251250-0x002512E4 lines 647-670 */
void shop_disp_common_scroll_bar(int x0, int y0, int z0, int height, int disp_pos, int list_num, int disp_num); /* 0x002512F0-0x002515F8 lines 563-615 */
void shop_disp_scroll_bar(anon_0_125 *work);                     /* 0x00251600-0x00251AB8 lines 427-560 */
void shop_disp_contents_frame(anon_0_125 *work);                 /* 0x00251AC0-0x00251D90 lines 312-416 */
void shop_disp_tab(anon_0_125 *work);                            /* 0x00251D90-0x002521B4 lines 200-302 */
void shop_disp_title(anon_0_125 *work);                          /* 0x002521C0-0x00252530 lines 88-185 */

#endif /* DDR_UNIT_src_CS_shop_shop_obj_c_H */
