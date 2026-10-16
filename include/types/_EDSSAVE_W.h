/* struct _EDSSAVE_W -- 3 members, size 0x238, layout e31c5badf6ca.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x3EBF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSSAVE_W *`.
 *
 * declared by: les.c (DIE 0x3EBF), les_play.c (DIE 0x12156), reconi.c (DIE 0x22285), onimode.c (DIE 0x2E88B), recend.c (DIE 0x368FA), eds_select.c (DIE 0x3D670), eds_main.c (DIE 0x43BA3), optscr.c (DIE 0x4A3C6), eds_aid.c (DIE 0x5228E), eds_break.c (DIE 0x59707), eds_record.c (DIE 0x5CC3D), optdoll.c (DIE 0x93324), dexport.c (DIE 0x98599), dinit.c (DIE 0x9CDB2)
 */
#ifndef DDR_types__EDSSAVE_W_H
#define DDR_types__EDSSAVE_W_H

struct _EDSS_DATA_W;
struct _EDSS_PLAY_W;

#include "types/_EDSS_DATA_W.h"
#include "types/_EDSS_PLAY_W.h"

struct _EDSSAVE_W {   // size 0x238
    /* 0x000 */ struct _EDSS_PLAY_W reg[2];           // 0xC0
    /* 0x0C0 */ struct _EDSS_DATA_W max_point;        // 0x10
    /* 0x0D0 */ unsigned int PlayFlag[90];            // 0x168
};

#endif /* DDR_types__EDSSAVE_W_H */
