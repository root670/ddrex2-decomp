/* struct one_motion_w -- 5 members, size 0x14, layout 856af39497da.
 *
 * One definition, agreed by the 7 units that declare it: dancer.c (DIE 0x2042E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct one_motion_w *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: dancer.c (DIE 0x2042E), model1.c (DIE 0x25CAD), model2.c (DIE 0x29E3E), motion1.c (DIE 0x2D804), motion2.c (DIE 0x2F5F6), dcamera.c (DIE 0x3508E), dinit.c (DIE 0x3F709)
 */
#ifndef DDR_types_one_motion_w_H
#define DDR_types_one_motion_w_H

struct one_motion_w {   // size 0x14
    /* 0x000 */ int m_id;                             // 0x4
    /* 0x004 */ int frame;                            // 0x4
    /* 0x008 */ unsigned int state;                   // 0x4
    /* 0x00C */ struct {   // size 0xC
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
    } *mdata;
    /* 0x010 */ int weight;                           // 0x4
};

#endif /* DDR_types_one_motion_w_H */
