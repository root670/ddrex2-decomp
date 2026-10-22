/* anonymous struct -- 2 members, size 0x4, layout 2f9ff101819f.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_2f9ff101819f` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: net.c (DIE 0x71E5B)
 */
#ifndef DDR_types_anon_2f9ff101819f_H
#define DDR_types_anon_2f9ff101819f_H

typedef struct {   // size 0x4
    /* 0x000 */ unsigned short s_w1;                  // 0x2
    /* 0x002 */ unsigned short s_w2;                  // 0x2
} anon_2f9ff101819f;

#endif /* DDR_types_anon_2f9ff101819f_H */
