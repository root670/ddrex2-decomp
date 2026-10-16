/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_lobby.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x0023F4C0-0x00240068
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* anonymous types (6) */

/* anon_0_110 -- @anon0, 0x8 bytes, net_sys_lobby.c (DIE 0x1EEA35) */
struct anon_0_110 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_110 -- @anon1, 0x1048 bytes, net_sys_lobby.c (DIE 0x1EECF4) */
struct anon_1_110 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_3_110 -- @anon3, 0x4 bytes, net_sys_lobby.c (DIE 0x1F32B8) */
struct anon_3_110 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_4_110 -- @anon4, 0x4 bytes, net_sys_lobby.c (DIE 0x1F395C) */
struct anon_4_110 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_2_110 -- @anon2, 0x4 bytes, net_sys_lobby.c (DIE 0x1F3071) */
union anon_2_110 {   // size 0x4
    /* 0x000 */ struct anon_3_110 S_un_b;             // 0x4
    /* 0x000 */ struct anon_4_110 S_un_w;             // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_5_110 -- @anon5, 0x10 bytes, net_sys_lobby.c (DIE 0x1F51EB) */
struct anon_5_110 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};


/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (6) */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetSysUserInit2(struct _NETWORK_W *);                       /* @0x002274A0 */
void NetSysLobbyToAccountConnect(struct _NETWORK_W *);           /* @0x0023F4C0 */
void NetGameInit(struct _NETWORK_W *);                           /* @0x001F6830 */
void NetSysLobbySelectKey(struct _NETWORK_W *);                  /* @0x0023F550 */
void NetSysLobbyMain(struct _NETWORK_W *);                       /* @0x0023F7A0 */

/* functions defined (4) */
static void NetSysLobbyToAccountConnect(struct _NETWORK_W *netw); /* 0x0023F4C0-0x0023F550 lines 326-344 */
static void NetSysLobbySelectKey(struct _NETWORK_W *netw);       /* 0x0023F550-0x0023F798 lines 296-319 */
static void NetSysLobbyMain(struct _NETWORK_W *netw);            /* 0x0023F7A0-0x0023FC18 lines 156-290 */
void NetSysLobbyInit(struct _NETWORK_W *netw);                   /* 0x0023FC20-0x00240068 lines 46-144 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H */
