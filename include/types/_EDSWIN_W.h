/* struct _EDSWIN_W -- 18 members, size 0x48, layout 04b4e4dd9962.
 *
 * One definition, agreed by the 6 units that declare it: eds_select.c (DIE 0x40455).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSWIN_W *`.
 *
 * declared by: eds_select.c (DIE 0x40455), eds_main.c (DIE 0x4679A), eds_win.c (DIE 0x4E370), eds_aid.c (DIE 0x551FF), eds_break.c (DIE 0x5A751), eds_record.c (DIE 0x5E032)
 */
#ifndef DDR_types__EDSWIN_W_H
#define DDR_types__EDSWIN_W_H

struct _EDSTEX_INIT_SET;
struct _EDSTEX_W;

#include "types/_EDSTEX_INIT_SET.h"
#include "types/_EDSTEX_W.h"

struct _EDSWIN_W {   // size 0x48
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float sx;                             // 0x4
    /* 0x00C */ float sy;                             // 0x4
    /* 0x010 */ int w;                                // 0x4
    /* 0x014 */ int h;                                // 0x4
    /* 0x018 */ int sw;                               // 0x4
    /* 0x01C */ int sh;                               // 0x4
    /* 0x020 */ float waveY;                          // 0x4
    /* 0x024 */ unsigned int flag;                    // 0x4
    /* 0x028 */ unsigned char alpha;                  // 0x1
    /* 0x029 */ unsigned char salpha;                 // 0x1
    /* 0x02A */ char step;                            // 0x1
    /* 0x02B */ char s_step;                          // 0x1
    /* 0x02C */ unsigned char type;                   // 0x1
    /* 0x02D */ unsigned char tex_id;                 // 0x1
    /* 0x02E */ // 0x2 bytes padding
    /* 0x030 */ struct _EDSTEX_INIT_SET *def;         // 0x4
    /* 0x034 */ struct _EDSTEX_W *tex[5];             // 0x14
};

#endif /* DDR_types__EDSWIN_W_H */
