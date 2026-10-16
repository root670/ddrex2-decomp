/* struct play_anime_db -- 4 members, size 0x10, layout 4b0397b5d1e4.
 *
 * One definition, agreed by the 1 unit that declares it: p_anime.c (DIE 0x7372E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_anime_db *`.
 *
 * declared by: p_anime.c (DIE 0x7372E)
 */
#ifndef DDR_types_play_anime_db_H
#define DDR_types_play_anime_db_H

struct play_anime_db {   // size 0x10
    /* 0x000 */ int note_id;                          // 0x4
    /* 0x004 */ int anime_id;                         // 0x4
    /* 0x008 */ int sub_id;                           // 0x4
    /* 0x00C */ int pre_counter;                      // 0x4
};

#endif /* DDR_types_play_anime_db_H */
