/* struct sq_standard -- 3 members, size 0x10, layout 989c970bd565.
 *
 * One definition, agreed by the 2 units that declare it: les_play.c (DIE 0xDD2B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sq_standard *`.
 *
 * declared by: les_play.c (DIE 0xDD2B), kn_lfunc.c (DIE 0x188FE)
 */
#ifndef DDR_types_sq_standard_H
#define DDR_types_sq_standard_H

struct sq_header;

#include "types/sq_header.h"

struct sq_standard {   // size 0x10
    /* 0x000 */ struct sq_header header;              // 0x8
    /* 0x008 */ unsigned int num;                     // 0x4
    /* 0x00C */ int body[1];                          // 0x4
};

#endif /* DDR_types_sq_standard_H */
