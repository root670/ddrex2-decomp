/* struct oni_mode -- 17 members, size 0xC, layout d4af93322df6.
 *
 * One definition, agreed by the 15 units that declare it: les.c (DIE 0x7847).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct oni_mode *`.
 *
 * declared by: les.c (DIE 0x7847), les_play.c (DIE 0x1097E), reconi.c (DIE 0x24892), onimode.c (DIE 0x29FC2), recend.c (DIE 0x3939C), eds_select.c (DIE 0x41EFB), eds_main.c (DIE 0x48043), optscr.c (DIE 0x4C4C3), oni_list.c (DIE 0x4DBDE), eds_aid.c (DIE 0x56CC1), eds_break.c (DIE 0x5B50D), eds_record.c (DIE 0x5F1CF), optdoll.c (DIE 0x95A09), dexport.c (DIE 0x9700E), dinit.c (DIE 0x9F04C)
 */
#ifndef DDR_types_oni_mode_H
#define DDR_types_oni_mode_H

struct oni_mode {   // size 0xC
    /* 0x000 */ unsigned int link_num;                // 0x4
    /* 0x004 */ unsigned char seq_kind;               // 0x1
    /* 0x005 */ unsigned char seq_transfer;           // 0x1
    /* 0x006 */ unsigned char sp_music;               // 0x1
    /* 0x007 */ unsigned char add_life;               // 0x1
    /* 0x008 */ unsigned int hidden : 2;              // bits 0..1
    /* 0x008 */ unsigned int thinout : 1;             // bits 2..2
    /* 0x008 */ unsigned int free : 1;                // bits 3..3
    /* 0x008 */ unsigned int soft : 1;                // bits 4..4
    /* 0x008 */ unsigned int boost : 2;               // bits 5..6
    /* 0x008 */ unsigned int speed : 5;               // bits 7..11
    /* 0x008 */ unsigned int scroll : 2;              // bits 12..13
    /* 0x008 */ unsigned int freeze : 1;              // bits 14..14
    /* 0x008 */ unsigned int vivid : 2;               // bits 15..16
    /* 0x008 */ unsigned int anime : 2;               // bits 17..18
    /* 0x008 */ unsigned int dark : 1;                // bits 19..19
    /* 0x008 */ unsigned int pad : 12;                // bits 20..31
};

#endif /* DDR_types_oni_mode_H */
