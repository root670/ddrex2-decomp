/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_rule.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00227AA0-0x002284E8
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
#ifndef DDR_UNIT_src_network_net_sys_net_sys_rule_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_rule_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"

/* functions referenced (4) */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */
void NetSysEnd(struct _NETWORK_W *);                             /* @0x00224270 */
void NetSysTopInit(struct _NETWORK_W *);                         /* @0x00226600 */
int CwsWin_Multi(struct _CWS_WIN_W *);                           /* @0x00209DB0 */

/* functions defined (5) */
static void NetSysRuleSelectKey(struct _NETWORK_W *netw);        /* 0x00227AA0-0x00227BC8 lines 338-354 */
static void NetSysRuleKey(struct _NETWORK_W *netw);              /* 0x00227BD0-0x00227D7C lines 297-335 */
static void NetSysRuleMain(struct _NETWORK_W *netw);             /* 0x00227D80-0x00228134 lines 159-291 */
void NetSysRuleInit(struct _NETWORK_W *netw);                    /* 0x00228140-0x00228290 lines 119-152 */
void NetSysRuleStartInit(struct _NETWORK_W *netw);               /* 0x00228290-0x002284E8 lines 61-116 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_rule_c_H */
