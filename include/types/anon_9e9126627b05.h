/* anonymous struct -- 3 members, size 0x28, layout 9e9126627b05.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_9e9126627b05` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x20CD8)
 */
#ifndef DDR_types_anon_9e9126627b05_H
#define DDR_types_anon_9e9126627b05_H

#include "types/anon_00dccc0f5082.h"
#include "types/anon_9e7dd0ae7596.h"

typedef struct {   // size 0x28
    /* 0x000 */ anon_9e7dd0ae7596 scale;              // 0x10
    /* 0x010 */ anon_00dccc0f5082 rotate;             // 0x8
    /* 0x018 */ anon_9e7dd0ae7596 trans;              // 0x10
} anon_9e9126627b05;

#endif /* DDR_types_anon_9e9126627b05_H */
