/* struct _ddrnet_infolist -- 2 members, size 0x46CC, layout 159aac02a607.
 *
 * One definition, agreed by the 20 units that declare it: net.c (DIE 0x709BD).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_infolist *`.
 *
 * declared by: net.c (DIE 0x709BD), net_main.c (DIE 0x7AFBD), net_type.c (DIE 0x82B9A), net_prg.c (DIE 0x8634E), net_game_main.c (DIE 0x9C8AA), net_game_window.c (DIE 0xA6DDC), net_game_opt.c (DIE 0xB4A65), net_game_match.c (DIE 0xC5089), net_game_list.c (DIE 0xD858B), net_sys_top.c (DIE 0x16013F), net_sys_user.c (DIE 0x167AE1), net_win_search.c (DIE 0x1A69BC), net_game_vs.c (DIE 0x1CA444), net_sys_lobby.c (DIE 0x1F13DE), net_game_prg.c (DIE 0x2EBBFA), ddrex2_usa_account.c (DIE 0x38BFC2), ddrex2_usa_connect.c (DIE 0x393452), ddrex2_usa_gate.c (DIE 0x394FCC), ddrex2_usa_util.c (DIE 0x3A057B), net_auth_main.c (DIE 0x3A817C)
 */
#ifndef DDR_types__ddrnet_infolist_H
#define DDR_types__ddrnet_infolist_H

struct _ddrnet_info;

#include "types/_ddrnet_info.h"

struct _ddrnet_infolist {   // size 0x46CC
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ struct _ddrnet_info entry[30];        // 0x46C8
};

#endif /* DDR_types__ddrnet_infolist_H */
