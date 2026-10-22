/* struct _tag_cOlData -- 9 members, size 0x68, layout 7c834054657c.
 *
 * One definition, agreed by the 1 unit that declares it: olmain.c (DIE 0x543C5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOlData *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: olmain.c (DIE 0x543C5)
 */
#ifndef DDR_types__tag_cOlData_H
#define DDR_types__tag_cOlData_H

#include "types/anon_31c7db27763e.h"
#include "types/anon_6c0c294bd5d4.h"

struct _tag_cOlData {   // size 0x68
    /* 0x000 */ unsigned int prog_addr;               // 0x4
    /* 0x004 */ unsigned char *prog_file;             // 0x4
    /* 0x008 */ anon_31c7db27763e fp;                 // 0x24
    /* 0x02C */ // 0x4 bytes padding
    /* 0x030 */ anon_6c0c294bd5d4 prog_pos;           // 0x8
    /* 0x038 */ unsigned int data_addr;               // 0x4
    /* 0x03C */ void *data_file[7];                   // 0x1C
    /* 0x058 */ void (*init_func)();                  // 0x4
    /* 0x05C */ int (*main_func)();                   // 0x4
    /* 0x060 */ void (*term_func)();                  // 0x4
    /* 0x064 */ // 0x4 bytes padding
};

#endif /* DDR_types__tag_cOlData_H */
