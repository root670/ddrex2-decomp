/* struct _DOUBLE_DISP_W -- 14 members, size 0xE0, layout 98c1f1273934.
 *
 * One definition, agreed by the 5 units that declare it: eye_system.c (DIE 0x47FB9).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _DOUBLE_DISP_W *`.
 *
 * declared by: eye_system.c (DIE 0x47FB9), eye_ref.c (DIE 0x51229), bk_disp.c (DIE 0xEA232), freeplay.c (DIE 0x11B1FD), fp_hand.c (DIE 0x1FF0A3)
 */
#ifndef DDR_types__DOUBLE_DISP_W_H
#define DDR_types__DOUBLE_DISP_W_H

struct sceImage;

#include "types/sceImage.h"

struct _DOUBLE_DISP_W {   // size 0xE0
    /* 0x000 */ int count_num;                        // 0x4
    /* 0x004 */ int packmode;                         // 0x4
    /* 0x008 */ int filter;                           // 0x4
    /* 0x00C */ int tex_num;                          // 0x4
    /* 0x010 */ int disp_num;                         // 0x4
    /* 0x014 */ void *bitstream[3];                   // 0xC
    /* 0x020 */ struct sceImage disp;                 // 0x18
    /* 0x038 */ struct sceImage lum_y;                // 0x18
    /* 0x050 */ struct sceImage cr;                   // 0x18
    /* 0x068 */ struct sceImage cb;                   // 0x18
    /* 0x080 */ struct sceImage tmpimage1;            // 0x18
    /* 0x098 */ struct sceImage tmpimage2;            // 0x18
    /* 0x0B0 */ struct sceImage tmpimage3;            // 0x18
    /* 0x0C8 */ struct sceImage rgba_disp;            // 0x18
};

#endif /* DDR_types__DOUBLE_DISP_W_H */
