/* struct g_game_w -- 80 members, size 0xAB544, layout 40a73f5f3748.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x4679).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct g_game_w *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: les.c (DIE 0x4679), les_play.c (DIE 0x13171), kn_lfunc.c (DIE 0x1B119), onimode.c (DIE 0x2BCEE), sp_ending_d.c (DIE 0x33EBF), eds_select.c (DIE 0x3EC10), eds_main.c (DIE 0x45230), eds_aid.c (DIE 0x53C95), b_anime.c (DIE 0x6F24A), p_anime.c (DIE 0x725E8), ani_load.c (DIE 0x77296), dexport.c (DIE 0x99633)
 */
#ifndef DDR_types_g_game_w_H
#define DDR_types_g_game_w_H

struct g_each_w;
struct music_info;
struct note_status;

#include "types/g_each_w.h"
#include "types/music_info.h"
#include "types/note_status.h"

struct g_game_w {   // size 0xAB544
    /* 0x000 */ short state;                          // 0x2
    /* 0x002 */ short genre;                          // 0x2
    /* 0x004 */ struct music_info *mip;               // 0x4
    /* 0x008 */ signed char start_chip;               // 0x1
    /* 0x009 */ signed char extra_chip;               // 0x1
    /* 0x00A */ signed char use_chip;                 // 0x1
    /* 0x00B */ signed char lost_chip;                // 0x1
    /* 0x00C */ short stage;                          // 0x2
    /* 0x00E */ short next_stage;                     // 0x2
    /* 0x010 */ short failed;                         // 0x2
    /* 0x012 */ short level;                          // 0x2
    /* 0x014 */ signed char game_kind;                // 0x1
    /* 0x015 */ signed char world;                    // 0x1
    /* 0x016 */ signed char nonstop;                  // 0x1
    /* 0x017 */ signed char event_mode;               // 0x1
    /* 0x018 */ signed char style;                    // 0x1
    /* 0x019 */ signed char music_group;              // 0x1
    /* 0x01A */ signed char music_select_mode;        // 0x1
    /* 0x01B */ signed char extra_stage;              // 0x1
    /* 0x01C */ signed char extra_fix;                // 0x1
    /* 0x01D */ signed char final_fix;                // 0x1
    /* 0x01E */ signed char meter_kind;               // 0x1
    /* 0x01F */ signed char roulette_stage;           // 0x1
    /* 0x020 */ signed char edit_total;               // 0x1
    /* 0x021 */ signed char roulette_total;           // 0x1
    /* 0x022 */ short music;                          // 0x2
    /* 0x024 */ signed char oni_mode;                 // 0x1
    /* 0x025 */ unsigned char oni_load_step;          // 0x1
    /* 0x026 */ short oni_next_music;                 // 0x2
    /* 0x028 */ signed char oni_nonstop_difficulty;   // 0x1
    /* 0x029 */ signed char oni_nonstop_option_selected;  // 0x1
    /* 0x02A */ signed char oni_pad[2];               // 0x2
    /* 0x02C */ signed char beginner_mode;            // 0x1
    /* 0x02D */ signed char beginner_selected;        // 0x1
    /* 0x02E */ signed char freez_selected;           // 0x1
    /* 0x02F */ signed char beginner_pad[1];          // 0x1
    /* 0x030 */ struct music_info *oni_next_mip;      // 0x4
    /* 0x034 */ struct g_each_w player[2];            // 0xA8530
    /* 0xA8564 */ signed char music_table[128];       // 0x80
    /* 0xA85E4 */ struct note_status note_status_table[300];  // 0x2EE0
    /* 0xAB4C4 */ struct {   // size 0x4
        /* 0x000 */ unsigned char old_stat;               // 0x1
        /* 0x001 */ unsigned char cur_stat;               // 0x1
        /* 0x002 */ unsigned char release_ct;             // 0x1
        /* 0x003 */ unsigned char warning;                // 0x1
    } hc_work[8];
    /* 0xAB4E4 */ int demoloop_ct;                    // 0x4
    /* 0xAB4E8 */ int mode_quit_ct[2];                // 0x8
    /* 0xAB4F0 */ int force_exit_ct[2];               // 0x8
    /* 0xAB4F8 */ int diet_play_time;                 // 0x4
    /* 0xAB4FC */ int old_play_time;                  // 0x4
    /* 0xAB500 */ int menu_num;                       // 0x4
    /* 0xAB504 */ int total_stage;                    // 0x4
    /* 0xAB508 */ int now_bpm;                        // 0x4
    /* 0xAB50C */ unsigned char *last_data_addr;      // 0x4
    /* 0xAB510 */ unsigned char *anime_data_addr;     // 0x4
    /* 0xAB514 */ unsigned char *anime_buff_addr;     // 0x4
    /* 0xAB518 */ unsigned char anime_load_flg;       // 0x1
    /* 0xAB519 */ unsigned char anime1_load_flg;      // 0x1
    /* 0xAB51A */ unsigned char anime2_load_flg;      // 0x1
    /* 0xAB51B */ unsigned char edit_name[12];        // 0xC
    /* 0xAB527 */ unsigned char diet_flg;             // 0x1
    /* 0xAB528 */ unsigned char auto_play_flg;        // 0x1
    /* 0xAB529 */ unsigned char caution_flg;          // 0x1
    /* 0xAB52A */ unsigned char mode_quit_flg;        // 0x1
    /* 0xAB52B */ unsigned char lib_loaded;           // 0x1
    /* 0xAB52C */ unsigned char force_exit_flg;       // 0x1
    /* 0xAB52D */ unsigned char music_stop_flg;       // 0x1
    /* 0xAB52E */ unsigned char train_state;          // 0x1
    /* 0xAB52F */ unsigned char lesson_flag;          // 0x1
    /* 0xAB530 */ unsigned char lesson_auto_play_flag;  // 0x1
    /* 0xAB531 */ unsigned char lesson_pad[2];        // 0x2
    /* 0xAB533 */ unsigned char oni_load_start0;      // 0x1
    /* 0xAB534 */ unsigned char oni_load_start1;      // 0x1
    /* 0xAB535 */ unsigned char oni_load_end0;        // 0x1
    /* 0xAB536 */ unsigned char oni_load_end1;        // 0x1
    /* 0xAB537 */ unsigned char oni_order_step;       // 0x1
    /* 0xAB538 */ unsigned char oni_order_stage;      // 0x1
    /* 0xAB539 */ unsigned char oni_order_cursor;     // 0x1
    /* 0xAB53A */ unsigned char oni_order_top_stage;  // 0x1
    /* 0xAB53B */ unsigned char temp_sqk[2];          // 0x2
    /* 0xAB53D */ unsigned char disp_seltu_flag;      // 0x1
    /* 0xAB53E */ unsigned char temp_pad[1];          // 0x1
    /* 0xAB53F */ unsigned char endless_flag;         // 0x1
    /* 0xAB540 */ unsigned char endless_pad[3];       // 0x3
    /* 0xAB543 */ // 0x1 bytes padding
};

#endif /* DDR_types_g_game_w_H */
