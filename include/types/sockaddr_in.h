/* struct sockaddr_in -- 4 members, size 0x10, layout 972eba24d3df.
 *
 * One definition, agreed by the 22 units that declare it: net.c (DIE 0x713EE).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sockaddr_in *`.
 *
 * declared by: net.c (DIE 0x713EE), net_main.c (DIE 0x80260), net_type.c (DIE 0x846A3), net_prg.c (DIE 0x8B8CB), net_game_main.c (DIE 0xA2D92), net_game_window.c (DIE 0xAA858), net_game_opt.c (DIE 0xB852E), net_game_match.c (DIE 0xC9089), net_game_list.c (DIE 0xDBECC), net_sys_top.c (DIE 0x164037), net_sys_user.c (DIE 0x16B91E), net_win_search.c (DIE 0x1A8F29), net_game_vs.c (DIE 0x1D06CC), net_sys_lobby.c (DIE 0x1F4DA6), net_game_prg.c (DIE 0x2EF76A), ddrex2_usa_account.c (DIE 0x38D105), ddrex2_usa_challenge.c (DIE 0x38F74F), ddrex2_usa_connect.c (DIE 0x39190D), ddrex2_usa_gate.c (DIE 0x395234), ddrex2_usa_lobby.c (DIE 0x398D63), ddrex2_usa_util.c (DIE 0x3A000D), net_auth_main.c (DIE 0x3A7F27)
 */
#ifndef DDR_types_sockaddr_in_H
#define DDR_types_sockaddr_in_H

struct in_addr;

#include "types/in_addr.h"

struct sockaddr_in {   // size 0x10
    /* 0x000 */ unsigned short sin_family;            // 0x2
    /* 0x002 */ unsigned short sin_port;              // 0x2
    /* 0x004 */ struct in_addr sin_addr;              // 0x4
    /* 0x008 */ unsigned char sin_zero[8];            // 0x8
};

#endif /* DDR_types_sockaddr_in_H */
