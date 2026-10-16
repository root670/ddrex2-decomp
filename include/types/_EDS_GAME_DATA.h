/* struct _EDS_GAME_DATA -- 11 members, size 0x34, layout 24a0334c1fca.
 *
 * One definition, agreed by the 2 units that declare it: adv_topmenu_obj.c (DIE 0x2724F7).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EDS_GAME_DATA *`.
 *
 * declared by: adv_topmenu_obj.c (DIE 0x2724F7), adv_endless_obj.c (DIE 0x27DEE8)
 */
#ifndef DDR_types__EDS_GAME_DATA_H
#define DDR_types__EDS_GAME_DATA_H

struct _EDS_GAME_DATA {   // size 0x34
    /* 0x000 */ int stage;                            // 0x4
    /* 0x004 */ int BreakStage;                       // 0x4
    /* 0x008 */ int play_music_max;                   // 0x4
    /* 0x00C */ int Combo;                            // 0x4
    /* 0x010 */ unsigned int ScoreMax[2];             // 0x8
    /* 0x018 */ unsigned int ScoreTmp[2];             // 0x8
    /* 0x020 */ int ComboMax;                         // 0x4
    /* 0x024 */ int StageMax;                         // 0x4
    /* 0x028 */ int Gauge;                            // 0x4
    /* 0x02C */ int StagePF;                          // 0x4
    /* 0x030 */ float B_stock;                        // 0x4
};

#endif /* DDR_types__EDS_GAME_DATA_H */
