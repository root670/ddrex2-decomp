/* struct _tag_cRecmDelWnd -- 9 members, size 0x1C, layout 3ee76f94e600.
 *
 * One definition, agreed by the 1 unit that declares it: reconi.c (DIE 0x23FE1).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRecmDelWnd *`.
 *
 * declared by: reconi.c (DIE 0x23FE1)
 */
#ifndef DDR_types__tag_cRecmDelWnd_H
#define DDR_types__tag_cRecmDelWnd_H

struct _tag_cRecmDelWnd {   // size 0x1C
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
    /* 0x008 */ int pri;                              // 0x4
    /* 0x00C */ int bri;                              // 0x4
    /* 0x010 */ int msg_id;                           // 0x4
    /* 0x014 */ int draw_wnd;                         // 0x4
    /* 0x018 */ int draw_yn;                          // 0x4
};

#endif /* DDR_types__tag_cRecmDelWnd_H */
