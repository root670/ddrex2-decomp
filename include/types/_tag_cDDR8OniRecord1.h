/* struct _tag_cDDR8OniRecord1 -- 12 members, size 0x28, layout c9c9f7aab5f9.
 *
 * One definition, agreed by the 55 units that declare it: onimode.c (DIE 0x4681).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR8OniRecord1 *`.
 *
 * declared by: onimode.c (DIE 0x4681), dexport.c (DIE 0x3B58D), dinit.c (DIE 0x3F2C4), eye_system.c (DIE 0x4852E), info_data.c (DIE 0x57CDB), fft_disp.c (DIE 0x642CC), bk_disp_sub.c (DIE 0xE1643), bk_disp.c (DIE 0xE8B35), fp_msel.c (DIE 0x1024A9), fp_chara.c (DIE 0x114ABF), fp_style.c (DIE 0x129994), fp_res.c (DIE 0x13502B), fp_opt.c (DIE 0x13DDC2), dmm_data.c (DIE 0x17F7E1), dmm_disp.c (DIE 0x187C71), dmm_init.c (DIE 0x18B675), fp_doll.c (DIE 0x1B4707), fp_msel_obj.c (DIE 0x1D74AC), shop_init.c (DIE 0x20E033), shop_list.c (DIE 0x218528), shop_obj.c (DIE 0x225FEA), shop_disp.c (DIE 0x235D70), shop_func.c (DIE 0x23AEF2), dmm_mc.c (DIE 0x24F3B5), rec_nor.c (DIE 0x2567CF), adv_endless_obj.c (DIE 0x285533), adv_main.c (DIE 0x291B32), tra_main.c (DIE 0x2B2D21), dmm_func.c (DIE 0x2CCC2E), tra_func.c (DIE 0x2D4A75), fp_qmenu.c (DIE 0x2FE2CF), info.c (DIE 0x33677D), infoshow.c (DIE 0x3484CC), les.c (DIE 0x368C67), les_play.c (DIE 0x379939), net_auth_main.c (DIE 0x3A7378), net_cnf_main.c (DIE 0x3B311F), dmm_event.c (DIE 0x3CADF9), dmm_event_cond.c (DIE 0x3CCBA8), dmm_event_exe.c (DIE 0x3D9515), dmm_play_course.c (DIE 0x3F40EA), dmm_qmenu.c (DIE 0x40671F), dmm_result.c (DIE 0x4082D6), dmm_select.c (DIE 0x4169A3), dmm_style.c (DIE 0x4244DA), opt_adjust.c (DIE 0x42DB2C), opt_doll.c (DIE 0x4323CE), opt_kconfig.c (DIE 0x4361D9), opt_mc.c (DIE 0x4486C4), opt_menu.c (DIE 0x44DA9E), workout_usermanage.c (DIE 0x459DED), rec_hi.c (DIE 0x47EA41), rec_cha.c (DIE 0x48340B), rec_end.c (DIE 0x486851), rec_hand.c (DIE 0x48BBBC)
 */
#ifndef DDR_types__tag_cDDR8OniRecord1_H
#define DDR_types__tag_cDDR8OniRecord1_H

struct _tag_cDDR8OniRecord1 {   // size 0x28
    /* 0x000 */ unsigned int Time[2];                 // 0x8
    /* 0x008 */ unsigned int Score[2];                // 0x8
    /* 0x010 */ unsigned short Combo[2];              // 0x4
    /* 0x014 */ unsigned char Stage[2];               // 0x2
    /* 0x016 */ unsigned char Miss[2];                // 0x2
    /* 0x018 */ unsigned char AllStage[2];            // 0x2
    /* 0x01A */ unsigned char Level[2];               // 0x2
    /* 0x01C */ unsigned char is_first_clear;         // 0x1
    /* 0x01D */ unsigned char is_full_combo_flag[2];  // 0x2
    /* 0x01F */ unsigned char pad[1];                 // 0x1
    /* 0x020 */ unsigned short ClearNum[2];           // 0x4
    /* 0x024 */ unsigned char pad2[2];                // 0x2
    /* 0x026 */ // 0x2 bytes padding
};

#endif /* DDR_types__tag_cDDR8OniRecord1_H */
