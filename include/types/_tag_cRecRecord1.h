/* struct _tag_cRecRecord1 -- 2 members, size 0x94, layout dac4729b9ce1.
 *
 * One definition, agreed by the 1 unit that declares it: reconi.c (DIE 0x23D9C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecRecord1 *`.
 *
 * declared by: reconi.c (DIE 0x23D9C)
 */
#ifndef DDR_types__tag_cRecRecord1_H
#define DDR_types__tag_cRecRecord1_H

struct _tag_cDDR7Record1;

#include "types/_tag_cDDR7Record1.h"

struct _tag_cRecRecord1 {   // size 0x94
    /* 0x000 */ struct _tag_cDDR7Record1 data;        // 0x90
    /* 0x090 */ struct _tag_cDDR7Record1 *original;   // 0x4
};

#endif /* DDR_types__tag_cRecRecord1_H */
