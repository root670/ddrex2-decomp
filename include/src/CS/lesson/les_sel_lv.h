/*
 * C:\work2\usaex2\src\CS\lesson\les_sel_lv.c
 * MW MIPS C Compiler, overlay les_rel4cd.prg; 11 functions, code 0x007F63F0-0x007F811C
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
#ifndef DDR_UNIT_src_CS_lesson_les_sel_lv_c_H
#define DDR_UNIT_src_CS_lesson_les_sel_lv_c_H

#include "types/_LES_RECT.h"
#include "types/_tag_cLes.h"
#include "types/_tag_cLesSelLevel.h"
#include "types/_tag_cLesSelLevelCursor.h"
#include "types/g_game_w.h"

/* anonymous types (6) */

/* anon_0_198 -- @anon0, 0x48 bytes, les_sel_lv.c (DIE 0x37CEEC) */
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
} anon_0_198;

/* anon_2_198 -- @anon2, 0x30 bytes, les_sel_lv.c (DIE 0x37D6BB) */
typedef struct {   // size 0x30
    /* 0x000 */ int t;                                // 0x4
    /* 0x004 */ int t_max;                            // 0x4
    /* 0x008 */ float x;                              // 0x4
    /* 0x00C */ float y;                              // 0x4
    /* 0x010 */ float sx;                             // 0x4
    /* 0x014 */ float sy;                             // 0x4
    /* 0x018 */ float fx;                             // 0x4
    /* 0x01C */ float fy;                             // 0x4
    /* 0x020 */ float ofs_x;                          // 0x4
    /* 0x024 */ float ofs_y;                          // 0x4
    /* 0x028 */ unsigned char alpha;                  // 0x1
    /* 0x029 */ unsigned char salpha;                 // 0x1
    /* 0x02A */ unsigned char Mode;                   // 0x1
    /* 0x02B */ unsigned char step;                   // 0x1
    /* 0x02C */ unsigned char flag;                   // 0x1
    /* 0x02D */ unsigned char ob_alpha;               // 0x1
    /* 0x02E */ // 0x2 bytes padding
} anon_2_198;

/* anon_5_198 -- @anon5, 0x30 bytes, les_sel_lv.c (DIE 0x37E52B) */
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
} anon_5_198;

/* anon_9_198 -- @anon9, 0x18 bytes, les_sel_lv.c (DIE 0x380E0A) */
typedef struct {   // size 0x18
    /* 0x000 */ int btn;                              // 0x4
    /* 0x004 */ float btn_cx;                         // 0x4
    /* 0x008 */ float btn_cy;                         // 0x4
    /* 0x00C */ int ex;                               // 0x4
    /* 0x010 */ float ex_x;                           // 0x4
    /* 0x014 */ float ex_cy;                          // 0x4
} anon_9_198;

/* anon_8_198 -- @anon8, 0x18 bytes, les_sel_lv.c (DIE 0x380AC4) */
typedef struct {   // size 0x18
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char fp_step;                // 0x1
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ float dx;                             // 0x4
    /* 0x008 */ float dy;                             // 0x4
    /* 0x00C */ float t;                              // 0x4
    /* 0x010 */ anon_9_198 *info[2];                  // 0x8
} anon_8_198;

/* anon_11_198 -- @anon11, 0x10 bytes, les_sel_lv.c (DIE 0x3811FC) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_11_198;


/* variables (11) */
struct _tag_cLesSelLevel *pLesSelLevel;                          /* @0x002DDE88 size 0x4 */
static short anime_offset[18];                                   /* not allocated size 0x24 */
static int cur_y_table[3];                                       /* @0x007FA7D8 size 0xC */
anon_11_198 les_lv_objf;                                         /* @0x007FA7F0 size 0x10 */
anon_11_198 lesson_button_objf[1];                               /* @0x007FA800 size 0x10 */
static anon_9_198 lesson_btn_info[4];                            /* @0x007FA8B0 size 0x60 */
struct _tag_cLes *pLes;                                          /* @0x002DDE80 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
static struct _tag_cLesSelLevel _pLesSelLevel;                   /* @0x007FE950 size 0xC0 */
static short font_anime_pos_y;                                   /* not allocated size 0x2 */
static short font_anime_pos_x;                                   /* not allocated size 0x2 */

/* functions defined (11) */
static int fp_btn_disp(void *w);                                 /* 0x007F63F0-0x007F6550 lines 1275-1339 */
static int fp_btn_move(void *w);                                 /* 0x007F6550-0x007F6648 lines 1241-1273 */
static int les_lv_item_disp(void *w);                            /* 0x007F6650-0x007F6E74 lines 1072-1214 */
static int les_lv_item_disap(void *w);                           /* 0x007F6E80-0x007F70D8 lines 1010-1069 */
static int les_lv_item_exec(void *w);                            /* 0x007F70E0-0x007F76D4 lines 840-1007 */
static int les_lv_item_apper(void *w);                           /* 0x007F76E0-0x007F7AB0 lines 755-837 */
static void init_cur(void);                                      /* 0x007F7AB0-0x007F7BC0 lines 517-546 */
int Update_LesSelLevel(void);                                    /* 0x007F7BC0-0x007F7CF0 lines 448-467 */
int View_LesSelLevel(void);                                      /* 0x007F7CF0-0x007F7CF8 lines 446-446 */
int Control_LesSelLevel(void);                                   /* 0x007F7D00-0x007F8080 lines 235-382 */
int Init_LesSelLevel(void);                                      /* 0x007F8080-0x007F811C lines 131-232 */

#endif /* DDR_UNIT_src_CS_lesson_les_sel_lv_c_H */
