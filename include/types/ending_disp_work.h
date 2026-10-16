/* struct ending_disp_work -- 11 members, size 0x2C, layout 6e37a3a7425f.
 *
 * One definition, agreed by the 1 unit that declares it: sp_ending_d.c (DIE 0x333C0).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct ending_disp_work *`.
 *
 * declared by: sp_ending_d.c (DIE 0x333C0)
 */
#ifndef DDR_types_ending_disp_work_H
#define DDR_types_ending_disp_work_H

struct file_position;

#include "types/file_position.h"

struct ending_disp_work {   // size 0x2C
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int movie_step;                       // 0x4
    /* 0x008 */ int movie_load_flag;                  // 0x4
    /* 0x00C */ int mv_tex_info_idx;                  // 0x4
    /* 0x010 */ int hn;                               // 0x4
    /* 0x014 */ int s_count_0;                        // 0x4
    /* 0x018 */ int s_count_1;                        // 0x4
    /* 0x01C */ int fn;                               // 0x4
    /* 0x020 */ short mov_w;                          // 0x2
    /* 0x022 */ short mov_h;                          // 0x2
    /* 0x024 */ struct file_position fpos;            // 0x8
};

#endif /* DDR_types_ending_disp_work_H */
