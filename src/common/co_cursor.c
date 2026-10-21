#include "src/common/co_cursor.h"

float sinf(float x);
int func_001B7AC8(int a);
void func_00127F60(anon_0_105 *info, int tex_id);
void func_001234E0(anon_2_105 *ft4);
void func_001B7C30(void *p, int n);

void co_cursor01_init(struct _tag_cCoCursor01 *p)
{
    func_001B7C30(p, 0xC);
    p->old_x = 2764.0f;
    p->old_y = 2764.0f;
}

static inline void co_cursor01_quad(anon_2_105 *ft4, anon_0_105 *info, int dir, float x, float y, float mxy, float u, float v, int pri, int bri, int a, int tex_id)
{
    float x0;
    float y0;
    float x1;
    float y2;
    float y3;

    if (dir == 1) {
        x0 = x + mxy;
        y0 = y - 6.0f;
        x1 = 10.0f + x0;
        y2 = 12.0f + y0;
        y3 = y2;
    } else if (dir == 2) {
        x0 = x - 5.0f;
        y0 = y + mxy;
        x1 = 10.0f + x0;
        y2 = 12.0f + y0;
        y3 = y2;
    } else if (dir == 3) {
        x0 = x - 5.0f;
        y0 = y - 12.0f - mxy;
        x1 = 10.0f + x0;
        y2 = y0;
        y3 = y0;
    } else {
        x0 = x - 10.0f - mxy;
        y0 = y - 6.0f;
        x1 = 10.0f + x0;
        y2 = 12.0f + y0;
        y3 = y2;
    }
    func_00127F60(info, tex_id);
    ft4->flg = 0;
    ft4->flg |= 0x100;
    ft4->q0 = 1.0f;
    ft4->q1 = 1.0f;
    ft4->q2 = 1.0f;
    ft4->q3 = 1.0f;
    ft4->s0 = u / info->rw;
    ft4->t0 = v / info->rh;
    ft4->s1 = (u + 10.0f) / info->rw;
    ft4->t1 = v / info->rh;
    ft4->s2 = u / info->rw;
    ft4->t2 = (v + 12.0f) / info->rh;
    ft4->s3 = (u + 10.0f) / info->rw;
    ft4->t3 = (v + 12.0f) / info->rh;
    ft4->r0 = bri;
    ft4->g0 = bri;
    ft4->b0 = bri;
    ft4->a0 = a;
    ft4->x0.fd = x0;
    ft4->y0.fd = y0;
    ft4->z0 = pri;
    ft4->x1.fd = x1;
    ft4->y1.fd = y0;
    ft4->z1 = pri;
    ft4->x2.fd = x0;
    ft4->y2.fd = y2;
    ft4->z2 = pri;
    ft4->x3.fd = x1;
    ft4->y3.fd = y3;
    ft4->z3 = pri;
    func_001234E0(ft4);
}

void co_cursor01_disp(struct _tag_cCoCursor01 *p, float x, float y, int a, int bri, int pri, int tex_id, int flag)
{
    anon_0_105 info;
    anon_2_105 ft4;
    int anime;
    int dir;
    float mxy;
    float u;
    float v;
    int koma;

    if (p->old_x != x)
        p->counter = 0;
    if (p->old_y != y)
        p->counter = 0;
    anime = flag & 0xF;
    if (anime == 1) {
        if (p->counter > 120) {
            koma = p->counter - 120;
            mxy = 10.0f * sinf(3.141592f * koma / 30.0f);
            mxy = func_001B7AC8(mxy);
        }
    } else
        mxy = 0.0f;
    dir = (flag >> 4) & 0xF;
    u = 0.0f;
    v = u;
    if (dir == 1)
        v = 24.0f;
    else if (dir == 2)
        v = 12.0f;
    else if (dir == 3)
        v = 36.0f;
    if (anime == 2) {
        koma = (p->counter % 60) / 10;
        if (koma == 1 || koma == 5)
            u += 10.0f;
        else if (koma == 2 || koma == 4)
            u += 20.0f;
        else if (koma == 3)
            u += 30.0f;
    }
    co_cursor01_quad(&ft4, &info, dir, x, y, mxy, u, v, pri, bri, a, tex_id);
    p->old_x = x;
    p->old_y = y;
    p->counter++;
}
