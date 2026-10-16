/* struct _sceDmaTag -- 5 members, size 0x10, layout 7395fc983cd1.
 *
 * One definition, agreed by the 1 unit that declares it: cs_staffroll_fft.c (DIE 0x350696).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _sceDmaTag *`.
 *
 * declared by: cs_staffroll_fft.c (DIE 0x350696)
 */
#ifndef DDR_types__sceDmaTag_H
#define DDR_types__sceDmaTag_H

struct _sceDmaTag {   // size 0x10
    /* 0x000 */ unsigned short qwc;                   // 0x2
    /* 0x002 */ unsigned char mark;                   // 0x1
    /* 0x003 */ unsigned char id;                     // 0x1
    /* 0x004 */ struct _sceDmaTag *next;              // 0x4
    /* 0x008 */ unsigned int p[2];                    // 0x8
};

#endif /* DDR_types__sceDmaTag_H */
