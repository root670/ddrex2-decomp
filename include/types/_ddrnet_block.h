/* struct _ddrnet_block -- 3 members, size 0x16, layout a14a95e36163.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x71319).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_block *`.
 *
 * declared by: net.c (DIE 0x71319), net_main.c (DIE 0x7BF42), net_type.c (DIE 0x83191), net_prg.c (DIE 0x86E5A), net_game_main.c (DIE 0x9DBDB), net_game_window.c (DIE 0xA7C8D), net_game_opt.c (DIE 0xB58E8), net_game_match.c (DIE 0xC6067), net_game_list.c (DIE 0xD93EA), net_sys_top.c (DIE 0x16170A), net_sys_user.c (DIE 0x1690B5), net_win_search.c (DIE 0x1A715E), net_game_vs.c (DIE 0x1CBBEB), net_sys_lobby.c (DIE 0x1F228A), net_game_prg.c (DIE 0x2EC413), ddrex2_usa_account.c (DIE 0x38C731), ddrex2_usa_connect.c (DIE 0x393C54), ddrex2_usa_lobby.c (DIE 0x398531), ddrex2_usa_util.c (DIE 0x3A0EA8), net_auth_main.c (DIE 0x3A997F)
 */
#ifndef DDR_types__ddrnet_block_H
#define DDR_types__ddrnet_block_H

struct _ddrnet_block {   // size 0x16
    /* 0x000 */ signed char type;                     // 0x1
    /* 0x001 */ // 0x1 bytes padding
    /* 0x002 */ unsigned short ucount;                // 0x2
    /* 0x004 */ unsigned char name[17];               // 0x11
    /* 0x015 */ // 0x1 bytes padding
};

#endif /* DDR_types__ddrnet_block_H */
