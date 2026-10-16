/* struct _nsv_rc_table_list_work -- 2 members, size 0x3C04, layout 14cc4d7921dd.
 *
 * One definition, agreed by the 30 units that declare it: net_main.c (DIE 0x7B9ED).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_rc_table_list_work *`.
 *
 * declared by: net_main.c (DIE 0x7B9ED), net_prg.c (DIE 0x8948D), net_read_data.c (DIE 0x966F0), net_game_main.c (DIE 0x9EFF6), net_game_window.c (DIE 0xA8D6F), net_game_opt.c (DIE 0xB69CA), net_game_logout.c (DIE 0xBC9CD), net_game_menu.c (DIE 0xC0E92), net_game_match.c (DIE 0xC7723), net_game_data.c (DIE 0xCDD4A), net_game_prac.c (DIE 0xD3D67), net_game_list.c (DIE 0xDA30C), net_sys_main.c (DIE 0x14F1C4), net_sys_menu.c (DIE 0x1547CC), net_sys_new.c (DIE 0x15A3D6), net_sys_top.c (DIE 0x162670), net_sys_user.c (DIE 0x169E13), net_sys_rule.c (DIE 0x16FA11), net_sys_connect.c (DIE 0x1737A5), net_sys_info.c (DIE 0x1774A2), net_sys_logout.c (DIE 0x19DEA3), net_play_main.c (DIE 0x1C256E), net_game_vs.c (DIE 0x1CCD2B), net_sys_lobby.c (DIE 0x1F3243), net_game_rc.c (DIE 0x267E32), net_game_challenge.c (DIE 0x26F278), net_auth_main.c (DIE 0x3AD79E), net_cnf_main.c (DIE 0x3B76FF), net_dnas_main.c (DIE 0x3BF1A7), net_router_main.c (DIE 0x3C29EF)
 */
#ifndef DDR_types__nsv_rc_table_list_work_H
#define DDR_types__nsv_rc_table_list_work_H

struct _nsv_rc_table_param_work;

#include "types/_nsv_rc_table_param_work.h"

struct _nsv_rc_table_list_work {   // size 0x3C04
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ struct _nsv_rc_table_param_work list[120];  // 0x3C00
};

#endif /* DDR_types__nsv_rc_table_list_work_H */
