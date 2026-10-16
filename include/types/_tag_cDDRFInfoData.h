/* struct _tag_cDDRFInfoData -- 4 members, size 0x510, layout d74cab7170a0.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x2EED).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDRFInfoData *`.
 *
 * declared by: onimode.c (DIE 0x2EED), dexport.c (DIE 0x3D19D), dinit.c (DIE 0x40D45), eye_system.c (DIE 0x4AB42), info_data.c (DIE 0x5911D), fft_disp.c (DIE 0x65C0C), bk_disp_sub.c (DIE 0xE37E4), bk_disp.c (DIE 0xEA597), fp_msel.c (DIE 0x104471), fp_chara.c (DIE 0x116C56), fp_style.c (DIE 0x12BD72), fp_res.c (DIE 0x13745D), fp_opt.c (DIE 0x140BB4), dmm_data.c (DIE 0x17A6C9), dmm_disp.c (DIE 0x183A33), dmm_init.c (DIE 0x18DB72), fp_doll.c (DIE 0x1B687A), fp_msel_obj.c (DIE 0x1D9B34), shop_init.c (DIE 0x21002F), shop_list.c (DIE 0x215A96), shop_obj.c (DIE 0x21F947), shop_disp.c (DIE 0x22F176), shop_func.c (DIE 0x23886A), dmm_mc.c (DIE 0x24814E), rec_nor.c (DIE 0x259085), adv_endless_obj.c (DIE 0x27D03D), adv_main.c (DIE 0x293A46), tra_main.c (DIE 0x2B5272), dmm_func.c (DIE 0x2C6A2E), tra_func.c (DIE 0x2D7474), fp_qmenu.c (DIE 0x2FFF1B), info.c (DIE 0x33AC1D), infoshow.c (DIE 0x34173B), les.c (DIE 0x36B459), les_play.c (DIE 0x37237F), net_auth_main.c (DIE 0x3A9FFE), net_cnf_main.c (DIE 0x3B51BC), dmm_event.c (DIE 0x3C756B), dmm_event_cond.c (DIE 0x3D0416), dmm_event_exe.c (DIE 0x3DC13D), dmm_play_course.c (DIE 0x3F7B33), dmm_qmenu.c (DIE 0x3FF657), dmm_result.c (DIE 0x40C053), dmm_select.c (DIE 0x4194CF), dmm_style.c (DIE 0x426C0A), opt_adjust.c (DIE 0x42EB38), opt_doll.c (DIE 0x433DC5), opt_kconfig.c (DIE 0x437A95), opt_mc.c (DIE 0x445AAD), opt_menu.c (DIE 0x44ACF7), workout_usermanage.c (DIE 0x457A61), rec_hi.c (DIE 0x47FC8C), rec_end.c (DIE 0x487A54), rec_hand.c (DIE 0x48CE07)
 */
#ifndef DDR_types__tag_cDDRFInfoData_H
#define DDR_types__tag_cDDRFInfoData_H

struct _tag_cDDRFInfoData {   // size 0x510
    /* 0x000 */ unsigned char Information[256];       // 0x100
    /* 0x100 */ int UnlockedNum[256];                 // 0x400
    /* 0x500 */ int unum;                             // 0x4
    /* 0x504 */ char pad[12];                         // 0xC
};

#endif /* DDR_types__tag_cDDRFInfoData_H */
