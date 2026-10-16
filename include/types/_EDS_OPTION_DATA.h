/* struct _EDS_OPTION_DATA -- 13 members, size 0x4, layout bffe4976c916.
 *
 * One definition, agreed by the 55 units that declare it: onimode.c (DIE 0x3D4B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDS_OPTION_DATA *`.
 *
 * declared by: onimode.c (DIE 0x3D4B), dexport.c (DIE 0x3D742), dinit.c (DIE 0x41425), eye_system.c (DIE 0x4B196), info_data.c (DIE 0x5932E), fft_disp.c (DIE 0x5FB53), bk_disp_sub.c (DIE 0xE3E38), bk_disp.c (DIE 0xEAB63), fp_msel.c (DIE 0x1048A8), fp_chara.c (DIE 0x117405), fp_style.c (DIE 0x12C48B), fp_res.c (DIE 0x137C90), fp_opt.c (DIE 0x141660), dmm_data.c (DIE 0x17C105), dmm_disp.c (DIE 0x1840C9), dmm_init.c (DIE 0x18E2CA), fp_doll.c (DIE 0x1B6F70), fp_msel_obj.c (DIE 0x1DA516), shop_init.c (DIE 0x210695), shop_list.c (DIE 0x2161C0), shop_obj.c (DIE 0x2201E2), shop_disp.c (DIE 0x230063), shop_func.c (DIE 0x238F2D), dmm_mc.c (DIE 0x249B5D), rec_nor.c (DIE 0x2596E0), adv_endless_obj.c (DIE 0x27E8A3), adv_main.c (DIE 0x290D12), adv_nonstop_obj.c (DIE 0x296B78), tra_main.c (DIE 0x2B5A6D), dmm_func.c (DIE 0x2C715F), tra_func.c (DIE 0x2D7AD4), fp_qmenu.c (DIE 0x300557), info.c (DIE 0x33B1DD), infoshow.c (DIE 0x342870), les.c (DIE 0x36B6D8), les_play.c (DIE 0x372D13), net_auth_main.c (DIE 0x3AA9C3), net_cnf_main.c (DIE 0x3B55EF), dmm_event.c (DIE 0x3C7E98), dmm_event_cond.c (DIE 0x3D0BEB), dmm_event_exe.c (DIE 0x3DC936), dmm_play_course.c (DIE 0x3F8398), dmm_qmenu.c (DIE 0x401066), dmm_result.c (DIE 0x40C989), dmm_select.c (DIE 0x419F69), dmm_style.c (DIE 0x427613), opt_adjust.c (DIE 0x42F18F), opt_doll.c (DIE 0x434091), opt_kconfig.c (DIE 0x43812F), opt_mc.c (DIE 0x44609B), opt_menu.c (DIE 0x44B2C5), workout_usermanage.c (DIE 0x457C72), rec_hi.c (DIE 0x480210), rec_end.c (DIE 0x487FD8), rec_hand.c (DIE 0x48D3AF)
 */
#ifndef DDR_types__EDS_OPTION_DATA_H
#define DDR_types__EDS_OPTION_DATA_H

struct _EDS_OPTION_DATA {   // size 0x4
    /* 0x000 */ unsigned int speed : 4;               // bits 0..3
    /* 0x000 */ unsigned int boost : 2;               // bits 4..5
    /* 0x000 */ unsigned int hidden : 2;              // bits 6..7
    /* 0x000 */ unsigned int turn : 2;                // bits 8..9
    /* 0x000 */ unsigned int thinout : 2;             // bits 10..11
    /* 0x000 */ unsigned int dark : 2;                // bits 12..13
    /* 0x000 */ unsigned int simultaneous : 3;        // bits 14..16
    /* 0x000 */ unsigned int scroll : 2;              // bits 17..18
    /* 0x000 */ unsigned int freeze : 2;              // bits 19..20
    /* 0x000 */ unsigned int player : 1;              // bits 21..21
    /* 0x000 */ unsigned int step : 3;                // bits 22..24
    /* 0x000 */ unsigned int stage : 4;               // bits 25..28
    /* 0x000 */ unsigned int pad : 3;                 // bits 29..31
};

#endif /* DDR_types__EDS_OPTION_DATA_H */
