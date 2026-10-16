/* struct _EDSTEX_W -- 8 members, size 0x20, layout c41c245311c5.
 *
 * One definition, agreed by the 6 units that declare it: eds_select.c (DIE 0x406E6).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSTEX_W *`.
 *
 * declared by: eds_select.c (DIE 0x406E6), eds_main.c (DIE 0x46A54), eds_win.c (DIE 0x4F490), eds_aid.c (DIE 0x554B9), eds_break.c (DIE 0x5AA0B), eds_record.c (DIE 0x5E2C3)
 */
#ifndef DDR_types__EDSTEX_W_H
#define DDR_types__EDSTEX_W_H

struct _EDSTEX_W {   // size 0x20
    /* 0x000 */ int x;                                // 0x4
    /* 0x004 */ int y;                                // 0x4
    /* 0x008 */ int u;                                // 0x4
    /* 0x00C */ int v;                                // 0x4
    /* 0x010 */ int w;                                // 0x4
    /* 0x014 */ int h;                                // 0x4
    /* 0x018 */ int z;                                // 0x4
    /* 0x01C */ int tex_num;                          // 0x4
};

#endif /* DDR_types__EDSTEX_W_H */
