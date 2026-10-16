/* struct _tag_cRecOni -- 23 members, size 0x12C, layout 76952c3cbf5d.
 *
 * One definition, agreed by the 1 unit that declares it: reconi.c (DIE 0x23208).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecOni *`.
 *
 * declared by: reconi.c (DIE 0x23208)
 */
#ifndef DDR_types__tag_cRecOni_H
#define DDR_types__tag_cRecOni_H

struct _tag_cRecOniData;
struct _tag_cRecOniRecord1;

#include "types/_tag_cRecOniData.h"
#include "types/_tag_cRecOniRecord1.h"

struct _tag_cRecOni {   // size 0x12C
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int fade_count;                       // 0x4
    /* 0x00C */ int fade_mode;                        // 0x4
    /* 0x010 */ int course_num;                       // 0x4
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
    /* 0x03C */ struct _tag_cRecOniData table_data[8];  // 0xC0
    /* 0x0FC */ int dir_arrow_count[2];               // 0x8
    /* 0x104 */ int dir_arrow_step[2];                // 0x8
    /* 0x10C */ int dir_arrow_bright[2];              // 0x8
    /* 0x114 */ struct _tag_cRecOniRecord1 *del_data;  // 0x4
    /* 0x118 */ int del_entry_mode;                   // 0x4
    /* 0x11C */ int ope_step[2];                      // 0x8
    /* 0x124 */ int ope_bright[2];                    // 0x8
};

#endif /* DDR_types__tag_cRecOni_H */
