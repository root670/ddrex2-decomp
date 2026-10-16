/* struct _EDSS_DATA_W -- 3 members, size 0x10, layout 80d8d77c3994.
 *
 * One definition, agreed by the 14 units that declare it: les.c (DIE 0x2EC4).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDSS_DATA_W *`.
 *
 * declared by: les.c (DIE 0x2EC4), les_play.c (DIE 0x11724), reconi.c (DIE 0x2550B), onimode.c (DIE 0x2E310), recend.c (DIE 0x39E40), eds_select.c (DIE 0x3C98E), eds_main.c (DIE 0x48D7A), optscr.c (DIE 0x4CFFA), eds_aid.c (DIE 0x57A45), eds_break.c (DIE 0x5BFE7), eds_record.c (DIE 0x5F4BD), optdoll.c (DIE 0x95E5F), dexport.c (DIE 0x97C7B), dinit.c (DIE 0x9C6F0)
 */
#ifndef DDR_types__EDSS_DATA_W_H
#define DDR_types__EDSS_DATA_W_H

struct _EDSS_DATA_W {   // size 0x10
    /* 0x000 */ unsigned int score[2];                // 0x8
    /* 0x008 */ int combo;                            // 0x4
    /* 0x00C */ int stage;                            // 0x4
};

#endif /* DDR_types__EDSS_DATA_W_H */
