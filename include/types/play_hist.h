/* struct play_hist -- 2 members, size 0xC, layout a3d6daee7587.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x7566).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_hist *`.
 *
 * declared by: les.c (DIE 0x7566), les_play.c (DIE 0x115DE), kn_lfunc.c (DIE 0x1A006), onimode.c (DIE 0x2E992), sp_ending_d.c (DIE 0x35E73), eds_select.c (DIE 0x3C786), eds_main.c (DIE 0x48BB2), eds_aid.c (DIE 0x57859), b_anime.c (DIE 0x6E201), p_anime.c (DIE 0x744D0), ani_load.c (DIE 0x763F1), dexport.c (DIE 0x97B59)
 */
#ifndef DDR_types_play_hist_H
#define DDR_types_play_hist_H

struct play_hist {   // size 0xC
    /* 0x000 */ int music_count;                      // 0x4
    /* 0x004 */ unsigned char input[8];               // 0x8
};

#endif /* DDR_types_play_hist_H */
