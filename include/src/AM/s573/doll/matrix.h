/*
 * C:\work\usam2\src\AM\s573\doll\matrix.c
 * MW MIPS C Compiler, overlay main; 5 functions, code 0x00249A10-0x00249D10
 * reconstructed from DWARF 1 by tools/dwarf1.py; offsets in hex
 */

/* functions defined (5) */
void CreateRotMatrixX(float (*mat)[4], float deg);               /* 0x00249A10-0x00249A50 lines 93-96 */
void CreateRotMatrixZ(float (*mat)[4], float deg);               /* 0x00249A50-0x00249A90 lines 87-90 */
void CreateRotMatrixY(float (*mat)[4], float deg);               /* 0x00249A90-0x00249AD0 lines 81-84 */
void convert_matrix_ps2dx(float (*m0)[4], struct @anon0 *m1);    /* 0x00249AD0-0x00249BEC lines 42-56 */
void convert_matrix_dx2ps(float (*m0)[4], struct @anon0 *m1);    /* 0x00249BF0-0x00249D10 lines 23-35 */
