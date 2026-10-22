/* anonymous struct -- 4 members, size 0xD40, layout 4fe0465b5497.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_4fe0465b5497` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x59A4)
 */
#ifndef DDR_types_anon_4fe0465b5497_H
#define DDR_types_anon_4fe0465b5497_H

typedef struct {   // size 0xD40
    /* 0x000 */ unsigned int program_calorie[24];     // 0x60
    /* 0x060 */ unsigned int program_play_count[24];  // 0x60
    /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
    /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
} anon_4fe0465b5497;

#endif /* DDR_types_anon_4fe0465b5497_H */
