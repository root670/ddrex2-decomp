/* struct _nsv_user_htoh_week_param_work -- 6 members, size 0x10, layout 1d613581bf8f.
 *
 * One definition, agreed by the 33 units that declare it: net_main.c (DIE 0x7965B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_user_htoh_week_param_work *`.
 *
 * declared by: net_main.c (DIE 0x7965B), net_prg.c (DIE 0x865A6), net_read_data.c (DIE 0x94876), net_game_main.c (DIE 0x9C57E), net_game_window.c (DIE 0xA66AD), net_game_opt.c (DIE 0xB4781), net_game_logout.c (DIE 0xBAA40), net_game_menu.c (DIE 0xBF342), net_game_match.c (DIE 0xC4C55), net_game_data.c (DIE 0xCC2F7), net_game_prac.c (DIE 0xD2404), net_game_list.c (DIE 0xD82A7), net_sys_main.c (DIE 0x14D246), net_sys_menu.c (DIE 0x152E69), net_sys_new.c (DIE 0x15811A), net_sys_top.c (DIE 0x15FD65), net_sys_user.c (DIE 0x1677FD), net_sys_rule.c (DIE 0x16E21C), net_sys_connect.c (DIE 0x171E42), net_sys_info.c (DIE 0x175869), net_sys_logout.c (DIE 0x19C700), net_win_suser.c (DIE 0x1A0A7F), net_win_user.c (DIE 0x1AE615), net_play_main.c (DIE 0x1C043A), net_game_vs.c (DIE 0x1C9F0F), net_sys_lobby.c (DIE 0x1F0B22), net_game_rc.c (DIE 0x2663E7), net_game_challenge.c (DIE 0x26D7C0), net_win_peruser.c (DIE 0x2F60E3), net_auth_main.c (DIE 0x3AB790), net_cnf_main.c (DIE 0x3B6360), net_dnas_main.c (DIE 0x3BDBF1), net_router_main.c (DIE 0x3C1222)
 */
#ifndef DDR_types__nsv_user_htoh_week_param_work_H
#define DDR_types__nsv_user_htoh_week_param_work_H

struct _nsv_user_htoh_week_param_work {   // size 0x10
    /* 0x000 */ unsigned int rank_num;                // 0x4
    /* 0x004 */ unsigned int last_rank_num;           // 0x4
    /* 0x008 */ unsigned short match;                 // 0x2
    /* 0x00A */ unsigned short win;                   // 0x2
    /* 0x00C */ unsigned short lose;                  // 0x2
    /* 0x00E */ unsigned short draw;                  // 0x2
};

#endif /* DDR_types__nsv_user_htoh_week_param_work_H */
