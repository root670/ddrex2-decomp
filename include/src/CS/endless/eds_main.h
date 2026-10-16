/*
 * C:\work\usam2\src\CS\endless\eds_main.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x002329B0-0x00232ED8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_CS_endless_eds_main_c_H
#define DDR_UNIT_src_CS_endless_eds_main_c_H

#include "types/_EDSSYS_W.h"
#include "types/_GAME_MODE_W.h"
#include "types/_tag_cDDR7SaveData.h"
#include "types/demo_loop_w.h"
#include "types/g_game_w.h"
#include "types/play_loop_w.h"

/* anonymous types (3) */

/* anon_0_19 -- @anon0, 0x8008 bytes, eds_main.c (DIE 0x43CA5) */
union anon_0_19 {   // size 0x8008
    /* 0x000 */ struct demo_loop_w demo_loop_w;       // 0x8008
    /* 0x000 */ struct play_loop_w play_loop_w;       // 0x8008
};

/* anon_1_19 -- @anon1, 0xCC8 bytes, eds_main.c (DIE 0x43F66) */
struct anon_1_19 {   // size 0xCC8
    /* 0x000 */ unsigned int program_calorie[9];      // 0x24
    /* 0x024 */ unsigned int program_play_count[9];   // 0x24
    /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
};

/* anon_2_19 -- @anon2, 0x4 bytes, eds_main.c (DIE 0x44061) */
struct anon_2_19 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};


/* variables (6) */
struct _EDSSYS_W *EDSSYSW;                                       /* @0x002A2254 size 0x4 */
static char *eds_bin_data[5];                                    /* @0x00282D00 size 0x14 */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xAB544 */
unsigned char *eds_tex_data[];                                   /* @0x00288610 */
struct _tag_cDDR7SaveData SaveData;                              /* @0x002B0470 size 0x5E30 */
static struct _EDSSYS_W _eds_sys_w;                              /* @0x006B2CC0 size 0xB00 */

/* functions defined (6) */
int EdsInitBreakTex(struct _EDSSYS_W *_eds);                     /* 0x002329B0-0x00232B28 lines 344-388 */
int EdsInitTex(struct _EDSSYS_W *_eds, int _num);                /* 0x00232B30-0x00232DC0 lines 238-336 */
void EdsSystemEnd(void);                                         /* 0x00232DC0-0x00232DCC lines 207-210 */
int EdsSystemMain(void);                                         /* 0x00232DD0-0x00232E0C lines 166-178 */
void EdsSystemInit(struct _GAME_MODE_W *game_mode_w);            /* 0x00232E10-0x00232ED0 lines 118-142 */
void EdsSetPreRead(void);                                        /* 0x00232ED0-0x00232ED8 lines 95-95 */

#endif /* DDR_UNIT_src_CS_endless_eds_main_c_H */
