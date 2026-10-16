/* struct dancer_model_w -- 22 members, size 0x730, layout 32f1e36a8a89.
 *
 * One definition, agreed by the 6 units that declare it: dancer.c (DIE 0x1FB24).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct dancer_model_w *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: dancer.c (DIE 0x1FB24), model1.c (DIE 0x24838), model2.c (DIE 0x2824D), motion1.c (DIE 0x2C57C), dcamera.c (DIE 0x338F4), dinit.c (DIE 0x42215)
 */
#ifndef DDR_types_dancer_model_w_H
#define DDR_types_dancer_model_w_H

struct _GsCOORDINATE2;

#include "types/_GsCOORDINATE2.h"

struct dancer_model_w {   // size 0x730
    /* 0x000 */ struct {   // size 0x14
        /* 0x000 */ unsigned int attribute;               // 0x4
        /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
        /* 0x008 */ unsigned int *tmd;                    // 0x4
        /* 0x00C */ unsigned int *packet;                 // 0x4
        /* 0x010 */ unsigned int id;                      // 0x4
    } obj[30];
    /* 0x258 */ int entry[17];                        // 0x44
    /* 0x29C */ unsigned int model;                   // 0x4
    /* 0x2A0 */ unsigned int *packet;                 // 0x4
    /* 0x2A4 */ unsigned int *header;                 // 0x4
    /* 0x2A8 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x2B0 */ float m[17][4][4];                    // 0x440
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
    /* 0x724 */ struct {   // size 0x10
        /* 0x000 */ float x;                              // 0x4
        /* 0x004 */ float y;                              // 0x4
        /* 0x008 */ float z;                              // 0x4
        /* 0x00C */ unsigned int disp : 1;                // bits 0..0
    } *einf;
    /* 0x728 */ // 0x8 bytes padding if 16-byte aligned, else a member DWARF omits
};

#endif /* DDR_types_dancer_model_w_H */
