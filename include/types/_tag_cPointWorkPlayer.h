/* struct _tag_cPointWorkPlayer -- 4 members, size 0x4C, layout 91702eaebd1f.
 *
 * One definition, agreed by the 1 unit that declares it: point.c (DIE 0x1E3E7B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cPointWorkPlayer *`.
 *
 * declared by: point.c (DIE 0x1E3E7B)
 */
#ifndef DDR_types__tag_cPointWorkPlayer_H
#define DDR_types__tag_cPointWorkPlayer_H

struct eval_w;

#include "types/eval_w.h"

struct _tag_cPointWorkPlayer {   // size 0x4C
    /* 0x000 */ int difficulty;                       // 0x4
    /* 0x004 */ struct eval_w eval;                   // 0x40
    /* 0x044 */ int disp_point;                       // 0x4
    /* 0x048 */ int real_point;                       // 0x4
};

#endif /* DDR_types__tag_cPointWorkPlayer_H */
