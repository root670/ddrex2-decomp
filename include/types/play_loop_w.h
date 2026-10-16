/* struct play_loop_w -- 3 members, size 0x8008, layout 781a32a82b90.
 *
 * One definition, agreed by the 2 units that declare it: net_play_main.c (DIE 0x1C11E5).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_loop_w *`.
 *
 * declared by: net_play_main.c (DIE 0x1C11E5), net_game_vs.c (DIE 0x1CFA2C)
 */
#ifndef DDR_types_play_loop_w_H
#define DDR_types_play_loop_w_H

struct play_loop_w {   // size 0x8008
    /* 0x000 */ int step;                             // 0x4
    /* 0x004 */ int sel_step;                         // 0x4
    /* 0x008 */ unsigned int game_mode_memory[8192];  // 0x8000
};

#endif /* DDR_types_play_loop_w_H */
