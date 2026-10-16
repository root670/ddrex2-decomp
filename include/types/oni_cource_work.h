/* struct oni_cource_work -- 4 members, size 0x9C, layout cc0d4c9b612f.
 *
 * One definition, agreed by the 1 unit that declares it: onimode.c (DIE 0x2A695).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct oni_cource_work *`.
 *
 * declared by: onimode.c (DIE 0x2A695)
 */
#ifndef DDR_types_oni_cource_work_H
#define DDR_types_oni_cource_work_H

struct oni_course;

#include "types/oni_course.h"

struct oni_cource_work {   // size 0x9C
    /* 0x000 */ int id;                               // 0x4
    /* 0x004 */ int init_ok;                          // 0x4
    /* 0x008 */ struct oni_course *course[32];        // 0x80
    /* 0x088 */ unsigned char seqkind_tab[20];        // 0x14
};

#endif /* DDR_types_oni_cource_work_H */
