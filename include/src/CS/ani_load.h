/*
 * C:\work2\usaex2\src\CS\ani_load.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x001C6490-0x001C6580
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_ani_load_c_H
#define DDR_UNIT_src_CS_ani_load_c_H

#include "types/g_game_w.h"

/* anonymous types (6) */

/* anon_3_12 -- @anon3, 0x4 bytes, ani_load.c (DIE 0x1E12D) */
union anon_3_12 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_4_12 -- @anon4, 0x10 bytes, ani_load.c (DIE 0x1EA65) */
struct anon_4_12 {   // size 0x10
    /* 0x000 */ union anon_3_12 x0;                   // 0x4
    /* 0x004 */ union anon_3_12 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_0_12 -- @anon0, 0x184 bytes, ani_load.c (DIE 0x1BC37) */
struct anon_0_12 {   // size 0x184
    /* 0x000 */ struct anon_4_12 line_a[8];           // 0x80
    /* 0x080 */ struct anon_4_12 line_b[8];           // 0x80
    /* 0x100 */ struct anon_4_12 line_c[8];           // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_1_12 -- @anon1, 0x8 bytes, ani_load.c (DIE 0x1DC43) */
struct anon_1_12 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};

/* anon_2_12 -- @anon2, 0x14 bytes, ani_load.c (DIE 0x1DD0B) */
struct anon_2_12 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_5_12 -- @anon5, 0x4 bytes, ani_load.c (DIE 0x1F034) */
struct anon_5_12 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};


/* variables (3) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct anon_1_12 ani_data_2p[];                                  /* @0x002DA4C0 */
struct anon_1_12 ani_data_1p[];                                  /* @0x002DA4B8 */

/* functions defined (4) */
void SetBeginnerFlg2p(int flg);                                  /* 0x001C6490-0x001C649C lines 97-98 */
void SetBeginnerFlg1p(int flg);                                  /* 0x001C64A0-0x001C64AC lines 93-94 */
int sysReadAnimeWait2(int player);                               /* 0x001C64B0-0x001C6518 lines 59-82 */
int sysReadAnimeInit2(int player);                               /* 0x001C6520-0x001C6580 lines 21-50 */

#endif /* DDR_UNIT_src_CS_ani_load_c_H */
