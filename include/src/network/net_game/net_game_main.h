/*
 * C:\work2\usaex2\src\network\net_game\net_game_main.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x001F6770-0x001F7294
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_game_net_game_main_c_H
#define DDR_UNIT_src_network_net_game_net_game_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet_playerdata.h"
#include "types/g_game_w.h"

/* anonymous types (12) */

/* anon_0_48 -- @anon0, 0x8 bytes, net_game_main.c (DIE 0x9937E) */
struct anon_0_48 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_48 -- @anon1, 0x1048 bytes, net_game_main.c (DIE 0x9A432) */
struct anon_1_48 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_2_48 -- @anon2, 0x4 bytes, net_game_main.c (DIE 0x9CF60) */
struct anon_2_48 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_4_48 -- @anon4, 0x4 bytes, net_game_main.c (DIE 0x9F06B) */
struct anon_4_48 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_6_48 -- @anon6, 0x4 bytes, net_game_main.c (DIE 0x9F8FC) */
struct anon_6_48 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_3_48 -- @anon3, 0x4 bytes, net_game_main.c (DIE 0x9EE24) */
union anon_3_48 {   // size 0x4
    /* 0x000 */ struct anon_4_48 S_un_b;              // 0x4
    /* 0x000 */ struct anon_6_48 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_7_48 -- @anon7, 0x4 bytes, net_game_main.c (DIE 0xA0C22) */
union anon_7_48 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_8_48 -- @anon8, 0x10 bytes, net_game_main.c (DIE 0xA1E51) */
struct anon_8_48 {   // size 0x10
    /* 0x000 */ union anon_7_48 x0;                   // 0x4
    /* 0x004 */ union anon_7_48 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_5_48 -- @anon5, 0x184 bytes, net_game_main.c (DIE 0x9F132) */
struct anon_5_48 {   // size 0x184
    /* 0x000 */ struct anon_8_48 line_a[8];           // 0x80
    /* 0x080 */ struct anon_8_48 line_b[8];           // 0x80
    /* 0x100 */ struct anon_8_48 line_c[8];           // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_9_48 -- @anon9, 0x14 bytes, net_game_main.c (DIE 0xA2F28) */
struct anon_9_48 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};

/* anon_10_48 -- @anon10, 0x18 bytes, net_game_main.c (DIE 0xA32B7) */
struct anon_10_48 {   // size 0x18
    /* 0x000 */ void *func;                           // 0x4
    /* 0x004 */ int x;                                // 0x4
    /* 0x008 */ int y;                                // 0x4
    /* 0x00C */ int w;                                // 0x4
    /* 0x010 */ int h;                                // 0x4
    /* 0x014 */ int z;                                // 0x4
};

/* anon_11_48 -- @anon11, 0x10 bytes, net_game_main.c (DIE 0xA34F5) */
struct anon_11_48 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};


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
