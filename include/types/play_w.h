/* struct play_w -- 42 members, size 0x110, layout ffd12002ab2a.
 *
 * One definition, agreed by the 69 units that declare it: onimode.c (DIE 0x3048).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_w *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: onimode.c (DIE 0x3048), b_anime.c (DIE 0x13BBA), p_anime.c (DIE 0x181C7), ani_load.c (DIE 0x1E18A), dexport.c (DIE 0x3BC95), eye_system.c (DIE 0x49031), fft_disp.c (DIE 0x6234D), title_demo.c (DIE 0x6B184), net.c (DIE 0x6F242), net_main.c (DIE 0x77CE7), net_read_data.c (DIE 0x93441), net_game_main.c (DIE 0x99CFC), workout.c (DIE 0xAC34A), bk_disp_sub.c (DIE 0xE1D34), bk_disp.c (DIE 0xE749D), fp_msel.c (DIE 0x102C61), fp_eyetoy.c (DIE 0x10CACB), fp_chara.c (DIE 0x115354), freeplay.c (DIE 0x120244), fp_style.c (DIE 0x12A29E), fp_res.c (DIE 0x135B59), fp_opt.c (DIE 0x13EA52), net_sys_main.c (DIE 0x14BDEE), net_sys_new.c (DIE 0x1566B5), dmm_init.c (DIE 0x18C1AC), dmm_main.c (DIE 0x1931C2), fp_doll.c (DIE 0x1B4F9C), net_play_main.c (DIE 0x1C2DE0), net_game_vs.c (DIE 0x1C7073), point.c (DIE 0x1E6777), dmm_chara.c (DIE 0x1E7FE4), fp_hand.c (DIE 0x202364), shop_init.c (DIE 0x20EA8F), shop_main.c (DIE 0x21D06D), shop_obj.c (DIE 0x2266F2), shop_disp.c (DIE 0x236478), dmm_mc.c (DIE 0x24662B), net_game_challenge.c (DIE 0x26B6BE), adv_topmenu_obj.c (DIE 0x277CE1), adv_endless_obj.c (DIE 0x27D0FF), adv_main.c (DIE 0x2922DF), adv_nonstop_obj.c (DIE 0x29C4E5), tra_menu.c (DIE 0x2A85BE), tra_main.c (DIE 0x2B3764), tra_msel.c (DIE 0x2BB118), net_game_vs_win.c (DIE 0x2BF21C), dmm_func.c (DIE 0x2C3CCB), tra_func.c (DIE 0x2D5298), tra_play.c (DIE 0x2DE1E3), tra_res.c (DIE 0x2E5199), net_game_prg.c (DIE 0x2E97DC), ed_edit.c (DIE 0x30A4C8), info.c (DIE 0x337E97), infoshow.c (DIE 0x3490D3), kn_lfunc.c (DIE 0x362A61), les.c (DIE 0x368F92), les_play.c (DIE 0x373E6D), les_sel_lv.c (DIE 0x381371), dmm_event_cond.c (DIE 0x3CEB09), dmm_event_exe.c (DIE 0x3DA680), dmm_judge.c (DIE 0x3E4533), dmm_play.c (DIE 0x3EB966), dmm_play_course.c (DIE 0x3F604B), dmm_qmenu.c (DIE 0x3FDBBB), dmm_result.c (DIE 0x408FEF), dmm_select.c (DIE 0x4179A4), dmm_style.c (DIE 0x424FED), opt_main.c (DIE 0x43E369), rec_main.c (DIE 0x470186)
 */
#ifndef DDR_types_play_w_H
#define DDR_types_play_w_H

struct play_hist;

#include "types/play_hist.h"
#include "types/anon_424e530946aa.h"

struct play_w {   // size 0x110
    /* 0x000 */ int music_counter;                    // 0x4
    /* 0x004 */ int beat_counter;                     // 0x4
    /* 0x008 */ int cur_p_counter;                    // 0x4
    /* 0x00C */ int last_p_counter;                   // 0x4
    /* 0x010 */ int begin_beat_count;                 // 0x4
    /* 0x014 */ int go_beat_count;                    // 0x4
    /* 0x018 */ int finish_beat_count;                // 0x4
    /* 0x01C */ int end_beat_count;                   // 0x4
    /* 0x020 */ int game_start_music_count;           // 0x4
    /* 0x024 */ int game_finish_music_count;          // 0x4
    /* 0x028 */ int back_trans_start_music_count;     // 0x4
    /* 0x02C */ int last_fs_nct;                      // 0x4
    /* 0x030 */ short last_input_count[8];            // 0x10
    /* 0x040 */ struct play_hist history[8];          // 0x60
    /* 0x0A0 */ int cur_his;                          // 0x4
    /* 0x0A4 */ int pre_nct;                          // 0x4
    /* 0x0A8 */ int cur_nct;                          // 0x4
    /* 0x0AC */ int disp_nct;                         // 0x4
    /* 0x0B0 */ int cur_great_combo;                  // 0x4
    /* 0x0B4 */ int cur_miss_combo;                   // 0x4
    /* 0x0B8 */ int max_great_combo;                  // 0x4
    /* 0x0BC */ int max_miss_combo;                   // 0x4
    /* 0x0C0 */ int miss_start_count;                 // 0x4
    /* 0x0C4 */ int cur_great_combo_total;            // 0x4
    /* 0x0C8 */ int max_great_combo_total;            // 0x4
    /* 0x0CC */ unsigned short input;                 // 0x2
    /* 0x0CE */ unsigned char dead;                   // 0x1
    /* 0x0CF */ signed char strictness;               // 0x1
    /* 0x0D0 */ short panel_count[8];                 // 0x10
    /* 0x0E0 */ short message_ct;                     // 0x2
    /* 0x0E2 */ short message_id;                     // 0x2
    /* 0x0E4 */ short meter_cur;                      // 0x2
    /* 0x0E6 */ short meter_vol;                      // 0x2
    /* 0x0E8 */ short meter_ct;                       // 0x2
    /* 0x0EA */ short offset;                         // 0x2
    /* 0x0EC */ short light_offset;                   // 0x2
    /* 0x0EE */ short meter_state;                    // 0x2
    /* 0x0F0 */ short anm_no;                         // 0x2
    /* 0x0F2 */ short dance_class;                    // 0x2
    /* 0x0F4 */ int bar_start;                        // 0x4
    /* 0x0F8 */ int bar_end;                          // 0x4
    /* 0x0FC */ anon_424e530946aa extra_arrow;        // 0x14
};

#endif /* DDR_types_play_w_H */
