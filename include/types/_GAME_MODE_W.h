/* struct _GAME_MODE_W -- 2 members, size 0x800C, layout 932ddc9339b0.
 *
 * One definition, agreed by the 6 units that declare it: eds_select.c (DIE 0x403BF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _GAME_MODE_W *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: eds_select.c (DIE 0x403BF), eds_main.c (DIE 0x43B33), eds_win.c (DIE 0x4E28D), eds_aid.c (DIE 0x5221E), eds_break.c (DIE 0x59697), eds_record.c (DIE 0x5CCF7)
 */
#ifndef DDR_types__GAME_MODE_W_H
#define DDR_types__GAME_MODE_W_H

struct demo_loop_w;
struct play_loop_w;

#include "types/demo_loop_w.h"
#include "types/play_loop_w.h"

struct _GAME_MODE_W {   // size 0x800C
    /* 0x000 */ int game_mode_step;                   // 0x4
    /* 0x004 */ union {   // size 0x8008
        /* 0x000 */ struct demo_loop_w demo_loop_w;       // 0x8008
        /* 0x000 */ struct play_loop_w play_loop_w;       // 0x8008
    } u;
};

#endif /* DDR_types__GAME_MODE_W_H */
