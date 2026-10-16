/* struct _tag_cNetDnasAve -- 17 members, size 0xD6C, layout 163f332c4411.
 *
 * One definition, agreed by the 1 unit that declares it: net_dnas_ave.c (DIE 0x3B9EC5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cNetDnasAve *`.
 *
 * declared by: net_dnas_ave.c (DIE 0x3B9EC5)
 */
#ifndef DDR_types__tag_cNetDnasAve_H
#define DDR_types__tag_cNetDnasAve_H

struct dginfo;
struct sceNetcnfifData;

#include "types/dginfo.h"
#include "types/sceNetcnfifData.h"

struct _tag_cNetDnasAve {   // size 0xD6C
    /* 0x000 */ int phase;                            // 0x4
    /* 0x004 */ int disp_phase;                       // 0x4
    /* 0x008 */ struct sceNetcnfifData *net_cnf;      // 0x4
    /* 0x00C */ int wait;                             // 0x4
    /* 0x010 */ unsigned int my_ipaddr;               // 0x4
    /* 0x014 */ unsigned int my_netmask;              // 0x4
    /* 0x018 */ unsigned int my_bcast;                // 0x4
    /* 0x01C */ unsigned int gateway;                 // 0x4
    /* 0x020 */ unsigned char domain[256];            // 0x100
    /* 0x120 */ unsigned int prsvr;                   // 0x4
    /* 0x124 */ unsigned int sesvr;                   // 0x4
    /* 0x128 */ int device_num;                       // 0x4
    /* 0x12C */ struct dginfo device_info[4];         // 0xC30
    /* 0xD5C */ int config_type;                      // 0x4
    /* 0xD60 */ int iftype;                           // 0x4
    /* 0xD64 */ int ether_init_timeout;               // 0x4
    /* 0xD68 */ int err_code;                         // 0x4
};

#endif /* DDR_types__tag_cNetDnasAve_H */
