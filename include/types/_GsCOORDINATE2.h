/* struct _GsCOORDINATE2 -- 6 members, size 0x50, layout 76b2d532e3ca.
 *
 * One definition, agreed by the 8 units that declare it: dancer.c (DIE 0x20FFC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _GsCOORDINATE2 *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: dancer.c (DIE 0x20FFC), model1.c (DIE 0x2659C), model2.c (DIE 0x275FD), motion1.c (DIE 0x2D925), motion2.c (DIE 0x2EF14), ps1lib.c (DIE 0x31034), dcamera.c (DIE 0x354A5), dinit.c (DIE 0x4093F)
 */
#ifndef DDR_types__GsCOORDINATE2_H
#define DDR_types__GsCOORDINATE2_H

#include "types/anon_9e9126627b05.h"
#include "types/anon_b6ba1fe93475.h"

struct _GsCOORDINATE2 {   // size 0x50
    /* 0x000 */ unsigned int flg;                     // 0x4
    /* 0x004 */ anon_b6ba1fe93475 coord;              // 0x20
    /* 0x024 */ anon_b6ba1fe93475 workm;              // 0x20
    /* 0x044 */ anon_9e9126627b05 *param;             // 0x4
    /* 0x048 */ struct _GsCOORDINATE2 *super;         // 0x4
    /* 0x04C */ struct _GsCOORDINATE2 *sub;           // 0x4
};

#endif /* DDR_types__GsCOORDINATE2_H */
