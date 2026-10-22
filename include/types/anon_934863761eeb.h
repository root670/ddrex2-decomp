/* anonymous struct -- 5 members, size 0x14, layout 934863761eeb.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_934863761eeb` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x211DB)
 */
#ifndef DDR_types_anon_934863761eeb_H
#define DDR_types_anon_934863761eeb_H

struct _GsCOORDINATE2;

#include "types/_GsCOORDINATE2.h"

typedef struct {   // size 0x14
    /* 0x000 */ unsigned int attribute;               // 0x4
    /* 0x004 */ struct _GsCOORDINATE2 *coord2;        // 0x4
    /* 0x008 */ unsigned int *tmd;                    // 0x4
    /* 0x00C */ unsigned int *packet;                 // 0x4
    /* 0x010 */ unsigned int id;                      // 0x4
} anon_934863761eeb;

#endif /* DDR_types_anon_934863761eeb_H */
