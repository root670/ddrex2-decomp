/* struct _COM_SCROLLBAR_WORK -- 11 members, size 0x28, layout 2429f7dee607.
 *
 * One definition, agreed by the 8 units that declare it: com_scrollbar.c (DIE 0x20AC2D).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _COM_SCROLLBAR_WORK *`.
 *
 * declared by: com_scrollbar.c (DIE 0x20AC2D), net_win_bar.c (DIE 0x20BB1B), adv_topmenu_obj.c (DIE 0x278771), adv_endless_obj.c (DIE 0x283C2C), infosel.c (DIE 0x32EA1F), info.c (DIE 0x3318B9), infoshow.c (DIE 0x340DD5), rec_co.c (DIE 0x476605)
 */
#ifndef DDR_types__COM_SCROLLBAR_WORK_H
#define DDR_types__COM_SCROLLBAR_WORK_H

struct _COM_SCROLLBAR_WORK {   // size 0x28
    /* 0x000 */ int tex_id;                           // 0x4
    /* 0x004 */ int x;                                // 0x4
    /* 0x008 */ int y;                                // 0x4
    /* 0x00C */ int h;                                // 0x4
    /* 0x010 */ int z;                                // 0x4
    /* 0x014 */ int c_max;                            // 0x4
    /* 0x018 */ int c_num;                            // 0x4
    /* 0x01C */ int c_now;                            // 0x4
    /* 0x020 */ unsigned int flag;                    // 0x4
    /* 0x024 */ unsigned char alpha;                  // 0x1
    /* 0x025 */ unsigned char bri;                    // 0x1
    /* 0x026 */ // 0x2 bytes padding
};

#endif /* DDR_types__COM_SCROLLBAR_WORK_H */
