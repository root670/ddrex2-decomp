/* struct _net_prg_w -- 6 members, size 0xC, layout a06588bd66ef.
 *
 * One definition, agreed by the 30 units that declare it: net_main.c (DIE 0x7C085).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _net_prg_w *`.
 *
 * declared by: net_main.c (DIE 0x7C085), net_prg.c (DIE 0x887C9), net_read_data.c (DIE 0x965F9), net_game_main.c (DIE 0x9EEFF), net_game_window.c (DIE 0xA8C78), net_game_opt.c (DIE 0xB68D3), net_game_logout.c (DIE 0xBC8D6), net_game_menu.c (DIE 0xC0D9B), net_game_match.c (DIE 0xC762C), net_game_data.c (DIE 0xCDC53), net_game_prac.c (DIE 0xD3C70), net_game_list.c (DIE 0xDA215), net_sys_main.c (DIE 0x14F0CD), net_sys_menu.c (DIE 0x1546D5), net_sys_new.c (DIE 0x15A295), net_sys_top.c (DIE 0x162579), net_sys_user.c (DIE 0x169D1C), net_sys_rule.c (DIE 0x16F91A), net_sys_connect.c (DIE 0x1736AE), net_sys_info.c (DIE 0x1773AB), net_sys_logout.c (DIE 0x19DDAC), net_play_main.c (DIE 0x1C51A5), net_game_vs.c (DIE 0x1CCC34), net_sys_lobby.c (DIE 0x1F314C), net_game_rc.c (DIE 0x267D3B), net_game_challenge.c (DIE 0x2705A8), net_auth_main.c (DIE 0x3ACB6F), net_cnf_main.c (DIE 0x3B4C96), net_dnas_main.c (DIE 0x3BE10B), net_router_main.c (DIE 0x3C132C)
 */
#ifndef DDR_types__net_prg_w_H
#define DDR_types__net_prg_w_H

struct _net_prg_w {   // size 0xC
    /* 0x000 */ char step;                            // 0x1
    /* 0x001 */ char s_step;                          // 0x1
    /* 0x002 */ char err_step;                        // 0x1
    /* 0x003 */ char err_code;                        // 0x1
    /* 0x004 */ int counter;                          // 0x4
    /* 0x008 */ int timer;                            // 0x4
};

#endif /* DDR_types__net_prg_w_H */
