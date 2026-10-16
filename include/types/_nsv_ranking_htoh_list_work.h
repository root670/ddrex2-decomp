/* struct _nsv_ranking_htoh_list_work -- 2 members, size 0x1454, layout fff8187dced3.
 *
 * One definition, agreed by the 1 unit that declares it: net_prg.c (DIE 0x8A0EB).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_ranking_htoh_list_work *`.
 *
 * declared by: net_prg.c (DIE 0x8A0EB)
 */
#ifndef DDR_types__nsv_ranking_htoh_list_work_H
#define DDR_types__nsv_ranking_htoh_list_work_H

struct _nsv_ranking_htoh_param_w;

#include "types/_nsv_ranking_htoh_param_w.h"

struct _nsv_ranking_htoh_list_work {   // size 0x1454
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ struct _nsv_ranking_htoh_param_w list[100];  // 0x1450
};

#endif /* DDR_types__nsv_ranking_htoh_list_work_H */
