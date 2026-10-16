/*
 * C:\work2\usaex2\src\network\net_game\net_game_list.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x002015B0-0x00202834
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_list_c_H
#define DDR_UNIT_src_network_net_game_net_game_list_c_H

#include "types/_CWS_WIN_W.h"
#include "types/_NETWORK_W.h"
#include "types/_NSV_USER_FILE_WORK.h"
#include "types/_NS_NET_INFO_W.h"

/* anonymous types (6) */

/* anon_0_57 -- @anon0, 0x8 bytes, net_game_list.c (DIE 0xD5703) */
struct anon_0_57 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_57 -- @anon1, 0x1048 bytes, net_game_list.c (DIE 0xD59F1) */
struct anon_1_57 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_3_57 -- @anon3, 0x4 bytes, net_game_list.c (DIE 0xDA381) */
struct anon_3_57 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_4_57 -- @anon4, 0x4 bytes, net_game_list.c (DIE 0xDA99A) */
struct anon_4_57 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_2_57 -- @anon2, 0x4 bytes, net_game_list.c (DIE 0xDA13A) */
union anon_2_57 {   // size 0x4
    /* 0x000 */ struct anon_3_57 S_un_b;              // 0x4
    /* 0x000 */ struct anon_4_57 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_5_57 -- @anon5, 0x10 bytes, net_game_list.c (DIE 0xDC3AD) */
struct anon_5_57 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};


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
