/* struct _tag_cLes -- 32 members, size 0x284, layout d5e4f61738f1.
 *
 * One definition, agreed by the 5 units that declare it: les_sel_lv.c (DIE 0xE25).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLes *`.
 *
 * declared by: les_sel_lv.c (DIE 0xE25), les.c (DIE 0x2F51), les_sel_sec.c (DIE 0x9432), les_play.c (DIE 0xDEF3), kn_ldisp.c (DIE 0x1D0A6)
 */
#ifndef DDR_types__tag_cLes_H
#define DDR_types__tag_cLes_H

struct _LESWIN_W;
struct _tag_cFilepackData;
struct _tag_cModeData;

#include "types/_LESWIN_W.h"
#include "types/_tag_cFilepackData.h"
#include "types/_tag_cModeData.h"

struct _tag_cLes {   // size 0x284
    /* 0x000 */ int StepLes;                          // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int Cursor[4];                        // 0x10
    /* 0x020 */ int Step;                             // 0x4
    /* 0x024 */ int Mode;                             // 0x4
    /* 0x028 */ int NextMode;                         // 0x4
    /* 0x02C */ int bDraw;                            // 0x4
    /* 0x030 */ int bTopDown;                         // 0x4
    /* 0x034 */ int Step2;                            // 0x4
    /* 0x038 */ int init_ok;                          // 0x4
    /* 0x03C */ int sd_dir;                           // 0x4
    /* 0x040 */ int nItemLetter;                      // 0x4
    /* 0x044 */ unsigned char **ExpKanji;             // 0x4
    /* 0x048 */ struct _tag_cModeData *mode_data_table;  // 0x4
    /* 0x04C */ struct _tag_cModeData *mode_data;     // 0x4
    /* 0x050 */ int base_tex_id;                      // 0x4
    /* 0x054 */ int level;                            // 0x4
    /* 0x058 */ int section;                          // 0x4
    /* 0x05C */ int play_pid;                         // 0x4
    /* 0x060 */ int ret_dance_play_step;              // 0x4
    /* 0x064 */ int music_label;                      // 0x4
    /* 0x068 */ int loaded_music_label;               // 0x4
    /* 0x06C */ struct _tag_cFilepackData tblFilepack[10];  // 0x50
    /* 0x0BC */ int sd_play_flag;                     // 0x4
    /* 0x0C0 */ int sd_called_flag;                   // 0x4
    /* 0x0C4 */ int sd_stopped_flag;                  // 0x4
    /* 0x0C8 */ int timing_cursor;                    // 0x4
    /* 0x0CC */ int timing_keep_flag[3];              // 0xC
    /* 0x0D8 */ unsigned int timing_keep_data[3][3];  // 0x24
    /* 0x0FC */ unsigned char font[4][64];            // 0x100
    /* 0x1FC */ struct _LESWIN_W winp[2];             // 0x88
};

#endif /* DDR_types__tag_cLes_H */
