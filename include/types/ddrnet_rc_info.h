/* struct ddrnet_rc_info -- 9 members, size 0x8C, layout daf39ca1d634.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x6F952).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct ddrnet_rc_info *`.
 *
 * declared by: net.c (DIE 0x6F952), net_main.c (DIE 0x78AD0), net_type.c (DIE 0x8199F), net_prg.c (DIE 0x8C9E1), net_game_main.c (DIE 0x9A5AB), net_game_window.c (DIE 0xA47DC), net_game_opt.c (DIE 0xB2745), net_game_match.c (DIE 0xC3146), net_game_list.c (DIE 0xD5B44), net_sys_top.c (DIE 0x15E24C), net_sys_user.c (DIE 0x165C28), net_win_search.c (DIE 0x1A4D51), net_game_vs.c (DIE 0x1C7877), net_sys_lobby.c (DIE 0x1EEE47), net_game_prg.c (DIE 0x2EA0E9), ddrex2_usa_account.c (DIE 0x38B6E9), ddrex2_usa_challenge.c (DIE 0x38F0D5), ddrex2_usa_connect.c (DIE 0x392E9D), ddrex2_usa_util.c (DIE 0x39FBD5), net_auth_main.c (DIE 0x3A3746)
 */
#ifndef DDR_types_ddrnet_rc_info_H
#define DDR_types_ddrnet_rc_info_H

struct ddrnet_rc_music;

#include "types/ddrnet_rc_music.h"

struct ddrnet_rc_info {   // size 0x8C
    /* 0x000 */ unsigned char type;                   // 0x1
    /* 0x001 */ // 0x3 bytes padding
    /* 0x004 */ unsigned int eventID;                 // 0x4
    /* 0x008 */ unsigned int typecnt;                 // 0x4
    /* 0x00C */ unsigned char limit;                  // 0x1
    /* 0x00D */ unsigned char gauge;                  // 0x1
    /* 0x00E */ unsigned char trycnt;                 // 0x1
    /* 0x00F */ unsigned char replenish;              // 0x1
    /* 0x010 */ unsigned char rule;                   // 0x1
    /* 0x011 */ // 0x1 bytes padding
    /* 0x012 */ struct ddrnet_rc_music music[10];     // 0x78
    /* 0x08A */ // 0x2 bytes padding
};

#endif /* DDR_types_ddrnet_rc_info_H */
