/* struct play_anime_work -- 2 members, size 0x24, layout 5cf8b963aa19.
 *
 * One definition, agreed by the 1 unit that declares it: p_anime.c (DIE 0x732DC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_anime_work *`.
 *
 * declared by: p_anime.c (DIE 0x732DC)
 */
#ifndef DDR_types_play_anime_work_H
#define DDR_types_play_anime_work_H

struct play_anime_db;

#include "types/play_anime_db.h"

struct play_anime_work {   // size 0x24
    /* 0x000 */ int mode;                             // 0x4
    /* 0x004 */ struct play_anime_db db[2];           // 0x20
};

#endif /* DDR_types_play_anime_work_H */
