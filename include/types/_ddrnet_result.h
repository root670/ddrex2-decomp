/* struct _ddrnet_result -- 6 members, size 0x24, layout 7b9af29fb7b2.
 *
 * One definition, agreed by the 4 units that declare it: net_prg.c (DIE 0x881FC).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _ddrnet_result *`.
 *
 * declared by: net_prg.c (DIE 0x881FC), net_game_vs.c (DIE 0x1CC7C4), net_game_prg.c (DIE 0x2EA722), ddrex2_usa_lobby.c (DIE 0x398BEC)
 */
#ifndef DDR_types__ddrnet_result_H
#define DDR_types__ddrnet_result_H

struct _ddrnet_result {   // size 0x24
    /* 0x000 */ short life;                           // 0x2
    /* 0x002 */ short max_combo;                      // 0x2
    /* 0x004 */ int score;                            // 0x4
    /* 0x008 */ int time;                             // 0x4
    /* 0x00C */ short steps[8];                       // 0x10
    /* 0x01C */ short freeze_arrow[4];                // 0x8
};

#endif /* DDR_types__ddrnet_result_H */
