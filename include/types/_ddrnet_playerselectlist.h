/* struct _ddrnet_playerselectlist -- 1 members, size 0x60, layout d6de6f05b0ee.
 *
 * One definition, agreed by the 19 units that declare it: net.c (DIE 0x71520).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerselectlist *`.
 *
 * declared by: net.c (DIE 0x71520), net_main.c (DIE 0x7C764), net_type.c (DIE 0x832DA), net_prg.c (DIE 0x88077), net_game_main.c (DIE 0x9E611), net_game_window.c (DIE 0xA8612), net_game_opt.c (DIE 0xB626D), net_game_match.c (DIE 0xC699E), net_game_list.c (DIE 0xD9D98), net_sys_top.c (DIE 0x162041), net_sys_user.c (DIE 0x1699C8), net_win_search.c (DIE 0x1A76A5), net_game_vs.c (DIE 0x1CC546), net_sys_lobby.c (DIE 0x1F2B9D), net_game_prg.c (DIE 0x2EC5EE), ddrex2_usa_account.c (DIE 0x38C7BE), ddrex2_usa_connect.c (DIE 0x393D05), ddrex2_usa_util.c (DIE 0x3A0F35), net_auth_main.c (DIE 0x3A9FA9)
 */
#ifndef DDR_types__ddrnet_playerselectlist_H
#define DDR_types__ddrnet_playerselectlist_H

struct _ddrnet_playerselect;

#include "types/_ddrnet_playerselect.h"

struct _ddrnet_playerselectlist {   // size 0x60
    /* 0x000 */ struct _ddrnet_playerselect entry[2];  // 0x60
};

#endif /* DDR_types__ddrnet_playerselectlist_H */
