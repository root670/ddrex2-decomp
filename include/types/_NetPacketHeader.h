/* struct _NetPacketHeader -- 5 members, size 0xC, layout 9a16cebc5348.
 *
 * One definition, agreed by the 1 unit that declares it: net_type.c (DIE 0x83071).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NetPacketHeader *`.
 *
 * declared by: net_type.c (DIE 0x83071)
 */
#ifndef DDR_types__NetPacketHeader_H
#define DDR_types__NetPacketHeader_H

struct _NetPacketHeader {   // size 0xC
    /* 0x000 */ int counter;                          // 0x4
    /* 0x004 */ short code;                           // 0x2
    /* 0x006 */ unsigned char type;                   // 0x1
    /* 0x007 */ unsigned char status;                 // 0x1
    /* 0x008 */ unsigned int data_size;               // 0x4
};

#endif /* DDR_types__NetPacketHeader_H */
