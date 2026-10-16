/* struct pp_ipcp_opts -- 6 members, size 0x18, layout ebd3905210d5.
 *
 * One definition, agreed by the 2 units that declare it: tcpint.c (DIE 0x1F99FC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct pp_ipcp_opts *`.
 *
 * declared by: tcpint.c (DIE 0x1F99FC), net_dnas_ave.c (DIE 0x3BA7A3)
 */
#ifndef DDR_types_pp_ipcp_opts_H
#define DDR_types_pp_ipcp_opts_H

struct pp_ipcp_opts {   // size 0x18
    /* 0x000 */ unsigned int his_ip;                  // 0x4
    /* 0x004 */ unsigned int my_ip;                   // 0x4
    /* 0x008 */ unsigned int his_dns1;                // 0x4
    /* 0x00C */ unsigned int his_dns2;                // 0x4
    /* 0x010 */ unsigned int my_dns1;                 // 0x4
    /* 0x014 */ unsigned int my_dns2;                 // 0x4
};

#endif /* DDR_types_pp_ipcp_opts_H */
