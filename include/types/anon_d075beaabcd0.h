/* anonymous union -- 2 members, size 0x4, layout d075beaabcd0.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_d075beaabcd0` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x5891)
 */
#ifndef DDR_types_anon_d075beaabcd0_H
#define DDR_types_anon_d075beaabcd0_H

typedef union {   // size 0x4
    /* 0x000 */ int id;                               // 0x4
    /* 0x000 */ float fd;                             // 0x4
} anon_d075beaabcd0;

#endif /* DDR_types_anon_d075beaabcd0_H */
