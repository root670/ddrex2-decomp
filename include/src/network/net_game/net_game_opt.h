/*
 * C:\work2\usaex2\src\network\net_game\net_game_opt.c
 * MW MIPS C Compiler, overlay main; 13 functions, code 0x001F92B0-0x001FA670
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
#ifndef DDR_UNIT_src_network_net_game_net_game_opt_c_H
#define DDR_UNIT_src_network_net_game_net_game_opt_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (4) */
int CwsWin_Multi2(struct _CWS_WIN_W *);                          /* @0x00240FB0 */
void NetGameMenuChangeTab(struct _NETWORK_W *);                  /* @0x001FABC0 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */

/* functions defined (13) */
static void NetGameOptPortSetKey(struct _NETWORK_W *netw);       /* 0x001F92B0-0x001F9598 lines 481-518 */
static void NetGameOptPortSetMain(struct _NETWORK_W *netw);      /* 0x001F95A0-0x001F9964 lines 394-476 */
static void NetGameOptPortSetInit(struct _NETWORK_W *netw);      /* 0x001F9970-0x001F99AC lines 388-392 */
static void NetGameOptKey(struct _NETWORK_W *netw);              /* 0x001F99B0-0x001F9C98 lines 344-382 */
static void NetGameOptMain(struct _NETWORK_W *netw);             /* 0x001F9CA0-0x001F9ED8 lines 245-338 */
static void NetGameOptInit2(struct _NETWORK_W *netw);            /* 0x001F9EE0-0x001F9F18 lines 239-243 */
void NetGameOptStepout(struct _NETWORK_W *netw);                 /* 0x001F9F20-0x001F9F60 lines 229-233 */
void NetGameOptStepin(struct _NETWORK_W *netw);                  /* 0x001F9F60-0x001F9FC0 lines 219-227 */
void NetGameOptExCursorOn(void);                                 /* 0x001F9FC0-0x001FA284 lines 164-213 */
void NetGameOptExCursorOff(void);                                /* 0x001FA290-0x001FA374 lines 145-161 */
void NetGameOptExClose(void);                                    /* 0x001FA380-0x001FA414 lines 128-138 */
void NetGameOptExOpen(void);                                     /* 0x001FA420-0x001FA4B4 lines 116-126 */
void NetGameOptInit(struct _NETWORK_W *netw);                    /* 0x001FA4C0-0x001FA670 lines 65-110 */

#endif /* DDR_UNIT_src_network_net_game_net_game_opt_c_H */
