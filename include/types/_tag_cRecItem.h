/* struct _tag_cRecItem -- 6 members, size 0x30, layout 5ba4486c716e.
 *
 * One definition, agreed by the 2 units that declare it: reconi.c (DIE 0x2473A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecItem *`.
 *
 * declared by: reconi.c (DIE 0x2473A), recend.c (DIE 0x37E85)
 */
#ifndef DDR_types__tag_cRecItem_H
#define DDR_types__tag_cRecItem_H

struct _tag_cRecItem {   // size 0x30
    /* 0x000 */ int x[3];                             // 0xC
    /* 0x00C */ int y[3];                             // 0xC
    /* 0x018 */ int a[3];                             // 0xC
    /* 0x024 */ int bright;                           // 0x4
    /* 0x028 */ int col;                              // 0x4
    /* 0x02C */ unsigned char *str;                   // 0x4
};

#endif /* DDR_types__tag_cRecItem_H */
