/*
 * C:\work\usam2\src\AM\s573\doll\dexport.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x00250370-0x0025070c
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_dexport_c_H
#define DDR_UNIT_src_AM_s573_doll_dexport_c_H

#include "types/_tag_cDDR7SaveData.h"
#include "types/g_game_w.h"

/* anonymous types (3) */

/* anon_0_55 -- @anon0, 0xcc8 bytes, dexport.c (DIE 0x988e9) */
struct anon_0_55 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_1_55 -- @anon1, 0x4 bytes, dexport.c (DIE 0x989e4) */
struct anon_1_55 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_2_55 -- @anon2, 0x3e bytes, dexport.c (DIE 0x9a79e) */
struct anon_2_55 {   // size 0x3e
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[61];                          // 0x3d
};


/* variables (2) */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xab544 */

/* functions defined (6) */
void ps2dancerInitHide(void);                                    /* 0x00250370-0x002503d8 lines 100-107 */
void ps2dancerGetDollListForOPT(struct anon_2_55 *wk);           /* 0x002503e0-0x00250450 lines 88-93 */
void ps2dancerGetDollList(struct anon_2_55 *wk, int mode);       /* 0x00250450-0x002505a8 lines 63-84 */
static void typical_entry(void);                                 /* 0x002505b0-0x002506a4 lines 43-56 */
void ps2dancerReChoiceChara(void);                               /* 0x002506b0-0x002506d4 lines 36-39 */
void ps2dancerTypicalInit(void);                                 /* 0x002506e0-0x0025070c lines 26-29 */

#endif /* DDR_UNIT_src_AM_s573_doll_dexport_c_H */
