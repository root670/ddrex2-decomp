/* struct _tag_cInfoshow -- 32 members, size 0x94, layout fafa95c8f283.
 *
 * One definition, agreed by the 2 units that declare it: info.c (DIE 0x33445F).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cInfoshow *`.
 *
 * declared by: info.c (DIE 0x33445F), infoshow.c (DIE 0x346F50)
 */
#ifndef DDR_types__tag_cInfoshow_H
#define DDR_types__tag_cInfoshow_H

struct _tag_cIdm5DataHeader;
struct _tag_cInfoText;

#include "types/_tag_cIdm5DataHeader.h"
#include "types/_tag_cInfoText.h"

struct _tag_cInfoshow {   // size 0x94
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int next_step;                        // 0x4
    /* 0x008 */ int draw_flag;                        // 0x4
    /* 0x00C */ struct _tag_cInfoText *info_text;     // 0x4
    /* 0x010 */ struct _tag_cIdm5DataHeader *dheader;  // 0x4
    /* 0x014 */ int str_lnum;                         // 0x4
    /* 0x018 */ int str_y0;                           // 0x4
    /* 0x01C */ int str_dy;                           // 0x4
    /* 0x020 */ int str_y1;                           // 0x4
    /* 0x024 */ int str_y;                            // 0x4
    /* 0x028 */ int str_ys;                           // 0x4
    /* 0x02C */ int str_ye;                           // 0x4
    /* 0x030 */ float str_x;                          // 0x4
    /* 0x034 */ float str_sx;                         // 0x4
    /* 0x038 */ int str_a;                            // 0x4
    /* 0x03C */ int title_y;                          // 0x4
    /* 0x040 */ int base_x;                           // 0x4
    /* 0x044 */ int base_y;                           // 0x4
    /* 0x048 */ int move_count[2];                    // 0x8
    /* 0x050 */ int move_zure_count[2];               // 0x8
    /* 0x058 */ int move_total_count[2];              // 0x8
    /* 0x060 */ int move_mode[2];                     // 0x8
    /* 0x068 */ int move_counter[2];                  // 0x8
    /* 0x070 */ int move_control_flag;                // 0x4
    /* 0x074 */ int arrow_counter;                    // 0x4
    /* 0x078 */ int arrow_offs;                       // 0x4
    /* 0x07C */ int thumbnail_tex_id;                 // 0x4
    /* 0x080 */ int dancer_id;                        // 0x4
    /* 0x084 */ int scroll_dir;                       // 0x4
    /* 0x088 */ int alpha;                            // 0x4
    /* 0x08C */ int cur_dance_master;                 // 0x4
    /* 0x090 */ int cur_ending_list;                  // 0x4
};

#endif /* DDR_types__tag_cInfoshow_H */
