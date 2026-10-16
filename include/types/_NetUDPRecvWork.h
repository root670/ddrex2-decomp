/* struct _NetUDPRecvWork -- 7 members, size 0xAC, layout 51a58f20d553.
 *
 * One definition, agreed by the 17 units that declare it: net.c (DIE 0x70723).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetUDPRecvWork *`.
 *
 * declared by: net.c (DIE 0x70723), net_main.c (DIE 0x7A7B8), net_type.c (DIE 0x8286F), net_prg.c (DIE 0x87767), net_game_main.c (DIE 0x9BA0F), net_game_window.c (DIE 0xA8A50), net_game_opt.c (DIE 0xB6668), net_game_match.c (DIE 0xC2D30), net_game_list.c (DIE 0xD9FAA), net_sys_top.c (DIE 0x163F0E), net_sys_user.c (DIE 0x16B7F5), net_win_search.c (DIE 0x1A663F), net_game_vs.c (DIE 0x1D0952), net_sys_lobby.c (DIE 0x1F3833), net_game_prg.c (DIE 0x2ECE55), ddrex2_usa_util.c (DIE 0x3A15E2), net_auth_main.c (DIE 0x3A8009)
 */
#ifndef DDR_types__NetUDPRecvWork_H
#define DDR_types__NetUDPRecvWork_H

struct _NetRecvPictBufWork;
struct _NetRecvProgBufWork;

#include "types/_NetRecvPictBufWork.h"
#include "types/_NetRecvProgBufWork.h"

struct _NetUDPRecvWork {   // size 0xAC
    /* 0x000 */ float timer;                          // 0x4
    /* 0x004 */ int sec_size_now;                     // 0x4
    /* 0x008 */ int frame_size;                       // 0x4
    /* 0x00C */ unsigned int status;                  // 0x4
    /* 0x010 */ int debug_bps;                        // 0x4
    /* 0x014 */ struct _NetRecvProgBufWork prog[10];  // 0x50
    /* 0x064 */ struct _NetRecvPictBufWork pict[3];   // 0x48
};

#endif /* DDR_types__NetUDPRecvWork_H */
