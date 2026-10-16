/* struct _ddrnet_ranking_column -- 9 members, size 0x30, layout ae3f5f48cbcb.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x73C11).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_ranking_column *`.
 *
 * declared by: net.c (DIE 0x73C11), net_main.c (DIE 0x7F6DB), net_type.c (DIE 0x83CB5), net_prg.c (DIE 0x8A2CC), net_game_main.c (DIE 0xA1BD9), net_game_window.c (DIE 0xA9B66), net_game_opt.c (DIE 0xB7813), net_game_match.c (DIE 0xC844B), net_game_list.c (DIE 0xDB1AC), net_sys_top.c (DIE 0x16332A), net_sys_user.c (DIE 0x16AACA), net_win_search.c (DIE 0x1A8621), net_game_vs.c (DIE 0x1CF8BF), net_sys_lobby.c (DIE 0x1F406F), net_game_prg.c (DIE 0x2EEC51), ddrex2_usa_account.c (DIE 0x38D907), ddrex2_usa_challenge.c (DIE 0x38F430), ddrex2_usa_connect.c (DIE 0x39219B), ddrex2_usa_util.c (DIE 0x39E83C), net_auth_main.c (DIE 0x3ABEED)
 */
#ifndef DDR_types__ddrnet_ranking_column_H
#define DDR_types__ddrnet_ranking_column_H

struct _ddrnet_ranking_column {   // size 0x30
    /* 0x000 */ unsigned char dancerid;               // 0x1
    /* 0x001 */ unsigned char pname[17];              // 0x11
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ unsigned int rank;                    // 0x4
    /* 0x018 */ unsigned int pid;                     // 0x4
    /* 0x01C */ unsigned int param_0;                 // 0x4
    /* 0x020 */ unsigned int param_1;                 // 0x4
    /* 0x024 */ unsigned int param_2;                 // 0x4
    /* 0x028 */ unsigned int param_3;                 // 0x4
    /* 0x02C */ unsigned int param_4;                 // 0x4
};

#endif /* DDR_types__ddrnet_ranking_column_H */
