/* struct sceImage -- 6 members, size 0x18, layout c83dad12d33f.
 *
 * One definition, agreed by the 6 units that declare it: eye_system.c (DIE 0x488E0).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceImage *`.
 *
 * declared by: eye_system.c (DIE 0x488E0), eye_ref.c (DIE 0x50F1C), eye_filter.c (DIE 0x68570), bk_disp.c (DIE 0xE9665), freeplay.c (DIE 0x11A94B), fp_hand.c (DIE 0x1FECE1)
 */
#ifndef DDR_types_sceImage_H
#define DDR_types_sceImage_H

struct sceImage {   // size 0x18
    /* 0x000 */ int _width;                           // 0x4
    /* 0x004 */ int _height;                          // 0x4
    /* 0x008 */ int _size;                            // 0x4
    /* 0x00C */ int _flags;                           // 0x4
    /* 0x010 */ void *_data;                          // 0x4
    /* 0x014 */ int _type;                            // 0x4
};

#endif /* DDR_types_sceImage_H */
