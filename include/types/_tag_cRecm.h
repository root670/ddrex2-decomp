/* struct _tag_cRecm -- 24 members, size 0x158, layout b73507a3d60d.
 *
 * One definition, agreed by the 1 unit that declares it: reconi.c (DIE 0x218D9).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecm *`.
 *
 * declared by: reconi.c (DIE 0x218D9)
 */
#ifndef DDR_types__tag_cRecm_H
#define DDR_types__tag_cRecm_H

struct _tag_cRecRecord1;
struct _tag_cRecmData;
struct _tag_cRecmDelWnd;

#include "types/_tag_cRecRecord1.h"
#include "types/_tag_cRecmData.h"
#include "types/_tag_cRecmDelWnd.h"

struct _tag_cRecm {   // size 0x158
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int fade_count;                       // 0x4
    /* 0x00C */ int fade_mode;                        // 0x4
    /* 0x010 */ int music_num;                        // 0x4
    /* 0x014 */ int cur_seg;                          // 0x4
    /* 0x018 */ int cur_off;                          // 0x4
    /* 0x01C */ int cur_col;                          // 0x4
    /* 0x020 */ int move_mode;                        // 0x4
    /* 0x024 */ int accelerate_flag;                  // 0x4
    /* 0x028 */ int cursor_count;                     // 0x4
    /* 0x02C */ int base_y;                           // 0x4
    /* 0x030 */ int level_count;                      // 0x4
    /* 0x034 */ int focus_bright_flag;                // 0x4
    /* 0x038 */ int focus_trg;                        // 0x4
    /* 0x03C */ struct _tag_cRecmData table_data[8];  // 0xC0
    /* 0x0FC */ int dir_arrow_count[2];               // 0x8
    /* 0x104 */ int dir_arrow_step[2];                // 0x8
    /* 0x10C */ int dir_arrow_bright[2];              // 0x8
    /* 0x114 */ struct _tag_cRecRecord1 *del_data;    // 0x4
    /* 0x118 */ int del_entry_mode;                   // 0x4
    /* 0x11C */ struct _tag_cRecmDelWnd wnd;          // 0x1C
    /* 0x138 */ int ope_step[4];                      // 0x10
    /* 0x148 */ int ope_bright[4];                    // 0x10
};

#endif /* DDR_types__tag_cRecm_H */
