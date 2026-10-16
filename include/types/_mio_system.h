/* struct _mio_system -- 2 members, size 0x1050, layout 0223194d05e7.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x74175).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _mio_system *`.
 *
 * declared by: net.c (DIE 0x74175), net_main.c (DIE 0x7FB6E), net_type.c (DIE 0x84171), net_prg.c (DIE 0x8B38A), net_game_main.c (DIE 0xA284B), net_game_window.c (DIE 0xAA0D6), net_game_opt.c (DIE 0xB7E3C), net_game_match.c (DIE 0xC89BB), net_game_list.c (DIE 0xDB7B1), net_sys_top.c (DIE 0x16392E), net_sys_user.c (DIE 0x16B0FE), net_win_search.c (DIE 0x1A8C1A), net_game_vs.c (DIE 0x1D0054), net_sys_lobby.c (DIE 0x1F46D8), miobase.c (DIE 0x206096), net_game_prg.c (DIE 0x2EF325), ddrex2_usa_account.c (DIE 0x38BA7D), ddrex2_usa_connect.c (DIE 0x391749), ddrex2_usa_util.c (DIE 0x39F4F6), net_auth_main.c (DIE 0x3A7BDC)
 */
#ifndef DDR_types__mio_system_H
#define DDR_types__mio_system_H

struct _mio_message;
struct _mio_security;

#include "types/_mio_message.h"
#include "types/_mio_security.h"

struct _mio_system {   // size 0x1050
    /* 0x000 */ struct _mio_message *msg;             // 0x4
    /* 0x004 */ struct _mio_security security;        // 0x104C
};

#endif /* DDR_types__mio_system_H */
