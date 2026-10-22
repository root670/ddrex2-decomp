/* anonymous struct -- 4 members, size 0x184, layout 5e4dacf47895.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_5e4dacf47895` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x5C7C)
 */
#ifndef DDR_types_anon_5e4dacf47895_H
#define DDR_types_anon_5e4dacf47895_H

#include "types/anon_99bb0cdc4bbf.h"

typedef struct {   // size 0x184
    /* 0x000 */ anon_99bb0cdc4bbf line_a[8];          // 0x80
    /* 0x080 */ anon_99bb0cdc4bbf line_b[8];          // 0x80
    /* 0x100 */ anon_99bb0cdc4bbf line_c[8];          // 0x80
    /* 0x180 */ int num;                              // 0x4
} anon_5e4dacf47895;

#endif /* DDR_types_anon_5e4dacf47895_H */
