/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_lobby.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x0023F4C0-0x00240068
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (3) */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetSysUserInit2(struct _NETWORK_W *);                       /* @0x002274A0 */
void NetGameInit(struct _NETWORK_W *);                           /* @0x001F6830 */

/* functions defined (4) */
static void NetSysLobbyToAccountConnect(struct _NETWORK_W *netw); /* 0x0023F4C0-0x0023F550 lines 326-344 */
static void NetSysLobbySelectKey(struct _NETWORK_W *netw);       /* 0x0023F550-0x0023F798 lines 296-319 */
static void NetSysLobbyMain(struct _NETWORK_W *netw);            /* 0x0023F7A0-0x0023FC18 lines 156-290 */
void NetSysLobbyInit(struct _NETWORK_W *netw);                   /* 0x0023FC20-0x00240068 lines 46-144 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_lobby_c_H */
