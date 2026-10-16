/* struct _nsv_player_list_file -- 19 members, size 0x54, layout d8a497a1a925.
 *
 * One definition, agreed by the 36 units that declare it: net_main.c (DIE 0x7A22E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_player_list_file *`.
 *
 * declared by: net_main.c (DIE 0x7A22E), net_prg.c (DIE 0x88476), net_read_data.c (DIE 0x95D6C), net_game_main.c (DIE 0x9E04C), net_game_window.c (DIE 0xA80FE), net_game_opt.c (DIE 0xB5DCB), net_game_logout.c (DIE 0xBC0D6), net_game_menu.c (DIE 0xC03FB), net_game_match.c (DIE 0xC64D8), net_game_data.c (DIE 0xCD613), net_game_prac.c (DIE 0xD3499), net_game_list.c (DIE 0xD98CD), net_sys_main.c (DIE 0x14E817), net_sys_menu.c (DIE 0x153EFE), net_sys_new.c (DIE 0x159A12), net_sys_top.c (DIE 0x161C32), net_sys_user.c (DIE 0x169526), net_sys_rule.c (DIE 0x16F2DA), net_sys_connect.c (DIE 0x172ED7), net_sys_info.c (DIE 0x176BD4), net_sys_logout.c (DIE 0x19D795), net_play_main.c (DIE 0x1C15E3), net_game_vs.c (DIE 0x1CC137), net_sys_lobby.c (DIE 0x1F26FB), net_win_listsel.c (DIE 0x254E9D), net_win_listdtl2.c (DIE 0x25EBA9), net_win_listdtl.c (DIE 0x26098E), net_win_listdtl3.c (DIE 0x262791), net_game_rc.c (DIE 0x2675D8), net_game_challenge.c (DIE 0x26E845), net_win_dhead.c (DIE 0x301CB8), net_win_dpoint.c (DIE 0x303828), net_auth_main.c (DIE 0x3ACCAE), net_cnf_main.c (DIE 0x3B6F8D), net_dnas_main.c (DIE 0x3BE202), net_router_main.c (DIE 0x3C221B)
 */
#ifndef DDR_types__nsv_player_list_file_H
#define DDR_types__nsv_player_list_file_H

struct _nsv_player_list_file {   // size 0x54
    /* 0x000 */ unsigned int pid;                     // 0x4
    /* 0x004 */ unsigned char name[20];               // 0x14
    /* 0x018 */ char dancer_number;                   // 0x1
    /* 0x019 */ // 0x3 bytes padding
    /* 0x01C */ int status;                           // 0x4
    /* 0x020 */ unsigned int dis_connect_count;       // 0x4
    /* 0x024 */ unsigned int htoh_total_rank;         // 0x4
    /* 0x028 */ unsigned int htoh_total_match;        // 0x4
    /* 0x02C */ unsigned int htoh_total_win;          // 0x4
    /* 0x030 */ unsigned int htoh_total_draw;         // 0x4
    /* 0x034 */ unsigned int htoh_total_lose;         // 0x4
    /* 0x038 */ unsigned int htoh_week_rank;          // 0x4
    /* 0x03C */ unsigned short htoh_week_match;       // 0x2
    /* 0x03E */ unsigned short htoh_week_win;         // 0x2
    /* 0x040 */ unsigned short htoh_week_draw;        // 0x2
    /* 0x042 */ unsigned short htoh_week_lose;        // 0x2
    /* 0x044 */ unsigned int points_total_rank;       // 0x4
    /* 0x048 */ unsigned int points_total_num;        // 0x4
    /* 0x04C */ unsigned int points_week_rank;        // 0x4
    /* 0x050 */ unsigned short points_week_num;       // 0x2
    /* 0x052 */ // 0x2 bytes padding
};

#endif /* DDR_types__nsv_player_list_file_H */
