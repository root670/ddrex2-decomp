/* struct _nsv_user_htoh_work -- 6 members, size 0x330, layout ebd9d25a43be.
 *
 * One definition, agreed by the 33 units that declare it: net_main.c (DIE 0x7ADDA).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_user_htoh_work *`.
 *
 * declared by: net_main.c (DIE 0x7ADDA), net_prg.c (DIE 0x8907E), net_read_data.c (DIE 0x9622E), net_game_main.c (DIE 0x9E68C), net_game_window.c (DIE 0xA868D), net_game_opt.c (DIE 0xB62E8), net_game_logout.c (DIE 0xBC52F), net_game_menu.c (DIE 0xC0988), net_game_match.c (DIE 0xC6A19), net_game_data.c (DIE 0xCDA95), net_game_prac.c (DIE 0xD38C9), net_game_list.c (DIE 0xD9E13), net_sys_main.c (DIE 0x14ED02), net_sys_menu.c (DIE 0x15432E), net_sys_new.c (DIE 0x159E3F), net_sys_top.c (DIE 0x1620BC), net_sys_user.c (DIE 0x169A43), net_sys_rule.c (DIE 0x16F733), net_sys_connect.c (DIE 0x173307), net_sys_info.c (DIE 0x177004), net_sys_logout.c (DIE 0x19DBC5), net_win_suser.c (DIE 0x19F784), net_win_user.c (DIE 0x1ACDF6), net_play_main.c (DIE 0x1C1D15), net_game_vs.c (DIE 0x1CC5C1), net_sys_lobby.c (DIE 0x1F2C18), net_game_rc.c (DIE 0x267973), net_game_challenge.c (DIE 0x26EECD), net_win_peruser.c (DIE 0x2F4C1E), net_auth_main.c (DIE 0x3AD289), net_cnf_main.c (DIE 0x3B74AC), net_dnas_main.c (DIE 0x3BED8B), net_router_main.c (DIE 0x3C27EB)
 */
#ifndef DDR_types__nsv_user_htoh_work_H
#define DDR_types__nsv_user_htoh_work_H

struct _nsv_user_htoh_week_log_work;
struct _nsv_user_htoh_week_param_work;
struct _nsv_user_htoh_year_param_work;
struct _nsv_user_htoh_year_rule_work;

#include "types/_nsv_user_htoh_week_log_work.h"
#include "types/_nsv_user_htoh_week_param_work.h"
#include "types/_nsv_user_htoh_year_param_work.h"
#include "types/_nsv_user_htoh_year_rule_work.h"

struct _nsv_user_htoh_work {   // size 0x330
    /* 0x000 */ unsigned int dis_connect_count;       // 0x4
    /* 0x004 */ int log_count;                        // 0x4
    /* 0x008 */ struct _nsv_user_htoh_year_param_work year_param;  // 0x18
    /* 0x020 */ struct _nsv_user_htoh_year_rule_work year_rule_param[3];  // 0x30
    /* 0x050 */ struct _nsv_user_htoh_week_param_work week_param;  // 0x10
    /* 0x060 */ struct _nsv_user_htoh_week_log_work week_log[60];  // 0x2D0
};

#endif /* DDR_types__nsv_user_htoh_work_H */
