/*
 * C:\work\usam2\src\CS\ani_load.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x002455A0-0x00245690
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_ani_load_c_H
#define DDR_UNIT_src_CS_ani_load_c_H

#include "types/g_game_w.h"

/* anonymous types (2) */

/* anon_0_38 -- @anon0, 0x4 bytes, ani_load.c (DIE 0x7680D) */
struct anon_0_38 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_1_38 -- @anon1, 0x8 bytes, ani_load.c (DIE 0x77FF6) */
struct anon_1_38 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};


/* variables (3) */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xAB544 */
struct anon_1_38 ani_data_2p[];                                  /* @0x002A1E88 */
struct anon_1_38 ani_data_1p[];                                  /* @0x002A1E80 */

/* functions defined (4) */
void SetBeginnerFlg2p(int flg);                                  /* 0x002455A0-0x002455AC lines 141-142 */
void SetBeginnerFlg1p(int flg);                                  /* 0x002455B0-0x002455BC lines 137-138 */
int sysReadAnimeWait2(int player);                               /* 0x002455C0-0x00245628 lines 63-86 */
int sysReadAnimeInit2(int player);                               /* 0x00245630-0x00245690 lines 23-54 */

#endif /* DDR_UNIT_src_CS_ani_load_c_H */
