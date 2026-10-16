/* struct _CWS_OBJ_SET -- 8 members, size 0x14, layout c975d65cd9ee.
 *
 * One definition, agreed by the 86 units that declare it: net_main.c (DIE 0x7B897).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _CWS_OBJ_SET *`.
 *
 * declared by: net_main.c (DIE 0x7B897), net_prg.c (DIE 0x86CA6), net_read_data.c (DIE 0x949A4), net_game_main.c (DIE 0x9C6F4), net_game_window.c (DIE 0xA67FF), net_game_opt.c (DIE 0xB48D3), net_game_logout.c (DIE 0xBAB4A), net_game_menu.c (DIE 0xBF44C), net_game_match.c (DIE 0xC4DA7), net_game_data.c (DIE 0xCC42A), net_game_prac.c (DIE 0xD250E), net_game_list.c (DIE 0xD83F9), cws_obj.c (DIE 0xEE892), cws_str.c (DIE 0xF0E8D), cws_win.c (DIE 0xF43B7), cws_wins.c (DIE 0xF66C1), cws_win_multi.c (DIE 0xF84D5), multi_window.c (DIE 0xFAC41), net_win_any.c (DIE 0xFCCBD), fp_eyetoy.c (DIE 0x10D74D), fp_opt.c (DIE 0x143F56), net_win_menu.c (DIE 0x14A208), net_sys_main.c (DIE 0x14D350), net_sys_menu.c (DIE 0x152F73), net_sys_new.c (DIE 0x158356), net_sys_top.c (DIE 0x16000D), net_sys_user.c (DIE 0x16794F), net_sys_rule.c (DIE 0x16E326), net_sys_connect.c (DIE 0x171F4C), net_sys_info.c (DIE 0x175973), net_sys_logout.c (DIE 0x19C80A), net_win_suser.c (DIE 0x19FCB9), net_win_tab.c (DIE 0x1A1ED5), net_win_watch.c (DIE 0x1A3AC0), net_win_search.c (DIE 0x1A7259), net_win_item.c (DIE 0x1AB686), net_win_user.c (DIE 0x1AD4F0), net_win_rcname.c (DIE 0x1BD0EC), net_play_main.c (DIE 0x1C1E60), net_game_vs.c (DIE 0x1CA312), fp_msel_obj.c (DIE 0x1D35CB), net_sys_lobby.c (DIE 0x1F1223), cws_win_multi2.c (DIE 0x1F63B3), net_win_bar.c (DIE 0x20BF21), shop_obj.c (DIE 0x21FA09), shop_select.c (DIE 0x22C841), shop_disp.c (DIE 0x22F044), shop_info.c (DIE 0x23D2B5), dmm_mess.c (DIE 0x23F8EF), net_win_slby.c (DIE 0x2508C7), net_inter.c (DIE 0x251DC3), net_win_listbk.c (DIE 0x25355C), net_win_listsel.c (DIE 0x25548B), net_win_listdtl2.c (DIE 0x25F3BA), net_win_listdtl.c (DIE 0x260F56), net_win_listdtl3.c (DIE 0x262F7C), net_win_infoboard.c (DIE 0x2643C9), net_game_rc.c (DIE 0x266626), net_game_challenge.c (DIE 0x26D500), adv_main.c (DIE 0x28D3CA), net_win_infosel.c (DIE 0x2A1344), net_win_rccssel.c (DIE 0x2A2EBB), tra_menu.c (DIE 0x2A6178), tra_main.c (DIE 0x2B050D), net_game_vs_win.c (DIE 0x2C00ED), tra_res.c (DIE 0x2E285B), net_win_base.c (DIE 0x2F0DC8), net_win_peruser.c (DIE 0x2F5343), net_win_perhead.c (DIE 0x2F7005), net_win_perpoint.c (DIE 0x2F864F), net_win_perrank.c (DIE 0x2F9B41), net_win_perstats.c (DIE 0x2FB117), net_win_dhead.c (DIE 0x302432), net_win_dpoint.c (DIE 0x303F79), info.c (DIE 0x333854), net_auth_main.c (DIE 0x3A5544), net_cnf_main.c (DIE 0x3B14AF), net_dnas_main.c (DIE 0x3BDD6A), net_router_main.c (DIE 0x3C2592), dmm_result.c (DIE 0x40C262), dmm_select.c (DIE 0x41988A), dmm_style.c (DIE 0x426CCC), opt_main.c (DIE 0x43F599), workout_usrrpass.c (DIE 0x468AD6), workout_message.c (DIE 0x46DEF5), rec_co.c (DIE 0x4746D1)
 */
#ifndef DDR_types__CWS_OBJ_SET_H
#define DDR_types__CWS_OBJ_SET_H

struct _CWS_OBJ_TEX;

#include "types/_CWS_OBJ_TEX.h"

struct _CWS_OBJ_SET {   // size 0x14
    /* 0x000 */ int (*func)(void *, void *);          // 0x4
    /* 0x004 */ int tex_num;                          // 0x4
    /* 0x008 */ int ptex_obj;                         // 0x4
    /* 0x00C */ struct _CWS_OBJ_TEX *ptex;            // 0x4
    /* 0x010 */ unsigned char r;                      // 0x1
    /* 0x011 */ unsigned char g;                      // 0x1
    /* 0x012 */ unsigned char b;                      // 0x1
    /* 0x013 */ unsigned char a;                      // 0x1
};

#endif /* DDR_types__CWS_OBJ_SET_H */
