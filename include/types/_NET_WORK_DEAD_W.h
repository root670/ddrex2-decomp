/* struct _NET_WORK_DEAD_W -- 4 members, size 0xC, layout 9af81ebd1d89.
 *
 * One definition, agreed by the 2 units that declare it: net_game_vs.c (DIE 0x1C8F44).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _NET_WORK_DEAD_W *`.
 *
 * declared by: net_game_vs.c (DIE 0x1C8F44), net_game_prg.c (DIE 0x2E9366)
 */
#ifndef DDR_types__NET_WORK_DEAD_W_H
#define DDR_types__NET_WORK_DEAD_W_H

struct _NET_WORK_DEAD_W {   // size 0xC
    /* 0x000 */ unsigned int flag;                    // 0x4
    /* 0x004 */ short life;                           // 0x2
    /* 0x006 */ short max_combo;                      // 0x2
    /* 0x008 */ int time;                             // 0x4
};

#endif /* DDR_types__NET_WORK_DEAD_W_H */
