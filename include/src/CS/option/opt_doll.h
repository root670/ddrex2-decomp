/*
 * C:\work2\usaex2\src\CS\option\opt_doll.c
 * MW MIPS C Compiler, overlay opt_rel4cd.prg; 1 functions, code 0x007F0600-0x007F07E4
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
#ifndef DDR_UNIT_src_CS_option_opt_doll_c_H
#define DDR_UNIT_src_CS_option_opt_doll_c_H

#include "types/_OPTSYS_W.h"
#include "types/_tag_OptDoll.h"
#include "types/_tag_cDDR8SaveData.h"
#include "types/oni_course.h"

/* anonymous types (2) */

/* anon_8_226 -- @anon8, 0x31 bytes, opt_doll.c (DIE 0x433AD4) */
typedef struct {   // size 0x31
    /* 0x000 */ char n;                               // 0x1
    /* 0x001 */ char id[48];                          // 0x30
} anon_8_226;

/* anon_9_226 -- @anon9, 0x8 bytes, opt_doll.c (DIE 0x433E87) */
typedef struct {   // size 0x8
    /* 0x000 */ short x;                              // 0x2
    /* 0x002 */ short y;                              // 0x2
    /* 0x004 */ short w;                              // 0x2
    /* 0x006 */ short h;                              // 0x2
} anon_9_226;


/* variables (4) */
static anon_9_226 crect;                                         /* @0x002DDEE8 size 0x8 */
struct _tag_cDDR8SaveData SaveData;                              /* @0x00308AD0 size 0x1FF50 */
struct _OPTSYS_W *OPTSYSW;                                       /* @0x002DDEF0 size 0x4 */
anon_8_226 lst;                                                  /* not allocated size 0x31 */

/* functions defined (1) */
int View_OptDoll(void);                                          /* 0x007F0600-0x007F07E4 lines 106-203 */

#endif /* DDR_UNIT_src_CS_option_opt_doll_c_H */
