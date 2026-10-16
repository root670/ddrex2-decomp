/* struct _sif_queue_data -- 6 members, size 0x18, layout 49da03f19a7c.
 *
 * One definition, agreed by the 3 units that declare it: libstr3.c (DIE 0x5DA17).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _sif_queue_data *`.
 *
 * declared by: libstr3.c (DIE 0x5DA17), tcpint.c (DIE 0x1F9BA3), bsdsock.c (DIE 0x3877E2)
 */
#ifndef DDR_types__sif_queue_data_H
#define DDR_types__sif_queue_data_H

struct _sif_serve_data;

#include "types/_sif_serve_data.h"

struct _sif_queue_data {   // size 0x18
    /* 0x000 */ int key;                              // 0x4
    /* 0x004 */ int active;                           // 0x4
    /* 0x008 */ struct _sif_serve_data *link;         // 0x4
    /* 0x00C */ struct _sif_serve_data *start;        // 0x4
    /* 0x010 */ struct _sif_serve_data *end;          // 0x4
    /* 0x014 */ struct _sif_queue_data *next;         // 0x4
};

#endif /* DDR_types__sif_queue_data_H */
