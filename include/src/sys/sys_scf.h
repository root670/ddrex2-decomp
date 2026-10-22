/*
 * C:\work2\usaex2\src\sys\sys_scf.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x001B3D30-0x001B3D70
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A layout the shared headers already define is
 * named by its own `anon_<digest>` alias instead, so the block holds one DIE
 * for it, as retail's does.
 */
#ifndef DDR_UNIT_src_sys_sys_scf_c_H
#define DDR_UNIT_src_sys_sys_scf_c_H

#include "types/_tag_SYS_SCF_WORK.h"

/* variables (1) */
struct _tag_SYS_SCF_WORK *pscf;                                  /* @0x002DE488 size 0x4 */

/* functions defined (2) */
int sysGetDateNotation(void);                                    /* 0x001B3D30-0x001B3D3C lines 50-51 */
void sysInitScf(struct _tag_SYS_SCF_WORK *p);                    /* 0x001B3D40-0x001B3D70 lines 24-43 */

#endif /* DDR_UNIT_src_sys_sys_scf_c_H */
