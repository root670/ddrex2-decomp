/*
 * C:\work2\usaex2\src\AM\s573\doll\ps1lib.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x001CC010-0x001CC6F8
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
#ifndef DDR_UNIT_src_AM_s573_doll_ps1lib_c_H
#define DDR_UNIT_src_AM_s573_doll_ps1lib_c_H

#include "types/_GsCOORDINATE2.h"

/* functions defined (8) */
void LoadAverageShort12(anon_00dccc0f5082 *v0, anon_00dccc0f5082 *v1, int p0, int p1, anon_00dccc0f5082 *v2); /* 0x001CC010-0x001CC08C lines 177-180 */
int VectorNormalSS(anon_00dccc0f5082 *v0, anon_00dccc0f5082 *v1); /* 0x001CC090-0x001CC148 lines 159-170 */
void OuterProduct12(anon_9e7dd0ae7596 *v0, anon_9e7dd0ae7596 *v1, anon_9e7dd0ae7596 *v2); /* 0x001CC150-0x001CC1E4 lines 151-154 */
anon_b6ba1fe93475 *TransposeMatrix(anon_b6ba1fe93475 *m0, anon_b6ba1fe93475 *m1); /* 0x001CC1F0-0x001CC250 lines 137-144 */
int ps1rcos(int a);                                              /* 0x001CC250-0x001CC2A4 lines 126-128 */
int ps1rsin(int a);                                              /* 0x001CC2B0-0x001CC304 lines 121-123 */
anon_b6ba1fe93475 *PsRotMatrix(anon_00dccc0f5082 *r, anon_b6ba1fe93475 *m); /* 0x001CC310-0x001CC658 lines 45-79 */
void GsInitCoordinate2(struct _GsCOORDINATE2 *super, struct _GsCOORDINATE2 *base); /* 0x001CC660-0x001CC6F8 lines 32-40 */

#endif /* DDR_UNIT_src_AM_s573_doll_ps1lib_c_H */
