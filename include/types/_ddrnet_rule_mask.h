/* struct _ddrnet_rule_mask -- 3 members, size 0x3, layout 6f15a7d3a42f.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x71F2C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_rule_mask *`.
 *
 * declared by: net.c (DIE 0x71F2C), net_main.c (DIE 0x7F13C), net_type.c (DIE 0x839F6), net_prg.c (DIE 0x896EB), net_game_main.c (DIE 0x9FA15), net_game_window.c (DIE 0xA9475), net_game_opt.c (DIE 0xB70F9), net_game_match.c (DIE 0xC7E4E), net_game_list.c (DIE 0xDAA8D), net_sys_top.c (DIE 0x162DA0), net_sys_user.c (DIE 0x16A4CD), net_win_search.c (DIE 0x1A81BB), net_game_vs.c (DIE 0x1CD68D), net_sys_lobby.c (DIE 0x1F3A4F), net_game_prg.c (DIE 0x2ED003), ddrex2_usa_account.c (DIE 0x38D333), ddrex2_usa_connect.c (DIE 0x391B3B), ddrex2_usa_lobby.c (DIE 0x398F62), ddrex2_usa_util.c (DIE 0x3A1529), net_auth_main.c (DIE 0x3AB2B6)
 */
#ifndef DDR_types__ddrnet_rule_mask_H
#define DDR_types__ddrnet_rule_mask_H

struct _ddrnet_rule_mask {   // size 0x3
    /* 0x000 */ signed char score;                    // 0x1
    /* 0x001 */ signed char combo;                    // 0x1
    /* 0x002 */ signed char survival;                 // 0x1
};

#endif /* DDR_types__ddrnet_rule_mask_H */
