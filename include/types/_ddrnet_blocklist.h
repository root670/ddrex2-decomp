/* struct _ddrnet_blocklist -- 2 members, size 0x18, layout 5264e6ab73e6.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x714AC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_blocklist *`.
 *
 * declared by: net.c (DIE 0x714AC), net_main.c (DIE 0x7C642), net_type.c (DIE 0x83266), net_prg.c (DIE 0x87FDD), net_game_main.c (DIE 0x9E579), net_game_window.c (DIE 0xA857A), net_game_opt.c (DIE 0xB61D5), net_game_match.c (DIE 0xC6906), net_game_list.c (DIE 0xD9CD7), net_sys_top.c (DIE 0x161FA9), net_sys_user.c (DIE 0x169930), net_win_search.c (DIE 0x1A7631), net_game_vs.c (DIE 0x1CC4AE), net_sys_lobby.c (DIE 0x1F2B05), net_game_prg.c (DIE 0x2EC57A), ddrex2_usa_account.c (DIE 0x38C881), ddrex2_usa_connect.c (DIE 0x391353), ddrex2_usa_lobby.c (DIE 0x398A9C), ddrex2_usa_util.c (DIE 0x3A0FF8), net_auth_main.c (DIE 0x3A9E21)
 */
#ifndef DDR_types__ddrnet_blocklist_H
#define DDR_types__ddrnet_blocklist_H

struct _ddrnet_block;

#include "types/_ddrnet_block.h"

struct _ddrnet_blocklist {   // size 0x18
    /* 0x000 */ unsigned short num_block;             // 0x2
    /* 0x002 */ struct _ddrnet_block block[1];        // 0x16
};

#endif /* DDR_types__ddrnet_blocklist_H */
