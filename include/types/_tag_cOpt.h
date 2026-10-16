/* struct _tag_cOpt -- 51 members, size 0x17C, layout 7076ccdaac02.
 *
 * One definition, agreed by the 3 units that declare it: optscr.c (DIE 0x4B499).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOpt *`.
 *
 * declared by: optscr.c (DIE 0x4B499), optlang.c (DIE 0x61268), optdoll.c (DIE 0x939AF)
 */
#ifndef DDR_types__tag_cOpt_H
#define DDR_types__tag_cOpt_H

struct _tag_cFilepackData;
struct _tag_cModeData;

#include "types/_tag_cFilepackData.h"
#include "types/_tag_cModeData.h"

struct _tag_cOpt {   // size 0x17C
    /* 0x000 */ int StepOpt;                          // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int cRepeat2[2];                      // 0x8
    /* 0x018 */ int Cursor[4];                        // 0x10
    /* 0x028 */ int Step;                             // 0x4
    /* 0x02C */ int Mode;                             // 0x4
    /* 0x030 */ int NextMode;                         // 0x4
    /* 0x034 */ int bDraw;                            // 0x4
    /* 0x038 */ int bTopDown;                         // 0x4
    /* 0x03C */ int Step2;                            // 0x4
    /* 0x040 */ int init_ok;                          // 0x4
    /* 0x044 */ int sd_dir;                           // 0x4
    /* 0x048 */ int title_step;                       // 0x4
    /* 0x04C */ int title_count;                      // 0x4
    /* 0x050 */ int nItemLetter;                      // 0x4
    /* 0x054 */ unsigned int str_base_address;        // 0x4
    /* 0x058 */ int out_str_exp_id;                   // 0x4
    /* 0x05C */ int is_draw_nest_button;              // 0x4
    /* 0x060 */ struct _tag_cModeData *mode_data_table;  // 0x4
    /* 0x064 */ struct _tag_cModeData *mode_data;     // 0x4
    /* 0x068 */ int item_bright[9];                   // 0x24
    /* 0x08C */ int item_select_num;                  // 0x4
    /* 0x090 */ int item_bright_delay[9];             // 0x24
    /* 0x0B4 */ int item_bright_count;                // 0x4
    /* 0x0B8 */ int item_bright_mode;                 // 0x4
    /* 0x0BC */ int subtitle_flag;                    // 0x4
    /* 0x0C0 */ int black_tile_rate;                  // 0x4
    /* 0x0C4 */ int black_tile_mode;                  // 0x4
    /* 0x0C8 */ int black_tile_flag;                  // 0x4
    /* 0x0CC */ int black_tile_count;                 // 0x4
    /* 0x0D0 */ int black_tile_open;                  // 0x4
    /* 0x0D4 */ float orange_arrow_x;                 // 0x4
    /* 0x0D8 */ float orange_arrow_y;                 // 0x4
    /* 0x0DC */ float orange_arrow_xn;                // 0x4
    /* 0x0E0 */ float orange_arrow_yn;                // 0x4
    /* 0x0E4 */ int orange_arrow_step;                // 0x4
    /* 0x0E8 */ int orange_arrow_count;               // 0x4
    /* 0x0EC */ int orange_arrow_angle;               // 0x4
    /* 0x0F0 */ int orange_arrow_zangle;              // 0x4
    /* 0x0F4 */ int orange_arrow_zanglen;             // 0x4
    /* 0x0F8 */ int ddrmax_count;                     // 0x4
    /* 0x0FC */ int ddrmax_type;                      // 0x4
    /* 0x100 */ struct _tag_cFilepackData tblFilepack[12];  // 0x60
    /* 0x160 */ int frame_cursor_counter;             // 0x4
    /* 0x164 */ int lang_butt_tex_id;                 // 0x4
    /* 0x168 */ int lang_font_tex_id;                 // 0x4
    /* 0x16C */ int lang_enable_cancel;               // 0x4
    /* 0x170 */ int optlang_exit_flag;                // 0x4
    /* 0x174 */ int putscore2_mode;                   // 0x4
    /* 0x178 */ int doll_new_mode;                    // 0x4
};

#endif /* DDR_types__tag_cOpt_H */
