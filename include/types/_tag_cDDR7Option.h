/* struct _tag_cDDR7Option -- 38 members, size 0x40, layout 7040c26d8895.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x7E2B).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR7Option *`.
 *
 * declared by: les.c (DIE 0x7E2B), les_play.c (DIE 0x10EE7), reconi.c (DIE 0x24CCE), onimode.c (DIE 0x2DB37), recend.c (DIE 0x39788), eds_select.c (DIE 0x3C137), eds_main.c (DIE 0x4858C), optscr.c (DIE 0x4C968), eds_aid.c (DIE 0x5720A), eds_break.c (DIE 0x5B8AF), eds_record.c (DIE 0x5F6B6), optdoll.c (DIE 0x94BA2), dexport.c (DIE 0x97533), dinit.c (DIE 0x9F3EE)
 */
#ifndef DDR_types__tag_cDDR7Option_H
#define DDR_types__tag_cDDR7Option_H

struct _tag_cDDR7Option {   // size 0x40
    /* 0x000 */ unsigned char Sound;                  // 0x1
    /* 0x001 */ unsigned char Voice;                  // 0x1
    /* 0x002 */ signed char Timing;                   // 0x1
    /* 0x003 */ char pad_sound[1];                    // 0x1
    /* 0x004 */ unsigned char KeyConfig[4];           // 0x4
    /* 0x008 */ unsigned char Vibration;              // 0x1
    /* 0x009 */ unsigned char DPlay;                  // 0x1
    /* 0x00A */ char pad_cont[2];                     // 0x2
    /* 0x00C */ unsigned char AutoSave;               // 0x1
    /* 0x00D */ unsigned char FolderLoad;             // 0x1
    /* 0x00E */ char pad_mc[2];                       // 0x2
    /* 0x010 */ unsigned char Level;                  // 0x1
    /* 0x011 */ unsigned char MaxStage[3];            // 0x3
    /* 0x014 */ unsigned char GameOver;               // 0x1
    /* 0x015 */ unsigned char TimeLimit;              // 0x1
    /* 0x016 */ unsigned char EventMode;              // 0x1
    /* 0x017 */ unsigned char DefaultDifficulty;      // 0x1
    /* 0x018 */ char pad_game[8];                     // 0x8
    /* 0x020 */ unsigned char BgEffect;               // 0x1
    /* 0x021 */ unsigned char BgBright;               // 0x1
    /* 0x022 */ unsigned char DangerDisplay;          // 0x1
    /* 0x023 */ unsigned char StepMarkColor;          // 0x1
    /* 0x024 */ signed char screen_x;                 // 0x1
    /* 0x025 */ signed char screen_y;                 // 0x1
    /* 0x026 */ unsigned char FlickerFree;            // 0x1
    /* 0x027 */ unsigned char SongDisplay;            // 0x1
    /* 0x028 */ unsigned char DietMeasure;            // 0x1
    /* 0x029 */ unsigned char DietDisplay;            // 0x1
    /* 0x02A */ unsigned char DietTime;               // 0x1
    /* 0x02B */ unsigned char DietPlayDefault;        // 0x1
    /* 0x02C */ unsigned char DietWeightUnit;         // 0x1
    /* 0x02D */ char pad_diet[3];                     // 0x3
    /* 0x030 */ unsigned char Language;               // 0x1
    /* 0x031 */ char pad_lang[7];                     // 0x7
    /* 0x038 */ unsigned char DollDisp;               // 0x1
    /* 0x039 */ unsigned char DollGuestNum;           // 0x1
    /* 0x03A */ unsigned char DollChara[3];           // 0x3
    /* 0x03D */ char pad[3];                          // 0x3
};

#endif /* DDR_types__tag_cDDR7Option_H */
