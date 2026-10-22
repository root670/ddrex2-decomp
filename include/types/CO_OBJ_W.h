/* struct CO_OBJ_W -- 8 members, size 0x280, layout 0dd90dd6653b.
 *
 * One definition, agreed by the 4 units that declare it: workout.c (DIE 0xAD179).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct CO_OBJ_W *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: workout.c (DIE 0xAD179), co_obj.c (DIE 0x1B9493), info.c (DIE 0x334039), opt_main.c (DIE 0x44216F)
 */
#ifndef DDR_types_CO_OBJ_W_H
#define DDR_types_CO_OBJ_W_H

#include "types/anon_1fa6d74458f3.h"

struct CO_OBJ_W {   // size 0x280
    /* 0x000 */ unsigned char step;                   // 0x1
    /* 0x001 */ unsigned char disp_flag;              // 0x1
    /* 0x002 */ unsigned char pri;                    // 0x1
    /* 0x003 */ unsigned char ini_flag;               // 0x1
    /* 0x004 */ unsigned char work[624];              // 0x270
    /* 0x274 */ struct CO_OBJ_W *next;                // 0x4
    /* 0x278 */ anon_1fa6d74458f3 *f;                 // 0x4
    /* 0x27C */ unsigned int id;                      // 0x4
};

#endif /* DDR_types_CO_OBJ_W_H */
