/* struct _tag_cDDR7Record1 -- 9 members, size 0x90, layout 79edb3d99eb4.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x6D0A).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cDDR7Record1 *`.
 *
 * declared by: les.c (DIE 0x6D0A), les_play.c (DIE 0xCCF8), reconi.c (DIE 0x23A51), onimode.c (DIE 0x2B568), recend.c (DIE 0x38795), eds_select.c (DIE 0x40131), eds_main.c (DIE 0x46DCB), optscr.c (DIE 0x4B2B4), eds_aid.c (DIE 0x55830), eds_break.c (DIE 0x5AC45), eds_record.c (DIE 0x5E50A), optdoll.c (DIE 0x951EC), dexport.c (DIE 0x9AA11), dinit.c (DIE 0x9E213)
 */
#ifndef DDR_types__tag_cDDR7Record1_H
#define DDR_types__tag_cDDR7Record1_H

struct _tag_cDDR7Record1 {   // size 0x90
    /* 0x000 */ unsigned int Score[10];               // 0x28
    /* 0x028 */ unsigned int Bonus[10];               // 0x28
    /* 0x050 */ unsigned int nPlayed;                 // 0x4
    /* 0x054 */ unsigned short LinkNum;               // 0x2
    /* 0x056 */ unsigned short Combo[10];             // 0x14
    /* 0x06A */ unsigned short ComboMax[10];          // 0x14
    /* 0x07E */ unsigned char Level[10];              // 0xA
    /* 0x088 */ unsigned char little_flag[2];         // 0x2
    /* 0x08A */ char pad[6];                          // 0x6
};

#endif /* DDR_types__tag_cDDR7Record1_H */
