/* struct play_mode -- 19 members, size 0xC, layout cebbe522df35.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x3B87).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_mode *`.
 *
 * declared by: les.c (DIE 0x3B87), les_play.c (DIE 0x12D5B), kn_lfunc.c (DIE 0x1A7F8), onimode.c (DIE 0x2A799), sp_ending_d.c (DIE 0x3357A), eds_select.c (DIE 0x3E2A7), eds_main.c (DIE 0x4431F), eds_aid.c (DIE 0x5236A), b_anime.c (DIE 0x6E929), p_anime.c (DIE 0x74A08), ani_load.c (DIE 0x7692D), dexport.c (DIE 0x98CA2)
 */
#ifndef DDR_types_play_mode_H
#define DDR_types_play_mode_H

struct play_mode {   // size 0xC
    /* 0x000 */ unsigned char seq_kind;               // 0x1
    /* 0x001 */ unsigned char seq_transfer;           // 0x1
    /* 0x002 */ unsigned char style;                  // 0x1
    /* 0x003 */ unsigned char pccard_seq;             // 0x1
    /* 0x004 */ unsigned char mcard_seq;              // 0x1
    /* 0x005 */ unsigned char padding;                // 0x1
    /* 0x006 */ short edseq_id;                       // 0x2
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

#endif /* DDR_types_play_mode_H */
