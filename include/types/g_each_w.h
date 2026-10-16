/* struct g_each_w -- 58 members, size 0x5428C, layout 835a3afa3f84.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x7519).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct g_each_w *`.
 *
 * declared by: onimode.c (DIE 0x7519), b_anime.c (DIE 0x12792), p_anime.c (DIE 0x19C64), ani_load.c (DIE 0x1CF10), dexport.c (DIE 0x39650), eye_system.c (DIE 0x4DE34), fft_disp.c (DIE 0x5FE6F), title_demo.c (DIE 0x6A015), net.c (DIE 0x7321D), net_main.c (DIE 0x7E51F), net_read_data.c (DIE 0x97D32), net_game_main.c (DIE 0xA0CF0), workout.c (DIE 0xAFA9E), bk_disp_sub.c (DIE 0xDFA32), bk_disp.c (DIE 0xED32C), fp_msel.c (DIE 0xFF907), fp_eyetoy.c (DIE 0x10A26A), fp_chara.c (DIE 0x111438), freeplay.c (DIE 0x11EB46), fp_style.c (DIE 0x126E30), fp_res.c (DIE 0x131BFB), fp_opt.c (DIE 0x145C8E), net_sys_main.c (DIE 0x15082F), net_sys_new.c (DIE 0x15BACC), dmm_init.c (DIE 0x1913A5), dmm_main.c (DIE 0x1974A1), fp_doll.c (DIE 0x1B1A6C), net_play_main.c (DIE 0x1C0544), net_game_vs.c (DIE 0x1CEAE5), point.c (DIE 0x1E5B5C), dmm_chara.c (DIE 0x1EC2C3), fp_hand.c (DIE 0x2006BE), shop_init.c (DIE 0x2130ED), shop_main.c (DIE 0x21BBC3), shop_obj.c (DIE 0x223748), shop_disp.c (DIE 0x233785), dmm_mc.c (DIE 0x24C9CD), net_game_challenge.c (DIE 0x2707C4), adv_topmenu_obj.c (DIE 0x275BB1), adv_endless_obj.c (DIE 0x282DC1), adv_main.c (DIE 0x28F261), adv_nonstop_obj.c (DIE 0x29A3E0), tra_menu.c (DIE 0x2A62AA), tra_main.c (DIE 0x2AF555), tra_msel.c (DIE 0x2B950B), net_game_vs_win.c (DIE 0x2C2094), dmm_func.c (DIE 0x2CA40B), tra_func.c (DIE 0x2D22C3), tra_play.c (DIE 0x2DCD41), tra_res.c (DIE 0x2E298D), net_game_prg.c (DIE 0x2EE26F), ed_edit.c (DIE 0x30C03C), info.c (DIE 0x33A2D2), infoshow.c (DIE 0x34636E), kn_lfunc.c (DIE 0x3659E9), les.c (DIE 0x36E077), les_play.c (DIE 0x3778C4), les_sel_lv.c (DIE 0x380179), dmm_event_cond.c (DIE 0x3D3E20), dmm_event_exe.c (DIE 0x3DFE32), dmm_judge.c (DIE 0x3E8BF1), dmm_play.c (DIE 0x3F0638), dmm_play_course.c (DIE 0x3FB95C), dmm_qmenu.c (DIE 0x404015), dmm_result.c (DIE 0x40E1D5), dmm_select.c (DIE 0x41DA6F), dmm_style.c (DIE 0x42AC6E), opt_main.c (DIE 0x4422A7), rec_main.c (DIE 0x47290A)
 */
#ifndef DDR_types_g_each_w_H
#define DDR_types_g_each_w_H

struct eval_w;
struct play_his;
struct play_mode;
struct play_w;
struct sequence;

#include "types/eval_w.h"
#include "types/play_his.h"
#include "types/play_mode.h"
#include "types/play_w.h"
#include "types/sequence.h"

