/* struct machine_point_work -- 4 members, size 0x14, layout bb320cdfc4a1.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x596A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct machine_point_work *`.
 *
 * declared by: les.c (DIE 0x596A), les_play.c (DIE 0x127AA), reconi.c (DIE 0x22996), onimode.c (DIE 0x2EC8C), recend.c (DIE 0x37B18), eds_select.c (DIE 0x3DEF4), eds_main.c (DIE 0x44181), optscr.c (DIE 0x4A954), eds_aid.c (DIE 0x52E26), eds_break.c (DIE 0x59B7B), eds_record.c (DIE 0x5D947), optdoll.c (DIE 0x94408), dexport.c (DIE 0x98B04), dinit.c (DIE 0x9D402)
 */
#ifndef DDR_types_machine_point_work_H
#define DDR_types_machine_point_work_H

struct machine_point_work {   // size 0x14
    /* 0x000 */ unsigned int hide_show[2];            // 0x8
    /* 0x008 */ unsigned int status;                  // 0x4
    /* 0x00C */ unsigned int period_time;             // 0x4
    /* 0x010 */ int cur_point;                        // 0x4
};

#endif /* DDR_types_machine_point_work_H */
