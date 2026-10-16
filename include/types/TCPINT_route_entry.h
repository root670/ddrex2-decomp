/* struct TCPINT_route_entry -- 2 members, size 0x8, layout 6ef9b5741f4f.
 *
 * One definition, agreed by the 1 unit that declares it: tcpint.c (DIE 0x1F9849).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct TCPINT_route_entry *`.
 *
 * declared by: tcpint.c (DIE 0x1F9849)
 */
#ifndef DDR_types_TCPINT_route_entry_H
#define DDR_types_TCPINT_route_entry_H

struct TCPINT_route_entry {   // size 0x8
    /* 0x000 */ unsigned int dstaddr;                 // 0x4
    /* 0x004 */ unsigned int gtwayaddr;               // 0x4
};

#endif /* DDR_types_TCPINT_route_entry_H */
