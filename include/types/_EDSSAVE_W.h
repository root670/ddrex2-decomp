/* struct _EDSSAVE_W -- 5 members, size 0x1570, layout 0d9c4aa2dcab.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x547A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSSAVE_W *`.
 *
 * declared by: onimode.c (DIE 0x547A), dexport.c (DIE 0x38430), dinit.c (DIE 0x42910), eye_system.c (DIE 0x4C9D6), info_data.c (DIE 0x56CD7), fft_disp.c (DIE 0x62263), bk_disp_sub.c (DIE 0xDE2DB), bk_disp.c (DIE 0xEC0E8), fp_msel.c (DIE 0xFF5BC), fp_chara.c (DIE 0x11023C), fp_style.c (DIE 0x125BA2), fp_res.c (DIE 0x13069F), fp_opt.c (DIE 0x1449DB), dmm_data.c (DIE 0x17DDFE), dmm_disp.c (DIE 0x185D2B), dmm_init.c (DIE 0x190119), fp_doll.c (DIE 0x1B0870), fp_msel_obj.c (DIE 0x1D3ADF), shop_init.c (DIE 0x211ECD), shop_list.c (DIE 0x2170C8), shop_obj.c (DIE 0x222528), shop_disp.c (DIE 0x232565), shop_func.c (DIE 0x239E9C), dmm_mc.c (DIE 0x24B7AD), rec_nor.c (DIE 0x25A5E9), adv_endless_obj.c (DIE 0x2818F6), adv_main.c (DIE 0x28DBC5), tra_main.c (DIE 0x2AD3E8), dmm_func.c (DIE 0x2C9032), tra_func.c (DIE 0x2D942C), fp_qmenu.c (DIE 0x2FC779), info.c (DIE 0x33419A), infoshow.c (DIE 0x344FE3), les.c (DIE 0x36DF8D), les_play.c (DIE 0x37617F), net_auth_main.c (DIE 0x3ADE26), net_cnf_main.c (DIE 0x3B7C0B), dmm_event.c (DIE 0x3C94B0), dmm_event_cond.c (DIE 0x3D2753), dmm_event_exe.c (DIE 0x3DE765), dmm_play_course.c (DIE 0x3FA28F), dmm_qmenu.c (DIE 0x402DD1), dmm_result.c (DIE 0x40FBD1), dmm_select.c (DIE 0x41C5CA), dmm_style.c (DIE 0x4299E2), opt_adjust.c (DIE 0x430262), opt_doll.c (DIE 0x4352E2), opt_kconfig.c (DIE 0x4399AB), opt_mc.c (DIE 0x447506), opt_menu.c (DIE 0x44C792), workout_usermanage.c (DIE 0x458C9A), rec_hi.c (DIE 0x4810B0), rec_end.c (DIE 0x488EE1), rec_hand.c (DIE 0x48E22B)
 */
#ifndef DDR_types__EDSSAVE_W_H
#define DDR_types__EDSSAVE_W_H

struct _EDSS_PLAY_W;
struct _EDS_NONSTOP_SAVE_W;
struct _EDS_OPTION_DATA;

#include "types/_EDSS_PLAY_W.h"
#include "types/_EDS_NONSTOP_SAVE_W.h"
#include "types/_EDS_OPTION_DATA.h"

struct _EDSSAVE_W {   // size 0x1570
    /* 0x000 */ struct _EDSS_PLAY_W reg[2];           // 0xC0
    /* 0x0C0 */ unsigned int PlayFlag[128];           // 0x200
    /* 0x2C0 */ struct _EDS_OPTION_DATA option;       // 0x4
    /* 0x2C4 */ struct _EDS_NONSTOP_SAVE_W NonstopData[39];  // 0x30C
    /* 0x5D0 */ struct _EDS_NONSTOP_SAVE_W NonstopOrderData[10][20];  // 0xFA0
};

#endif /* DDR_types__EDSSAVE_W_H */
