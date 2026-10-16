/* struct _mio_message -- 9 members, size 0x480, layout 4d94f174dcb2.
 *
 * One definition, agreed by the 23 units that declare it: net.c (DIE 0x71A88).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _mio_message *`.
 *
 * declared by: net.c (DIE 0x71A88), net_main.c (DIE 0x7D064), net_type.c (DIE 0x8378C), net_prg.c (DIE 0x89215), net_game_main.c (DIE 0x9F680), net_game_window.c (DIE 0xA9106), net_game_opt.c (DIE 0xB6D87), net_game_match.c (DIE 0xC7B02), net_game_list.c (DIE 0xDA6F2), net_sys_top.c (DIE 0x162A30), net_sys_user.c (DIE 0x16A1AA), net_win_search.c (DIE 0x1A7BCA), net_game_vs.c (DIE 0x1CD133), net_sys_lobby.c (DIE 0x1F35DA), miobase.c (DIE 0x205F42), net_game_prg.c (DIE 0x2ECC91), ddrex2_usa_account.c (DIE 0x38B895), ddrex2_usa_challenge.c (DIE 0x38EF81), ddrex2_usa_connect.c (DIE 0x3917B9), ddrex2_usa_gate.c (DIE 0x394B3D), ddrex2_usa_lobby.c (DIE 0x397C83), ddrex2_usa_util.c (DIE 0x39EB47), net_auth_main.c (DIE 0x3A5F7C)
 */
#ifndef DDR_types__mio_message_H
#define DDR_types__mio_message_H

struct _mio_message {   // size 0x480
    /* 0x000 */ int msgid;                            // 0x4
    /* 0x004 */ int len;                              // 0x4
    /* 0x008 */ unsigned int serial;                  // 0x4
    /* 0x00C */ char head[24];                        // 0x18
    /* 0x024 */ // 0x1C bytes not in DWARF (a member CodeWarrior did not describe)
    /* 0x040 */ char body[1024];                      // 0x400
    /* 0x440 */ char digest[16];                      // 0x10
    /* 0x450 */ int hp;                               // 0x4
    /* 0x454 */ int bp;                               // 0x4
    /* 0x458 */ short stat;                           // 0x2
    /* 0x45A */ // 0x26 bytes not in DWARF (a member CodeWarrior did not describe)
};

#endif /* DDR_types__mio_message_H */
