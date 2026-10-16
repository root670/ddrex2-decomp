/* struct _ddrnet_conmgr -- 8 members, size 0x100, layout ae5e4fe9d8b4.
 *
 * One definition, agreed by the 19 units that declare it: net.c (DIE 0x7033F).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_conmgr *`.
 *
 * declared by: net.c (DIE 0x7033F), net_main.c (DIE 0x79C47), net_type.c (DIE 0x824F9), net_prg.c (DIE 0x8D8CA), net_game_main.c (DIE 0x9BCCA), net_game_window.c (DIE 0xA5FD5), net_game_opt.c (DIE 0xB3C11), net_game_match.c (DIE 0xC407D), net_game_list.c (DIE 0xD7784), net_sys_top.c (DIE 0x15F662), net_sys_user.c (DIE 0x166FCA), net_win_search.c (DIE 0x1A6239), net_game_vs.c (DIE 0x1C91F8), net_sys_lobby.c (DIE 0x1F023F), net_game_prg.c (DIE 0x2EB582), ddrex2_usa_account.c (DIE 0x38C031), ddrex2_usa_connect.c (DIE 0x3934C1), ddrex2_usa_util.c (DIE 0x3A0610), net_auth_main.c (DIE 0x3A70B7)
 */
#ifndef DDR_types__ddrnet_conmgr_H
#define DDR_types__ddrnet_conmgr_H

struct _ddrnet_con;
struct _types_fd_set;

#include "types/_ddrnet_con.h"
#include "types/_types_fd_set.h"

struct _ddrnet_conmgr {   // size 0x100
    /* 0x000 */ struct _ddrnet_con con[4];            // 0x80
    /* 0x080 */ struct _types_fd_set fds;             // 0x8
    /* 0x088 */ int maxsd;                            // 0x4
    /* 0x08C */ int heartbeat_timer;                  // 0x4
    /* 0x090 */ int last_recv_time;                   // 0x4
    /* 0x094 */ unsigned char uname[17];              // 0x11
    /* 0x0A5 */ unsigned char passwd[17];             // 0x11
    /* 0x0B6 */ unsigned char ccode[4][17];           // 0x44
    /* 0x0FA */ // 0x6 bytes padding
};

#endif /* DDR_types__ddrnet_conmgr_H */
