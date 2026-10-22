/* anonymous struct -- 3 members, size 0x4, layout 9cfc060f8d1f.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_9cfc060f8d1f` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x8889)
 */
#ifndef DDR_types_anon_9cfc060f8d1f_H
#define DDR_types_anon_9cfc060f8d1f_H

typedef struct {   // size 0x4
    /* 0x000 */ unsigned char game_over;              // 0x1
    /* 0x001 */ unsigned char calorie_check;          // 0x1
    /* 0x002 */ unsigned char pad[2];                 // 0x2
} anon_9cfc060f8d1f;

#endif /* DDR_types_anon_9cfc060f8d1f_H */
