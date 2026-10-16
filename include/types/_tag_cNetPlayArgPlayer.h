/* struct _tag_cNetPlayArgPlayer -- 3 members, size 0x14, layout 441ef90a2624.
 *
 * One definition, agreed by the 2 units that declare it: net_play_main.c (DIE 0x1C26C3).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetPlayArgPlayer *`.
 *
 * declared by: net_play_main.c (DIE 0x1C26C3), net_game_vs.c (DIE 0x1CD720)
 */
#ifndef DDR_types__tag_cNetPlayArgPlayer_H
#define DDR_types__tag_cNetPlayArgPlayer_H

struct play_mode;

#include "types/play_mode.h"

struct _tag_cNetPlayArgPlayer {   // size 0x14
    /* 0x000 */ struct play_mode mode;                // 0xC
    /* 0x00C */ int dancer_id;                        // 0x4
    /* 0x010 */ int eyetoy_disp_flag;                 // 0x4
};

#endif /* DDR_types__tag_cNetPlayArgPlayer_H */
