/* anonymous union -- 3 members, size 0x4, layout 7e56caf1fdae.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_7e56caf1fdae` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: net.c (DIE 0x71726)
 */
#ifndef DDR_types_anon_7e56caf1fdae_H
#define DDR_types_anon_7e56caf1fdae_H

#include "types/anon_0bb59b81774d.h"
#include "types/anon_2f9ff101819f.h"

typedef union {   // size 0x4
    /* 0x000 */ anon_0bb59b81774d S_un_b;             // 0x4
    /* 0x000 */ anon_2f9ff101819f S_un_w;             // 0x4
    /* 0x000 */ unsigned int S_addr;                  // 0x4
} anon_7e56caf1fdae;

#endif /* DDR_types_anon_7e56caf1fdae_H */
