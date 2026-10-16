/* struct _EDS_NONSTOP_SAVE_W -- 3 members, size 0x14, layout 6dc2ab8f8af2.
 *
 * One definition, agreed by the 55 units that declare it: onimode.c (DIE 0x50E8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDS_NONSTOP_SAVE_W *`.
 *
 * declared by: onimode.c (DIE 0x50E8), dexport.c (DIE 0x37F05), dinit.c (DIE 0x425E5), eye_system.c (DIE 0x4C52F), info_data.c (DIE 0x56B5D), fft_disp.c (DIE 0x619E4), bk_disp_sub.c (DIE 0xDDB80), bk_disp.c (DIE 0xEBC1A), fp_msel.c (DIE 0xFDEC3), fp_chara.c (DIE 0x10FADD), fp_style.c (DIE 0x125377), fp_res.c (DIE 0x12FD79), fp_opt.c (DIE 0x144088), dmm_data.c (DIE 0x17D703), dmm_disp.c (DIE 0x185797), dmm_init.c (DIE 0x18F847), fp_doll.c (DIE 0x1B03E5), fp_msel_obj.c (DIE 0x1D3237), shop_init.c (DIE 0x211936), shop_list.c (DIE 0x216E0E), shop_obj.c (DIE 0x221EDD), shop_disp.c (DIE 0x231D38), shop_func.c (DIE 0x239BBE), dmm_mc.c (DIE 0x24B182), rec_nor.c (DIE 0x25A32F), adv_endless_obj.c (DIE 0x280F28), adv_main.c (DIE 0x28D5C6), adv_nonstop_obj.c (DIE 0x298767), tra_main.c (DIE 0x2B6C70), dmm_func.c (DIE 0x2C87E1), tra_func.c (DIE 0x2D8D32), fp_qmenu.c (DIE 0x2FC2B2), info.c (DIE 0x3339CE), infoshow.c (DIE 0x3448D2), les.c (DIE 0x36CCDB), les_play.c (DIE 0x3758AE), net_auth_main.c (DIE 0x3AD137), net_cnf_main.c (DIE 0x3B73EE), dmm_event.c (DIE 0x3C9099), dmm_event_cond.c (DIE 0x3D201F), dmm_event_exe.c (DIE 0x3DE0B9), dmm_play_course.c (DIE 0x3F9979), dmm_qmenu.c (DIE 0x402547), dmm_result.c (DIE 0x40F249), dmm_select.c (DIE 0x41BE1E), dmm_style.c (DIE 0x429134), opt_adjust.c (DIE 0x42FF60), opt_doll.c (DIE 0x435120), opt_kconfig.c (DIE 0x439455), opt_mc.c (DIE 0x44707D), opt_menu.c (DIE 0x44C298), workout_usermanage.c (DIE 0x458B20), rec_hi.c (DIE 0x480DF6), rec_end.c (DIE 0x488C27), rec_hand.c (DIE 0x48DF71)
 */
#ifndef DDR_types__EDS_NONSTOP_SAVE_W_H
#define DDR_types__EDS_NONSTOP_SAVE_W_H

struct _EDS_OPTION_DATA;
struct _EDS_RANK_DATA;

#include "types/_EDS_OPTION_DATA.h"
#include "types/_EDS_RANK_DATA.h"

struct _EDS_NONSTOP_SAVE_W {   // size 0x14
    /* 0x000 */ int music_id;                         // 0x4
    /* 0x004 */ struct _EDS_RANK_DATA recourd[2];     // 0x8
    /* 0x00C */ struct _EDS_OPTION_DATA flag[2];      // 0x8
};

#endif /* DDR_types__EDS_NONSTOP_SAVE_W_H */
