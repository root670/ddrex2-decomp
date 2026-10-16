/* struct _tag_cInfoText -- 4 members, size 0x10, layout 6672c41d33a8.
 *
 * One definition, agreed by the 3 units that declare it: infosel.c (DIE 0x32E95C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cInfoText *`.
 *
 * declared by: infosel.c (DIE 0x32E95C), info.c (DIE 0x332369), infoshow.c (DIE 0x340CEB)
 */
#ifndef DDR_types__tag_cInfoText_H
#define DDR_types__tag_cInfoText_H

struct _tag_cInfoText {   // size 0x10
    /* 0x000 */ int infotxt_num;                      // 0x4
    /* 0x004 */ int page_num;                         // 0x4
    /* 0x008 */ int new_state;                        // 0x4
    /* 0x00C */ unsigned int text_address;            // 0x4
};

#endif /* DDR_types__tag_cInfoText_H */
