/* struct _NetP2PSendW -- 2 members, size 0x24, layout 39a45941a533.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x715E5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetP2PSendW *`.
 *
 * declared by: net.c (DIE 0x715E5), net_main.c (DIE 0x7C98C), net_type.c (DIE 0x8337B), net_prg.c (DIE 0x8A188), net_game_main.c (DIE 0x9D964), net_game_window.c (DIE 0xAA146), net_game_opt.c (DIE 0xB7DD0), net_game_match.c (DIE 0xC3E7F), net_game_list.c (DIE 0xDB745), net_sys_top.c (DIE 0x15E3F8), net_sys_user.c (DIE 0x165DD4), net_win_search.c (DIE 0x1A7B3A), net_game_vs.c (DIE 0x1C7F19), net_sys_lobby.c (DIE 0x1F4EF9), net_game_prg.c (DIE 0x2EF8B8), ddrex2_usa_util.c (DIE 0x39F200), net_auth_main.c (DIE 0x3AA79F)
 */
#ifndef DDR_types__NetP2PSendW_H
#define DDR_types__NetP2PSendW_H

struct _NetP2PSendW {   // size 0x24
    /* 0x000 */ unsigned char buff[32];               // 0x20
    /* 0x020 */ int counter;                          // 0x4
};

#endif /* DDR_types__NetP2PSendW_H */
