/* struct _tag_cLesSelLevelCursor -- 17 members, size 0xA0, layout dfb9bf6f6651.
 *
 * One definition, agreed by the 1 unit that declares it: les_sel_lv.c (DIE 0x37CC41).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLesSelLevelCursor *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: les_sel_lv.c (DIE 0x37CC41)
 */
#ifndef DDR_types__tag_cLesSelLevelCursor_H
#define DDR_types__tag_cLesSelLevelCursor_H

#include "types/anon_fa86f3882d77.h"

struct _tag_cLesSelLevelCursor {   // size 0xA0
    /* 0x000 */ int pmode;                            // 0x4
    /* 0x004 */ int pcount;                           // 0x4
    /* 0x008 */ int pcounter;                         // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ anon_fa86f3882d77 pos __attribute__((aligned(16)));  // 0x10
    /* 0x020 */ anon_fa86f3882d77 npos;               // 0x10
    /* 0x030 */ anon_fa86f3882d77 ipos;               // 0x10
    /* 0x040 */ int amode;                            // 0x4
    /* 0x044 */ int acount;                           // 0x4
    /* 0x048 */ int acounter;                         // 0x4
    /* 0x04C */ // 0x4 bytes padding
    /* 0x050 */ anon_fa86f3882d77 angle __attribute__((aligned(16)));  // 0x10
    /* 0x060 */ anon_fa86f3882d77 nangle;             // 0x10
    /* 0x070 */ anon_fa86f3882d77 iangle;             // 0x10
    /* 0x080 */ int step;                             // 0x4
    /* 0x084 */ int can_select;                       // 0x4
    /* 0x088 */ int bright;                           // 0x4
    /* 0x08C */ int alpha;                            // 0x4
    /* 0x090 */ int pri;                              // 0x4
    /* 0x094 */ // 0xC bytes padding
};

#endif /* DDR_types__tag_cLesSelLevelCursor_H */
