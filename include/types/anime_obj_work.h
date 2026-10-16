/* struct anime_obj_work -- 4 members, size 0x120, layout f19a138318e8.
 *
 * One definition, agreed by the 1 unit that declares it: b_anime.c (DIE 0x14E6C).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct anime_obj_work *`.
 *
 * declared by: b_anime.c (DIE 0x14E6C)
 */
#ifndef DDR_types_anime_obj_work_H
#define DDR_types_anime_obj_work_H

struct anime_db;

#include "types/anime_db.h"

struct anime_obj_work {   // size 0x120
    /* 0x000 */ unsigned long every_q;                // 0x8
    /* 0x008 */ int mode;                             // 0x4
    /* 0x00C */ int kyoutai_flash_id;                 // 0x4
    /* 0x010 */ struct anime_db db[2];                // 0x110
};

#endif /* DDR_types_anime_obj_work_H */
