/* struct popular -- 3 members, size 0x804, layout 7ac52f12bd70.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x3FB8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct popular *`.
 *
 * declared by: onimode.c (DIE 0x3FB8), dexport.c (DIE 0x3D9AF), dinit.c (DIE 0x41354), eye_system.c (DIE 0x4B0C5), info_data.c (DIE 0x56490), fft_disp.c (DIE 0x5FDC0), bk_disp_sub.c (DIE 0xE3D67), bk_disp.c (DIE 0xEADD0), fp_msel.c (DIE 0x1002C2), fp_chara.c (DIE 0x117672), fp_style.c (DIE 0x12C6F8), fp_res.c (DIE 0x137EFD), fp_opt.c (DIE 0x1418CD), dmm_data.c (DIE 0x17C372), dmm_disp.c (DIE 0x184336), dmm_init.c (DIE 0x18E537), fp_doll.c (DIE 0x1B71DD), fp_msel_obj.c (DIE 0x1DA320), shop_init.c (DIE 0x210902), shop_list.c (DIE 0x21642D), shop_obj.c (DIE 0x22044F), shop_disp.c (DIE 0x2302D0), shop_func.c (DIE 0x23919A), dmm_mc.c (DIE 0x249DCA), rec_nor.c (DIE 0x25994D), adv_endless_obj.c (DIE 0x27DE17), adv_main.c (DIE 0x293D13), tra_main.c (DIE 0x2B5CDA), dmm_func.c (DIE 0x2C73CC), tra_func.c (DIE 0x2D7D41), fp_qmenu.c (DIE 0x3007C4), info.c (DIE 0x33249C), infoshow.c (DIE 0x3402E2), les.c (DIE 0x36A6F6), les_play.c (DIE 0x37A976), net_auth_main.c (DIE 0x3ABE64), net_cnf_main.c (DIE 0x3B6822), dmm_event.c (DIE 0x3C8105), dmm_event_cond.c (DIE 0x3D0AF6), dmm_event_exe.c (DIE 0x3DC841), dmm_play_course.c (DIE 0x3F82A3), dmm_qmenu.c (DIE 0x4012D3), dmm_result.c (DIE 0x40C870), dmm_select.c (DIE 0x419DB2), dmm_style.c (DIE 0x427880), opt_adjust.c (DIE 0x42F095), opt_doll.c (DIE 0x4331FC), opt_kconfig.c (DIE 0x43805E), opt_mc.c (DIE 0x446308), opt_menu.c (DIE 0x44B532), workout_usermanage.c (DIE 0x458443), rec_hi.c (DIE 0x48047D), rec_end.c (DIE 0x488245), rec_hand.c (DIE 0x48D61C)
 */
#ifndef DDR_types_popular_H
#define DDR_types_popular_H

struct popular {   // size 0x804
    /* 0x000 */ short cur_c;                          // 0x2
    /* 0x002 */ short last_c;                         // 0x2
    /* 0x004 */ unsigned short count[256][4];         // 0x800
};

#endif /* DDR_types_popular_H */
