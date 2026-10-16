/* struct _NetRecvPictBufWork -- 7 members, size 0x18, layout 5731c328a66e.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x74252).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetRecvPictBufWork *`.
 *
 * declared by: net.c (DIE 0x74252), net_main.c (DIE 0x7FD7E), net_type.c (DIE 0x841E1), net_prg.c (DIE 0x8C210), net_game_main.c (DIE 0xA189D), net_game_window.c (DIE 0xA4681), net_game_opt.c (DIE 0xB24BD), net_game_match.c (DIE 0xC5D96), net_game_list.c (DIE 0xD58BC), net_sys_top.c (DIE 0x15FBE8), net_sys_user.c (DIE 0x167550), net_win_search.c (DIE 0x1A8DF4), net_game_vs.c (DIE 0x1CA087), net_sys_lobby.c (DIE 0x1EF4C2), net_game_prg.c (DIE 0x2EA8F6), ddrex2_usa_util.c (DIE 0x3A0217), net_auth_main.c (DIE 0x3AC930)
 */
#ifndef DDR_types__NetRecvPictBufWork_H
#define DDR_types__NetRecvPictBufWork_H

struct _NetRecvPictBufWork {   // size 0x18
    /* 0x000 */ unsigned int id;                      // 0x4
    /* 0x004 */ unsigned int recv_size;               // 0x4
    /* 0x008 */ unsigned int total_size;              // 0x4
    /* 0x00C */ unsigned int status;                  // 0x4
    /* 0x010 */ short split_total;                    // 0x2
    /* 0x012 */ short split_recv_num;                 // 0x2
    /* 0x014 */ void *eye_buf;                        // 0x4
};

#endif /* DDR_types__NetRecvPictBufWork_H */
