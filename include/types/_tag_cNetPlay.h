/* struct _tag_cNetPlay -- 8 members, size 0x5C, layout f9a1ff7c76ee.
 *
 * One definition, agreed by the 1 unit that declares it: net_play_main.c (DIE 0x1BEA17).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetPlay *`.
 *
 * declared by: net_play_main.c (DIE 0x1BEA17)
 */
#ifndef DDR_types__tag_cNetPlay_H
#define DDR_types__tag_cNetPlay_H

struct _tag_cNetPlayArg;

#include "types/_tag_cNetPlayArg.h"

struct _tag_cNetPlay {   // size 0x5C
    /* 0x000 */ struct _tag_cNetPlayArg arg;          // 0x40
    /* 0x040 */ int force_exit_flag;                  // 0x4
    /* 0x044 */ int force_clear_flag;                 // 0x4
    /* 0x048 */ int before_sync_flag;                 // 0x4
    /* 0x04C */ int after_sync_flag;                  // 0x4
    /* 0x050 */ int before_sync_state;                // 0x4
    /* 0x054 */ int after_sync_state;                 // 0x4
    /* 0x058 */ int main_step;                        // 0x4
};

#endif /* DDR_types__tag_cNetPlay_H */
