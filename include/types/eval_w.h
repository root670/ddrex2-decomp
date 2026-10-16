/* struct eval_w -- 9 members, size 0x6C, layout 31c7ad03a611.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x7C35).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct eval_w *`.
 *
 * declared by: les.c (DIE 0x7C35), les_play.c (DIE 0x11A84), kn_lfunc.c (DIE 0x1A2C3), onimode.c (DIE 0x2EDBE), sp_ending_d.c (DIE 0x32D5D), eds_select.c (DIE 0x3D128), eds_main.c (DIE 0x4915F), eds_aid.c (DIE 0x57E03), b_anime.c (DIE 0x6E3B3), p_anime.c (DIE 0x74616), ani_load.c (DIE 0x76513), dexport.c (DIE 0x98252)
 */
#ifndef DDR_types_eval_w_H
#define DDR_types_eval_w_H

struct eval_w {   // size 0x6C
    /* 0x000 */ int value_ct[7];                      // 0x1C
    /* 0x01C */ int freez_value_ct[4];                // 0x10
    /* 0x02C */ int groov_bonus[6];                   // 0x18
    /* 0x044 */ int groov_bonus_max[6];               // 0x18
    /* 0x05C */ int score;                            // 0x4
    /* 0x060 */ int max_combo_ct;                     // 0x4
    /* 0x064 */ int jump_ct;                          // 0x4
    /* 0x068 */ short dance_level;                    // 0x2
    /* 0x06A */ short fixed_level;                    // 0x2
};

#endif /* DDR_types_eval_w_H */
