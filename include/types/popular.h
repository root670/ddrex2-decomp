/* struct popular -- 3 members, size 0x4B4, layout c67ca52d0137.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x6FEE).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct popular *`.
 *
 * declared by: les.c (DIE 0x6FEE), les_play.c (DIE 0xD276), reconi.c (DIE 0x23E36), onimode.c (DIE 0x2CC4E), recend.c (DIE 0x389C4), eds_select.c (DIE 0x40895), eds_main.c (DIE 0x46FF8), optscr.c (DIE 0x4BD6A), eds_aid.c (DIE 0x55A83), eds_break.c (DIE 0x5AE72), eds_record.c (DIE 0x5E73C), optdoll.c (DIE 0x9549B), dexport.c (DIE 0x9AC3E), dinit.c (DIE 0x9E688)
 */
#ifndef DDR_types_popular_H
#define DDR_types_popular_H

struct popular {   // size 0x4B4
    /* 0x000 */ short cur_c;                          // 0x2
    /* 0x002 */ short last_c;                         // 0x2
    /* 0x004 */ unsigned short count[150][4];         // 0x4B0
};

#endif /* DDR_types_popular_H */
