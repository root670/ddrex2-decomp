/* struct _COM_KEYBOARD_WORK -- 11 members, size 0x38, layout 1e2c4a376d51.
 *
 * One definition, agreed by the 5 units that declare it: net_prg.c (DIE 0x8C7F4).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _COM_KEYBOARD_WORK *`.
 *
 * declared by: net_prg.c (DIE 0x8C7F4), net_sys_new.c (DIE 0x15CD16), com_keyboard.c (DIE 0x199BFB), el_name.c (DIE 0x31AB74), net_auth_main.c (DIE 0x3A7CCA)
 */
#ifndef DDR_types__COM_KEYBOARD_WORK_H
#define DDR_types__COM_KEYBOARD_WORK_H

struct _COM_KEYBOARD_WORK {   // size 0x38
    /* 0x000 */ int board_id;                         // 0x4
    /* 0x004 */ int frame_id;                         // 0x4
    /* 0x008 */ int cur_id;                           // 0x4
    /* 0x00C */ int y;                                // 0x4
    /* 0x010 */ int z;                                // 0x4
    /* 0x014 */ int type;                             // 0x4
    /* 0x018 */ int cur_x;                            // 0x4
    /* 0x01C */ int cur_y;                            // 0x4
    /* 0x020 */ unsigned int flag;                    // 0x4
    /* 0x024 */ unsigned int ban_flag[4];             // 0x10
    /* 0x034 */ unsigned char alpha;                  // 0x1
    /* 0x035 */ // 0x3 bytes padding
};

#endif /* DDR_types__COM_KEYBOARD_WORK_H */
