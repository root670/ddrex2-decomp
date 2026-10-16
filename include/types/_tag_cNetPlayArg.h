/* struct _tag_cNetPlayArg -- 7 members, size 0x40, layout ab4bf0a7251c.
 *
 * One definition, agreed by the 2 units that declare it: net_play_main.c (DIE 0x1C2C9A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetPlayArg *`.
 *
 * declared by: net_play_main.c (DIE 0x1C2C9A), net_game_vs.c (DIE 0x1CF6E4)
 */
#ifndef DDR_types__tag_cNetPlayArg_H
#define DDR_types__tag_cNetPlayArg_H

struct _tag_cNetPlayArgPlayer;
struct play_loop_w;

#include "types/_tag_cNetPlayArgPlayer.h"
#include "types/play_loop_w.h"

struct _tag_cNetPlayArg {   // size 0x40
    /* 0x000 */ struct play_loop_w *play_loop_w;      // 0x4
    /* 0x004 */ unsigned int addr_play_data;          // 0x4
    /* 0x008 */ unsigned int addr_result_data;        // 0x4
    /* 0x00C */ int game_rule;                        // 0x4
    /* 0x010 */ int dance_num;                        // 0x4
    /* 0x014 */ int play_style;                       // 0x4
    /* 0x018 */ struct _tag_cNetPlayArgPlayer player[2];  // 0x28
};

#endif /* DDR_types__tag_cNetPlayArg_H */
