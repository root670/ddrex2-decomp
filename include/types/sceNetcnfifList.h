/* struct sceNetcnfifList -- 5 members, size 0x240, layout fef68e6e0b08.
 *
 * One definition, agreed by the 1 unit that declares it: net_cnf_main.c (DIE 0x3B6D3E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceNetcnfifList *`.
 *
 * declared by: net_cnf_main.c (DIE 0x3B6D3E)
 */
#ifndef DDR_types_sceNetcnfifList_H
#define DDR_types_sceNetcnfifList_H

struct sceNetcnfifList {   // size 0x240
    /* 0x000 */ int type;                             // 0x4
    /* 0x004 */ int stat;                             // 0x4
    /* 0x008 */ char sys_name[256];                   // 0x100
    /* 0x108 */ char usr_name[256];                   // 0x100
    /* 0x208 */ int padding[14];                      // 0x38
};

#endif /* DDR_types_sceNetcnfifList_H */
