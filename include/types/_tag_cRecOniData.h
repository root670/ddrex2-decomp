/* struct _tag_cRecOniData -- 4 members, size 0x18, layout 7e2880a030d4.
 *
 * One definition, agreed by the 1 unit that declares it: reconi.c (DIE 0x22423).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecOniData *`.
 *
 * declared by: reconi.c (DIE 0x22423)
 */
#ifndef DDR_types__tag_cRecOniData_H
#define DDR_types__tag_cRecOniData_H

struct _tag_cRecOniRecord1;

#include "types/_tag_cRecOniRecord1.h"

struct _tag_cRecOniData {   // size 0x18
    /* 0x000 */ struct _tag_cRecOniRecord1 *data;     // 0x4
    /* 0x004 */ int y[2];                             // 0x8
    /* 0x00C */ int a[2];                             // 0x8
    /* 0x014 */ int bright;                           // 0x4
};

#endif /* DDR_types__tag_cRecOniData_H */
