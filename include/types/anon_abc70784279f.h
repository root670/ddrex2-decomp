/* anonymous struct -- 9 members, size 0x12E0, layout abc70784279f.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_abc70784279f` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x823C)
 */
#ifndef DDR_types_anon_abc70784279f_H
#define DDR_types_anon_abc70784279f_H

#include "types/anon_70097740c207.h"

typedef struct {   // size 0x12E0
    /* 0x000 */ int weight;                           // 0x4
    /* 0x004 */ int lbs;                              // 0x4
    /* 0x008 */ int norm_type;                        // 0x4
    /* 0x00C */ int norm_time;                        // 0x4
    /* 0x010 */ int norm_calorie;                     // 0x4
    /* 0x014 */ int workout_step;                     // 0x4
    /* 0x018 */ int simultaneous_step;                // 0x4
    /* 0x01C */ anon_70097740c207 history[400];       // 0x12C0
    /* 0x12DC */ int check_sum_val;                   // 0x4
} anon_abc70784279f;

#endif /* DDR_types_anon_abc70784279f_H */
