/* struct _OPTWIN_MLW_W -- 13 members, size 0x74, layout 6266b8c92013.
 *
 * One definition, agreed by the 8 units that declare it: opt_adjust.c (DIE 0x42FD16).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _OPTWIN_MLW_W *`.
 *
 * declared by: opt_adjust.c (DIE 0x42FD16), opt_doll.c (DIE 0x434D0E), opt_kconfig.c (DIE 0x4391E7), opt_lang.c (DIE 0x43C798), opt_main.c (DIE 0x4408B6), opt_mc.c (DIE 0x446E0F), opt_menu.c (DIE 0x44BFE0), opt_win.c (DIE 0x45058C)
 */
#ifndef DDR_types__OPTWIN_MLW_W_H
#define DDR_types__OPTWIN_MLW_W_H

struct _OPTWIN_MLW_W {   // size 0x74
    /* 0x000 */ int wait_timer;                       // 0x4
    /* 0x004 */ int time;                             // 0x4
    /* 0x008 */ short tx;                             // 0x2
    /* 0x00A */ short x;                              // 0x2
    /* 0x00C */ short y;                              // 0x2
    /* 0x00E */ char line;                            // 0x1
    /* 0x00F */ char num;                             // 0x1
    /* 0x010 */ unsigned char stex_num;               // 0x1
    /* 0x011 */ unsigned char stex_num2;              // 0x1
    /* 0x012 */ unsigned char flag;                   // 0x1
    /* 0x013 */ unsigned char status;                 // 0x1
    /* 0x014 */ unsigned char str[64];                // 0x40
    /* 0x054 */ unsigned char str2[32];               // 0x20
};

#endif /* DDR_types__OPTWIN_MLW_W_H */
