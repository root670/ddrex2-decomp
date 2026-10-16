/* struct play_loop_w -- 3 members, size 0x8008, layout 7d59a7b93504.
 *
 * One definition, agreed by the 6 units that declare it: eds_select.c (DIE 0x41AB8).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct play_loop_w *`.
 *
 * declared by: eds_select.c (DIE 0x41AB8), eds_main.c (DIE 0x49046), eds_win.c (DIE 0x4FE29), eds_aid.c (DIE 0x57CEA), eds_break.c (DIE 0x5C220), eds_record.c (DIE 0x5CADF)
 */
#ifndef DDR_types_play_loop_w_H
#define DDR_types_play_loop_w_H

struct play_loop_w {   // size 0x8008
    /* 0x000 */ int play_loop_step;                   // 0x4
    /* 0x004 */ int select_step;                      // 0x4
    /* 0x008 */ unsigned int game_mode_memory[8192];  // 0x8000
};

#endif /* DDR_types_play_loop_w_H */
