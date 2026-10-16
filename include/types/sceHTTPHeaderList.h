/* struct sceHTTPHeaderList -- 4 members, size 0x10, layout a005dfbe21e6.
 *
 * One definition, agreed by the 1 unit that declares it: ddrex2_usa_id.c (DIE 0x396D35).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceHTTPHeaderList *`.
 *
 * declared by: ddrex2_usa_id.c (DIE 0x396D35)
 */
#ifndef DDR_types_sceHTTPHeaderList_H
#define DDR_types_sceHTTPHeaderList_H

struct sceHTTPHeaderList {   // size 0x10
    /* 0x000 */ struct sceHTTPHeaderList *forw;       // 0x4
    /* 0x004 */ struct sceHTTPHeaderList *back;       // 0x4
    /* 0x008 */ char *name;                           // 0x4
    /* 0x00C */ char *value;                          // 0x4
};

#endif /* DDR_types_sceHTTPHeaderList_H */
