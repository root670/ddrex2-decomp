/* struct sequence -- 9 members, size 0x38, layout cf1f43bf546a.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x3BC8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct sequence *`.
 *
 * declared by: onimode.c (DIE 0x3BC8), b_anime.c (DIE 0x14339), p_anime.c (DIE 0x179D7), ani_load.c (DIE 0x1E8E2), dexport.c (DIE 0x3C4C9), eye_system.c (DIE 0x49F4A), fft_disp.c (DIE 0x62D20), title_demo.c (DIE 0x6BAA1), net.c (DIE 0x6FC99), net_main.c (DIE 0x78758), net_read_data.c (DIE 0x93C45), net_game_main.c (DIE 0x9A77B), workout.c (DIE 0xACAA2), bk_disp_sub.c (DIE 0xE27A8), bk_disp.c (DIE 0xE9408), fp_msel.c (DIE 0x1036F9), fp_eyetoy.c (DIE 0x10D247), fp_chara.c (DIE 0x115B88), freeplay.c (DIE 0x11A3E3), fp_style.c (DIE 0x12AAD2), fp_res.c (DIE 0x13638D), fp_opt.c (DIE 0x13F33D), net_sys_main.c (DIE 0x14C5F2), net_sys_new.c (DIE 0x1570A1), dmm_init.c (DIE 0x18CAAD), dmm_main.c (DIE 0x193A30), fp_doll.c (DIE 0x1B57D0), net_play_main.c (DIE 0x1C3536), net_game_vs.c (DIE 0x1C79FD), point.c (DIE 0x1E7025), dmm_chara.c (DIE 0x1E8852), fp_hand.c (DIE 0x202C4D), shop_init.c (DIE 0x20F35B), shop_main.c (DIE 0x219753), shop_obj.c (DIE 0x21E736), shop_disp.c (DIE 0x22DCD8), dmm_mc.c (DIE 0x247068), net_game_challenge.c (DIE 0x26BEDF), adv_topmenu_obj.c (DIE 0x2785CA), adv_endless_obj.c (DIE 0x2860BD), adv_main.c (DIE 0x292BD2), adv_nonstop_obj.c (DIE 0x29CDCE), tra_menu.c (DIE 0x2A9172), tra_main.c (DIE 0x2B43C6), tra_msel.c (DIE 0x2BBFEF), net_game_vs_win.c (DIE 0x2BF976), dmm_func.c (DIE 0x2C58AA), tra_func.c (DIE 0x2D3B7A), tra_play.c (DIE 0x2DDC64), tra_res.c (DIE 0x2E5962), net_game_prg.c (DIE 0x2EA43A), ed_edit.c (DIE 0x30AD83), info.c (DIE 0x338F76), infoshow.c (DIE 0x33FF04), kn_lfunc.c (DIE 0x3632B0), les.c (DIE 0x36A1B9), les_play.c (DIE 0x37A0C6), les_sel_lv.c (DIE 0x37CABE), dmm_event_cond.c (DIE 0x3CF5E6), dmm_event_exe.c (DIE 0x3DB287), dmm_judge.c (DIE 0x3E4DA1), dmm_play.c (DIE 0x3EC1D4), dmm_play_course.c (DIE 0x3F6BDD), dmm_qmenu.c (DIE 0x3FE4BB), dmm_result.c (DIE 0x40ADAB), dmm_select.c (DIE 0x4184D8), dmm_style.c (DIE 0x4259AA), opt_main.c (DIE 0x43F271), rec_main.c (DIE 0x470975)
 */
#ifndef DDR_types_sequence_H
#define DDR_types_sequence_H

struct sequence {   // size 0x38
    /* 0x000 */ int beat_count;                       // 0x4
    /* 0x004 */ short kind;                           // 0x2
    /* 0x006 */ short next_change;                    // 0x2
    /* 0x008 */ short music_count;                    // 0x2
    /* 0x00A */ short judge_count;                    // 0x2
    /* 0x00C */ short stolen_count;                   // 0x2
    /* 0x00E */ short op_note_ct;                     // 0x2
    /* 0x010 */ unsigned int hold_length[8];          // 0x20
    /* 0x030 */ unsigned char hold_stat[8];           // 0x8
};

#endif /* DDR_types_sequence_H */
