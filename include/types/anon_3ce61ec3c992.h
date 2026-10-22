/* anonymous union -- 2 members, size 0x4, layout 3ce61ec3c992.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_3ce61ec3c992` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x80E6)
 */
#ifndef DDR_types_anon_3ce61ec3c992_H
#define DDR_types_anon_3ce61ec3c992_H

#include "types/anon_3ba9260b1b71.h"

typedef union {   // size 0x4
    /* 0x000 */ unsigned int ui;                      // 0x4
    /* 0x000 */ anon_3ba9260b1b71 s;                  // 0x4
} anon_3ce61ec3c992;

#endif /* DDR_types_anon_3ce61ec3c992_H */
