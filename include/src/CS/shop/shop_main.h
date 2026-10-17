/*
 * C:\work2\usaex2\src\CS\shop\shop_main.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x002496B0-0x00249910
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_shop_shop_main_c_H
#define DDR_UNIT_src_CS_shop_shop_main_c_H

#include "types/g_game_w.h"

/* anonymous types (11) */

/* anon_0_124 -- @anon0, 0x8 bytes, shop_main.c (DIE 0x219674) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_0_124;

/* anon_1_124 -- @anon1, 0x14 bytes, shop_main.c (DIE 0x2199D6) */
typedef struct {   // size 0x14
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int count;                            // 0x4
    /* 0x008 */ int frame;                            // 0x4
    /* 0x00C */ int x;                                // 0x4
    /* 0x010 */ int y;                                // 0x4
} anon_1_124;

/* anon_2_124 -- @anon2, 0x10 bytes, shop_main.c (DIE 0x219ABA) */
typedef struct {   // size 0x10
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float cur_y;                          // 0x4
    /* 0x008 */ float dst_y;                          // 0x4
    /* 0x00C */ float speed;                          // 0x4
} anon_2_124;

/* anon_7_124 -- @anon7, 0x4 bytes, shop_main.c (DIE 0x21A7A9) */
typedef struct {   // size 0x4
    /* 0x000 */ short secret_no;                      // 0x2
    /* 0x002 */ short value;                          // 0x2
} anon_7_124;

/* anon_5_124 -- @anon5, 0x10 bytes, shop_main.c (DIE 0x21A637) */
typedef struct {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int br;                               // 0x4
} anon_5_124;

/* anon_11_124 -- @anon11, 0x10 bytes, shop_main.c (DIE 0x21CA9A) */
typedef struct {   // size 0x10
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ float spd;                            // 0x4
    /* 0x008 */ float a;                              // 0x4
    /* 0x00C */ int z;                                // 0x4
} anon_11_124;

/* anon_13_124 -- @anon13, 0x14 bytes, shop_main.c (DIE 0x21CD2C) */
typedef struct {   // size 0x14
    /* 0x000 */ int dx;                               // 0x4
    /* 0x004 */ int dy;                               // 0x4
    /* 0x008 */ int repeat_y;                         // 0x4
    /* 0x00C */ int decide;                           // 0x4
    /* 0x010 */ int cancel;                           // 0x4
} anon_13_124;

/* anon_4_124 -- @anon4, 0x8 bytes, shop_main.c (DIE 0x21A297) */
typedef struct {   // size 0x8
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ float ct;                             // 0x4
} anon_4_124;

/* anon_3_124 -- @anon3, 0x518 bytes, shop_main.c (DIE 0x219BCE) */
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
    /* 0x234 */ anon_7_124 secret_list[50];           // 0xC8
    /* 0x2FC */ int genwnd_tex_id;                    // 0x4
    /* 0x300 */ anon_2_124 text_w;                    // 0x10
    /* 0x310 */ anon_5_124 button_disp_w;             // 0x10
    /* 0x320 */ anon_11_124 fade_env;                 // 0x10
    /* 0x330 */ anon_13_124 pad_w;                    // 0x14
    /* 0x344 */ anon_4_124 mess_w;                    // 0x8
    /* 0x34C */ unsigned int cur_track;               // 0x4
    /* 0x350 */ unsigned int reserve_track;           // 0x4
    /* 0x354 */ int track_delay_time;                 // 0x4
    /* 0x358 */ unsigned char string[256];            // 0x100
    /* 0x458 */ short before_mode;                    // 0x2
    /* 0x45A */ // 0x2 bytes padding
    /* 0x45C */ anon_1_124 move_w[9];                 // 0xB4
    /* 0x510 */ anon_0_124 shop_rect;                 // 0x8
} anon_3_124;

/* anon_9_124 -- @anon9, 0x4 bytes, shop_main.c (DIE 0x21C888) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_9_124;

/* anon_10_124 -- @anon10, 0x10 bytes, shop_main.c (DIE 0x21C955) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_9_124 x0;                        // 0x4
    /* 0x004 */ anon_9_124 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_10_124;


/* variables (3) */
static int step0;                                                /* @0x002DE560 size 0x4 */
anon_3_124 *shop_w;                                              /* @0x002DE564 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions defined (6) */
void shop_set_step(int step);                                    /* 0x002496B0-0x00249760 lines 169-184 */
anon_3_124 *shop_get_work(void);                                 /* 0x00249760-0x00249768 lines 157-157 */
void ShopFinish(void);                                           /* 0x00249770-0x00249778 lines 142-142 */
int ShopStep(void);                                              /* 0x00249780-0x00249818 lines 105-129 */
void ShopAddrInit(unsigned char *addr);                          /* 0x00249820-0x0024989C lines 73-98 */
void ShopInit(void);                                             /* 0x002498A0-0x00249910 lines 35-57 */

#endif /* DDR_UNIT_src_CS_shop_shop_main_c_H */
