/* struct _LESWIN_W -- 20 members, size 0x4C, layout c2aaf7992b0b.
 *
 * One definition, agreed by the 6 units that declare it: kn_ldisp.c (DIE 0x35AA22).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _LESWIN_W *`.
 *
 * declared by: kn_ldisp.c (DIE 0x35AA22), les_aid.c (DIE 0x35F39A), les.c (DIE 0x367FF9), les_play.c (DIE 0x3775A7), les_sel_lv.c (DIE 0x37D209), les_sel_sec.c (DIE 0x383640)
 */
#ifndef DDR_types__LESWIN_W_H
#define DDR_types__LESWIN_W_H

struct _LESTEX_INIT_SET;
struct _LESTEX_W;

#include "types/_LESTEX_INIT_SET.h"
#include "types/_LESTEX_W.h"

struct _LESWIN_W {   // size 0x4C
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
    /* 0x028 */ int timer;                            // 0x4
    /* 0x02C */ unsigned char alpha;                  // 0x1
    /* 0x02D */ unsigned char salpha;                 // 0x1
    /* 0x02E */ // 0x2 bytes padding
    /* 0x030 */ int bri;                              // 0x4
    /* 0x034 */ char step;                            // 0x1
    /* 0x035 */ char s_step;                          // 0x1
    /* 0x036 */ unsigned char type;                   // 0x1
    /* 0x037 */ unsigned char tex_id;                 // 0x1
    /* 0x038 */ struct _LESTEX_INIT_SET *def;         // 0x4
    /* 0x03C */ struct _LESTEX_W *tex[4];             // 0x10
};

#endif /* DDR_types__LESWIN_W_H */
