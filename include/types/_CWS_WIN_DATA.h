/* struct _CWS_WIN_DATA -- 10 members, size 0x1C, layout c6815d757ea0.
 *
 * One definition, agreed by the 86 units that declare it: net_main.c (DIE 0x7C1C9).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _CWS_WIN_DATA *`.
 *
 * declared by: net_main.c (DIE 0x7C1C9), net_prg.c (DIE 0x88322), net_read_data.c (DIE 0x95834), net_game_main.c (DIE 0x9DA87), net_game_window.c (DIE 0xA7AE7), net_game_opt.c (DIE 0xB5794), net_game_logout.c (DIE 0xBBBC2), net_game_menu.c (DIE 0xBFEE7), net_game_match.c (DIE 0xC5F13), net_game_data.c (DIE 0xCD0FF), net_game_prac.c (DIE 0xD2F85), net_game_list.c (DIE 0xD9296), cws_obj.c (DIE 0xEF145), cws_str.c (DIE 0xF12DD), cws_win.c (DIE 0xF4523), cws_wins.c (DIE 0xF682D), cws_win_multi.c (DIE 0xF893B), multi_window.c (DIE 0xFADAD), net_win_any.c (DIE 0xFCE4F), fp_eyetoy.c (DIE 0x10DA49), fp_opt.c (DIE 0x146647), net_win_menu.c (DIE 0x14A3C0), net_sys_main.c (DIE 0x14E2DD), net_sys_menu.c (DIE 0x1539EA), net_sys_new.c (DIE 0x15959B), net_sys_top.c (DIE 0x1617DF), net_sys_user.c (DIE 0x168F61), net_sys_rule.c (DIE 0x16ED9D), net_sys_connect.c (DIE 0x1729C3), net_sys_info.c (DIE 0x1766C0), net_sys_logout.c (DIE 0x19D281), net_win_suser.c (DIE 0x19FF32), net_win_tab.c (DIE 0x1A2067), net_win_watch.c (DIE 0x1A3C2C), net_win_search.c (DIE 0x1A801F), net_win_item.c (DIE 0x1AB83E), net_win_user.c (DIE 0x1ADCD7), net_win_rcname.c (DIE 0x1BD258), net_play_main.c (DIE 0x1C2890), net_game_vs.c (DIE 0x1CBCC0), fp_msel_obj.c (DIE 0x1D4795), net_sys_lobby.c (DIE 0x1F2112), cws_win_multi2.c (DIE 0x1F6819), net_win_bar.c (DIE 0x20C08D), shop_obj.c (DIE 0x220A3C), shop_select.c (DIE 0x22CA6D), shop_disp.c (DIE 0x2308E3), shop_info.c (DIE 0x23D64F), dmm_mess.c (DIE 0x240EC5), net_win_slby.c (DIE 0x250A85), net_inter.c (DIE 0x251F2F), net_win_listbk.c (DIE 0x25394A), net_win_listsel.c (DIE 0x25561D), net_win_listdtl2.c (DIE 0x25F526), net_win_listdtl.c (DIE 0x2613B6), net_win_listdtl3.c (DIE 0x2630E8), net_win_infoboard.c (DIE 0x26455B), net_game_rc.c (DIE 0x2671A9), net_game_challenge.c (DIE 0x26E2C5), adv_main.c (DIE 0x28DD47), net_win_infosel.c (DIE 0x2A14B0), net_win_rccssel.c (DIE 0x2A3577), tra_menu.c (DIE 0x2A77D7), tra_main.c (DIE 0x2B1A09), net_game_vs_win.c (DIE 0x2C0918), tra_res.c (DIE 0x2E39F4), net_win_base.c (DIE 0x2F120A), net_win_peruser.c (DIE 0x2F55E2), net_win_perhead.c (DIE 0x2F6A2D), net_win_perpoint.c (DIE 0x2F7E10), net_win_perrank.c (DIE 0x2F9380), net_win_perstats.c (DIE 0x2FA956), net_win_dhead.c (DIE 0x30259E), net_win_dpoint.c (DIE 0x30410E), info.c (DIE 0x331E75), net_auth_main.c (DIE 0x3ADF10), net_cnf_main.c (DIE 0x3B7AB7), net_dnas_main.c (DIE 0x3BE9CB), net_router_main.c (DIE 0x3C2AD9), dmm_result.c (DIE 0x40D653), dmm_select.c (DIE 0x41ABD6), dmm_style.c (DIE 0x427F11), opt_main.c (DIE 0x43F84D), workout_usrrpass.c (DIE 0x469004), workout_message.c (DIE 0x46E887), rec_co.c (DIE 0x47520B)
 */
#ifndef DDR_types__CWS_WIN_DATA_H
#define DDR_types__CWS_WIN_DATA_H

struct _CWS_WIN_DATA {   // size 0x1C
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int z;                                // 0x4
    /* 0x014 */ int bri;                              // 0x4
    /* 0x018 */ unsigned char r;                      // 0x1
    /* 0x019 */ unsigned char g;                      // 0x1
    /* 0x01A */ unsigned char b;                      // 0x1
    /* 0x01B */ unsigned char a;                      // 0x1
};

#endif /* DDR_types__CWS_WIN_DATA_H */
