/*
 * C:\work2\usaex2\src\AM\s573\doll\ps1lib.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x001CC010-0x001CC6F8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so an
 * anonymous type is declared here (`anon_<N>_<unit>`) and nowhere else -- as a
 * typedef of an *unnamed* aggregate, which is the spelling the compiler
 * records back as `@anonN`.  A named type's anonymous member is spelled
 * inline in the shared header that defines it, and is not declared again.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_ps1lib_c_H
#define DDR_UNIT_src_AM_s573_doll_ps1lib_c_H

#include "types/_GsCOORDINATE2.h"

/* anonymous types (3) */

/* anon_0_21 -- @anon0, 0x8 bytes, ps1lib.c (DIE 0x30E2F) */
typedef struct {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
} anon_0_21;

/* anon_1_21 -- @anon1, 0x20 bytes, ps1lib.c (DIE 0x30ECB) */
typedef struct {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
} anon_1_21;

/* anon_2_21 -- @anon2, 0x10 bytes, ps1lib.c (DIE 0x30F98) */
typedef struct {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00C */ int pad;                              // 0x4
} anon_2_21;


/* functions defined (8) */
void LoadAverageShort12(anon_0_21 *v0, anon_0_21 *v1, int p0, int p1, anon_0_21 *v2); /* 0x001CC010-0x001CC08C lines 177-180 */
int VectorNormalSS(anon_0_21 *v0, anon_0_21 *v1);                /* 0x001CC090-0x001CC148 lines 159-170 */
void OuterProduct12(anon_2_21 *v0, anon_2_21 *v1, anon_2_21 *v2); /* 0x001CC150-0x001CC1E4 lines 151-154 */
anon_1_21 *TransposeMatrix(anon_1_21 *m0, anon_1_21 *m1);        /* 0x001CC1F0-0x001CC250 lines 137-144 */
int ps1rcos(int a);                                              /* 0x001CC250-0x001CC2A4 lines 126-128 */
int ps1rsin(int a);                                              /* 0x001CC2B0-0x001CC304 lines 121-123 */
anon_1_21 *PsRotMatrix(anon_0_21 *r, anon_1_21 *m);              /* 0x001CC310-0x001CC658 lines 45-79 */
void GsInitCoordinate2(struct _GsCOORDINATE2 *super, struct _GsCOORDINATE2 *base); /* 0x001CC660-0x001CC6F8 lines 32-40 */

#endif /* DDR_UNIT_src_AM_s573_doll_ps1lib_c_H */
