/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_logout.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x0022C4B0-0x0022CCEC
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_logout_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_logout_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"

/* anonymous types (1) */

/* anon_0_90 -- @anon0, 0x8 bytes, net_sys_logout.c (DIE 0x19B3E9) */
struct anon_0_90 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* functions referenced (5) */
void NetSysMenuInit2(struct _NETWORK_W *);                       /* @0x00224AD0 */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */
void NetSysLogoutKey(struct _NETWORK_W *);                       /* @0x0022C4B0 */
void NetSysLogoutMain(struct _NETWORK_W *);                      /* @0x0022C620 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */

/* functions defined (3) */
static void NetSysLogoutKey(struct _NETWORK_W *netw);            /* 0x0022C4B0-0x0022C618 lines 150-170 */
static void NetSysLogoutMain(struct _NETWORK_W *netw);           /* 0x0022C620-0x0022CB54 lines 68-144 */
void NetSysLogoutInit(struct _NETWORK_W *netw);                  /* 0x0022CB60-0x0022CCEC lines 29-61 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_logout_c_H */
