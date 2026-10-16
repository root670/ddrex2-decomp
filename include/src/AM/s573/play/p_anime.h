/*
 * C:\work2\usaex2\src\AM\s573\play\p_anime.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001C5B40-0x001C6490
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
#include "types/play_w.h"
#include "types/sequence.h"

/* anonymous types (5) */

/* anon_0_11 -- @anon0, 0x4 bytes, p_anime.c (DIE 0x1805F) */
struct anon_0_11 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_2_11 -- @anon2, 0x4 bytes, p_anime.c (DIE 0x1A929) */
union anon_2_11 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_3_11 -- @anon3, 0x10 bytes, p_anime.c (DIE 0x1A9AA) */
struct anon_3_11 {   // size 0x10
    /* 0x000 */ union anon_2_11 x0;                   // 0x4
    /* 0x004 */ union anon_2_11 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_1_11 -- @anon1, 0x184 bytes, p_anime.c (DIE 0x1898B) */
struct anon_1_11 {   // size 0x184
    /* 0x000 */ struct anon_3_11 line_a[8];           // 0x80
    /* 0x080 */ struct anon_3_11 line_b[8];           // 0x80
    /* 0x100 */ struct anon_3_11 line_c[8];           // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_4_11 -- @anon4, 0x14 bytes, p_anime.c (DIE 0x1AB38) */
struct anon_4_11 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};


/* variables (6) */
static int anime_id_tbl[11];                                     /* @0x002D0B60 size 0x2C */
static int hold_release;                                         /* @0x002DE49C size 0x4 */
static int pre_hold_flag;                                        /* @0x002DE4A0 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
struct play_anime_work *paw_p;                                   /* @0x002DE4A4 size 0x4 */
struct play_anime_work play_anime_w;                             /* @0x0070FE90 size 0x3C */

/* functions defined (5) */
void play_anime_step_inst(void);                                 /* 0x001C5B40-0x001C5F5C lines 383-574 */
void play_anime_finish(void);                                    /* 0x001C5F60-0x001C5F68 lines 365-365 */
void play_anime_step(void);                                      /* 0x001C5F70-0x001C6414 lines 110-359 */
void play_anime_init(void);                                      /* 0x001C6420-0x001C6478 lines 80-99 */
void play_anime_set_inst_mode(void);                             /* 0x001C6480-0x001C6490 lines 67-68 */

#endif /* DDR_UNIT_src_AM_s573_play_p_anime_c_H */
