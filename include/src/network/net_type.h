/*
 * C:\work2\usaex2\src\network\net_type.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001EB9C0-0x001EBD40
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
#ifndef DDR_UNIT_src_network_net_type_c_H
#define DDR_UNIT_src_network_net_type_c_H

#include "types/_NS_NET_INFO_W.h"
#include "types/_NetPacketHeader.h"
#include "types/_ddrnet_con.h"

/* anonymous types (1) */

/* anon_x82a28_44 -- @enum, 0x1 bytes, net_type.c (DIE 0x82A28) */
typedef enum {   // size 0x1
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
} anon_x82a28_44;


/* variables (2) */
static unsigned int net_type_work_size[9];                       /* @0x002B8BF0 size 0x24 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */

/* functions defined (5) */
void *NsNetP2PRecv(anon_x82a28_44 type);                         /* 0x001EB9C0-0x001EB9F0 lines 294-300 */
int NetP2PSendProgram(anon_x82a28_44 type, void *memory);        /* 0x001EB9F0-0x001EBAC8 lines 224-289 */
void *NetRecvProgramData(anon_x82a28_44 type, int counter, unsigned int flag); /* 0x001EBAD0-0x001EBB64 lines 172-214 */
int NetSendPicture(void);                                        /* 0x001EBB70-0x001EBC24 lines 81-163 */
int NetSendProgram(anon_x82a28_44 type, void *memory);           /* 0x001EBC30-0x001EBD40 lines 41-74 */

#endif /* DDR_UNIT_src_network_net_type_c_H */
