/* struct dginfo -- 6 members, size 0x30C, layout 00ac0ab589aa.
 *
 * One definition, agreed by the 2 units that declare it: tcpint.c (DIE 0x1F8781).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct dginfo *`.
 *
 * declared by: tcpint.c (DIE 0x1F8781), net_dnas_ave.c (DIE 0x3BAA0D)
 */
#ifndef DDR_types_dginfo_H
#define DDR_types_dginfo_H

struct dginfo {   // size 0x30C
    /* 0x000 */ int uid;                              // 0x4
    /* 0x004 */ int bustype;                          // 0x4
    /* 0x008 */ int iftype;                           // 0x4
    /* 0x00C */ unsigned char vendor[256];            // 0x100
    /* 0x10C */ unsigned char product[256];           // 0x100
    /* 0x20C */ unsigned char module[256];            // 0x100
};

#endif /* DDR_types_dginfo_H */
