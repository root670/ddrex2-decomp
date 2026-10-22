/*
 * C:\work2\usaex2\src\CS\ani_load.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x001C6490-0x001C6580
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
#ifndef DDR_UNIT_src_CS_ani_load_c_H
#define DDR_UNIT_src_CS_ani_load_c_H

#include "types/g_game_w.h"

/* anonymous types (1) */

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
