/* struct play_w -- 35 members, size 0xEC, layout cf4c7f634e99.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x407E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_w *`.
 *
 * declared by: les.c (DIE 0x407E), les_play.c (DIE 0xF83C), kn_lfunc.c (DIE 0x1AB54), onimode.c (DIE 0x2B6DD), sp_ending_d.c (DIE 0x338B2), eds_select.c (DIE 0x3E5DF), eds_main.c (DIE 0x44C47), eds_aid.c (DIE 0x536AC), b_anime.c (DIE 0x6EC85), p_anime.c (DIE 0x74D88), ani_load.c (DIE 0x76CAD), dexport.c (DIE 0x99024)
 */
#ifndef DDR_types_play_w_H
#define DDR_types_play_w_H

struct play_hist;

#include "types/play_hist.h"

struct play_w {   // size 0xEC
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
    /* 0x0C4 */ unsigned short input;                 // 0x2
    /* 0x0C6 */ unsigned char dead;                   // 0x1
    /* 0x0C7 */ signed char strictness;               // 0x1
    /* 0x0C8 */ short panel_count[8];                 // 0x10
    /* 0x0D8 */ short message_ct;                     // 0x2
    /* 0x0DA */ short message_id;                     // 0x2
    /* 0x0DC */ short meter_cur;                      // 0x2
    /* 0x0DE */ short meter_vol;                      // 0x2
    /* 0x0E0 */ short meter_ct;                       // 0x2
    /* 0x0E2 */ short dance_class;                    // 0x2
    /* 0x0E4 */ int bar_start;                        // 0x4
    /* 0x0E8 */ int bar_end;                          // 0x4
};

#endif /* DDR_types_play_w_H */
