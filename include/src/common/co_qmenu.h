/*
 * C:\work2\usaex2\src\common\co_qmenu.c
 * MW MIPS C Compiler, overlay main; 16 functions, code 0x0023D340-0x0023E12C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_common_co_qmenu_c_H
#define DDR_UNIT_src_common_co_qmenu_c_H

#include "types/_tag_cCoCursor01.h"
#include "types/tex_bind.h"

/* anonymous types (8) */

/* anon_0_107 -- @anon0, 0xC bytes, co_qmenu.c (DIE 0x1E18A4) */
typedef struct {   // size 0xC
    /* 0x000 */ int (*func)();                        // 0x4
    /* 0x004 */ int (*ini)();                         // 0x4
    /* 0x008 */ unsigned char *str;                   // 0x4
} anon_0_107;

/* anon_1_107 -- @anon1, 0x48 bytes, co_qmenu.c (DIE 0x1E197F) */
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
} anon_1_107;

/* anon_3_107 -- @anon3, 0x4 bytes, co_qmenu.c (DIE 0x1E1E26) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_107;

/* anon_2_107 -- @anon2, 0x24 bytes, co_qmenu.c (DIE 0x1E1C92) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_3_107 x0;                        // 0x4
    /* 0x004 */ anon_3_107 y0;                        // 0x4
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
} anon_2_107;

/* anon_4_107 -- @anon4, 0x30 bytes, co_qmenu.c (DIE 0x1E1E83) */
typedef struct {   // size 0x30
    /* 0x000 */ anon_3_107 x0;                        // 0x4
    /* 0x004 */ anon_3_107 y0;                        // 0x4
    /* 0x008 */ anon_3_107 x1;                        // 0x4
    /* 0x00C */ anon_3_107 y1;                        // 0x4
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
} anon_4_107;

/* anon_5_107 -- @anon5, 0x10 bytes, co_qmenu.c (DIE 0x1E2098) */
typedef struct {   // size 0x10
    /* 0x000 */ float alpha;                          // 0x4
    /* 0x004 */ float t;                              // 0x4
    /* 0x008 */ int iw;                               // 0x4
    /* 0x00C */ float fw;                             // 0x4
} anon_5_107;

/* anon_6_107 -- @anon6, 0x40 bytes, co_qmenu.c (DIE 0x1E22FB) */
typedef struct {   // size 0x40
    /* 0x000 */ int qw00_tex_id;                      // 0x4
    /* 0x004 */ int cur01_tex_id;                     // 0x4
    /* 0x008 */ int csxx20_tex_id;                    // 0x4
    /* 0x00C */ int (*tmp_func)();                    // 0x4
    /* 0x010 */ unsigned short z;                     // 0x2
    /* 0x012 */ unsigned char stat;                   // 0x1
    /* 0x013 */ unsigned char cur;                    // 0x1
    /* 0x014 */ unsigned char num;                    // 0x1
    /* 0x015 */ unsigned char open_req;               // 0x1
    /* 0x016 */ unsigned char close_req;              // 0x1
    /* 0x017 */ unsigned char func_req;               // 0x1
    /* 0x018 */ int obj_id;                           // 0x4
    /* 0x01C */ void *obj_p;                          // 0x4
    /* 0x020 */ float w;                              // 0x4
    /* 0x024 */ float h;                              // 0x4
    /* 0x028 */ float max_w;                          // 0x4
    /* 0x02C */ float y0;                             // 0x4
    /* 0x030 */ anon_0_107 **qd;                      // 0x4
    /* 0x034 */ struct _tag_cCoCursor01 cur_w;        // 0xC
} anon_6_107;

/* anon_7_107 -- @anon7, 0x10 bytes, co_qmenu.c (DIE 0x1E25BC) */
typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_7_107;


/* variables (4) */
static anon_7_107 co_qmenu_objf;                                 /* @0x002BEDE0 size 0x10 */
static anon_6_107 *qmw;                                          /* @0x002DDC2C size 0x4 */
struct tex_bind tex_bind[375];                                   /* @0x0058C390 size 0x2904 */
static anon_6_107 co_qmenu_w;                                    /* @0x0071F8A0 size 0x40 */

/* functions defined (16) */
static int co_qmenu_disp(void *wp);                              /* 0x0023D340-0x0023D968 lines 614-765 */
static int co_qmenu_exec(void *w);                               /* 0x0023D970-0x0023DC40 lines 527-611 */
void co_qmenu_exec_func(void);                                   /* 0x0023DC40-0x0023DC54 lines 509-511 */
unsigned char co_qmenu_cursor_get(void);                         /* 0x0023DC60-0x0023DC6C lines 503-504 */
void co_qmenu_cursor_dec(void);                                  /* 0x0023DC70-0x0023DCAC lines 493-497 */
void co_qmenu_cursor_inc(void);                                  /* 0x0023DCB0-0x0023DCF4 lines 485-489 */
void co_qmenu_cursor_set(unsigned char cur);                     /* 0x0023DD00-0x0023DD28 lines 477-480 */
void co_qmenu_close(void);                                       /* 0x0023DD30-0x0023DD40 lines 471-472 */
void co_qmenu_open(void);                                        /* 0x0023DD40-0x0023DD50 lines 464-465 */
unsigned char co_qmenu_get_stat(void);                           /* 0x0023DD50-0x0023DD5C lines 457-458 */
void co_qmenu_set_y(float y0);                                   /* 0x0023DD60-0x0023DD6C lines 450-451 */
void co_qmenu_set_width(float width);                            /* 0x0023DD70-0x0023DD98 lines 442-444 */
void co_quick_menu_data_set(anon_0_107 **qdp);                   /* 0x0023DDA0-0x0023DEB8 lines 391-411 */
void co_quick_menu_disap(void);                                  /* 0x0023DEC0-0x0023DF24 lines 366-371 */
void co_quick_menu_set(anon_0_107 **qdp, unsigned short pri, unsigned char obj_pri); /* 0x0023DF30-0x0023E11C lines 325-361 */
void co_quick_menu_init(void);                                   /* 0x0023E120-0x0023E12C lines 314-314 */

#endif /* DDR_UNIT_src_common_co_qmenu_c_H */
