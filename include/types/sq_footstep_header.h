/* struct sq_footstep_header -- 3 members, size 0x4, layout 5771899c32e9.
 *
 * One definition, agreed by the 1 unit that declares it: fp_hand.c (DIE 0x1FEAD2).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sq_footstep_header *`.
 *
 * declared by: fp_hand.c (DIE 0x1FEAD2)
 */
#ifndef DDR_types_sq_footstep_header_H
#define DDR_types_sq_footstep_header_H

struct sq_footstep_header {   // size 0x4
    /* 0x000 */ unsigned int panel : 4;               // bits 0..3
    /* 0x000 */ unsigned int player : 4;              // bits 4..7
    /* 0x001 */ unsigned char seq_kind;               // 0x1
};

#endif /* DDR_types_sq_footstep_header_H */
