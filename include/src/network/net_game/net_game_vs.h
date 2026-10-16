/*
 * C:\work2\usaex2\src\network\net_game\net_game_vs.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x002321F0-0x00233C48
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
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

/* anonymous types (11) */

/* anon_0_103 -- @anon0, 0x8 bytes, net_game_vs.c (DIE 0x1C69A4) */
struct anon_0_103 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_103 -- @anon1, 0x1048 bytes, net_game_vs.c (DIE 0x1C7014) */
struct anon_1_103 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_2_103 -- @anon2, 0x4 bytes, net_game_vs.c (DIE 0x1CA9DA) */
struct anon_2_103 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_4_103 -- @anon4, 0x4 bytes, net_game_vs.c (DIE 0x1CCDA0) */
struct anon_4_103 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_6_103 -- @anon6, 0x4 bytes, net_game_vs.c (DIE 0x1CD550) */
struct anon_6_103 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_3_103 -- @anon3, 0x4 bytes, net_game_vs.c (DIE 0x1CCB5E) */
union anon_3_103 {   // size 0x4
    /* 0x000 */ struct anon_4_103 S_un_b;             // 0x4
    /* 0x000 */ struct anon_6_103 S_un_w;             // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_7_103 -- @anon7, 0x4 bytes, net_game_vs.c (DIE 0x1CE98C) */
union anon_7_103 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_8_103 -- @anon8, 0x10 bytes, net_game_vs.c (DIE 0x1CFC3E) */
struct anon_8_103 {   // size 0x10
    /* 0x000 */ union anon_7_103 x0;                  // 0x4
    /* 0x004 */ union anon_7_103 y0;                  // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_5_103 -- @anon5, 0x184 bytes, net_game_vs.c (DIE 0x1CD287) */
struct anon_5_103 {   // size 0x184
    /* 0x000 */ struct anon_8_103 line_a[8];          // 0x80
    /* 0x080 */ struct anon_8_103 line_b[8];          // 0x80
    /* 0x100 */ struct anon_8_103 line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_9_103 -- @anon9, 0x14 bytes, net_game_vs.c (DIE 0x1D0B65) */
struct anon_9_103 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_10_103 -- @anon10, 0x10 bytes, net_game_vs.c (DIE 0x1D0EAE) */
struct anon_10_103 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};


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
