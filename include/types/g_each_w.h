/* struct g_each_w -- 52 members, size 0x54298, layout 2f1f60995a9c.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x63B9).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct g_each_w *`.
 *
 * declared by: les.c (DIE 0x63B9), les_play.c (DIE 0xD3F6), kn_lfunc.c (DIE 0x18C30), onimode.c (DIE 0x2D212), sp_ending_d.c (DIE 0x35200), eds_select.c (DIE 0x409AE), eds_main.c (DIE 0x470A5), eds_aid.c (DIE 0x55B30), b_anime.c (DIE 0x7068F), p_anime.c (DIE 0x73925), ani_load.c (DIE 0x781D7), dexport.c (DIE 0x9ACEB)
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

struct g_each_w {   // size 0x54298
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
    /* 0x030 */ unsigned int max_score;               // 0x4
    /* 0x034 */ unsigned int old_max_score;           // 0x4
    /* 0x038 */ unsigned int max_bonus;               // 0x4
    /* 0x03C */ unsigned int old_max_bonus;           // 0x4
    /* 0x040 */ unsigned int cal;                     // 0x4
    /* 0x044 */ unsigned int old_cal;                 // 0x4
    /* 0x048 */ unsigned int real_cal;                // 0x4
    /* 0x04C */ unsigned int disp_cal;                // 0x4
    /* 0x050 */ unsigned int average_cal;             // 0x4
    /* 0x054 */ int diet_norm_cal;                    // 0x4
    /* 0x058 */ int diet_norm_minute;                 // 0x4
    /* 0x05C */ int old_norm_cal;                     // 0x4
    /* 0x060 */ int old_norm_minute;                  // 0x4
    /* 0x064 */ int minimum_cal;                      // 0x4
    /* 0x068 */ unsigned char add_cal_flg;            // 0x1
    /* 0x069 */ unsigned char chk_cal_flg;            // 0x1
    /* 0x06A */ unsigned char pad[2];                 // 0x2
    /* 0x06C */ unsigned int play_stage;              // 0x4
    /* 0x070 */ unsigned int decode_key1;             // 0x4
    /* 0x074 */ unsigned int decode_key2;             // 0x4
    /* 0x078 */ unsigned int decode_key3;             // 0x4
    /* 0x07C */ struct play_mode mode;                // 0xC
    /* 0x088 */ struct play_his his[7];               // 0x38
    /* 0x0C0 */ struct eval_w stage_evaluation;       // 0x6C
    /* 0x12C */ struct eval_w total_evaluation;       // 0x6C
    /* 0x198 */ struct play_w play_work;              // 0xEC
    /* 0x284 */ int total_notes;                      // 0x4
    /* 0x288 */ int total_jump;                       // 0x4
    /* 0x28C */ int total_freez;                      // 0x4
    /* 0x290 */ int category;                         // 0x4
    /* 0x294 */ int total_category;                   // 0x4
    /* 0x298 */ struct sequence sequence_buff[6144];  // 0x54000
};

#endif /* DDR_types_g_each_w_H */
