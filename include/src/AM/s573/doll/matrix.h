/*
 * C:\work\usam2\src\AM\s573\doll\matrix.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00249a10-0x00249d10
 * reconstructed from DWARF 1 by tools/oracle/emit_headers.py; offsets in hex
 *
 * C mode: a use is `struct <tag> *`, and the named types this unit needs are
 * included from include/types/.  `@anonN` is this unit's own numbering, so it
 * is named here (`anon_<N>_<unit>`) and nowhere else.
 */
#ifndef DDR_UNIT_src_AM_s573_doll_matrix_c_H
#define DDR_UNIT_src_AM_s573_doll_matrix_c_H

/* anonymous types (1) */

/* anon_0_47 -- @anon0, 0x20 bytes, matrix.c (DIE 0x82afa) */
struct anon_0_47 {   // size 0x20
    /* 0x000 */ short m[3][3];                        // 0x12
    /* 0x012 */ // 0x2 bytes padding
    /* 0x014 */ int t[3];                             // 0xc
};


/* functions defined (5) */
void CreateRotMatrixX(float (*mat)[4], float deg);               /* 0x00249a10-0x00249a50 lines 93-96 */
void CreateRotMatrixZ(float (*mat)[4], float deg);               /* 0x00249a50-0x00249a90 lines 87-90 */
void CreateRotMatrixY(float (*mat)[4], float deg);               /* 0x00249a90-0x00249ad0 lines 81-84 */
void convert_matrix_ps2dx(float (*m0)[4], struct anon_0_47 *m1); /* 0x00249ad0-0x00249bec lines 42-56 */
void convert_matrix_dx2ps(float (*m0)[4], struct anon_0_47 *m1); /* 0x00249bf0-0x00249d10 lines 23-35 */

#endif /* DDR_UNIT_src_AM_s573_doll_matrix_c_H */
