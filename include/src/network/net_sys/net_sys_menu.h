/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_menu.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00224580-0x00224FB4
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
#ifndef DDR_UNIT_src_network_net_sys_net_sys_menu_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_menu_c_H

#include "types/_NETWORK_W.h"

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
