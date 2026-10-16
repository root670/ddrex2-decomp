/* struct sq_indicator -- 2 members, size 0x2, layout 80ca135fd872.
 *
 * One definition, agreed by the 3 units that declare it: dmm_init.c (DIE 0x18F796).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sq_indicator *`.
 *
 * declared by: dmm_init.c (DIE 0x18F796), fp_hand.c (DIE 0x1FEA45), ed_ssq_func.c (DIE 0x30522F)
 */
#ifndef DDR_types_sq_indicator_H
#define DDR_types_sq_indicator_H

struct sq_indicator {   // size 0x2
    /* 0x000 */ unsigned char class;                  // 0x1
    /* 0x001 */ unsigned char icode;                  // 0x1
};

#endif /* DDR_types_sq_indicator_H */
