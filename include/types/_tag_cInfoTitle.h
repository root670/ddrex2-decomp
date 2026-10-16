/* struct _tag_cInfoTitle -- 7 members, size 0x1C, layout a3aff0287372.
 *
 * One definition, agreed by the 3 units that declare it: infosel.c (DIE 0x32E796).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cInfoTitle *`.
 *
 * declared by: infosel.c (DIE 0x32E796), info.c (DIE 0x3350D7), infoshow.c (DIE 0x3417FD)
 */
#ifndef DDR_types__tag_cInfoTitle_H
#define DDR_types__tag_cInfoTitle_H

struct _tag_cInfoText;

#include "types/_tag_cInfoText.h"

struct _tag_cInfoTitle {   // size 0x1C
    /* 0x000 */ struct _tag_cInfoText *info_text;     // 0x4
    /* 0x004 */ float x;                              // 0x4
    /* 0x008 */ float y;                              // 0x4
    /* 0x00C */ float sx;                             // 0x4
    /* 0x010 */ float sy;                             // 0x4
    /* 0x014 */ int t;                                // 0x4
    /* 0x018 */ int t_max;                            // 0x4
};

#endif /* DDR_types__tag_cInfoTitle_H */
