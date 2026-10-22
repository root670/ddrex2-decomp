/* struct one_motion_w -- 5 members, size 0x14, layout 856af39497da.
 *
 * One definition, agreed by the 7 units that declare it: dancer.c (DIE 0x2042E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct one_motion_w *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: dancer.c (DIE 0x2042E), model1.c (DIE 0x25CAD), model2.c (DIE 0x29E3E), motion1.c (DIE 0x2D804), motion2.c (DIE 0x2F5F6), dcamera.c (DIE 0x3508E), dinit.c (DIE 0x3F709)
 */
#ifndef DDR_types_one_motion_w_H
#define DDR_types_one_motion_w_H

#include "types/anon_fc1cdcfc0514.h"

struct one_motion_w {   // size 0x14
    /* 0x000 */ int m_id;                             // 0x4
    /* 0x004 */ int frame;                            // 0x4
    /* 0x008 */ unsigned int state;                   // 0x4
    /* 0x00C */ anon_fc1cdcfc0514 *mdata;             // 0x4
    /* 0x010 */ int weight;                           // 0x4
};

#endif /* DDR_types_one_motion_w_H */
