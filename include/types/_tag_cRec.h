/* struct _tag_cRec -- 35 members, size 0x644, layout 216e5ee83e16.
 *
 * One definition, agreed by the 2 units that declare it: reconi.c (DIE 0x21D22).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cRec *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: reconi.c (DIE 0x21D22), recend.c (DIE 0x369B2)
 */
#ifndef DDR_types__tag_cRec_H
#define DDR_types__tag_cRec_H

struct _tag_cFilepackData;
struct _tag_cModeData;
struct _tag_cRecBK1;
struct _tag_cRecItem;
struct _tag_cRecOniTitleInfo;
struct _tag_cRecTitleInfo;

#include "types/_tag_cFilepackData.h"
#include "types/_tag_cModeData.h"
#include "types/_tag_cRecBK1.h"
#include "types/_tag_cRecItem.h"
#include "types/_tag_cRecOniTitleInfo.h"
#include "types/_tag_cRecTitleInfo.h"

struct _tag_cRec {   // size 0x644
    /* 0x000 */ int StepRec;                          // 0x4
    /* 0x004 */ int cWait;                            // 0x4
    /* 0x008 */ int cRepeat[2];                       // 0x8
    /* 0x010 */ int cRepeat2[2];                      // 0x8
    /* 0x018 */ int Cursor[4];                        // 0x10
    /* 0x028 */ int cWait2;                           // 0x4
    /* 0x02C */ int Step;                             // 0x4
    /* 0x030 */ int Mode;                             // 0x4
    /* 0x034 */ int NextMode;                         // 0x4
    /* 0x038 */ int bDraw;                            // 0x4
    /* 0x03C */ int bTopDown;                         // 0x4
    /* 0x040 */ int Step2;                            // 0x4
    /* 0x044 */ int init_ok;                          // 0x4
    /* 0x048 */ int control_ok;                       // 0x4
    /* 0x04C */ int nItemLetter;                      // 0x4
    /* 0x050 */ unsigned int str_base_address;        // 0x4
    /* 0x054 */ int out_str_exp_id;                   // 0x4
    /* 0x058 */ struct _tag_cModeData *mode_data_table;  // 0x4
    /* 0x05C */ struct _tag_cModeData *mode_data;     // 0x4
    /* 0x060 */ struct _tag_cRecItem item[6];         // 0x120
    /* 0x180 */ int item_select_num;                  // 0x4
    /* 0x184 */ int item_count;                       // 0x4
    /* 0x188 */ int item_state;                       // 0x4
    /* 0x18C */ struct _tag_cRecBK1 bk1[4];           // 0x60
    /* 0x1EC */ int bk1_open;                         // 0x4
    /* 0x1F0 */ int bk1_flag;                         // 0x4
    /* 0x1F4 */ int bk1_count;                        // 0x4
    /* 0x1F8 */ int bk1_fill_num;                     // 0x4
    /* 0x1FC */ struct _tag_cFilepackData tblFilepack[22];  // 0xB0
    /* 0x2AC */ struct _tag_cRecTitleInfo TitleInfo[80];  // 0x280
    /* 0x52C */ struct _tag_cRecOniTitleInfo OniTitleInfo[32];  // 0x100
    /* 0x62C */ int diet_date;                        // 0x4
    /* 0x630 */ struct {   // size 0xC
        /* 0x000 */ int year;                             // 0x4
        /* 0x004 */ int month;                            // 0x4
        /* 0x008 */ int day;                              // 0x4
    } date;
    /* 0x63C */ int diet_mode;                        // 0x4
    /* 0x640 */ int diet_swap_flag;                   // 0x4
};

#endif /* DDR_types__tag_cRec_H */
