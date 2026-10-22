/* struct _tag_cOlWork -- 5 members, size 0x40, layout 81eeda8b01f9.
 *
 * One definition, agreed by the 1 unit that declares it: olmain.c (DIE 0x548E7).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOlWork *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: olmain.c (DIE 0x548E7)
 */
#ifndef DDR_types__tag_cOlWork_H
#define DDR_types__tag_cOlWork_H

struct _tag_cOlModule;

#include "types/_tag_cOlModule.h"
#include "types/anon_a52589d29f2d.h"

struct _tag_cOlWork {   // size 0x40
    /* 0x000 */ struct _tag_cOlModule module[4];      // 0x30
    /* 0x030 */ anon_a52589d29f2d cdrmode;            // 0x4
    /* 0x034 */ unsigned int prog_addr;               // 0x4
    /* 0x038 */ unsigned char *prog_file;             // 0x4
    /* 0x03C */ int fp_size;                          // 0x4
};

#endif /* DDR_types__tag_cOlWork_H */
