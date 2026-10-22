/* anonymous struct -- 5 members, size 0x14, layout 424e530946aa.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_424e530946aa` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x893F)
 */
#ifndef DDR_types_anon_424e530946aa_H
#define DDR_types_anon_424e530946aa_H

typedef struct {   // size 0x14
    /* 0x000 */ int state;                            // 0x4
    /* 0x004 */ int music_count;                      // 0x4
    /* 0x008 */ int dir;                              // 0x4
    /* 0x00C */ int effect_count;                     // 0x4
    /* 0x010 */ int id;                               // 0x4
} anon_424e530946aa;

#endif /* DDR_types_anon_424e530946aa_H */
