/* struct _CWS_WIN_W -- 13 members, size 0x158, layout b5b2a95e578d.
 *
 * One definition, agreed by the 86 units that declare it: net_main.c (DIE 0x7CA85).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _CWS_WIN_W *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: net_main.c (DIE 0x7CA85), net_prg.c (DIE 0x89502), net_read_data.c (DIE 0x96355), net_game_main.c (DIE 0x9EBD4), net_game_window.c (DIE 0xA8824), net_game_opt.c (DIE 0xB647F), net_game_logout.c (DIE 0xBC67A), net_game_menu.c (DIE 0xC0B3F), net_game_match.c (DIE 0xC7143), net_game_data.c (DIE 0xCB06E), net_game_prac.c (DIE 0xD3A14), net_game_list.c (DIE 0xD6D73), cws_obj.c (DIE 0xEE6A9), cws_str.c (DIE 0xF08EA), cws_win.c (DIE 0xF4076), cws_wins.c (DIE 0xF630D), cws_win_multi.c (DIE 0xF7AA9), multi_window.c (DIE 0xFA58C), net_win_any.c (DIE 0xFC86F), fp_eyetoy.c (DIE 0x108B77), fp_opt.c (DIE 0x13DA71), net_win_menu.c (DIE 0x149E2B), net_sys_main.c (DIE 0x14EE71), net_sys_menu.c (DIE 0x154479), net_sys_new.c (DIE 0x15A088), net_sys_top.c (DIE 0x1622BA), net_sys_user.c (DIE 0x165874), net_sys_rule.c (DIE 0x16D621), net_sys_connect.c (DIE 0x173452), net_sys_info.c (DIE 0x17714F), net_sys_logout.c (DIE 0x19B556), net_win_suser.c (DIE 0x19F069), net_win_tab.c (DIE 0x1A1812), net_win_watch.c (DIE 0x1A35C2), net_win_search.c (DIE 0x1A4EB3), net_win_item.c (DIE 0x1AB25B), net_win_user.c (DIE 0x1ACA22), net_win_rcname.c (DIE 0x1BCB35), net_play_main.c (DIE 0x1C3D12), net_game_vs.c (DIE 0x1CC951), fp_msel_obj.c (DIE 0x1D5873), net_sys_lobby.c (DIE 0x1F2DAF), cws_win_multi2.c (DIE 0x1F5B88), net_win_bar.c (DIE 0x20B6A2), shop_obj.c (DIE 0x2213A2), shop_select.c (DIE 0x22C383), shop_disp.c (DIE 0x22E0FA), shop_info.c (DIE 0x23DB6F), dmm_mess.c (DIE 0x2416A5), net_win_slby.c (DIE 0x25042D), net_inter.c (DIE 0x2522EF), net_win_listbk.c (DIE 0x25309C), net_win_listsel.c (DIE 0x254C1D), net_win_listdtl2.c (DIE 0x25F001), net_win_listdtl.c (DIE 0x2604A2), net_win_listdtl3.c (DIE 0x262AE4), net_win_infoboard.c (DIE 0x263F7E), net_game_rc.c (DIE 0x267B08), net_game_challenge.c (DIE 0x26ECBD), adv_main.c (DIE 0x28C7FB), net_win_infosel.c (DIE 0x2A0F65), net_win_rccssel.c (DIE 0x2A2722), tra_menu.c (DIE 0x2A7C6F), tra_main.c (DIE 0x2B2463), net_game_vs_win.c (DIE 0x2BE78A), tra_res.c (DIE 0x2E3E68), net_win_base.c (DIE 0x2F0A61), net_win_peruser.c (DIE 0x2F4870), net_win_perhead.c (DIE 0x2F6844), net_win_perpoint.c (DIE 0x2F82E5), net_win_perrank.c (DIE 0x2F97D7), net_win_perstats.c (DIE 0x2FAD16), net_win_dhead.c (DIE 0x302053), net_win_dpoint.c (DIE 0x303BC3), info.c (DIE 0x332EDA), net_auth_main.c (DIE 0x3A355D), net_cnf_main.c (DIE 0x3B0F91), net_dnas_main.c (DIE 0x3BEF22), net_router_main.c (DIE 0x3C1D2C), dmm_result.c (DIE 0x40D3D4), dmm_select.c (DIE 0x414D4A), dmm_style.c (DIE 0x427002), opt_main.c (DIE 0x43FC7B), workout_usrrpass.c (DIE 0x46788D), workout_message.c (DIE 0x46E04B), rec_co.c (DIE 0x475794)
 */
#ifndef DDR_types__CWS_WIN_W_H
#define DDR_types__CWS_WIN_W_H

struct _CWS_OBJ;
struct _CWS_STR;
struct _CWS_WIN_DATA;

#include "types/_CWS_OBJ.h"
#include "types/_CWS_STR.h"
#include "types/_CWS_WIN_DATA.h"

struct _CWS_WIN_W {   // size 0x158
    /* 0x000 */ int (*func)(struct _CWS_WIN_W *);     // 0x4
    /* 0x004 */ unsigned int status;                  // 0x4
    /* 0x008 */ char step[4];                         // 0x4
    /* 0x00C */ struct {   // size 0x8
        /* 0x000 */ short x;                              // 0x2
        /* 0x002 */ short y;                              // 0x2
        /* 0x004 */ short w;                              // 0x2
        /* 0x006 */ short h;                              // 0x2
    } def;
    /* 0x014 */ struct _CWS_WIN_DATA v;               // 0x1C
    /* 0x030 */ struct _CWS_WIN_DATA s;               // 0x1C
    /* 0x04C */ int timer;                            // 0x4
    /* 0x050 */ char code;                            // 0x1
    /* 0x051 */ char mode;                            // 0x1
    /* 0x052 */ // 0x2 bytes padding
    /* 0x054 */ int work[32];                         // 0x80
    /* 0x0D4 */ struct _CWS_OBJ *obj[16];             // 0x40
    /* 0x114 */ struct _CWS_STR *str[16];             // 0x40
    /* 0x154 */ struct _CWS_WIN_W *master_link;       // 0x4
};

#endif /* DDR_types__CWS_WIN_W_H */
