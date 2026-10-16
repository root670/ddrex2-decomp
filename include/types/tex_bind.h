/* struct tex_bind -- 13 members, size 0x1C, layout 40c321e33033.
 *
 * One definition, agreed by the 27 units that declare it: b_anime.c (DIE 0x114BC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct tex_bind *`.
 *
 * declared by: b_anime.c (DIE 0x114BC), bk_disp.c (DIE 0xE8317), fp_eyetoy.c (DIE 0x10B5D3), fp_res.c (DIE 0x12E471), dmm_disp.c (DIE 0x18377F), co_diap.c (DIE 0x1BA765), fp_msel_obj.c (DIE 0x1D5128), co_qmenu.c (DIE 0x1E2135), fp_hand.c (DIE 0x202E18), shop_obj.c (DIE 0x21F693), shop_disp.c (DIE 0x22DE5B), dmm_mess.c (DIE 0x24219E), adv_endless_obj.c (DIE 0x284820), adv_nonstop_obj.c (DIE 0x299088), tra_menu.c (DIE 0x2A6F85), tra_res.c (DIE 0x2E3668), ed_menu.c (DIE 0x30DF60), ed_select.c (DIE 0x315A0C), el_name.c (DIE 0x31E5E9), el_disp_obj.c (DIE 0x32422B), info.c (DIE 0x335818), infoshow.c (DIE 0x342ADD), dmm_event_exe.c (DIE 0x3D9707), dmm_select.c (DIE 0x414B60), opt_win.c (DIE 0x44FC57), rec_co.c (DIE 0x474B37), rec_top.c (DIE 0x47A53D)
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
