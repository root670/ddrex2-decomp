/* struct _sif_rpc_data -- 4 members, size 0x10, layout bb96b91488f3.
 *
 * One definition, agreed by the 3 units that declare it: libstr3.c (DIE 0x5DB68).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _sif_rpc_data *`.
 *
 * declared by: libstr3.c (DIE 0x5DB68), tcpint.c (DIE 0x1F86D5), bsdsock.c (DIE 0x387FE6)
 */
#ifndef DDR_types__sif_rpc_data_H
#define DDR_types__sif_rpc_data_H

struct _sif_rpc_data {   // size 0x10
    /* 0x000 */ void *paddr;                          // 0x4
    /* 0x004 */ unsigned int pid;                     // 0x4
    /* 0x008 */ int tid;                              // 0x4
    /* 0x00C */ unsigned int mode;                    // 0x4
};

#endif /* DDR_types__sif_rpc_data_H */
