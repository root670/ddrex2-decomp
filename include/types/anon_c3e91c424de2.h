/* anonymous struct -- 2 members, size 0x8, layout c3e91c424de2.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_c3e91c424de2` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x21A58)
 */
#ifndef DDR_types_anon_c3e91c424de2_H
#define DDR_types_anon_c3e91c424de2_H

#include "types/anon_fc1cdcfc0514.h"

typedef struct {   // size 0x8
    /* 0x000 */ char *name;                           // 0x4
    /* 0x004 */ anon_fc1cdcfc0514 *offset;            // 0x4
} anon_c3e91c424de2;

#endif /* DDR_types_anon_c3e91c424de2_H */
