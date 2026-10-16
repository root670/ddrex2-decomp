/* struct _ddrnet_svr -- 7 members, size 0x30, layout a426ca5710c9.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x6FB5A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_svr *`.
 *
 * declared by: net.c (DIE 0x6FB5A), net_main.c (DIE 0x792CE), net_type.c (DIE 0x81F98), net_prg.c (DIE 0x8CEDE), net_game_main.c (DIE 0x9AB0C), net_game_window.c (DIE 0xA4B96), net_game_opt.c (DIE 0xB2B04), net_game_match.c (DIE 0xC3627), net_game_list.c (DIE 0xD5EDA), net_sys_top.c (DIE 0x15E672), net_sys_user.c (DIE 0x16604E), net_win_search.c (DIE 0x1A50E8), net_game_vs.c (DIE 0x1C7DFE), net_sys_lobby.c (DIE 0x1EF203), net_game_prg.c (DIE 0x2EA607), ddrex2_usa_account.c (DIE 0x38B34A), ddrex2_usa_connect.c (DIE 0x392C66), ddrex2_usa_gate.c (DIE 0x394A22), ddrex2_usa_util.c (DIE 0x39F2B6), net_auth_main.c (DIE 0x3A4799)
 */
#ifndef DDR_types__ddrnet_svr_H
#define DDR_types__ddrnet_svr_H

struct _ddrnet_svr {   // size 0x30
    /* 0x000 */ int svid;                             // 0x4
    /* 0x004 */ int svtype;                           // 0x4
    /* 0x008 */ short ucount;                         // 0x2
    /* 0x00A */ unsigned short svport;                // 0x2
    /* 0x00C */ unsigned short svrgid;                // 0x2
    /* 0x00E */ char svname[17];                      // 0x11
    /* 0x01F */ char svaddr[16];                      // 0x10
    /* 0x02F */ // 0x1 bytes padding
};

#endif /* DDR_types__ddrnet_svr_H */
