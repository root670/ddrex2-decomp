/* struct _EDSS_PLAY_W -- 2 members, size 0x60, layout b76533438544.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x2FD5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSS_PLAY_W *`.
 *
 * declared by: onimode.c (DIE 0x2FD5), dexport.c (DIE 0x3D25F), dinit.c (DIE 0x40E07), eye_system.c (DIE 0x4AC28), info_data.c (DIE 0x591DF), fft_disp.c (DIE 0x65CF4), bk_disp_sub.c (DIE 0xE38CA), bk_disp.c (DIE 0xEA659), fp_msel.c (DIE 0x1045D7), fp_chara.c (DIE 0x116DAB), fp_style.c (DIE 0x12BE7C), fp_res.c (DIE 0x13758B), fp_opt.c (DIE 0x140CBE), dmm_data.c (DIE 0x17A7B1), dmm_disp.c (DIE 0x183AF5), dmm_init.c (DIE 0x18DC5A), fp_doll.c (DIE 0x1B6987), fp_msel_obj.c (DIE 0x1D9C40), shop_init.c (DIE 0x2100F1), shop_list.c (DIE 0x215C7F), shop_obj.c (DIE 0x21FBFB), shop_disp.c (DIE 0x22F3FC), shop_func.c (DIE 0x2389EC), dmm_mc.c (DIE 0x2494EF), rec_nor.c (DIE 0x259147), adv_endless_obj.c (DIE 0x27D87C), adv_main.c (DIE 0x293B08), tra_main.c (DIE 0x2B5334), dmm_func.c (DIE 0x2C6AF0), tra_func.c (DIE 0x2D755A), fp_qmenu.c (DIE 0x2FFFDD), info.c (DIE 0x33AD03), infoshow.c (DIE 0x341954), les.c (DIE 0x36B51B), les_play.c (DIE 0x372546), net_auth_main.c (DIE 0x3AA12E), net_cnf_main.c (DIE 0x3B527E), dmm_event.c (DIE 0x3C762D), dmm_event_cond.c (DIE 0x3D0597), dmm_event_exe.c (DIE 0x3DC2E2), dmm_play_course.c (DIE 0x3F7CFC), dmm_qmenu.c (DIE 0x3FF719), dmm_result.c (DIE 0x40C15D), dmm_select.c (DIE 0x4197CF), dmm_style.c (DIE 0x426E24), opt_adjust.c (DIE 0x42EC1E), opt_doll.c (DIE 0x433F42), opt_kconfig.c (DIE 0x437B7B), opt_mc.c (DIE 0x445B6F), opt_menu.c (DIE 0x44ADB9), workout_usermanage.c (DIE 0x457B23), rec_hi.c (DIE 0x47FD4E), rec_end.c (DIE 0x487B16), rec_hand.c (DIE 0x48CEED)
 */
#ifndef DDR_types__EDSS_PLAY_W_H
#define DDR_types__EDSS_PLAY_W_H

struct _EDSS_DATA_W;

#include "types/_EDSS_DATA_W.h"

struct _EDSS_PLAY_W {   // size 0x60
    /* 0x000 */ struct _EDSS_DATA_W p_single[3];      // 0x30
    /* 0x030 */ struct _EDSS_DATA_W p_double[3];      // 0x30
};

#endif /* DDR_types__EDSS_PLAY_W_H */
