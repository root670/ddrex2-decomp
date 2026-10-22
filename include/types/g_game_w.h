/* struct g_game_w -- 100 members, size 0xACDC4, layout 8eda8a4359de.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x63BF).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct g_game_w *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: onimode.c (DIE 0x63BF), b_anime.c (DIE 0x116CC), p_anime.c (DIE 0x18B9E), ani_load.c (DIE 0x1BE4A), dexport.c (DIE 0x3851A), eye_system.c (DIE 0x4CB9E), fft_disp.c (DIE 0x5EA67), title_demo.c (DIE 0x68F2B), net.c (DIE 0x72157), net_main.c (DIE 0x7D2B0), net_read_data.c (DIE 0x96B9E), net_game_main.c (DIE 0x9FB14), workout.c (DIE 0xAE9D8), bk_disp_sub.c (DIE 0xDE7F9), bk_disp.c (DIE 0xEC1D2), fp_msel.c (DIE 0xFE4F6), fp_eyetoy.c (DIE 0x1091A4), fp_chara.c (DIE 0x110326), freeplay.c (DIE 0x11D9FC), fp_style.c (DIE 0x125CD6), fp_res.c (DIE 0x130891), fp_opt.c (DIE 0x144B0D), net_sys_main.c (DIE 0x14F69B), net_sys_new.c (DIE 0x15A8AD), dmm_init.c (DIE 0x19024B), dmm_main.c (DIE 0x1963DB), fp_doll.c (DIE 0x1B095A), net_play_main.c (DIE 0x1BEDC5), net_game_vs.c (DIE 0x1CD8A2), point.c (DIE 0x1E4A16), dmm_chara.c (DIE 0x1EB1FD), fp_hand.c (DIE 0x1FF5D1), shop_init.c (DIE 0x211FB7), shop_main.c (DIE 0x21AAFD), shop_obj.c (DIE 0x222612), shop_disp.c (DIE 0x23264F), dmm_mc.c (DIE 0x24B897), net_game_challenge.c (DIE 0x26F4E2), adv_topmenu_obj.c (DIE 0x274A69), adv_endless_obj.c (DIE 0x281B2A), adv_main.c (DIE 0x28DE9B), adv_nonstop_obj.c (DIE 0x29924E), tra_menu.c (DIE 0x2A50B2), tra_main.c (DIE 0x2AD917), tra_msel.c (DIE 0x2B8445), net_game_vs_win.c (DIE 0x2C0F24), dmm_func.c (DIE 0x2C911C), tra_func.c (DIE 0x2D1169), tra_play.c (DIE 0x2DBC7B), tra_res.c (DIE 0x2E1795), net_game_prg.c (DIE 0x2ED096), ed_edit.c (DIE 0x30AF2C), info.c (DIE 0x339168), infoshow.c (DIE 0x3451CA), kn_lfunc.c (DIE 0x3648FD), les.c (DIE 0x36CEC7), les_play.c (DIE 0x37644D), les_sel_lv.c (DIE 0x37EFFB), dmm_event_cond.c (DIE 0x3D2963), dmm_event_exe.c (DIE 0x3DE951), dmm_judge.c (DIE 0x3E7B2B), dmm_play.c (DIE 0x3EF3DD), dmm_play_course.c (DIE 0x3FA49F), dmm_qmenu.c (DIE 0x402EBB), dmm_result.c (DIE 0x40FDE1), dmm_select.c (DIE 0x41C7DA), dmm_style.c (DIE 0x429B14), opt_main.c (DIE 0x441085), rec_main.c (DIE 0x471844)
 */
#ifndef DDR_types_g_game_w_H
#define DDR_types_g_game_w_H

struct g_each_w;
struct music_info;
struct note_status;

#include "types/g_each_w.h"
#include "types/music_info.h"
#include "types/note_status.h"
#include "types/anon_2e94f6ba7a86.h"
#include "types/anon_5e4dacf47895.h"

