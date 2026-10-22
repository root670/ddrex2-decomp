/*
 * C:\work2\usaex2\src\CS\shop\shop_func.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x00253AE0-0x0025427C
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
#ifndef DDR_UNIT_src_CS_shop_shop_func_c_H
#define DDR_UNIT_src_CS_shop_shop_func_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (9) */

/* anon_0_128 -- @anon0, 0x8 bytes, shop_func.c (DIE 0x237602) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_0_128;

/* anon_7_128 -- @anon7, 0x4 bytes, shop_func.c (DIE 0x239936) */
typedef struct {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
} anon_7_128;

/* anon_4_128 -- @anon4, 0x10 bytes, shop_func.c (DIE 0x238E87) */
typedef struct {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
} anon_4_128;

/* anon_6_128 -- @anon6, 0x10 bytes, shop_func.c (DIE 0x239830) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_6_128;

/* anon_11_128 -- @anon11, 0x10 bytes, shop_func.c (DIE 0x23AA44) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_11_128;

/* anon_13_128 -- @anon13, 0x14 bytes, shop_func.c (DIE 0x23AD66) */
typedef struct {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
} anon_13_128;

/* anon_5_128 -- @anon5, 0x8 bytes, shop_func.c (DIE 0x2397AB) */
typedef struct {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
} anon_5_128;

/* anon_3_128 -- @anon3, 0x14 bytes, shop_func.c (DIE 0x23892C) */
typedef struct {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
} anon_3_128;

/* anon_1_128 -- @anon1, 0x518 bytes, shop_func.c (DIE 0x237707) */
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
    /* 0x234 */ anon_7_128 secret_list[50];           // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ anon_4_128 text_w;                    // 0x10
    /* 0x310 */ anon_6_128 button_disp_w;             // 0x10
    /* 0x320 */ anon_11_128 fade_env;                 // 0x10
    /* 0x330 */ anon_13_128 pad_w;                    // 0x14
    /* 0x344 */ anon_5_128 mess_w;                    // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ anon_3_128 move_w[9];                 // 0xB4
    /* 0x510 */ anon_0_128 shop_rect;                 // 0x8
} anon_1_128;


/* variables (1) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */

/* functions defined (19) */
void shop_bgm_set(unsigned int call);                            /* 0x00253AE0-0x00253B08 lines 511-514 */
void shop_bgm_call(void);                                        /* 0x00253B10-0x00253B70 lines 496-507 */
void shop_bgm_init(void);                                        /* 0x00253B70-0x00253B98 lines 484-490 */
void shop_multi_win_destroy(anon_1_128 *work);                   /* 0x00253BA0-0x00253BE8 lines 450-458 */
void shop_multi_win_init(anon_1_128 *work);                      /* 0x00253BF0-0x00253C5C lines 408-441 */
void shop_bind_nm(void);                                         /* 0x00253C60-0x00253D20 lines 350-386 */
void shop_bind_tex(void);                                        /* 0x00253D20-0x00253E70 lines 282-323 */
int shop_wait_obj_move(anon_1_128 *work, int obj_kind);          /* 0x00253E70-0x00253EA8 lines 250-255 */
int shop_get_obj_frame(anon_1_128 *work, int obj_kind);          /* 0x00253EB0-0x00253EC8 lines 244-245 */
int shop_get_obj_count(anon_1_128 *work, int obj_kind);          /* 0x00253ED0-0x00253EF0 lines 238-239 */
void shop_set_obj_move(anon_1_128 *work, int obj_kind, int type, int frame); /* 0x00253EF0-0x00253F14 lines 229-233 */
int shop_init_obj_move_work(anon_1_128 *work);                   /* 0x00253F20-0x00253F84 lines 212-219 */
int shop_get_secret_value(anon_1_128 *work, int list_no);        /* 0x00253F90-0x00253FA0 lines 151-152 */
int shop_get_secret_no(anon_1_128 *work, int list_no);           /* 0x00253FA0-0x00253FB0 lines 137-138 */
int shop_get_disp_num(anon_1_128 *work);                         /* 0x00253FB0-0x00254018 lines 103-124 */
int shop_get_contents_num(anon_1_128 *work);                     /* 0x00254020-0x00254028 lines 98-98 */
void shop_purchase(anon_1_128 *work);                            /* 0x00254030-0x00254134 lines 60-74 */
int shop_is_purchasable2(anon_1_128 *work, int list_no);         /* 0x00254140-0x002541DC lines 42-52 */
int shop_is_purchasable(anon_1_128 *work);                       /* 0x002541E0-0x0025427C lines 29-39 */

#endif /* DDR_UNIT_src_CS_shop_shop_func_c_H */
