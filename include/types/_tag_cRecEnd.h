/* struct _tag_cRecEnd -- 7 members, size 0x340, layout ea42600a71cf.
 *
 * One definition, agreed by the 1 unit that declares it: recend.c (DIE 0x374AA).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecEnd *`.
 *
 * declared by: recend.c (DIE 0x374AA)
 */
#ifndef DDR_types__tag_cRecEnd_H
#define DDR_types__tag_cRecEnd_H

struct _recendtex_w;

#include "types/_recendtex_w.h"

struct _tag_cRecEnd {   // size 0x340
    /* 0x000 */ int pad;                              // 0x4
    /* 0x004 */ int page;                             // 0x4
    /* 0x008 */ int cur;                              // 0x4
    /* 0x00C */ int step;                             // 0x4
    /* 0x010 */ char kakunin;                         // 0x1
    /* 0x011 */ char flash;                           // 0x1
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ struct _recendtex_w twork[29];        // 0x32C
};

#endif /* DDR_types__tag_cRecEnd_H */
