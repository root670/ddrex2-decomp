/* struct music_info -- 22 members, size 0xA0, layout c0383b81bffa.
 *
 * One definition, agreed by the 77 units that declare it: onimode.c (DIE 0x2A19).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct music_info *`.
 *
 * declared by: onimode.c (DIE 0x2A19), b_anime.c (DIE 0x130DD), p_anime.c (DIE 0x1A5AF), ani_load.c (DIE 0x1D85B), dexport.c (DIE 0x39FE3), eye_system.c (DIE 0x48A40), info_data.c (DIE 0x56807), fft_disp.c (DIE 0x60CD4), title_demo.c (DIE 0x68BD5), net.c (DIE 0x6ED8B), net_main.c (DIE 0x76FFF), net_read_data.c (DIE 0x92E76), net_game_main.c (DIE 0x9943B), net_game_window.c (DIE 0xA5554), workout.c (DIE 0xABE88), bk_disp_sub.c (DIE 0xDE4A3), bk_disp.c (DIE 0xE6533), fp_msel.c (DIE 0xFE0C2), fp_eyetoy.c (DIE 0x10ABB5), fp_chara.c (DIE 0x111E0A), freeplay.c (DIE 0x11A566), fp_style.c (DIE 0x1277A1), fp_res.c (DIE 0x13256C), fp_opt.c (DIE 0x13E1E6), net_sys_main.c (DIE 0x14B978), net_sys_new.c (DIE 0x156226), dmm_init.c (DIE 0x18BA99), dmm_main.c (DIE 0x197DEC), fp_doll.c (DIE 0x1B23FF), net_play_main.c (DIE 0x1C0E8F), net_game_vs.c (DIE 0x1C6A6F), fp_msel_obj.c (DIE 0x1D4096), point.c (DIE 0x1E3A93), dmm_chara.c (DIE 0x1ECC0E), fp_hand.c (DIE 0x201009), shop_init.c (DIE 0x20E433), shop_list.c (DIE 0x21755D), shop_main.c (DIE 0x21C50E), shop_obj.c (DIE 0x22424C), shop_disp.c (DIE 0x234289), dmm_mc.c (DIE 0x24D33C), net_game_challenge.c (DIE 0x26B2DA), adv_topmenu_obj.c (DIE 0x2746CB), adv_endless_obj.c (DIE 0x27E0A7), adv_main.c (DIE 0x28FBD2), adv_nonstop_obj.c (DIE 0x29754D), tra_menu.c (DIE 0x2A6BF5), tra_main.c (DIE 0x2B016F), tra_msel.c (DIE 0x2B9E56), net_game_vs_win.c (DIE 0x2BECFA), dmm_func.c (DIE 0x2CAD7C), tra_func.c (DIE 0x2D2F31), tra_play.c (DIE 0x2DD68C), tra_res.c (DIE 0x2E3312), net_game_prg.c (DIE 0x2E9418), ed_edit.c (DIE 0x309F5A), ed_select.c (DIE 0x311E47), el_disp_obj.c (DIE 0x32623D), info.c (DIE 0x332ACE), infoshow.c (DIE 0x34251A), kn_lfunc.c (DIE 0x3625CB), les.c (DIE 0x3688D2), les_play.c (DIE 0x374B41), les_sel_lv.c (DIE 0x37E720), dmm_event_cond.c (DIE 0x3CE3FB), dmm_event_exe.c (DIE 0x3D9F4C), dmm_judge.c (DIE 0x3E953C), dmm_play.c (DIE 0x3F0F83), dmm_play_course.c (DIE 0x3F593D), dmm_qmenu.c (DIE 0x404986), dmm_result.c (DIE 0x408907), dmm_select.c (DIE 0x417207), dmm_style.c (DIE 0x4248FE), opt_main.c (DIE 0x43DF46), rec_main.c (DIE 0x46FC4E), rec_hi.c (DIE 0x47D20F), rec_hand.c (DIE 0x48A37D)
 */
#ifndef DDR_types_music_info_H
#define DDR_types_music_info_H

struct music_info {   // size 0xA0
    /* 0x000 */ char base_name[6];                    // 0x6
    /* 0x006 */ signed char kind;                     // 0x1
    /* 0x007 */ signed char album;                    // 0x1
    /* 0x008 */ short dance_num;                      // 0x2
    /* 0x00A */ short order;                          // 0x2
    /* 0x00C */ unsigned int main_track;              // 0x4
    /* 0x010 */ unsigned int select_track;            // 0x4
    /* 0x014 */ unsigned short bpm_max;               // 0x2
    /* 0x016 */ unsigned short bpm_min;               // 0x2
    /* 0x018 */ unsigned short verm_num;              // 0x2
    /* 0x01A */ unsigned short pcseq_num;             // 0x2
    /* 0x01C */ // 0x4 bytes padding
    /* 0x020 */ unsigned long hide;                   // 0x8
    /* 0x028 */ short adjust_mc;                      // 0x2
    /* 0x02A */ // 0x2 bytes padding
    /* 0x02C */ unsigned int difficulty[2];           // 0x8
    /* 0x034 */ unsigned int special;                 // 0x4
    /* 0x038 */ unsigned short max_spm[9];            // 0x12
    /* 0x04A */ unsigned short avg_spm[9];            // 0x12
    /* 0x05C */ unsigned short avg_jpm[9];            // 0x12
    /* 0x06E */ unsigned short chaos_v[9];            // 0x12
    /* 0x080 */ unsigned short freez_v[9];            // 0x12
    /* 0x092 */ // 0x2 bytes padding
    /* 0x094 */ char *title;                          // 0x4
    /* 0x098 */ char *l_name;                         // 0x4
    /* 0x09C */ // 0x4 bytes padding
};

#endif /* DDR_types_music_info_H */
