/* anonymous struct -- 4 members, size 0x8, layout 00dccc0f5082.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_00dccc0f5082` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x20502)
 */
#ifndef DDR_types_anon_00dccc0f5082_H
#define DDR_types_anon_00dccc0f5082_H

typedef struct {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
} anon_00dccc0f5082;

#endif /* DDR_types_anon_00dccc0f5082_H */
