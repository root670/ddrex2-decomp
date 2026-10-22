/* anonymous struct -- 4 members, size 0x4, layout a52589d29f2d.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_a52589d29f2d` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: olmain.c (DIE 0x54550)
 */
#ifndef DDR_types_anon_a52589d29f2d_H
#define DDR_types_anon_a52589d29f2d_H

typedef struct {   // size 0x4
    /* 0x000 */ unsigned char trycount;               // 0x1
    /* 0x001 */ unsigned char spindlctrl;             // 0x1
    /* 0x002 */ unsigned char datapattern;            // 0x1
    /* 0x003 */ unsigned char pad;                    // 0x1
} anon_a52589d29f2d;

#endif /* DDR_types_anon_a52589d29f2d_H */
