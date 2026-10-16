/* struct _CWS_STR -- 16 members, size 0xB0, layout 281a48008484.
 *
 * One definition, agreed by the 86 units that declare it: net_main.c (DIE 0x76D9D).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _CWS_STR *`.
 *
 * declared by: net_main.c (DIE 0x76D9D), net_prg.c (DIE 0x8B0DB), net_read_data.c (DIE 0x926DC), net_game_main.c (DIE 0xA165F), net_game_window.c (DIE 0xA974A), net_game_opt.c (DIE 0xB73F7), net_game_logout.c (DIE 0xBCD07), net_game_menu.c (DIE 0xC1400), net_game_match.c (DIE 0xC802F), net_game_data.c (DIE 0xCE0FF), net_game_prac.c (DIE 0xD40F3), net_game_list.c (DIE 0xDAD67), cws_obj.c (DIE 0xEF500), cws_str.c (DIE 0xF0AD3), cws_win.c (DIE 0xF4B4A), cws_wins.c (DIE 0xF6E54), cws_win_multi.c (DIE 0xF8CDE), multi_window.c (DIE 0xFA835), net_win_any.c (DIE 0xFD2A9), fp_eyetoy.c (DIE 0x10885A), fp_opt.c (DIE 0x13D623), net_win_menu.c (DIE 0x14A81A), net_sys_main.c (DIE 0x15117A), net_sys_menu.c (DIE 0x15508C), net_sys_new.c (DIE 0x15C45F), net_sys_top.c (DIE 0x16302E), net_sys_user.c (DIE 0x16A685), net_sys_rule.c (DIE 0x16FCF9), net_sys_connect.c (DIE 0x173A8D), net_sys_info.c (DIE 0x17797B), net_sys_logout.c (DIE 0x19E1DD), net_win_suser.c (DIE 0x1A0676), net_win_tab.c (DIE 0x1A286C), net_win_watch.c (DIE 0x1A40FE), net_win_search.c (DIE 0x1A948C), net_win_item.c (DIE 0x1ABD0A), net_win_user.c (DIE 0x1AE232), net_win_rcname.c (DIE 0x1BD750), net_play_main.c (DIE 0x1C4721), net_game_vs.c (DIE 0x1CF454), fp_msel_obj.c (DIE 0x1D726E), net_sys_lobby.c (DIE 0x1F3C2D), cws_win_multi2.c (DIE 0x1F6A64), net_win_bar.c (DIE 0x20C2F3), shop_obj.c (DIE 0x221C76), shop_select.c (DIE 0x22C033), shop_disp.c (DIE 0x231AAD), shop_info.c (DIE 0x23DDF2), dmm_mess.c (DIE 0x241BFC), net_win_slby.c (DIE 0x250F2B), net_inter.c (DIE 0x252572), net_win_listbk.c (DIE 0x253E79), net_win_listsel.c (DIE 0x255AEF), net_win_listdtl2.c (DIE 0x25F9F8), net_win_listdtl.c (DIE 0x261627), net_win_listdtl3.c (DIE 0x263568), net_win_infoboard.c (DIE 0x264A07), net_game_rc.c (DIE 0x268268), net_game_challenge.c (DIE 0x26A5E0), adv_main.c (DIE 0x291283), net_win_infosel.c (DIE 0x2A1959), net_win_rccssel.c (DIE 0x2A3AEE), tra_menu.c (DIE 0x2A8CA8), tra_main.c (DIE 0x2B3EC1), net_game_vs_win.c (DIE 0x2C29DF), tra_res.c (DIE 0x2E4F5B), net_win_base.c (DIE 0x2F1739), net_win_peruser.c (DIE 0x2F5D52), net_win_perhead.c (DIE 0x2F7220), net_win_perpoint.c (DIE 0x2F886A), net_win_perrank.c (DIE 0x2F9D5C), net_win_perstats.c (DIE 0x2FB332), net_win_dhead.c (DIE 0x3029F8), net_win_dpoint.c (DIE 0x30458E), info.c (DIE 0x333DD4), net_auth_main.c (DIE 0x3A6876), net_cnf_main.c (DIE 0x3B26AA), net_dnas_main.c (DIE 0x3BBB6D), net_router_main.c (DIE 0x3C3643), dmm_result.c (DIE 0x40F44C), dmm_select.c (DIE 0x4148FE), dmm_style.c (DIE 0x428ECD), opt_main.c (DIE 0x4404FA), workout_usrrpass.c (DIE 0x46762B), workout_message.c (DIE 0x46E513), rec_co.c (DIE 0x476184)
 */
#ifndef DDR_types__CWS_STR_H
#define DDR_types__CWS_STR_H

struct _CWS_STR {   // size 0xB0
    /* 0x000 */ int tex_id;                           // 0x4
    /* 0x004 */ int x;                                // 0x4
    /* 0x008 */ int y;                                // 0x4
    /* 0x00C */ int z;                                // 0x4
    /* 0x010 */ int font_type;                        // 0x4
    /* 0x014 */ unsigned int status;                  // 0x4
    /* 0x018 */ unsigned int mode_flag;               // 0x4
    /* 0x01C */ unsigned char bri;                    // 0x1
    /* 0x01D */ unsigned char a;                      // 0x1
    /* 0x01E */ unsigned char col;                    // 0x1
    /* 0x01F */ unsigned char dmy;                    // 0x1
    /* 0x020 */ int rx_num;                           // 0x4
    /* 0x024 */ int ry_num;                           // 0x4
    /* 0x028 */ int rx_size;                          // 0x4
    /* 0x02C */ int ry_size;                          // 0x4
    /* 0x030 */ unsigned char string[128];            // 0x80
};

#endif /* DDR_types__CWS_STR_H */
