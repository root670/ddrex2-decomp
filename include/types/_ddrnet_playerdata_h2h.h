/* struct _ddrnet_playerdata_h2h -- 5 members, size 0xC, layout 60fe2660bd5b.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x6FE1C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerdata_h2h *`.
 *
 * declared by: net.c (DIE 0x6FE1C), net_main.c (DIE 0x793E9), net_type.c (DIE 0x820B3), net_prg.c (DIE 0x8D08B), net_game_main.c (DIE 0x9ACF7), net_game_window.c (DIE 0xA4D81), net_game_opt.c (DIE 0xB2CEF), net_game_match.c (DIE 0xC3812), net_game_list.c (DIE 0xD60C5), net_sys_top.c (DIE 0x15E85D), net_sys_user.c (DIE 0x166239), net_win_search.c (DIE 0x1A564E), net_game_vs.c (DIE 0x1C809D), net_sys_lobby.c (DIE 0x1EF3EE), net_game_prg.c (DIE 0x2EA822), ddrex2_usa_account.c (DIE 0x38B55D), ddrex2_usa_connect.c (DIE 0x392D81), ddrex2_usa_lobby.c (DIE 0x397ADB), ddrex2_usa_util.c (DIE 0x39F566), net_auth_main.c (DIE 0x3A4CAA)
 */
#ifndef DDR_types__ddrnet_playerdata_h2h_H
#define DDR_types__ddrnet_playerdata_h2h_H

struct _ddrnet_playerdata_h2h {   // size 0xC
    /* 0x000 */ unsigned int rank;                    // 0x4
    /* 0x004 */ unsigned short match;                 // 0x2
    /* 0x006 */ unsigned short win;                   // 0x2
    /* 0x008 */ unsigned short draw;                  // 0x2
    /* 0x00A */ unsigned short lose;                  // 0x2
};

#endif /* DDR_types__ddrnet_playerdata_h2h_H */
