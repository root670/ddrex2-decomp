/* anonymous struct -- 15 members, size 0x18, layout 09669fc426c8.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_09669fc426c8` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: infosel.c (DIE 0x32F71F)
 */
#ifndef DDR_types_anon_09669fc426c8_H
#define DDR_types_anon_09669fc426c8_H

typedef struct {   // size 0x18
    /* 0x000 */ unsigned long arrow_clut_ct;          // 0x8
    /* 0x008 */ short ny_music_num;                   // 0x2
    /* 0x00A */ short scroll_ct;                      // 0x2
    /* 0x00C */ unsigned char scroll_spd;             // 0x1
    /* 0x00D */ unsigned char special_bar;            // 0x1
    /* 0x00E */ unsigned char adjust_bar;             // 0x1
    /* 0x00F */ unsigned char bar_start;              // 0x1
    /* 0x010 */ unsigned char bar_end;                // 0x1
    /* 0x011 */ unsigned char bar_max;                // 0x1
    /* 0x012 */ unsigned char c_bar_max;              // 0x1
    /* 0x013 */ unsigned char c_bar_adjust;           // 0x1
    /* 0x014 */ unsigned char train_alpha0;           // 0x1
    /* 0x015 */ unsigned char player;                 // 0x1
    /* 0x016 */ unsigned char level;                  // 0x1
    /* 0x017 */ unsigned char dummy;                  // 0x1
} anon_09669fc426c8;

#endif /* DDR_types_anon_09669fc426c8_H */
