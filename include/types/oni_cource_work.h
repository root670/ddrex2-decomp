/* struct oni_cource_work -- 7 members, size 0xCC, layout 6b3ad9bbd026.
 *
 * One definition, agreed by the 1 unit that declares it: onimode.c (DIE 0x4873).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct oni_cource_work *`.
 *
 * declared by: onimode.c (DIE 0x4873)
 */
#ifndef DDR_types_oni_cource_work_H
#define DDR_types_oni_cource_work_H

struct oni_course;

#include "types/oni_course.h"

struct oni_cource_work {   // size 0xCC
    /* 0x000 */ int id;                               // 0x4
    /* 0x004 */ int init_ok;                          // 0x4
    /* 0x008 */ struct oni_course *course[41];        // 0xA4
    /* 0x0AC */ int tex_kind;                         // 0x4
    /* 0x0B0 */ int tex_load_step;                    // 0x4
    /* 0x0B4 */ unsigned char seqkind_tab[20];        // 0x14
    /* 0x0C8 */ int dancer_flag;                      // 0x4
};

#endif /* DDR_types_oni_cource_work_H */
