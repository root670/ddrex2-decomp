/*
 * C:\work2\usaex2\src\network\net_game\net_game_list.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x002015B0-0x00202834
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
#ifndef DDR_UNIT_src_network_net_game_net_game_list_c_H
#define DDR_UNIT_src_network_net_game_net_game_list_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/_NS_NET_INFO_W.h"

/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (11) */
void NetGameListInit2(struct _NETWORK_W *);                      /* @0x00202130 */
void NetGameListDetailKey(struct _NETWORK_W *);                  /* @0x002015B0 */
void NetGameListDetailMain(struct _NETWORK_W *);                 /* @0x00201620 */
int NetWin_Listdtl3(struct _CWS_WIN_W *);                        /* @0x0025C660 */
int NetWin_Listdtl2(struct _CWS_WIN_W *);                        /* @0x0025B610 */
int NetWin_Listdtl(struct _CWS_WIN_W *);                         /* @0x0025BEC0 */
void NetGameListDetailInit(struct _NETWORK_W *);                 /* @0x00201760 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */
void NetGameListKey(struct _NETWORK_W *);                        /* @0x00201910 */
void NetGameListMain(struct _NETWORK_W *);                       /* @0x00201B10 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */

/* functions defined (7) */
static void NetGameListDetailKey(struct _NETWORK_W *netw);       /* 0x002015B0-0x00201618 lines 410-417 */
static void NetGameListDetailMain(struct _NETWORK_W *netw);      /* 0x00201620-0x00201758 lines 358-405 */
static void NetGameListDetailInit(struct _NETWORK_W *netw);      /* 0x00201760-0x00201904 lines 302-353 */
static void NetGameListKey(struct _NETWORK_W *netw);             /* 0x00201910-0x00201B10 lines 269-292 */
static void NetGameListMain(struct _NETWORK_W *netw);            /* 0x00201B10-0x00202130 lines 181-263 */
static void NetGameListInit2(struct _NETWORK_W *netw);           /* 0x00202130-0x00202140 lines 174-175 */
void NetGameListInit(struct _NETWORK_W *netw);                   /* 0x00202140-0x00202834 lines 54-159 */

#endif /* DDR_UNIT_src_network_net_game_net_game_list_c_H */
