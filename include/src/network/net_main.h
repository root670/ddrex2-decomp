/*
 * C:\work2\usaex2\src\network\net_main.c
 * MW MIPS C Compiler, overlay main; 7 functions, code 0x001EB010-0x001EB9C0
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_main_c_H
#define DDR_UNIT_src_network_net_main_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"
#include "types/g_game_w.h"

/* anonymous types (11) */

/* anon_0_43 -- @anon0, 0x10 bytes, net_main.c (DIE 0x773C3) */
struct anon_0_43 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};

/* anon_1_43 -- @anon1, 0x8 bytes, net_main.c (DIE 0x785BB) */
struct anon_1_43 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_2_43 -- @anon2, 0x1048 bytes, net_main.c (DIE 0x788DB) */
struct anon_2_43 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_3_43 -- @anon3, 0x4 bytes, net_main.c (DIE 0x7AC6A) */
struct anon_3_43 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_8_43 -- @anon8, 0x4 bytes, net_main.c (DIE 0x7F319) */
union anon_8_43 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_9_43 -- @anon9, 0x10 bytes, net_main.c (DIE 0x7F909) */
struct anon_9_43 {   // size 0x10
    /* 0x000 */ union anon_8_43 x0;                   // 0x4
    /* 0x004 */ union anon_8_43 y0;                   // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
};

/* anon_4_43 -- @anon4, 0x184 bytes, net_main.c (DIE 0x7C6B6) */
struct anon_4_43 {   // size 0x184
    /* 0x000 */ struct anon_9_43 line_a[8];           // 0x80
    /* 0x080 */ struct anon_9_43 line_b[8];           // 0x80
    /* 0x100 */ struct anon_9_43 line_c[8];           // 0x80
    /* 0x180 */ int num;                              // 0x4
};

/* anon_6_43 -- @anon6, 0x4 bytes, net_main.c (DIE 0x7CD1E) */
struct anon_6_43 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_7_43 -- @anon7, 0x4 bytes, net_main.c (DIE 0x7EE6A) */
struct anon_7_43 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_5_43 -- @anon5, 0x4 bytes, net_main.c (DIE 0x7CC92) */
union anon_5_43 {   // size 0x4
    /* 0x000 */ struct anon_6_43 S_un_b;              // 0x4
    /* 0x000 */ struct anon_7_43 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_10_43 -- @anon10, 0x14 bytes, net_main.c (DIE 0x80352) */
struct anon_10_43 {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
};


/* variables (3) */
static int test_shutdown;                                        /* @0x002DE504 size 0x4 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
struct g_game_w g_game_w;                                        /* @0x00607A70 size 0xACDC4 */

/* functions referenced (5) */
void NetToSysInit(struct _NETWORK_W *);                          /* @0x001EB340 */
void NetSysTopInit2(struct _NETWORK_W *);                        /* @0x00226380 */
void NetGameInit(struct _NETWORK_W *);                           /* @0x001F6830 */
void NetSysInit(struct _NETWORK_W *);                            /* @0x00224330 */
void NetSysEnd(struct _NETWORK_W *);                             /* @0x00224270 */

/* functions defined (7) */
char NetPadCon(unsigned int key);                                /* 0x001EB010-0x001EB198 lines 288-312 */
void NetToLogout(struct _NETWORK_W *netw);                       /* 0x001EB1A0-0x001EB260 lines 246-262 */
void NetToGameInit(struct _NETWORK_W *netw);                     /* 0x001EB260-0x001EB340 lines 209-241 */
void NetToSysInit(struct _NETWORK_W *netw);                      /* 0x001EB340-0x001EB460 lines 153-205 */
void NetEnd(void);                                               /* 0x001EB460-0x001EB4A4 lines 142-148 */
int NetMain(void);                                               /* 0x001EB4B0-0x001EB92C lines 64-138 */
void NetInit(void);                                              /* 0x001EB930-0x001EB9C0 lines 35-60 */

#endif /* DDR_UNIT_src_network_net_main_c_H */
