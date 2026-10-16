/*
 * C:\work\usam2\src\AM\s573\doll\ps1lib.c
 * MW MIPS C Compiler, overlay main; 8 functions, code 0x0024e2c0-0x0024e9a8
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_ps1lib_c_H
#define DDR_UNIT_src_AM_s573_doll_ps1lib_c_H

#include "types/_GsCOORDINATE2.h"

/* anonymous types (4) */

/* anon_0_52 -- @anon0, 0x20 bytes, ps1lib.c (DIE 0x8f4d7) */
struct anon_0_52 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xc
};

/* anon_1_52 -- @anon1, 0x8 bytes, ps1lib.c (DIE 0x8f536) */
struct anon_1_52 {   // size 0x8
    /* 0x000 */ short vx;                             // 0x2
    /* 0x002 */ short vy;                             // 0x2
    /* 0x004 */ short vz;                             // 0x2
    /* 0x006 */ short pad;                            // 0x2
};

/* anon_2_52 -- @anon2, 0x10 bytes, ps1lib.c (DIE 0x8f6d4) */
struct anon_2_52 {   // size 0x10
    /* 0x000 */ int vx;                               // 0x4
    /* 0x004 */ int vy;                               // 0x4
    /* 0x008 */ int vz;                               // 0x4
    /* 0x00c */ int pad;                              // 0x4
};

/* anon_3_52 -- @anon3, 0x28 bytes, ps1lib.c (DIE 0x8f7de) */
struct anon_3_52 {   // size 0x28
    /* 0x000 */ struct anon_2_52 scale;               // 0x10
    /* 0x010 */ struct anon_1_52 rotate;              // 0x8
    /* 0x018 */ struct anon_2_52 trans;               // 0x10
};


/* functions defined (8) */
void LoadAverageShort12(struct anon_1_52 *v0, struct anon_1_52 *v1, int p0, int p1, struct anon_1_52 *v2); /* 0x0024e2c0-0x0024e33c lines 179-182 */
int VectorNormalSS(struct anon_1_52 *v0, struct anon_1_52 *v1);  /* 0x0024e340-0x0024e3f8 lines 161-172 */
void OuterProduct12(struct anon_2_52 *v0, struct anon_2_52 *v1, struct anon_2_52 *v2); /* 0x0024e400-0x0024e494 lines 153-156 */
struct anon_0_52 *TransposeMatrix(struct anon_0_52 *m0, struct anon_0_52 *m1); /* 0x0024e4a0-0x0024e500 lines 139-146 */
int ps1rcos(int a);                                              /* 0x0024e500-0x0024e554 lines 128-130 */
int ps1rsin(int a);                                              /* 0x0024e560-0x0024e5b4 lines 123-125 */
struct anon_0_52 *PsRotMatrix(struct anon_1_52 *r, struct anon_0_52 *m); /* 0x0024e5c0-0x0024e908 lines 47-81 */
void GsInitCoordinate2(struct _GsCOORDINATE2 *super, struct _GsCOORDINATE2 *base); /* 0x0024e910-0x0024e9a8 lines 34-42 */

#endif /* DDR_UNIT_src_AM_s573_doll_ps1lib_c_H */
