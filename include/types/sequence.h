/* struct sequence -- 9 members, size 0x38, layout cf1f43bf546a.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x73E3).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sequence *`.
 *
 * declared by: les.c (DIE 0x73E3), les_play.c (DIE 0x1047B), kn_lfunc.c (DIE 0x18757), onimode.c (DIE 0x2E708), sp_ending_d.c (DIE 0x35C4C), eds_select.c (DIE 0x3BA10), eds_main.c (DIE 0x483E5), eds_aid.c (DIE 0x57063), b_anime.c (DIE 0x6E07E), p_anime.c (DIE 0x74295), ani_load.c (DIE 0x7626E), dexport.c (DIE 0x9738C)
 */
#ifndef DDR_types_sequence_H
#define DDR_types_sequence_H

struct sequence {   // size 0x38
    /* 0x000 */ int beat_count;                       // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ short next_change;                    // 0x2
    /* 0x008 */ short music_count;                    // 0x2
    /* 0x00A */ short judge_count;                    // 0x2
    /* 0x00C */ short stolen_count;                   // 0x2
    /* 0x00E */ short op_note_ct;                     // 0x2
    /* 0x010 */ unsigned int hold_length[8];          // 0x20
    /* 0x030 */ unsigned char hold_stat[8];           // 0x8
};

#endif /* DDR_types_sequence_H */
