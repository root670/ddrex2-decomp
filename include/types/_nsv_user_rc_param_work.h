/* struct _nsv_user_rc_param_work -- 6 members, size 0x14, layout 2a7c83d25196.
 *
 * One definition, agreed by the 34 units that declare it: net_main.c (DIE 0x7E3BE).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_user_rc_param_work *`.
 *
 * declared by: net_main.c (DIE 0x7E3BE), net_prg.c (DIE 0x8BE16), net_read_data.c (DIE 0x91D80), net_game_main.c (DIE 0xA2A9D), net_game_window.c (DIE 0xAA1D6), net_game_opt.c (DIE 0xB7ED0), net_game_logout.c (DIE 0xBD164), net_game_menu.c (DIE 0xC18D1), net_game_match.c (DIE 0xC8A2B), net_game_data.c (DIE 0xCE600), net_game_prac.c (DIE 0xD4579), net_game_list.c (DIE 0xDB86E), net_sys_main.c (DIE 0x151741), net_sys_menu.c (DIE 0x155564), net_sys_new.c (DIE 0x15CB5D), net_sys_top.c (DIE 0x16413D), net_sys_user.c (DIE 0x16B197), net_sys_rule.c (DIE 0x170156), net_sys_connect.c (DIE 0x173F13), net_sys_info.c (DIE 0x177E2A), net_sys_logout.c (DIE 0x19E663), net_win_suser.c (DIE 0x19FBA5), net_win_user.c (DIE 0x1AD3DC), net_play_main.c (DIE 0x1C3F1F), net_game_vs.c (DIE 0x1D07D2), net_sys_lobby.c (DIE 0x1F4748), net_game_rc.c (DIE 0x26884E), net_game_challenge.c (DIE 0x26A2A3), net_win_peruser.c (DIE 0x2F522F), net_win_perrank.c (DIE 0x2F9FE9), net_auth_main.c (DIE 0x3A6165), net_cnf_main.c (DIE 0x3B1B4D), net_dnas_main.c (DIE 0x3BF650), net_router_main.c (DIE 0x3C3325)
 */
#ifndef DDR_types__nsv_user_rc_param_work_H
#define DDR_types__nsv_user_rc_param_work_H

struct _nsv_user_rc_param_work {   // size 0x14
    /* 0x000 */ unsigned int rank_num;                // 0x4
    /* 0x004 */ unsigned int score;                   // 0x4
    /* 0x008 */ unsigned int time;                    // 0x4
    /* 0x00C */ unsigned short combo;                 // 0x2
    /* 0x00E */ unsigned short dance_gauge;           // 0x2
    /* 0x010 */ signed char ranking_challenge_num;    // 0x1
    /* 0x011 */ // 0x3 bytes padding
};

#endif /* DDR_types__nsv_user_rc_param_work_H */
