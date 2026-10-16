/*
 * C:\work2\usaex2\src\network\net_game\net_game_match.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x001FB620-0x001FCD18
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_match_c_H
#define DDR_UNIT_src_network_net_game_net_game_match_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* anonymous types (6) */

/* anon_0_54 -- @anon0, 0x8 bytes, net_game_match.c (DIE 0xC2C99) */
struct anon_0_54 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_54 -- @anon1, 0x1048 bytes, net_game_match.c (DIE 0xC2FCD) */
struct anon_1_54 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_3_54 -- @anon3, 0x4 bytes, net_game_match.c (DIE 0xC77BC) */
struct anon_3_54 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_4_54 -- @anon4, 0x4 bytes, net_game_match.c (DIE 0xC7D5B) */
struct anon_4_54 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_2_54 -- @anon2, 0x4 bytes, net_game_match.c (DIE 0xC7393) */
union anon_2_54 {   // size 0x4
    /* 0x000 */ struct anon_3_54 S_un_b;              // 0x4
    /* 0x000 */ struct anon_4_54 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_5_54 -- @anon5, 0x10 bytes, net_game_match.c (DIE 0xC93F6) */
struct anon_5_54 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};


/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (10) */
void NetGameMatchStepin(struct _NETWORK_W *);                    /* @0x001FC310 */
void NetGameMatchStepout(struct _NETWORK_W *);                   /* @0x001FC2D0 */
void NetGameMenuChangeTab(struct _NETWORK_W *);                  /* @0x001FABC0 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetGameMatchSearchKey(struct _NETWORK_W *);                 /* @0x001FB620 */
void NetGameReverseMenu(struct _NETWORK_W *);                    /* @0x001F67A0 */
void NetGameMatchKey(struct _NETWORK_W *);                       /* @0x001FBA20 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */
void NetGameMatchMain(struct _NETWORK_W *);                      /* @0x001FBFA0 */
void NetGameMatchSearchMain(struct _NETWORK_W *);                /* @0x001FB7D0 */

/* functions defined (11) */
static void NetGameMatchSearchKey(struct _NETWORK_W *netw);      /* 0x001FB620-0x001FB7D0 lines 577-599 */
static void NetGameMatchSearchMain(struct _NETWORK_W *netw);     /* 0x001FB7D0-0x001FBA18 lines 490-571 */
static void NetGameMatchKey(struct _NETWORK_W *netw);            /* 0x001FBA20-0x001FBFA0 lines 424-483 */
static void NetGameMatchMain(struct _NETWORK_W *netw);           /* 0x001FBFA0-0x001FC2C8 lines 300-418 */
void NetGameMatchStepout(struct _NETWORK_W *netw);               /* 0x001FC2D0-0x001FC310 lines 289-294 */
void NetGameMatchStepin(struct _NETWORK_W *netw);                /* 0x001FC310-0x001FC390 lines 273-287 */
void NetGameMatchExCursorOn(struct _NETWORK_W *netw);            /* 0x001FC390-0x001FC6B4 lines 212-265 */
void NetGameMatchExCursorOff(struct _NETWORK_W *netw);           /* 0x001FC6C0-0x001FC8F8 lines 172-209 */
void NetGameMatchExClose(struct _NETWORK_W *netw);               /* 0x001FC900-0x001FC9C8 lines 154-165 */
void NetGameMatchExOpen(struct _NETWORK_W *netw);                /* 0x001FC9D0-0x001FCA90 lines 139-151 */
void NetGameMatchInit(struct _NETWORK_W *netw);                  /* 0x001FCA90-0x001FCD18 lines 85-132 */

#endif /* DDR_UNIT_src_network_net_game_net_game_match_c_H */
