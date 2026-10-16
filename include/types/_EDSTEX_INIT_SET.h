/* struct _EDSTEX_INIT_SET -- 6 members, size 0x28, layout 670fedbdc474.
 *
 * One definition, agreed by the 6 units that declare it: eds_select.c (DIE 0x3FF8A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSTEX_INIT_SET *`.
 *
 * declared by: eds_select.c (DIE 0x3FF8A), eds_main.c (DIE 0x45F48), eds_win.c (DIE 0x4F32A), eds_aid.c (DIE 0x54989), eds_break.c (DIE 0x5A29D), eds_record.c (DIE 0x5DB34)
 */
#ifndef DDR_types__EDSTEX_INIT_SET_H
#define DDR_types__EDSTEX_INIT_SET_H

struct _EDSTEX_INIT_SET {   // size 0x28
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int flag;                             // 0x4
    /* 0x014 */ int id[5];                            // 0x14
};

#endif /* DDR_types__EDSTEX_INIT_SET_H */
