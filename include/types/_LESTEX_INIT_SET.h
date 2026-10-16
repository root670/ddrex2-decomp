/* struct _LESTEX_INIT_SET -- 6 members, size 0x24, layout 1a30c4964652.
 *
 * One definition, agreed by the 6 units that declare it: kn_ldisp.c (DIE 0x35B169).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _LESTEX_INIT_SET *`.
 *
 * declared by: kn_ldisp.c (DIE 0x35B169), les_aid.c (DIE 0x35F721), les.c (DIE 0x369916), les_play.c (DIE 0x37513B), les_sel_lv.c (DIE 0x37D907), les_sel_sec.c (DIE 0x38431E)
 */
#ifndef DDR_types__LESTEX_INIT_SET_H
#define DDR_types__LESTEX_INIT_SET_H

struct _LESTEX_INIT_SET {   // size 0x24
    /* 0x000 */ float x;                              // 0x4
    /* 0x004 */ float y;                              // 0x4
    /* 0x008 */ int w;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int flag;                             // 0x4
    /* 0x014 */ int id[4];                            // 0x10
};

#endif /* DDR_types__LESTEX_INIT_SET_H */
