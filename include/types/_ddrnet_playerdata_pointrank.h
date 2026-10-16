/* struct _ddrnet_playerdata_pointrank -- 2 members, size 0x8, layout eaaa7e739214.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x70035).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerdata_pointrank *`.
 *
 * declared by: net.c (DIE 0x70035), net_main.c (DIE 0x798F1), net_type.c (DIE 0x822A5), net_prg.c (DIE 0x8D40E), net_game_main.c (DIE 0x9B8B9), net_game_window.c (DIE 0xA5D5D), net_game_opt.c (DIE 0xB3999), net_game_match.c (DIE 0xC3D99), net_game_list.c (DIE 0xD7530), net_sys_top.c (DIE 0x15F2B9), net_sys_user.c (DIE 0x166C4A), net_win_search.c (DIE 0x1A5E46), net_game_vs.c (DIE 0x1C89CD), net_sys_lobby.c (DIE 0x1EFA58), net_game_prg.c (DIE 0x2EACE5), ddrex2_usa_account.c (DIE 0x38BAED), ddrex2_usa_connect.c (DIE 0x3930B9), ddrex2_usa_lobby.c (DIE 0x3984B9), ddrex2_usa_util.c (DIE 0x39FE15), net_auth_main.c (DIE 0x3A62E8)
 */
#ifndef DDR_types__ddrnet_playerdata_pointrank_H
#define DDR_types__ddrnet_playerdata_pointrank_H

struct _ddrnet_playerdata_pointrank {   // size 0x8
    /* 0x000 */ unsigned int rank;                    // 0x4
    /* 0x004 */ unsigned short point;                 // 0x2
    /* 0x006 */ // 0x2 bytes padding
};

#endif /* DDR_types__ddrnet_playerdata_pointrank_H */
