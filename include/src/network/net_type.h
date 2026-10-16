/*
 * C:\work2\usaex2\src\network\net_type.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001EB9C0-0x001EBD40
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_net_type_c_H
#define DDR_UNIT_src_network_net_type_c_H

#include "types/_NS_NET_INFO_W.h"
#include "types/_NetPacketHeader.h"
#include "types/_ddrnet_con.h"

/* anonymous types (6) */

/* anon_0_44 -- @anon0, 0x10 bytes, net_type.c (DIE 0x8164D) */
struct anon_0_44 {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
};

/* anon_1_44 -- @anon1, 0x1048 bytes, net_type.c (DIE 0x818D2) */
struct anon_1_44 {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
};

/* anon_x82a28_44 -- @enum, 0x1 bytes, net_type.c (DIE 0x82A28) */
enum anon_x82a28_44 {   // size 0x1
    NET_WORK_TYPE_NON = 0,
    NET_WORK_TYPE_RSEQ_BUF = 1,
    NET_WORK_TYPE_PICT = 2,
    NET_WORK_TYPE_OPT_REQ = 3,
    NET_WORK_TYPE_OPT_RES = 4,
    NET_WORK_TYPE_RESULT_REQ = 5,
    NET_WORK_TYPE_RESULT_RES = 6,
    NET_WORK_TYPE_HEART_BEAT = 7,
    NET_WORK_TYPE_DEAD = 8,
    NET_WORK_TYPE_MAX = 9,
};

/* anon_3_44 -- @anon3, 0x4 bytes, net_type.c (DIE 0x834DA) */
struct anon_3_44 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_4_44 -- @anon4, 0x4 bytes, net_type.c (DIE 0x83971) */
struct anon_4_44 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_2_44 -- @anon2, 0x4 bytes, net_type.c (DIE 0x8344E) */
union anon_2_44 {   // size 0x4
    /* 0x000 */ struct anon_3_44 S_un_b;              // 0x4
    /* 0x000 */ struct anon_4_44 S_un_w;              // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};


/* variables (2) */
static unsigned int net_type_work_size[9];                       /* @0x002B8BF0 size 0x24 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions defined (5) */
void *NsNetP2PRecv(enum anon_x82a28_44 type);                    /* 0x001EB9C0-0x001EB9F0 lines 294-300 */
int NetP2PSendProgram(enum anon_x82a28_44 type, void *memory);   /* 0x001EB9F0-0x001EBAC8 lines 224-289 */
void *NetRecvProgramData(enum anon_x82a28_44 type, int counter, unsigned int flag); /* 0x001EBAD0-0x001EBB64 lines 172-214 */
int NetSendPicture(void);                                        /* 0x001EBB70-0x001EBC24 lines 81-163 */
int NetSendProgram(enum anon_x82a28_44 type, void *memory);      /* 0x001EBC30-0x001EBD40 lines 41-74 */

#endif /* DDR_UNIT_src_network_net_type_c_H */
