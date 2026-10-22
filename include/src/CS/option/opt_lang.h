/*
 * C:\work2\usaex2\src\CS\option\opt_lang.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 2 functions, code 0x007F1BC0-0x007F1FC0
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
#ifndef DDR_UNIT_src_CS_option_opt_lang_c_H
#define DDR_UNIT_src_CS_option_opt_lang_c_H

#include "types/G_SYS_W_.h"
#include "types/_OPTSYS_W.h"

/* variables (2) */
struct G_SYS_W_ g_sys_w;                                         /* @0x006B4840 size 0x98 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */

/* functions referenced (2) */
void OptMenuInit3(struct _OPTSYS_W *);                           /* @0x007F5E50 */
void OptLangMain(struct _OPTSYS_W *);                            /* @0x007F1BC0 */

/* functions defined (2) */
void OptLangMain(struct _OPTSYS_W *_opt);                        /* 0x007F1BC0-0x007F1F80 lines 31-104 */
void OptLangInit(struct _OPTSYS_W *_opt);                        /* 0x007F1F80-0x007F1FC0 lines 23-28 */

#endif /* DDR_UNIT_src_CS_option_opt_lang_c_H */
