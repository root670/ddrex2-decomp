/* struct anime_db -- 10 members, size 0x88, layout 91060832c240.
 *
 * One definition, agreed by the 1 unit that declares it: b_anime.c (DIE 0x144BC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct anime_db *`.
 *
 * A member this type holds anonymously is spelled out below, because it
 * has no name that could travel: `@anonN` is per-unit numbering.  The
 * layout digest above is compared across every declaration, which is what
 * makes spelling it out here faithful.
 *
 * declared by: b_anime.c (DIE 0x144BC)
 */
#ifndef DDR_types_anime_db_H
#define DDR_types_anime_db_H

struct anime_db {   // size 0x88
    /* 0x000 */ unsigned long size;                   // 0x8
    /* 0x008 */ unsigned long total_anime;            // 0x8
    /* 0x010 */ unsigned long begin_block;            // 0x8
    /* 0x018 */ unsigned long *buff;                  // 0x4
    /* 0x01C */ int req_anime;                        // 0x4
    /* 0x020 */ int cur_id;                           // 0x4
    /* 0x024 */ struct {   // size 0x8
        /* 0x000 */ short x;                              // 0x2
        /* 0x002 */ short y;                              // 0x2
        /* 0x004 */ short w;                              // 0x2
        /* 0x006 */ short h;                              // 0x2
    } prect;
    /* 0x02C */ struct {   // size 0x8
        /* 0x000 */ short x;                              // 0x2
        /* 0x002 */ short y;                              // 0x2
        /* 0x004 */ short w;                              // 0x2
        /* 0x006 */ short h;                              // 0x2
    } crect;
    /* 0x034 */ int can_block;                        // 0x4
    /* 0x038 */ int tan_block[19];                    // 0x4C
    /* 0x084 */ // 0x4 bytes padding
};

#endif /* DDR_types_anime_db_H */
