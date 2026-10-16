/* struct sq_standard -- 3 members, size 0x10, layout 989c970bd565.
 *
 * One definition, agreed by the 7 units that declare it: dmm_init.c (DIE 0x18F5F1).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sq_standard *`.
 *
 * declared by: dmm_init.c (DIE 0x18F5F1), fp_hand.c (DIE 0x1FEB9F), tra_func.c (DIE 0x2D3900), ed_ssq_func.c (DIE 0x305495), infoshow.c (DIE 0x341A0F), kn_lfunc.c (DIE 0x361743), les_play.c (DIE 0x3739F3)
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
