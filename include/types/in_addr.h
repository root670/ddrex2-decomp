/* struct in_addr -- 1 members, size 0x4, layout 8f523eff6efd.
 *
 * One definition, agreed by the 23 units that declare it: net.c (DIE 0x71651).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct in_addr *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: net.c (DIE 0x71651), net_main.c (DIE 0x7C9F8), net_type.c (DIE 0x833E7), net_prg.c (DIE 0x888C0), net_game_main.c (DIE 0x9EDBD), net_game_window.c (DIE 0xA8A0D), net_game_opt.c (DIE 0xB6791), net_game_match.c (DIE 0xC732C), net_game_list.c (DIE 0xDA0D3), net_sys_top.c (DIE 0x162277), net_sys_user.c (DIE 0x169BDA), net_win_search.c (DIE 0x1A76FA), net_game_vs.c (DIE 0x1CC90E), net_sys_lobby.c (DIE 0x1F2F98), net_game_prg.c (DIE 0x2EC6B3), bsdsock.c (DIE 0x38798E), ddrex2_usa_account.c (DIE 0x38C2BF), ddrex2_usa_challenge.c (DIE 0x38F25D), ddrex2_usa_connect.c (DIE 0x3937E2), ddrex2_usa_gate.c (DIE 0x395061), ddrex2_usa_lobby.c (DIE 0x3986E2), ddrex2_usa_util.c (DIE 0x39ED78), net_auth_main.c (DIE 0x3A46E0)
 */
#ifndef DDR_types_in_addr_H
#define DDR_types_in_addr_H

struct in_addr {   // size 0x4
    /* 0x000 */ union {   // size 0x4
        /* 0x000 */ struct {   // size 0x4
            /* 0x000 */ unsigned char s_b1;                   // 0x1
            /* 0x001 */ unsigned char s_b2;                   // 0x1
            /* 0x002 */ unsigned char s_b3;                   // 0x1
            /* 0x003 */ unsigned char s_b4;                   // 0x1
        } S_un_b;
        /* 0x000 */ struct {   // size 0x4
            /* 0x000 */ unsigned short s_w1;                  // 0x2
            /* 0x002 */ unsigned short s_w2;                  // 0x2
        } S_un_w;
        /* 0x000 */ unsigned int S_addr;                  // 0x4
    } S_un;
};

#endif /* DDR_types_in_addr_H */
