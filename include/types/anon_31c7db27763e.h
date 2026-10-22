/* anonymous struct -- 5 members, size 0x24, layout 31c7db27763e.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_31c7db27763e` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 2 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: sys_demo.c (DIE 0x621), olmain.c (DIE 0x54603)
 */
#ifndef DDR_types_anon_31c7db27763e_H
#define DDR_types_anon_31c7db27763e_H

typedef struct {   // size 0x24
    /* 0x000 */ unsigned int lsn;                     // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
    /* 0x008 */ char name[16];                        // 0x10
    /* 0x018 */ unsigned char date[8];                // 0x8
    /* 0x020 */ unsigned int flag;                    // 0x4
} anon_31c7db27763e;

#endif /* DDR_types_anon_31c7db27763e_H */
