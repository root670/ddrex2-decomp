/* struct _ddrnet_playerselect -- 9 members, size 0x30, layout c95fc9e9bfa0.
 *
 * One definition, agreed by the 19 units that declare it: net.c (DIE 0x71030).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerselect *`.
 *
 * declared by: net.c (DIE 0x71030), net_main.c (DIE 0x7BB0C), net_type.c (DIE 0x82DF4), net_prg.c (DIE 0x86B22), net_game_main.c (DIE 0x9D76F), net_game_window.c (DIE 0xA7888), net_game_opt.c (DIE 0xB5535), net_game_match.c (DIE 0xC5B7F), net_game_list.c (DIE 0xD9037), net_sys_top.c (DIE 0x160B61), net_sys_user.c (DIE 0x168B20), net_win_search.c (DIE 0x1A6E00), net_game_vs.c (DIE 0x1CAAB2), net_sys_lobby.c (DIE 0x1F1EB3), net_game_prg.c (DIE 0x2EC247), ddrex2_usa_account.c (DIE 0x38BB65), ddrex2_usa_connect.c (DIE 0x39365E), ddrex2_usa_util.c (DIE 0x3A096B), net_auth_main.c (DIE 0x3A86AC)
 */
#ifndef DDR_types__ddrnet_playerselect_H
#define DDR_types__ddrnet_playerselect_H

struct _ddrnet_playerselect {   // size 0x30
    /* 0x000 */ unsigned char index;                  // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ unsigned int pid;                     // 0x4
    /* 0x008 */ int playtime;                         // 0x4
    /* 0x00C */ unsigned char pname[17];              // 0x11
    /* 0x01D */ signed char dancer;                   // 0x1
    /* 0x01E */ // 0x2 bytes padding
    /* 0x020 */ unsigned int points;                  // 0x4
    /* 0x024 */ unsigned int win;                     // 0x4
    /* 0x028 */ unsigned int lose;                    // 0x4
    /* 0x02C */ unsigned int draw;                    // 0x4
};

#endif /* DDR_types__ddrnet_playerselect_H */
