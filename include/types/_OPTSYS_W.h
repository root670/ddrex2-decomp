/* struct _OPTSYS_W -- 34 members, size 0xF1C, layout 9165e5106269.
 *
 * One definition, agreed by the 8 units that declare it: opt_adjust.c (DIE 0x42D423).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _OPTSYS_W *`.
 *
 * declared by: opt_adjust.c (DIE 0x42D423), opt_doll.c (DIE 0x43292E), opt_kconfig.c (DIE 0x4367BD), opt_lang.c (DIE 0x43BE31), opt_main.c (DIE 0x43EA53), opt_mc.c (DIE 0x4449D8), opt_menu.c (DIE 0x449B48), opt_win.c (DIE 0x44F179)
 */
#ifndef DDR_types__OPTSYS_W_H
#define DDR_types__OPTSYS_W_H

struct _OPTWIN_W;
struct _tag_OptDoll;
struct _tag_cCoCursor01;
struct _tag_cFilepackData;

#include "types/_OPTWIN_W.h"
#include "types/_tag_OptDoll.h"
#include "types/_tag_cCoCursor01.h"
#include "types/_tag_cFilepackData.h"

struct _OPTSYS_W {   // size 0xF1C
    /* 0x000 */ void (*MainFunc)();                   // 0x4
    /* 0x004 */ unsigned int SystemFlag;              // 0x4
    /* 0x008 */ unsigned int MenuMode;                // 0x4
    /* 0x00C */ unsigned int NextMenuMode;            // 0x4
    /* 0x010 */ unsigned int str_base_address;        // 0x4
    /* 0x014 */ int out_str_exp_id;                   // 0x4
    /* 0x018 */ int help_new_str_id;                  // 0x4
    /* 0x01C */ int help_old_str_id;                  // 0x4
    /* 0x020 */ int help_new_alpha;                   // 0x4
    /* 0x024 */ int help_old_alpha;                   // 0x4
    /* 0x028 */ int line[9];                          // 0x24
    /* 0x04C */ int MenuCursor[17];                   // 0x44
    /* 0x090 */ unsigned char SystemStep;             // 0x1
    /* 0x091 */ unsigned char DataStep;               // 0x1
    /* 0x092 */ unsigned char MenuStep;               // 0x1
    /* 0x093 */ unsigned char LangStep;               // 0x1
    /* 0x094 */ unsigned char AdjustStep;             // 0x1
    /* 0x095 */ unsigned char KConfigStep;            // 0x1
    /* 0x096 */ unsigned char McExeStep;              // 0x1
    /* 0x097 */ // 0x1 bytes padding
    /* 0x098 */ int CursorY;                          // 0x4
    /* 0x09C */ int CursorW;                          // 0x4
    /* 0x0A0 */ struct _tag_cCoCursor01 cur_w;        // 0xC
    /* 0x0AC */ int TmpX;                             // 0x4
    /* 0x0B0 */ int TmpY;                             // 0x4
    /* 0x0B4 */ int ConfigLRflag;                     // 0x4
    /* 0x0B8 */ int ConfigX;                          // 0x4
    /* 0x0BC */ int ConfigY;                          // 0x4
    /* 0x0C0 */ int ConfigFlag;                       // 0x4
    /* 0x0C4 */ char EditKey[24];                     // 0x18
    /* 0x0DC */ int timer;                            // 0x4
    /* 0x0E0 */ struct _OPTWIN_W opt_win;             // 0xDA4
    /* 0xE84 */ struct _tag_OptDoll opt_doll;         // 0x2C
    /* 0xEB0 */ int push_counter;                     // 0x4
    /* 0xEB4 */ struct _tag_cFilepackData tblFilepack[13];  // 0x68
};

#endif /* DDR_types__OPTSYS_W_H */
