/* struct tm -- 9 members, size 0x24, layout 49a822cd330a.
 *
 * One definition, agreed by the 25 units that declare it: b_anime.c (DIE 0x15985).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct tm *`.
 *
 * declared by: b_anime.c (DIE 0x15985), net_game_menu.c (DIE 0xC0799), fp_chara.c (DIE 0x10F516), fp_style.c (DIE 0x124DA3), fp_res.c (DIE 0x12F7C8), fp_opt.c (DIE 0x143814), com_keyboard.c (DIE 0x19A379), net_win_tab.c (DIE 0x1A2427), net_win_search.c (DIE 0x1A8272), fp_msel_obj.c (DIE 0x1D2310), shop_disp.c (DIE 0x231751), adv_endless_obj.c (DIE 0x280A9C), adv_nonstop_obj.c (DIE 0x298554), tra_func.c (DIE 0x2D8A23), tra_play.c (DIE 0x2DFFA9), el_name.c (DIE 0x31AD17), ed_edit_disp.c (DIE 0x32CC64), infoshow.c (DIE 0x344342), les_play.c (DIE 0x374FDE), dmm_play.c (DIE 0x3EE979), dmm_play_course.c (DIE 0x3F95CD), dmm_result.c (DIE 0x40ECC2), opt_kconfig.c (DIE 0x43901E), opt_lang.c (DIE 0x43C976), opt_win.c (DIE 0x45042F)
 */
#ifndef DDR_types_tm_H
#define DDR_types_tm_H

struct tm {   // size 0x24
    /* 0x000 */ int tm_sec;                           // 0x4
    /* 0x004 */ int tm_min;                           // 0x4
    /* 0x008 */ int tm_hour;                          // 0x4
    /* 0x00C */ int tm_mday;                          // 0x4
    /* 0x010 */ int tm_mon;                           // 0x4
    /* 0x014 */ int tm_year;                          // 0x4
    /* 0x018 */ int tm_wday;                          // 0x4
    /* 0x01C */ int tm_yday;                          // 0x4
    /* 0x020 */ int tm_isdst;                         // 0x4
};

#endif /* DDR_types_tm_H */
