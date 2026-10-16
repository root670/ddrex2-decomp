/* struct _ADVANCED_MODE_W -- 16 members, size 0x13C, layout c77c11c20842.
 *
 * One definition, agreed by the 4 units that declare it: adv_topmenu_obj.c (DIE 0x274221).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ADVANCED_MODE_W *`.
 *
 * declared by: adv_topmenu_obj.c (DIE 0x274221), adv_endless_obj.c (DIE 0x28128D), adv_main.c (DIE 0x28D03D), adv_nonstop_obj.c (DIE 0x298965)
 */
#ifndef DDR_types__ADVANCED_MODE_W_H
#define DDR_types__ADVANCED_MODE_W_H

struct _ADVANCED_MODE_W {   // size 0x13C
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step_s;                           // 0x4
    /* 0x008 */ int mode;                             // 0x4
    /* 0x00C */ int timer;                            // 0x4
    /* 0x010 */ int advanced_load_flag;               // 0x4
    /* 0x014 */ int tex_group_no;                     // 0x4
    /* 0x018 */ int tex_cnt;                          // 0x4
    /* 0x01C */ int tex_id[64];                       // 0x100
    /* 0x11C */ void *top_item;                       // 0x4
    /* 0x120 */ void *btn;                            // 0x4
    /* 0x124 */ void *option;                         // 0x4
    /* 0x128 */ int btn_obj_id;                       // 0x4
    /* 0x12C */ short option_step;                    // 0x2
    /* 0x12E */ unsigned char option_data[12];        // 0xC
    /* 0x13A */ unsigned char cur_option;             // 0x1
    /* 0x13B */ unsigned char cur_option_max;         // 0x1
};

#endif /* DDR_types__ADVANCED_MODE_W_H */
