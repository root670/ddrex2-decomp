/* struct _tag_cOpening -- 28 members, size 0xA4, layout 50a34539d53c.
 *
 * One definition, agreed by the 1 unit that declares it: openinglogo.c (DIE 0x7B170).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOpening *`.
 *
 * declared by: openinglogo.c (DIE 0x7B170)
 */
#ifndef DDR_types__tag_cOpening_H
#define DDR_types__tag_cOpening_H

struct _tag_cFilepackData;
struct _tag_cModeData;

#include "types/_tag_cFilepackData.h"
#include "types/_tag_cModeData.h"

struct _tag_cOpening {   // size 0xA4
    /* 0x000 */ int StepOpening;                      // 0x4
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
    /* 0x03C */ struct _tag_cModeData *mode_data_table;  // 0x4
    /* 0x040 */ struct _tag_cModeData *mode_data;     // 0x4
    /* 0x044 */ struct _tag_cFilepackData tblFilepack[5];  // 0x28
    /* 0x06C */ int draw_mcwnd;                       // 0x4
    /* 0x070 */ int msg_id;                           // 0x4
    /* 0x074 */ int mc_counter;                       // 0x4
    /* 0x078 */ int is_edit_folder_load_disp;         // 0x4
    /* 0x07C */ int mc_ret_init;                      // 0x4
    /* 0x080 */ int mc_ret;                           // 0x4
    /* 0x084 */ int mc_type;                          // 0x4
    /* 0x088 */ int mc_free;                          // 0x4
    /* 0x08C */ int mc_format;                        // 0x4
    /* 0x090 */ int mc_cmd;                           // 0x4
    /* 0x094 */ int mc_result;                        // 0x4
    /* 0x098 */ int bg_read_step;                     // 0x4
    /* 0x09C */ int edit_folder_load_read_flag;       // 0x4
    /* 0x0A0 */ int ddrobjs_read_flag;                // 0x4
};

#endif /* DDR_types__tag_cOpening_H */
