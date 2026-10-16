/* struct _sif_serve_data -- 17 members, size 0x44, layout 929b16b8961f.
 *
 * One definition, agreed by the 3 units that declare it: libstr3.c (DIE 0x5D354).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _sif_serve_data *`.
 *
 * declared by: libstr3.c (DIE 0x5D354), tcpint.c (DIE 0x1F91C1), bsdsock.c (DIE 0x3867D7)
 */
#ifndef DDR_types__sif_serve_data_H
#define DDR_types__sif_serve_data_H

struct _sif_client_data;
struct _sif_queue_data;

#include "types/_sif_client_data.h"
#include "types/_sif_queue_data.h"

struct _sif_serve_data {   // size 0x44
    /* 0x000 */ unsigned int command;                 // 0x4
    /* 0x004 */ void *(*func)(unsigned int, void *, int);  // 0x4
    /* 0x008 */ void *buff;                           // 0x4
    /* 0x00C */ int size;                             // 0x4
    /* 0x010 */ void *(*cfunc)(unsigned int, void *, int);  // 0x4
    /* 0x014 */ void *cbuff;                          // 0x4
    /* 0x018 */ int csize;                            // 0x4
    /* 0x01C */ struct _sif_client_data *client;      // 0x4
    /* 0x020 */ void *paddr;                          // 0x4
    /* 0x024 */ unsigned int fno;                     // 0x4
    /* 0x028 */ void *receive;                        // 0x4
    /* 0x02C */ int rsize;                            // 0x4
    /* 0x030 */ int rmode;                            // 0x4
    /* 0x034 */ unsigned int rid;                     // 0x4
    /* 0x038 */ struct _sif_serve_data *link;         // 0x4
    /* 0x03C */ struct _sif_serve_data *next;         // 0x4
    /* 0x040 */ struct _sif_queue_data *base;         // 0x4
};

#endif /* DDR_types__sif_serve_data_H */
