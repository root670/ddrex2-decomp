/* struct _ddrnet_playerdata -- 21 members, size 0x90, layout f31bab2bad5d.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x743D4).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_playerdata *`.
 *
 * declared by: net.c (DIE 0x743D4), net_main.c (DIE 0x7FED3), net_type.c (DIE 0x84316), net_prg.c (DIE 0x8B466), net_game_main.c (DIE 0x9E7B3), net_game_window.c (DIE 0xAA2EA), net_game_opt.c (DIE 0xB7FE4), net_game_match.c (DIE 0xC8B3F), net_game_list.c (DIE 0xDB982), net_sys_top.c (DIE 0x1639C4), net_sys_user.c (DIE 0x16B2AB), net_win_search.c (DIE 0x1A900B), net_game_vs.c (DIE 0x1D0182), net_sys_lobby.c (DIE 0x1F485C), net_game_prg.c (DIE 0x2EF3B9), ddrex2_usa_account.c (DIE 0x38D3EC), ddrex2_usa_connect.c (DIE 0x391CC8), ddrex2_usa_lobby.c (DIE 0x397FE6), ddrex2_usa_util.c (DIE 0x3A170B), net_auth_main.c (DIE 0x3AC57D)
 */
#ifndef DDR_types__ddrnet_playerdata_H
#define DDR_types__ddrnet_playerdata_H

struct _ddrnet_pldata_match;

#include "types/_ddrnet_pldata_match.h"

struct _ddrnet_playerdata {   // size 0x90
    /* 0x000 */ unsigned int pid;                     // 0x4
    /* 0x004 */ unsigned char pname[17];              // 0x11
    /* 0x015 */ signed char dancerid;                 // 0x1
    /* 0x016 */ unsigned short disconnect;            // 0x2
    /* 0x018 */ int playtime;                         // 0x4
    /* 0x01C */ int login_count;                      // 0x4
    /* 0x020 */ unsigned int total_rank;              // 0x4
    /* 0x024 */ unsigned int total_rank_last;         // 0x4
    /* 0x028 */ struct _ddrnet_pldata_match match[4];  // 0x40
    /* 0x068 */ unsigned int rank_thisweek;           // 0x4
    /* 0x06C */ unsigned int rank_lastweek;           // 0x4
    /* 0x070 */ unsigned short match_thisweek;        // 0x2
    /* 0x072 */ unsigned short win_thisweek;          // 0x2
    /* 0x074 */ unsigned short draw_thisweek;         // 0x2
    /* 0x076 */ unsigned short lose_thisweek;         // 0x2
    /* 0x078 */ unsigned int total_point_rank;        // 0x4
    /* 0x07C */ unsigned int total_point_rank_last;   // 0x4
    /* 0x080 */ unsigned int point_total;             // 0x4
    /* 0x084 */ unsigned int point_rank_thisweek;     // 0x4
    /* 0x088 */ unsigned int point_rank_lastweek;     // 0x4
    /* 0x08C */ unsigned short point_thisweek;        // 0x2
    /* 0x08E */ // 0x2 bytes padding
};

#endif /* DDR_types__ddrnet_playerdata_H */
