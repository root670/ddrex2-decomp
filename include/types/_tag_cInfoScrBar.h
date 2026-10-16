/* struct _tag_cInfoScrBar -- 9 members, size 0x24, layout f18a593eda27.
 *
 * One definition, agreed by the 3 units that declare it: infosel.c (DIE 0x32F4DF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cInfoScrBar *`.
 *
 * declared by: infosel.c (DIE 0x32F4DF), info.c (DIE 0x335A04), infoshow.c (DIE 0x343266)
 */
#ifndef DDR_types__tag_cInfoScrBar_H
#define DDR_types__tag_cInfoScrBar_H

struct _tag_cInfoScrBar {   // size 0x24
    /* 0x000 */ int y0;                               // 0x4
    /* 0x004 */ int y1;                               // 0x4
    /* 0x008 */ int bright;                           // 0x4
    /* 0x00C */ int alpha;                            // 0x4
    /* 0x010 */ int xs;                               // 0x4
    /* 0x014 */ int xe;                               // 0x4
    /* 0x018 */ int x;                                // 0x4
    /* 0x01C */ int counter;                          // 0x4
    /* 0x020 */ int disp_flag;                        // 0x4
};

#endif /* DDR_types__tag_cInfoScrBar_H */
