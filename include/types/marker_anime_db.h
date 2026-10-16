/* struct marker_anime_db -- 3 members, size 0x20, layout 62e082393762.
 *
 * One definition, agreed by the 1 unit that declares it: b_anime.c (DIE 0x157D0).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct marker_anime_db *`.
 *
 * declared by: b_anime.c (DIE 0x157D0)
 */
#ifndef DDR_types_marker_anime_db_H
#define DDR_types_marker_anime_db_H

struct marker_anime_db {   // size 0x20
    /* 0x000 */ unsigned long flash_bit[2];           // 0x10
    /* 0x010 */ int ct[2];                            // 0x8
    /* 0x018 */ unsigned long every_q;                // 0x8
};

#endif /* DDR_types_marker_anime_db_H */
