/* struct in_addr -- 1 members, size 0x4, layout 8f523eff6efd.
 *
 * One definition, agreed by the 23 units that declare it: net.c (DIE 0x71651).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct in_addr *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: net.c (DIE 0x71651), net_main.c (DIE 0x7C9F8), net_type.c (DIE 0x833E7), net_prg.c (DIE 0x888C0), net_game_main.c (DIE 0x9EDBD), net_game_window.c (DIE 0xA8A0D), net_game_opt.c (DIE 0xB6791), net_game_match.c (DIE 0xC732C), net_game_list.c (DIE 0xDA0D3), net_sys_top.c (DIE 0x162277), net_sys_user.c (DIE 0x169BDA), net_win_search.c (DIE 0x1A76FA), net_game_vs.c (DIE 0x1CC90E), net_sys_lobby.c (DIE 0x1F2F98), net_game_prg.c (DIE 0x2EC6B3), bsdsock.c (DIE 0x38798E), ddrex2_usa_account.c (DIE 0x38C2BF), ddrex2_usa_challenge.c (DIE 0x38F25D), ddrex2_usa_connect.c (DIE 0x3937E2), ddrex2_usa_gate.c (DIE 0x395061), ddrex2_usa_lobby.c (DIE 0x3986E2), ddrex2_usa_util.c (DIE 0x39ED78), net_auth_main.c (DIE 0x3A46E0)
 */
#ifndef DDR_types_in_addr_H
#define DDR_types_in_addr_H

#include "types/anon_7e56caf1fdae.h"

struct in_addr {   // size 0x4
    /* 0x000 */ anon_7e56caf1fdae S_un;               // 0x4
};

#endif /* DDR_types_in_addr_H */
