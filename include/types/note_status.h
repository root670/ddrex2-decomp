/* struct note_status -- 2 members, size 0x28, layout 366edeb915db.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x8A35).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct note_status *`.
 *
 * declared by: onimode.c (DIE 0x8A35), b_anime.c (DIE 0x135E0), p_anime.c (DIE 0x1796A), ani_load.c (DIE 0x1DDDC), dexport.c (DIE 0x3AF44), eye_system.c (DIE 0x47D12), fft_disp.c (DIE 0x61749), title_demo.c (DIE 0x6AE7D), net.c (DIE 0x6E84B), net_main.c (DIE 0x80424), net_read_data.c (DIE 0x92A1F), net_game_main.c (DIE 0xA3009), workout.c (DIE 0xABB55), bk_disp_sub.c (DIE 0xE10A7), bk_disp.c (DIE 0xE7C58), fp_msel.c (DIE 0x1011CA), fp_eyetoy.c (DIE 0x10BEBF), fp_chara.c (DIE 0x1143E8), freeplay.c (DIE 0x11FD2A), fp_style.c (DIE 0x12938F), fp_res.c (DIE 0x134940), fp_opt.c (DIE 0x147B16), net_sys_main.c (DIE 0x151B5F), net_sys_new.c (DIE 0x15CF9A), dmm_init.c (DIE 0x18AE3F), dmm_main.c (DIE 0x198BBF), fp_doll.c (DIE 0x1B4056), net_play_main.c (DIE 0x1C1F92), net_game_vs.c (DIE 0x1D0C92), point.c (DIE 0x1E65E6), dmm_chara.c (DIE 0x1ED9E1), fp_hand.c (DIE 0x201F34), shop_init.c (DIE 0x20D270), shop_main.c (DIE 0x21CC09), shop_obj.c (DIE 0x225964), shop_disp.c (DIE 0x23570E), dmm_mc.c (DIE 0x24ED49), net_game_challenge.c (DIE 0x26A95C), adv_topmenu_obj.c (DIE 0x2777BC), adv_endless_obj.c (DIE 0x284F71), adv_main.c (DIE 0x2915BC), adv_nonstop_obj.c (DIE 0x29BF4F), tra_menu.c (DIE 0x2A7F29), tra_main.c (DIE 0x2B23D2), tra_msel.c (DIE 0x2BA39F), net_game_vs_win.c (DIE 0x2BE6D5), dmm_func.c (DIE 0x2CC3CD), tra_func.c (DIE 0x2D4371), tra_play.c (DIE 0x2DE0C2), tra_res.c (DIE 0x2E4122), net_game_prg.c (DIE 0x2EFA61), ed_edit.c (DIE 0x309D8C), info.c (DIE 0x336BAA), infoshow.c (DIE 0x347F9F), kn_lfunc.c (DIE 0x362214), les.c (DIE 0x3683C5), les_play.c (DIE 0x379556), les_sel_lv.c (DIE 0x380FE3), dmm_event_cond.c (DIE 0x3CC343), dmm_event_exe.c (DIE 0x3D7650), dmm_judge.c (DIE 0x3E9FFB), dmm_play.c (DIE 0x3F1CA8), dmm_play_course.c (DIE 0x3F3885), dmm_qmenu.c (DIE 0x405F08), dmm_result.c (DIE 0x407A29), dmm_select.c (DIE 0x4160EF), dmm_style.c (DIE 0x4229A1), opt_main.c (DIE 0x43DCAB), rec_main.c (DIE 0x46F991)
 */
#ifndef DDR_types_note_status_H
#define DDR_types_note_status_H

struct note_status {   // size 0x28
    /* 0x000 */ unsigned char state[8];               // 0x8
    /* 0x008 */ unsigned int length[8];               // 0x20
};

#endif /* DDR_types_note_status_H */
