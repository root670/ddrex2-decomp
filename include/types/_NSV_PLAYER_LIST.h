/* struct _NSV_PLAYER_LIST -- 1 members, size 0x14820, layout a3ac257d1322.
 *
 * One definition, agreed by the 30 units that declare it: net_main.c (DIE 0x786E6).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NSV_PLAYER_LIST *`.
 *
 * declared by: net_main.c (DIE 0x786E6), net_prg.c (DIE 0x8B989), net_read_data.c (DIE 0x940A6), net_game_main.c (DIE 0x9ADCB), net_game_window.c (DIE 0xA4E55), net_game_opt.c (DIE 0xB2DC3), net_game_logout.c (DIE 0xBA395), net_game_menu.c (DIE 0xBE9CF), net_game_match.c (DIE 0xC38E6), net_game_data.c (DIE 0xCBB96), net_game_prac.c (DIE 0xD17AA), net_game_list.c (DIE 0xD6199), net_sys_main.c (DIE 0x14CA2D), net_sys_menu.c (DIE 0x1527BE), net_sys_new.c (DIE 0x157318), net_sys_top.c (DIE 0x15E931), net_sys_user.c (DIE 0x16637A), net_sys_rule.c (DIE 0x16DB71), net_sys_connect.c (DIE 0x171196), net_sys_info.c (DIE 0x1751BE), net_sys_logout.c (DIE 0x19BAA6), net_play_main.c (DIE 0x1C25E3), net_game_vs.c (DIE 0x1C8171), net_sys_lobby.c (DIE 0x1EF5F7), net_game_rc.c (DIE 0x265E1F), net_game_challenge.c (DIE 0x26CA49), net_auth_main.c (DIE 0x3A56C0), net_cnf_main.c (DIE 0x3B1755), net_dnas_main.c (DIE 0x3BC65C), net_router_main.c (DIE 0x3C31D8)
 */
#ifndef DDR_types__NSV_PLAYER_LIST_H
#define DDR_types__NSV_PLAYER_LIST_H

struct _nsv_player_list_file;

#include "types/_nsv_player_list_file.h"

struct _NSV_PLAYER_LIST {   // size 0x14820
    /* 0x000 */ struct _nsv_player_list_file list[1000];  // 0x14820
};

#endif /* DDR_types__NSV_PLAYER_LIST_H */
