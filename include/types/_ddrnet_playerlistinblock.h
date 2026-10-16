/* struct _ddrnet_playerlistinblock -- 2 members, size 0x13884, layout 31c5383253d7.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x73D7E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerlistinblock *`.
 *
 * declared by: net.c (DIE 0x73D7E), net_main.c (DIE 0x7F848), net_type.c (DIE 0x83E22), net_prg.c (DIE 0x8A439), net_game_main.c (DIE 0xA1D46), net_game_window.c (DIE 0xA9CD3), net_game_opt.c (DIE 0xB7980), net_game_match.c (DIE 0xC85B8), net_game_list.c (DIE 0xDB319), net_sys_top.c (DIE 0x163497), net_sys_user.c (DIE 0x16AC37), net_win_search.c (DIE 0x1A878E), net_game_vs.c (DIE 0x1CFAC5), net_sys_lobby.c (DIE 0x1F41DC), net_game_prg.c (DIE 0x2EEDBE), ddrex2_usa_account.c (DIE 0x38D2BC), ddrex2_usa_connect.c (DIE 0x391AC4), ddrex2_usa_lobby.c (DIE 0x398CEC), ddrex2_usa_util.c (DIE 0x3A14B2), net_auth_main.c (DIE 0x3ABDED)
 */
#ifndef DDR_types__ddrnet_playerlistinblock_H
#define DDR_types__ddrnet_playerlistinblock_H

struct _ddrnet_playerinblock;

#include "types/_ddrnet_playerinblock.h"

struct _ddrnet_playerlistinblock {   // size 0x13884
    /* 0x000 */ unsigned short count;                 // 0x2
    /* 0x002 */ // 0x2 bytes padding
    /* 0x004 */ struct _ddrnet_playerinblock list[1000];  // 0x13880
};

#endif /* DDR_types__ddrnet_playerlistinblock_H */
