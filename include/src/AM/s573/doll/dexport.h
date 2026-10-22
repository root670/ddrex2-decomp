/*
 * C:\work2\usaex2\src\AM\s573\doll\dexport.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001CF1B0-0x001CF378
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
#ifndef DDR_UNIT_src_AM_s573_doll_dexport_c_H
#define DDR_UNIT_src_AM_s573_doll_dexport_c_H

#include "types/_tag_cDDR8SaveData.h"
#include "types/g_game_w.h"
#include "types/oni_course.h"

/* anonymous types (1) */

/* anon_1_26 -- @anon1, 0x31 bytes, dexport.c (DIE 0x383D2) */
typedef struct {   // size 0x31
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[48];                          // 0x30
} anon_1_26;


/* variables (2) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions defined (2) */
void ps2dancerInitHide(void);                                    /* 0x001CF1B0-0x001CF220 lines 98-105 */
void ps2dancerGetDollList(anon_1_26 *wk, int mode);              /* 0x001CF220-0x001CF378 lines 61-82 */

#endif /* DDR_UNIT_src_AM_s573_doll_dexport_c_H */
