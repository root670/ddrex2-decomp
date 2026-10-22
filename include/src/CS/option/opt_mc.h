/*
 * C:\work2\usaex2\src\CS\option\opt_mc.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 6 functions, code 0x007F33A0-0x007F375C
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
#ifndef DDR_UNIT_src_CS_option_opt_mc_c_H
#define DDR_UNIT_src_CS_option_opt_mc_c_H

#include "types/_OPTMC_W.h"
#include "types/_OPTSYS_W.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* variables (5) */
struct _OPTMC_W *OPTMCW;                                         /* @0x002DDEF8 size 0x4 */
int RequestAutoSave;                                             /* @0x002DE1AC size 0x4 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
static struct _OPTMC_W _opt_mc_w;                                /* @0x00803770 size 0x54 */

/* functions referenced (3) */
void OptMenuInit3(struct _OPTSYS_W *);                           /* @0x007F5E50 */
void OptMcLoadMain(struct _OPTSYS_W *);                          /* @0x007F35C0 */
void OptMcSaveMain(struct _OPTSYS_W *);                          /* @0x007F3690 */

/* functions defined (6) */
static int OptMcLoadExe(void);                                   /* 0x007F33A0-0x007F34B4 lines 128-166 */
static int OptMcSaveExe(void);                                   /* 0x007F34C0-0x007F35B4 lines 90-123 */
void OptMcLoadMain(struct _OPTSYS_W *_opt);                      /* 0x007F35C0-0x007F3648 lines 63-80 */
void OptMcLoadInit(struct _OPTSYS_W *_opt);                      /* 0x007F3650-0x007F368C lines 54-60 */
void OptMcSaveMain(struct _OPTSYS_W *_opt);                      /* 0x007F3690-0x007F3718 lines 32-49 */
void OptMcSaveInit(struct _OPTSYS_W *_opt);                      /* 0x007F3720-0x007F375C lines 23-29 */

#endif /* DDR_UNIT_src_CS_option_opt_mc_c_H */
