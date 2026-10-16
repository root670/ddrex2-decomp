/*
 * C:\work\usam2\src\sys\sys_demo.c
 * MW MIPS C Compiler, overlay main; 1 functions, code 0x00227B00-0x00227B08
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_sys_sys_demo_c_H
#define DDR_UNIT_src_sys_sys_demo_c_H

#include "types/_tag_SYS_DEMO_WORK.h"

/* anonymous types (1) */

/* anon_0_10 -- @anon0, 0x24 bytes, sys_demo.c (DIE 0x27EF5) */
struct anon_0_10 {   // size 0x24
    /* 0x000 */ unsigned int lsn;                     // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
    /* 0x008 */ char name[16];                        // 0x10
    /* 0x018 */ unsigned char date[8];                // 0x8
    /* 0x020 */ unsigned int flag;                    // 0x4
};


/* variables (1) */
struct _tag_SYS_DEMO_WORK *pdemo;                                /* @0x002A2AA0 size 0x4 */

/* functions defined (1) */
void sysDemoSet(struct _tag_SYS_DEMO_WORK *p);                   /* 0x00227B00-0x00227B08 lines 54-54 */

#endif /* DDR_UNIT_src_sys_sys_demo_c_H */
