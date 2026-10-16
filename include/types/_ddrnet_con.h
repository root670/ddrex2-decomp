/* struct _ddrnet_con -- 5 members, size 0x20, layout 1fcfd0c63a56.
 *
 * One definition, agreed by the 22 units that declare it: net.c (DIE 0x6FF3D).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_con *`.
 *
 * declared by: net.c (DIE 0x6FF3D), net_main.c (DIE 0x797AF), net_type.c (DIE 0x821AD), net_prg.c (DIE 0x85DF0), net_game_main.c (DIE 0x9B484), net_game_window.c (DIE 0xA5480), net_game_opt.c (DIE 0xB35AC), net_game_match.c (DIE 0xC39A7), net_game_list.c (DIE 0xD711A), net_sys_top.c (DIE 0x15EA7E), net_sys_user.c (DIE 0x166436), net_win_search.c (DIE 0x1A57DF), net_game_vs.c (DIE 0x1C85DB), net_sys_lobby.c (DIE 0x1EF68F), net_game_prg.c (DIE 0x2EAA51), ddrex2_usa_account.c (DIE 0x38B489), ddrex2_usa_challenge.c (DIE 0x38EEAD), ddrex2_usa_connect.c (DIE 0x391BCE), ddrex2_usa_gate.c (DIE 0x394E8C), ddrex2_usa_lobby.c (DIE 0x397BAF), ddrex2_usa_util.c (DIE 0x3A034C), net_auth_main.c (DIE 0x3A5EA8)
 */
#ifndef DDR_types__ddrnet_con_H
#define DDR_types__ddrnet_con_H

struct sockaddr_in;

#include "types/sockaddr_in.h"

struct _ddrnet_con {   // size 0x20
    /* 0x000 */ int sd;                               // 0x4
    /* 0x004 */ struct sockaddr_in svaddr_in;         // 0x10
    /* 0x014 */ unsigned int rid;                     // 0x4
    /* 0x018 */ unsigned int wid;                     // 0x4
    /* 0x01C */ unsigned int lastrecv_sec;            // 0x4
};

#endif /* DDR_types__ddrnet_con_H */
