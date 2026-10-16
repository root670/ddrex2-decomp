/* struct _ddrnet_pldata_match -- 4 members, size 0x10, layout 8bc5489f3211.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x73F57).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_pldata_match *`.
 *
 * declared by: net.c (DIE 0x73F57), net_main.c (DIE 0x7FA99), net_type.c (DIE 0x83F7A), net_prg.c (DIE 0x8A84F), net_game_main.c (DIE 0xA2003), net_game_window.c (DIE 0xA9E70), net_game_opt.c (DIE 0xB7B6A), net_game_match.c (DIE 0xC8755), net_game_list.c (DIE 0xDB4B6), net_sys_top.c (DIE 0x163658), net_sys_user.c (DIE 0x16ADD4), net_win_search.c (DIE 0x1A8B69), net_game_vs.c (DIE 0x1CFD82), net_sys_lobby.c (DIE 0x1F4472), net_game_prg.c (DIE 0x2EF12C), ddrex2_usa_account.c (DIE 0x38D1E7), ddrex2_usa_connect.c (DIE 0x3919EF), ddrex2_usa_lobby.c (DIE 0x398E8D), ddrex2_usa_util.c (DIE 0x3A1401), net_auth_main.c (DIE 0x3AC0EC)
 */
#ifndef DDR_types__ddrnet_pldata_match_H
#define DDR_types__ddrnet_pldata_match_H

struct _ddrnet_pldata_match {   // size 0x10
    /* 0x000 */ unsigned int match;                   // 0x4
    /* 0x004 */ unsigned int win;                     // 0x4
    /* 0x008 */ unsigned int draw;                    // 0x4
    /* 0x00C */ unsigned int lose;                    // 0x4
};

#endif /* DDR_types__ddrnet_pldata_match_H */
