/* anonymous struct -- 4 members, size 0x10, layout 67489868bb1e.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_67489868bb1e` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x2159A)
 */
#ifndef DDR_types_anon_67489868bb1e_H
#define DDR_types_anon_67489868bb1e_H

typedef struct {   // size 0x10
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float z;                              // 0x4
    /* 0x00C */ unsigned int disp : 1;                // bits 0..0
} anon_67489868bb1e;

#endif /* DDR_types_anon_67489868bb1e_H */
