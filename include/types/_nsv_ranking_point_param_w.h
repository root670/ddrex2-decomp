/* struct _nsv_ranking_point_param_w -- 5 members, size 0x24, layout 265d42bb78d1.
 *
 * One definition, agreed by the 2 units that declare it: net_prg.c (DIE 0x8D6E6).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_ranking_point_param_w *`.
 *
 * declared by: net_prg.c (DIE 0x8D6E6), net_game_data.c (DIE 0xCBC31)
 */
#ifndef DDR_types__nsv_ranking_point_param_w_H
#define DDR_types__nsv_ranking_point_param_w_H

struct _nsv_ranking_point_param_w {   // size 0x24
    /* 0x000 */ unsigned int pid;                     // 0x4
    /* 0x004 */ unsigned char name[20];               // 0x14
    /* 0x018 */ short dancer_number;                  // 0x2
    /* 0x01A */ // 0x2 bytes padding
    /* 0x01C */ unsigned int rank;                    // 0x4
    /* 0x020 */ unsigned int points;                  // 0x4
};

#endif /* DDR_types__nsv_ranking_point_param_w_H */
