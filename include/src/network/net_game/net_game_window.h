/*
 * C:\work2\usaex2\src\network\net_game\net_game_window.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x001F72A0-0x001F7F68
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_window_c_H
#define DDR_UNIT_src_network_net_game_net_game_window_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/music_info.h"

/* anonymous types (6) */

/* anon_0_49 -- @anon0, 0x8 bytes, net_game_window.c (DIE 0xA3DEC) */
struct anon_0_49 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_49 -- @anon1, 0x1048 bytes, net_game_window.c (DIE 0xA4554) */
struct anon_1_49 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_3_49 -- @anon3, 0x4 bytes, net_game_window.c (DIE 0xA8DE4) */
struct anon_3_49 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_4_49 -- @anon4, 0x4 bytes, net_game_window.c (DIE 0xA9382) */
struct anon_4_49 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_2_49 -- @anon2, 0x4 bytes, net_game_window.c (DIE 0xA8B9D) */
union anon_2_49 {   // size 0x4
    /* 0x000 */ struct anon_3_49 S_un_b;              // 0x4
    /* 0x000 */ struct anon_4_49 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_5_49 -- @anon5, 0x10 bytes, net_game_window.c (DIE 0xAACE5) */
struct anon_5_49 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};


/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (4) */
void NetGameVsInit(struct _NETWORK_W *);                         /* @0x002338D0 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetGameWinInterVSKey(struct _NETWORK_W *);                  /* @0x001F72A0 */
void NetGamePrgReverseMenu(struct _NETWORK_W *);                 /* @0x00282DF0 */

/* functions defined (3) */
static void NetGameWinInterVSKey(struct _NETWORK_W *netw);       /* 0x001F72A0-0x001F7308 lines 434-442 */
void NetGameWinInterVSMain(struct _NETWORK_W *netw);             /* 0x001F7310-0x001F7A38 lines 214-432 */
static void NetGameWinInterVSInit(struct _NETWORK_W *netw);      /* 0x001F7A40-0x001F7F68 lines 92-212 */

#endif /* DDR_UNIT_src_network_net_game_net_game_window_c_H */
