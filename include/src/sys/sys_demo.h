/*
 * C:\work2\usaex2\src\sys\sys_demo.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001B3D70-0x001B3D88
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

/* anon_0_1 -- @anon0, 0x24 bytes, sys_demo.c (DIE 0x621) */
struct anon_0_1 {   // size 0x24
    /* 0x000 */ unsigned int lsn;                     // 0x4
    /* 0x004 */ unsigned int size;                    // 0x4
    /* 0x008 */ char name[16];                        // 0x10
    /* 0x018 */ unsigned char date[8];                // 0x8
    /* 0x020 */ unsigned int flag;                    // 0x4
};


/* variables (1) */
struct _tag_SYS_DEMO_WORK *pdemo;                                /* @0x002DE48C size 0x4 */

/* functions defined (2) */
void sysDemoSetMainLoopBreakRequest(int val);                    /* 0x001B3D70-0x001B3D7C lines 80-81 */
void sysDemoSet(struct _tag_SYS_DEMO_WORK *p);                   /* 0x001B3D80-0x001B3D88 lines 54-54 */

#endif /* DDR_UNIT_src_sys_sys_demo_c_H */
