/* struct _InputBuffer -- 2 members, size 0x48, layout 0ddcfc3ef1a0.
 *
 * One definition, agreed by the 25 units that declare it: b_anime.c (DIE 0x14D36).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _InputBuffer *`.
 *
 * declared by: b_anime.c (DIE 0x14D36), net_game_menu.c (DIE 0xBF19D), fp_chara.c (DIE 0x117346), fp_style.c (DIE 0x12C418), fp_res.c (DIE 0x137C1D), fp_opt.c (DIE 0x1413D1), com_keyboard.c (DIE 0x19A03A), net_win_tab.c (DIE 0x1A1E3C), net_win_search.c (DIE 0x1A707D), fp_msel_obj.c (DIE 0x1DA783), shop_disp.c (DIE 0x22FFF0), adv_endless_obj.c (DIE 0x27EB34), adv_nonstop_obj.c (DIE 0x296E2F), tra_func.c (DIE 0x2D7A61), tra_play.c (DIE 0x2DFA63), el_name.c (DIE 0x31F953), ed_edit_disp.c (DIE 0x32DDC5), infoshow.c (DIE 0x3424A7), les_play.c (DIE 0x372CA0), dmm_play.c (DIE 0x3EE134), dmm_play_course.c (DIE 0x3F8629), dmm_result.c (DIE 0x40CC1A), opt_kconfig.c (DIE 0x43839C), opt_lang.c (DIE 0x43C58B), opt_win.c (DIE 0x44FB07)
 */
#ifndef DDR_types__InputBuffer_H
#define DDR_types__InputBuffer_H

struct _InputData;

#include "types/_InputData.h"

struct _InputBuffer {   // size 0x48
    /* 0x000 */ unsigned long current_buffer;         // 0x8
    /* 0x008 */ struct _InputData data[2];            // 0x40
};

#endif /* DDR_types__InputBuffer_H */
