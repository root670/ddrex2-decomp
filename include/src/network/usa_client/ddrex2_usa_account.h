/*
 * C:\work2\usaex2\src\network\usa_client\ddrex2_usa_account.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 10 functions, code 0x007F44A0-0x007F49D8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_usa_client_ddrex2_usa_account_c_H
#define DDR_UNIT_src_network_usa_client_ddrex2_usa_account_c_H

#include "types/_ddrnet.h"
#include "types/_ddrnet_con.h"
#include "types/_ddrnet_playerselect.h"
#include "types/_ddrnet_playerselectlist.h"
#include "types/_mio_message.h"

/* anonymous types (3) */

/* anon_2_201 -- @anon2, 0x4 bytes, ddrex2_usa_account.c (DIE 0x38C3FC) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
} anon_2_201;

/* anon_3_201 -- @anon3, 0x4 bytes, ddrex2_usa_account.c (DIE 0x38C531) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_3_201;

/* anon_4_201 -- @anon4, 0x58 bytes, ddrex2_usa_account.c (DIE 0x38DB77) */
typedef struct {   // size 0x58
    /* 0x000 */ unsigned int state[4];                // 0x10
    /* 0x010 */ unsigned int count[2];                // 0x8
    /* 0x018 */ unsigned char buffer[64];             // 0x40
} anon_4_201;


/* functions defined (10) */
int ddrnet_acc_res_delplayer(struct _mio_message *msg, int *result); /* 0x007F44A0-0x007F44AC lines 318-318 */
int ddrnet_acc_req_delplayer(struct _ddrnet_con *con, signed char index); /* 0x007F44B0-0x007F4514 lines 292-306 */
int ddrnet_acc_res_regplayer(struct _mio_message *msg, int *result); /* 0x007F4520-0x007F452C lines 282-282 */
int ddrnet_acc_req_regplayer(struct _ddrnet_con *con, signed char index, unsigned char *pname, signed char dancer); /* 0x007F4530-0x007F45C0 lines 250-268 */
int ddrnet_acc_res_playerlist(struct _mio_message *msg, struct _ddrnet_playerselectlist *plist, int *result); /* 0x007F45C0-0x007F471C lines 200-241 */
int ddrnet_acc_req_playerlist(struct _ddrnet_con *con);          /* 0x007F4720-0x007F4728 lines 189-189 */
int ddrnet_res_auth(struct _mio_message *msg, int *result);      /* 0x007F4730-0x007F4754 lines 174-179 */
int ddrnet_req_auth(struct _ddrnet *work, struct _ddrnet_con *con, unsigned char *uname, unsigned char *passwd, unsigned char *ccode); /* 0x007F4760-0x007F4930 lines 89-162 */
int ddrnet_res_ccode(struct _mio_message *msg, unsigned char *ccode); /* 0x007F4930-0x007F49CC lines 44-78 */
int ddrnet_req_ccode(struct _ddrnet_con *con);                   /* 0x007F49D0-0x007F49D8 lines 34-34 */

#endif /* DDR_UNIT_src_network_usa_client_ddrex2_usa_account_c_H */
