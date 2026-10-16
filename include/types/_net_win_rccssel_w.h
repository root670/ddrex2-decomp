/* struct _net_win_rccssel_w -- 10 members, size 0x80, layout 92995b581e12.
 *
 * One definition, agreed by the 1 unit that declares it: net_win_rccssel.c (DIE 0x2A2BA9).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _net_win_rccssel_w *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: net_win_rccssel.c (DIE 0x2A2BA9)
 */
#ifndef DDR_types__net_win_rccssel_w_H
#define DDR_types__net_win_rccssel_w_H

struct _nsv_rc_table_param_work;

#include "types/_nsv_rc_table_param_work.h"

struct _net_win_rccssel_w {   // size 0x80
    /* 0x000 */ struct _nsv_rc_table_param_work *RcData;  // 0x4
    /* 0x004 */ int counter;                          // 0x4
    /* 0x008 */ int move_time[5];                     // 0x14
    /* 0x01C */ // 0x4 bytes padding if 16-byte aligned, else a member DWARF omits
    /* 0x020 */ struct {   // size 0x10
        /* 0x000 */ int x;                                // 0x4
        /* 0x004 */ int y;                                // 0x4
        /* 0x008 */ int w;                                // 0x4
        /* 0x00C */ int h;                                // 0x4
    } line_pos[5];
    /* 0x070 */ char line_disp_flag[5];               // 0x5
    /* 0x075 */ char line_step;                       // 0x1
    /* 0x076 */ char nm_page;                         // 0x1
    /* 0x077 */ // 0x1 bytes padding
    /* 0x078 */ int line_move_time;                   // 0x4
    /* 0x07C */ short line_start_point_y;             // 0x2
    /* 0x07E */ unsigned short status;                // 0x2
};

#endif /* DDR_types__net_win_rccssel_w_H */
