/*
 * C:\work2\usaex2\src\network\net_game\net_game_main.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x001F6770-0x001F7294
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
#ifndef DDR_UNIT_src_network_net_game_net_game_main_c_H
#define DDR_UNIT_src_network_net_game_net_game_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_playerdata.h"
#include "types/g_game_w.h"

/* anonymous types (1) */

/* anon_10_48 -- @anon10, 0x18 bytes, net_game_main.c (DIE 0xA32B7) */
typedef struct {   // size 0x18
    /* 0x000 */ void *func;                           // 0x4
    /* 0x004 */ int x;                                // 0x4
    /* 0x008 */ int y;                                // 0x4
    /* 0x00C */ int w;                                // 0x4
    /* 0x010 */ int h;                                // 0x4
    /* 0x014 */ int z;                                // 0x4
} anon_10_48;


/* variables (3) */
static short svr_tbl_minfo_num[75];                              /* @0x002B94A0 size 0x96 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (4) */
void NetGameWinInterVSMain(struct _NETWORK_W *);                 /* @0x001F7310 */
void NetSysInit(struct _NETWORK_W *);                            /* @0x00224330 */
void NetGameMenuInit(struct _NETWORK_W *);                       /* @0x001FB360 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */

/* functions defined (4) */
int NetGameGetMusicNum(int num);                                 /* 0x001F6770-0x001F6794 lines 746-751 */
void NetGameReverseMenu(struct _NETWORK_W *netw);                /* 0x001F67A0-0x001F67E0 lines 627-645 */
void NetGameEnd(struct _NETWORK_W *netw);                        /* 0x001F67E0-0x001F6830 lines 612-618 */
void NetGameInit(struct _NETWORK_W *netw);                       /* 0x001F6830-0x001F7294 lines 13-599 */

#endif /* DDR_UNIT_src_network_net_game_net_game_main_c_H */
