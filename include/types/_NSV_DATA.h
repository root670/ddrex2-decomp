/* struct _NSV_DATA -- 6 members, size 0x10, layout aea96c887dc5.
 *
 * One definition, agreed by the 30 units that declare it: net_main.c (DIE 0x794E1).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NSV_DATA *`.
 *
 * declared by: net_main.c (DIE 0x794E1), net_prg.c (DIE 0x86980), net_read_data.c (DIE 0x9476A), net_game_main.c (DIE 0x9C44E), net_game_window.c (DIE 0xA657D), net_game_opt.c (DIE 0xB4651), net_game_logout.c (DIE 0xBA934), net_game_menu.c (DIE 0xBF236), net_game_match.c (DIE 0xC4B25), net_game_data.c (DIE 0xCC1EB), net_game_prac.c (DIE 0xD22F8), net_game_list.c (DIE 0xD8177), net_sys_main.c (DIE 0x14D13A), net_sys_menu.c (DIE 0x152D5D), net_sys_new.c (DIE 0x15824A), net_sys_top.c (DIE 0x15FEDB), net_sys_user.c (DIE 0x1676CD), net_sys_rule.c (DIE 0x16E110), net_sys_connect.c (DIE 0x171D36), net_sys_info.c (DIE 0x17575D), net_sys_logout.c (DIE 0x19C5F4), net_play_main.c (DIE 0x1BEC25), net_game_vs.c (DIE 0x1CA1E0), net_sys_lobby.c (DIE 0x1F09F2), net_game_rc.c (DIE 0x2664F1), net_game_challenge.c (DIE 0x26D656), net_auth_main.c (DIE 0x3AB660), net_cnf_main.c (DIE 0x3B6103), net_dnas_main.c (DIE 0x3BDA77), net_router_main.c (DIE 0x3C1116)
 */
#ifndef DDR_types__NSV_DATA_H
#define DDR_types__NSV_DATA_H

struct _NSV_DATA {   // size 0x10
    /* 0x000 */ unsigned int now_time;                // 0x4
    /* 0x004 */ unsigned int rc_end_time;             // 0x4
    /* 0x008 */ unsigned int now_login_user_num;      // 0x4
    /* 0x00C */ char now_week;                        // 0x1
    /* 0x00D */ unsigned char rule_mask;              // 0x1
    /* 0x00E */ char padn[2];                         // 0x2
};

#endif /* DDR_types__NSV_DATA_H */
