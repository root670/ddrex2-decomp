/* struct G_INPUT_W_ -- 2 members, size 0x50, layout 756b8a9145de.
 *
 * One definition, agreed by the 4 units that declare it: les_play.c (DIE 0x11C0E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct G_INPUT_W_ *`.
 *
 * declared by: les_play.c (DIE 0x11C0E), onimode.c (DIE 0x2EF6C), sp_ending_d.c (DIE 0x32CF1), eds_select.c (DIE 0x3D096)
 */
#ifndef DDR_types_G_INPUT_W__H
#define DDR_types_G_INPUT_W__H

struct _InputBuffer;
struct _InputData;

#include "types/_InputBuffer.h"
#include "types/_InputData.h"

struct G_INPUT_W_ {   // size 0x50
    /* 0x000 */ struct _InputData *dp;                // 0x4
    /* 0x004 */ // 0x4 bytes padding
    /* 0x008 */ struct _InputBuffer buffer;           // 0x48
};

#endif /* DDR_types_G_INPUT_W__H */
