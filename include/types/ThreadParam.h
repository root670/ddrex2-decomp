/* struct ThreadParam -- 12 members, size 0x30, layout 63a534b6f911.
 *
 * One definition, agreed by the 1 unit that declares it: libstr3.c (DIE 0x5D5E3).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct ThreadParam *`.
 *
 * declared by: libstr3.c (DIE 0x5D5E3)
 */
#ifndef DDR_types_ThreadParam_H
#define DDR_types_ThreadParam_H

struct ThreadParam {   // size 0x30
    /* 0x000 */ int status;                           // 0x4
    /* 0x004 */ void (*entry)(void *);                // 0x4
    /* 0x008 */ void *stack;                          // 0x4
    /* 0x00C */ int stackSize;                        // 0x4
    /* 0x010 */ void *gpReg;                          // 0x4
    /* 0x014 */ int initPriority;                     // 0x4
    /* 0x018 */ int currentPriority;                  // 0x4
    /* 0x01C */ unsigned int attr;                    // 0x4
    /* 0x020 */ unsigned int option;                  // 0x4
    /* 0x024 */ int waitType;                         // 0x4
    /* 0x028 */ int waitId;                           // 0x4
    /* 0x02C */ int wakeupCount;                      // 0x4
};

#endif /* DDR_types_ThreadParam_H */
