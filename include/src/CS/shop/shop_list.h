/*
 * C:\work2\usaex2\src\CS\shop\shop_list.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x00248A80-0x002496AC
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
#ifndef DDR_UNIT_src_CS_shop_shop_list_c_H
#define DDR_UNIT_src_CS_shop_shop_list_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/music_info.h"
#include "types/oni_course.h"

/* anonymous types (9) */

/* anon_0_123 -- @anon0, 0x8 bytes, shop_list.c (DIE 0x21482E) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_0_123;

/* anon_4_123 -- @anon4, 0x4 bytes, shop_list.c (DIE 0x215C18) */
typedef struct {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
} anon_4_123;

/* anon_5_123 -- @anon5, 0x10 bytes, shop_list.c (DIE 0x21611A) */
typedef struct {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
} anon_5_123;

/* anon_7_123 -- @anon7, 0x10 bytes, shop_list.c (DIE 0x216AC3) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_7_123;

/* anon_11_123 -- @anon11, 0x10 bytes, shop_list.c (DIE 0x21800E) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_11_123;

/* anon_13_123 -- @anon13, 0x14 bytes, shop_list.c (DIE 0x218354) */
typedef struct {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
} anon_13_123;

/* anon_6_123 -- @anon6, 0x8 bytes, shop_list.c (DIE 0x216A3E) */
typedef struct {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
} anon_6_123;

/* anon_3_123 -- @anon3, 0x14 bytes, shop_list.c (DIE 0x215B58) */
typedef struct {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
} anon_3_123;

/* anon_1_123 -- @anon1, 0x518 bytes, shop_list.c (DIE 0x21497D) */
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
    /* 0x234 */ anon_4_123 secret_list[50];           // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ anon_5_123 text_w;                    // 0x10
    /* 0x310 */ anon_7_123 button_disp_w;             // 0x10
    /* 0x320 */ anon_11_123 fade_env;                 // 0x10
    /* 0x330 */ anon_13_123 pad_w;                    // 0x14
    /* 0x344 */ anon_6_123 mess_w;                    // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ anon_3_123 move_w[9];                 // 0xB4
    /* 0x510 */ anon_0_123 shop_rect;                 // 0x8
} anon_1_123;


/* variables (1) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (7) */
static void shop_make_contents_list_other(anon_1_123 *work);     /* 0x00248A80-0x00248C40 lines 389-442 */
static void shop_make_contents_list_custom(anon_1_123 *work);    /* 0x00248C40-0x00248DE8 lines 323-379 */
static void shop_make_contents_list_info(anon_1_123 *work);      /* 0x00248DF0-0x00248FB0 lines 261-314 */
static void shop_make_contents_list_outfit(anon_1_123 *work);    /* 0x00248FB0-0x00249128 lines 211-252 */
static void shop_make_contents_list_course(anon_1_123 *work);    /* 0x00249130-0x00249380 lines 128-199 */
static void shop_make_contents_list_music(anon_1_123 *work);     /* 0x00249380-0x00249604 lines 53-124 */
void shop_make_contents_list(anon_1_123 *work);                  /* 0x00249610-0x002496AC lines 24-49 */

#endif /* DDR_UNIT_src_CS_shop_shop_list_c_H */
