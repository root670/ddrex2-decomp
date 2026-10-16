/* struct double_buffer -- 3 members, size 0x628, layout 81eb47472c4b.
 *
 * One definition, agreed by the 1 unit that declares it: les_play.c (DIE 0x12C11).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct double_buffer *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: les_play.c (DIE 0x12C11)
 */
#ifndef DDR_types_double_buffer_H
#define DDR_types_double_buffer_H

struct double_buffer {   // size 0x628
    /* 0x000 */ struct {   // size 0x28
        /* 0x000 */ unsigned long length;                 // 0x8
        /* 0x008 */ struct {   // size 0x4
            /* 0x000 */ unsigned int p : 24;                  // bits 0..23
            /* 0x003 */ unsigned char num : 8;                // bits 0..7
        } *org;
        /* 0x00C */ // 0x4 bytes padding
        /* 0x010 */ unsigned long offset;                 // 0x8
        /* 0x018 */ unsigned long point;                  // 0x8
        /* 0x020 */ struct {   // size 0x4
            /* 0x000 */ unsigned int p : 24;                  // bits 0..23
            /* 0x003 */ unsigned char num : 8;                // bits 0..7
        } *tag;
        /* 0x024 */ // 0x4 bytes padding
    } gs_ot;
    /* 0x028 */ struct {   // size 0x4
        /* 0x000 */ unsigned int p : 24;                  // bits 0..23
        /* 0x003 */ unsigned char num : 8;                // bits 0..7
    } z_sort[256];
    /* 0x428 */ unsigned char packet[512];            // 0x200
};

#endif /* DDR_types_double_buffer_H */
