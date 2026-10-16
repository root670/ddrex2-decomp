/* struct _NS_NET_SOCK_W -- 6 members, size 0x28, layout 103e1ca7de3f.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x71190).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NS_NET_SOCK_W *`.
 *
 * declared by: net.c (DIE 0x71190), net_main.c (DIE 0x7BC6C), net_type.c (DIE 0x82F54), net_prg.c (DIE 0x88B6F), net_game_main.c (DIE 0x9C331), net_game_window.c (DIE 0xA95BC), net_game_opt.c (DIE 0xB71F8), net_game_match.c (DIE 0xC352E), net_game_list.c (DIE 0xDAB8C), net_sys_top.c (DIE 0x164492), net_sys_user.c (DIE 0x16BCE0), net_win_search.c (DIE 0x1A6F60), net_game_vs.c (DIE 0x1D1296), net_sys_lobby.c (DIE 0x1F42E7), net_game_prg.c (DIE 0x2EEFA1), ddrex2_usa_util.c (DIE 0x39EA2A), net_auth_main.c (DIE 0x3A9862)
 */
#ifndef DDR_types__NS_NET_SOCK_W_H
#define DDR_types__NS_NET_SOCK_W_H

struct sockaddr_in;

#include "types/sockaddr_in.h"

struct _NS_NET_SOCK_W {   // size 0x28
    /* 0x000 */ struct sockaddr_in my_addr;           // 0x10
    /* 0x010 */ struct sockaddr_in peer_addr;         // 0x10
    /* 0x020 */ int DC;                               // 0x4
    /* 0x024 */ short step;                           // 0x2
    /* 0x026 */ char status;                          // 0x1
    /* 0x027 */ char padn;                            // 0x1
};

#endif /* DDR_types__NS_NET_SOCK_W_H */
