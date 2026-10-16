/*
 * C:\work2\usaex2\src\network\net_grf.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001EBD40-0x001EBDF8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_grf_c_H
#define DDR_UNIT_src_network_net_grf_c_H

/* anonymous types (2) */

/* anon_1_45 -- @anon1, 0x4 bytes, net_grf.c (DIE 0x85255) */
union anon_1_45 {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
};

/* anon_0_45 -- @anon0, 0x34 bytes, net_grf.c (DIE 0x84F7F) */
struct anon_0_45 {   // size 0x34
    /* 0x000 */ union anon_1_45 x0;                   // 0x4
    /* 0x004 */ union anon_1_45 y0;                   // 0x4
    /* 0x008 */ union anon_1_45 x1;                   // 0x4
    /* 0x00C */ union anon_1_45 y1;                   // 0x4
    /* 0x010 */ union anon_1_45 x2;                   // 0x4
    /* 0x014 */ union anon_1_45 y2;                   // 0x4
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
};


/* variables (1) */
static char dancer_num[22];                                      /* @0x002B8C20 size 0x16 */

/* functions defined (2) */
int peerPrintf(char *format);                                    /* 0x001EBD40-0x001EBDA8 lines 69-80 */
int NetGrfGetDancerIDToNumberPoint(int dancer_id);               /* 0x001EBDB0-0x001EBDF8 lines 64-65 */

#endif /* DDR_UNIT_src_network_net_grf_c_H */
