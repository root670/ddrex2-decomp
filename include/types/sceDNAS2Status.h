/* struct sceDNAS2Status -- 4 members, size 0x10, layout d2dd943945f2.
 *
 * One definition, agreed by the 2 units that declare it: net_dnas_mes_e.c (DIE 0x1AF292).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sceDNAS2Status *`.
 *
 * declared by: net_dnas_mes_e.c (DIE 0x1AF292), net_dnas_main.c (DIE 0x3BE911)
 */
#ifndef DDR_types_sceDNAS2Status_H
#define DDR_types_sceDNAS2Status_H

struct sceDNAS2Status {   // size 0x10
    /* 0x000 */ int code;                             // 0x4
    /* 0x004 */ int sub_code;                         // 0x4
    /* 0x008 */ int progress;                         // 0x4
    /* 0x00C */ void *optional;                       // 0x4
};

#endif /* DDR_types_sceDNAS2Status_H */
