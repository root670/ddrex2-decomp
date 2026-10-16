/* struct _ddrnet_svrlist -- 2 members, size 0x2584, layout fa8148e96c76.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x70187).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_svrlist *`.
 *
 * declared by: net.c (DIE 0x70187), net_main.c (DIE 0x79A8F), net_type.c (DIE 0x82365), net_prg.c (DIE 0x8D630), net_game_main.c (DIE 0x9BB5C), net_game_window.c (DIE 0xA5E67), net_game_opt.c (DIE 0xB3AA3), net_game_match.c (DIE 0xC3EEB), net_game_list.c (DIE 0xD7616), net_sys_top.c (DIE 0x15F4F4), net_sys_user.c (DIE 0x166E5C), net_win_search.c (DIE 0x1A5F76), net_game_vs.c (DIE 0x1C9042), net_sys_lobby.c (DIE 0x1F00D1), net_game_prg.c (DIE 0x2EB3F0), ddrex2_usa_account.c (DIE 0x38B9E9), ddrex2_usa_connect.c (DIE 0x393025), ddrex2_usa_gate.c (DIE 0x394CFD), ddrex2_usa_util.c (DIE 0x39FD81), net_auth_main.c (DIE 0x3A6CD9)
 */
#ifndef DDR_types__ddrnet_svrlist_H
#define DDR_types__ddrnet_svrlist_H

struct _ddrnet_svr;

#include "types/_ddrnet_svr.h"

struct _ddrnet_svrlist {   // size 0x2584
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ struct _ddrnet_svr entry[200];        // 0x2580
};

#endif /* DDR_types__ddrnet_svrlist_H */
