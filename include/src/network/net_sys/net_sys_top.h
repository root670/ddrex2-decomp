/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_top.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00225C60-0x00226874
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
#ifndef DDR_UNIT_src_network_net_sys_net_sys_top_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_top_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (3) */
void NetSysEnd(struct _NETWORK_W *);                             /* @0x00224270 */
void NetSysRuleInit(struct _NETWORK_W *);                        /* @0x00228140 */
void NetCnfMain(struct _NETWORK_W *);                            /* @0x00802460 */

/* functions defined (4) */
static void NetSysTopKey(struct _NETWORK_W *netw);               /* 0x00225C60-0x00225EA8 lines 317-349 */
static void NetSysTopMain(struct _NETWORK_W *netw);              /* 0x00225EB0-0x00226380 lines 163-310 */
void NetSysTopInit2(struct _NETWORK_W *netw);                    /* 0x00226380-0x002265FC lines 97-155 */
void NetSysTopInit(struct _NETWORK_W *netw);                     /* 0x00226600-0x00226874 lines 35-93 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_top_c_H */
