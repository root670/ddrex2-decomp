/*
 * C:\work2\usaex2\src\network\net_main.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x001EB010-0x001EB9C0
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
#ifndef DDR_UNIT_src_network_net_main_c_H
#define DDR_UNIT_src_network_net_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/g_game_w.h"

/* variables (3) */
static int test_shutdown;                                        /* @0x002DE504 size 0x4 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (4) */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */
void NetGameInit(struct _NETWORK_W *);                           /* @0x001F6830 */
void NetSysInit(struct _NETWORK_W *);                            /* @0x00224330 */
void NetSysEnd(struct _NETWORK_W *);                             /* @0x00224270 */

/* functions defined (7) */
char NetPadCon(unsigned int key);                                /* 0x001EB010-0x001EB198 lines 288-312 */
void NetToLogout(struct _NETWORK_W *netw);                       /* 0x001EB1A0-0x001EB260 lines 246-262 */
void NetToGameInit(struct _NETWORK_W *netw);                     /* 0x001EB260-0x001EB340 lines 209-241 */
void NetToSysInit(struct _NETWORK_W *netw);                      /* 0x001EB340-0x001EB460 lines 153-205 */
void NetEnd(void);                                               /* 0x001EB460-0x001EB4A4 lines 142-148 */
int NetMain(void);                                               /* 0x001EB4B0-0x001EB92C lines 64-138 */
void NetInit(void);                                              /* 0x001EB930-0x001EB9C0 lines 35-60 */

#endif /* DDR_UNIT_src_network_net_main_c_H */
