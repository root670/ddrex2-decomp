/*
 * C:\work2\usaex2\src\network\usa_client\ddrex2_usa_util.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 11 functions, code 0x007F8890-0x007F98F0
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
#ifndef DDR_UNIT_src_network_usa_client_ddrex2_usa_util_c_H
#define DDR_UNIT_src_network_usa_client_ddrex2_usa_util_c_H

#include "types/_NS_NET_INFO_W.h"
#include "types/_ddrnet.h"
#include "types/_ddrnet_con.h"
#include "types/_mio_message.h"

/* variables (4) */
static void (*msg_rcv_proc)(struct _ddrnet *, int);              /* @0x002DE63C size 0x4 */
static void (*msg_err_proc)(struct _ddrnet *, int, int);         /* @0x002DE640 size 0x4 */
struct _NS_NET_INFO_W *netiw;                                    /* @0x002DDA84 size 0x4 */
char lobby_proc_event_flg;                                       /* @0x002DE644 size 0x1 */

/* functions defined (11) */
int ddrnet_only_get_result(struct _mio_message *msg, int msgid, int *result); /* 0x007F8890-0x007F8914 lines 837-853 */
int ddrnet_only_request(struct _ddrnet_con *con, int msgid);     /* 0x007F8920-0x007F8974 lines 817-828 */
int ddrnet_check_recvtime(struct _ddrnet *pn);                   /* 0x007F8980-0x007F8A20 lines 762-791 */
int ddrnet_send_heartbeat(struct _ddrnet *pn);                   /* 0x007F8A20-0x007F8AD4 lines 715-744 */
int ddrnet_get_svrlistindex_by_type(struct _ddrnet *pn, int svrtype, int *lastindex); /* 0x007F8AE0-0x007F8BA0 lines 676-707 */
int ddrnet_mproc_lobby(struct _ddrnet *pn);                      /* 0x007F8BA0-0x007F9390 lines 427-664 */
int ddrnet_mproc_acc(struct _ddrnet *pn);                        /* 0x007F9390-0x007F94AC lines 363-421 */
static int ddrnet_mproc_gate(struct _ddrnet *pn);                /* 0x007F94B0-0x007F95C8 lines 291-357 */
int ddrnet_proc_message(struct _ddrnet *ddrnet_);                /* 0x007F95D0-0x007F9788 lines 175-284 */
int ddrnet_connect_gate(struct _ddrnet *ddrnet_, char *addr, int port, int sec_tout); /* 0x007F9790-0x007F97E8 lines 125-143 */
void ddrnet_create(struct _ddrnet **work, void (*mrcvproc)(struct _ddrnet *, int), void (*merrproc)(struct _ddrnet *, int, int)); /* 0x007F97F0-0x007F98F0 lines 72-95 */

#endif /* DDR_UNIT_src_network_usa_client_ddrex2_usa_util_c_H */
