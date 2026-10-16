/* struct _nsv_user_htoh_week_log_work -- 5 members, size 0xC, layout 7dda17628ce3.
 *
 * One definition, agreed by the 34 units that declare it: net_main.c (DIE 0x789A8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_user_htoh_week_log_work *`.
 *
 * declared by: net_main.c (DIE 0x789A8), net_prg.c (DIE 0x86062), net_read_data.c (DIE 0x9449F), net_game_main.c (DIE 0x9BE41), net_game_window.c (DIE 0xA614C), net_game_opt.c (DIE 0xB3D88), net_game_logout.c (DIE 0xBA6FE), net_game_menu.c (DIE 0xBEF40), net_game_match.c (DIE 0xC41F4), net_game_data.c (DIE 0xCBF63), net_game_prac.c (DIE 0xD20C2), net_game_list.c (DIE 0xD78FB), net_sys_main.c (DIE 0x14CE96), net_sys_menu.c (DIE 0x152B27), net_sys_new.c (DIE 0x157E9C), net_sys_top.c (DIE 0x15F7D9), net_sys_user.c (DIE 0x167141), net_sys_rule.c (DIE 0x16DEDA), net_sys_connect.c (DIE 0x1714FF), net_sys_info.c (DIE 0x175527), net_sys_logout.c (DIE 0x19BE0F), net_win_suser.c (DIE 0x1A097B), net_win_user.c (DIE 0x1AE4BF), net_play_main.c (DIE 0x1BE7FA), net_game_vs.c (DIE 0x1C94C1), net_sys_lobby.c (DIE 0x1F0574), net_game_rc.c (DIE 0x266188), net_game_challenge.c (DIE 0x26D300), net_win_peruser.c (DIE 0x2F5FDF), net_win_perhead.c (DIE 0x2F74AD), net_auth_main.c (DIE 0x3AA89B), net_cnf_main.c (DIE 0x3B5511), net_dnas_main.c (DIE 0x3BD78A), net_router_main.c (DIE 0x3C1014)
 */
#ifndef DDR_types__nsv_user_htoh_week_log_work_H
#define DDR_types__nsv_user_htoh_week_log_work_H

struct _nsv_user_htoh_week_log_work {   // size 0xC
    /* 0x000 */ unsigned int rank_num;                // 0x4
    /* 0x004 */ unsigned short match;                 // 0x2
    /* 0x006 */ unsigned short win;                   // 0x2
    /* 0x008 */ unsigned short draw;                  // 0x2
    /* 0x00A */ unsigned short lose;                  // 0x2
};

#endif /* DDR_types__nsv_user_htoh_week_log_work_H */
