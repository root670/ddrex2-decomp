/* struct _nsv_rc_table_param_work -- 8 members, size 0x80, layout fbabdf216228.
 *
 * One definition, agreed by the 31 units that declare it: net_main.c (DIE 0x78CC8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_rc_table_param_work *`.
 *
 * declared by: net_main.c (DIE 0x78CC8), net_prg.c (DIE 0x85B3A), net_read_data.c (DIE 0x94208), net_game_main.c (DIE 0x9B66C), net_game_window.c (DIE 0xA5B58), net_game_opt.c (DIE 0xB3794), net_game_logout.c (DIE 0xBA4D3), net_game_menu.c (DIE 0xBEB0D), net_game_match.c (DIE 0xC3B94), net_game_data.c (DIE 0xCAD2E), net_game_prac.c (DIE 0xD18E8), net_game_list.c (DIE 0xD732B), net_sys_main.c (DIE 0x14CB8F), net_sys_menu.c (DIE 0x1528FC), net_sys_new.c (DIE 0x157456), net_sys_top.c (DIE 0x15EC69), net_sys_user.c (DIE 0x166A45), net_sys_rule.c (DIE 0x16DCAF), net_sys_connect.c (DIE 0x1712D4), net_sys_info.c (DIE 0x1752FC), net_sys_logout.c (DIE 0x19BBE4), net_play_main.c (DIE 0x1C1A98), net_game_vs.c (DIE 0x1C87C8), net_sys_lobby.c (DIE 0x1EF853), net_game_rc.c (DIE 0x265F5D), net_game_challenge.c (DIE 0x26C8B2), net_win_rccssel.c (DIE 0x2A290B), net_auth_main.c (DIE 0x3A8E3F), net_cnf_main.c (DIE 0x3B6E1C), net_dnas_main.c (DIE 0x3BCDCF), net_router_main.c (DIE 0x3C201F)
 */
#ifndef DDR_types__nsv_rc_table_param_work_H
#define DDR_types__nsv_rc_table_param_work_H

struct _nsv_music_data_work;

#include "types/_nsv_music_data_work.h"

struct _nsv_rc_table_param_work {   // size 0x80
    /* 0x000 */ short serial_number;                  // 0x2
    /* 0x002 */ char kind;                            // 0x1
    /* 0x003 */ char counter;                         // 0x1
    /* 0x004 */ char lim_entry_type;                  // 0x1
    /* 0x005 */ char dance_gauge_type;                // 0x1
    /* 0x006 */ char rule_type;                       // 0x1
    /* 0x007 */ char max_entry_num;                   // 0x1
    /* 0x008 */ struct _nsv_music_data_work music_data[10];  // 0x78
};

#endif /* DDR_types__nsv_rc_table_param_work_H */
