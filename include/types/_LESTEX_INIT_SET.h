/* struct _LESTEX_INIT_SET -- 6 members, size 0x20, layout ae667e131fbd.
 *
 * One definition, agreed by the 6 units that declare it: les_sel_lv.c (DIE 0x687).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _LESTEX_INIT_SET *`.
 *
 * declared by: les_sel_lv.c (DIE 0x687), les.c (DIE 0x3F53), les_sel_sec.c (DIE 0x9CD2), les_play.c (DIE 0x10291), kn_ldisp.c (DIE 0x1E686), les_aid.c (DIE 0x7992E)
 */
#ifndef DDR_types__LESTEX_INIT_SET_H
#define DDR_types__LESTEX_INIT_SET_H

struct _LESTEX_INIT_SET {   // size 0x20
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int flag;                             // 0x4
    /* 0x014 */ int id[3];                            // 0xC
};

#endif /* DDR_types__LESTEX_INIT_SET_H */
