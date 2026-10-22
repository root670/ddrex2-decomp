/*
 * C:\work2\usaex2\src\network\usa_client\ddrex2_usa_lobby.c
 * MW MIPS C Compiler, overlay net_rel4cd.prg; 52 functions, code 0x007F69C0-0x007F8884
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
#ifndef DDR_UNIT_src_network_usa_client_ddrex2_usa_lobby_c_H
#define DDR_UNIT_src_network_usa_client_ddrex2_usa_lobby_c_H

#include "types/_ddrnet_block.h"
#include "types/_ddrnet_blocklist.h"
#include "types/_ddrnet_con.h"
#include "types/_ddrnet_opponent.h"
#include "types/_ddrnet_playerdata.h"
#include "types/_ddrnet_playerdata_h2h.h"
#include "types/_ddrnet_playerdata_pointrank.h"
#include "types/_ddrnet_playerdata_rankchallenge.h"
#include "types/_ddrnet_playerinblock.h"
#include "types/_ddrnet_playerlistinblock.h"
#include "types/_ddrnet_result.h"
#include "types/_ddrnet_room.h"
#include "types/_ddrnet_roomlist.h"
#include "types/_ddrnet_rule_mask.h"
#include "types/_mio_message.h"

/* functions defined (52) */
int ddrnet_lobby_res_rulemask(struct _mio_message *msg, int *result, struct _ddrnet_rule_mask *mask); /* 0x007F69C0-0x007F6A90 lines 1564-1587 */
int ddrnet_lobby_req_rulemask(struct _ddrnet_con *con);          /* 0x007F6A90-0x007F6A98 lines 1552-1552 */
int ddrnet_lobby_res_set_ipaddress(struct _mio_message *msg, int *result); /* 0x007F6AA0-0x007F6AAC lines 1539-1539 */
int ddrnet_lobby_req_set_ipaddress(struct _ddrnet_con *con, unsigned char index, char *ip_int, char *ip_ext, unsigned short port_int, unsigned short port_ext, unsigned char nat); /* 0x007F6AB0-0x007F6B7C lines 1507-1527 */
int ddrnet_lobby_res_log_challenge_data(struct _mio_message *msg, int *count, struct _ddrnet_playerdata_rankchallenge **data); /* 0x007F6B80-0x007F6C9C lines 1467-1493 */
int ddrnet_lobby_res_log_challenge_start(struct _mio_message *msg, int *result, int *count, struct _ddrnet_playerdata_rankchallenge *data); /* 0x007F6CA0-0x007F6D88 lines 1430-1458 */
int ddrnet_lobby_req_log_challenge(struct _ddrnet_con *con);     /* 0x007F6D90-0x007F6D98 lines 1418-1418 */
int ddrnet_lobby_res_log_point_data(struct _mio_message *msg, int *count, struct _ddrnet_playerdata_pointrank **data); /* 0x007F6DA0-0x007F6E7C lines 1386-1408 */
int ddrnet_lobby_res_log_point_start(struct _mio_message *msg, int *result, int *count, struct _ddrnet_playerdata_pointrank *data); /* 0x007F6E80-0x007F6F70 lines 1349-1377 */
int ddrnet_lobby_res_log_h2h_data(struct _mio_message *msg, int *count, struct _ddrnet_playerdata_h2h **data); /* 0x007F6F70-0x007F707C lines 1300-1325 */
int ddrnet_lobby_res_log_h2h_start(struct _mio_message *msg, int *result, int *count, struct _ddrnet_playerdata_h2h *data); /* 0x007F7080-0x007F7170 lines 1263-1291 */
int ddrnet_lobby_req_log_h2h(struct _ddrnet_con *con);           /* 0x007F7170-0x007F7178 lines 1251-1251 */
int ddrnet_lobby_res_set_option(struct _mio_message *msg, int *result); /* 0x007F7180-0x007F718C lines 1239-1239 */
int ddrnet_lobby_recv_resetroom(struct _mio_message *msg, int *result); /* 0x007F7190-0x007F719C lines 1198-1198 */
int ddrnet_lobby_res_set_plopt(struct _mio_message *msg, int *result); /* 0x007F71A0-0x007F71AC lines 1182-1182 */
int ddrnet_lobby_req_set_plopt(struct _ddrnet_con *con, unsigned int pid, unsigned char *option); /* 0x007F71B0-0x007F7230 lines 1154-1170 */
int ddrnet_lobby_res_get_plopt(struct _mio_message *msg, unsigned char *option); /* 0x007F7230-0x007F72BC lines 1128-1145 */
int ddrnet_lobby_req_get_plopt(struct _ddrnet_con *con, unsigned int pid); /* 0x007F72C0-0x007F7324 lines 1105-1120 */
int ddrnet_lobby_recv_matchmake(struct _mio_message *msg, struct _ddrnet_opponent *opponent); /* 0x007F7330-0x007F7454 lines 1070-1097 */
int ddrnet_lobby_res_confiscate(struct _mio_message *msg, int *result); /* 0x007F7460-0x007F746C lines 1060-1060 */
int ddrnet_lobby_req_confiscate(struct _ddrnet_con *con, signed char winner, signed char disconnect); /* 0x007F7470-0x007F74E4 lines 1028-1044 */
int ddrnet_lobby_res_endgame(struct _mio_message *msg, int *result, unsigned char *match_stats); /* 0x007F74F0-0x007F7590 lines 1003-1019 */
int ddrnet_lobby_req_endgame(struct _ddrnet_con *con, struct _ddrnet_result *result); /* 0x007F7590-0x007F768C lines 959-987 */
int ddrnet_lobby_recv_readystatus(struct _mio_message *msg, signed char *status); /* 0x007F7690-0x007F770C lines 925-943 */
int ddrnet_lobby_res_readystatus(struct _mio_message *msg, int *result); /* 0x007F7710-0x007F771C lines 912-912 */
int ddrnet_lobby_send_readystatus(struct _ddrnet_con *con, signed char status); /* 0x007F7720-0x007F7784 lines 881-895 */
int ddrnet_lobby_recv_p2p(struct _mio_message *msg, void *data); /* 0x007F7790-0x007F7824 lines 857-873 */
int ddrnet_lobby_send_p2p(struct _ddrnet_con *con, void *data, int length); /* 0x007F7830-0x007F78C8 lines 828-845 */
int ddrnet_lobby_res_playerinfo(struct _mio_message *msg, int *result, struct _ddrnet_playerdata *data); /* 0x007F78D0-0x007F7ACC lines 760-814 */
int ddrnet_lobby_req_playerinfo(struct _ddrnet_con *con, unsigned int pid); /* 0x007F7AD0-0x007F7B40 lines 732-751 */
int ddrnet_lobby_res_restartautomatch(struct _mio_message *msg, int *result); /* 0x007F7B40-0x007F7B4C lines 721-721 */
int ddrnet_lobby_recv_opponentleaveroom(struct _mio_message *msg, int *result); /* 0x007F7B50-0x007F7B5C lines 690-690 */
int ddrnet_lobby_recv_roomstatusupdate(struct _mio_message *msg, signed char *status); /* 0x007F7B60-0x007F7BDC lines 665-678 */
int ddrnet_lobby_res_gooutroom(struct _mio_message *msg, int *result); /* 0x007F7BE0-0x007F7BEC lines 654-654 */
int ddrnet_lobby_req_gooutroom(struct _ddrnet_con *con);         /* 0x007F7BF0-0x007F7BF8 lines 637-637 */
int ddrnet_lobby_recv_roomlistupdate(struct _mio_message *msg, struct _ddrnet_roomlist *roomlist); /* 0x007F7C00-0x007F7E10 lines 555-626 */
int ddrnet_lobby_recv_roomlistdel(struct _mio_message *msg, struct _ddrnet_roomlist *roomlist); /* 0x007F7E10-0x007F7EDC lines 509-543 */
int ddrnet_lobby_res_createroom(struct _mio_message *msg, int *result); /* 0x007F7EE0-0x007F7EEC lines 495-495 */
int ddrnet_lobby_req_createroom(struct _ddrnet_con *con, unsigned char *roomname, unsigned char rule, unsigned char difficulty); /* 0x007F7EF0-0x007F7FFC lines 448-479 */
int ddrnet_lobby_res_roomlist(struct _mio_message *msg, struct _ddrnet_roomlist *roomlist); /* 0x007F8000-0x007F8134 lines 405-436 */
int ddrnet_lobby_res_roomliststart(struct _mio_message *msg, struct _ddrnet_roomlist *roomlist, int *result); /* 0x007F8140-0x007F8190 lines 382-393 */
int ddrnet_lobby_req_roomlist(struct _ddrnet_con *con);          /* 0x007F8190-0x007F8198 lines 367-367 */
int ddrnet_lobby_recv_blockplistupdate(struct _mio_message *msg, struct _ddrnet_playerlistinblock *playerlist); /* 0x007F81A0-0x007F83B8 lines 288-355 */
int ddrnet_lobby_res_blockplist(struct _mio_message *msg, struct _ddrnet_playerlistinblock *playerlist); /* 0x007F83C0-0x007F8578 lines 228-274 */
int ddrnet_lobby_res_blockpliststart(struct _mio_message *msg, struct _ddrnet_playerlistinblock *playerlist, int *result); /* 0x007F8580-0x007F85D8 lines 207-218 */
int ddenet_lobby_req_blockplist(struct _ddrnet_con *con);        /* 0x007F85E0-0x007F85E8 lines 191-191 */
int ddrnet_lobby_res_enterblock(struct _mio_message *msg, int *result); /* 0x007F85F0-0x007F85FC lines 179-179 */
int ddrnet_lobby_req_enterblock(struct _ddrnet_con *con, unsigned char index); /* 0x007F8600-0x007F8664 lines 150-165 */
int ddrnet_lobby_res_blocklist(struct _mio_message *msg, struct _ddrnet_blocklist *blocklist); /* 0x007F8670-0x007F8744 lines 114-142 */
int ddrnet_lobby_req_blocklist(struct _ddrnet_con *con);         /* 0x007F8750-0x007F8758 lines 104-104 */
int ddrnet_res_selplayer(struct _mio_message *msg, unsigned int pid, int *result); /* 0x007F8760-0x007F8818 lines 68-92 */
int ddrnet_req_selplayer(struct _ddrnet_con *con, unsigned char index); /* 0x007F8820-0x007F8884 lines 39-54 */

#endif /* DDR_UNIT_src_network_usa_client_ddrex2_usa_lobby_c_H */
