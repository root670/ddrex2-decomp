/* struct _net_pack_w -- 3 members, size 0x38, layout 0fa2e313c8b3.
 *
 * One definition, agreed by the 30 units that declare it: net_main.c (DIE 0x7D225).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _net_pack_w *`.
 *
 * declared by: net_main.c (DIE 0x7D225), net_prg.c (DIE 0x89FCC), net_read_data.c (DIE 0x986CA), net_game_main.c (DIE 0xA1A1F), net_game_window.c (DIE 0xA99D5), net_game_opt.c (DIE 0xB7682), net_game_logout.c (DIE 0xBCF92), net_game_menu.c (DIE 0xC168B), net_game_match.c (DIE 0xC82BA), net_game_data.c (DIE 0xCE3B3), net_game_prac.c (DIE 0xD437E), net_game_list.c (DIE 0xDAFF2), net_sys_main.c (DIE 0x151405), net_sys_menu.c (DIE 0x155317), net_sys_new.c (DIE 0x15B9F4), net_sys_top.c (DIE 0x162F32), net_sys_user.c (DIE 0x16A910), net_sys_rule.c (DIE 0x16FF84), net_sys_connect.c (DIE 0x173D18), net_sys_info.c (DIE 0x177C2F), net_sys_logout.c (DIE 0x19E468), net_play_main.c (DIE 0x1C54EE), net_game_vs.c (DIE 0x1CE9E9), net_sys_lobby.c (DIE 0x1F3EDE), net_game_rc.c (DIE 0x26816C), net_game_challenge.c (DIE 0x271287), net_auth_main.c (DIE 0x3AD934), net_cnf_main.c (DIE 0x3B53D0), net_dnas_main.c (DIE 0x3BF242), net_router_main.c (DIE 0x3C2190)
 */
#ifndef DDR_types__net_pack_w_H
#define DDR_types__net_pack_w_H

struct _net_pack_w {   // size 0x38
    /* 0x000 */ unsigned char *addr;                  // 0x4
    /* 0x004 */ int num;                              // 0x4
    /* 0x008 */ int size[12];                         // 0x30
};

#endif /* DDR_types__net_pack_w_H */
