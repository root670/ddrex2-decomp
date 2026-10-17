/*
 * C:\work2\usaex2\src\sys\sys_demo.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001B3D70-0x001B3D88
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_sys_sys_demo_c_H
#define DDR_UNIT_src_sys_sys_demo_c_H

#include "types/_tag_SYS_DEMO_WORK.h"

/* variables (1) */
struct _tag_SYS_DEMO_WORK *pdemo;                                /* @0x002DE48C size 0x4 */

/* functions defined (2) */
void sysDemoSetMainLoopBreakRequest(int val);                    /* 0x001B3D70-0x001B3D7C lines 80-81 */
void sysDemoSet(struct _tag_SYS_DEMO_WORK *p);                   /* 0x001B3D80-0x001B3D88 lines 54-54 */

#endif /* DDR_UNIT_src_sys_sys_demo_c_H */
