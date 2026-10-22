/* struct _tag_cInfo -- 46 members, size 0x370, layout 64dc4d33051b.
 *
 * One definition, agreed by the 3 units that declare it: infosel.c (DIE 0x32ED8B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cInfo *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: infosel.c (DIE 0x32ED8B), info.c (DIE 0x33763C), infoshow.c (DIE 0x341D2F)
 */
#ifndef DDR_types__tag_cInfo_H
#define DDR_types__tag_cInfo_H

struct _COM_SCROLLBAR_WORK;
struct _tag_cCoCursor01;
struct _tag_cFilepackData;
struct _tag_cIdm5FileHeader;
struct _tag_cInfoScrBar;
struct _tag_cInfoText;
struct _tag_cInfoTitle;
struct _tag_cModeData;

#include "types/_COM_SCROLLBAR_WORK.h"
#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cFilepackData.h"
#include "types/_tag_cIdm5FileHeader.h"
#include "types/_tag_cInfoScrBar.h"
#include "types/_tag_cInfoText.h"
#include "types/_tag_cInfoTitle.h"
#include "types/_tag_cModeData.h"
#include "types/anon_09669fc426c8.h"

struct _tag_cInfo {   // size 0x370
    /* 0x000 */ int StepInfo;                         // 0x4
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
    /* 0x04C */ struct _tag_cModeData *mode_data_table;  // 0x4
    /* 0x050 */ struct _tag_cModeData *mode_data;     // 0x4
    /* 0x054 */ struct _tag_cFilepackData tex_data[33];  // 0x108
    /* 0x15C */ int free_tex_id;                      // 0x4
    /* 0x160 */ struct _tag_cInfoText *pInfoText;     // 0x4
    /* 0x164 */ int nInfoText;                        // 0x4
    /* 0x168 */ struct _tag_cIdm5FileHeader *text_file;  // 0x4
    /* 0x16C */ struct _tag_cInfoTitle Title[11];     // 0x134
    /* 0x2A0 */ int cur_seg;                          // 0x4
    /* 0x2A4 */ int cur_off;                          // 0x4
    /* 0x2A8 */ int title_move_counter[2];            // 0x8
    /* 0x2B0 */ int title_move_mode[2];               // 0x8
    /* 0x2B8 */ int title_control_flag;               // 0x4
    /* 0x2BC */ int info_x;                           // 0x4
    /* 0x2C0 */ int info_move_counter;                // 0x4
    /* 0x2C4 */ int info_move_mode;                   // 0x4
    /* 0x2C8 */ unsigned int sd_poll_step;            // 0x4
    /* 0x2CC */ unsigned int sd_poll_end;             // 0x4
    /* 0x2D0 */ unsigned int sd_poll_nop;             // 0x4
    /* 0x2D4 */ unsigned int sd_play_now;             // 0x4
    /* 0x2D8 */ unsigned int sd_play_next;            // 0x4
    /* 0x2DC */ unsigned int sd_std_music_id;         // 0x4
    /* 0x2E0 */ int open_se_flag;                     // 0x4
    /* 0x2E4 */ struct _tag_cInfoScrBar scr_bar;      // 0x24
    /* 0x308 */ int dancer_load_flag;                 // 0x4
    /* 0x30C */ int dance_master_disp_flag;           // 0x4
    /* 0x310 */ int ending_list_disp_flag;            // 0x4
    /* 0x314 */ int info_type;                        // 0x4
    /* 0x318 */ struct _COM_SCROLLBAR_WORK sb;        // 0x28
    /* 0x340 */ struct _tag_cCoCursor01 cur_left_w;   // 0xC
    /* 0x34C */ struct _tag_cCoCursor01 cur_right_w;  // 0xC
    /* 0x358 */ anon_09669fc426c8 extra_arrow_w;      // 0x18
};

#endif /* DDR_types__tag_cInfo_H */
