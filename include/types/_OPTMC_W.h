/* struct _OPTMC_W -- 12 members, size 0x54, layout 06f435e23d5f.
 *
 * One definition, agreed by the 2 units that declare it: fp_qmenu.c (DIE 0x2FDDB6).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _OPTMC_W *`.
 *
 * declared by: fp_qmenu.c (DIE 0x2FDDB6), opt_mc.c (DIE 0x446BD3)
 */
#ifndef DDR_types__OPTMC_W_H
#define DDR_types__OPTMC_W_H

struct _OPTMC_W {   // size 0x54
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int step2;                            // 0x4
    /* 0x008 */ int swap_fg;                          // 0x4
    /* 0x00C */ int draw_mcwnd;                       // 0x4
    /* 0x010 */ int counter;                          // 0x4
    /* 0x014 */ int sstep;                            // 0x4
    /* 0x018 */ unsigned int hide_show;               // 0x4
    /* 0x01C */ int update_yesno_check;               // 0x4
    /* 0x020 */ int sup_draw;                         // 0x4
    /* 0x024 */ int sup_item_num[2][4];               // 0x20
    /* 0x044 */ unsigned int sup_HideFlag[2];         // 0x8
    /* 0x04C */ unsigned int sup_DollFlag[2];         // 0x8
};

#endif /* DDR_types__OPTMC_W_H */
