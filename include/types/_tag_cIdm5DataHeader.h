/* struct _tag_cIdm5DataHeader -- 5 members, size 0x20, layout 80706b0c8c65.
 *
 * One definition, agreed by the 2 units that declare it: info.c (DIE 0x33317B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cIdm5DataHeader *`.
 *
 * declared by: info.c (DIE 0x33317B), infoshow.c (DIE 0x344EFE)
 */
#ifndef DDR_types__tag_cIdm5DataHeader_H
#define DDR_types__tag_cIdm5DataHeader_H

struct _tag_cIdm5DataHeader {   // size 0x20
    /* 0x000 */ int size;                             // 0x4
    /* 0x004 */ int offset_string;                    // 0x4
    /* 0x008 */ int offset_color;                     // 0x4
    /* 0x00C */ int nline;                            // 0x4
    /* 0x010 */ char pad[16];                         // 0x10
};

#endif /* DDR_types__tag_cIdm5DataHeader_H */
