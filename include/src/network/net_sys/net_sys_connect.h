/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_connect.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x002284F0-0x002285C0
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
#ifndef DDR_UNIT_src_network_net_sys_net_sys_connect_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_connect_c_H

#include "types/_NETWORK_W.h"

/* functions referenced (3) */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetRouterMain(struct _NETWORK_W *);                         /* @0x008062B0 */
void NetSysConnectMain(struct _NETWORK_W *);                     /* @0x002284F0 */

/* functions defined (2) */
static void NetSysConnectMain(struct _NETWORK_W *netw);          /* 0x002284F0-0x002285B0 lines 19-67 */
void NetSysConnectInit(struct _NETWORK_W *netw);                 /* 0x002285B0-0x002285C0 lines 15-16 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_connect_c_H */
