/* struct G_SYS_W_ -- 12 members, size 0x98, layout efbc683fe9e6.
 *
 * One definition, agreed by the 25 units that declare it: b_anime.c (DIE 0x15DCC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct G_SYS_W_ *`.
 *
 * declared by: b_anime.c (DIE 0x15DCC), net_game_menu.c (DIE 0xC0F2B), fp_chara.c (DIE 0x10FD4A), fp_style.c (DIE 0x125732), fp_res.c (DIE 0x13004A), fp_opt.c (DIE 0x14436F), com_keyboard.c (DIE 0x19A58C), net_win_tab.c (DIE 0x1A2619), net_win_search.c (DIE 0x1A8987), fp_msel_obj.c (DIE 0x1D36FD), shop_disp.c (DIE 0x232187), adv_endless_obj.c (DIE 0x28160D), adv_nonstop_obj.c (DIE 0x298CE5), tra_func.c (DIE 0x2D8FDE), tra_play.c (DIE 0x2E03EF), el_name.c (DIE 0x31E407), ed_edit_disp.c (DIE 0x32CF9B), infoshow.c (DIE 0x344B7E), les_play.c (DIE 0x375DA0), dmm_play.c (DIE 0x3EF078), dmm_play_course.c (DIE 0x3F9FA9), dmm_result.c (DIE 0x40F8EB), opt_kconfig.c (DIE 0x4396E9), opt_lang.c (DIE 0x43CB8A), opt_win.c (DIE 0x4508B7)
 */
#ifndef DDR_types_G_SYS_W__H
#define DDR_types_G_SYS_W__H

struct G_INPUT_W_;
struct tm;

#include "types/G_INPUT_W_.h"
#include "types/tm.h"

struct G_SYS_W_ {   // size 0x98
    /* 0x000 */ struct G_INPUT_W_ input_w;            // 0x50
    /* 0x050 */ struct tm start_tm;                   // 0x24
    /* 0x074 */ unsigned int v_counter;               // 0x4
    /* 0x078 */ unsigned long v_counter2;             // 0x8
    /* 0x080 */ unsigned int s_counter;               // 0x4
    /* 0x084 */ int u_counter;                        // 0x4
    /* 0x088 */ int read_time;                        // 0x4
    /* 0x08C */ int start_time;                       // 0x4
    /* 0x090 */ unsigned char read_flag;              // 0x1
    /* 0x091 */ unsigned char entry_bit;              // 0x1
    /* 0x092 */ char vpf;                             // 0x1
    /* 0x093 */ char pad[2];                          // 0x2
    /* 0x095 */ // 0x3 bytes padding
};

#endif /* DDR_types_G_SYS_W__H */
