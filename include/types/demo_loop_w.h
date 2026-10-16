/* struct demo_loop_w -- 3 members, size 0x8008, layout c17da91147fc.
 *
 * One definition, agreed by the 6 units that declare it: eds_select.c (DIE 0x41563).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct demo_loop_w *`.
 *
 * declared by: eds_select.c (DIE 0x41563), eds_main.c (DIE 0x48C8C), eds_win.c (DIE 0x4FD5F), eds_aid.c (DIE 0x57933), eds_break.c (DIE 0x5BF1D), eds_record.c (DIE 0x5FD48)
 */
#ifndef DDR_types_demo_loop_w_H
#define DDR_types_demo_loop_w_H

struct demo_loop_w {   // size 0x8008
    /* 0x000 */ int demo_loop_step;                   // 0x4
    /* 0x004 */ int loop_ntimes;                      // 0x4
    /* 0x008 */ unsigned int game_mode_memory[8192];  // 0x8000
};

#endif /* DDR_types_demo_loop_w_H */
