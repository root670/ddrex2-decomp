/*
 * C:\work2\usaex2\src\network\net_game\net_game_vs.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x002321F0-0x00233C48
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_vs_c_H
#define DDR_UNIT_src_network_net_game_net_game_vs_c_H

#include "types/_NETWORK_W.h"
#include "types/_NET_WORK_DEAD_W.h"
#include "types/_NET_WORK_TYPE_RSEQ_BUF.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_result.h"
#include "types/_tag_cNetPlayArg.h"
#include "types/g_game_w.h"
#include "types/play_mode.h"
#include "types/play_w.h"
#include "types/sequence.h"

/* anonymous types (4) */

/* anon_4_103 -- @anon4, 0x4 bytes, net_game_vs.c (DIE 0x1CCDA0) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
} anon_4_103;

/* anon_6_103 -- @anon6, 0x4 bytes, net_game_vs.c (DIE 0x1CD550) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_6_103;

/* anon_7_103 -- @anon7, 0x4 bytes, net_game_vs.c (DIE 0x1CE98C) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_7_103;

/* anon_8_103 -- @anon8, 0x10 bytes, net_game_vs.c (DIE 0x1CFC3E) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_7_103 x0;                        // 0x4
    /* 0x004 */ anon_7_103 y0;                        // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_8_103;


/* variables (6) */
static int old_seq_data_num;                                     /* @0x002DE558 size 0x4 */
static int seq_data_max;                                         /* @0x002DE55C size 0x4 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */
short seq_data[1000];                                            /* @0x0071F0D0 size 0x7D0 */
struct _NET_WORK_TYPE_RSEQ_BUF recv_data;                        /* @0x0071F080 size 0x4C */

/* functions referenced (3) */
void NetToGameInit(struct _NETWORK_W *);                         /* @0x001EB260 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetGameVsMain(struct _NETWORK_W *);                         /* @0x002333B0 */

/* functions defined (5) */
static int NetGameVsPlay(struct _NETWORK_W *netw);               /* 0x002321F0-0x00232F40 lines 474-954 */
static int NetGameVsSetup(void);                                 /* 0x00232F40-0x002333AC lines 341-470 */
static void NetGameVsMain(struct _NETWORK_W *netw);              /* 0x002333B0-0x002338C4 lines 137-336 */
void NetGameVsInit(struct _NETWORK_W *netw);                     /* 0x002338D0-0x00233BD8 lines 56-129 */
void NetGameVsInitForWin(void);                                  /* 0x00233BE0-0x00233C48 lines 43-53 */

#endif /* DDR_UNIT_src_network_net_game_net_game_vs_c_H */
