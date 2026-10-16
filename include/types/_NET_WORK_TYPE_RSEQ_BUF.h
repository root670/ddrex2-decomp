/* struct _NET_WORK_TYPE_RSEQ_BUF -- 5 members, size 0x4C, layout 1a82b48f3ba7.
 *
 * One definition, agreed by the 1 unit that declares it: net_game_vs.c (DIE 0x1C6F1F).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NET_WORK_TYPE_RSEQ_BUF *`.
 *
 * declared by: net_game_vs.c (DIE 0x1C6F1F)
 */
#ifndef DDR_types__NET_WORK_TYPE_RSEQ_BUF_H
#define DDR_types__NET_WORK_TYPE_RSEQ_BUF_H

struct _NWT_RSEQ_BUF_00;

#include "types/_NWT_RSEQ_BUF_00.h"

struct _NET_WORK_TYPE_RSEQ_BUF {   // size 0x4C
    /* 0x000 */ struct _NWT_RSEQ_BUF_00 seqb[4];      // 0x40
    /* 0x040 */ int seq_data_num;                     // 0x4
    /* 0x044 */ short cur_point;                      // 0x2
    /* 0x046 */ short cur_great_combo;                // 0x2
    /* 0x048 */ unsigned int real_score;              // 0x4
};

#endif /* DDR_types__NET_WORK_TYPE_RSEQ_BUF_H */
