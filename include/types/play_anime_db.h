/* struct play_anime_db -- 7 members, size 0x1C, layout c22cae2e3679.
 *
 * One definition, agreed by the 1 unit that declares it: p_anime.c (DIE 0x17BEC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_anime_db *`.
 *
 * declared by: p_anime.c (DIE 0x17BEC)
 */
#ifndef DDR_types_play_anime_db_H
#define DDR_types_play_anime_db_H

struct play_anime_db {   // size 0x1C
    /* 0x000 */ int note_id;                          // 0x4
    /* 0x004 */ int anime_id;                         // 0x4
    /* 0x008 */ int sub_id;                           // 0x4
    /* 0x00C */ int pre_counter;                      // 0x4
    /* 0x010 */ int frz_end_cnt;                      // 0x4
    /* 0x014 */ int frz_step;                         // 0x4
    /* 0x018 */ int bak_anime_flag;                   // 0x4
};

#endif /* DDR_types_play_anime_db_H */
