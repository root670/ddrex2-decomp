/* struct note_status -- 2 members, size 0x28, layout 366edeb915db.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x6F39).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct note_status *`.
 *
 * declared by: les.c (DIE 0x6F39), les_play.c (DIE 0xF4A2), kn_lfunc.c (DIE 0x197C0), onimode.c (DIE 0x2E139), sp_ending_d.c (DIE 0x35A71), eds_select.c (DIE 0x41609), eds_main.c (DIE 0x47C13), eds_aid.c (DIE 0x5669E), b_anime.c (DIE 0x6D717), p_anime.c (DIE 0x74196), ani_load.c (DIE 0x75D61), dexport.c (DIE 0x9B7A2)
 */
#ifndef DDR_types_note_status_H
#define DDR_types_note_status_H

struct note_status {   // size 0x28
    /* 0x000 */ unsigned char state[8];               // 0x8
    /* 0x008 */ unsigned int length[8];               // 0x20
};

#endif /* DDR_types_note_status_H */
