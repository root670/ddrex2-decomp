/* struct _tag_cLesSelSection -- 8 members, size 0xCC, layout 3ff1d9db08c7.
 *
 * One definition, agreed by the 1 unit that declares it: les_sel_sec.c (DIE 0xACF2).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLesSelSection *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: les_sel_sec.c (DIE 0xACF2)
 */
#ifndef DDR_types__tag_cLesSelSection_H
#define DDR_types__tag_cLesSelSection_H

struct _tag_cLesSectionBannerData;

#include "types/_tag_cLesSectionBannerData.h"

struct _tag_cLesSelSection {   // size 0xCC
    /* 0x000 */ struct {   // size 0x14
        /* 0x000 */ unsigned char *msg;                   // 0x4
        /* 0x004 */ struct {   // size 0x8
            /* 0x000 */ short x;                              // 0x2
            /* 0x002 */ short y;                              // 0x2
            /* 0x004 */ short w;                              // 0x2
            /* 0x006 */ short h;                              // 0x2
        } *win;
        /* 0x008 */ short msg_num;                        // 0x2
        /* 0x00A */ short font_size;                      // 0x2
        /* 0x00C */ int ot;                               // 0x4
        /* 0x010 */ int bright;                           // 0x4
    } font_w;
    /* 0x014 */ int counter;                          // 0x4
    /* 0x018 */ float lx;                             // 0x4
    /* 0x01C */ float ly;                             // 0x4
    /* 0x020 */ int lcounter;                         // 0x4
    /* 0x024 */ int lflag;                            // 0x4
    /* 0x028 */ struct _tag_cLesSectionBannerData sbanner[8];  // 0xA0
    /* 0x0C8 */ int scount;                           // 0x4
};

#endif /* DDR_types__tag_cLesSelSection_H */
