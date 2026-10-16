/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_menu.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00224580-0x00224FB4
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_menu_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_menu_c_H

#include "types/_NETWORK_W.h"

/* anonymous types (1) */

/* anon_0_78 -- @anon0, 0x8 bytes, net_sys_menu.c (DIE 0x152313) */
struct anon_0_78 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* functions referenced (5) */
void NetSysLogoutInit(struct _NETWORK_W *);                      /* @0x0022CB60 */
void NetSysInfoInit(struct _NETWORK_W *);                        /* @0x00229050 */
void NetSysUserInit(struct _NETWORK_W *);                        /* @0x00227780 */
void NetSysMenuSelectKey(struct _NETWORK_W *);                   /* @0x00224580 */
void NetSysMenuMain(struct _NETWORK_W *);                        /* @0x00224710 */

/* functions defined (4) */
static void NetSysMenuSelectKey(struct _NETWORK_W *netw);        /* 0x00224580-0x00224710 lines 266-289 */
static void NetSysMenuMain(struct _NETWORK_W *netw);             /* 0x00224710-0x00224AC8 lines 159-260 */
void NetSysMenuInit2(struct _NETWORK_W *netw);                   /* 0x00224AD0-0x00224D3C lines 98-153 */
void NetSysMenuInit(struct _NETWORK_W *netw);                    /* 0x00224D40-0x00224FB4 lines 37-95 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_menu_c_H */
