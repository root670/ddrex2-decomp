/*
 * C:\work\usam2\src\AM\s573\play\p_anime.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00245110-0x002454F0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_play_p_anime_c_H
#define DDR_UNIT_src_AM_s573_play_p_anime_c_H

#include "types/g_game_w.h"
#include "types/note_status.h"
#include "types/play_anime_db.h"
#include "types/play_anime_work.h"
#include "types/sequence.h"

/* anonymous types (1) */

/* anon_0_36 -- @anon0, 0x4 bytes, p_anime.c (DIE 0x748C4) */
struct anon_0_36 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};


/* variables (4) */
static int anime_id_tbl[11];                                     /* @0x0029F3A0 size 0x2C */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xAB544 */
struct play_anime_work *paw_p;                                   /* @0x002A2AAC size 0x4 */
struct play_anime_work play_anime_w;                             /* @0x006B42B0 size 0x24 */

/* functions defined (4) */
void play_anime_finish(void);                                    /* 0x00245110-0x00245118 lines 257-257 */
void play_anime_step(void);                                      /* 0x00245120-0x00245494 lines 86-252 */
void play_anime_init(void);                                      /* 0x002454A0-0x002454E0 lines 64-76 */
void play_anime_set_inst_mode(void);                             /* 0x002454E0-0x002454F0 lines 52-53 */

#endif /* DDR_UNIT_src_AM_s573_play_p_anime_c_H */
