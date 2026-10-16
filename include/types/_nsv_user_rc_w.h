/* struct _nsv_user_rc_w -- 3 members, size 0x968, layout a2bc09be150e.
 *
 * One definition, agreed by the 33 units that declare it: net_main.c (DIE 0x7F532).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_user_rc_w *`.
 *
 * declared by: net_main.c (DIE 0x7F532), net_prg.c (DIE 0x8C503), net_read_data.c (DIE 0x92AD4), net_game_main.c (DIE 0xA321A), net_game_window.c (DIE 0xAABF0), net_game_opt.c (DIE 0xB885F), net_game_logout.c (DIE 0xBD455), net_game_menu.c (DIE 0xC1C14), net_game_match.c (DIE 0xC9349), net_game_data.c (DIE 0xCE995), net_game_prac.c (DIE 0xD488E), net_game_list.c (DIE 0xDC1D4), net_sys_main.c (DIE 0x151C6C), net_sys_menu.c (DIE 0x155855), net_sys_new.c (DIE 0x15D0D0), net_sys_top.c (DIE 0x1643F5), net_sys_user.c (DIE 0x16BC0A), net_sys_rule.c (DIE 0x170470), net_sys_connect.c (DIE 0x174204), net_sys_info.c (DIE 0x178144), net_sys_logout.c (DIE 0x19E954), net_win_suser.c (DIE 0x19FE4B), net_win_user.c (DIE 0x1ADBED), net_play_main.c (DIE 0x1C465B), net_game_vs.c (DIE 0x1D0DED), net_sys_lobby.c (DIE 0x1F50AD), net_game_rc.c (DIE 0x268A0D), net_game_challenge.c (DIE 0x26B07B), net_win_peruser.c (DIE 0x2F54FB), net_auth_main.c (DIE 0x3A729C), net_cnf_main.c (DIE 0x3B3082), net_dnas_main.c (DIE 0x3BBAD0), net_router_main.c (DIE 0x3C38D0)
 */
#ifndef DDR_types__nsv_user_rc_w_H
#define DDR_types__nsv_user_rc_w_H

struct _nsv_user_rc_param_work;

#include "types/_nsv_user_rc_param_work.h"

struct _nsv_user_rc_w {   // size 0x968
    /* 0x000 */ int log_count;                        // 0x4
    /* 0x004 */ char challenge_num[2];                // 0x2
    /* 0x006 */ // 0x2 bytes padding
    /* 0x008 */ struct _nsv_user_rc_param_work param[120];  // 0x960
};

#endif /* DDR_types__nsv_user_rc_w_H */
