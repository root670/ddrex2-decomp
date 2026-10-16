/* struct _ddrnet_playerinblock -- 12 members, size 0x50, layout 04c5c4bd3ab5.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x71855).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerinblock *`.
 *
 * declared by: net.c (DIE 0x71855), net_main.c (DIE 0x7CE31), net_type.c (DIE 0x8357D), net_prg.c (DIE 0x88C8C), net_game_main.c (DIE 0x9F1E0), net_game_window.c (DIE 0xA8E87), net_game_opt.c (DIE 0xB6AE2), net_game_match.c (DIE 0xC785F), net_game_list.c (DIE 0xDA44D), net_sys_top.c (DIE 0x162788), net_sys_user.c (DIE 0x169F2B), net_win_search.c (DIE 0x1A7D1E), net_game_vs.c (DIE 0x1CCE43), net_sys_lobby.c (DIE 0x1F335B), net_game_prg.c (DIE 0x2EC897), ddrex2_usa_account.c (DIE 0x38CEF6), ddrex2_usa_connect.c (DIE 0x3914A5), ddrex2_usa_lobby.c (DIE 0x397DD7), ddrex2_usa_util.c (DIE 0x3A10DA), net_auth_main.c (DIE 0x3AA47B)
 */
#ifndef DDR_types__ddrnet_playerinblock_H
#define DDR_types__ddrnet_playerinblock_H

struct _ddrnet_playerdata_h2h;
struct _ddrnet_pldata_match;

#include "types/_ddrnet_playerdata_h2h.h"
#include "types/_ddrnet_pldata_match.h"

struct _ddrnet_playerinblock {   // size 0x50
    /* 0x000 */ signed char dancerid;                 // 0x1
    /* 0x001 */ // 0x1 bytes padding
    /* 0x002 */ unsigned short point_thisweek;        // 0x2
    /* 0x004 */ unsigned int pid;                     // 0x4
    /* 0x008 */ unsigned int roomid;                  // 0x4
    /* 0x00C */ unsigned int disconnect;              // 0x4
    /* 0x010 */ unsigned int rank_total;              // 0x4
    /* 0x014 */ unsigned int point_rank_total;        // 0x4
    /* 0x018 */ unsigned int point_total;             // 0x4
    /* 0x01C */ unsigned int point_rank_thisweek;     // 0x4
    /* 0x020 */ unsigned char pname[17];              // 0x11
    /* 0x031 */ // 0x3 bytes padding
    /* 0x034 */ struct _ddrnet_pldata_match param_total;  // 0x10
    /* 0x044 */ struct _ddrnet_playerdata_h2h param_thisweek;  // 0xC
};

#endif /* DDR_types__ddrnet_playerinblock_H */
