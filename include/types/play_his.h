/* struct play_his -- 6 members, size 0x8, layout 155772b32f36.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x5E4C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_his *`.
 *
 * declared by: onimode.c (DIE 0x5E4C), b_anime.c (DIE 0x15CB3), p_anime.c (DIE 0x18A39), ani_load.c (DIE 0x1BCE5), dexport.c (DIE 0x3804D), eye_system.c (DIE 0x4C827), fft_disp.c (DIE 0x65B19), title_demo.c (DIE 0x6CC6B), net.c (DIE 0x71D1B), net_main.c (DIE 0x7C7B9), net_read_data.c (DIE 0x96837), net_game_main.c (DIE 0x9F413), workout.c (DIE 0xAE558), bk_disp_sub.c (DIE 0xDDE78), bk_disp.c (DIE 0xEBD63), fp_msel.c (DIE 0xFDF5D), fp_eyetoy.c (DIE 0x108ED7), fp_chara.c (DIE 0x10FB77), freeplay.c (DIE 0x11D409), fp_style.c (DIE 0x125585), fp_res.c (DIE 0x12FEC1), fp_opt.c (DIE 0x1441F8), net_sys_main.c (DIE 0x14F30B), net_sys_new.c (DIE 0x15A592), dmm_init.c (DIE 0x18FC5B), dmm_main.c (DIE 0x19613F), fp_doll.c (DIE 0x1B047F), net_play_main.c (DIE 0x1BE8FE), net_game_vs.c (DIE 0x1CD335), point.c (DIE 0x1E48B1), dmm_chara.c (DIE 0x1EAF61), fp_hand.c (DIE 0x1FEF42), shop_init.c (DIE 0x211B24), shop_main.c (DIE 0x21A998), shop_obj.c (DIE 0x22204A), shop_disp.c (DIE 0x231EA5), dmm_mc.c (DIE 0x24B2F1), net_game_challenge.c (DIE 0x26F139), adv_topmenu_obj.c (DIE 0x2744AE), adv_endless_obj.c (DIE 0x28151A), adv_main.c (DIE 0x28D70E), adv_nonstop_obj.c (DIE 0x298BF2), tra_menu.c (DIE 0x2AA83D), tra_main.c (DIE 0x2ACD29), tra_msel.c (DIE 0x2BDD1F), net_game_vs_win.c (DIE 0x2C0D77), dmm_func.c (DIE 0x2C8B76), tra_func.c (DIE 0x2D8E7B), tra_play.c (DIE 0x2E02D6), tra_res.c (DIE 0x2E8218), net_game_prg.c (DIE 0x2ECB78), ed_edit.c (DIE 0x30ABB2), info.c (DIE 0x338C67), infoshow.c (DIE 0x344A1B), kn_lfunc.c (DIE 0x36474E), les.c (DIE 0x36CB78), les_play.c (DIE 0x375B0F), les_sel_lv.c (DIE 0x37EDE0), dmm_event_cond.c (DIE 0x3D255C), dmm_event_exe.c (DIE 0x3DE3B2), dmm_judge.c (DIE 0x3E788F), dmm_play.c (DIE 0x3EEF5F), dmm_play_course.c (DIE 0x3F9EB6), dmm_qmenu.c (DIE 0x4028EC), dmm_result.c (DIE 0x40F7F8), dmm_select.c (DIE 0x41C3F7), dmm_style.c (DIE 0x429548), opt_main.c (DIE 0x440D03), rec_main.c (DIE 0x4716DF)
 */
#ifndef DDR_types_play_his_H
#define DDR_types_play_his_H

struct play_his {   // size 0x8
    /* 0x000 */ short music;                          // 0x2
    /* 0x002 */ short edit_id;                        // 0x2
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ signed char roulette;                 // 0x1
    /* 0x006 */ signed char extra;                    // 0x1
    /* 0x007 */ signed char pad;                      // 0x1
};

#endif /* DDR_types_play_his_H */
