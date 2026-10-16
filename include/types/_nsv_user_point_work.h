/* struct _nsv_user_point_work -- 4 members, size 0x1FC, layout c1b3d956dddd.
 *
 * One definition, agreed by the 33 units that declare it: net_main.c (DIE 0x77C1B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_user_point_work *`.
 *
 * declared by: net_main.c (DIE 0x77C1B), net_prg.c (DIE 0x85A6E), net_read_data.c (DIE 0x9413C), net_game_main.c (DIE 0x9B57C), net_game_window.c (DIE 0xA58AA), net_game_opt.c (DIE 0xB3680), net_game_logout.c (DIE 0xBA407), net_game_menu.c (DIE 0xBEA41), net_game_match.c (DIE 0xC3A7B), net_game_data.c (DIE 0xCBD3E), net_game_prac.c (DIE 0xD181C), net_game_list.c (DIE 0xD7217), net_sys_main.c (DIE 0x14CAC3), net_sys_menu.c (DIE 0x152830), net_sys_new.c (DIE 0x15738A), net_sys_top.c (DIE 0x15EB52), net_sys_user.c (DIE 0x16650A), net_sys_rule.c (DIE 0x16DBE3), net_sys_connect.c (DIE 0x171208), net_sys_info.c (DIE 0x175230), net_sys_logout.c (DIE 0x19BB18), net_win_suser.c (DIE 0x1A05AA), net_win_user.c (DIE 0x1AE166), net_play_main.c (DIE 0x1C5390), net_game_vs.c (DIE 0x1C86AF), net_sys_lobby.c (DIE 0x1EF763), net_game_rc.c (DIE 0x265E91), net_game_challenge.c (DIE 0x26C79C), net_win_peruser.c (DIE 0x2F5C5D), net_auth_main.c (DIE 0x3A9E95), net_cnf_main.c (DIE 0x3B50CC), net_dnas_main.c (DIE 0x3BD2EA), net_router_main.c (DIE 0x3C0C8B)
 */
#ifndef DDR_types__nsv_user_point_work_H
#define DDR_types__nsv_user_point_work_H

struct _nsv_user_point_week_log_work;
struct _nsv_user_point_week_param_work;
struct _nsv_user_point_year_param_work;

#include "types/_nsv_user_point_week_log_work.h"
#include "types/_nsv_user_point_week_param_work.h"
#include "types/_nsv_user_point_year_param_work.h"

struct _nsv_user_point_work {   // size 0x1FC
    /* 0x000 */ int log_count;                        // 0x4
    /* 0x004 */ struct _nsv_user_point_year_param_work year_param;  // 0xC
    /* 0x010 */ struct _nsv_user_point_week_param_work week_param;  // 0xC
    /* 0x01C */ struct _nsv_user_point_week_log_work week_log[60];  // 0x1E0
};

#endif /* DDR_types__nsv_user_point_work_H */
