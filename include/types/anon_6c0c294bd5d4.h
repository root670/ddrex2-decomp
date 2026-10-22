/* anonymous struct -- 3 members, size 0x8, layout 6c0c294bd5d4.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_6c0c294bd5d4` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: olmain.c (DIE 0x547C6)
 */
#ifndef DDR_types_anon_6c0c294bd5d4_H
#define DDR_types_anon_6c0c294bd5d4_H

typedef struct {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
} anon_6c0c294bd5d4;

#endif /* DDR_types_anon_6c0c294bd5d4_H */
