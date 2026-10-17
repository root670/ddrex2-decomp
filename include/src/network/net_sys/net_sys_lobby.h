/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_lobby.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x0023F4C0-0x00240068
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* anonymous types (2) */

/* anon_3_110 -- @anon3, 0x4 bytes, net_sys_lobby.c (DIE 0x1F32B8) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
} anon_3_110;

/* anon_4_110 -- @anon4, 0x4 bytes, net_sys_lobby.c (DIE 0x1F395C) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_4_110;


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
