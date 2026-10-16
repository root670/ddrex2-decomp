/* struct _NetP2PRecvW -- 2 members, size 0x21, layout 03eb2adbaf7c.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x71BDC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetP2PRecvW *`.
 *
 * declared by: net.c (DIE 0x71BDC), net_main.c (DIE 0x7D1B8), net_type.c (DIE 0x838E0), net_prg.c (DIE 0x8A5B2), net_game_main.c (DIE 0x9E3EA), net_game_window.c (DIE 0xAA95E), net_game_opt.c (DIE 0xB8639), net_game_match.c (DIE 0xC4474), net_game_list.c (DIE 0xDBFAE), net_sys_top.c (DIE 0x15E97D), net_sys_user.c (DIE 0x16630D), net_win_search.c (DIE 0x1A7F2D), net_game_vs.c (DIE 0x1C854A), net_sys_lobby.c (DIE 0x1F514A), net_game_prg.c (DIE 0x2EFC3E), ddrex2_usa_util.c (DIE 0x39F465), net_auth_main.c (DIE 0x3AB192)
 */
#ifndef DDR_types__NetP2PRecvW_H
#define DDR_types__NetP2PRecvW_H

struct _NetP2PRecvW {   // size 0x21
    /* 0x000 */ unsigned char buff[32];               // 0x20
    /* 0x020 */ unsigned char get_type;               // 0x1
};

#endif /* DDR_types__NetP2PRecvW_H */
