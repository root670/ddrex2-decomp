/* struct _tag_cOptScr -- 7 members, size 0x64, layout eaee7da809bc.
 *
 * One definition, agreed by the 1 unit that declares it: optscr.c (DIE 0x4A7A3).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cOptScr *`.
 *
 * declared by: optscr.c (DIE 0x4A7A3)
 */
#ifndef DDR_types__tag_cOptScr_H
#define DDR_types__tag_cOptScr_H

struct _tag_cOptScr {   // size 0x64
    /* 0x000 */ int tmp_x;                            // 0x4
    /* 0x004 */ int tmp_y;                            // 0x4
    /* 0x008 */ int is_press[5];                      // 0x14
    /* 0x01C */ int side_count_flag;                  // 0x4
    /* 0x020 */ int side_counter;                     // 0x4
    /* 0x024 */ int ope_step[8];                      // 0x20
    /* 0x044 */ int ope_bright[8];                    // 0x20
};

#endif /* DDR_types__tag_cOptScr_H */
