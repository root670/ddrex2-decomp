/* struct _sif_client_data -- 7 members, size 0x28, layout 8f6822ce1a87.
 *
 * One definition, agreed by the 3 units that declare it: libstr3.c (DIE 0x5D187).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _sif_client_data *`.
 *
 * declared by: libstr3.c (DIE 0x5D187), tcpint.c (DIE 0x1F8F22), bsdsock.c (DIE 0x387335)
 */
#ifndef DDR_types__sif_client_data_H
#define DDR_types__sif_client_data_H

struct _sif_rpc_data;
struct _sif_serve_data;

#include "types/_sif_rpc_data.h"
#include "types/_sif_serve_data.h"

struct _sif_client_data {   // size 0x28
    /* 0x000 */ struct _sif_rpc_data rpcd;            // 0x10
    /* 0x010 */ unsigned int command;                 // 0x4
    /* 0x014 */ void *buff;                           // 0x4
    /* 0x018 */ void *gp;                             // 0x4
    /* 0x01C */ void (*func)(void *);                 // 0x4
    /* 0x020 */ void *para;                           // 0x4
    /* 0x024 */ struct _sif_serve_data *serve;        // 0x4
};

#endif /* DDR_types__sif_client_data_H */
