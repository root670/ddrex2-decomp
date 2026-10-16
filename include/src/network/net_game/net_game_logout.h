/*
 * C:\work2\usaex2\src\network\net_game\net_game_logout.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x001FA670-0x001FABC0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_logout_c_H
#define DDR_UNIT_src_network_net_game_net_game_logout_c_H

#include "types/_NETWORK_W.h"

/* anonymous types (1) */

/* anon_0_52 -- @anon0, 0x8 bytes, net_game_logout.c (DIE 0xB9EEA) */
struct anon_0_52 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* functions referenced (5) */
void NetGameEnd(struct _NETWORK_W *);                            /* @0x001F67E0 */
void NetGameLogoutStepout(struct _NETWORK_W *);                  /* @0x001FA980 */
void NetGameLogoutKey(struct _NETWORK_W *);                      /* @0x001FA670 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */
void NetGameLogoutMain(struct _NETWORK_W *);                     /* @0x001FA7F0 */

/* functions defined (8) */
static void NetGameLogoutKey(struct _NETWORK_W *netw);           /* 0x001FA670-0x001FA7E8 lines 176-197 */
static void NetGameLogoutMain(struct _NETWORK_W *netw);          /* 0x001FA7F0-0x001FA97C lines 114-170 */
void NetGameLogoutStepout(struct _NETWORK_W *netw);              /* 0x001FA980-0x001FA9CC lines 102-107 */
void NetGameLogoutStepin(struct _NETWORK_W *netw);               /* 0x001FA9D0-0x001FAAC0 lines 77-100 */
void NetGameLogoutExCursorOff(void);                             /* 0x001FAAC0-0x001FAAC8 lines 68-68 */
void NetGameLogoutExClose(void);                                 /* 0x001FAAD0-0x001FAAD8 lines 61-61 */
void NetGameLogoutExOpen(void);                                  /* 0x001FAAE0-0x001FAAE8 lines 58-58 */
void NetGameLogoutInit(void);                                    /* 0x001FAAF0-0x001FABC0 lines 36-51 */

#endif /* DDR_UNIT_src_network_net_game_net_game_logout_c_H */
