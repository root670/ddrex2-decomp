/* struct _nsv_ranking_htoh_param_w -- 9 members, size 0x34, layout 13cd81d0079f.
 *
 * One definition, agreed by the 2 units that declare it: net_prg.c (DIE 0x8C5B0).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_ranking_htoh_param_w *`.
 *
 * declared by: net_prg.c (DIE 0x8C5B0), net_game_data.c (DIE 0xCCED6)
 */
#ifndef DDR_types__nsv_ranking_htoh_param_w_H
#define DDR_types__nsv_ranking_htoh_param_w_H

struct _nsv_ranking_htoh_param_w {   // size 0x34
    /* 0x000 */ unsigned int pid;                     // 0x4
    /* 0x004 */ unsigned char name[20];               // 0x14
    /* 0x018 */ short dancer_number;                  // 0x2
    /* 0x01A */ // 0x2 bytes padding
    /* 0x01C */ unsigned int rank;                    // 0x4
    /* 0x020 */ unsigned int match;                   // 0x4
    /* 0x024 */ unsigned int win;                     // 0x4
    /* 0x028 */ unsigned int lose;                    // 0x4
    /* 0x02C */ unsigned int draw;                    // 0x4
    /* 0x030 */ float win_avg;                        // 0x4
};

#endif /* DDR_types__nsv_ranking_htoh_param_w_H */
