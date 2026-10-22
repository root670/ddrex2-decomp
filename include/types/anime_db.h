/* struct anime_db -- 10 members, size 0x88, layout 91060832c240.
 *
 * One definition, agreed by the 1 unit that declares it: b_anime.c (DIE 0x144BC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct anime_db *`.
 *
 * An anonymous member is named, not spelled out here: its layout is
 * defined once in the `types/anon_<digest>.h` header included below, as a
 * typedef of an *unnamed* aggregate, so every use of that layout in a
 * unit's block is one DIE -- retail's own block has one, and two
 * declarations of it are 5 DIEs and 0x97 bytes of overrun.
 *
 * declared by: b_anime.c (DIE 0x144BC)
 */
#ifndef DDR_types_anime_db_H
#define DDR_types_anime_db_H

#include "types/anon_b14b78a0b5d3.h"

struct anime_db {   // size 0x88
    /* 0x000 */ unsigned long size;                   // 0x8
    /* 0x008 */ unsigned long total_anime;            // 0x8
    /* 0x010 */ unsigned long begin_block;            // 0x8
    /* 0x018 */ unsigned long *buff;                  // 0x4
    /* 0x01C */ int req_anime;                        // 0x4
    /* 0x020 */ int cur_id;                           // 0x4
    /* 0x024 */ anon_b14b78a0b5d3 prect;              // 0x8
    /* 0x02C */ anon_b14b78a0b5d3 crect;              // 0x8
    /* 0x034 */ int can_block;                        // 0x4
    /* 0x038 */ int tan_block[19];                    // 0x4C
    /* 0x084 */ // 0x4 bytes padding
};

#endif /* DDR_types_anime_db_H */
