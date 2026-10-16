/* struct _ddrnet_roomlist -- 2 members, size 0xCB24, layout 7b17bdf86c5c.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x6E4B8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_roomlist *`.
 *
 * declared by: net.c (DIE 0x6E4B8), net_main.c (DIE 0x769D9), net_type.c (DIE 0x8138B), net_prg.c (DIE 0x8BBA3), net_game_main.c (DIE 0xA309A), net_game_window.c (DIE 0xAAAB8), net_game_opt.c (DIE 0xB876F), net_game_match.c (DIE 0xC91E7), net_game_list.c (DIE 0xDC0E4), net_sys_top.c (DIE 0x1642CF), net_sys_user.c (DIE 0x16BACB), net_win_search.c (DIE 0x1A9CF2), net_game_vs.c (DIE 0x1D0AD3), net_sys_lobby.c (DIE 0x1F4FBD), net_game_prg.c (DIE 0x2EFACE), ddrex2_usa_account.c (DIE 0x38DC03), ddrex2_usa_connect.c (DIE 0x392467), ddrex2_usa_lobby.c (DIE 0x398B7E), ddrex2_usa_util.c (DIE 0x39ED0A), net_auth_main.c (DIE 0x3AD1D1)
 */
#ifndef DDR_types__ddrnet_roomlist_H
#define DDR_types__ddrnet_roomlist_H

struct _ddrnet_room;

#include "types/_ddrnet_room.h"

struct _ddrnet_roomlist {   // size 0xCB24
    /* 0x000 */ unsigned int count;                   // 0x4
    /* 0x004 */ struct _ddrnet_room list[1000];       // 0xCB20
};

#endif /* DDR_types__ddrnet_roomlist_H */
