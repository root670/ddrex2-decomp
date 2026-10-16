/* struct _CWS_WINS_W -- 11 members, size 0xA30, layout 1fc5452d839e.
 *
 * One definition, agreed by the 4 units that declare it: cws_obj.c (DIE 0xEF2C2).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _CWS_WINS_W *`.
 *
 * declared by: cws_obj.c (DIE 0xEF2C2), cws_str.c (DIE 0xF169D), cws_win.c (DIE 0xF490C), cws_wins.c (DIE 0xF6C16)
 */
#ifndef DDR_types__CWS_WINS_W_H
#define DDR_types__CWS_WINS_W_H

struct _CWS_OBJ;
struct _CWS_STR;
struct _CWS_WIN_W;

#include "types/_CWS_OBJ.h"
#include "types/_CWS_STR.h"
#include "types/_CWS_WIN_W.h"

struct _CWS_WINS_W {   // size 0xA30
    /* 0x000 */ unsigned int top_addr;                // 0x4
    /* 0x004 */ unsigned int end_addr;                // 0x4
    /* 0x008 */ int size;                             // 0x4
    /* 0x00C */ unsigned int status;                  // 0x4
    /* 0x010 */ int win_max;                          // 0x4
    /* 0x014 */ int str_max;                          // 0x4
    /* 0x018 */ int obj_max;                          // 0x4
    /* 0x01C */ int dam;                              // 0x4
    /* 0x020 */ struct _CWS_WIN_W *win[100];          // 0x190
    /* 0x1B0 */ struct _CWS_STR *str[224];            // 0x380
    /* 0x530 */ struct _CWS_OBJ *obj[320];            // 0x500
};

#endif /* DDR_types__CWS_WINS_W_H */
