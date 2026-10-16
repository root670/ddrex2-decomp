/* struct _nsv_user_htoh_year_param_work -- 6 members, size 0x18, layout 0799ab1e4465.
 *
 * One definition, agreed by the 33 units that declare it: net_main.c (DIE 0x7A124).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_user_htoh_year_param_work *`.
 *
 * declared by: net_main.c (DIE 0x7A124), net_prg.c (DIE 0x880CC), net_read_data.c (DIE 0x959AC), net_game_main.c (DIE 0x9DC68), net_game_window.c (DIE 0xA7D1A), net_game_opt.c (DIE 0xB5975), net_game_logout.c (DIE 0xBBD16), net_game_menu.c (DIE 0xC003B), net_game_match.c (DIE 0xC60F4), net_game_data.c (DIE 0xCD253), net_game_prac.c (DIE 0xD30D9), net_game_list.c (DIE 0xD9477), net_sys_main.c (DIE 0x14E431), net_sys_menu.c (DIE 0x153B3E), net_sys_new.c (DIE 0x15946D), net_sys_top.c (DIE 0x1615DA), net_sys_user.c (DIE 0x169142), net_sys_rule.c (DIE 0x16EF1A), net_sys_connect.c (DIE 0x172B17), net_sys_info.c (DIE 0x176814), net_sys_logout.c (DIE 0x19D3D5), net_win_suser.c (DIE 0x19F492), net_win_user.c (DIE 0x1ACCA2), net_play_main.c (DIE 0x1C1936), net_game_vs.c (DIE 0x1CBABB), net_sys_lobby.c (DIE 0x1F2317), net_game_rc.c (DIE 0x267055), net_game_challenge.c (DIE 0x26E6A9), net_win_peruser.c (DIE 0x2F4A59), net_auth_main.c (DIE 0x3ACA65), net_cnf_main.c (DIE 0x3B6C24), net_dnas_main.c (DIE 0x3BE001), net_router_main.c (DIE 0x3C1F15)
 */
#ifndef DDR_types__nsv_user_htoh_year_param_work_H
#define DDR_types__nsv_user_htoh_year_param_work_H

struct _nsv_user_htoh_year_param_work {   // size 0x18
    /* 0x000 */ unsigned int rank_num;                // 0x4
    /* 0x004 */ unsigned int last_rank_num;           // 0x4
    /* 0x008 */ unsigned int match;                   // 0x4
    /* 0x00C */ unsigned int win;                     // 0x4
    /* 0x010 */ unsigned int lose;                    // 0x4
    /* 0x014 */ unsigned int draw;                    // 0x4
};

#endif /* DDR_types__nsv_user_htoh_year_param_work_H */
