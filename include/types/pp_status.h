/* struct pp_status -- 7 members, size 0x2C, layout e2f5973db83e.
 *
 * One definition, agreed by the 2 units that declare it: tcpint.c (DIE 0x1F95CA).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct pp_status *`.
 *
 * declared by: tcpint.c (DIE 0x1F95CA), net_dnas_ave.c (DIE 0x3BA8E9)
 */
#ifndef DDR_types_pp_status_H
#define DDR_types_pp_status_H

struct pp_ipcp_opts;

#include "types/pp_ipcp_opts.h"

struct pp_status {   // size 0x2C
    /* 0x000 */ unsigned int his_ip;                  // 0x4
    /* 0x004 */ unsigned int my_ip;                   // 0x4
    /* 0x008 */ short phase;                          // 0x2
    /* 0x00A */ // 0x2 bytes padding
    /* 0x00C */ int baud_rate;                        // 0x4
    /* 0x010 */ short port_inuse;                     // 0x2
    /* 0x012 */ short last_error;                     // 0x2
    /* 0x014 */ struct pp_ipcp_opts ipcpOpts;         // 0x18
};

#endif /* DDR_types_pp_status_H */
