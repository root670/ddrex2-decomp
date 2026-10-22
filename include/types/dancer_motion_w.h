/* struct dancer_motion_w -- 11 members, size 0x5F8, layout 8a53f1437763.
 *
 * One definition, agreed by the 7 units that declare it: dancer.c (DIE 0x20699).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct dancer_motion_w *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: dancer.c (DIE 0x20699), model1.c (DIE 0x24F37), model2.c (DIE 0x27C0E), motion1.c (DIE 0x2D0B6), motion2.c (DIE 0x2EC93), dcamera.c (DIE 0x351AC), dinit.c (DIE 0x3FC7B)
 */
#ifndef DDR_types_dancer_motion_w_H
#define DDR_types_dancer_motion_w_H

struct _GsCOORDINATE2;
struct one_motion_w;

#include "types/_GsCOORDINATE2.h"
#include "types/one_motion_w.h"
#include "types/anon_caea742522ec.h"

struct dancer_motion_w {   // size 0x5F8
    /* 0x000 */ struct _GsCOORDINATE2 coord2[18];     // 0x5A0
    /* 0x5A0 */ unsigned char model_change[16];       // 0x10
    /* 0x5B0 */ int cur_dance_id;                     // 0x4
    /* 0x5B4 */ int last_dance_id;                    // 0x4
    /* 0x5B8 */ struct one_motion_w motion[2];        // 0x28
    /* 0x5E0 */ anon_caea742522ec *mpack;             // 0x4
    /* 0x5E4 */ int cur_p_counter;                    // 0x4
    /* 0x5E8 */ int last_p_counter;                   // 0x4
    /* 0x5EC */ int dance_class;                      // 0x4
    /* 0x5F0 */ float adj_x;                          // 0x4
    /* 0x5F4 */ float adj_z;                          // 0x4
};

#endif /* DDR_types_dancer_motion_w_H */
