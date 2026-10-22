/* anonymous struct -- 4 members, size 0x10, layout caea742522ec.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_caea742522ec` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x20F4E)
 */
#ifndef DDR_types_anon_caea742522ec_H
#define DDR_types_anon_caea742522ec_H

#include "types/anon_c3e91c424de2.h"

typedef struct {   // size 0x10
    /* 0x000 */ char magic[2];                        // 0x2
    /* 0x002 */ short nbmdt;                          // 0x2
    /* 0x004 */ int reserve;                          // 0x4
    /* 0x008 */ anon_c3e91c424de2 motion[1];          // 0x8
} anon_caea742522ec;

#endif /* DDR_types_anon_caea742522ec_H */
