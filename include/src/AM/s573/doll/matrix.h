/*
 * C:\work2\usaex2\src\AM\s573\doll\matrix.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x001C7430-0x001C7730
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_matrix_c_H
#define DDR_UNIT_src_AM_s573_doll_matrix_c_H

/* anonymous types (1) */

/* anon_0_16 -- @anon0, 0x20 bytes, matrix.c (DIE 0x23ED0) */
struct anon_0_16 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xC
};


/* functions defined (5) */
void CreateRotMatrixX(float (*mat)[4], float deg);               /* 0x001C7430-0x001C7470 lines 91-94 */
void CreateRotMatrixZ(float (*mat)[4], float deg);               /* 0x001C7470-0x001C74B0 lines 85-88 */
void CreateRotMatrixY(float (*mat)[4], float deg);               /* 0x001C74B0-0x001C74F0 lines 79-82 */
void convert_matrix_ps2dx(float (*m0)[4], struct anon_0_16 *m1); /* 0x001C74F0-0x001C760C lines 40-54 */
void convert_matrix_dx2ps(float (*m0)[4], struct anon_0_16 *m1); /* 0x001C7610-0x001C7730 lines 21-33 */

#endif /* DDR_UNIT_src_AM_s573_doll_matrix_c_H */
