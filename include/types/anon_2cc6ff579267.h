/* anonymous struct -- 6 members, size 0x14, layout 2cc6ff579267.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_2cc6ff579267` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: les_sel_sec.c (DIE 0x385202)
 */
#ifndef DDR_types_anon_2cc6ff579267_H
#define DDR_types_anon_2cc6ff579267_H

#include "types/anon_b14b78a0b5d3.h"

typedef struct {   // size 0x14
    /* 0x000 */ unsigned char *msg;                   // 0x4
    /* 0x004 */ anon_b14b78a0b5d3 *win;               // 0x4
    /* 0x008 */ short msg_num;                        // 0x2
    /* 0x00A */ short font_size;                      // 0x2
    /* 0x00C */ int ot;                               // 0x4
    /* 0x010 */ int bright;                           // 0x4
} anon_2cc6ff579267;

#endif /* DDR_types_anon_2cc6ff579267_H */
