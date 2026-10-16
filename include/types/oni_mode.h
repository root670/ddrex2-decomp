/* struct oni_mode -- 19 members, size 0xC, layout 2d15fdf396d4.
 *
 * One definition, agreed by the 60 units that declare it: onimode.c (DIE 0x3858).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct oni_mode *`.
 *
 * declared by: onimode.c (DIE 0x3858), oni_list.c (DIE 0xF061), dexport.c (DIE 0x3D3D2), dinit.c (DIE 0x41008), eye_system.c (DIE 0x4AD2F), info_data.c (DIE 0x5823D), fft_disp.c (DIE 0x5E71B), bk_disp_sub.c (DIE 0xE39D1), bk_disp.c (DIE 0xEA7CF), fp_msel.c (DIE 0x104B15), fp_chara.c (DIE 0x116FD6), fp_style.c (DIE 0x12C084), fp_res.c (DIE 0x137803), fp_opt.c (DIE 0x140F93), dmm_data.c (DIE 0x17AA0F), dmm_disp.c (DIE 0x183C90), dmm_init.c (DIE 0x18DE92), fp_doll.c (DIE 0x1B6BB4), fp_msel_obj.c (DIE 0x1D9F66), shop_init.c (DIE 0x210325), shop_list.c (DIE 0x215DCE), shop_obj.c (DIE 0x21FDCC), shop_disp.c (DIE 0x22FC5C), shop_func.c (DIE 0x238B3B), dmm_mc.c (DIE 0x24974A), rec_nor.c (DIE 0x2592BD), net_game_challenge.c (DIE 0x26C450), adv_endless_obj.c (DIE 0x27DA13), adv_main.c (DIE 0x28CB84), tra_main.c (DIE 0x2B56B3), dmm_func.c (DIE 0x2C6D27), tra_func.c (DIE 0x2D76CD), fp_qmenu.c (DIE 0x30020B), info.c (DIE 0x3371E0), infoshow.c (DIE 0x33FB6E), les.c (DIE 0x36A384), les_play.c (DIE 0x37A551), net_auth_main.c (DIE 0x3AB92D), net_cnf_main.c (DIE 0x3B646A), dmm_event.c (DIE 0x3C7AA8), dmm_event_cond.c (DIE 0x3D069E), dmm_event_exe.c (DIE 0x3DC3E9), dmm_play_course.c (DIE 0x3F7E4B), dmm_qmenu.c (DIE 0x3FF950), dmm_result.c (DIE 0x40C4DA), dmm_select.c (DIE 0x419A1C), dmm_style.c (DIE 0x42727F), opt_adjust.c (DIE 0x42ECFF), opt_doll.c (DIE 0x432E7A), opt_kconfig.c (DIE 0x437CA4), opt_mc.c (DIE 0x445CBE), opt_menu.c (DIE 0x44AF2C), workout_setting.c (DIE 0x4536C3), workout_usermanage.c (DIE 0x459AA1), workout_userlist.c (DIE 0x45D101), workout_useredit.c (DIE 0x464288), workout_usrrpass.c (DIE 0x467ED3), rec_hi.c (DIE 0x47FEC4), rec_end.c (DIE 0x487C8C), rec_hand.c (DIE 0x48D063)
 */
#ifndef DDR_types_oni_mode_H
#define DDR_types_oni_mode_H

struct oni_mode {   // size 0xC
    /* 0x000 */ unsigned int link_num;                // 0x4
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ unsigned char seq_transfer;           // 0x1
    /* 0x006 */ unsigned char sp_music;               // 0x1
    /* 0x007 */ unsigned char add_life;               // 0x1
    /* 0x008 */ unsigned int speed : 4;               // bits 0..3
    /* 0x008 */ unsigned int boost : 2;               // bits 4..5
    /* 0x008 */ unsigned int hidden : 3;              // bits 6..8
    /* 0x008 */ unsigned int turn : 2;                // bits 9..10
    /* 0x008 */ unsigned int thinout : 2;             // bits 11..12
    /* 0x008 */ unsigned int dark : 2;                // bits 13..14
    /* 0x008 */ unsigned int simultaneous : 3;        // bits 15..17
    /* 0x008 */ unsigned int scroll : 2;              // bits 18..19
    /* 0x008 */ unsigned int freeze : 2;              // bits 20..21
    /* 0x008 */ unsigned int free : 1;                // bits 22..22
    /* 0x008 */ unsigned int soft : 1;                // bits 23..23
    /* 0x008 */ unsigned int vivid : 2;               // bits 24..25
    /* 0x008 */ unsigned int anime : 2;               // bits 26..27
    /* 0x008 */ unsigned int pad : 4;                 // bits 28..31
};

#endif /* DDR_types_oni_mode_H */
