/* anonymous struct -- 7 members, size 0x10, layout 99bb0cdc4bbf.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_99bb0cdc4bbf` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x5D50)
 */
#ifndef DDR_types_anon_99bb0cdc4bbf_H
#define DDR_types_anon_99bb0cdc4bbf_H

#include "types/anon_d075beaabcd0.h"

typedef struct {   // size 0x10
    /* 0x000 */ anon_d075beaabcd0 x0;                 // 0x4
    /* 0x004 */ anon_d075beaabcd0 y0;                 // 0x4
    /* 0x008 */ unsigned int z0;                      // 0x4
    /* 0x00C */ unsigned char r0;                     // 0x1
    /* 0x00D */ unsigned char g0;                     // 0x1
    /* 0x00E */ unsigned char b0;                     // 0x1
    /* 0x00F */ unsigned char a0;                     // 0x1
} anon_99bb0cdc4bbf;

#endif /* DDR_types_anon_99bb0cdc4bbf_H */
