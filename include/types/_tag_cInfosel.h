/* struct _tag_cInfosel -- 9 members, size 0x3C, layout 7ac66b949f54.
 *
 * One definition, agreed by the 1 unit that declares it: infosel.c (DIE 0x32FBC7).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cInfosel *`.
 *
 * declared by: infosel.c (DIE 0x32FBC7)
 */
#ifndef DDR_types__tag_cInfosel_H
#define DDR_types__tag_cInfosel_H

struct _tag_cInfosel {   // size 0x3C
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int next_step;                        // 0x4
    /* 0x008 */ int title_move_count[2];              // 0x8
    /* 0x010 */ int title_move_zure_count[2];         // 0x8
    /* 0x018 */ int title_move_total_count[2];        // 0x8
    /* 0x020 */ int show_flag;                        // 0x4
    /* 0x024 */ int arrow_counter[2];                 // 0x8
    /* 0x02C */ int arrow_alpha[2];                   // 0x8
    /* 0x034 */ int arrow_offs[2];                    // 0x8
};

#endif /* DDR_types__tag_cInfosel_H */
