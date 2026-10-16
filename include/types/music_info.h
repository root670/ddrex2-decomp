/* struct music_info -- 22 members, size 0x98, layout 67e49d6f28cf.
 *
 * One definition, agreed by the 12 units that declare it: les.c (DIE 0x362C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct music_info *`.
 *
 * declared by: les.c (DIE 0x362C), les_play.c (DIE 0xFE01), kn_lfunc.c (DIE 0x19990), onimode.c (DIE 0x2AEEC), sp_ending_d.c (DIE 0x34C45), eds_select.c (DIE 0x3CC61), eds_main.c (DIE 0x46083), eds_aid.c (DIE 0x54AE8), b_anime.c (DIE 0x6D9DA), p_anime.c (DIE 0x73390), ani_load.c (DIE 0x75E3A), dexport.c (DIE 0x97EFC)
 */
#ifndef DDR_types_music_info_H
#define DDR_types_music_info_H

struct music_info {   // size 0x98
    /* 0x000 */ char base_name[6];                    // 0x6
    /* 0x006 */ signed char kind;                     // 0x1
    /* 0x007 */ signed char album;                    // 0x1
    /* 0x008 */ short dance_num;                      // 0x2
    /* 0x00A */ short order;                          // 0x2
    /* 0x00C */ unsigned short main_track;            // 0x2
    /* 0x00E */ unsigned short select_track;          // 0x2
    /* 0x010 */ unsigned short bpm_max;               // 0x2
    /* 0x012 */ unsigned short bpm_min;               // 0x2
    /* 0x014 */ unsigned short verm_num;              // 0x2
    /* 0x016 */ unsigned short pcseq_num;             // 0x2
    /* 0x018 */ unsigned long hide;                   // 0x8
    /* 0x020 */ short adjust_mc;                      // 0x2
    /* 0x022 */ // 0x2 bytes padding
    /* 0x024 */ unsigned int difficulty[2];           // 0x8
    /* 0x02C */ unsigned int special;                 // 0x4
    /* 0x030 */ unsigned short max_spm[9];            // 0x12
    /* 0x042 */ unsigned short avg_spm[9];            // 0x12
    /* 0x054 */ unsigned short avg_jpm[9];            // 0x12
    /* 0x066 */ unsigned short chaos_v[9];            // 0x12
    /* 0x078 */ unsigned short freez_v[9];            // 0x12
    /* 0x08A */ // 0x2 bytes padding
    /* 0x08C */ char *title;                          // 0x4
    /* 0x090 */ char *l_name;                         // 0x4
    /* 0x094 */ // 0x4 bytes padding
};

#endif /* DDR_types_music_info_H */
