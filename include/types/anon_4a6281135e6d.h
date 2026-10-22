/* anonymous struct -- 6 members, size 0xC, layout 4a6281135e6d.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_4a6281135e6d` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: dancer.c (DIE 0x21835)
 */
#ifndef DDR_types_anon_4a6281135e6d_H
#define DDR_types_anon_4a6281135e6d_H

#include "types/anon_f1abe6ba0ab9.h"

typedef struct {   // size 0xC
    /* 0x000 */ unsigned char id;                     // 0x1
    /* 0x001 */ unsigned char format;                 // 0x1
    /* 0x002 */ unsigned char hastrans;               // 0x1
    /* 0x003 */ unsigned char parent_id;              // 0x1
    /* 0x004 */ unsigned int nbwave;                  // 0x4
    /* 0x008 */ anon_f1abe6ba0ab9 **offset;           // 0x4
} anon_4a6281135e6d;

#endif /* DDR_types_anon_4a6281135e6d_H */
