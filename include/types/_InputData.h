/* struct _InputData -- 7 members, size 0x20, layout 24d0a0d472ef.
 *
 * One definition, agreed by the 25 units that declare it: b_anime.c (DIE 0x148E1).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _InputData *`.
 *
 * declared by: b_anime.c (DIE 0x148E1), net_game_menu.c (DIE 0xBED64), fp_chara.c (DIE 0x10F8E5), fp_style.c (DIE 0x12522D), fp_res.c (DIE 0x12FC2F), fp_opt.c (DIE 0x140754), com_keyboard.c (DIE 0x199DC2), net_win_tab.c (DIE 0x1A1B2E), net_win_search.c (DIE 0x1A6820), fp_msel_obj.c (DIE 0x1D32D1), shop_disp.c (DIE 0x22EDE8), adv_endless_obj.c (DIE 0x27CECF), adv_nonstop_obj.c (DIE 0x296057), tra_func.c (DIE 0x2D71F4), tra_play.c (DIE 0x2DF7F7), el_name.c (DIE 0x31E011), ed_edit_disp.c (DIE 0x32CE2D), infoshow.c (DIE 0x341497), les_play.c (DIE 0x3720D9), dmm_play.c (DIE 0x3EDC92), dmm_play_course.c (DIE 0x3F79C5), dmm_result.c (DIE 0x40BEE5), opt_kconfig.c (DIE 0x437927), opt_lang.c (DIE 0x43C3B1), opt_win.c (DIE 0x44F870)
 */
#ifndef DDR_types__InputData_H
#define DDR_types__InputData_H

struct _InputData {   // size 0x20
    /* 0x000 */ unsigned short player_input[4];       // 0x8
    /* 0x008 */ unsigned short player_input_trigger[4];  // 0x8
    /* 0x010 */ unsigned short player_input_released[4];  // 0x8
    /* 0x018 */ unsigned short etc;                   // 0x2
    /* 0x01A */ unsigned short etc_trigger;           // 0x2
    /* 0x01C */ unsigned short etc_released;          // 0x2
    /* 0x01E */ unsigned short padding;               // 0x2
};

#endif /* DDR_types__InputData_H */
