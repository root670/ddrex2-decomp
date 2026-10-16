/* struct _NetUDPSendWork -- 11 members, size 0x40, layout c7502c3e1b6a.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x6E5BC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetUDPSendWork *`.
 *
 * declared by: net.c (DIE 0x6E5BC), net_main.c (DIE 0x76BDF), net_type.c (DIE 0x8146B), net_prg.c (DIE 0x8CBEA), net_game_main.c (DIE 0xA28BB), net_game_window.c (DIE 0xA5976), net_game_opt.c (DIE 0xB33EE), net_game_match.c (DIE 0xC7448), net_game_list.c (DIE 0xD6F5C), net_sys_top.c (DIE 0x160CE5), net_sys_user.c (DIE 0x168CA4), net_win_search.c (DIE 0x1A9DD2), net_game_vs.c (DIE 0x1CB8D9), net_sys_lobby.c (DIE 0x1F03B6), net_game_prg.c (DIE 0x2EB6F9), ddrex2_usa_util.c (DIE 0x3A07AD), net_auth_main.c (DIE 0x3AD9BF)
 */
#ifndef DDR_types__NetUDPSendWork_H
#define DDR_types__NetUDPSendWork_H

struct _NetSendPictBufWork;

#include "types/_NetSendPictBufWork.h"

struct _NetUDPSendWork {   // size 0x40
    /* 0x000 */ float timer;                          // 0x4
    /* 0x004 */ int counter;                          // 0x4
    /* 0x008 */ int type;                             // 0x4
    /* 0x00C */ int sec_size_max;                     // 0x4
    /* 0x010 */ int sec_size_now;                     // 0x4
    /* 0x014 */ int frame_size;                       // 0x4
    /* 0x018 */ int interval;                         // 0x4
    /* 0x01C */ unsigned int status;                  // 0x4
    /* 0x020 */ int err_flag;                         // 0x4
    /* 0x024 */ int debug_bps;                        // 0x4
    /* 0x028 */ struct _NetSendPictBufWork pict;      // 0x18
};

#endif /* DDR_types__NetUDPSendWork_H */
