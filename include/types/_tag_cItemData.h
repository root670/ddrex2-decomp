/* struct _tag_cItemData -- 3 members, size 0xC, layout fa3a389cf1c7.
 *
 * One definition, agreed by the 2 units that declare it: optlang.c (DIE 0x60E91).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cItemData *`.
 *
 * declared by: optlang.c (DIE 0x60E91), optdoll.c (DIE 0x949BF)
 */
#ifndef DDR_types__tag_cItemData_H
#define DDR_types__tag_cItemData_H

struct _tag_cItemData {   // size 0xC
    /* 0x000 */ int (*GetBoolExist)();                // 0x4
    /* 0x004 */ int (*GetNew)();                      // 0x4
    /* 0x008 */ char *name;                           // 0x4
};

#endif /* DDR_types__tag_cItemData_H */
