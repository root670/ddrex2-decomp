/* struct _EDSS_PLAY_W -- 2 members, size 0x60, layout b76533438544.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x3A36).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSS_PLAY_W *`.
 *
 * declared by: les.c (DIE 0x3A36), les_play.c (DIE 0x11A11), reconi.c (DIE 0x216CE), onimode.c (DIE 0x2E5B9), recend.c (DIE 0x3A0A1), eds_select.c (DIE 0x3CFDB), eds_main.c (DIE 0x490EC), optscr.c (DIE 0x4D20F), eds_aid.c (DIE 0x57D90), eds_break.c (DIE 0x5C2C6), eds_record.c (DIE 0x5CA48), optdoll.c (DIE 0x96098), dexport.c (DIE 0x983DC), dinit.c (DIE 0x9CC00)
 */
#ifndef DDR_types__EDSS_PLAY_W_H
#define DDR_types__EDSS_PLAY_W_H

struct _EDSS_DATA_W;

#include "types/_EDSS_DATA_W.h"

struct _EDSS_PLAY_W {   // size 0x60
    /* 0x000 */ struct _EDSS_DATA_W p_single[3];      // 0x30
    /* 0x030 */ struct _EDSS_DATA_W p_double[3];      // 0x30
};

#endif /* DDR_types__EDSS_PLAY_W_H */
