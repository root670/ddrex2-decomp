/*
 * C:\work2\usaex2\src\network\net_sys\net_sys_info.c
 * MW MIPS C Compiler, overlay main; 6 functions, code 0x002285C0-0x002293DC
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
#ifndef DDR_UNIT_src_network_net_sys_net_sys_info_c_H
#define DDR_UNIT_src_network_net_sys_net_sys_info_c_H

#include "types/_NETWORK_W.h"

/* anonymous types (3) */

/* anon_3_84 -- @anon3, 0x4 bytes, net_sys_info.c (DIE 0x1778D1) */
typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_3_84;

/* anon_1_84 -- @anon1, 0x34 bytes, net_sys_info.c (DIE 0x175ADF) */
typedef struct {   // size 0x34
    /* 0x000 */ anon_3_84 x0;                         // 0x4
    /* 0x004 */ anon_3_84 y0;                         // 0x4
    /* 0x008 */ anon_3_84 x1;                         // 0x4
    /* 0x00C */ anon_3_84 y1;                         // 0x4
    /* 0x010 */ anon_3_84 x2;                         // 0x4
    /* 0x014 */ anon_3_84 y2;                         // 0x4
    /* 0x018 */ unsigned int z0;                      // 0x4
    /* 0x01C */ unsigned int z1;                      // 0x4
    /* 0x020 */ unsigned int z2;                      // 0x4
    /* 0x024 */ unsigned char r0;                     // 0x1
    /* 0x025 */ unsigned char g0;                     // 0x1
    /* 0x026 */ unsigned char b0;                     // 0x1
    /* 0x027 */ unsigned char a0;                     // 0x1
    /* 0x028 */ unsigned char r1;                     // 0x1
    /* 0x029 */ unsigned char g1;                     // 0x1
    /* 0x02A */ unsigned char b1;                     // 0x1
    /* 0x02B */ unsigned char a1;                     // 0x1
    /* 0x02C */ unsigned char r2;                     // 0x1
    /* 0x02D */ unsigned char g2;                     // 0x1
    /* 0x02E */ unsigned char b2;                     // 0x1
    /* 0x02F */ unsigned char a2;                     // 0x1
    /* 0x030 */ int flg;                              // 0x4
} anon_1_84;

/* anon_2_84 -- @anon2, 0x24 bytes, net_sys_info.c (DIE 0x1775CF) */
typedef struct {   // size 0x24
    /* 0x000 */ anon_3_84 x0;                         // 0x4
    /* 0x004 */ anon_3_84 y0;                         // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ float w;                              // 0x4
    /* 0x010 */ float h;                              // 0x4
    /* 0x014 */ float u;                              // 0x4
    /* 0x018 */ float v;                              // 0x4
    /* 0x01C */ unsigned char r0;                     // 0x1
    /* 0x01D */ unsigned char g0;                     // 0x1
    /* 0x01E */ unsigned char b0;                     // 0x1
    /* 0x01F */ unsigned char a0;                     // 0x1
    /* 0x020 */ int flg;                              // 0x4
} anon_2_84;


/* functions referenced (7) */
void NetSysInfoInit(struct _NETWORK_W *);                        /* @0x00229050 */
void NetSysInfoDispInit(struct _NETWORK_W *);                    /* @0x00228960 */
void NetSysInfoDispKey(struct _NETWORK_W *);                     /* @0x002285C0 */
void NetSysInfoDispMain(struct _NETWORK_W *);                    /* @0x002287E0 */
void NetSysMenuInit2(struct _NETWORK_W *);                       /* @0x00224AD0 */
void NetSysInfoKey(struct _NETWORK_W *);                         /* @0x00228AC0 */
void NetSysInfoMain(struct _NETWORK_W *);                        /* @0x00228CB0 */

/* functions defined (6) */
static void NetSysInfoDispKey(struct _NETWORK_W *netw);          /* 0x002285C0-0x002287DC lines 483-521 */
static void NetSysInfoDispMain(struct _NETWORK_W *netw);         /* 0x002287E0-0x00228960 lines 381-479 */
static void NetSysInfoDispInit(struct _NETWORK_W *netw);         /* 0x00228960-0x00228AC0 lines 327-376 */
static void NetSysInfoKey(struct _NETWORK_W *netw);              /* 0x00228AC0-0x00228CA8 lines 280-318 */
static void NetSysInfoMain(struct _NETWORK_W *netw);             /* 0x00228CB0-0x0022904C lines 171-275 */
void NetSysInfoInit(struct _NETWORK_W *netw);                    /* 0x00229050-0x002293DC lines 98-166 */

#endif /* DDR_UNIT_src_network_net_sys_net_sys_info_c_H */
