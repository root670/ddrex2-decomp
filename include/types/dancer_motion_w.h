/* struct dancer_motion_w -- 11 members, size 0x5F8, layout 8a53f1437763.
 *
 * One definition, agreed by the 7 units that declare it: dcamera.c (DIE 0x7FA81).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct dancer_motion_w *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: dcamera.c (DIE 0x7FA81), model1.c (DIE 0x848CE), model2.c (DIE 0x87A94), motion1.c (DIE 0x8BDD9), motion2.c (DIE 0x8DC0E), dancer.c (DIE 0x9115E), dinit.c (DIE 0x9E388)
 */
#ifndef DDR_types_dancer_motion_w_H
#define DDR_types_dancer_motion_w_H

struct _GsCOORDINATE2;
struct one_motion_w;

#include "types/_GsCOORDINATE2.h"
#include "types/one_motion_w.h"

struct dancer_motion_w {   // size 0x5F8
    /* 0x000 */ struct _GsCOORDINATE2 coord2[18];     // 0x5A0
    /* 0x5A0 */ unsigned char model_change[16];       // 0x10
    /* 0x5B0 */ int cur_dance_id;                     // 0x4
    /* 0x5B4 */ int last_dance_id;                    // 0x4
    /* 0x5B8 */ struct one_motion_w motion[2];        // 0x28
    /* 0x5E0 */ struct {   // size 0x10
        /* 0x000 */ char magic[2];                        // 0x2
        /* 0x002 */ short nbmdt;                          // 0x2
        /* 0x004 */ int reserve;                          // 0x4
        /* 0x008 */ struct {   // size 0x8
            /* 0x000 */ char *name;                           // 0x4
            /* 0x004 */ struct {   // size 0xC
                /* 0x000 */ unsigned int size;                    // 0x4
                /* 0x004 */ unsigned short nbparts;               // 0x2
                /* 0x006 */ unsigned short nbframe;               // 0x2
                /* 0x008 */ struct {   // size 0xC
                    /* 0x000 */ unsigned char id;                     // 0x1
                    /* 0x001 */ unsigned char format;                 // 0x1
                    /* 0x002 */ unsigned char hastrans;               // 0x1
                    /* 0x003 */ unsigned char parent_id;              // 0x1
                    /* 0x004 */ unsigned int nbwave;                  // 0x4
                    /* 0x008 */ struct {   // size 0x8
                        /* 0x000 */ unsigned char kind;                   // 0x1
                        /* 0x001 */ unsigned char pad[3];                 // 0x3
                        /* 0x004 */ struct {   // size 0x4
                            /* 0x000 */ unsigned short shift_bit;             // 0x2
                            /* 0x002 */ struct {   // size 0x2
                                /* 0x000 */ unsigned short offset;                // 0x2
                            } tbl[1];
                        } data;
                    } **offset;
                } **offset;
            } *offset;
        } motion[1];
    } *mpack;
    /* 0x5E4 */ int cur_p_counter;                    // 0x4
    /* 0x5E8 */ int last_p_counter;                   // 0x4
    /* 0x5EC */ int dance_class;                      // 0x4
    /* 0x5F0 */ float adj_x;                          // 0x4
    /* 0x5F4 */ float adj_z;                          // 0x4
};

#endif /* DDR_types_dancer_motion_w_H */
