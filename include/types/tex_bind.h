/* struct tex_bind -- 13 members, size 0x1C, layout 40c321e33033.
 *
 * One definition, agreed by the 2 units that declare it: sp_ending_d.c (DIE 0x3293E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct tex_bind *`.
 *
 * declared by: sp_ending_d.c (DIE 0x3293E), b_anime.c (DIE 0x6D7A8)
 */
#ifndef DDR_types_tex_bind_H
#define DDR_types_tex_bind_H

struct tex_bind {   // size 0x1C
    /* 0x000 */ short id;                             // 0x2
    /* 0x002 */ short type;                           // 0x2
    /* 0x004 */ short px;                             // 0x2
    /* 0x006 */ short py;                             // 0x2
    /* 0x008 */ short pw;                             // 0x2
    /* 0x00A */ short ph;                             // 0x2
    /* 0x00C */ short clut;                           // 0x2
    /* 0x00E */ unsigned char sub_x;                  // 0x1
    /* 0x00F */ unsigned char sub_y;                  // 0x1
    /* 0x010 */ char *name;                           // 0x4
    /* 0x014 */ short state;                          // 0x2
    /* 0x016 */ short cx;                             // 0x2
    /* 0x018 */ short cy;                             // 0x2
    /* 0x01A */ // 0x2 bytes padding
};

#endif /* DDR_types_tex_bind_H */
