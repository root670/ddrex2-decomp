/* struct _EDS_RANK_DATA -- 4 members, size 0x4, layout 877860ef6250.
 *
 * One definition, agreed by the 55 units that declare it: onimode.c (DIE 0x4E59).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDS_RANK_DATA *`.
 *
 * declared by: onimode.c (DIE 0x4E59), dexport.c (DIE 0x3E4DA), dinit.c (DIE 0x41EDB), eye_system.c (DIE 0x4C230), info_data.c (DIE 0x56393), fft_disp.c (DIE 0x613C7), bk_disp_sub.c (DIE 0xE4DFD), bk_disp.c (DIE 0xEB967), fp_msel.c (DIE 0x105E9A), fp_chara.c (DIE 0x10F262), fp_style.c (DIE 0x124C10), fp_res.c (DIE 0x12F635), fp_opt.c (DIE 0x14354E), dmm_data.c (DIE 0x17D3B8), dmm_disp.c (DIE 0x1852E4), dmm_init.c (DIE 0x18F386), fp_doll.c (DIE 0x1AFB2D), fp_msel_obj.c (DIE 0x1DB0E9), shop_init.c (DIE 0x211637), shop_list.c (DIE 0x216BED), shop_obj.c (DIE 0x221952), shop_disp.c (DIE 0x2315C0), shop_func.c (DIE 0x2399C1), dmm_mc.c (DIE 0x24AE3F), rec_nor.c (DIE 0x25A132), adv_endless_obj.c (DIE 0x280799), adv_main.c (DIE 0x28CED0), adv_nonstop_obj.c (DIE 0x298358), tra_main.c (DIE 0x2B692D), dmm_func.c (DIE 0x2C849E), tra_func.c (DIE 0x2D88B6), fp_qmenu.c (DIE 0x2FBF17), info.c (DIE 0x3325DE), infoshow.c (DIE 0x34418D), les.c (DIE 0x36C63E), les_play.c (DIE 0x373C82), net_auth_main.c (DIE 0x3AC2EE), net_cnf_main.c (DIE 0x3B6A73), dmm_event.c (DIE 0x3C8BAD), dmm_event_cond.c (DIE 0x3D1C8C), dmm_event_exe.c (DIE 0x3DDC5A), dmm_play_course.c (DIE 0x3F941D), dmm_qmenu.c (DIE 0x402122), dmm_result.c (DIE 0x40E08B), dmm_select.c (DIE 0x41B7D0), dmm_style.c (DIE 0x428B19), opt_adjust.c (DIE 0x42FAEF), opt_doll.c (DIE 0x434B0D), opt_kconfig.c (DIE 0x438E1B), opt_mc.c (DIE 0x446A42), opt_menu.c (DIE 0x44BDBB), workout_usermanage.c (DIE 0x45874A), rec_hi.c (DIE 0x480BD5), rec_end.c (DIE 0x488A2A), rec_hand.c (DIE 0x48DD74)
 */
#ifndef DDR_types__EDS_RANK_DATA_H
#define DDR_types__EDS_RANK_DATA_H

struct _EDS_RANK_DATA {   // size 0x4
    /* 0x000 */ unsigned int single_normal : 8;       // bits 0..7
    /* 0x000 */ unsigned int single_difficult : 8;    // bits 8..15
    /* 0x000 */ unsigned int double_normal : 8;       // bits 16..23
    /* 0x000 */ unsigned int double_difficult : 8;    // bits 24..31
};

#endif /* DDR_types__EDS_RANK_DATA_H */