struct g_game_w {   // size 0xACDC4
    /* 0x000 */ short state;                          // 0x2
    /* 0x002 */ short genre;                          // 0x2
    /* 0x004 */ struct music_info *mip;               // 0x4
    /* 0x008 */ short stage;                          // 0x2
    /* 0x00A */ short next_stage;                     // 0x2
    /* 0x00C */ short failed;                         // 0x2
    /* 0x00E */ short level;                          // 0x2
    /* 0x010 */ signed char game_kind;                // 0x1
    /* 0x011 */ signed char world;                    // 0x1
    /* 0x012 */ signed char oni_nonstop_course_id;    // 0x1
    /* 0x013 */ signed char event_mode;               // 0x1
    /* 0x014 */ signed char event_two_flag;           // 0x1
    /* 0x015 */ signed char style;                    // 0x1
    /* 0x016 */ signed char music_group;              // 0x1
    /* 0x017 */ signed char music_select_mode;        // 0x1
    /* 0x018 */ signed char meter_kind;               // 0x1
    /* 0x019 */ // 0x1 bytes padding
    /* 0x01A */ short music;                          // 0x2
    /* 0x01C */ signed char oni_nonstop_mode;         // 0x1
    /* 0x01D */ unsigned char oni_load_step;          // 0x1
    /* 0x01E */ signed char oni_nonstop_difficulty;   // 0x1
    /* 0x01F */ signed char use_oni_gauge;            // 0x1
    /* 0x020 */ signed char beginner_mode;            // 0x1
    /* 0x021 */ signed char beginner_selected;        // 0x1
    /* 0x022 */ signed char freez_selected;           // 0x1
    /* 0x023 */ signed char judge_invalid;            // 0x1
    /* 0x024 */ short oni_next_music;                 // 0x2
    /* 0x026 */ // 0x2 bytes padding
    /* 0x028 */ struct music_info *oni_next_mip;      // 0x4
    /* 0x02C */ struct g_each_w player[2];            // 0xA8518
    /* 0xA8544 */ signed char music_table[128];       // 0x80
    /* 0xA85C4 */ struct note_status note_status_table[300];  // 0x2EE0
    /* 0xAB4A4 */ anon_2e94f6ba7a86 hc_work[8];       // 0x20
    /* 0xAB4C4 */ int mode_quit_ct[2];                // 0x8
    /* 0xAB4CC */ int force_exit_ct[2];               // 0x8
    /* 0xAB4D4 */ int workout_play_time;              // 0x4
    /* 0xAB4D8 */ int old_play_time;                  // 0x4
    /* 0xAB4DC */ int menu_num;                       // 0x4
    /* 0xAB4E0 */ int total_stage;                    // 0x4
    /* 0xAB4E4 */ int now_bpm;                        // 0x4
    /* 0xAB4E8 */ unsigned char *last_data_addr;      // 0x4
    /* 0xAB4EC */ unsigned char edit_name[12];        // 0xC
    /* 0xAB4F8 */ unsigned char workout_flg;          // 0x1
    /* 0xAB4F9 */ unsigned char workout_step_flg;     // 0x1
    /* 0xAB4FA */ unsigned char auto_play_flg[2];     // 0x2
    /* 0xAB4FC */ unsigned char caution_flg;          // 0x1
    /* 0xAB4FD */ unsigned char mode_quit_flg;        // 0x1
    /* 0xAB4FE */ unsigned char lib_loaded;           // 0x1
    /* 0xAB4FF */ unsigned char force_exit_flg;       // 0x1
    /* 0xAB500 */ unsigned char train_state;          // 0x1
    /* 0xAB501 */ unsigned char padding[3];           // 0x3
    /* 0xAB504 */ unsigned int lesson_flag : 8;       // bits 0..7
    /* 0xAB504 */ unsigned int lesson_auto_play_flag : 8;  // bits 8..15
    /* 0xAB504 */ unsigned int lesson_skip_selecter_flag : 1;  // bits 16..16
    /* 0xAB508 */ unsigned int dmm_retry;             // 0x4
    /* 0xAB50C */ unsigned char oni_load_start0;      // 0x1
    /* 0xAB50D */ unsigned char oni_load_start1;      // 0x1
    /* 0xAB50E */ unsigned char oni_load_end0;        // 0x1
    /* 0xAB50F */ unsigned char oni_load_end1;        // 0x1
    /* 0xAB510 */ unsigned char oni_order_step;       // 0x1
    /* 0xAB511 */ unsigned char oni_order_stage;      // 0x1
    /* 0xAB512 */ unsigned char oni_order_cursor;     // 0x1
    /* 0xAB513 */ unsigned char oni_order_top_stage;  // 0x1
    /* 0xAB514 */ unsigned char oni_order_selopt;     // 0x1
    /* 0xAB515 */ unsigned char anime1_load_flg;      // 0x1
    /* 0xAB516 */ unsigned char anime2_load_flg;      // 0x1
    /* 0xAB517 */ unsigned char temp_sqk[2];          // 0x2
    /* 0xAB519 */ unsigned char endless_flag;         // 0x1
    /* 0xAB51A */ unsigned char eyetoy_flag;          // 0x1
    /* 0xAB51B */ unsigned char dancemaster_flag;     // 0x1
    /* 0xAB51C */ unsigned char step_mark_color;      // 0x1
    /* 0xAB51D */ unsigned char hand_solo_seq_kind;   // 0x1
    /* 0xAB51E */ unsigned char is_course_exit;       // 0x1
    /* 0xAB51F */ unsigned char to_opt_select;        // 0x1
    /* 0xAB520 */ unsigned char is_new_clothes;       // 0x1
    /* 0xAB521 */ unsigned char nononi_msel_flag;     // 0x1
    /* 0xAB522 */ unsigned char select_randaom_flag;  // 0x1
    /* 0xAB523 */ unsigned char fp_cur_back_flag;     // 0x1
    /* 0xAB524 */ unsigned char lib_sel_num;          // 0x1
    /* 0xAB525 */ // 0x3 bytes padding
    /* 0xAB528 */ unsigned int bar_state;             // 0x4
    /* 0xAB52C */ int rloadtex_num;                   // 0x4
    /* 0xAB530 */ int rload_next_step;                // 0x4
    /* 0xAB534 */ char quit_course_flag;              // 0x1
    /* 0xAB535 */ char nonstop_selopt_flag;           // 0x1
    /* 0xAB536 */ unsigned char dancer_id[3];         // 0x3
    /* 0xAB539 */ // 0x3 bytes padding
    /* 0xAB53C */ anon_5e4dacf47895 line_data[16];    // 0x1840
    /* 0xACD7C */ int line_speed;                     // 0x4
    /* 0xACD80 */ int bk_ef_kind;                     // 0x4
    /* 0xACD84 */ int bk_ef_colset[3];                // 0xC
    /* 0xACD90 */ int bk_ef_type;                     // 0x4
    /* 0xACD94 */ int bk_ef_reset;                    // 0x4
    /* 0xACD98 */ int event_result_exit_flag;         // 0x4
    /* 0xACD9C */ int network_flag;                   // 0x4
    /* 0xACDA0 */ int read_end_flag;                  // 0x4
    /* 0xACDA4 */ int online_play_mode;               // 0x4
    /* 0xACDA8 */ int advance_flag;                   // 0x4
    /* 0xACDAC */ int advance_mode;                   // 0x4
    /* 0xACDB0 */ int endless_select_difficulty;      // 0x4
    /* 0xACDB4 */ int nonstop_dance_meter;            // 0x4
    /* 0xACDB8 */ int network_get_data;               // 0x4
    /* 0xACDBC */ int network_get_data_step;          // 0x4
    /* 0xACDC0 */ int network_start_data_step;        // 0x4
};

#endif /* DDR_types_g_game_w_H */
