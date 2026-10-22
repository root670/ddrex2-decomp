/* anonymous struct -- 3 members, size 0x8, layout f1abe6ba0ab9.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_f1abe6ba0ab9` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x2171D)
 */
#ifndef DDR_types_anon_f1abe6ba0ab9_H
#define DDR_types_anon_f1abe6ba0ab9_H

#include "types/anon_4c0903f15570.h"

typedef struct {   // size 0x8
    /* 0x000 */ unsigned char kind;                   // 0x1
    /* 0x001 */ unsigned char pad[3];                 // 0x3
    /* 0x004 */ anon_4c0903f15570 data;               // 0x4
} anon_f1abe6ba0ab9;

#endif /* DDR_types_anon_f1abe6ba0ab9_H */
