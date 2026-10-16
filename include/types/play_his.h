/* struct play_his -- 6 members, size 0x8, layout 155772b32f36.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x5E4D).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_his *`.
 *
 * declared by: les.c (DIE 0x5E4D), les_play.c (DIE 0xCB09), kn_lfunc.c (DIE 0x1821F), onimode.c (DIE 0x2D08E), sp_ending_d.c (DIE 0x3510D), eds_select.c (DIE 0x402CC), eds_main.c (DIE 0x46C8E), eds_aid.c (DIE 0x556F3), b_anime.c (DIE 0x7050A), p_anime.c (DIE 0x7380C), ani_load.c (DIE 0x780BE), dexport.c (DIE 0x9A8D4)
 */
#ifndef DDR_types_play_his_H
#define DDR_types_play_his_H

struct play_his {   // size 0x8
    /* 0x000 */ short music;                          // 0x2
    /* 0x002 */ short edit_id;                        // 0x2
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ signed char roulette;                 // 0x1
    /* 0x006 */ signed char extra;                    // 0x1
    /* 0x007 */ signed char pad;                      // 0x1
};

#endif /* DDR_types_play_his_H */
