/*
 * C:\work2\usaex2\src\CS\ani_load.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x001C6490-0x001C6580
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_CS_ani_load_c_H
#define DDR_UNIT_src_CS_ani_load_c_H

#include "types/g_game_w.h"

/* anonymous types (3) */

/* anon_3_12 -- @anon3, 0x4 bytes, ani_load.c (DIE 0x1E12D) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_12;

/* anon_4_12 -- @anon4, 0x10 bytes, ani_load.c (DIE 0x1EA65) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_3_12 x0;                         // 0x4
    /* 0x004 */ anon_3_12 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_4_12;

/* anon_1_12 -- @anon1, 0x8 bytes, ani_load.c (DIE 0x1DC43) */
typedef struct {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
} anon_1_12;


/* variables (3) */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
anon_1_12 ani_data_2p[];                                         /* @0x002DA4C0 */
anon_1_12 ani_data_1p[];                                         /* @0x002DA4B8 */

/* functions defined (4) */
void SetBeginnerFlg2p(int flg);                                  /* 0x001C6490-0x001C649C lines 97-98 */
void SetBeginnerFlg1p(int flg);                                  /* 0x001C64A0-0x001C64AC lines 93-94 */
int sysReadAnimeWait2(int player);                               /* 0x001C64B0-0x001C6518 lines 59-82 */
int sysReadAnimeInit2(int player);                               /* 0x001C6520-0x001C6580 lines 21-50 */

#endif /* DDR_UNIT_src_CS_ani_load_c_H */
