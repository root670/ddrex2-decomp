/* struct _recendtex_w -- 8 members, size 0x1C, layout b46a1cdbc546.
 *
 * One definition, agreed by the 1 unit that declares it: recend.c (DIE 0x3839E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _recendtex_w *`.
 *
 * declared by: recend.c (DIE 0x3839E)
 */
#ifndef DDR_types__recendtex_w_H
#define DDR_types__recendtex_w_H

struct _recendtex_w {   // size 0x1C
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int sx;                               // 0x4
    /* 0x00C */ int sy;                               // 0x4
    /* 0x010 */ int flag;                             // 0x4
    /* 0x014 */ int tex;                              // 0x4
    /* 0x018 */ unsigned char col;                    // 0x1
    /* 0x019 */ unsigned char alpha;                  // 0x1
    /* 0x01A */ // 0x2 bytes padding
};

#endif /* DDR_types__recendtex_w_H */
