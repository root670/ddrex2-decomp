/* anonymous struct -- 4 members, size 0x10, layout fa86f3882d77.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_fa86f3882d77` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: les_sel_lv.c (DIE 0x37D16E)
 */
#ifndef DDR_types_anon_fa86f3882d77_H
#define DDR_types_anon_fa86f3882d77_H

typedef struct {   // size 0x10
    /* 0x000 */ float vx;                             // 0x4
    /* 0x004 */ float vy;                             // 0x4
    /* 0x008 */ float vz;                             // 0x4
    /* 0x00C */ float vw;                             // 0x4
} anon_fa86f3882d77;

#endif /* DDR_types_anon_fa86f3882d77_H */
