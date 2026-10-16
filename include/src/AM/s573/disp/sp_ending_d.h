/*
 * C:\work\usam2\src\AM\s573\disp\sp_ending_d.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x0022ae60-0x0022af30
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_disp_sp_ending_d_c_H
#define DDR_UNIT_src_AM_s573_disp_sp_ending_d_c_H

#include "types/G_SYS_W_.h"
#include "types/ending_disp_work.h"
#include "types/g_game_w.h"

/* anonymous types (2) */

/* anon_0_14 -- @anon0, 0x4 bytes, sp_ending_d.c (DIE 0x3330c) */
struct anon_0_14 {   // size 0x4
    /* 0x000 */ unsigned char old_stat;               // 0x1
    /* 0x001 */ unsigned char cur_stat;               // 0x1
    /* 0x002 */ unsigned char release_ct;             // 0x1
    /* 0x003 */ unsigned char warning;                // 0x1
};

/* anon_1_14 -- @anon1, 0x8 bytes, sp_ending_d.c (DIE 0x35dcf) */
struct anon_1_14 {   // size 0x8
    /* 0x000 */ unsigned long number : 16;            // bits 0..15
    /* 0x000 */ unsigned long sector : 24;            // bits 16..39
    /* 0x000 */ unsigned long size : 24;              // bits 40..63
};


/* variables (3) */
struct g_game_w g_game_w;                                        /* @0x00592050 size 0xab544 */
struct G_SYS_W_ g_sys_w;                                         /* @0x0063d5a0 size 0x90 */
struct anon_1_14 zzenda_ip2[];                                   /* not allocated */

/* functions defined (2) */
int special_ending_disp_step(void);                              /* 0x0022ae60-0x0022ae68 lines 1002-1002 */
void special_ending_disp_init(void *w);                          /* 0x0022ae70-0x0022af30 lines 284-360 */

#endif /* DDR_UNIT_src_AM_s573_disp_sp_ending_d_c_H */
