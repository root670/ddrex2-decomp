/* struct _nsv_music_data_work -- 11 members, size 0xC, layout a247e1253631.
 *
 * One definition, agreed by the 31 units that declare it: net_main.c (DIE 0x7EEEF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_music_data_work *`.
 *
 * declared by: net_main.c (DIE 0x7EEEF), net_prg.c (DIE 0x8BC11), net_read_data.c (DIE 0x92467), net_game_main.c (DIE 0xA2BB1), net_game_window.c (DIE 0xAA677), net_game_opt.c (DIE 0xB8371), net_game_logout.c (DIE 0xBD278), net_game_menu.c (DIE 0xC19E5), net_game_match.c (DIE 0xC8ECC), net_game_data.c (DIE 0xCE714), net_game_prac.c (DIE 0xD468D), net_game_list.c (DIE 0xDBD0F), net_sys_main.c (DIE 0x151855), net_sys_menu.c (DIE 0x155678), net_sys_new.c (DIE 0x15C97C), net_sys_top.c (DIE 0x163D51), net_sys_user.c (DIE 0x16B638), net_sys_rule.c (DIE 0x17026A), net_sys_connect.c (DIE 0x174027), net_sys_info.c (DIE 0x177F3E), net_sys_logout.c (DIE 0x19E777), net_play_main.c (DIE 0x1C4183), net_game_vs.c (DIE 0x1D050F), net_sys_lobby.c (DIE 0x1F4BE9), net_game_rc.c (DIE 0x268691), net_game_challenge.c (DIE 0x26A3FF), net_win_rccssel.c (DIE 0x2A2FED), net_auth_main.c (DIE 0x3A6394), net_cnf_main.c (DIE 0x3B24ED), net_dnas_main.c (DIE 0x3BF764), net_router_main.c (DIE 0x3C345D)
 */
#ifndef DDR_types__nsv_music_data_work_H
#define DDR_types__nsv_music_data_work_H

struct _nsv_music_data_work {   // size 0xC
    /* 0x000 */ short music_id;                       // 0x2
    /* 0x002 */ char difficult;                       // 0x1
    /* 0x003 */ char speed;                           // 0x1
    /* 0x004 */ char boost;                           // 0x1
    /* 0x005 */ char appearance;                      // 0x1
    /* 0x006 */ char turn;                            // 0x1
    /* 0x007 */ char scroll;                          // 0x1
    /* 0x008 */ char freeze_arrow;                    // 0x1
    /* 0x009 */ char little;                          // 0x1
    /* 0x00A */ char dark;                            // 0x1
    /* 0x00B */ char simultaneous;                    // 0x1
};

#endif /* DDR_types__nsv_music_data_work_H */
