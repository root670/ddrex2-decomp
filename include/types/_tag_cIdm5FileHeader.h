/* struct _tag_cIdm5FileHeader -- 4 members, size 0x10, layout 2ed1f360dee0.
 *
 * One definition, agreed by the 3 units that declare it: infosel.c (DIE 0x32E8A3).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cIdm5FileHeader *`.
 *
 * declared by: infosel.c (DIE 0x32E8A3), info.c (DIE 0x332525), infoshow.c (DIE 0x3447D1)
 */
#ifndef DDR_types__tag_cIdm5FileHeader_H
#define DDR_types__tag_cIdm5FileHeader_H

struct _tag_cIdm5FileHeader {   // size 0x10
    /* 0x000 */ int size;                             // 0x4
    /* 0x004 */ int ninfo;                            // 0x4
    /* 0x008 */ int flag;                             // 0x4
    /* 0x00C */ int offset_data;                      // 0x4
};

#endif /* DDR_types__tag_cIdm5FileHeader_H */
