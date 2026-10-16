/*
 * C:\work2\usaex2\src\network\net_play\net_play_main.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x00231A90-0x002321EC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_play_net_play_main_c_H
#define DDR_UNIT_src_network_net_play_net_play_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_nsv_rc_table_param_work.h"
#include "types/_tag_cNetPlay.h"
#include "types/_tag_cNetPlayArg.h"
#include "types/g_game_w.h"

/* anonymous types (6) */

/* anon_1_102 -- @anon1, 0x4 bytes, net_play_main.c (DIE 0x1C141E) */
union anon_1_102 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_2_102 -- @anon2, 0x10 bytes, net_play_main.c (DIE 0x1C1C19) */
struct anon_2_102 {   // size 0x10
    /* 0x000 */ union anon_1_102 x0;                  // 0x4
    /* 0x004 */ union anon_1_102 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_0_102 -- @anon0, 0x184 bytes, net_play_main.c (DIE 0x1BE74C) */
struct anon_0_102 {   // size 0x184
    /* 0x000 */ struct anon_2_102 line_a[8];          // 0x80
    /* 0x080 */ struct anon_2_102 line_b[8];          // 0x80
    /* 0x100 */ struct anon_2_102 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_3_102 -- @anon3, 0x14 bytes, net_play_main.c (DIE 0x1C1FFF) */
struct anon_3_102 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_4_102 -- @anon4, 0x8 bytes, net_play_main.c (DIE 0x1C40C8) */
struct anon_4_102 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_5_102 -- @anon5, 0x4 bytes, net_play_main.c (DIE 0x1C4C76) */
struct anon_5_102 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};


/* variables (6) */
struct _tag_cNetPlay *pNetPlay;                                  /* @0x002DDBE8 size 0x4 */
static struct _tag_cNetPlayArg *pDebugArg;                       /* not allocated size 0x4 */
static int Step0;                                                /* not allocated size 0x4 */
static int Step1;                                                /* not allocated size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
static struct _tag_cNetPlay _pNetPlay;                           /* @0x0071F020 size 0x5C */

/* functions defined (19) */
int npGetUseDancerNum(void);                                     /* 0x00231A90-0x00231AC8 lines 440-450 */
unsigned int npGetResultDataAddr(void);                          /* 0x00231AD0-0x00231ADC lines 432-433 */
unsigned int npGetPlayDataAddr(void);                            /* 0x00231AE0-0x00231AEC lines 424-425 */
int npGetAfterSyncState(void);                                   /* 0x00231AF0-0x00231AFC lines 416-417 */
void npSetAfterSyncState(int state);                             /* 0x00231B00-0x00231B0C lines 413-414 */
int npGetBeforeSyncState(void);                                  /* 0x00231B10-0x00231B1C lines 405-406 */
void npSetBeforeSyncState(int state);                            /* 0x00231B20-0x00231B2C lines 402-403 */
int npGetAfterSyncFlag(void);                                    /* 0x00231B30-0x00231B3C lines 394-395 */
void npSetAfterSyncFlag(int flag);                               /* 0x00231B40-0x00231B4C lines 391-392 */
int npGetBeforeSyncFlag(void);                                   /* 0x00231B50-0x00231B5C lines 383-384 */
void npSetBeforeSyncFlag(int flag);                              /* 0x00231B60-0x00231B6C lines 380-381 */
int npGetForceClearFlag(void);                                   /* 0x00231B70-0x00231B7C lines 372-373 */
void npSetForceClearFlag(int flag);                              /* 0x00231B80-0x00231B8C lines 369-370 */
int TermNetRankPlay(void);                                       /* 0x00231B90-0x00231BB8 lines 347-350 */
int MainNetRankPlay(void);                                       /* 0x00231BC0-0x00231CDC lines 302-343 */
int InitNetRankPlay(struct _NETWORK_W *netw);                    /* 0x00231CE0-0x00231EB8 lines 202-298 */
int TermNetPlay(void);                                           /* 0x00231EC0-0x00231EEC lines 187-193 */
int MainNetPlay(void);                                           /* 0x00231EF0-0x0023200C lines 141-183 */
int InitNetPlay(struct _tag_cNetPlayArg *arg);                   /* 0x00232010-0x002321EC lines 48-137 */

#endif /* DDR_UNIT_src_network_net_play_net_play_main_c_H */
