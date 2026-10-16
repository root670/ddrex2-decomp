/* struct _tri_w -- 11 members, size 0x2C, layout 287f4517648c.
 *
 * One definition, agreed by the 1 unit that declares it: eye_ref.c (DIE 0x510AB).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tri_w *`.
 *
 * declared by: eye_ref.c (DIE 0x510AB)
 */
#ifndef DDR_types__tri_w_H
#define DDR_types__tri_w_H

struct _tri_w {   // size 0x2C
    /* 0x000 */ float Xrr;                            // 0x4
    /* 0x004 */ float Yrr;                            // 0x4
    /* 0x008 */ float X00;                            // 0x4
    /* 0x00C */ float Y00;                            // 0x4
    /* 0x010 */ float X01;                            // 0x4
    /* 0x014 */ float Y01;                            // 0x4
    /* 0x018 */ float X02;                            // 0x4
    /* 0x01C */ float Y02;                            // 0x4
    /* 0x020 */ float A;                              // 0x4
    /* 0x024 */ int Ans;                              // 0x4
    /* 0x028 */ int flag;                             // 0x4
};

#endif /* DDR_types__tri_w_H */
