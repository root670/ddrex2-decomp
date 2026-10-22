/* anonymous struct -- 4 members, size 0x8, layout b14b78a0b5d3.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_b14b78a0b5d3` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 4 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: b_anime.c (DIE 0x13671), net_main.c (DIE 0x785BB), les_play.c (DIE 0x372465), les_sel_sec.c (DIE 0x3838EF)
 */
#ifndef DDR_types_anon_b14b78a0b5d3_H
#define DDR_types_anon_b14b78a0b5d3_H

typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_b14b78a0b5d3;

#endif /* DDR_types_anon_b14b78a0b5d3_H */
