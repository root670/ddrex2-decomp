/* anonymous struct -- 5 members, size 0xC, layout 70097740c207.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_70097740c207` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x629F)
 */
#ifndef DDR_types_anon_70097740c207_H
#define DDR_types_anon_70097740c207_H

typedef struct {   // size 0xC
    /* 0x000 */ int date;                             // 0x4
    /* 0x004 */ unsigned int weight : 12;             // bits 0..11
    /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
    /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
    /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
} anon_70097740c207;

#endif /* DDR_types_anon_70097740c207_H */
