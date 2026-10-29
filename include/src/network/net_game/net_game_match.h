/*
 * C:\work2\usaex2\src\network\net_game\net_game_match.c
 * MW MIPS C Compiler, overlay main; 11 functions, code 0x001FB620-0x001FCD18
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
#ifndef DDR_UNIT_src_network_net_game_net_game_match_c_H
#define DDR_UNIT_src_network_net_game_net_game_match_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (4) */
void NetGameMenuChangeTab(struct _NETWORK_W *);                  /* @0x001FABC0 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetGameReverseMenu(struct _NETWORK_W *);                    /* @0x001F67A0 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */

/* functions defined (11) */
static void NetGameMatchSearchKey(struct _NETWORK_W *netw);      /* 0x001FB620-0x001FB7D0 lines 577-599 */
static void NetGameMatchSearchMain(struct _NETWORK_W *netw);     /* 0x001FB7D0-0x001FBA18 lines 490-571 */
static void NetGameMatchKey(struct _NETWORK_W *netw);            /* 0x001FBA20-0x001FBFA0 lines 424-483 */
static void NetGameMatchMain(struct _NETWORK_W *netw);           /* 0x001FBFA0-0x001FC2C8 lines 300-418 */
void NetGameMatchStepout(struct _NETWORK_W *netw);               /* 0x001FC2D0-0x001FC310 lines 289-294 */
void NetGameMatchStepin(struct _NETWORK_W *netw);                /* 0x001FC310-0x001FC390 lines 273-287 */
void NetGameMatchExCursorOn(struct _NETWORK_W *netw);            /* 0x001FC390-0x001FC6B4 lines 212-265 */
void NetGameMatchExCursorOff(struct _NETWORK_W *netw);           /* 0x001FC6C0-0x001FC8F8 lines 172-209 */
void NetGameMatchExClose(struct _NETWORK_W *netw);               /* 0x001FC900-0x001FC9C8 lines 154-165 */
void NetGameMatchExOpen(struct _NETWORK_W *netw);                /* 0x001FC9D0-0x001FCA90 lines 139-151 */
void NetGameMatchInit(struct _NETWORK_W *netw);                  /* 0x001FCA90-0x001FCD18 lines 85-132 */

#endif /* DDR_UNIT_src_network_net_game_net_game_match_c_H */
