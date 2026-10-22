/* struct _mio_security -- 2 members, size 0x104C, layout f83edc6c8e47.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x73B68).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _mio_security *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: net.c (DIE 0x73B68), net_main.c (DIE 0x7F642), net_type.c (DIE 0x83C45), net_prg.c (DIE 0x8A542), net_game_main.c (DIE 0xA1DE1), net_game_window.c (DIE 0xA9D6E), net_game_opt.c (DIE 0xB7A1B), net_game_match.c (DIE 0xC8653), net_game_list.c (DIE 0xDB3B4), net_sys_top.c (DIE 0x16350E), net_sys_user.c (DIE 0x16ACD2), net_win_search.c (DIE 0x1A851F), net_game_vs.c (DIE 0x1CFB3C), net_sys_lobby.c (DIE 0x1F4277), miobase.c (DIE 0x2062B2), net_game_prg.c (DIE 0x2EEE35), ddrex2_usa_account.c (DIE 0x38B655), ddrex2_usa_connect.c (DIE 0x391435), ddrex2_usa_util.c (DIE 0x39F3D1), net_auth_main.c (DIE 0x3A76D1)
 */
#ifndef DDR_types__mio_security_H
#define DDR_types__mio_security_H

#include "types/anon_5914497fe2d8.h"

struct _mio_security {   // size 0x104C
    /* 0x000 */ anon_5914497fe2d8 ctx;                // 0x1048
    /* 0x1048 */ char scrambler[4];                   // 0x4
};

#endif /* DDR_types__mio_security_H */
