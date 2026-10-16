/* struct G_INPUT_W_ -- 2 members, size 0x50, layout 756b8a9145de.
 *
 * One definition, agreed by the 25 units that declare it: b_anime.c (DIE 0x15B74).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct G_INPUT_W_ *`.
 *
 * declared by: b_anime.c (DIE 0x15B74), net_game_menu.c (DIE 0xC0AAF), fp_chara.c (DIE 0x10F80B), fp_style.c (DIE 0x125155), fp_res.c (DIE 0x12FA23), fp_opt.c (DIE 0x143DE6), com_keyboard.c (DIE 0x19A4D6), net_win_tab.c (DIE 0x1A2584), net_win_search.c (DIE 0x1A858F), fp_msel_obj.c (DIE 0x1D3103), shop_disp.c (DIE 0x2319F9), adv_endless_obj.c (DIE 0x280E98), adv_nonstop_obj.c (DIE 0x298801), tra_func.c (DIE 0x2D8C7E), tra_play.c (DIE 0x2E0198), el_name.c (DIE 0x31DE57), ed_edit_disp.c (DIE 0x32CDC1), infoshow.c (DIE 0x344765), les_play.c (DIE 0x3757D6), dmm_play.c (DIE 0x3EEBD4), dmm_play_course.c (DIE 0x3F98E9), dmm_result.c (DIE 0x40F1B9), opt_kconfig.c (DIE 0x4393E9), opt_lang.c (DIE 0x43CAD3), opt_win.c (DIE 0x45076A)
 */
#ifndef DDR_types_G_INPUT_W__H
#define DDR_types_G_INPUT_W__H

struct _InputBuffer;
struct _InputData;

#include "types/_InputBuffer.h"
#include "types/_InputData.h"

struct G_INPUT_W_ {   // size 0x50
    /* 0x000 */ struct _InputData *dp;                // 0x4
    /* 0x004 */ // 0x4 bytes padding
    /* 0x008 */ struct _InputBuffer buffer;           // 0x48
};

#endif /* DDR_types_G_INPUT_W__H */
