/* anonymous struct -- 2 members, size 0x4, layout 4c0903f15570.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_4c0903f15570` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x203A1)
 */
#ifndef DDR_types_anon_4c0903f15570_H
#define DDR_types_anon_4c0903f15570_H

#include "types/anon_cd7e314f3c82.h"

typedef struct {   // size 0x4
    /* 0x000 */ unsigned short shift_bit;             // 0x2
    /* 0x002 */ anon_cd7e314f3c82 tbl[1];             // 0x2
} anon_4c0903f15570;

#endif /* DDR_types_anon_4c0903f15570_H */
