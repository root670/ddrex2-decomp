/*
 * C:\work2\usaex2\src\network\usa_client\ddrex2_usa_challenge.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 16 functions, code 0x007F49E0-0x007F53B4
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
#ifndef DDR_UNIT_src_network_usa_client_ddrex2_usa_challenge_c_H
#define DDR_UNIT_src_network_usa_client_ddrex2_usa_challenge_c_H

#include "types/_ddrnet_con.h"
#include "types/_ddrnet_ranking_column.h"
#include "types/_mio_message.h"
#include "types/ddrnet_rc_info.h"
#include "types/ddrnet_rc_music.h"

/* functions defined (16) */
int ddrnet_rc_res_rcidlist(struct _mio_message *msg, unsigned char *num, unsigned char *rc_id); /* 0x007F49E0-0x007F4ABC lines 458-478 */
int ddrnet_rc_req_rcidlist(struct _ddrnet_con *con);             /* 0x007F4AC0-0x007F4AC8 lines 447-447 */
int ddrnet_rc_recv_week(struct _mio_message *msg, unsigned char *week); /* 0x007F4AD0-0x007F4B4C lines 423-437 */
int ddrnet_rc_res_schedule(struct _mio_message *msg, unsigned char *week, unsigned int *time, unsigned int *term); /* 0x007F4B50-0x007F4C0C lines 397-415 */
int ddrnet_rc_req_schedule(struct _ddrnet_con *con);             /* 0x007F4C10-0x007F4C18 lines 385-385 */
int ddrnet_res_ranking(struct _mio_message *msg, int *count, struct _ddrnet_ranking_column *data); /* 0x007F4C20-0x007F4D4C lines 342-375 */
int ddrnet_res_ranking_start(struct _mio_message *msg, int *result, int *count, struct _ddrnet_ranking_column *data); /* 0x007F4D50-0x007F4DAC lines 321-329 */
int ddrnet_req_ranking(struct _ddrnet_con *con, unsigned char type, short week, unsigned char sub, int from, int num); /* 0x007F4DB0-0x007F4EF0 lines 260-305 */
int ddrnet_rc_res_regist(struct _mio_message *msg, int *result); /* 0x007F4EF0-0x007F4EFC lines 235-235 */
int ddrnet_rc_req_regist(struct _ddrnet_con *con, unsigned int pid, int score, int time, short combo, short gauge); /* 0x007F4F00-0x007F4FA4 lines 205-224 */
int ddrnet_rc_res_entry(struct _mio_message *msg, int *result);  /* 0x007F4FB0-0x007F4FBC lines 190-190 */
int ddrnet_rc_req_entry(struct _ddrnet_con *con, unsigned int pid, unsigned char type); /* 0x007F4FC0-0x007F5034 lines 163-179 */
int ddrnet_rc_res_trycount(struct _mio_message *msg, int *result, signed char *count); /* 0x007F5040-0x007F5100 lines 137-153 */
int ddrnet_rc_req_trycount(struct _ddrnet_con *con, unsigned int pid); /* 0x007F5100-0x007F5164 lines 113-128 */
int ddrnet_rc_res_info(struct _mio_message *msg, int *result, struct ddrnet_rc_info *rc_info); /* 0x007F5170-0x007F5334 lines 59-105 */
int ddrnet_rc_req_info(struct _ddrnet_con *con, unsigned char type, unsigned char week); /* 0x007F5340-0x007F53B4 lines 33-49 */

#endif /* DDR_UNIT_src_network_usa_client_ddrex2_usa_challenge_c_H */
