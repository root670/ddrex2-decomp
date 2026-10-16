/* struct play_mode -- 19 members, size 0xC, layout 62eb21634ae1.
 *
 * One definition, agreed by the 73 units that declare it: onimode.c (DIE 0x4A58).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_mode *`.
 *
 * declared by: onimode.c (DIE 0x4A58), b_anime.c (DIE 0x153DB), p_anime.c (DIE 0x17D1E), ani_load.c (DIE 0x1ECF3), dexport.c (DIE 0x3E030), eye_system.c (DIE 0x4BAB3), fft_disp.c (DIE 0x6475D), title_demo.c (DIE 0x6C198), net.c (DIE 0x70C3B), net_main.c (DIE 0x7A905), net_read_data.c (DIE 0x94C9B), net_game_main.c (DIE 0x9CA80), workout.c (DIE 0xADD1A), bk_disp_sub.c (DIE 0xE48A9), bk_disp.c (DIE 0xEB451), fp_msel.c (DIE 0x10576B), fp_eyetoy.c (DIE 0x10DE12), fp_chara.c (DIE 0x117CF3), freeplay.c (DIE 0x11CC20), fp_style.c (DIE 0x123F05), fp_res.c (DIE 0x12E637), fp_opt.c (DIE 0x14206F), net_sys_main.c (DIE 0x14D647), net_sys_new.c (DIE 0x15864D), dmm_data.c (DIE 0x17CC48), dmm_disp.c (DIE 0x1849AF), dmm_init.c (DIE 0x18EBFB), dmm_main.c (DIE 0x195604), fp_doll.c (DIE 0x1B7838), net_play_main.c (DIE 0x1C4D2A), net_game_vs.c (DIE 0x1C81E3), point.c (DIE 0x1E4054), dmm_chara.c (DIE 0x1EA426), fp_hand.c (DIE 0x1FE28C), shop_init.c (DIE 0x21108A), shop_main.c (DIE 0x21A2F6), shop_obj.c (DIE 0x220F13), shop_disp.c (DIE 0x230DBA), dmm_mess.c (DIE 0x2412C7), dmm_mc.c (DIE 0x24A48E), net_game_challenge.c (DIE 0x26DA92), adv_topmenu_obj.c (DIE 0x272C5A), adv_endless_obj.c (DIE 0x27F7CC), adv_main.c (DIE 0x28BFBE), adv_nonstop_obj.c (DIE 0x29720C), tra_menu.c (DIE 0x2AA22D), tra_main.c (DIE 0x2B6415), tra_msel.c (DIE 0x2BD44A), net_game_vs_win.c (DIE 0x2C027D), dmm_func.c (DIE 0x2C7A90), tra_func.c (DIE 0x2D83E8), tra_play.c (DIE 0x2DFB46), tra_res.c (DIE 0x2E7072), net_game_prg.c (DIE 0x2EBC69), ed_edit.c (DIE 0x30982F), info.c (DIE 0x335FE4), infoshow.c (DIE 0x343663), kn_lfunc.c (DIE 0x363B33), les.c (DIE 0x36BED0), les_play.c (DIE 0x3726B5), les_sel_lv.c (DIE 0x37E0B5), dmm_event.c (DIE 0x3C877F), dmm_event_cond.c (DIE 0x3D173E), dmm_event_exe.c (DIE 0x3DD489), dmm_judge.c (DIE 0x3E6999), dmm_play.c (DIE 0x3EE25A), dmm_play_course.c (DIE 0x3F8F84), dmm_qmenu.c (DIE 0x401997), dmm_result.c (DIE 0x40DAFA), dmm_select.c (DIE 0x41B059), dmm_style.c (DIE 0x428365), opt_main.c (DIE 0x440002), rec_main.c (DIE 0x471110)
 */
#ifndef DDR_types_play_mode_H
#define DDR_types_play_mode_H

struct play_mode {   // size 0xC
    /* 0x000 */ unsigned char seq_kind;               // 0x1
    /* 0x001 */ unsigned char seq_transfer;           // 0x1
    /* 0x002 */ unsigned char style;                  // 0x1
    /* 0x003 */ unsigned char pccard_seq;             // 0x1
    /* 0x004 */ unsigned char mcard_seq;              // 0x1
    /* 0x005 */ unsigned char padding;                // 0x1
    /* 0x006 */ short edseq_id;                       // 0x2
    /* 0x008 */ unsigned int hidden : 3;              // bits 0..2
    /* 0x008 */ unsigned int thinout : 1;             // bits 3..3
    /* 0x008 */ unsigned int free : 1;                // bits 4..4
    /* 0x008 */ unsigned int soft : 1;                // bits 5..5
    /* 0x008 */ unsigned int boost : 2;               // bits 6..7
    /* 0x008 */ unsigned int speed : 5;               // bits 8..12
    /* 0x008 */ unsigned int scroll : 2;              // bits 13..14
    /* 0x008 */ unsigned int freeze : 1;              // bits 15..15
    /* 0x008 */ unsigned int vivid : 2;               // bits 16..17
    /* 0x008 */ unsigned int anime : 2;               // bits 18..19
    /* 0x008 */ unsigned int dark : 1;                // bits 20..20
    /* 0x008 */ unsigned int simultaneous : 2;        // bits 21..22
};

#endif /* DDR_types_play_mode_H */
