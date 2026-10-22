/* anonymous struct -- 4 members, size 0x10, layout 11313902d7fa.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_11313902d7fa` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: net.c (DIE 0x6E948)
 */
#ifndef DDR_types_anon_11313902d7fa_H
#define DDR_types_anon_11313902d7fa_H

typedef struct {   // size 0x10
    /* 0x000 */ int rtv;                              // 0x4
    /* 0x004 */ int ip_addr;                          // 0x4
    /* 0x008 */ int netmask;                          // 0x4
    /* 0x00C */ int broadcast;                        // 0x4
} anon_11313902d7fa;

#endif /* DDR_types_anon_11313902d7fa_H */
