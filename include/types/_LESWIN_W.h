/* struct _LESWIN_W -- 19 members, size 0x44, layout c63b19ad350c.
 *
 * One definition, agreed by the 6 units that declare it: les_sel_lv.c (DIE 0x1C01).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _LESWIN_W *`.
 *
 * declared by: les_sel_lv.c (DIE 0x1C01), les.c (DIE 0x5AC0), les_sel_sec.c (DIE 0x993B), les_play.c (DIE 0xE48A), kn_ldisp.c (DIE 0x1D8FD), les_aid.c (DIE 0x78EF8)
 */
#ifndef DDR_types__LESWIN_W_H
#define DDR_types__LESWIN_W_H

struct _LESTEX_INIT_SET;
struct _LESTEX_W;

#include "types/_LESTEX_INIT_SET.h"
#include "types/_LESTEX_W.h"

struct _LESWIN_W {   // size 0x44
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
    /* 0x02A */ // 0x2 bytes padding
    /* 0x02C */ int bri;                              // 0x4
    /* 0x030 */ char step;                            // 0x1
    /* 0x031 */ char s_step;                          // 0x1
    /* 0x032 */ unsigned char type;                   // 0x1
    /* 0x033 */ unsigned char tex_id;                 // 0x1
    /* 0x034 */ struct _LESTEX_INIT_SET *def;         // 0x4
    /* 0x038 */ struct _LESTEX_W *tex[3];             // 0xC
};

#endif /* DDR_types__LESWIN_W_H */
