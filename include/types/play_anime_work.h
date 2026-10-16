/* struct play_anime_work -- 2 members, size 0x3C, layout 2af525cefc70.
 *
 * One definition, agreed by the 1 unit that declares it: p_anime.c (DIE 0x18137).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_anime_work *`.
 *
 * declared by: p_anime.c (DIE 0x18137)
 */
#ifndef DDR_types_play_anime_work_H
#define DDR_types_play_anime_work_H

struct play_anime_db;

#include "types/play_anime_db.h"

struct play_anime_work {   // size 0x3C
    /* 0x000 */ int mode;                             // 0x4
    /* 0x004 */ struct play_anime_db db[2];           // 0x38
};

#endif /* DDR_types_play_anime_work_H */
