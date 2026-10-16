/* struct dance_set -- 2 members, size 0x24, layout c9026be88383.
 *
 * One definition, agreed by the 1 unit that declares it: motion1.c (DIE 0x2CAF7).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct dance_set *`.
 *
 * declared by: motion1.c (DIE 0x2CAF7)
 */
#ifndef DDR_types_dance_set_H
#define DDR_types_dance_set_H

struct dance_set {   // size 0x24
    /* 0x000 */ int kind;                             // 0x4
    /* 0x004 */ char motion_name[2][16];              // 0x20
};

#endif /* DDR_types_dance_set_H */
