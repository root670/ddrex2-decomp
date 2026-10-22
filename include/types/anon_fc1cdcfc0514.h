/* anonymous struct -- 4 members, size 0xC, layout fc1cdcfc0514.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_fc1cdcfc0514` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x205E8)
 */
#ifndef DDR_types_anon_fc1cdcfc0514_H
#define DDR_types_anon_fc1cdcfc0514_H

#include "types/anon_4a6281135e6d.h"

typedef struct {   // size 0xC
    /* 0x000 */ unsigned int size;                    // 0x4
    /* 0x004 */ unsigned short nbparts;               // 0x2
    /* 0x006 */ unsigned short nbframe;               // 0x2
    /* 0x008 */ anon_4a6281135e6d **offset;           // 0x4
} anon_fc1cdcfc0514;

#endif /* DDR_types_anon_fc1cdcfc0514_H */
