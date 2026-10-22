/* anonymous struct -- 4 members, size 0x10, layout 9e7dd0ae7596.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_9e7dd0ae7596` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x2029D)
 */
#ifndef DDR_types_anon_9e7dd0ae7596_H
#define DDR_types_anon_9e7dd0ae7596_H

typedef struct {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
} anon_9e7dd0ae7596;

#endif /* DDR_types_anon_9e7dd0ae7596_H */
