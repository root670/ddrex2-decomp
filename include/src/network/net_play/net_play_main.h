/*
 * C:\work2\usaex2\src\network\net_play\net_play_main.c
 * MW MIPS C Compiler, overlay main; 19 functions, code 0x00231A90-0x002321EC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_play_net_play_main_c_H
#define DDR_UNIT_src_network_net_play_net_play_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_nsv_rc_table_param_work.h"
#include "types/_tag_cNetPlay.h"
#include "types/_tag_cNetPlayArg.h"
#include "types/g_game_w.h"

/* anonymous types (2) */

/* anon_1_102 -- @anon1, 0x4 bytes, net_play_main.c (DIE 0x1C141E) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_1_102;

/* anon_2_102 -- @anon2, 0x10 bytes, net_play_main.c (DIE 0x1C1C19) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_1_102 x0;                        // 0x4
    /* 0x004 */ anon_1_102 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_2_102;


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