struct g_each_w {   // size 0x5428C
    /* 0x000 */ unsigned int play_time;               // 0x4
    /* 0x004 */ unsigned int game_time;               // 0x4
    /* 0x008 */ unsigned int game_time_total;         // 0x4
    /* 0x00C */ signed char select;                   // 0x1
    /* 0x00D */ signed char character;                // 0x1
    /* 0x00E */ signed char costume;                  // 0x1
    /* 0x00F */ signed char motiontype;               // 0x1
    /* 0x010 */ signed char loaded_model;             // 0x1
    /* 0x011 */ signed char loaded_texture;           // 0x1
    /* 0x012 */ signed char loaded_motion;            // 0x1
    /* 0x013 */ unsigned char play_disp_flag;         // 0x1
    /* 0x014 */ unsigned char model_disp_flag;        // 0x1
    /* 0x015 */ unsigned char gauge_disp_flag;        // 0x1
    /* 0x016 */ short cur_point;                      // 0x2
    /* 0x018 */ int cur_life;                         // 0x4
    /* 0x01C */ unsigned int score;                   // 0x4
    /* 0x020 */ unsigned int old_score;               // 0x4
    /* 0x024 */ unsigned int real_score;              // 0x4
    /* 0x028 */ unsigned int bonus;                   // 0x4
    /* 0x02C */ unsigned int old_bonus;               // 0x4
    /* 0x030 */ unsigned int challenge_score;         // 0x4
    /* 0x034 */ unsigned int real_challenge_score;    // 0x4
    /* 0x038 */ unsigned int cal;                     // 0x4
    /* 0x03C */ unsigned int old_cal;                 // 0x4
    /* 0x040 */ unsigned int real_cal;                // 0x4
    /* 0x044 */ unsigned int disp_cal;                // 0x4
    /* 0x048 */ unsigned int average_cal;             // 0x4
    /* 0x04C */ int workout_norm_cal;                 // 0x4
    /* 0x050 */ int workout_norm_minute;              // 0x4
    /* 0x054 */ int old_norm_cal;                     // 0x4
    /* 0x058 */ int old_norm_minute;                  // 0x4
    /* 0x05C */ int minimum_cal;                      // 0x4
    /* 0x060 */ unsigned char add_cal_flg;            // 0x1
    /* 0x061 */ unsigned char chk_cal_flg;            // 0x1
    /* 0x062 */ unsigned char combo_no_disp_flag;     // 0x1
    /* 0x063 */ unsigned char pad;                    // 0x1
    /* 0x064 */ unsigned int play_stage;              // 0x4
    /* 0x068 */ unsigned int decode_key1;             // 0x4
    /* 0x06C */ unsigned int decode_key2;             // 0x4
    /* 0x070 */ unsigned int decode_key3;             // 0x4
    /* 0x074 */ int used_unfair_command;              // 0x4
    /* 0x078 */ int nonstop_dead_flag;                // 0x4
    /* 0x07C */ struct play_mode mode;                // 0xC
    /* 0x088 */ struct play_his his[7];               // 0x38
    /* 0x0C0 */ struct eval_w stage_evaluation;       // 0x40
    /* 0x100 */ struct eval_w total_evaluation;       // 0x40
    /* 0x140 */ struct play_w play_work;              // 0x110
    /* 0x250 */ int total_notes;                      // 0x4
    /* 0x254 */ int total_jump;                       // 0x4
    /* 0x258 */ int total_freez;                      // 0x4
    /* 0x25C */ int category;                         // 0x4
    /* 0x260 */ int total_category;                   // 0x4
    /* 0x264 */ int ck_freeze_seq_pos[2];             // 0x8
    /* 0x26C */ struct sequence sequence_buff[6144];  // 0x54000
    /* 0x5426C */ int total_notes_all;                // 0x4
    /* 0x54270 */ int total_freez_all;                // 0x4
    /* 0x54274 */ unsigned char name[20];             // 0x14
    /* 0x54288 */ char winlose_flag;                  // 0x1
    /* 0x54289 */ // 0x3 bytes padding
};

#endif /* DDR_types_g_each_w_H */
