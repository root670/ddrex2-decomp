/* struct eval_w -- 7 members, size 0x40, layout 54ff2b7f389f.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x923A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct eval_w *`.
 *
 * declared by: onimode.c (DIE 0x923A), b_anime.c (DIE 0x139AE), p_anime.c (DIE 0x1ACBD), ani_load.c (DIE 0x1DED9), dexport.c (DIE 0x3B377), eye_system.c (DIE 0x48720), fft_disp.c (DIE 0x618B4), title_demo.c (DIE 0x6AF9E), net.c (DIE 0x6EBCB), net_main.c (DIE 0x76885), net_read_data.c (DIE 0x92C21), net_game_main.c (DIE 0xA33C5), workout.c (DIE 0xABC8E), bk_disp_sub.c (DIE 0xE1835), bk_disp.c (DIE 0xE88FC), fp_msel.c (DIE 0x101B2C), fp_eyetoy.c (DIE 0x10C13F), fp_chara.c (DIE 0x1148A8), freeplay.c (DIE 0x11FE27), fp_style.c (DIE 0x129733), fp_res.c (DIE 0x12F187), fp_opt.c (DIE 0x13D91D), net_sys_main.c (DIE 0x151D3D), net_sys_new.c (DIE 0x15D1A1), dmm_init.c (DIE 0x18B2BA), dmm_main.c (DIE 0x199153), fp_doll.c (DIE 0x1B44F0), net_play_main.c (DIE 0x1C23D0), net_game_vs.c (DIE 0x1D1142), point.c (DIE 0x1E46AF), dmm_chara.c (DIE 0x1EDF75), fp_hand.c (DIE 0x202031), shop_init.c (DIE 0x20DD56), shop_main.c (DIE 0x21CE19), shop_obj.c (DIE 0x225DD3), shop_disp.c (DIE 0x235B59), dmm_mc.c (DIE 0x24F156), net_game_challenge.c (DIE 0x26B118), adv_topmenu_obj.c (DIE 0x277996), adv_endless_obj.c (DIE 0x285725), adv_main.c (DIE 0x29191B), adv_nonstop_obj.c (DIE 0x29C0DC), tra_menu.c (DIE 0x2A8076), tra_main.c (DIE 0x2B2AAC), tra_msel.c (DIE 0x2BA567), net_game_vs_win.c (DIE 0x2BE9DF), dmm_func.c (DIE 0x2CC9F3), tra_func.c (DIE 0x2D46A8), tra_play.c (DIE 0x2DDDE7), tra_res.c (DIE 0x2E4337), net_game_prg.c (DIE 0x2EAB25), ed_edit.c (DIE 0x30CE4E), info.c (DIE 0x33287B), infoshow.c (DIE 0x34828F), kn_lfunc.c (DIE 0x362337), les.c (DIE 0x36850A), les_play.c (DIE 0x3784E5), les_sel_lv.c (DIE 0x3810A8), dmm_event_cond.c (DIE 0x3CCDBE), dmm_event_exe.c (DIE 0x3D98CD), dmm_judge.c (DIE 0x3EA58F), dmm_play.c (DIE 0x3F223C), dmm_play_course.c (DIE 0x3F4300), dmm_qmenu.c (DIE 0x4064E4), dmm_result.c (DIE 0x4084C8), dmm_select.c (DIE 0x416B95), dmm_style.c (DIE 0x42411F), opt_main.c (DIE 0x43DD86), rec_main.c (DIE 0x46FA8E)
 */
#ifndef DDR_types_eval_w_H
#define DDR_types_eval_w_H

struct eval_w {   // size 0x40
    /* 0x000 */ int value_ct[8];                      // 0x20
    /* 0x020 */ int freez_value_ct[4];                // 0x10
    /* 0x030 */ int score;                            // 0x4
    /* 0x034 */ int bonus;                            // 0x4
    /* 0x038 */ int max_combo_ct;                     // 0x4
    /* 0x03C */ short dance_level;                    // 0x2
    /* 0x03E */ short fixed_level;                    // 0x2
};

#endif /* DDR_types_eval_w_H */
