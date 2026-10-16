/*
 * C:\work\usam2\src\CS\endless\eds_break.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x00237c30-0x00237f50
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_endless_eds_break_c_H
#define DDR_UNIT_src_CS_endless_eds_break_c_H

#include "types/_EDSSYS_W.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/demo_loop_w.h"
#include "types/play_loop_w.h"

/* anonymous types (2) */

/* anon_0_25 -- @anon0, 0x8008 bytes, eds_break.c (DIE 0x597e5) */
union anon_0_25 {   // size 0x8008
    /* 0x000 */ struct demo_loop_w demo_loop_w;       // 0x8008
    /* 0x000 */ struct play_loop_w play_loop_w;       // 0x8008
};

/* anon_1_25 -- @anon1, 0xcc8 bytes, eds_break.c (DIE 0x59a5c) */
struct anon_1_25 {   // size 0xcc8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};


/* variables (2) */
struct _EDSSYS_W *EDSSYSW;                                       /* @0x002a2254 size 0x4 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002b0470 size 0x5e30 */

/* functions referenced (3) */
void EdsPlayCommon(struct _EDSSYS_W *);                          /* @0x002301a0 */
void EdsBreakStageEnd(struct _EDSSYS_W *);                       /* @0x00237c30 */
void EdsBreakStageMain(struct _EDSSYS_W *);                      /* @0x00237c90 */

/* functions defined (3) */
static void EdsBreakStageEnd(struct _EDSSYS_W *_eds);            /* 0x00237c30-0x00237c88 lines 198-214 */
static void EdsBreakStageMain(struct _EDSSYS_W *_eds);           /* 0x00237c90-0x00237e70 lines 84-191 */
void EdsBreakStageInit(struct _EDSSYS_W *_eds);                  /* 0x00237e70-0x00237f50 lines 30-77 */

#endif /* DDR_UNIT_src_CS_endless_eds_break_c_H */
