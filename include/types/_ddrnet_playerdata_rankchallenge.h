/* struct _ddrnet_playerdata_rankchallenge -- 6 members, size 0x10, layout 974116e3ee94.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x701F5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerdata_rankchallenge *`.
 *
 * declared by: net.c (DIE 0x701F5), net_main.c (DIE 0x79B21), net_type.c (DIE 0x823D3), net_prg.c (DIE 0x8D7CA), net_game_main.c (DIE 0x9BBCA), net_game_window.c (DIE 0xA5ED5), net_game_opt.c (DIE 0xB3B11), net_game_match.c (DIE 0xC3F7D), net_game_list.c (DIE 0xD7684), net_sys_top.c (DIE 0x15F562), net_sys_user.c (DIE 0x166ECA), net_win_search.c (DIE 0x1A6113), net_game_vs.c (DIE 0x1C90F8), net_sys_lobby.c (DIE 0x1F013F), net_game_prg.c (DIE 0x2EB482), ddrex2_usa_account.c (DIE 0x38BE0C), ddrex2_usa_connect.c (DIE 0x393278), ddrex2_usa_lobby.c (DIE 0x3985BE), ddrex2_usa_util.c (DIE 0x3A00F1), net_auth_main.c (DIE 0x3A6F49)
 */
#ifndef DDR_types__ddrnet_playerdata_rankchallenge_H
#define DDR_types__ddrnet_playerdata_rankchallenge_H

struct _ddrnet_playerdata_rankchallenge {   // size 0x10
    /* 0x000 */ signed char id;                       // 0x1
    /* 0x001 */ // 0x1 bytes padding
    /* 0x002 */ unsigned short score;                 // 0x2
    /* 0x004 */ unsigned short time;                  // 0x2
    /* 0x006 */ unsigned short combo;                 // 0x2
    /* 0x008 */ unsigned short gauge;                 // 0x2
    /* 0x00A */ // 0x2 bytes padding
    /* 0x00C */ unsigned int rank;                    // 0x4
};

#endif /* DDR_types__ddrnet_playerdata_rankchallenge_H */
