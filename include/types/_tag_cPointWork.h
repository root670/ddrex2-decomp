/* struct _tag_cPointWork -- 3 members, size 0xA0, layout dfcef445fcfa.
 *
 * One definition, agreed by the 1 unit that declares it: point.c (DIE 0x1E6E61).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cPointWork *`.
 *
 * declared by: point.c (DIE 0x1E6E61)
 */
#ifndef DDR_types__tag_cPointWork_H
#define DDR_types__tag_cPointWork_H

struct _tag_cPointWorkPlayer;

#include "types/_tag_cPointWorkPlayer.h"

struct _tag_cPointWork {   // size 0xA0
    /* 0x000 */ int mode;                             // 0x4
    /* 0x004 */ int hist_point;                       // 0x4
    /* 0x008 */ struct _tag_cPointWorkPlayer player[2];  // 0x98
};

#endif /* DDR_types__tag_cPointWork_H */
