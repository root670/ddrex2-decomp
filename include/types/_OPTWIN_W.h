/* struct _OPTWIN_W -- 9 members, size 0xDA4, layout 1ce15a77948f.
 *
 * One definition, agreed by the 8 units that declare it: opt_adjust.c (DIE 0x430372).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _OPTWIN_W *`.
 *
 * declared by: opt_adjust.c (DIE 0x430372), opt_doll.c (DIE 0x4354C9), opt_kconfig.c (DIE 0x439B97), opt_lang.c (DIE 0x43CD90), opt_main.c (DIE 0x440EFE), opt_mc.c (DIE 0x44737F), opt_menu.c (DIE 0x44C60B), opt_win.c (DIE 0x450ABD)
 */
#ifndef DDR_types__OPTWIN_W_H
#define DDR_types__OPTWIN_W_H

struct _OPTWIN_MLW_W;

#include "types/_OPTWIN_MLW_W.h"

struct _OPTWIN_W {   // size 0xDA4
    /* 0x000 */ int TitleTexNum;                      // 0x4
    /* 0x004 */ unsigned char AdjustFlag;             // 0x1
    /* 0x005 */ unsigned char AdjustAlpha;            // 0x1
    /* 0x006 */ unsigned short AdjustCheck;           // 0x2
    /* 0x008 */ unsigned char KConfigBackFlag;        // 0x1
    /* 0x009 */ unsigned char KConfigBackAlpha;       // 0x1
    /* 0x00A */ unsigned char LangFlag;               // 0x1
    /* 0x00B */ unsigned char LangAlpha;              // 0x1
    /* 0x00C */ struct _OPTWIN_MLW_W MLW[30];         // 0xD98
};

#endif /* DDR_types__OPTWIN_W_H */
