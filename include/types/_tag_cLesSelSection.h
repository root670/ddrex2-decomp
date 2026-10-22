/* struct _tag_cLesSelSection -- 11 members, size 0xD8, layout 9fc14c9e9357.
 *
 * One definition, agreed by the 1 unit that declares it: les_sel_sec.c (DIE 0x384EE4).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLesSelSection *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: les_sel_sec.c (DIE 0x384EE4)
 */
#ifndef DDR_types__tag_cLesSelSection_H
#define DDR_types__tag_cLesSelSection_H

struct _tag_cLesSectionBannerData;

#include "types/_tag_cLesSectionBannerData.h"
#include "types/anon_2cc6ff579267.h"

struct _tag_cLesSelSection {   // size 0xD8
    /* 0x000 */ anon_2cc6ff579267 font_w;             // 0x14
    /* 0x014 */ int counter;                          // 0x4
    /* 0x018 */ float lx;                             // 0x4
    /* 0x01C */ float ly;                             // 0x4
    /* 0x020 */ int lcounter;                         // 0x4
    /* 0x024 */ int lflag;                            // 0x4
    /* 0x028 */ struct _tag_cLesSectionBannerData sbanner[8];  // 0xA0
    /* 0x0C8 */ int scount;                           // 0x4
    /* 0x0CC */ int step;                             // 0x4
    /* 0x0D0 */ int timer;                            // 0x4
    /* 0x0D4 */ void *item;                           // 0x4
};

#endif /* DDR_types__tag_cLesSelSection_H */
