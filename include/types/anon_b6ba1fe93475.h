/* anonymous struct -- 2 members, size 0x20, layout b6ba1fe93475.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_b6ba1fe93475` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x21AC4)
 */
#ifndef DDR_types_anon_b6ba1fe93475_H
#define DDR_types_anon_b6ba1fe93475_H

typedef struct {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
} anon_b6ba1fe93475;

#endif /* DDR_types_anon_b6ba1fe93475_H */
