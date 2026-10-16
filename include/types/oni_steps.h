/* struct oni_steps -- 2 members, size 0x14, layout 9c0de1878b96.
 *
 * One definition, agreed by the 2 units that declare it: onimode.c (DIE 0x2D1A7).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct oni_steps *`.
 *
 * declared by: onimode.c (DIE 0x2D1A7), oni_list.c (DIE 0x4E0D4)
 */
#ifndef DDR_types_oni_steps_H
#define DDR_types_oni_steps_H

struct oni_steps {   // size 0x14
    /* 0x000 */ unsigned int link_num;                // 0x4
    /* 0x004 */ unsigned short steps[2][4];           // 0x10
};

#endif /* DDR_types_oni_steps_H */
