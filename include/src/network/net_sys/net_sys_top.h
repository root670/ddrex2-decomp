/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_top.c
 * MW MIPS C Compiler, overlay main; 4 functions, code 0x00225C60-0x00226874
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_sys_net_sys_top_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_top_c_H

#include "types/_NETWORK_W.h"
#include "types/_NS_NET_INFO_W.h"

/* anonymous types (6) */

/* anon_0_80 -- @anon0, 0x8 bytes, net_sys_top.c (DIE 0x15D98E) */
struct anon_0_80 {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
};

/* anon_1_80 -- @anon1, 0x1048 bytes, net_sys_top.c (DIE 0x15E0F9) */
struct anon_1_80 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_3_80 -- @anon3, 0x4 bytes, net_sys_top.c (DIE 0x1626E5) */
struct anon_3_80 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_4_80 -- @anon4, 0x4 bytes, net_sys_top.c (DIE 0x162C60) */
struct anon_4_80 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_2_80 -- @anon2, 0x4 bytes, net_sys_top.c (DIE 0x1624A3) */
union anon_2_80 {   // size 0x4
    /* 0x000 */ struct anon_3_80 S_un_b;              // 0x4
    /* 0x000 */ struct anon_4_80 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};

/* anon_5_80 -- @anon5, 0x10 bytes, net_sys_top.c (DIE 0x16458B) */
struct anon_5_80 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};


/* variables (1) */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions referenced (5) */
void NetSysEnd(struct _NETWORK_W *);                             /* @0x00224270 */
void NetSysRuleInit(struct _NETWORK_W *);                        /* @0x00228140 */
void NetCnfMain(struct _NETWORK_W *);                            /* @0x00802460 */
void NetSysTopKey(struct _NETWORK_W *);                          /* @0x00225C60 */
void NetSysTopMain(struct _NETWORK_W *);                         /* @0x00225EB0 */

/* functions defined (4) */
static void NetSysTopKey(struct _NETWORK_W *netw);               /* 0x00225C60-0x00225EA8 lines 317-349 */
static void NetSysTopMain(struct _NETWORK_W *netw);              /* 0x00225EB0-0x00226380 lines 163-310 */
void NetSysTopInit2(struct _NETWORK_W *netw);                    /* 0x00226380-0x002265FC lines 97-155 */
void NetSysTopInit(struct _NETWORK_W *netw);                     /* 0x00226600-0x00226874 lines 35-93 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_top_c_H */
