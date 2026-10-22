/* anonymous struct -- 4 members, size 0x10, layout 1fa6d74458f3.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_1fa6d74458f3` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: workout.c (DIE 0xACE9F)
 */
#ifndef DDR_types_anon_1fa6d74458f3_H
#define DDR_types_anon_1fa6d74458f3_H

typedef struct {   // size 0x10
    /* 0x000 */ int (*appr)(void *);                  // 0x4
    /* 0x004 */ int (*exec)(void *);                  // 0x4
    /* 0x008 */ int (*disap)(void *);                 // 0x4
    /* 0x00C */ int (*disp)(void *);                  // 0x4
} anon_1fa6d74458f3;

#endif /* DDR_types_anon_1fa6d74458f3_H */
