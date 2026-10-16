/* struct play_hist -- 2 members, size 0xC, layout a3d6daee7587.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x58EE).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_hist *`.
 *
 * declared by: onimode.c (DIE 0x58EE), b_anime.c (DIE 0x15B06), p_anime.c (DIE 0x188D5), ani_load.c (DIE 0x1BBA5), dexport.c (DIE 0x37E07), eye_system.c (DIE 0x4C455), fft_disp.c (DIE 0x65732), title_demo.c (DIE 0x6CA85), net.c (DIE 0x71694), net_main.c (DIE 0x7BFF3), net_read_data.c (DIE 0x96176), net_game_main.c (DIE 0x9E50B), workout.c (DIE 0xAE2EE), bk_disp_sub.c (DIE 0xE4FFD), bk_disp.c (DIE 0xEBB1C), fp_msel.c (DIE 0x1060DF), fp_eyetoy.c (DIE 0x108ABC), fp_chara.c (DIE 0x10F72F), freeplay.c (DIE 0x11D2A1), fp_style.c (DIE 0x124F48), fp_res.c (DIE 0x12F96D), fp_opt.c (DIE 0x143A2F), net_sys_main.c (DIE 0x14EC4A), net_sys_new.c (DIE 0x159F66), dmm_init.c (DIE 0x18F583), dmm_main.c (DIE 0x195D6A), fp_doll.c (DIE 0x1AFDF8), net_play_main.c (DIE 0x1C5480), net_game_vs.c (DIE 0x1CC730), point.c (DIE 0x1E4641), dmm_chara.c (DIE 0x1EAB8C), fp_hand.c (DIE 0x1FEC73), shop_init.c (DIE 0x211812), shop_main.c (DIE 0x21A834), shop_obj.c (DIE 0x221B2B), shop_disp.c (DIE 0x2318F6), dmm_mc.c (DIE 0x24B03C), net_game_challenge.c (DIE 0x26E7D7), adv_topmenu_obj.c (DIE 0x273FDC), adv_endless_obj.c (DIE 0x280C89), adv_main.c (DIE 0x28D338), adv_nonstop_obj.c (DIE 0x2986D5), tra_menu.c (DIE 0x2AA6FC), tra_main.c (DIE 0x2B6B2A), tra_msel.c (DIE 0x2BDBB8), net_game_vs_win.c (DIE 0x2C0A90), dmm_func.c (DIE 0x2C869B), tra_func.c (DIE 0x2D8BC8), tra_play.c (DIE 0x2E012A), tra_res.c (DIE 0x2E799F), net_game_prg.c (DIE 0x2EC50C), ed_edit.c (DIE 0x30961C), info.c (DIE 0x333D66), infoshow.c (DIE 0x34450B), kn_lfunc.c (DIE 0x364555), les.c (DIE 0x36C7DD), les_play.c (DIE 0x375534), les_sel_lv.c (DIE 0x37ECA0), dmm_event_cond.c (DIE 0x3D1F35), dmm_event_exe.c (DIE 0x3DDE76), dmm_judge.c (DIE 0x3E74BA), dmm_play.c (DIE 0x3EEB1E), dmm_play_course.c (DIE 0x3F9823), dmm_qmenu.c (DIE 0x40231F), dmm_result.c (DIE 0x40EE9B), dmm_select.c (DIE 0x41BB91), dmm_style.c (DIE 0x428D3A), opt_main.c (DIE 0x440A94), rec_main.c (DIE 0x47154D)
 */
#ifndef DDR_types_play_hist_H
#define DDR_types_play_hist_H

struct play_hist {   // size 0xC
    /* 0x000 */ int music_count;                      // 0x4
    /* 0x004 */ unsigned char input[8];               // 0x8
};

#endif /* DDR_types_play_hist_H */
