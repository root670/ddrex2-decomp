/*
 * C:\work2\usaex2\src\AM\s573\play\p_anime.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001C5B40-0x001C6490
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
#ifndef DDR_UNIT_src_AM_s573_play_p_anime_c_H
#define DDR_UNIT_src_AM_s573_play_p_anime_c_H

#include "types/g_game_w.h"
#include "types/note_status.h"
#include "types/play_anime_db.h"
#include "types/play_anime_work.h"
#include "types/play_w.h"
#include "types/sequence.h"

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
