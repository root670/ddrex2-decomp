/* struct sq_header -- 3 members, size 0x8, layout c933ea8274b7.
 *
 * One definition, agreed by the 7 units that declare it: dmm_init.c (DIE 0x18F6C5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sq_header *`.
 *
 * declared by: dmm_init.c (DIE 0x18F6C5), fp_hand.c (DIE 0x1FF342), tra_func.c (DIE 0x2D37A0), ed_ssq_func.c (DIE 0x30540C), infoshow.c (DIE 0x3413A2), kn_lfunc.c (DIE 0x363433), les_play.c (DIE 0x373616)
 */
#ifndef DDR_types_sq_header_H
#define DDR_types_sq_header_H

struct sq_header {   // size 0x8
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short kind;                  // 0x2
    /* 0x006 */ unsigned short division;              // 0x2
};

#endif /* DDR_types_sq_header_H */
