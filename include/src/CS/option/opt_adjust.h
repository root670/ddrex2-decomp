/*
 * C:\work2\usaex2\src\CS\option\opt_adjust.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 2 functions, code 0x007F0080-0x007F0600
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
#ifndef DDR_UNIT_src_CS_option_opt_adjust_c_H
#define DDR_UNIT_src_CS_option_opt_adjust_c_H

#include "types/_OPTSYS_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* variables (2) */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */

/* functions referenced (1) */
void OptMenuInit2(struct _OPTSYS_W *);                           /* @0x007F5E70 */

/* functions defined (2) */
void OptAdjustMain(struct _OPTSYS_W *_opt);                      /* 0x007F0080-0x007F0598 lines 27-135 */
void OptAdjustInit(struct _OPTSYS_W *_opt);                      /* 0x007F05A0-0x007F0600 lines 9-22 */

#endif /* DDR_UNIT_src_CS_option_opt_adjust_c_H */
