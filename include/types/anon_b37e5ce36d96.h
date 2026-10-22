/* anonymous struct -- 10 members, size 0x2134, layout b37e5ce36d96.
 *
 * DWARF gives this type no name (`@anonN` is per-unit numbering), so the alias
 * `anon_b37e5ce36d96` is the oracle's own, derived from the layout digest: every header
 * that uses the layout names the same typedef, and a unit's block then holds
 * one DIE for it -- retail's own has one.
 *
 * 1 declarations share this layout, all structurally identical; the
 * definition comes from the first in `.debug` order.
 *
 * declared by: onimode.c (DIE 0x84DD)
 */
#ifndef DDR_types_anon_b37e5ce36d96_H
#define DDR_types_anon_b37e5ce36d96_H

struct oni_course;

#include "types/oni_course.h"
#include "types/anon_3ce61ec3c992.h"
#include "types/anon_4fe0465b5497.h"
#include "types/anon_abc70784279f.h"

typedef struct {   // size 0x2134
    /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
    /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
    /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
    /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
    /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
    /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
    /* 0x004 */ anon_3ce61ec3c992 userpass;           // 0x4
    /* 0x008 */ anon_abc70784279f pwork;              // 0x12E0
    /* 0x12E8 */ anon_4fe0465b5497 workout_calorie_record;  // 0xD40
    /* 0x2028 */ struct oni_course program_order;     // 0x10C
} anon_b37e5ce36d96;

#endif /* DDR_types_anon_b37e5ce36d96_H */
