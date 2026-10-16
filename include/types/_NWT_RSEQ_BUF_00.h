/* struct _NWT_RSEQ_BUF_00 -- 4 members, size 0x10, layout 6ea82478b9c0.
 *
 * One definition, agreed by the 1 unit that declares it: net_game_vs.c (DIE 0x1CA678).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NWT_RSEQ_BUF_00 *`.
 *
 * declared by: net_game_vs.c (DIE 0x1CA678)
 */
#ifndef DDR_types__NWT_RSEQ_BUF_00_H
#define DDR_types__NWT_RSEQ_BUF_00_H

struct _NWT_RSEQ_BUF_00 {   // size 0x10
    /* 0x000 */ short seq_num;                        // 0x2
    /* 0x002 */ short judge_count;                    // 0x2
    /* 0x004 */ unsigned char hold_stat[8];           // 0x8
    /* 0x00C */ char dmy[4];                          // 0x4
};

#endif /* DDR_types__NWT_RSEQ_BUF_00_H */
