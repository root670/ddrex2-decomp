/* struct _tag_cDDR7OniRecord1 -- 9 members, size 0x38, layout 74f01279363d.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x7664).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR7OniRecord1 *`.
 *
 * declared by: les.c (DIE 0x7664), les_play.c (DIE 0x1080A), reconi.c (DIE 0x21741), onimode.c (DIE 0x2B3AC), recend.c (DIE 0x39228), eds_select.c (DIE 0x41D87), eds_main.c (DIE 0x47ECF), optscr.c (DIE 0x4C2DF), eds_aid.c (DIE 0x56B4D), eds_break.c (DIE 0x5B399), eds_record.c (DIE 0x5F05B), optdoll.c (DIE 0x95895), dexport.c (DIE 0x96E76), dinit.c (DIE 0x9EEB4)
 */
#ifndef DDR_types__tag_cDDR7OniRecord1_H
#define DDR_types__tag_cDDR7OniRecord1_H

struct _tag_cDDR7OniRecord1 {   // size 0x38
    /* 0x000 */ unsigned int Score[4];                // 0x10
    /* 0x010 */ unsigned short Time[4];               // 0x8
    /* 0x018 */ unsigned short Combo[4];              // 0x8
    /* 0x020 */ unsigned short Miss[4];               // 0x8
    /* 0x028 */ unsigned char Stage[4];               // 0x4
    /* 0x02C */ unsigned char Clear[4];               // 0x4
    /* 0x030 */ unsigned char Level[4];               // 0x4
    /* 0x034 */ unsigned char is_first_clear;         // 0x1
    /* 0x035 */ unsigned char pad[3];                 // 0x3
};

#endif /* DDR_types__tag_cDDR7OniRecord1_H */
