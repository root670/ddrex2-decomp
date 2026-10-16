/* struct _tag_cDDR7SaveData -- 21 members, size 0x5E30, layout 36e5f2e19755.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x5F8A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR7SaveData *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: les.c (DIE 0x5F8A), les_play.c (DIE 0x141AF), reconi.c (DIE 0x22D30), onimode.c (DIE 0x2A31C), recend.c (DIE 0x37FB9), eds_select.c (DIE 0x3F994), eds_main.c (DIE 0x463D9), optscr.c (DIE 0x4AD83), eds_aid.c (DIE 0x54E3E), eds_break.c (DIE 0x5A3B4), eds_record.c (DIE 0x5DC17), optdoll.c (DIE 0x94646), dexport.c (DIE 0x9A3B7), dinit.c (DIE 0x9D773)
 */
#ifndef DDR_types__tag_cDDR7SaveData_H
#define DDR_types__tag_cDDR7SaveData_H

struct G_RANKING_W_;
struct _DDRCommonHeader;
struct _EDSSAVE_W;
struct _tag_cDDR7OniRecord1;
struct _tag_cDDR7Option;
struct _tag_cDDR7Record1;
struct machine_point_work;
struct oni_course;
struct popular;

#include "types/G_RANKING_W_.h"
#include "types/_DDRCommonHeader.h"
#include "types/_EDSSAVE_W.h"
#include "types/_tag_cDDR7OniRecord1.h"
#include "types/_tag_cDDR7Option.h"
#include "types/_tag_cDDR7Record1.h"
#include "types/machine_point_work.h"
#include "types/oni_course.h"
#include "types/popular.h"

struct _tag_cDDR7SaveData {   // size 0x5E30
    /* 0x000 */ struct _DDRCommonHeader CommonHeader;  // 0x10
    /* 0x010 */ struct _tag_cDDR7Option Option;       // 0x40
    /* 0x050 */ struct _tag_cDDR7Record1 MRecord[80];  // 0x2D00
    /* 0x2D50 */ unsigned char Information[144];      // 0x90
    /* 0x2DE0 */ unsigned int nMusic;                 // 0x4
    /* 0x2DE4 */ unsigned int nBoot;                  // 0x4
    /* 0x2DE8 */ unsigned int nPlayerType[3];         // 0xC
    /* 0x2DF4 */ unsigned int nDifficulty[5];         // 0x14
    /* 0x2E08 */ int nwork[2];                        // 0x8
    /* 0x2E10 */ unsigned char LessonWork[32];        // 0x20
    /* 0x2E30 */ struct _tag_cDDR7OniRecord1 OniRecord[32];  // 0x700
    /* 0x3530 */ struct popular popular;              // 0x4B4
    /* 0x39E4 */ // 0x4 bytes padding
    /* 0x39E8 */ struct G_RANKING_W_ high_score[30];  // 0x1E0
    /* 0x3BC8 */ struct machine_point_work machine_p;  // 0x14
    /* 0x3BDC */ unsigned int HideMusic[4];           // 0x10
    /* 0x3BEC */ unsigned int HideFlag[4];            // 0x10
    /* 0x3BFC */ unsigned int HideDoll[2];            // 0x8
    /* 0x3C04 */ struct _EDSSAVE_W EdsRecords;        // 0x238
    /* 0x3E3C */ struct oni_course oni_order[3];      // 0x330
    /* 0x416C */ struct oni_course dietprogram_order[3];  // 0x330
    /* 0x449C */ struct {   // size 0xCC8
        /* 0x000 */ unsigned int program_calorie[9];      // 0x24
        /* 0x024 */ unsigned int program_play_count[9];   // 0x24
        /* 0x048 */ unsigned int song_calorie[80][5];     // 0x640
        /* 0x688 */ unsigned int song_play_count[80][5];  // 0x640
    } diet_calorie_record[2];
    /* 0x5E2C */ // 0x4 bytes padding
};

#endif /* DDR_types__tag_cDDR7SaveData_H */
