/* struct SemaParam -- 6 members, size 0x18, layout 19968c04fa4f.
 *
 * One definition, agreed by the 2 units that declare it: libstr3.c (DIE 0x5D85F).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct SemaParam *`.
 *
 * declared by: libstr3.c (DIE 0x5D85F), bsdsock.c (DIE 0x3875CF)
 */
#ifndef DDR_types_SemaParam_H
#define DDR_types_SemaParam_H

struct SemaParam {   // size 0x18
    /* 0x000 */ int currentCount;                     // 0x4
    /* 0x004 */ int maxCount;                         // 0x4
    /* 0x008 */ int initCount;                        // 0x4
    /* 0x00C */ int numWaitThreads;                   // 0x4
    /* 0x010 */ unsigned int attr;                    // 0x4
    /* 0x014 */ unsigned int option;                  // 0x4
};

#endif /* DDR_types_SemaParam_H */
