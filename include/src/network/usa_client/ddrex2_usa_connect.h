/*
 * C:\work2\usaex2\src\network\usa_client\ddrex2_usa_connect.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 8 functions, code 0x007F53C0-0x007F5A5C
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_network_usa_client_ddrex2_usa_connect_c_H
#define DDR_UNIT_src_network_usa_client_ddrex2_usa_connect_c_H

#include "types/_ddrnet.h"
#include "types/_ddrnet_con.h"
#include "types/_mio_message.h"

/* anonymous types (2) */

/* anon_2_203 -- @anon2, 0x4 bytes, ddrex2_usa_connect.c (DIE 0x39391F) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned char s_b1;                   // 0x1
    /* 0x001 */ unsigned char s_b2;                   // 0x1
    /* 0x002 */ unsigned char s_b3;                   // 0x1
    /* 0x003 */ unsigned char s_b4;                   // 0x1
} anon_2_203;

/* anon_3_203 -- @anon3, 0x4 bytes, ddrex2_usa_connect.c (DIE 0x393A54) */
typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_3_203;


/* variables (2) */
static int tocount;                                              /* @0x002DE634 size 0x4 */
static int connect_phase;                                        /* @0x002DE638 size 0x4 */

/* functions defined (8) */
void ddrnet_close_all_connection(struct _ddrnet *pn);            /* 0x007F53C0-0x007F5458 lines 394-404 */
void ddrnet_close_connection(struct _ddrnet *pn, int stype);     /* 0x007F5460-0x007F54FC lines 372-389 */
void ddrnet_init_blowfish(struct _ddrnet *work);                 /* 0x007F5500-0x007F554C lines 348-366 */
int ddrnet_send_message(struct _mio_message *msg, struct _ddrnet_con *pcon); /* 0x007F5550-0x007F5588 lines 331-342 */
int ddrnet_recv_message(struct _mio_message *msg, struct _ddrnet_con *pcon); /* 0x007F5590-0x007F5644 lines 301-325 */
int ddrnet_disconnect(struct _ddrnet_con *pcon);                 /* 0x007F5650-0x007F56D0 lines 217-238 */
int ddrnet_connect_nb(char *servername, int port, struct _ddrnet_con *pcon, int sec_tout); /* 0x007F56D0-0x007F59D4 lines 86-211 */
int ddrnet_connect_server_by_index(struct _ddrnet *pn, int index, int sec_tout); /* 0x007F59E0-0x007F5A5C lines 59-78 */

#endif /* DDR_UNIT_src_network_usa_client_ddrex2_usa_connect_c_H */
