/* struct _tag_cRecOniRecord1 -- 3 members, size 0x40, layout 1b111b4809ed.
 *
 * One definition, agreed by the 1 unit that declares it: reconi.c (DIE 0x22363).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecOniRecord1 *`.
 *
 * declared by: reconi.c (DIE 0x22363)
 */
#ifndef DDR_types__tag_cRecOniRecord1_H
#define DDR_types__tag_cRecOniRecord1_H

struct _tag_cDDR7OniRecord1;

#include "types/_tag_cDDR7OniRecord1.h"

struct _tag_cRecOniRecord1 {   // size 0x40
    /* 0x000 */ struct _tag_cDDR7OniRecord1 data;     // 0x38
    /* 0x038 */ struct _tag_cDDR7OniRecord1 *original;  // 0x4
    /* 0x03C */ int course;                           // 0x4
};

#endif /* DDR_types__tag_cRecOniRecord1_H */
