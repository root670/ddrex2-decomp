/* struct _tag_cRecmData -- 4 members, size 0x18, layout be2c84101c51.
 *
 * One definition, agreed by the 1 unit that declares it: reconi.c (DIE 0x23CA2).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecmData *`.
 *
 * declared by: reconi.c (DIE 0x23CA2)
 */
#ifndef DDR_types__tag_cRecmData_H
#define DDR_types__tag_cRecmData_H

struct _tag_cRecRecord1;

#include "types/_tag_cRecRecord1.h"

struct _tag_cRecmData {   // size 0x18
    /* 0x000 */ struct _tag_cRecRecord1 *data;        // 0x4
    /* 0x004 */ int y[2];                             // 0x8
    /* 0x00C */ int a[2];                             // 0x8
    /* 0x014 */ int bright;                           // 0x4
};

#endif /* DDR_types__tag_cRecmData_H */
