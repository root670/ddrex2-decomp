/* struct _tag_cMusicData -- 5 members, size 0x14, layout 10de192dd200.
 *
 * One definition, agreed by the 6 units that declare it: music_all.c (DIE 0xC8E8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _tag_cMusicData *`.
 *
 * declared by: music_all.c (DIE 0xC8E8), fp_msel.c (DIE 0x10036F), net_game_challenge.c (DIE 0x26DF17), adv_endless_obj.c (DIE 0x280678), rec_hi.c (DIE 0x47D589), rec_hand.c (DIE 0x48A6D3)
 */
#ifndef DDR_types__tag_cMusicData_H
#define DDR_types__tag_cMusicData_H

struct _tag_cMusicData {   // size 0x14
    /* 0x000 */ int link_num;                         // 0x4
    /* 0x004 */ unsigned char *base_name;             // 0x4
    /* 0x008 */ unsigned char *music_name;            // 0x4
    /* 0x00C */ unsigned char *music_name_mc;         // 0x4
    /* 0x010 */ unsigned char *artist_name;           // 0x4
};

#endif /* DDR_types__tag_cMusicData_H */
