/* struct _CWS_OBJ -- 18 members, size 0x3C, layout b5090497e788.
 *
 * One definition, agreed by the 86 units that declare it: net_main.c (DIE 0x7C3D6).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _CWS_OBJ *`.
 *
 * declared by: net_main.c (DIE 0x7C3D6), net_prg.c (DIE 0x88903), net_read_data.c (DIE 0x95ADC), net_game_main.c (DIE 0x9DDBC), net_game_window.c (DIE 0xA7E6E), net_game_opt.c (DIE 0xB5AC9), net_game_logout.c (DIE 0xBBE46), net_game_menu.c (DIE 0xC016B), net_game_match.c (DIE 0xC6248), net_game_data.c (DIE 0xCD383), net_game_prac.c (DIE 0xD3209), net_game_list.c (DIE 0xD95CB), cws_obj.c (DIE 0xEE43D), cws_str.c (DIE 0xF1431), cws_win.c (DIE 0xF4677), cws_wins.c (DIE 0xF6981), cws_win_multi.c (DIE 0xF8269), multi_window.c (DIE 0xFAF01), net_win_any.c (DIE 0xFCFA3), fp_eyetoy.c (DIE 0x10857D), fp_opt.c (DIE 0x146956), net_win_menu.c (DIE 0x14A514), net_sys_main.c (DIE 0x14E561), net_sys_menu.c (DIE 0x153C6E), net_sys_new.c (DIE 0x15975E), net_sys_top.c (DIE 0x1619A2), net_sys_user.c (DIE 0x169296), net_sys_rule.c (DIE 0x16F04A), net_sys_connect.c (DIE 0x172C47), net_sys_info.c (DIE 0x176944), net_sys_logout.c (DIE 0x19D505), net_win_suser.c (DIE 0x1A00AC), net_win_tab.c (DIE 0x1A21BB), net_win_watch.c (DIE 0x1A3D80), net_win_search.c (DIE 0x1A738B), net_win_item.c (DIE 0x1AB992), net_win_user.c (DIE 0x1AD958), net_win_rcname.c (DIE 0x1BD3AC), net_play_main.c (DIE 0x1C29E4), net_game_vs.c (DIE 0x1CBEA7), fp_msel_obj.c (DIE 0x1D4AF9), net_sys_lobby.c (DIE 0x1F246B), cws_win_multi2.c (DIE 0x1F6147), net_win_bar.c (DIE 0x20B88B), shop_obj.c (DIE 0x220CA7), shop_select.c (DIE 0x22CC67), shop_disp.c (DIE 0x230B4E), shop_info.c (DIE 0x23D802), dmm_mess.c (DIE 0x24105B), net_win_slby.c (DIE 0x250BD9), net_inter.c (DIE 0x252083), net_win_listbk.c (DIE 0x253A9E), net_win_listsel.c (DIE 0x255771), net_win_listdtl2.c (DIE 0x25F67A), net_win_listdtl.c (DIE 0x26068B), net_win_listdtl3.c (DIE 0x26323C), net_win_infoboard.c (DIE 0x2646AF), net_game_rc.c (DIE 0x267348), net_game_challenge.c (DIE 0x26E419), adv_main.c (DIE 0x28EFD1), net_win_infosel.c (DIE 0x2A1604), net_win_rccssel.c (DIE 0x2A36CB), tra_menu.c (DIE 0x2A792B), tra_main.c (DIE 0x2B1C37), net_game_vs_win.c (DIE 0x2BFB1D), tra_res.c (DIE 0x2E3B6C), net_win_base.c (DIE 0x2F135E), net_win_peruser.c (DIE 0x2F5736), net_win_perhead.c (DIE 0x2F6B81), net_win_perpoint.c (DIE 0x2F7FE2), net_win_perrank.c (DIE 0x2F94D4), net_win_perstats.c (DIE 0x2FAAAA), net_win_dhead.c (DIE 0x3026F2), net_win_dpoint.c (DIE 0x304262), info.c (DIE 0x3320FD), net_auth_main.c (DIE 0x3A6551), net_cnf_main.c (DIE 0x3B1C85), net_dnas_main.c (DIE 0x3BEB1F), net_router_main.c (DIE 0x3C2C2D), dmm_result.c (DIE 0x40D88E), dmm_select.c (DIE 0x41AD2A), dmm_style.c (DIE 0x4280F9), opt_main.c (DIE 0x43F9A1), workout_usrrpass.c (DIE 0x46927A), workout_message.c (DIE 0x46E27E), rec_co.c (DIE 0x4753D0)
 */
#ifndef DDR_types__CWS_OBJ_H
#define DDR_types__CWS_OBJ_H

struct _CWS_OBJ_SET;
struct _CWS_OBJ_TEX;

#include "types/_CWS_OBJ_SET.h"
#include "types/_CWS_OBJ_TEX.h"

struct _CWS_OBJ {   // size 0x3C
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int tu;                               // 0x4
    /* 0x014 */ int tv;                               // 0x4
    /* 0x018 */ int tw;                               // 0x4
    /* 0x01C */ int th;                               // 0x4
    /* 0x020 */ int z;                                // 0x4
    /* 0x024 */ unsigned char red;                    // 0x1
    /* 0x025 */ unsigned char green;                  // 0x1
    /* 0x026 */ unsigned char blue;                   // 0x1
    /* 0x027 */ unsigned char alpha;                  // 0x1
    /* 0x028 */ int timer;                            // 0x4
    /* 0x02C */ int tex_num;                          // 0x4
    /* 0x030 */ unsigned int status;                  // 0x4
    /* 0x034 */ struct _CWS_OBJ_TEX *ptex;            // 0x4
    /* 0x038 */ struct _CWS_OBJ_SET *def;             // 0x4
};

#endif /* DDR_types__CWS_OBJ_H */
