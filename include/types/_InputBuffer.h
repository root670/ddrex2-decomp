/* struct _InputBuffer -- 2 members, size 0x48, layout 0ddcfc3ef1a0.
 *
 * One definition, agreed by the 4 units that declare it: les_play.c (DIE 0x145E2).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _InputBuffer *`.
 *
 * declared by: les_play.c (DIE 0x145E2), onimode.c (DIE 0x2CE65), sp_ending_d.c (DIE 0x34FBF), eds_select.c (DIE 0x3FE61)
 */
#ifndef DDR_types__InputBuffer_H
#define DDR_types__InputBuffer_H

struct _InputData;

#include "types/_InputData.h"

struct _InputBuffer {   // size 0x48
    /* 0x000 */ unsigned long current_buffer;         // 0x8
    /* 0x008 */ struct _InputData data[2];            // 0x40
};

#endif /* DDR_types__InputBuffer_H */
