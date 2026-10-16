/* struct _NSV_USER_FILE_WORK -- 11 members, size 0xEE0, layout c5f7aa493ffd.
 *
 * One definition, agreed by the 33 units that declare it: net_main.c (DIE 0x783F7).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NSV_USER_FILE_WORK *`.
 *
 * declared by: net_main.c (DIE 0x783F7), net_prg.c (DIE 0x8A643), net_read_data.c (DIE 0x93DEC), net_game_main.c (DIE 0x9A948), net_game_window.c (DIE 0xA49D2), net_game_opt.c (DIE 0xB2940), net_game_logout.c (DIE 0xBA101), net_game_menu.c (DIE 0xBE18C), net_game_match.c (DIE 0xC336A), net_game_data.c (DIE 0xCB902), net_game_prac.c (DIE 0xD1516), net_game_list.c (DIE 0xD5D16), net_sys_main.c (DIE 0x14C799), net_sys_menu.c (DIE 0x15252A), net_sys_new.c (DIE 0x156EDD), net_sys_top.c (DIE 0x15E4AE), net_sys_user.c (DIE 0x165E8A), net_sys_rule.c (DIE 0x16D8DD), net_sys_connect.c (DIE 0x170F02), net_sys_info.c (DIE 0x174F2A), net_sys_logout.c (DIE 0x19B812), net_win_suser.c (DIE 0x19F5C0), net_win_user.c (DIE 0x1AD076), net_play_main.c (DIE 0x1C21E8), net_game_vs.c (DIE 0x1C7C3A), net_sys_lobby.c (DIE 0x1EF03F), net_game_rc.c (DIE 0x265B8B), net_game_challenge.c (DIE 0x26C266), net_win_peruser.c (DIE 0x2F4E9D), net_auth_main.c (DIE 0x3A321B), net_cnf_main.c (DIE 0x3B78F3), net_dnas_main.c (DIE 0x3BBDF5), net_router_main.c (DIE 0x3C2F3D)
 */
#ifndef DDR_types__NSV_USER_FILE_WORK_H
#define DDR_types__NSV_USER_FILE_WORK_H

struct _nsv_option_work;
struct _nsv_user_htoh_work;
struct _nsv_user_point_work;
struct _nsv_user_rc_w;

#include "types/_nsv_option_work.h"
#include "types/_nsv_user_htoh_work.h"
#include "types/_nsv_user_point_work.h"
#include "types/_nsv_user_rc_w.h"

struct _NSV_USER_FILE_WORK {   // size 0xEE0
    /* 0x000 */ unsigned int pid;                     // 0x4
    /* 0x004 */ unsigned char name[20];               // 0x14
    /* 0x018 */ short dancer_number;                  // 0x2
    /* 0x01A */ // 0x2 bytes padding
    /* 0x01C */ int last_login_time;                  // 0x4
    /* 0x020 */ int play_time;                        // 0x4
    /* 0x024 */ int login_count;                      // 0x4
    /* 0x028 */ struct _nsv_user_htoh_work htoh;      // 0x330
    /* 0x358 */ struct _nsv_user_point_work points;   // 0x1FC
    /* 0x554 */ struct _nsv_user_rc_w rc;             // 0x968
    /* 0xEBC */ char status;                          // 0x1
    /* 0xEBD */ // 0x3 bytes padding
    /* 0xEC0 */ struct _nsv_option_work option;       // 0x20
};

#endif /* DDR_types__NSV_USER_FILE_WORK_H */
