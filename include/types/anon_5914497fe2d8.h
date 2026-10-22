/* anonymous struct -- 2 members, size 0x1048, layout 5914497fe2d8.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_5914497fe2d8` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: net.c (DIE 0x6F151)
 */
#ifndef DDR_types_anon_5914497fe2d8_H
#define DDR_types_anon_5914497fe2d8_H

typedef struct {   // size 0x1048
    /* 0x000 */ unsigned int P[18];                   // 0x48
    /* 0x048 */ unsigned int S[4][256];               // 0x1000
} anon_5914497fe2d8;

#endif /* DDR_types_anon_5914497fe2d8_H */
