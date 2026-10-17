/*
 * C:\work2\usaex2\src\network\net_game\net_game_main.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x001F6770-0x001F7294
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_main_c_H
#define DDR_UNIT_src_network_net_game_net_game_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_playerdata.h"
#include "types/g_game_w.h"

/* anonymous types (5) */

/* anon_4_48 -- @anon4, 0x4 bytes, net_game_main.c (DIE 0x9F06B) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
} anon_4_48;

/* anon_6_48 -- @anon6, 0x4 bytes, net_game_main.c (DIE 0x9F8FC) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_6_48;

/* anon_7_48 -- @anon7, 0x4 bytes, net_game_main.c (DIE 0xA0C22) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_7_48;

/* anon_8_48 -- @anon8, 0x10 bytes, net_game_main.c (DIE 0xA1E51) */
typedef struct {   // size 0x10
    /* 0x000 */ anon_7_48 x0;                         // 0x4
    /* 0x004 */ anon_7_48 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_8_48;

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

/* functions referenced (6) */
void NetGameWinInterVSMain(struct _NETWORK_W *);                 /* @0x001F7310 */
void NetSysInit(struct _NETWORK_W *);                            /* @0x00224330 */
void NetGameEnd(struct _NETWORK_W *);                            /* @0x001F67E0 */
void NetGameReverseMenu(struct _NETWORK_W *);                    /* @0x001F67A0 */
void NetGameMenuInit(struct _NETWORK_W *);                       /* @0x001FB360 */
void NetToLogout(struct _NETWORK_W *);                           /* @0x001EB1A0 */

/* functions defined (4) */
int NetGameGetMusicNum(int num);                                 /* 0x001F6770-0x001F6794 lines 746-751 */
void NetGameReverseMenu(struct _NETWORK_W *netw);                /* 0x001F67A0-0x001F67E0 lines 627-645 */
void NetGameEnd(struct _NETWORK_W *netw);                        /* 0x001F67E0-0x001F6830 lines 612-618 */
void NetGameInit(struct _NETWORK_W *netw);                       /* 0x001F6830-0x001F7294 lines 13-599 */

#endif /* DDR_UNIT_src_network_net_game_net_game_main_c_H */
