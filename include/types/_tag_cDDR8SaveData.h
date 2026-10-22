/* struct _tag_cDDR8SaveData -- 30 members, size 0x1FF50, layout 57e8f78144bf.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x4065).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR8SaveData *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: onimode.c (DIE 0x4065), dexport.c (DIE 0x3DA82), dinit.c (DIE 0x41724), eye_system.c (DIE 0x4B495), info_data.c (DIE 0x595E3), fft_disp.c (DIE 0x607DE), bk_disp_sub.c (DIE 0xE42B3), bk_disp.c (DIE 0xEAEA3), fp_msel.c (DIE 0x104E61), fp_chara.c (DIE 0x117745), fp_style.c (DIE 0x12C7CB), fp_res.c (DIE 0x137FD0), fp_opt.c (DIE 0x1419A0), dmm_data.c (DIE 0x17C445), dmm_disp.c (DIE 0x1843E3), dmm_init.c (DIE 0x18E60A), fp_doll.c (DIE 0x1B728A), fp_msel_obj.c (DIE 0x1DA888), shop_init.c (DIE 0x210A7C), shop_list.c (DIE 0x2164DA), shop_obj.c (DIE 0x220522), shop_disp.c (DIE 0x2303A3), shop_func.c (DIE 0x239247), dmm_mc.c (DIE 0x249E9D), rec_nor.c (DIE 0x2599FA), adv_endless_obj.c (DIE 0x27ECD2), adv_main.c (DIE 0x28B9C8), tra_main.c (DIE 0x2B5DD4), dmm_func.c (DIE 0x2C749F), tra_func.c (DIE 0x2D7E3A), fp_qmenu.c (DIE 0x300871), info.c (DIE 0x33B73B), infoshow.c (DIE 0x342D70), les.c (DIE 0x36B9B6), les_play.c (DIE 0x372FCA), net_auth_main.c (DIE 0x3AAC78), net_cnf_main.c (DIE 0x3B5880), dmm_event.c (DIE 0x3C81B2), dmm_event_cond.c (DIE 0x3D0F0E), dmm_event_exe.c (DIE 0x3DCC59), dmm_play_course.c (DIE 0x3F872E), dmm_qmenu.c (DIE 0x4013A6), dmm_result.c (DIE 0x40CE6E), dmm_select.c (DIE 0x41A268), dmm_style.c (DIE 0x4279F7), opt_adjust.c (DIE 0x42F46A), opt_doll.c (DIE 0x434322), opt_kconfig.c (DIE 0x43847D), opt_mc.c (DIE 0x4463DE), opt_menu.c (DIE 0x44B64C), workout_usermanage.c (DIE 0x457F03), rec_hi.c (DIE 0x48052A), rec_end.c (DIE 0x4882F2), rec_hand.c (DIE 0x48D6C9)
 */
#ifndef DDR_types__tag_cDDR8SaveData_H
#define DDR_types__tag_cDDR8SaveData_H

struct _DDRCommonHeader;
struct _EDSSAVE_W;
struct _eyetoy_option;
struct _tag_cDDR8OniRecord1;
struct _tag_cDDR8Option;
struct _tag_cDDR8Record1;
struct _tag_cDDRFInfoData;
struct _tag_cNetSaveWork;
struct _tag_cPointSaveWork;
struct oni_course;
struct oni_mode;
struct popular;

#include "types/_DDRCommonHeader.h"
#include "types/_EDSSAVE_W.h"
#include "types/_eyetoy_option.h"
#include "types/_tag_cDDR8OniRecord1.h"
#include "types/_tag_cDDR8Option.h"
#include "types/_tag_cDDR8Record1.h"
#include "types/_tag_cDDRFInfoData.h"
#include "types/_tag_cNetSaveWork.h"
#include "types/_tag_cPointSaveWork.h"
#include "types/oni_course.h"
#include "types/oni_mode.h"
#include "types/popular.h"
#include "types/anon_3de85bd4740a.h"
#include "types/anon_9cfc060f8d1f.h"
#include "types/anon_b37e5ce36d96.h"

struct _tag_cDDR8SaveData {   // size 0x1FF50
    /* 0x000 */ struct _DDRCommonHeader CommonHeader;  // 0x10
    /* 0x010 */ struct _tag_cDDR8Option Option;       // 0x58
    /* 0x068 */ struct _tag_cDDR8Record1 MRecord[80];  // 0x2BC0
    /* 0x2C28 */ struct _tag_cDDRFInfoData InfoData;  // 0x510
    /* 0x3138 */ unsigned int nMusic;                 // 0x4
    /* 0x313C */ unsigned int nBoot;                  // 0x4
    /* 0x3140 */ unsigned int nPlayerType[3];         // 0xC
    /* 0x314C */ unsigned int nDifficulty[5];         // 0x14
    /* 0x3160 */ unsigned int ArrowType;              // 0x4
    /* 0x3164 */ int nwork[2];                        // 0x8
    /* 0x316C */ unsigned char LessonWork[32];        // 0x20
    /* 0x318C */ struct _tag_cDDR8OniRecord1 OniRecord[78];  // 0xC30
    /* 0x3DBC */ struct _tag_cDDR8OniRecord1 NonstopRecord[78];  // 0xC30
    /* 0x49EC */ struct popular popular;              // 0x804
    /* 0x51F0 */ unsigned int HideAppFlag[8];         // 0x20
    /* 0x5210 */ unsigned int HideAppNewFlag[8];      // 0x20
    /* 0x5230 */ unsigned int HideFlag[8];            // 0x20
    /* 0x5250 */ unsigned int HideNewFlag[8];         // 0x20
    /* 0x5270 */ struct _EDSSAVE_W EdsRecords;        // 0x1570
    /* 0x67E0 */ anon_3de85bd4740a dmm;               // 0x1300
    /* 0x7AE0 */ struct oni_mode nonstop_course[39];  // 0x1D4
    /* 0x7CB4 */ struct oni_course nonstop_order[10];  // 0xA78
    /* 0x872C */ unsigned int nMusic_on_last_unlocked;  // 0x4
    /* 0x8730 */ struct _eyetoy_option eyetoy_option;  // 0x4
    /* 0x8734 */ struct _tag_cDDR8Record1 mg_solo_MRecord[80];  // 0x2BC0
    /* 0xB2F4 */ anon_9cfc060f8d1f wk_save[2];        // 0x8
    /* 0xB2FC */ int workout_user_num;                // 0x4
    /* 0xB300 */ anon_b37e5ce36d96 workout_user[10];  // 0x14C08
    /* 0x1FF08 */ struct _tag_cPointSaveWork point_work;  // 0x8
    /* 0x1FF10 */ struct _tag_cNetSaveWork net_work;  // 0x40
};

#endif /* DDR_types__tag_cDDR8SaveData_H */
