/* struct _tag_cLesSelLevel -- 5 members, size 0xC0, layout 4fc895bf1a1b.
 *
 * One definition, agreed by the 1 unit that declares it: les_sel_lv.c (DIE 0x37D594).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLesSelLevel *`.
 *
 * declared by: les_sel_lv.c (DIE 0x37D594)
 */
#ifndef DDR_types__tag_cLesSelLevel_H
#define DDR_types__tag_cLesSelLevel_H

struct _tag_cLesSelLevelCursor;

#include "types/_tag_cLesSelLevelCursor.h"

struct _tag_cLesSelLevel {   // size 0xC0
    /* 0x000 */ int counter;                          // 0x4
    /* 0x004 */ int disp_level;                       // 0x4
    /* 0x008 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x010 */ struct _tag_cLesSelLevelCursor Cursor;  // 0xA0
    /* 0x0B0 */ int step;                             // 0x4
    /* 0x0B4 */ int timer;                            // 0x4
    /* 0x0B8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

#endif /* DDR_types__tag_cLesSelLevel_H */
