#include "src/AM/s573/doll/matrix.h"
typedef float sceVu0FVECTOR[4];
void func_00102E90(sceVu0FVECTOR *m);
void sceVu0RotMatrixX(sceVu0FVECTOR *m0, sceVu0FVECTOR *m1, float rx);
void sceVu0RotMatrixY(sceVu0FVECTOR *m0, sceVu0FVECTOR *m1, float ry);
void sceVu0RotMatrixZ(sceVu0FVECTOR *m0, sceVu0FVECTOR *m1, float rz);












void convert_matrix_dx2ps(sceVu0FVECTOR *m0, anon_0_16 *m1)
{
    m1->m[0][0] = m0[0][0] * 4096.0f;
    m1->m[0][1] = m0[0][1] * 4096.0f;
    m1->m[0][2] = m0[0][2] * 4096.0f;
    m1->m[1][0] = m0[1][0] * 4096.0f;
    m1->m[1][1] = m0[1][1] * 4096.0f;
    m1->m[1][2] = m0[1][2] * 4096.0f;
    m1->m[2][0] = m0[2][0] * 4096.0f;
    m1->m[2][1] = m0[2][1] * 4096.0f;
    m1->m[2][2] = m0[2][2] * 4096.0f;
    m1->t[0] = m0[3][0];
    m1->t[1] = m0[3][1];
    m1->t[2] = m0[3][2];
}




void convert_matrix_ps2dx(sceVu0FVECTOR *m0, anon_0_16 *m1)
{
    m0[0][0] = m1->m[0][0] / 4096.0f;
    m0[0][1] = m1->m[0][1] / 4096.0f;
    m0[0][2] = m1->m[0][2] / 4096.0f;
    m0[1][0] = m1->m[1][0] / 4096.0f;
    m0[1][1] = m1->m[1][1] / 4096.0f;
    m0[1][2] = m1->m[1][2] / 4096.0f;
    m0[2][0] = m1->m[2][0] / 4096.0f;
    m0[2][1] = m1->m[2][1] / 4096.0f;
    m0[2][2] = m1->m[2][2] / 4096.0f;
    m0[3][0] = m1->t[0];
    m0[3][1] = m1->t[1];
    m0[3][2] = m1->t[2];
    m0[0][3] = m0[1][3] = m0[2][3] = 0.0f;
    m0[3][3] = 1.0f;
}























void CreateRotMatrixY(sceVu0FVECTOR *mat, float deg)
{
    func_00102E90(mat);
    sceVu0RotMatrixY(mat, mat, deg);
}

void CreateRotMatrixZ(sceVu0FVECTOR *mat, float deg)
{
    func_00102E90(mat);
    sceVu0RotMatrixZ(mat, mat, deg);
}

void CreateRotMatrixX(sceVu0FVECTOR *mat, float deg)
{
    func_00102E90(mat);
    sceVu0RotMatrixX(mat, mat, deg);
}
