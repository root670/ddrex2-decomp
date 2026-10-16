/*
 * C:\work2\usaex2\src\network\usa_client\ddrex2_usa_gate.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 8 functions, code 0x007F5A60-0x007F5E08
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_network_usa_client_ddrex2_usa_gate_c_H
#define DDR_UNIT_src_network_usa_client_ddrex2_usa_gate_c_H

#include "types/_ddrnet_con.h"
#include "types/_ddrnet_info.h"
#include "types/_ddrnet_infolist.h"
#include "types/_ddrnet_svr.h"
#include "types/_ddrnet_svrlist.h"
#include "types/_mio_message.h"

/* anonymous types (3) */

/* anon_1_204 -- @anon1, 0x4 bytes, ddrex2_usa_gate.c (DIE 0x395130) */
struct anon_1_204 {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
};

/* anon_2_204 -- @anon2, 0x4 bytes, ddrex2_usa_gate.c (DIE 0x3951D3) */
struct anon_2_204 {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
};

/* anon_0_204 -- @anon0, 0x4 bytes, ddrex2_usa_gate.c (DIE 0x3950A4) */
union anon_0_204 {   // size 0x4
    /* 0x000 */ struct anon_1_204 S_un_b;             // 0x4
    /* 0x000 */ struct anon_2_204 S_un_w;             // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
};


/* functions defined (8) */
int ddrnet_gate_res_infolist(struct _mio_message *msg, struct _ddrnet_infolist *list); /* 0x007F5A60-0x007F5B60 lines 201-224 */
int ddrnet_gate_res_infoliststart(struct _mio_message *msg, int *result); /* 0x007F5B60-0x007F5B6C lines 191-191 */
int ddrnet_gate_req_infolist(struct _ddrnet_con *con);           /* 0x007F5B70-0x007F5B78 lines 178-178 */
int ddrnet_gate_res_svrtime(struct _mio_message *msg, unsigned int *time); /* 0x007F5B80-0x007F5BFC lines 150-165 */
int ddrnet_gate_req_svrtime(struct _ddrnet_con *con);            /* 0x007F5C00-0x007F5C08 lines 140-140 */
int ddrnet_gate_res_svrlist(struct _mio_message *msg, struct _ddrnet_svrlist *list); /* 0x007F5C10-0x007F5D20 lines 101-128 */
int ddrnet_gate_res_svrliststart(struct _mio_message *msg, struct _ddrnet_svrlist *list, int *result); /* 0x007F5D20-0x007F5E00 lines 64-93 */
int ddrnet_gate_req_svrlist(struct _ddrnet_con *con);            /* 0x007F5E00-0x007F5E08 lines 53-53 */

#endif /* DDR_UNIT_src_network_usa_client_ddrex2_usa_gate_c_H */
