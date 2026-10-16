/* struct sockaddr -- 2 members, size 0x10, layout e62070e61984.
 *
 * One definition, agreed by the 1 unit that declares it: bsdsock.c (DIE 0x387C33).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sockaddr *`.
 *
 * declared by: bsdsock.c (DIE 0x387C33)
 */
#ifndef DDR_types_sockaddr_H
#define DDR_types_sockaddr_H

struct sockaddr {   // size 0x10
    /* 0x000 */ unsigned short sa_family;             // 0x2
    /* 0x002 */ char sa_data[14];                     // 0xE
};

#endif /* DDR_types_sockaddr_H */
