/* struct _tag_cLes -- 37 members, size 0x2A4, layout 190b96ac3aba.
 *
 * One definition, agreed by the 6 units that declare it: kn_ldisp.c (DIE 0x35B24C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cLes *`.
 *
 * declared by: kn_ldisp.c (DIE 0x35B24C), les_aid.c (DIE 0x35FC07), les.c (DIE 0x369A43), les_play.c (DIE 0x374557), les_sel_lv.c (DIE 0x37DA0E), les_sel_sec.c (DIE 0x384401)
 */
#ifndef DDR_types__tag_cLes_H
#define DDR_types__tag_cLes_H

struct _LESWIN_W;
struct _tag_cFilepackData;
struct _tag_cModeData;

#include "types/_LESWIN_W.h"
#include "types/_tag_cFilepackData.h"
#include "types/_tag_cModeData.h"

struct _tag_cLes {   // size 0x2A4
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
    /* 0x06C */ struct _tag_cFilepackData tblFilepack[19];  // 0x98
    /* 0x104 */ int sd_play_flag;                     // 0x4
    /* 0x108 */ int sd_called_flag;                   // 0x4
    /* 0x10C */ int sd_stopped_flag;                  // 0x4
    /* 0x110 */ int timing_cursor;                    // 0x4
    /* 0x114 */ int timing_keep_flag[3];              // 0xC
    /* 0x120 */ unsigned int timing_keep_data[3][3];  // 0x24
    /* 0x144 */ unsigned char font[4][64];            // 0x100
    /* 0x244 */ struct _LESWIN_W winp[1];             // 0x4C
    /* 0x290 */ int DispMode;                         // 0x4
    /* 0x294 */ void *lv_item;                        // 0x4
    /* 0x298 */ void *se_item;                        // 0x4
    /* 0x29C */ void *btn;                            // 0x4
    /* 0x2A0 */ unsigned int btn_obj_id;              // 0x4
};

#endif /* DDR_types__tag_cLes_H */
