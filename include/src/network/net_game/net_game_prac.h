/*
 * C:\work2\usaex2\src\network\net_game\net_game_prac.c
 * MW MIPS C Compiler, overlay main; 9 functions, code 0x00200B90-0x002015A8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_prac_c_H
#define DDR_UNIT_src_network_net_game_net_game_prac_c_H

#include "types/_NETWORK_W.h"

/* anonymous types (1) */

/* anon_0_56 -- @anon0, 0x8 bytes, net_game_prac.c (DIE 0xD12FF) */
struct anon_0_56 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};


/* functions referenced (5) */
void NetGameMenuChangeTab(struct _NETWORK_W *);                  /* @0x001FABC0 */
void NetGamePracStepout(struct _NETWORK_W *);                    /* @0x00200FB0 */
void NetGamePracKey(struct _NETWORK_W *);                        /* @0x00200B90 */
void NetGameMenuInit2(struct _NETWORK_W *);                      /* @0x001FB280 */
void NetGamePracMain(struct _NETWORK_W *);                       /* @0x00200EC0 */

/* functions defined (9) */
static void NetGamePracKey(struct _NETWORK_W *netw);             /* 0x00200B90-0x00200EB8 lines 275-312 */
static void NetGamePracMain(struct _NETWORK_W *netw);            /* 0x00200EC0-0x00200FA8 lines 231-269 */
void NetGamePracStepout(struct _NETWORK_W *netw);                /* 0x00200FB0-0x00200FF0 lines 221-225 */
void NetGamePracStepin(struct _NETWORK_W *netw);                 /* 0x00200FF0-0x00201030 lines 215-219 */
void NetGamePracExCursorOn(void);                                /* 0x00201030-0x002011F0 lines 158-207 */
void NetGamePracExCursorOff(void);                               /* 0x002011F0-0x002012D0 lines 129-155 */
void NetGamePracExClose(void);                                   /* 0x002012D0-0x00201314 lines 118-122 */
void NetGamePracExOpen(void);                                    /* 0x00201320-0x00201364 lines 112-116 */
void NetGamePracInit(struct _NETWORK_W *netw);                   /* 0x00201370-0x002015A8 lines 62-106 */

#endif /* DDR_UNIT_src_network_net_game_net_game_prac_c_H */
