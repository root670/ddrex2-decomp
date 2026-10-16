/* struct _tag_cDDR8SaveData -- 30 members, size 0x1FF50, layout 57e8f78144bf.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x4065).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR8SaveData *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
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
    /* 0x67E0 */ struct {   // size 0x1300
        /* 0x000 */ unsigned char evboot[24];             // 0x18
        /* 0x018 */ unsigned char is_savedata;            // 0x1
        /* 0x019 */ signed char max_area;                 // 0x1
        /* 0x01A */ signed char disp_type;                // 0x1
        /* 0x01B */ char pading;                          // 0x1
        /* 0x01C */ unsigned char dancer_use_cnt[24];     // 0x18
        /* 0x034 */ int cur_cursor;                       // 0x4
        /* 0x038 */ unsigned int all_clear_count;         // 0x4
        /* 0x03C */ unsigned int all_play_time;           // 0x4
        /* 0x040 */ int route[200];                       // 0x320
        /* 0x360 */ struct {   // size 0x14
            /* 0x000 */ unsigned char cone_state[8];          // 0x8
            /* 0x008 */ unsigned char state;                  // 0x1
            /* 0x009 */ unsigned char perfect;                // 0x1
            /* 0x00A */ unsigned short play_count;            // 0x2
            /* 0x00C */ unsigned short play_time;             // 0x2
            /* 0x00E */ unsigned short clear_count;           // 0x2
            /* 0x010 */ unsigned short first_clear_count;     // 0x2
            /* 0x012 */ unsigned short first_clear_time;      // 0x2
        } subject[200];
    } dmm;
    /* 0x7AE0 */ struct oni_mode nonstop_course[39];  // 0x1D4
    /* 0x7CB4 */ struct oni_course nonstop_order[10];  // 0xA78
    /* 0x872C */ unsigned int nMusic_on_last_unlocked;  // 0x4
    /* 0x8730 */ struct _eyetoy_option eyetoy_option;  // 0x4
    /* 0x8734 */ struct _tag_cDDR8Record1 mg_solo_MRecord[80];  // 0x2BC0
    /* 0xB2F4 */ struct {   // size 0x4
        /* 0x000 */ unsigned char game_over;              // 0x1
        /* 0x001 */ unsigned char calorie_check;          // 0x1
        /* 0x002 */ unsigned char pad[2];                 // 0x2
    } wk_save[2];
    /* 0xB2FC */ int workout_user_num;                // 0x4
    /* 0xB300 */ struct {   // size 0x2134
        /* 0x000 */ unsigned int uno : 8;                 // bits 0..7
        /* 0x000 */ unsigned int ino : 8;                 // bits 8..15
        /* 0x000 */ unsigned int frame_no : 8;            // bits 16..23
        /* 0x000 */ unsigned int f_passuse : 1;           // bits 24..24
        /* 0x000 */ unsigned int f_enable : 1;            // bits 25..25
        /* 0x000 */ unsigned int f_program_free : 1;      // bits 26..26
        /* 0x004 */ union {   // size 0x4
            /* 0x000 */ unsigned int ui;                      // 0x4
            /* 0x000 */ struct {   // size 0x4
                /* 0x000 */ unsigned char d[4];                   // 0x4
            } s;
        } userpass;
        /* 0x008 */ struct {   // size 0x12E0
            /* 0x000 */ int weight;                           // 0x4
            /* 0x004 */ int lbs;                              // 0x4
            /* 0x008 */ int norm_type;                        // 0x4
            /* 0x00C */ int norm_time;                        // 0x4
            /* 0x010 */ int norm_calorie;                     // 0x4
            /* 0x014 */ int workout_step;                     // 0x4
            /* 0x018 */ int simultaneous_step;                // 0x4
            /* 0x01C */ struct {   // size 0xC
                /* 0x000 */ int date;                             // 0x4
                /* 0x004 */ unsigned int weight : 12;             // bits 0..11
                /* 0x004 */ unsigned int calorie : 20;            // bits 12..31
                /* 0x008 */ unsigned int play_count : 12;         // bits 0..11
                /* 0x008 */ unsigned int play_time : 20;          // bits 12..31
            } history[400];
            /* 0x12DC */ int check_sum_val;                   // 0x4
        } pwork;
        /* 0x12E8 */ struct {   // size 0xD40
            /* 0x000 */ unsigned int program_calorie[24];     // 0x60
            /* 0x060 */ unsigned int program_play_count[24];  // 0x60
            /* 0x0C0 */ unsigned int song_calorie[80][5];     // 0x640
            /* 0x700 */ unsigned int song_play_count[80][5];  // 0x640
        } workout_calorie_record;
        /* 0x2028 */ struct oni_course program_order;     // 0x10C
    } workout_user[10];
    /* 0x1FF08 */ struct _tag_cPointSaveWork point_work;  // 0x8
    /* 0x1FF10 */ struct _tag_cNetSaveWork net_work;  // 0x40
};

#endif /* DDR_types__tag_cDDR8SaveData_H */
