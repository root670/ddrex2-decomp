/* struct _nsv_ranking_rc_work -- 2 members, size 0x12C4, layout aacc7e88981a.
 *
 * One definition, agreed by the 1 unit that declares it: net_prg.c (DIE 0x87EF8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_ranking_rc_work *`.
 *
 * declared by: net_prg.c (DIE 0x87EF8)
 */
#ifndef DDR_types__nsv_ranking_rc_work_H
#define DDR_types__nsv_ranking_rc_work_H

struct _nsv_ranking_rc_param_w;

#include "types/_nsv_ranking_rc_param_w.h"

struct _nsv_ranking_rc_work {   // size 0x12C4
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ struct _nsv_ranking_rc_param_w list[100];  // 0x12C0
};

#endif /* DDR_types__nsv_ranking_rc_work_H */
