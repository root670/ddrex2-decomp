/* anonymous struct -- 11 members, size 0x1300, layout 3de85bd4740a.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_3de85bd4740a` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x7ED0)
 */
#ifndef DDR_types_anon_3de85bd4740a_H
#define DDR_types_anon_3de85bd4740a_H

#include "types/anon_70651db20a98.h"

typedef struct {   // size 0x1300
    /* 0x000 */ unsigned char evboot[24];             // 0x18
    /* 0x018 */ unsigned char is_savedata;            // 0x1
    /* 0x019 */ signed char max_area;                 // 0x1
    /* 0x01A */ signed char disp_type;                // 0x1
    /* 0x01B */ char pading;                          // 0x1
    /* 0x01C */ unsigned char dancer_use_cnt[24];     // 0x18
    /* 0x034 */ int cur_cursor;                       // 0x4
    /* 0x038 */ unsigned int all_clear_count;         // 0x4
    /* 0x03C */ unsigned int all_play_time;           // 0x4
    /* 0x040 */ int route[200];                       // 0x320
    /* 0x360 */ anon_70651db20a98 subject[200];       // 0xFA0
} anon_3de85bd4740a;

#endif /* DDR_types_anon_3de85bd4740a_H */
