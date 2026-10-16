/* struct _ddrnet_info -- 6 members, size 0x25C, layout 7a591830e8ce.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x70596).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_info *`.
 *
 * declared by: net.c (DIE 0x70596), net_main.c (DIE 0x7A005), net_type.c (DIE 0x82706), net_prg.c (DIE 0x85CAB), net_game_main.c (DIE 0x9C110), net_game_window.c (DIE 0xA63CC), net_game_opt.c (DIE 0xB4008), net_game_match.c (DIE 0xC44E1), net_game_list.c (DIE 0xD7B7B), net_sys_top.c (DIE 0x15F927), net_sys_user.c (DIE 0x1673E7), net_win_search.c (DIE 0x1A648E), net_game_vs.c (DIE 0x1C95E9), net_sys_lobby.c (DIE 0x1F0818), net_game_prg.c (DIE 0x2EB925), ddrex2_usa_account.c (DIE 0x38BD11), ddrex2_usa_connect.c (DIE 0x39317D), ddrex2_usa_gate.c (DIE 0x394D91), ddrex2_usa_util.c (DIE 0x39FF12), net_auth_main.c (DIE 0x3A756A)
 */
#ifndef DDR_types__ddrnet_info_H
#define DDR_types__ddrnet_info_H

struct _ddrnet_info {   // size 0x25C
    /* 0x000 */ unsigned int id;                      // 0x4
    /* 0x004 */ char important;                       // 0x1
    /* 0x005 */ char present;                         // 0x1
    /* 0x006 */ char reldate[20];                     // 0x14
    /* 0x01A */ char title[65];                       // 0x41
    /* 0x05B */ char text[513];                       // 0x201
};

#endif /* DDR_types__ddrnet_info_H */
