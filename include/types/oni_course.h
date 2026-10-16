/* struct oni_course -- 10 members, size 0x10C, layout 9a8997172489.
 *
 * One definition, agreed by the 60 units that declare it: onimode.c (DIE 0x2875).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct oni_course *`.
 *
 * declared by: onimode.c (DIE 0x2875), oni_list.c (DIE 0xEE71), dexport.c (DIE 0x3A6A9), dinit.c (DIE 0x4304B), eye_system.c (DIE 0x4EA2F), info_data.c (DIE 0x5663F), fft_disp.c (DIE 0x6316F), bk_disp_sub.c (DIE 0xE0481), bk_disp.c (DIE 0xE6D0A), fp_msel.c (DIE 0x100C66), fp_chara.c (DIE 0x113026), fp_style.c (DIE 0x1287B9), fp_res.c (DIE 0x133633), fp_opt.c (DIE 0x146E98), dmm_data.c (DIE 0x17E4C7), dmm_disp.c (DIE 0x18671D), dmm_init.c (DIE 0x1921FD), fp_doll.c (DIE 0x1B3417), fp_msel_obj.c (DIE 0x1D4955), shop_init.c (DIE 0x213E2B), shop_list.c (DIE 0x2171D8), shop_obj.c (DIE 0x224995), shop_disp.c (DIE 0x2349D2), shop_func.c (DIE 0x23A342), dmm_mc.c (DIE 0x24DB9F), rec_nor.c (DIE 0x257395), net_game_challenge.c (DIE 0x26D8CA), adv_endless_obj.c (DIE 0x283A88), adv_main.c (DIE 0x2904D1), tra_main.c (DIE 0x2B0CBC), dmm_func.c (DIE 0x2CB5B9), tra_func.c (DIE 0x2D398C), fp_qmenu.c (DIE 0x2FCF39), info.c (DIE 0x333666), infoshow.c (DIE 0x3445C1), les.c (DIE 0x36C901), les_play.c (DIE 0x37560E), net_auth_main.c (DIE 0x3A6AC4), net_cnf_main.c (DIE 0x3B2959), dmm_event.c (DIE 0x3C9A95), dmm_event_cond.c (DIE 0x3D484B), dmm_event_exe.c (DIE 0x3E085D), dmm_play_course.c (DIE 0x3FC3AB), dmm_qmenu.c (DIE 0x4050F1), dmm_result.c (DIE 0x41146D), dmm_select.c (DIE 0x4143D7), dmm_style.c (DIE 0x42BC5B), opt_adjust.c (DIE 0x430794), opt_doll.c (DIE 0x434F58), opt_kconfig.c (DIE 0x43A236), opt_mc.c (DIE 0x4479D2), opt_menu.c (DIE 0x44CD17), workout_setting.c (DIE 0x45432F), workout_usermanage.c (DIE 0x458582), workout_userlist.c (DIE 0x45E4FC), workout_useredit.c (DIE 0x465210), workout_usrrpass.c (DIE 0x468E60), rec_hi.c (DIE 0x47DB41), rec_end.c (DIE 0x4858E0), rec_hand.c (DIE 0x48AC02)
 */
#ifndef DDR_types_oni_course_H
#define DDR_types_oni_course_H

struct oni_mode;

#include "types/oni_mode.h"

struct oni_course {   // size 0x10C
    /* 0x000 */ unsigned int course_allnum;           // 0x4
    /* 0x004 */ unsigned int course_defnum;           // 0x4
    /* 0x008 */ short avairable_level;                // 0x2
    /* 0x00A */ short order;                          // 0x2
    /* 0x00C */ short start_life;                     // 0x2
    /* 0x00E */ short flag;                           // 0x2
    /* 0x010 */ unsigned int stage;                   // 0x4
    /* 0x014 */ int single_steps;                     // 0x4
    /* 0x018 */ int double_steps;                     // 0x4
    /* 0x01C */ struct oni_mode mode[20];             // 0xF0
};

#endif /* DDR_types_oni_course_H */
