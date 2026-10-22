/* struct dancer_model_w -- 22 members, size 0x730, layout 32f1e36a8a89.
 *
 * One definition, agreed by the 6 units that declare it: dancer.c (DIE 0x1FB24).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct dancer_model_w *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: dancer.c (DIE 0x1FB24), model1.c (DIE 0x24838), model2.c (DIE 0x2824D), motion1.c (DIE 0x2C57C), dcamera.c (DIE 0x338F4), dinit.c (DIE 0x42215)
 */
#ifndef DDR_types_dancer_model_w_H
#define DDR_types_dancer_model_w_H

#include "types/anon_67489868bb1e.h"
#include "types/anon_934863761eeb.h"

struct dancer_model_w {   // size 0x730
    /* 0x000 */ anon_934863761eeb obj[30];            // 0x258
    /* 0x258 */ int entry[17];                        // 0x44
    /* 0x29C */ unsigned int model;                   // 0x4
    /* 0x2A0 */ unsigned int *packet;                 // 0x4
    /* 0x2A4 */ unsigned int *header;                 // 0x4
    /* 0x2A8 */ // 0x8 bytes padding
    /* 0x2B0 */ float m[17][4][4] __attribute__((aligned(16)));  // 0x440
    /* 0x6F0 */ unsigned int *prim_tbl;               // 0x4
    /* 0x6F4 */ float dist;                           // 0x4
    /* 0x6F8 */ float scale;                          // 0x4
    /* 0x6FC */ float sscale;                         // 0x4
    /* 0x700 */ float x;                              // 0x4
    /* 0x704 */ float y;                              // 0x4
    /* 0x708 */ float z;                              // 0x4
    /* 0x70C */ short winkcnt;                        // 0x2
    /* 0x70E */ unsigned short chara;                 // 0x2
    /* 0x710 */ char hide;                            // 0x1
    /* 0x711 */ // 0x3 bytes padding
    /* 0x714 */ float sel_ox;                         // 0x4
    /* 0x718 */ float sel_oy;                         // 0x4
    /* 0x71C */ float sel_oz;                         // 0x4
    /* 0x720 */ unsigned char id;                     // 0x1
    /* 0x721 */ unsigned char pad[2];                 // 0x2
    /* 0x723 */ // 0x1 bytes padding
    /* 0x724 */ anon_67489868bb1e *einf;              // 0x4
    /* 0x728 */ // 0x8 bytes padding
};

#endif /* DDR_types_dancer_model_w_H */
