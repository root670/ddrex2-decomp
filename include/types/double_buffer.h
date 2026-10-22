/* struct double_buffer -- 3 members, size 0x628, layout 81eb47472c4b.
 *
 * One definition, agreed by the 1 unit that declares it: les_play.c (DIE 0x379BBB).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct double_buffer *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: les_play.c (DIE 0x379BBB)
 */
#ifndef DDR_types_double_buffer_H
#define DDR_types_double_buffer_H

#include "types/anon_271abd9b3a92.h"
#include "types/anon_91122355aec6.h"

struct double_buffer {   // size 0x628
    /* 0x000 */ anon_271abd9b3a92 gs_ot;              // 0x28
    /* 0x028 */ anon_91122355aec6 z_sort[256];        // 0x400
    /* 0x428 */ unsigned char packet[512];            // 0x200
};

#endif /* DDR_types_double_buffer_H */
