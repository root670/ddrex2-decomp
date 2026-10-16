/* struct _EDSBOX_W -- 11 members, size 0x98, layout 0fa5e0ec44a1.
 *
 * One definition, agreed by the 3 units that declare it: eds_select.c (DIE 0x41910).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSBOX_W *`.
 *
 * declared by: eds_select.c (DIE 0x41910), eds_record.c (DIE 0x5EB73), eds_box.c (DIE 0x62885)
 */
#ifndef DDR_types__EDSBOX_W_H
#define DDR_types__EDSBOX_W_H

struct _EDSBOXPOINT_W;

#include "types/_EDSBOXPOINT_W.h"

struct _EDSBOX_W {   // size 0x98
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ float sx;                             // 0x4
    /* 0x00C */ float sy;                             // 0x4
    /* 0x010 */ struct _EDSBOXPOINT_W p[4];           // 0x40
    /* 0x050 */ struct _EDSBOXPOINT_W s[4];           // 0x40
    /* 0x090 */ unsigned int flag;                    // 0x4
    /* 0x094 */ char col;                             // 0x1
    /* 0x095 */ char step;                            // 0x1
    /* 0x096 */ char s_step;                          // 0x1
    /* 0x097 */ unsigned char type;                   // 0x1
};

#endif /* DDR_types__EDSBOX_W_H */
