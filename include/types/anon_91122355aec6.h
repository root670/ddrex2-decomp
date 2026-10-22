/* anonymous struct -- 2 members, size 0x4, layout 91122355aec6.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_91122355aec6` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: les_play.c (DIE 0x37A26D)
 */
#ifndef DDR_types_anon_91122355aec6_H
#define DDR_types_anon_91122355aec6_H

typedef struct {   // size 0x4
    /* 0x000 */ unsigned int p : 24;                  // bits 0..23
    /* 0x003 */ unsigned char num : 8;                // bits 0..7
} anon_91122355aec6;

#endif /* DDR_types_anon_91122355aec6_H */
