/* struct _tag_cOlWork -- 5 members, size 0x40, layout 81eeda8b01f9.
 *
 * One definition, agreed by the 1 unit that declares it: olmain.c (DIE 0x548E7).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOlWork *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: olmain.c (DIE 0x548E7)
 */
#ifndef DDR_types__tag_cOlWork_H
#define DDR_types__tag_cOlWork_H

struct _tag_cOlModule;

#include "types/_tag_cOlModule.h"

struct _tag_cOlWork {   // size 0x40
    /* 0x000 */ struct _tag_cOlModule module[4];      // 0x30
    /* 0x030 */ struct {   // size 0x4
        /* 0x000 */ unsigned char trycount;               // 0x1
        /* 0x001 */ unsigned char spindlctrl;             // 0x1
        /* 0x002 */ unsigned char datapattern;            // 0x1
        /* 0x003 */ unsigned char pad;                    // 0x1
    } cdrmode;
    /* 0x034 */ unsigned int prog_addr;               // 0x4
    /* 0x038 */ unsigned char *prog_file;             // 0x4
    /* 0x03C */ int fp_size;                          // 0x4
};

#endif /* DDR_types__tag_cOlWork_H */
