/* anonymous struct -- 8 members, size 0x14, layout 70651db20a98.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_70651db20a98` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x5F89)
 */
#ifndef DDR_types_anon_70651db20a98_H
#define DDR_types_anon_70651db20a98_H

typedef struct {   // size 0x14
    /* 0x000 */ unsigned char cone_state[8];          // 0x8
    /* 0x008 */ unsigned char state;                  // 0x1
    /* 0x009 */ unsigned char perfect;                // 0x1
    /* 0x00A */ unsigned short play_count;            // 0x2
    /* 0x00C */ unsigned short play_time;             // 0x2
    /* 0x00E */ unsigned short clear_count;           // 0x2
    /* 0x010 */ unsigned short first_clear_count;     // 0x2
    /* 0x012 */ unsigned short first_clear_time;      // 0x2
} anon_70651db20a98;

#endif /* DDR_types_anon_70651db20a98_H */
