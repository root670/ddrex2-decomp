/* struct _tag_cNetRouter -- 7 members, size 0x2C, layout 65dbf8e9f4df.
 *
 * One definition, agreed by the 1 unit that declares it: net_router_main.c (DIE 0x3C0D7B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetRouter *`.
 *
 * declared by: net_router_main.c (DIE 0x3C0D7B)
 */
#ifndef DDR_types__tag_cNetRouter_H
#define DDR_types__tag_cNetRouter_H

struct _NETWORK_W;
struct _tag_cUpnp;

#include "types/_NETWORK_W.h"
#include "types/_tag_cUpnp.h"

struct _tag_cNetRouter {   // size 0x2C
    /* 0x000 */ struct _NETWORK_W *ntw;               // 0x4
    /* 0x004 */ int step;                             // 0x4
    /* 0x008 */ int step1;                            // 0x4
    /* 0x00C */ int next_step;                        // 0x4
    /* 0x010 */ int msg_id;                           // 0x4
    /* 0x014 */ int warning_msg_id;                   // 0x4
    /* 0x018 */ struct _tag_cUpnp upnp;               // 0x14
};

#endif /* DDR_types__tag_cNetRouter_H */
