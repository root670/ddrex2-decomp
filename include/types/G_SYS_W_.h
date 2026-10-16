/* struct G_SYS_W_ -- 9 members, size 0x90, layout ca6ae9c22d5f.
 *
 * One definition, agreed by the 4 units that declare it: les_play.c (DIE 0x11F0E).
 *
 * DWARF 1 resolves typedefs away, so the only spelling the evidence offers
 * for a use is `struct G_SYS_W_ *`.
 *
 * declared by: les_play.c (DIE 0x11F0E), onimode.c (DIE 0x2F16F), sp_ending_d.c (DIE 0x330E7), eds_select.c (DIE 0x3D501)
 */
#ifndef DDR_types_G_SYS_W__H
#define DDR_types_G_SYS_W__H

struct G_INPUT_W_;
struct tm;

#include "types/G_INPUT_W_.h"
#include "types/tm.h"

struct G_SYS_W_ {   // size 0x90
    /* 0x000 */ struct G_INPUT_W_ input_w;            // 0x50
    /* 0x050 */ struct tm start_tm;                   // 0x24
    /* 0x074 */ unsigned int v_counter;               // 0x4
    /* 0x078 */ unsigned long v_counter2;             // 0x8
    /* 0x080 */ unsigned int s_counter;               // 0x4
    /* 0x084 */ int u_counter;                        // 0x4
    /* 0x088 */ unsigned char entry_bit;              // 0x1
    /* 0x089 */ char vpf;                             // 0x1
    /* 0x08A */ char pad[2];                          // 0x2
    /* 0x08C */ // 0x4 bytes padding
};

#endif /* DDR_types_G_SYS_W__H */
