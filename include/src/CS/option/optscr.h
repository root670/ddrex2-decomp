/*
 * C:\work\usam2\src\CS\option\optscr.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00232EE0-0x00233DE0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_option_optscr_c_H
#define DDR_UNIT_src_CS_option_optscr_c_H

#include "types/_tag_cDDR7SaveData.h"
#include "types/_tag_cOpt.h"
#include "types/_tag_cOptScr.h"

/* anonymous types (5) */

/* anon_0_21 -- @anon0, 0xCC8 bytes, optscr.c (DIE 0x4A6CC) */
struct anon_0_21 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_2_21 -- @anon2, 0x4 bytes, optscr.c (DIE 0x4AD26) */
union anon_2_21 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_1_21 -- @anon1, 0x24 bytes, optscr.c (DIE 0x4AAE0) */
struct anon_1_21 {   // size 0x24
    /* 0x000 */ union anon_2_21 x0;                   // 0x4
    /* 0x004 */ union anon_2_21 y0;                   // 0x4
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

/* anon_3_21 -- @anon3, 0x48 bytes, optscr.c (DIE 0x4C05D) */
struct anon_3_21 {   // size 0x48
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

/* anon_4_21 -- @anon4, 0x10 bytes, optscr.c (DIE 0x4C889) */
struct anon_4_21 {   // size 0x10
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
};


/* variables (6) */
struct _tag_cOptScr *pOptScr;                                    /* @0x002A2270 size 0x4 */
static unsigned int button_bit_table[6];                         /* @0x00282F00 size 0x18 */
static struct anon_4_21 button_tex[6];                           /* @0x00282F20 size 0x60 */
struct _tag_cOpt *pOpt;                                          /* @0x002A05C0 size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
static struct _tag_cOptScr _pOptScr;                             /* @0x006B37C0 size 0x64 */

/* functions defined (4) */
int Update_Optscr(void);                                         /* 0x00232EE0-0x002330C8 lines 508-567 */
int View_Optscr(void);                                           /* 0x002330D0-0x00233768 lines 310-504 */
int Control_Optscr(void);                                        /* 0x00233770-0x00233D18 lines 133-298 */
int Init_Optscr(void);                                           /* 0x00233D20-0x00233DE0 lines 99-128 */

#endif /* DDR_UNIT_src_CS_option_optscr_c_H */
