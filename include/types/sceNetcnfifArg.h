/* struct sceNetcnfifArg -- 7 members, size 0x310, layout d6c57921bc1f.
 *
 * One definition, agreed by the 1 unit that declares it: net_cnf_main.c (DIE 0x3B620F).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceNetcnfifArg *`.
 *
 * declared by: net_cnf_main.c (DIE 0x3B620F)
 */
#ifndef DDR_types_sceNetcnfifArg_H
#define DDR_types_sceNetcnfifArg_H

struct sceNetcnfifArg {   // size 0x310
    /* 0x000 */ int data;                             // 0x4
    /* 0x004 */ int f_no_decode;                      // 0x4
    /* 0x008 */ int type;                             // 0x4
    /* 0x00C */ int addr;                             // 0x4
    /* 0x010 */ char fname[256];                      // 0x100
    /* 0x110 */ char usr_name[256];                   // 0x100
    /* 0x210 */ char new_usr_name[256];               // 0x100
};

#endif /* DDR_types_sceNetcnfifArg_H */
