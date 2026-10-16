/* struct _ddrnet_room -- 7 members, size 0x34, layout 67742a42d13f.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x74053).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_room *`.
 *
 * declared by: net.c (DIE 0x74053), net_main.c (DIE 0x7FBDE), net_type.c (DIE 0x8404F), net_prg.c (DIE 0x8AFB9), net_game_main.c (DIE 0xA2729), net_game_window.c (DIE 0xA9FB4), net_game_opt.c (DIE 0xB7CAE), net_game_match.c (DIE 0xC8899), net_game_list.c (DIE 0xDB623), net_sys_top.c (DIE 0x16380C), net_sys_user.c (DIE 0x16AFDC), net_win_search.c (DIE 0x1A8CD2), net_game_vs.c (DIE 0x1CFF0C), net_sys_lobby.c (DIE 0x1F45B6), net_game_prg.c (DIE 0x2EF203), ddrex2_usa_account.c (DIE 0x38D779), ddrex2_usa_connect.c (DIE 0x392055), ddrex2_usa_lobby.c (DIE 0x398397), ddrex2_usa_util.c (DIE 0x3A1A98), net_auth_main.c (DIE 0x3AC3EB)
 */
#ifndef DDR_types__ddrnet_room_H
#define DDR_types__ddrnet_room_H

struct _ddrnet_room {   // size 0x34
    /* 0x000 */ signed char status;                   // 0x1
    /* 0x001 */ signed char endflag;                  // 0x1
    /* 0x002 */ unsigned char rule;                   // 0x1
    /* 0x003 */ unsigned char difficulty;             // 0x1
    /* 0x004 */ unsigned int room_id;                 // 0x4
    /* 0x008 */ unsigned int pid[2];                  // 0x8
    /* 0x010 */ unsigned char room_name[33];          // 0x21
    /* 0x031 */ // 0x3 bytes padding
};

#endif /* DDR_types__ddrnet_room_H */
