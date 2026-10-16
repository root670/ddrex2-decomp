/* struct _tag_cDDR8Record1 -- 8 members, size 0x8C, layout 598e46ec4548.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x5B31).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR8Record1 *`.
 *
 * declared by: onimode.c (DIE 0x5B31), dexport.c (DIE 0x3A8BB), dinit.c (DIE 0x43237), eye_system.c (DIE 0x4EE38), info_data.c (DIE 0x57465), fft_disp.c (DIE 0x63381), bk_disp_sub.c (DIE 0xE078C), bk_disp.c (DIE 0xE6F42), fp_msel.c (DIE 0x10074D), fp_chara.c (DIE 0x113392), fp_style.c (DIE 0x128B96), fp_res.c (DIE 0x133CAC), fp_opt.c (DIE 0x147378), dmm_data.c (DIE 0x17E6D9), dmm_disp.c (DIE 0x186909), dmm_init.c (DIE 0x19240F), fp_doll.c (DIE 0x1B3784), fp_msel_obj.c (DIE 0x1D53BA), shop_init.c (DIE 0x214063), shop_list.c (DIE 0x217AFA), shop_obj.c (DIE 0x224DC3), shop_disp.c (DIE 0x234C0A), shop_func.c (DIE 0x23A554), dmm_mc.c (DIE 0x24DDB1), rec_nor.c (DIE 0x257581), adv_endless_obj.c (DIE 0x284476), adv_main.c (DIE 0x290901), tra_main.c (DIE 0x2B164E), dmm_func.c (DIE 0x2CB7CB), tra_func.c (DIE 0x2D3D21), fp_qmenu.c (DIE 0x2FD286), info.c (DIE 0x33536C), infoshow.c (DIE 0x347981), les.c (DIE 0x367C76), les_play.c (DIE 0x378B1A), net_auth_main.c (DIE 0x3A4964), net_cnf_main.c (DIE 0x3B1340), dmm_event.c (DIE 0x3C9C81), dmm_event_cond.c (DIE 0x3D4D8B), dmm_event_exe.c (DIE 0x3E0D9D), dmm_play_course.c (DIE 0x3FC8EB), dmm_qmenu.c (DIE 0x405303), dmm_result.c (DIE 0x4118E2), dmm_select.c (DIE 0x414F9F), dmm_style.c (DIE 0x42BE6D), opt_adjust.c (DIE 0x430AA1), opt_doll.c (DIE 0x431A56), opt_kconfig.c (DIE 0x43A546), opt_mc.c (DIE 0x447BBE), opt_menu.c (DIE 0x44CF27), workout_usermanage.c (DIE 0x4594E4), rec_hi.c (DIE 0x47CE22), rec_end.c (DIE 0x485ACC), rec_hand.c (DIE 0x489F07)
 */
#ifndef DDR_types__tag_cDDR8Record1_H
#define DDR_types__tag_cDDR8Record1_H

struct _tag_cDDR8Record1 {   // size 0x8C
    /* 0x000 */ unsigned int Score[10];               // 0x28
    /* 0x028 */ unsigned int Bonus[10];               // 0x28
    /* 0x050 */ unsigned int nPlayed;                 // 0x4
    /* 0x054 */ unsigned short LinkNum;               // 0x2
    /* 0x056 */ unsigned short Combo[10];             // 0x14
    /* 0x06A */ unsigned short ComboMax[10];          // 0x14
    /* 0x07E */ unsigned char Level[10];              // 0xA
    /* 0x088 */ unsigned char pad[2];                 // 0x2
    /* 0x08A */ // 0x2 bytes padding
};

#endif /* DDR_types__tag_cDDR8Record1_H */
