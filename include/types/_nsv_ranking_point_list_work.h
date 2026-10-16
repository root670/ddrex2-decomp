/* struct _nsv_ranking_point_list_work -- 2 members, size 0xE14, layout 6d5b51fe15b6.
 *
 * One definition, agreed by the 1 unit that declares it: net_prg.c (DIE 0x85F0E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _nsv_ranking_point_list_work *`.
 *
 * declared by: net_prg.c (DIE 0x85F0E)
 */
#ifndef DDR_types__nsv_ranking_point_list_work_H
#define DDR_types__nsv_ranking_point_list_work_H

struct _nsv_ranking_point_param_w;

#include "types/_nsv_ranking_point_param_w.h"

struct _nsv_ranking_point_list_work {   // size 0xE14
    /* 0x000 */ int count;                            // 0x4
    /* 0x004 */ struct _nsv_ranking_point_param_w list[100];  // 0xE10
};

#endif /* DDR_types__nsv_ranking_point_list_work_H */
