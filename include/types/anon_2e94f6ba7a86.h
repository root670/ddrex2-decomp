/* anonymous struct -- 4 members, size 0x4, layout 2e94f6ba7a86.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_2e94f6ba7a86` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x51A6)
 */
#ifndef DDR_types_anon_2e94f6ba7a86_H
#define DDR_types_anon_2e94f6ba7a86_H

typedef struct {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
} anon_2e94f6ba7a86;

#endif /* DDR_types_anon_2e94f6ba7a86_H */
