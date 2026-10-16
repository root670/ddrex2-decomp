/* struct _NetSendPictBufWork -- 6 members, size 0x18, layout b826f9717e0e.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x7202B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetSendPictBufWork *`.
 *
 * declared by: net.c (DIE 0x7202B), net_main.c (DIE 0x7F376), net_type.c (DIE 0x83AF5), net_prg.c (DIE 0x8BA1D), net_game_main.c (DIE 0x9F506), net_game_window.c (DIE 0xAADB6), net_game_opt.c (DIE 0xB8959), net_game_match.c (DIE 0xC4F81), net_game_list.c (DIE 0xDC2A5), net_sys_top.c (DIE 0x15F3EC), net_sys_user.c (DIE 0x166D54), net_win_search.c (DIE 0x1A83F3), net_game_vs.c (DIE 0x1C93B9), net_sys_lobby.c (DIE 0x1EEBEC), net_game_prg.c (DIE 0x2E9EEC), ddrex2_usa_util.c (DIE 0x39FACD), net_auth_main.c (DIE 0x3ABC9D)
 */
#ifndef DDR_types__NetSendPictBufWork_H
#define DDR_types__NetSendPictBufWork_H

struct _NetSendPictBufWork {   // size 0x18
    /* 0x000 */ unsigned int id;                      // 0x4
    /* 0x004 */ int split_num;                        // 0x4
    /* 0x008 */ unsigned int total_size;              // 0x4
    /* 0x00C */ unsigned int send_size;               // 0x4
    /* 0x010 */ unsigned int status;                  // 0x4
    /* 0x014 */ void *eye_buf;                        // 0x4
};

#endif /* DDR_types__NetSendPictBufWork_H */
