/*
 * C:\work\usam2\src\sys\sys_scf.c
 * MW MIPS C Compiler, overlay main; 2 functions, code 0x0021c410-0x0021c450
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_sys_sys_scf_c_H
#define DDR_UNIT_src_sys_sys_scf_c_H

#include "types/_tag_SYS_SCF_WORK.h"

/* variables (1) */
struct _tag_SYS_SCF_WORK *pscf;                                  /* @0x002a2a78 size 0x4 */

/* functions defined (2) */
int sysGetDateNotation(void);                                    /* 0x0021c410-0x0021c41c lines 41-42 */
void sysInitScf(struct _tag_SYS_SCF_WORK *p);                    /* 0x0021c420-0x0021c450 lines 24-34 */

#endif /* DDR_UNIT_src_sys_sys_scf_c_H */
