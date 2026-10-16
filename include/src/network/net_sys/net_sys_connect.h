/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_connect.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x002284F0-0x002285C0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_connect_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_connect_c_H

#include "types/_NETWORK_W.h"

/* anonymous types (1) */

/* anon_0_83 -- @anon0, 0x8 bytes, net_sys_connect.c (DIE 0x170CEB) */
struct anon_0_83 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* functions referenced (3) */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetRouterMain(struct _NETWORK_W *);                         /* @0x008062B0 */
void NetSysConnectMain(struct _NETWORK_W *);                     /* @0x002284F0 */

/* functions defined (2) */
static void NetSysConnectMain(struct _NETWORK_W *netw);          /* 0x002284F0-0x002285B0 lines 19-67 */
void NetSysConnectInit(struct _NETWORK_W *netw);                 /* 0x002285B0-0x002285C0 lines 15-16 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_connect_c_H */
