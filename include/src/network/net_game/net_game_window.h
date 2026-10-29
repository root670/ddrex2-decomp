/*
 * C:\work2\usaex2\src\network\net_game\net_game_window.c
 * MW MIPS C Compiler, overlay main; 3 functions, code 0x001F72A0-0x001F7F68
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
#ifndef DDR_UNIT_src_network_net_game_net_game_window_c_H
#define DDR_UNIT_src_network_net_game_net_game_window_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/music_info.h"

/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (3) */
void NetGameVsInit(struct _NETWORK_W *);                         /* @0x002338D0 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */
void NetGamePrgReverseMenu(struct _NETWORK_W *);                 /* @0x00282DF0 */

/* functions defined (3) */
static void NetGameWinInterVSKey(struct _NETWORK_W *netw);       /* 0x001F72A0-0x001F7308 lines 434-442 */
void NetGameWinInterVSMain(struct _NETWORK_W *netw);             /* 0x001F7310-0x001F7A38 lines 214-432 */
static void NetGameWinInterVSInit(struct _NETWORK_W *netw);      /* 0x001F7A40-0x001F7F68 lines 92-212 */

#endif /* DDR_UNIT_src_network_net_game_net_game_window_c_H */
