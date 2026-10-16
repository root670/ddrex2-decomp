/* struct _NetRecvProgBufWork -- 2 members, size 0x8, layout 6bdbacb63433.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x704DA).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetRecvProgBufWork *`.
 *
 * declared by: net.c (DIE 0x704DA), net_main.c (DIE 0x79DBC), net_type.c (DIE 0x8264A), net_prg.c (DIE 0x86A8C), net_game_main.c (DIE 0x9AE63), net_game_window.c (DIE 0xA84C0), net_game_opt.c (DIE 0xB5D59), net_game_match.c (DIE 0xC92D7), net_game_list.c (DIE 0xD985B), net_sys_top.c (DIE 0x163709), net_sys_user.c (DIE 0x16AE85), net_win_search.c (DIE 0x1A63D4), net_game_vs.c (DIE 0x1D00C4), net_sys_lobby.c (DIE 0x1F2FFF), net_game_prg.c (DIE 0x2EC6F6), ddrex2_usa_util.c (DIE 0x3A138F), net_auth_main.c (DIE 0x3A7741)
 */
#ifndef DDR_types__NetRecvProgBufWork_H
#define DDR_types__NetRecvProgBufWork_H

struct _NetRecvProgBufWork {   // size 0x8
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int del_time;                         // 0x4
};

#endif /* DDR_types__NetRecvProgBufWork_H */
