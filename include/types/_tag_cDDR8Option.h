/* struct _tag_cDDR8Option -- 43 members, size 0x58, layout d0c4d5998068.
 *
 * One definition, agreed by the 54 units that declare it: onimode.c (DIE 0x8B32).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR8Option *`.
 *
 * declared by: onimode.c (DIE 0x8B32), dexport.c (DIE 0x3C76E), dinit.c (DIE 0x401AC), eye_system.c (DIE 0x4A181), info_data.c (DIE 0x58716), fft_disp.c (DIE 0x64F7C), bk_disp_sub.c (DIE 0xE2A2D), bk_disp.c (DIE 0xE989E), fp_msel.c (DIE 0x103A7A), fp_chara.c (DIE 0x116122), fp_style.c (DIE 0x12AFD7), fp_res.c (DIE 0x1366A0), fp_opt.c (DIE 0x13FB86), dmm_data.c (DIE 0x1799B5), dmm_disp.c (DIE 0x1819BE), dmm_init.c (DIE 0x18CEC6), fp_doll.c (DIE 0x1B5D6A), fp_msel_obj.c (DIE 0x1D8C8D), shop_init.c (DIE 0x20F600), shop_list.c (DIE 0x215167), shop_obj.c (DIE 0x21EBD3), shop_disp.c (DIE 0x22E4A7), shop_func.c (DIE 0x237F3B), dmm_mc.c (DIE 0x24747E), rec_nor.c (DIE 0x25866C), adv_endless_obj.c (DIE 0x2865C5), adv_main.c (DIE 0x292F7E), tra_main.c (DIE 0x2B46B3), dmm_func.c (DIE 0x2C5D5E), tra_func.c (DIE 0x2D5F2C), fp_qmenu.c (DIE 0x2FF5C8), info.c (DIE 0x3385A7), infoshow.c (DIE 0x340607), les.c (DIE 0x36AA2A), les_play.c (DIE 0x37ACAD), net_auth_main.c (DIE 0x3A90EE), net_cnf_main.c (DIE 0x3B45B2), dmm_event.c (DIE 0x3C5683), dmm_event_cond.c (DIE 0x3CF867), dmm_event_exe.c (DIE 0x3DB635), dmm_play_course.c (DIE 0x3F6E5E), dmm_qmenu.c (DIE 0x3FE8D1), dmm_result.c (DIE 0x40B18B), dmm_select.c (DIE 0x41880F), dmm_style.c (DIE 0x425DC3), opt_adjust.c (DIE 0x42E209), opt_doll.c (DIE 0x4333F0), opt_kconfig.c (DIE 0x43701C), opt_mc.c (DIE 0x445136), opt_menu.c (DIE 0x44A338), workout_usermanage.c (DIE 0x456F27), rec_hi.c (DIE 0x47F311), rec_end.c (DIE 0x4870D9), rec_hand.c (DIE 0x48C48C)
 */
#ifndef DDR_types__tag_cDDR8Option_H
#define DDR_types__tag_cDDR8Option_H

struct _tag_cDDR8Option {   // size 0x58
    /* 0x000 */ unsigned char Sound;                  // 0x1
    /* 0x001 */ unsigned char Voice;                  // 0x1
    /* 0x002 */ signed char Timing;                   // 0x1
    /* 0x003 */ char pad_sound[1];                    // 0x1
    /* 0x004 */ char EditKey[24];                     // 0x18
    /* 0x01C */ unsigned char KeyConfig[4];           // 0x4
    /* 0x020 */ unsigned char DModeSet;               // 0x1
    /* 0x021 */ unsigned char Vibration;              // 0x1
    /* 0x022 */ unsigned char DPlay;                  // 0x1
    /* 0x023 */ char pad_cont[1];                     // 0x1
    /* 0x024 */ unsigned char AutoSave;               // 0x1
    /* 0x025 */ unsigned char FolderLoad;             // 0x1
    /* 0x026 */ char pad_mc[2];                       // 0x2
    /* 0x028 */ unsigned char Level;                  // 0x1
    /* 0x029 */ unsigned char MaxStage[3];            // 0x3
    /* 0x02C */ unsigned char GameOver;               // 0x1
    /* 0x02D */ unsigned char TimeLimit;              // 0x1
    /* 0x02E */ unsigned char EventMode;              // 0x1
    /* 0x02F */ unsigned char DefaultDifficulty;      // 0x1
    /* 0x030 */ char pad_game[8];                     // 0x8
    /* 0x038 */ unsigned char BgEffect;               // 0x1
    /* 0x039 */ unsigned char BgBright;               // 0x1
    /* 0x03A */ unsigned char DangerDisplay;          // 0x1
    /* 0x03B */ unsigned char StepMarkColor;          // 0x1
    /* 0x03C */ signed char screen_x;                 // 0x1
    /* 0x03D */ signed char screen_y;                 // 0x1
    /* 0x03E */ unsigned char FlickerFree;            // 0x1
    /* 0x03F */ unsigned char MarvellousDisplay;      // 0x1
    /* 0x040 */ unsigned char WorkoutMeasure;         // 0x1
    /* 0x041 */ unsigned char WorkoutDisplay;         // 0x1
    /* 0x042 */ unsigned char WorkoutTime;            // 0x1
    /* 0x043 */ unsigned char WorkoutPlayDefault;     // 0x1
    /* 0x044 */ unsigned char WorkoutWeightUnit;      // 0x1
    /* 0x045 */ char pad_workout[3];                  // 0x3
    /* 0x048 */ unsigned char Language;               // 0x1
    /* 0x049 */ char pad_lang[2];                     // 0x2
    /* 0x04B */ unsigned char NetworkAutomatic;       // 0x1
    /* 0x04C */ unsigned int NetworkUdpPort;          // 0x4
    /* 0x050 */ unsigned char DollDisp;               // 0x1
    /* 0x051 */ unsigned char DollChara[3];           // 0x3
    /* 0x054 */ unsigned char DollGuestNum;           // 0x1
    /* 0x055 */ unsigned char DollSelect;             // 0x1
    /* 0x056 */ char pad[2];                          // 0x2
};

#endif /* DDR_types__tag_cDDR8Option_H */
