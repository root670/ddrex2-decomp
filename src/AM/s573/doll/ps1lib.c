#include "src/AM/s573/doll/ps1lib.h"

typedef float sceVu0FVECTOR[4];

void sceVu0Normalize(sceVu0FVECTOR v0, sceVu0FVECTOR v1);
float cosf(float x);
float sinf(float x);

void GsInitCoordinate2(struct _GsCOORDINATE2 *super, struct _GsCOORDINATE2 *base)
{
    anon_b6ba1fe93475 *m;
    int i, j;

    m = &base->coord;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            m->m[i][j] = 0;
        m->m[i][i] = 0x1000;
    }
    m->t[0] = m->t[1] = m->t[2] = 0;
    base->flg = 0;
    base->workm = *m;
    base->super = super;
}

int ps1rsin(int a)
{
    return (int)(4096.0f * sinf(0.017453292f * (0.087890625f * a)));
}

int ps1rcos(int a)
{
    return (int)(4096.0f * cosf(0.017453292f * (0.087890625f * a)));
}

anon_b6ba1fe93475 *TransposeMatrix(anon_b6ba1fe93475 *m0, anon_b6ba1fe93475 *m1)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            m1->m[i][j] = m0->m[j][i];
        m1->t[i] = m0->t[i];
    }
    return m1;
}

void OuterProduct12(anon_9e7dd0ae7596 *v0, anon_9e7dd0ae7596 *v1, anon_9e7dd0ae7596 *v2)
{
    v2->vx = (v0->vy * v1->vz - v0->vz * v1->vy) / 4096;
    v2->vy = (v0->vz * v1->vx - v0->vx * v1->vz) / 4096;
    v2->vz = (v0->vx * v1->vy - v0->vy * v1->vx) / 4096;
}

int VectorNormalSS(anon_00dccc0f5082 *v0, anon_00dccc0f5082 *v1)
{
    float v[4];
    float nv[4];

    v[0] = v0->vx;
    v[1] = v0->vy;
    v[2] = v0->vz;
    sceVu0Normalize(nv, v);
    v1->vx = (int)(nv[0] * 4096.0f);
    v1->vy = (int)(nv[1] * 4096.0f);
    v1->vz = (int)(nv[2] * 4096.0f);
    return 1;
}

void LoadAverageShort12(anon_00dccc0f5082 *v0, anon_00dccc0f5082 *v1, int p0, int p1, anon_00dccc0f5082 *v2)
{
    v2->vx = (v0->vx * p0 + v1->vx * p1) / 4096;
    v2->vy = (v0->vy * p0 + v1->vy * p1) / 4096;
    v2->vz = (v0->vz * p0 + v1->vz * p1) / 4096;
}

anon_b6ba1fe93475 *PsRotMatrix(anon_00dccc0f5082 *r, anon_b6ba1fe93475 *m)
{
    int cx;
    int sx;
    int cy;
    int sz;
    int sy;
    int cz;
    int i;
    int j;

    cx = (int)(4096.0f * cosf(0.017453292f * (0.087890625f * r->vx)));
    sx = (int)(4096.0f * sinf(0.017453292f * (0.087890625f * r->vx)));
    cy = (int)(4096.0f * cosf(0.017453292f * (0.087890625f * r->vy)));
    sy = (int)(4096.0f * sinf(0.017453292f * (0.087890625f * r->vy)));
    cz = (int)(4096.0f * cosf(0.017453292f * (0.087890625f * r->vz)));
    sz = (int)(4096.0f * sinf(0.017453292f * (0.087890625f * r->vz)));
    m->m[0][2] = sy;
    m->m[1][2] = -(sx * cy) / 4096;
    m->m[2][2] = cx * cy / 4096;
    m->m[0][0] = cy * cz / 4096;
    m->m[0][1] = -(cy * sz) / 4096;
    i = sy * cz / 4096;
    m->m[1][0] = sx * i / 4096 + cx * sz / 4096;
    m->m[2][0] = -cx * i / 4096 + sx * sz / 4096;
    j = sy * sz / 4096;
    m->m[1][1] = -sx * j / 4096 + cx * cz / 4096;
    m->m[2][1] = cx * j / 4096 + sx * cz / 4096;
    return m;
}
