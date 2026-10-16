/* struct _EXTRA_WORK -- 5 members, size 0x10, layout 7a0d2a068152.
 *
 * One definition, agreed by the 1 unit that declares it: adv_main.c (DIE 0x290291).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct _EXTRA_WORK *`.
 *
 * declared by: adv_main.c (DIE 0x290291)
 */
#ifndef DDR_types__EXTRA_WORK_H
#define DDR_types__EXTRA_WORK_H

struct _EXTRA_WORK {   // size 0x10
    /* 0x000 */ short step;                           // 0x2
    /* 0x002 */ short cursor;                         // 0x2
    /* 0x004 */ int decide;                           // 0x4
    /* 0x008 */ int timer;                            // 0x4
    /* 0x00C */ int tex_id_top;                       // 0x4
};

#endif /* DDR_types__EXTRA_WORK_H */
