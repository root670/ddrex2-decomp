/* struct _GsCOORDINATE2 -- 6 members, size 0x50, layout 76b2d532e3ca.
 *
 * One definition, agreed by the 8 units that declare it: dancer.c (DIE 0x20FFC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _GsCOORDINATE2 *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: dancer.c (DIE 0x20FFC), model1.c (DIE 0x2659C), model2.c (DIE 0x275FD), motion1.c (DIE 0x2D925), motion2.c (DIE 0x2EF14), ps1lib.c (DIE 0x31034), dcamera.c (DIE 0x354A5), dinit.c (DIE 0x4093F)
 */
#ifndef DDR_types__GsCOORDINATE2_H
#define DDR_types__GsCOORDINATE2_H

struct _GsCOORDINATE2 {   // size 0x50
    /* 0x000 */ unsigned int flg;                     // 0x4
    /* 0x004 */ struct {   // size 0x20
        /* 0x000 */ short m[3][3];                        // 0x12
        /* 0x012 */ // 0x2 bytes padding
        /* 0x014 */ int t[3];                             // 0xC
    } coord;
    /* 0x024 */ struct {   // size 0x20
        /* 0x000 */ short m[3][3];                        // 0x12
        /* 0x012 */ // 0x2 bytes padding
        /* 0x014 */ int t[3];                             // 0xC
    } workm;
    /* 0x044 */ struct {   // size 0x28
        /* 0x000 */ struct {   // size 0x10
            /* 0x000 */ int vx;                               // 0x4
            /* 0x004 */ int vy;                               // 0x4
            /* 0x008 */ int vz;                               // 0x4
            /* 0x00C */ int pad;                              // 0x4
        } scale;
        /* 0x010 */ struct {   // size 0x8
            /* 0x000 */ short vx;                             // 0x2
            /* 0x002 */ short vy;                             // 0x2
            /* 0x004 */ short vz;                             // 0x2
            /* 0x006 */ short pad;                            // 0x2
        } rotate;
        /* 0x018 */ struct {   // size 0x10
            /* 0x000 */ int vx;                               // 0x4
            /* 0x004 */ int vy;                               // 0x4
            /* 0x008 */ int vz;                               // 0x4
            /* 0x00C */ int pad;                              // 0x4
        } trans;
    } *param;
    /* 0x048 */ struct _GsCOORDINATE2 *super;         // 0x4
    /* 0x04C */ struct _GsCOORDINATE2 *sub;           // 0x4
};

#endif /* DDR_types__GsCOORDINATE2_H */
