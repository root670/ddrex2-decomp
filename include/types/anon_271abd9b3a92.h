/* anonymous struct -- 5 members, size 0x28, layout 271abd9b3a92.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_271abd9b3a92` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: les_play.c (DIE 0x37AAB5)
 */
#ifndef DDR_types_anon_271abd9b3a92_H
#define DDR_types_anon_271abd9b3a92_H

#include "types/anon_91122355aec6.h"

typedef struct {   // size 0x28
    /* 0x000 */ unsigned long length;                 // 0x8
    /* 0x008 */ anon_91122355aec6 *org;               // 0x4
    /* 0x00C */ // 0x4 bytes padding
    /* 0x010 */ unsigned long offset;                 // 0x8
    /* 0x018 */ unsigned long point;                  // 0x8
    /* 0x020 */ anon_91122355aec6 *tag;               // 0x4
    /* 0x024 */ // 0x4 bytes padding
} anon_271abd9b3a92;

#endif /* DDR_types_anon_271abd9b3a92_H */
