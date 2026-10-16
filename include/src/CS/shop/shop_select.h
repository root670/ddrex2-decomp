/*
 * C:\work2\usaex2\src\CS\shop\shop_select.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00252530-0x002533E4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_shop_shop_select_c_H
#define DDR_UNIT_src_CS_shop_shop_select_c_H

#include "types/_CWS_WIN_W.h"

/* anonymous types (9) */

/* anon_8_126 -- @anon8, 0x4 bytes, shop_select.c (DIE 0x22CFF5) */
struct anon_8_126 {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
};

/* anon_5_126 -- @anon5, 0x10 bytes, shop_select.c (DIE 0x22CBC1) */
struct anon_5_126 {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
};

/* anon_7_126 -- @anon7, 0x10 bytes, shop_select.c (DIE 0x22CF32) */
struct anon_7_126 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
};

/* anon_2_126 -- @anon2, 0x10 bytes, shop_select.c (DIE 0x22C56C) */
struct anon_2_126 {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
};

/* anon_1_126 -- @anon1, 0x14 bytes, shop_select.c (DIE 0x22C271) */
struct anon_1_126 {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
};

/* anon_6_126 -- @anon6, 0x8 bytes, shop_select.c (DIE 0x22CED3) */
struct anon_6_126 {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
};

/* anon_4_126 -- @anon4, 0x14 bytes, shop_select.c (DIE 0x22C9AD) */
struct anon_4_126 {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
};

/* anon_3_126 -- @anon3, 0x8 bytes, shop_select.c (DIE 0x22C652) */
struct anon_3_126 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_0_126 -- @anon0, 0x518 bytes, shop_select.c (DIE 0x22B96A) */
struct anon_0_126 {   // size 0x518
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
    /* 0x234 */ struct anon_8_126 secret_list[50];    // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ struct anon_5_126 text_w;             // 0x10
    /* 0x310 */ struct anon_7_126 button_disp_w;      // 0x10
    /* 0x320 */ struct anon_2_126 fade_env;           // 0x10
    /* 0x330 */ struct anon_1_126 pad_w;              // 0x14
    /* 0x344 */ struct anon_6_126 mess_w;             // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ struct anon_4_126 move_w[9];          // 0xB4
    /* 0x510 */ struct anon_3_126 shop_rect;          // 0x8
};


/* functions defined (5) */
static int shop_select_confirm_ctrl(void);                       /* 0x00252530-0x00252768 lines 606-669 */
static int shop_select_confirm(void);                            /* 0x00252770-0x00252A88 lines 498-603 */
static void shop_select_disp(void);                              /* 0x00252A90-0x00252B28 lines 435-487 */
static int shop_select_ctrl(void);                               /* 0x00252B30-0x0025308C lines 244-426 */
void shop_select(struct anon_0_126 *work);                       /* 0x00253090-0x002533E4 lines 39-184 */

#endif /* DDR_UNIT_src_CS_shop_shop_select_c_H */
