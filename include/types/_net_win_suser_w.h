/* struct _net_win_suser_w -- 4 members, size 0x10, layout b191ff7a7d01.
 *
 * One definition, agreed by the 1 unit that declares it: net_win_suser.c (DIE 0x19F30C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _net_win_suser_w *`.
 *
 * declared by: net_win_suser.c (DIE 0x19F30C)
 */
#ifndef DDR_types__net_win_suser_w_H
#define DDR_types__net_win_suser_w_H

struct _NSV_USER_FILE_WORK;

#include "types/_NSV_USER_FILE_WORK.h"

struct _net_win_suser_w {   // size 0x10
    /* 0x000 */ int file_num;                         // 0x4
    /* 0x004 */ int board_status;                     // 0x4
    /* 0x008 */ int entry_flag;                       // 0x4
    /* 0x00C */ struct _NSV_USER_FILE_WORK *user_file;  // 0x4
};

#endif /* DDR_types__net_win_suser_w_H */
