/*
 * C:\work2\usaex2\src\AM\s573\play\p_anime.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001C5B40-0x001C6490
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_AM_s573_play_p_anime_c_H
#define DDR_UNIT_src_AM_s573_play_p_anime_c_H

#include "types/g_game_w.h"
#include "types/note_status.h"
#include "types/play_anime_db.h"
#include "types/play_anime_work.h"
#include "types/play_w.h"
#include "types/sequence.h"

/* anonymous types (2) */

/* anon_2_11 -- @anon2, 0x4 bytes, p_anime.c (DIE 0x1A929) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_2_11;

/* anon_3_11 -- @anon3, 0x10 bytes, p_anime.c (DIE 0x1A9AA) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_2_11 x0;                         // 0x4
    /* 0x004 */ anon_2_11 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_3_11;


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
