/* struct _tag_cOlModule -- 3 members, size 0xC, layout f303d975104a.
 *
 * One definition, agreed by the 1 unit that declares it: olmain.c (DIE 0x54739).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOlModule *`.
 *
 * declared by: olmain.c (DIE 0x54739)
 */
#ifndef DDR_types__tag_cOlModule_H
#define DDR_types__tag_cOlModule_H

struct _tag_cOlData;

#include "types/_tag_cOlData.h"

struct _tag_cOlModule {   // size 0xC
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int id;                               // 0x4
    /* 0x008 */ struct _tag_cOlData *data;            // 0x4
};

#endif /* DDR_types__tag_cOlModule_H */
